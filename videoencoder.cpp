#include "videoencoder.h"
#include <QDebug>

VideoEncoder::VideoEncoder(int targetWidth, int targetHeight, int fps)
    : m_targetWidth(targetWidth), m_targetHeight(targetHeight), m_fps(fps)
{
}

VideoEncoder::~VideoEncoder()
{
    this->stop();
    releaseResources();
}

void VideoEncoder::setTargetResolution(int width, int height) {
    QMutexLocker locker(&m_mutex);
    if (m_targetWidth != width || m_targetHeight != height) {
        m_targetWidth = width;
        m_targetHeight = height;
        m_targetResolutionChanged = true;
        m_condition.wakeOne(); // 唤醒子线程以更新编码器配置
    }
}

void VideoEncoder::pushFrame(const QImage& img) {
    QMutexLocker locker(&m_mutex);
    // 编码线程跟不上时进行丢帧
    if (m_frameQueue.size() >= 5) {
        return;
    }
    m_frameQueue.append(img);
    m_condition.wakeOne();
}

void VideoEncoder::stop() {
    {
        QMutexLocker locker(&m_mutex);
        m_stop = true;
        m_condition.wakeOne();
    }
    if (isRunning()) {
        wait();
    }
}

void VideoEncoder::initEncoder(int width, int height) {
    const AVCodec* codec = avcodec_find_encoder(AV_CODEC_ID_H264);
    if (!codec) {
        qDebug() << "找不到 H264 编码器";
        return;
    }
    m_codecCtx = avcodec_alloc_context3(codec);
    m_codecCtx->width = width;
    m_codecCtx->height = height;
    m_codecCtx->time_base = {1, m_fps};
    m_codecCtx->framerate = {m_fps, 1};
    m_codecCtx->pix_fmt = AV_PIX_FMT_YUV420P;
    m_codecCtx->gop_size = m_fps / 2;
    m_codecCtx->max_b_frames = 0;  // 视频会议/直播等零延时场景禁用 B 帧
    // 根据分辨率大小动态分配码率（长x宽x帧率x画面复杂因子）
    int64_t bitrate = static_cast<int64_t>(width) * height * m_fps * 0.15;
    // 限制码率在合理区间（例如 500Kbps 到 4Mbps）避免暴涨，但也绝不能过低
    if (bitrate < 600000) bitrate = 600000;
    if (bitrate > 4000000) bitrate = 4000000;
    m_codecCtx->bit_rate = bitrate;
    // m_codecCtx->rc_buffer_size = static_cast<int>(bitrate);
    // m_codecCtx->rc_max_rate = static_cast<int>(bitrate * 1.2);
    m_codecCtx->rc_buffer_size = bitrate / m_fps;
    m_codecCtx->rc_max_rate = bitrate;
    // crf 的范围是 0-51。23 是默认值，18-22 是准无损效果。这里建议设为 21（非常清晰流畅）
    av_opt_set(m_codecCtx->priv_data, "crf", "21", 0);
    av_opt_set(m_codecCtx->priv_data, "preset", "ultrafast", 0); // 极速运行编码
    av_opt_set(m_codecCtx->priv_data, "tune", "zerolatency", 0); // 消除编码延迟
    if (avcodec_open2(m_codecCtx, codec, nullptr) < 0) {
        qDebug() << "打开编码器失败";
        return;
    }
    m_yuvFrame = av_frame_alloc();
    m_yuvFrame->format = AV_PIX_FMT_YUV420P;
    m_yuvFrame->width = width;
    m_yuvFrame->height = height;
    av_frame_get_buffer(m_yuvFrame, 0);
    // 记录下当前编码器究竟使用的分辨率
    m_currentEncoderWidth = width;
    m_currentEncoderHeight = height;
    // 初始化时将 sws 相关的缓存重置
    m_swsCtx = nullptr;
    m_srcWidth = 0;
    m_srcHeight = 0;
}

void VideoEncoder::reinitEncoder(int newWidth, int newHeight) {
    qDebug() << "正在重构编码器器，新分辨率:" << newWidth << "x" << newHeight;
    if (m_codecCtx) {
        avcodec_send_frame(m_codecCtx, nullptr);
        AVPacket* flushPkt = av_packet_alloc();
        while (avcodec_receive_packet(m_codecCtx, flushPkt) >= 0) {
            QByteArray h264Data(reinterpret_cast<char*>(flushPkt->data), flushPkt->size);
            emit newPacket(h264Data);
            av_packet_unref(flushPkt);
        }
        av_packet_free(&flushPkt);
    }
    if (m_swsCtx) {
        sws_freeContext(m_swsCtx);
        m_swsCtx = nullptr;
    }
    if (m_yuvFrame) {
        av_frame_free(&m_yuvFrame);
        m_yuvFrame = nullptr;
    }
    if (m_codecCtx) {
        avcodec_free_context(&m_codecCtx);
        m_codecCtx = nullptr;
    }
    initEncoder(newWidth, newHeight);
}

bool VideoEncoder::encodeFrame(const QImage& img, AVPacket* pkt) {
    QImage rgbaImg = img.convertToFormat(QImage::Format_RGBA8888);
    if (rgbaImg.isNull()) {
        return false;
    }
    int srcW = rgbaImg.width();
    int srcH = rgbaImg.height();
    // 重新制作 sws 映射，将输入分辨率 (srcW x srcH) 转换并缩放到目标的 (m_currentEncoderWidth x m_currentEncoderHeight)
    if (!m_swsCtx || m_srcWidth != srcW || m_srcHeight != srcH) {
        if (m_swsCtx) {
            sws_freeContext(m_swsCtx);
        }
        m_srcWidth = srcW;
        m_srcHeight = srcH;
        // 虽然多耗费几微秒，但是像素边缘清晰度会呈指数级上升，彻底解决“糊”的问题。
        m_swsCtx = sws_getContext(m_srcWidth, m_srcHeight, AV_PIX_FMT_RGBA,
                                  m_currentEncoderWidth, m_currentEncoderHeight, AV_PIX_FMT_YUV420P,
                                  SWS_BICUBIC, nullptr, nullptr, nullptr);
    }

    const uint8_t* inData[1] = { rgbaImg.bits() };
    int inLinesize[1] = { static_cast<int>(rgbaImg.bytesPerLine()) };
    // 将任何大小的相机输入自动且高清地缩放裁剪填充到 YUV 当前设定的图层上
    sws_scale(m_swsCtx, inData, inLinesize, 0, m_srcHeight,  // 这里的输入是真实的 m_srcHeight
              m_yuvFrame->data, m_yuvFrame->linesize);
    m_yuvFrame->pts = m_frameCount++;
    // H264 编码并发送
    if (avcodec_send_frame(m_codecCtx, m_yuvFrame) >= 0) {
        while (avcodec_receive_packet(m_codecCtx, pkt) >= 0) {
            QByteArray h264Data(reinterpret_cast<char*>(pkt->data), pkt->size);
            emit newPacket(h264Data);
            av_packet_unref(pkt);
        }
        return true;
    }
    return false;
}

void VideoEncoder::run() {
    resetState();
    int initW, initH;
    {
        QMutexLocker locker(&m_mutex);
        initW = m_targetWidth;
        initH = m_targetHeight;
        m_targetResolutionChanged = false;
    }

    initEncoder(initW, initH);
    AVPacket* pkt = av_packet_alloc();
    while (true) {
        QImage img;
        bool targetChanged = false;
        int reqW = 0, reqH = 0;

        {
            QMutexLocker locker(&m_mutex);
            while (m_frameQueue.isEmpty() && !m_stop && !m_targetResolutionChanged) {
                m_condition.wait(&m_mutex);
            }
            // 1. 如果是用户通过 UI 修改了编码目标分辨率，我们将重建标志捞出
            if (m_targetResolutionChanged) {
                targetChanged = true;
                reqW = m_targetWidth;
                reqH = m_targetHeight;
                m_targetResolutionChanged = false;
            }
            // 退出条件
            if (m_stop && m_frameQueue.isEmpty()) {
                break;
            }
            if (!m_frameQueue.isEmpty()) {
                img = m_frameQueue.takeFirst();
            }
        }
        if (targetChanged && reqW > 0 && reqH > 0) {
            reinitEncoder(reqW, reqH);
        }
        if (img.isNull()) {
            continue;
        }
        encodeFrame(img, pkt);
    }
    av_packet_free(&pkt);
}

void VideoEncoder::releaseResources() {
    if (m_swsCtx) {
        sws_freeContext(m_swsCtx);
        m_swsCtx = nullptr;
    }
    if (m_yuvFrame) {
        av_frame_free(&m_yuvFrame);
        m_yuvFrame = nullptr;
    }
    if (m_codecCtx) {
        avcodec_free_context(&m_codecCtx);
        m_codecCtx = nullptr;
    }
}

void VideoEncoder::resetState()
{
    m_frameCount = 0;
    m_srcWidth = 0;
    m_srcHeight = 0;
    m_targetResolutionChanged = false;
}

#include "videodecoder.h"
#include <QDebug>
#include <QElapsedTimer>

VideoDecoder::VideoDecoder(QObject *parent)
    : QThread(parent)
{
    if(!init()){
        qDebug()<<"初始化失败";
    }
}

VideoDecoder::~VideoDecoder()
{
    stop();
}

bool VideoDecoder::init()
{
    m_codecCtx = avcodec_find_decoder(AV_CODEC_ID_H264);
    if (!m_codecCtx) {
        qDebug() << "错误: 找不到 H264 解码器";
        return false;
    }
    m_codecContext = avcodec_alloc_context3(m_codecCtx);
    if (!m_codecContext) {
        qDebug() << "错误: 无法分配解码器上下文";
        return false;
    }
    m_codecContext->thread_count = 1;
    m_codecContext->flags |= AV_CODEC_FLAG_LOW_DELAY;
    m_codecContext->flags2 |= AV_CODEC_FLAG2_FAST;
    if (avcodec_open2(m_codecContext, m_codecCtx, nullptr) < 0) {
        qDebug() << "错误: 无法打开解码器";
        freeResources();
        return false;
    }
    m_decodedFrame = av_frame_alloc();
    m_packet = av_packet_alloc();

    if (!m_decodedFrame || !m_packet) {
        qDebug() << "错误: 无法分配帧/包缓存";
        freeResources();
        return false;
    }

    m_width = 0;
    m_height = 0;

    qDebug() << "H264 解码器初始化成功";
    return true;
}

void VideoDecoder::decodeData(const QByteArray &h264Data)
{
    QMutexLocker locker(&m_mutex);

    // 限制队列大小，避免内存堆积，丢弃旧数据
    if (m_dataQueue.size() >= 3) {
        m_dataQueue.dequeue();
    }

    m_dataQueue.append(h264Data);
    m_condition.wakeOne();
}

void VideoDecoder::stop()
{
    {
        QMutexLocker locker(&m_mutex);
        m_stop = true;
        m_condition.wakeOne();
    }
    if (isRunning()) {
        wait();
    }
}

void VideoDecoder::run()
{
    if (!m_codecContext) {
        qDebug() << "解码器未初始化";
        return;
    }

    QElapsedTimer timer;

    while (true) {
        QByteArray h264Data;

        {
            QMutexLocker locker(&m_mutex);
            while (m_dataQueue.isEmpty() && !m_stop) {
                m_condition.wait(&m_mutex);
            }
            if (m_stop && m_dataQueue.isEmpty()) {
                break;
            }
            if (!m_dataQueue.isEmpty()) {
                h264Data = m_dataQueue.dequeue();
            }
        }
        if (h264Data.isEmpty()) {
            continue;
        }
        if (!m_packet || !m_decodedFrame) {
            continue;
        }
        timer.start();
        m_packet->data = reinterpret_cast<uint8_t*>(const_cast<char*>(h264Data.constData()));
        m_packet->size = h264Data.size();
        if (m_packet->size <= 0) {
            continue;
        }
        int ret = avcodec_send_packet(m_codecContext, m_packet);
        if (ret < 0) {
            if (ret != AVERROR(EAGAIN)) {
                qDebug() << "错误: 发送数据包到解码器失败" << ret;
            }
            continue;
        }
        while (ret >= 0) {
            ret = avcodec_receive_frame(m_codecContext, m_decodedFrame);
            if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
                break;
            } else if (ret < 0) {
                qDebug() << "错误: 解码过程中出错" << ret;
                break;
            }
            int width = m_decodedFrame->width;
            int height = m_decodedFrame->height;
            if (width != m_width || height != m_height || !m_swsContext) {
                m_width = width;
                m_height = height;
                if (m_swsContext) {
                    sws_freeContext(m_swsContext);
                }
                m_swsContext = sws_getContext(
                    m_width, m_height, (AVPixelFormat)m_decodedFrame->format,
                    m_width, m_height, AV_PIX_FMT_RGB32,
                    SWS_FAST_BILINEAR, nullptr, nullptr, nullptr
                    );
                if (!m_swsContext) {
                    qDebug() << "创建 SWS 上下文失败";
                    continue;
                }
                qDebug() << "解码器分辨率变更:" << width << "x" << height;
            }
            QImage destImage(m_width, m_height, QImage::Format_RGB32);
            uint8_t *dstData[4] = { destImage.bits(), nullptr, nullptr, nullptr };
            int dstLinesize[4] = { static_cast<int>(destImage.bytesPerLine()), 0, 0, 0 };
            sws_scale(
                m_swsContext,
                m_decodedFrame->data,
                m_decodedFrame->linesize,
                0,
                m_height,
                dstData,
                dstLinesize
                );
            emit newFrame(destImage);
            qint64 elapsed = timer.elapsed();
            if (elapsed > 10) {
                qDebug() << "解码耗时:" << elapsed << "ms";
            }
        }
    }
    qDebug() << "解码线程退出";
    freeResources();
}

void VideoDecoder::freeResources()
{
    if (m_swsContext) {
        sws_freeContext(m_swsContext);
        m_swsContext = nullptr;
    }
    if (m_decodedFrame) {
        av_frame_free(&m_decodedFrame);
        m_decodedFrame = nullptr;
    }
    if (m_packet) {
        av_packet_free(&m_packet);
        m_packet = nullptr;
    }
    if (m_codecContext) {
        avcodec_free_context(&m_codecContext);
        m_codecContext = nullptr;
    }
    m_codecCtx = nullptr;
}

#ifndef VIODEENCODER_H
#define VIODEENCODER_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QList>
#include <QImage>

// FFmpeg Headers...
extern "C" {
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <libavutil/opt.h>
#include <libavutil/imgutils.h>
}

class VideoEncoder : public QThread {
    Q_OBJECT
public:
    VideoEncoder(int targetWidth, int targetHeight, int fps);
    ~VideoEncoder();

    void pushFrame(const QImage& img);
    void stop();

    // 👉 1. 新增：向外界暴露的“用户选择分辨率”接口
    void setTargetResolution(int width, int height);

signals:
    void newPacket(const QByteArray& data);

protected:
    void run() override;

private:
    void initEncoder(int width, int height);
    void reinitEncoder(int newWidth, int newHeight);
    bool encodeFrame(const QImage& img, AVPacket* pkt);
    void releaseResources();
    void resetState();

    // 目标（用户选择的）编码分辨率
    int m_targetWidth;
    int m_targetHeight;
    bool m_targetResolutionChanged = false; // 用户是否点击了切换分辨率

    // 当前编码器实际工作的分辨率
    int m_currentEncoderWidth = 0;
    int m_currentEncoderHeight = 0;

    // 相机输入图像的实际分辨率
    int m_srcWidth = 0;
    int m_srcHeight = 0;

    int m_fps;
    bool m_stop = false;
    int m_frameCount = 0;

    QMutex m_mutex;
    QWaitCondition m_condition;
    QList<QImage> m_frameQueue;

    // FFmpeg
    AVCodecContext* m_codecCtx = nullptr;
    SwsContext* m_swsCtx = nullptr;
    AVFrame* m_yuvFrame = nullptr;
};
#endif // VIODEENCODER_H

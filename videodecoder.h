#ifndef VIDEODECODER_H
#define VIDEODECODER_H

#include <QThread>
#include <QMutex>
#include <QQueue>
#include <QImage>
#include <QWaitCondition>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
}

class VideoDecoder : public QThread
{
    Q_OBJECT

public:
    explicit VideoDecoder(QObject *parent = nullptr);
    ~VideoDecoder();

    bool init();
    void decodeData(const QByteArray &h264Data);
    void stop();

signals:
    void newFrame(const QImage &frame);

protected:
    void run() override;

private:
    void processDecodeLoop();
    void freeResources();

    // FFmpeg 资源
    const AVCodec* m_codecCtx = nullptr;
    AVCodecContext* m_codecContext = nullptr;
    AVFrame* m_decodedFrame = nullptr;
    AVPacket* m_packet = nullptr;
    SwsContext* m_swsContext = nullptr;

    // 解码状态
    int m_width = 0;
    int m_height = 0;

    // 数据缓冲队列
    QQueue<QByteArray> m_dataQueue;
    QMutex m_mutex;
    QWaitCondition m_condition;
    bool m_stop = false;
};

#endif // VIDEODECODER_H

#ifndef CAMERAWIDGET_H
#define CAMERAWIDGET_H

#include <QWidget>
#include <QCamera>
#include <QVideoSink>
#include <QTime>

QT_BEGIN_NAMESPACE
namespace Ui {
class CameraWidget;
}
QT_END_NAMESPACE

class CameraWidget : public QWidget
{
    Q_OBJECT

public:
    CameraWidget(QWidget *parent = nullptr);
    ~CameraWidget();
    void paintEvent(QPaintEvent* ev)override;
    void enterEvent(QEnterEvent* ev)override;
    void leaveEvent(QEvent* ev)override;
    void closeEvent(QCloseEvent* ev)override;

    void startCapture();
    void setImage(const QImage& image);
    void setWidgetExchanged(bool isExchanged);
    void setConnected(bool isConnected);
    bool isConnected(){return connected;};
    void setCaller(bool isCaller);
    bool getIsCaller(){return isCaller;};
    QTime getTime();
    // void setCalling(bool isCalling);
signals:
    void outputImage(const QImage& image);
    void acceptVideo();
    void hangUp(const QTime& time);
private:
    Ui::CameraWidget *ui;
    QMediaCaptureSession* session;
    QCamera* camera;
    QVideoSink* sink;
    // QVideoFrame current_frame;
    QImage current_image;
    QTimer* timer;

    bool isCaller = false;//是否为通话发起者
    bool connected = false;//是否接通
    bool widgetExchanged = false;//是否交换了窗口显示
};
#endif // CAMERAWIDGET_H

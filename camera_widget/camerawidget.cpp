#include "camerawidget.h"
#include "ui_camerawidget.h"
#include "macro.h"

#include <QCloseEvent>
#include <QMediaCaptureSession>
#include <QPainter>
#include <QScreen>
#include <QTimer>

CameraWidget::CameraWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CameraWidget)
{
    ui->setupUi(this);
    this->setFixedSize(VIDEO_WIDTH, VIDEO_HEIGHT);

    ui->subWidget->setRangeLimit(QRect(0, 0, VIDEO_WIDTH-200, VIDEO_HEIGHT-150));

    timer_clock = new QTimer(this);
    timer_pxp = new QTimer(this);
    session = new QMediaCaptureSession(this);
    camera = new QCamera(this);
    sink = new QVideoSink(this);
    m_decoder = new VideoDecoder(this);

    timer_pxp->setSingleShot(true);
    ui->label_time->setStyleSheet("ClockLabel{"
                                  "font:20px;"
                                  "color:white;"
                                  "}");
    connect(m_decoder, &VideoDecoder::newFrame, this, [=](const QImage &image){
        this->setImage(image);
    });
    session->setCamera(camera);
    session->setVideoSink(sink);
    connect(sink,&QVideoSink::videoFrameChanged,this,[=](const QVideoFrame& frame){
        QImage image = frame.toImage();
        if(widgetExchanged){
            this->current_image = image;
            update();
        }else{
            ui->subWidget->setImage(image);
        }
        emit outputImage(image);
    });
    camera->start();

    connect(ui->btn_accept,&QPushButton::clicked,this,[=](){
        if(!connected && !isCaller){//为被叫方且还未接通
            this->setConnected(true);
            ui->btn_accept->setIcon(QIcon(":/res/shut.png"));

            emit acceptVideo();
        }else{
            this->close();
        }
    });
    connect(ui->subWidget,&PictureView::clicked,this,[=](){
        widgetExchanged = !widgetExchanged;
    });
    connect(timer_clock, &QTimer::timeout, this, [=](){
        ui->label_time->addTime(1);
    });
    connect(timer_pxp, &QTimer::timeout, this, [=](){
        current_image = QImage();
        update();
    });
}

CameraWidget::~CameraWidget()
{
    delete ui;
    if(m_decoder->isRunning()){
        m_decoder->stop();
        m_decoder->wait();
        delete m_decoder;
    }
}

void CameraWidget::paintEvent(QPaintEvent *ev)
{
    Q_UNUSED(ev);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    if(!current_image.isNull()){
        // QImage& image = this->current_image;
        // painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
        // painter.drawImage((width()-image.width())/2 , (height()-image.height())/2 , image);
        painter.drawImage(rect(), current_image);
    }else{
        painter.fillRect(rect(), Qt::black);
    }
}

void CameraWidget::enterEvent(QEnterEvent *ev)
{
    Q_UNUSED(ev);
    ui->widget_tool->show();
}

void CameraWidget::leaveEvent(QEvent *ev)
{
    Q_UNUSED(ev);
    ui->widget_tool->hide();
}

void CameraWidget::closeEvent(QCloseEvent *ev)
{
    emit hangUp(ui->label_time->getTime());
    ev->accept();
}

void CameraWidget::startCapture()
{
    camera->start();
}

void CameraWidget::setImage(const QImage &image)
{
    if(connected){//通话接通了才能显示
        if(widgetExchanged){
            ui->subWidget->setImage(image);
        }else{
            this->current_image = image;
            update();
            timer_pxp->start(500);
        }
    }
}

void CameraWidget::setH264Data(const QByteArray &data)
{
    if(!m_decoder->isRunning()){
        m_decoder->start();
    }
    m_decoder->decodeData(data);
}

void CameraWidget::setWidgetExchanged(bool isExchanged)
{
    this->widgetExchanged = isExchanged;
}

void CameraWidget::setConnected(bool isConnected)
{
    this->connected = isConnected;
    timer_clock->start(1000);
}

void CameraWidget::setCaller(bool isCaller){
    this->isCaller = isCaller;
    if(isCaller){
        ui->btn_accept->setIcon(QIcon(":/res/shut.png"));
    }
}

QTime CameraWidget::getTime()
{
    return ui->label_time->getTime();
}

#include "camerawidget.h"
#include "ui_camerawidget.h"

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
    // auto screen = QApplication::primaryScreen();
    this->resize(800,600);

    ui->subWidget->setRangeLimit(QRect(0,0,800-200,600-150));

    timer = new QTimer(this);
    session = new QMediaCaptureSession(this);
    camera = new QCamera(this);
    sink = new QVideoSink(this);

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
    connect(timer,&QTimer::timeout,this,[=](){
        ui->label_time->addTime(1);
    });
}

CameraWidget::~CameraWidget()
{
    delete ui;
}

void CameraWidget::paintEvent(QPaintEvent *ev)
{
    Q_UNUSED(ev);
    if(!current_image.isNull()){
        QImage& image = this->current_image;
        QPainter painter(this);
        painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
        painter.drawImage((width()-image.width())/2 , (height()-image.height())/2 , image);
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
        }
    }
}

void CameraWidget::setWidgetExchanged(bool isExchanged)
{
    this->widgetExchanged = isExchanged;
}

void CameraWidget::setConnected(bool isConnected)
{
    this->connected = isConnected;
    timer->start(1000);
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

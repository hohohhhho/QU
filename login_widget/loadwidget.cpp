#include "loadwidget.h"

#include <QPainter>
#include <QPainterPath>
#include <QApplication>

LoadWidget::LoadWidget(QString text,QWidget *parent)
    : QWidget{parent}
{
    this->text=text;
    this->setFixedSize(500,80);
    this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
}

void LoadWidget::paintEvent(QPaintEvent *ev)
{
    Q_UNUSED(ev);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    // painter.fillRect(this->rect(),Qt::transparent);

    QPainterPath path_background;
    path_background.addRoundedRect(this->rect(),40,40);
    QPainterPath path_progress;
    path_progress.addRoundedRect(0,0,width()*progress,height(),40,40);
    painter.setBrush(Qt::gray);
    painter.setPen(Qt::gray);
    painter.drawPath(path_background);
    painter.setBrush(QColor(244,234,42));
    painter.setPen(QColor(244,234,42));
    painter.drawPath(path_progress);

    QFont font("微软雅黑",30);
    painter.setFont(font);
    painter.setPen(Qt::black);
    painter.drawText(this->rect(),Qt::AlignCenter,text);
}

void LoadWidget::changeText(const QString &text)
{
    this->text=text;
    update();
}

void LoadWidget::changeProgress(qreal progress,const QString& text)
{
    this->text=text;
    this->progress=progress;
    update();
    QApplication::processEvents();
    if(progress==1.0f){
        emit finished();
    }
}

#include "loadwidget.h"

#include <QPainter>
#include <QPainterPath>
#include <QApplication>
#include <QMenu>
#include <QContextMenuEvent>

LoadWidget::LoadWidget(QString text,QWidget *parent)
    : QWidget{parent}
{
    this->text=text;
    this->setFixedSize(500,80);
    this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint /*| Qt::Tool*/);
    this->setAttribute(Qt::WA_TranslucentBackground);
}

void LoadWidget::paintEvent(QPaintEvent *ev)
{
    Q_UNUSED(ev);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    // painter.fillRect(this->rect(),Qt::gray);
    // painter.fillRect(0,0,width()*progress,80,QColor(244,234,42));

    QPainterPath path_border;
    path_border.addRoundedRect(rect(),40,40);

    QPainterPath path_background;
    path_background.addRoundedRect(this->rect(),40,40);
    QPainterPath path_progress;
    int w = width()*progress;

    path_progress.addRoundedRect(0,0,w,height(),40,40);
    if(w < 80){
        painter.setClipPath(path_border);
    }

    painter.setBrush(Qt::gray);
    painter.setPen(Qt::gray);
    painter.drawPath(path_background);
    painter.setBrush(QColor(244,234,42));
    painter.setPen(Qt::NoPen);
    painter.drawPath(path_progress);

    // QBitmap mask(this->size());
    // mask.fill(Qt::color0);
    // QPainter p_mask(&mask);
    // p_mask.setBrush(Qt::color1);
    // p_mask.setPen(Qt::NoPen);
    // QPainterPath path_roundedRect;
    // path_roundedRect.addRoundedRect(this->rect(),40,40);
    // p_mask.setRenderHint(QPainter::Antialiasing);
    // p_mask.drawPath(path_roundedRect);
    // this->setMask(mask);

    QFont font("微软雅黑",30);
    painter.setFont(font);
    painter.setPen(Qt::black);
    painter.drawText(this->rect(),Qt::AlignCenter,text);
}

void LoadWidget::contextMenuEvent(QContextMenuEvent *ev)
{
    QMenu* menu = new QMenu;
    QAction* act = new QAction("关闭");
    connect(act,&QAction::triggered,this,[=](){
        this->close();
    });
    menu->addAction(act);

    menu->exec(ev->globalPos());
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

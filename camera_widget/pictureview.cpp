#include "pictureview.h"

#include <QMouseEvent>
#include <QPainter>
#include <QTimer>

PictureView::PictureView(QWidget *parent)
    : QWidget{parent}
{
    m_timer = new QTimer(this);
    m_timer->setSingleShot(true);
    connect(m_timer, &QTimer::timeout, this, [=](){
        pxp = QPixmap();
        update();
    });
}

void PictureView::paintEvent(QPaintEvent *ev)
{
    Q_UNUSED(ev);
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    if(!pxp.isNull()){
        painter.drawPixmap(0,0,pxp.scaled(this->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
    }else{
        painter.fillRect(rect(), Qt::black);
    }
}

void PictureView::mousePressEvent(QMouseEvent *ev)
{
    Q_UNUSED(ev);
    this->pos_pressed = ev->globalPosition();
    this->pos_origin = pos();
    emit clicked();
}

void PictureView::mouseMoveEvent(QMouseEvent *ev)
{
    QPointF mouse_pos = ev->globalPosition();
    QPoint new_pos = pos_origin + mouse_pos.toPoint() - pos_pressed.toPoint();
    new_pos = QPoint( qBound(move_range.x() , new_pos.x() , move_range.width())
                    , qBound(move_range.y() , new_pos.y() , move_range.height()) );
    this->move(new_pos);
}

void PictureView::setImage(const QImage &image)
{
    this->pxp = QPixmap::fromImage(image);
    update();
    m_timer->start(500);//500ms内没有新帧则抛弃旧帧
}

void PictureView::setRangeLimit(QRect range)
{
    this->move_range = range;
}

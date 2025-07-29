#include "pictureview.h"

#include <QMouseEvent>
#include <QPainter>

PictureView::PictureView(QWidget *parent)
    : QWidget{parent}
{}

void PictureView::paintEvent(QPaintEvent *ev)
{
    Q_UNUSED(ev);
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    if(!pxp.isNull()){
        painter.drawPixmap(0,0,pxp.scaled(this->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
    }else{
        painter.fillRect(rect(),Qt::lightGray);
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
}

void PictureView::setRangeLimit(QRect range)
{
    this->move_range = range;
}

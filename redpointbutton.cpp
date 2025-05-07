#include "redpointbutton.h"

#include <QPainter>
#include <QPainterPath>

RedPointButton::RedPointButton(QWidget *parent)
    : MyHintPushButton{parent}
{

}

void RedPointButton::paintEvent(QPaintEvent *ev)
{
    Q_UNUSED(ev);

    MyHintPushButton::paintEvent(ev);

    if(m_num>0){
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        QRect rect;
        if(square){
            static int pad=1;
            rect=QRect(this->width()*3/4-pad,pad,this->height()/4,this->height()/4);
        }else{
            static int pad=1+this->height()/8;
            rect=QRect(this->width()*3/4,pad,this->height()-pad*2,this->height()-pad*2);
        }
        QPainterPath path;
        path.addEllipse(rect);
        painter.setBrush(Qt::red);
        painter.setPen(Qt::red);
        painter.drawPath(path);
        painter.setPen(Qt::white);
        painter.setFont(QFont("黑体"));
        painter.drawText(rect,Qt::AlignCenter,QString::number(m_num));
    }
}

void RedPointButton::setNum(int num)
{
    this->m_num=num;
    update();
}

void RedPointButton::setNotSquare()
{
    this->square=false;
    this->setMaximumSize(999,999);
}

void RedPointButton::resizeEvent(QResizeEvent *ev)
{
    Q_UNUSED(ev);
    if(square){
        this->resize(this->width(),this->width());
        this->setIconSize(this->size()*0.9);
    }else{
        this->setMinimumHeight(39);
    }
}

QSize RedPointButton::sizeHint() const
{
    return QSize(30,30);
}

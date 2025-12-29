#include "clocklabel.h"

#include <QPainter>
#include <QTime>

ClockLabel::ClockLabel(QWidget *parent)
    : QLabel{parent}
{
    h=m=s=0;
    this->setAlignment(Qt::AlignCenter);
    this->setStyleSheet("QLabel{"
                        "background-color:transparent;"
                        "border:none;"
                        "font-size:20px;"
                        "}");
}

// void ClockLabel::paintEvent(QPaintEvent *ev)
// {
//     Q_UNUSED(ev);
//     QPainter painter(this);
//     painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
// }

void ClockLabel::setTime(uint _h, uint _m, uint _s)
{
    this->h=_h;
    this->m=_m;
    this->s=_s;
    updateTime();
}

void ClockLabel::addTime(uint _s, uint _m, uint _h)
{
    s += _s;//总秒数
    _m += s/60;//秒向分钟进位
    s %= 60;//进位后的总分钟数

    m += _m;//总分钟数
    _h += m/60;//分钟向小时进位
    m %= 60;//进位后的总分钟数

    h += _h;//总小时数
    if(h > 99){
        h = 0;//防溢出
    }
    updateTime();
}

QTime ClockLabel::getTime()
{
    return QTime(h,m,s);
}

void ClockLabel::updateTime()
{
    QString text = QString("%1:%2:%3").arg(h,2,10,QChar('0')).arg(m,2,10,QChar('0')).arg(s,2,10,QChar('0'));
    this->setText(text);
}

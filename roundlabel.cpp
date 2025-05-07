#include "roundlabel.h"

#include <QPainter>
#include <QPainterPath>

RoundLabel::RoundLabel(QWidget *parent)
    : QLabel{parent}
{}

void RoundLabel::paintEvent(QPaintEvent *ev)
{
    Q_UNUSED(ev);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    // painter.fillRect(this->rect(),Qt::transparent);

    QPainterPath path_background;
    const int radius=height()/2;
    path_background.addRoundedRect(this->rect(),radius,radius);
    painter.setBrush(QColor(244,234,42,200));
    painter.setPen(QColor(244,234,42,200));
    painter.drawPath(path_background);

    // QFont font("微软雅黑",30);
    // painter.setFont(font);
    // painter.setPen(Qt::black);
    // painter.drawText(this->rect(),Qt::AlignCenter,"加载中...");

    QLabel::paintEvent(ev);
}

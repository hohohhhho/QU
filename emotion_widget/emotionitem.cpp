#include "emotionitem.h"

#include <QPainter>
#include <QFont>

EmotionItem::EmotionItem(QWidget *parent)
    : QWidget{parent}
{
    label_tooltip=new QLabel;
    label_tooltip->setWindowFlags(Qt::ToolTip | Qt::FramelessWindowHint);
    label_tooltip->setFocusPolicy(Qt::NoFocus);
    label_tooltip->setAttribute(Qt::WA_ShowWithoutActivating);
}

void EmotionItem::paintEvent(QPaintEvent *ev)
{
    Q_UNUSED(ev);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    // painter.fillRect(this->rect(),Qt::red);

    QFont font("Segoe UI Emoji");  // Windows 默认
    font.setPixelSize(this->height()*scaling);
    painter.setFont(font);
    painter.drawText(this->rect(),Qt::AlignCenter,m_emotion);
}

void EmotionItem::mousePressEvent(QMouseEvent *ev)
{
    Q_UNUSED(ev);
    emit clicked();
}

void EmotionItem::enterEvent(QEnterEvent *ev)
{
    Q_UNUSED(ev);
    if(label_tooltip && m_introduce!="无介绍"){
        label_tooltip->show();
        QPoint pos( (std::abs(this->width()-label_tooltip->width()))/2 , this->height()+1);
        label_tooltip->move(this->mapToGlobal(pos));
    }
    scaling=0.9f;
    update();
}

void EmotionItem::leaveEvent(QEvent *ev)
{
    Q_UNUSED(ev);
    if(label_tooltip->isVisible()){
        label_tooltip->close();
    }
    scaling=0.8f;
    update();
}

void EmotionItem::setEmotion(const QByteArray &emo,const QString& introduce)
{
    this->m_emotion=emo;
    this->m_introduce=introduce;
    label_tooltip->setText(introduce);
    update();
}

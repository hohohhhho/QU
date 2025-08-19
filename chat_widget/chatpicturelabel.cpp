#include "chatpicturelabel.h"

#include <QApplication>
#include <QResizeEvent>

ChatPictureLabel::ChatPictureLabel(QWidget *parent)
    : QLabel{parent}
{}

void ChatPictureLabel::resizeEvent(QResizeEvent *ev)
{
    qDebug()<<"ChatPictureLabel::resizeEvent"<<ev->size();
    if(ev->size().width() != m_pxp.width()){

    }
    setPicture(m_pxp);

    // QWidget::resizeEvent(ev);
}

void ChatPictureLabel::setPicture(QPixmap pxp)
{
    m_pxp = pxp;
    if(this->width() == 0){
        qDebug()<<"ChatPictureLabel::width = 0";
        return;
    }

    if(pxp.width() != this->width()){
        // qreal ratio = qApp->devicePixelRatio();
        qreal rate = static_cast<qreal>(this->width()/**ratio*/)/pxp.width();

        pxp = pxp.scaled(pxp.size() * rate,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    }

    this->setFixedSize(pxp.size());
    this->setPixmap(pxp);

    QWidget* parent = this->parentWidget();
    if(parent){
        parent->setFixedSize(this->size());
    }else{
        qDebug()<<"ChatPictureLabel::parent = nullptr";
    }
}

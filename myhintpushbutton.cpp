#include "myhintpushbutton.h"

#include <QResizeEvent>

MyHintPushButton::MyHintPushButton(QWidget *parent)
    : QPushButton{parent}
{
    this->setMinimumSize(39,39);
    this->setMaximumSize(70,70);
    // this->setStyleSheet("QPushButton{\n	background-color:rgb(255,255,255);\n}\nQPushButton:checked{\n	background-color:rgba(244,234,42,200);\n}");
}

void MyHintPushButton::resizeEvent(QResizeEvent *ev)
{
    Q_UNUSED(ev);
    this->resize(this->width(),this->width());
    this->setIconSize(this->size()*0.9);
    // qDebug()<<"size"<<size();
}

QSize MyHintPushButton::sizeHint() const
{
    return QSize(30,30);
}

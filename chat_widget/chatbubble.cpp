#include "chatbubble.h"

#include <QPainter>
#include <QVBoxLayout>

ChatBubble::ChatBubble(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout* vl=new QVBoxLayout(this);
    this->stack=new QStackedWidget(this);
    this->edit=new AutoHeightTextEdit(stack);
    this->label_pxp=new QLabel(stack);

    vl->addWidget(stack);
    stack->addWidget(edit);
    stack->addWidget(label_pxp);
    stack->setCurrentWidget(edit);

    vl->setContentsMargins(0,0,0,0);
    stack->setContentsMargins(0,0,0,0);
    stack->layout()->setSpacing(0);
    stack->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    edit->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    label_pxp->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);


    edit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    edit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    edit->setReadOnly(true);
}

// void ChatBubble::paintEvent(QPaintEvent *ev)
// {
//     Q_UNUSED(ev);
//     QPainter painter(this);
//     painter.fillRect(this->rect(),Qt::red);
// }

void ChatBubble::setText(const QString &text)
{
    edit->setText(text);
    stack->setCurrentWidget(edit);
}

void ChatBubble::setPximap(const QPixmap &pxp)
{
    this->label_pxp->setPixmap(pxp);
    stack->setCurrentWidget(label_pxp);
}

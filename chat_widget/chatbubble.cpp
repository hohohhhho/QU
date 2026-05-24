#include "chatbubble.h"

#include <QPainter>
#include <QPainterPath>
#include <QResizeEvent>
#include <QVBoxLayout>

ChatBubble::ChatBubble(QWidget *parent)
    : QWidget{parent}
{
    // this->setStyleSheet("QWidget{"//添加阴影增加立体感（丑）
    //                     "background-color:rgb(244,234,42);"
    //                     "border:1px solid rgb(255,255,255);"
    //                     "border-top-color: rgba(255,255,255,0.6);"
    //                     "border-left-color: rgba(255,255,255,0.6);"
    //                     "border-right-color: rgba(0,0,0,0.2);"
    //                     "border-bottom-color: rgba(0,0,0,0.2);"
    //                     "border-radius:10px;"
    //                     "}");

    QVBoxLayout* vl = new QVBoxLayout(this);
    this->stack = new QStackedWidget(this);
    this->edit = new AutoHeightTextEdit(stack);
    this->label_file = new ChatFileLabel(stack);

    vl->addWidget(stack);
    stack->addWidget(edit);
    stack->addWidget(label_file);
    stack->setCurrentWidget(edit);

    vl->setContentsMargins(0,0,0,0);
    stack->setContentsMargins(0,0,0,0);
    stack->layout()->setSpacing(0);

    this->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Fixed);
    stack->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    edit->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    label_file->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);


    edit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    edit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    edit->setReadOnly(true);
}

void ChatBubble::paintEvent(QPaintEvent *ev)
{
    Q_UNUSED(ev);
    QPainter painter(this);
    painter.setBrush(QColor(244,234,42));
    painter.setPen(Qt::NoPen);

    QPainterPath path;
    path.addRoundedRect(this->rect(),10,10);

    painter.drawPath(path);
}

void ChatBubble::resizeEvent(QResizeEvent *ev)
{
    // qDebug()<<"ChatBubble::resizeEvent"<<ev->size()<<"maximumWidth()"<<this->maximumWidth();
    this->stack->setMaximumWidth(ev->size().width());
    this->edit->setMaximumWidth(ev->size().width());
}

void ChatBubble::setText(const QString &text)
{
    this->m_type = Message::MessageType::Text;
    edit->setText(text);
    stack->setCurrentWidget(edit);
}

void ChatBubble::setPicture(const QString &filename, const QPixmap &pxp)
{
    this->m_type = Message::MessageType::Picture;
    this->label_file->setPicture(filename, pxp);
    stack->setCurrentWidget(label_file);
}

void ChatBubble::setVideo(const QString& filename, const QByteArray &data)
{
    this->m_type = Message::MessageType::Video;
    this->label_file->setVideo(filename, data);
    stack->setCurrentWidget(label_file);
}

void ChatBubble::setNormalFile(const QString& filename, const QByteArray &data)
{
    this->m_type = Message::MessageType::File;
    this->label_file->setNormalFile(filename, data);
    stack->setCurrentWidget(label_file);
}

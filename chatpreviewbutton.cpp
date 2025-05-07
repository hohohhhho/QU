#include "chatpreviewbutton.h"
#include "userpatcher.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QPainter>

extern QMutex mutex_chat;
extern QMap<int,QList<Message>> map_chat_history;
extern QMap<int,QList<Message>> map_chat_unread;

ChatPreviewButton::ChatPreviewButton(User user, QWidget *parent)
    : QWidget{parent},m_user(user)
{
    int pad=2;
    this->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Fixed);
    this->setFixedHeight(64+pad*2);
    // this->setStyleSheet("QWidget{"
    //                     "background-color:gray;"
    //                     "}");
    if(m_user.nickname.isEmpty()){
        UserPatcher* userPatcher=new UserPatcher;
        userPatcher->patchUser(m_user);
        userPatcher->cleanUp();
    }
    m_hl=new QHBoxLayout(this);
    m_hl->setContentsMargins(pad,pad,0,pad);
    m_hl->setSpacing(0);
    Profile* profile=new Profile(this);
    profile->setFixedSize(64,64);
    profile->setIcon(user.icon);
    // profile->setIconSize(profile->size()*0.9);

    m_vl1=new QVBoxLayout;
    label_nickname=new QLabel(user.nickname,this);
    label_nickname->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::MinimumExpanding);
    label_msg=new QLabel(this);
    label_nickname->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    m_vl1->addWidget(label_nickname);
    m_vl1->addWidget(label_msg);

    m_vl2=new QVBoxLayout;
    label_time=new QLabel(this);
    label_time->setAlignment(Qt::AlignCenter);
    label_time->setFixedWidth(35);
    label_num_msg=new QLabel(this);
    label_num_msg->setAlignment(Qt::AlignCenter);
    label_num_msg->setFixedWidth(35);

    m_vl2->addWidget(label_time);
    m_vl2->addWidget(label_num_msg);

    profile->setAttribute(Qt::WA_TransparentForMouseEvents);
    label_nickname->setAttribute(Qt::WA_TransparentForMouseEvents);
    label_msg->setAttribute(Qt::WA_TransparentForMouseEvents);
    label_time->setAttribute(Qt::WA_TransparentForMouseEvents);
    label_num_msg->setAttribute(Qt::WA_TransparentForMouseEvents);

    m_hl->addWidget(profile,2);
    m_hl->addLayout(m_vl1,3);
    m_hl->addLayout(m_vl2,1);

    updateState();
    // hl->addWidget(label_nickname);
}

void ChatPreviewButton::paintEvent(QPaintEvent *ev)
{
    Q_UNUSED(ev);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    // painter.fillRect(this->rect(),Qt::gray);
    painter.setPen(Qt::white);
    painter.setBrush(color_bk);
    painter.drawRect(this->rect());
}

void ChatPreviewButton::mousePressEvent(QMouseEvent *ev)
{
    Q_UNUSED(ev);
    if(m_user.nickname.isEmpty()){
        UserPatcher* userPatcher=new UserPatcher;
        userPatcher->patchUser(m_user);
        userPatcher->cleanUp();
    }

    if(!list_message_unread.isEmpty()){
        this->list_message.append(list_message_unread);
        list_message_unread.clear();
    }

    mutex_chat.lock();
    auto it=map_chat_unread.find(m_user.id);
    if(it!=map_chat_unread.end() && !it->isEmpty()){
        emit readMsgNum(it->size());
        map_chat_history[m_user.id].append(*it);
        it->clear();
        mutex_chat.unlock();
        updateState();
    }else{
        mutex_chat.unlock();
        // qDebug()<<"it迭代器无效或链表为空";
    }


    mutex_checked.lock();
    bool fchecked=this->checked;
    mutex_checked.unlock();
    if(fchecked){
        emit clicked(true);
    }else{
        emit clicked(false);
    }

}

void ChatPreviewButton::choose(bool choose)
{
    mutex_checked.lock();
    if(checked!=choose){
        this->checked=choose;
        mutex_checked.unlock();
        if(checked){
            color_bk=QColor(244,234,42,200);
        }else{
            color_bk=QColor(244,234,42,100);
        }
        update();
    }else{
        mutex_checked.unlock();
    }

}

void ChatPreviewButton::updateState()
{
    if(!unique_text.isEmpty()){
        label_msg->setText(unique_text);
        return;
    }
    mutex_chat.lock();

    auto it_map_chat_unread=map_chat_unread.find(m_user.id);
    auto it_map_chat_history=map_chat_history.find(m_user.id);
    Message::MessageType type;
    QString text;
    if(!list_message_unread.isEmpty()){
        type=list_message_unread.last().type;
        if(type == Message::MessageType::Text){
            text=list_message_unread.last().msg;
        }else if(type == Message::MessageType::Picture){
            text="[图片]";
        }else if(type == Message::MessageType::File){
            text="[文件]";
        }
    }else if(it_map_chat_unread!=map_chat_unread.end() && !it_map_chat_unread->isEmpty()){
        type=it_map_chat_unread->last().type;
        if(type == Message::MessageType::Text){
            text=it_map_chat_unread->last().msg;
        }else if(type == Message::MessageType::Picture){
            text="[图片]";
        }else if(type == Message::MessageType::File){
            text="[文件]";
        }
    }else if(!list_message.isEmpty()){
        type=list_message.last().type;
        if(type == Message::MessageType::Text){
            text=list_message.last().msg;
        }else if(type == Message::MessageType::Picture){
            text="[图片]";
        }else if(type == Message::MessageType::File){
            text="[文件]";
        }
    }else if(it_map_chat_history!=map_chat_history.end() && !it_map_chat_history->isEmpty()){
        type=it_map_chat_history->last().type;
        if(type == Message::MessageType::Text){
            text=it_map_chat_history->last().msg;
        }else if(type == Message::MessageType::Picture){
            text="[图片]";
        }else if(type == Message::MessageType::File){
            text="[文件]";
        }
    }
    label_msg->setText(text);

    if(!list_message_unread.isEmpty()){
        label_num_msg->setText(QString::number(qBound(1,list_message_unread.size(),999)));
    }else if(!map_chat_unread[m_user.id].isEmpty()){
        label_num_msg->setText(QString::number(qBound(1,map_chat_unread[m_user.id].size(),999)));
    }else{
        label_num_msg->setText("");
    }

    mutex_chat.unlock();

    update();
}

bool ChatPreviewButton::isChecked()
{
    this->mutex_checked.lock();
    bool fchecked=checked;
    mutex_checked.unlock();
    return fchecked;
}

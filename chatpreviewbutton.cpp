#include "chatpreviewbutton.h"
#include "userpatcher.h"
#include <QContextMenuEvent>
#include <QHBoxLayout>
#include <QLabel>
#include <QMenu>
#include <QPainter>

extern QMutex mutex_chat;
extern QMap<int,QList<Message>> map_userchat_history;
extern QMap<int,QList<Message>> map_userchat_unread;
extern QMap<int,QList<Message>> map_groupchat_history;
extern QMap<int,QList<Message>> map_groupchat_unread;

ChatPreviewButton::ChatPreviewButton(User user, QWidget *parent)
    : QWidget{parent},m_user(user)
{
    type = Type::user;
    init();
}

ChatPreviewButton::ChatPreviewButton(Group group, QWidget *parent)
: QWidget{parent},m_group(group)
{
    type = Type::group;
    init();
}

ChatPreviewButton::~ChatPreviewButton()
{
    if(m_menu){
        delete m_menu;
    }
}

void ChatPreviewButton::init()
{
    this->m_menu =nullptr;

    int pad=2;
    this->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Fixed);
    this->setFixedHeight(64+pad*2);

    m_hl=new QHBoxLayout(this);
    m_hl->setContentsMargins(pad,pad,0,pad);
    m_hl->setSpacing(0);
    Profile* profile=new Profile(this);
    profile->setFixedSize(64,64);    

    m_vl1=new QVBoxLayout;
    label_nickname=new QLabel(this);
    label_nickname->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::MinimumExpanding);
    label_msg=new QLabel(this);
    label_msg->setStyleSheet("QLabel{"
                             "font-size:18px;"
                             "}");
    label_nickname->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    m_vl1->addWidget(label_nickname);
    m_vl1->addWidget(label_msg);

    if(type == user){
        if(m_user.isEmpty()){
            UserPatcher* userPatcher=new UserPatcher;
            connect(userPatcher,&UserPatcher::userPatchFinished,this,[=](User user_patched){
                m_user = user_patched;
                profile->setIcon(m_user.icon);
                label_nickname->setText(m_user.nickname);

                userPatcher->cleanUp();
                userPatcher->deleteLater();
            });
            userPatcher->patchUser(m_user);

        }else{
            profile->setIcon(m_user.icon);
            label_nickname->setText(m_user.nickname);
        }
    }else  if(type == group){
        if(m_group.isEmpty()){
            UserPatcher* userPatcher=new UserPatcher;
            connect(userPatcher,&UserPatcher::groupPatchFinished,this,[=](Group group_patched){
                m_group = group_patched;
                profile->setIcon(m_group.icon);
                label_nickname->setText(m_group.name);

                userPatcher->cleanUp();
                userPatcher->deleteLater();
            });
            userPatcher->patchGroup(m_group);
        }else{
            profile->setIcon(m_group.icon);
            label_nickname->setText(m_group.name);
        }
    }

    m_vl2=new QVBoxLayout;
    label_time=new QLabel(this);
    label_time->setAlignment(Qt::AlignCenter);
    label_time->setFixedWidth(35);
    label_num_msg=new QLabel(this);
    label_num_msg->setAlignment(Qt::AlignCenter);
    label_num_msg->setFixedWidth(35);
    label_num_msg->setStyleSheet("QLabel{"
                                 "font-size:18px;"
                                 "color:white;"
                                 "}");

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
}


void ChatPreviewButton::paintEvent(QPaintEvent *ev)
{
    Q_UNUSED(ev);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::white);
    painter.setBrush(color_bk);
    painter.drawRect(this->rect());
}

void ChatPreviewButton::mousePressEvent(QMouseEvent *ev)
{
    Q_UNUSED(ev);
    qDebug()<<"ChatPreviewButton::mousePressEvent";

    if(!list_message_unread.isEmpty()){
        this->list_message.append(list_message_unread);
        list_message_unread.clear();
    }

    if(type == user){
        mutex_chat.lock();
        auto it=map_userchat_unread.find(m_user.id);
        if(it!=map_userchat_unread.end() && !it->isEmpty()){
            emit readMsgNum(it->size());
            map_userchat_history[m_user.id].append(*it);
            it->clear();
            mutex_chat.unlock();
            updateState();
        }else{
            mutex_chat.unlock();
            // qDebug()<<"it迭代器无效或链表为空";
        }
    }else if(type == group){
        mutex_chat.lock();
        auto it=map_groupchat_unread.find(m_group.id);
        if(it!=map_groupchat_unread.end() && !it->isEmpty()){
            emit readMsgNum(it->size());
            map_groupchat_history[m_group.id].append(*it);
            it->clear();
            mutex_chat.unlock();
            updateState();
        }else{
            mutex_chat.unlock();
        }
    }else{
        qDebug()<<"控件类型错误";
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

void ChatPreviewButton::contextMenuEvent(QContextMenuEvent *ev)
{
    if(m_menu){
        m_menu->exec(ev->globalPos());
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

    QList<Message> it_map_chat_unread;
    QList<Message> it_map_chat_history;
    if(type == user){
        it_map_chat_unread = map_userchat_unread.value(m_user.id);
        it_map_chat_history = map_userchat_history.value(m_user.id);
    }else if(type ==group){
        it_map_chat_unread = map_groupchat_unread.value(m_group.id);
        it_map_chat_history = map_groupchat_history.value(m_group.id);
    }
    QString text;
    auto getText = [=](Message msg)->QString{
        Message::MessageType msg_type = msg.type;
        if(msg_type == Message::MessageType::Text){
            return msg.msg;
        }else if(msg_type == Message::MessageType::Picture){
            return "[图片]";
        }else if(msg_type == Message::MessageType::File){
            return "[文件]";
        }
        return "void";
    };
    if(!list_message_unread.isEmpty()){
        text = getText(list_message_unread.last());
    }else if(!it_map_chat_unread.isEmpty()){
        text = getText(it_map_chat_unread.last());
    }else if(!list_message.isEmpty()){
        text = getText(list_message.last());
    }else if(!it_map_chat_history.isEmpty()){
        text = getText(it_map_chat_history.last());
    }else{
        text="";
    }
    label_msg->setText(text);
    // QString text;
    // Message::MessageType msg_type
    // if(!list_message_unread.isEmpty()){
    //     msg_type = list_message_unread.last().type;
    //     if(msg_type == Message::MessageType::Text){
    //         text = list_message_unread.last().msg;
    //     }else if(msg_type == Message::MessageType::Picture){
    //         text = "[图片]";
    //     }else if(msg_type == Message::MessageType::File){
    //         text = "[文件]";
    //     }
    // }else if(it_map_chat_unread!=map_userchat_unread.end() && !it_map_chat_unread->isEmpty()){
    //     msg_type=it_map_chat_unread->last().type;
    //     if(msg_type == Message::MessageType::Text){
    //         text=it_map_chat_unread->last().msg;
    //     }else if(msg_type == Message::MessageType::Picture){
    //         text="[图片]";
    //     }else if(msg_type == Message::MessageType::File){
    //         text="[文件]";
    //     }
    // }else if(!list_message.isEmpty()){
    //     msg_type=list_message.last().type;
    //     if(msg_type == Message::MessageType::Text){
    //         text=list_message.last().msg;
    //     }else if(msg_type == Message::MessageType::Picture){
    //         text="[图片]";
    //     }else if(msg_type == Message::MessageType::File){
    //         text="[文件]";
    //     }
    // }else if(it_map_chat_history!=map_userchat_history.end() && !it_map_chat_history->isEmpty()){
    //     msg_type=it_map_chat_history->last().type;
    //     if(msg_type == Message::MessageType::Text){
    //         text=it_map_chat_history->last().msg;
    //     }else if(msg_type == Message::MessageType::Picture){
    //         text="[图片]";
    //     }else if(msg_type == Message::MessageType::File){
    //         text="[文件]";
    //     }
    // }else{
    //     qDebug()<<"";
    // }
    // label_msg->setText(text);

    if(!list_message_unread.isEmpty()){
        label_num_msg->setText(QString::number(qBound(1,list_message_unread.size(),999)));
    }else if(this->type == user && !map_userchat_unread[m_user.id].isEmpty()){
        {
            label_num_msg->setText(QString::number(qBound(1,map_userchat_unread[m_user.id].size(),999)));
        }
    }else if(this->type == group && !map_groupchat_unread[m_group.id].isEmpty()){
        {
            label_num_msg->setText(QString::number(qBound(1,map_groupchat_unread[m_group.id].size(),999)));
        }
    }else{
        label_num_msg->setText("");
    }

    mutex_chat.unlock();

    update();
}

void ChatPreviewButton::setMenuContext(QMenu *menu)
{
    m_menu = menu;
    // m_menu->setParent(this);
    m_menu->setWindowFlag(Qt::Popup);
    m_menu->setVisible(false);
}

bool ChatPreviewButton::isChecked()
{
    this->mutex_checked.lock();
    bool fchecked=checked;
    mutex_checked.unlock();
    return fchecked;
}

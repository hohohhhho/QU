#include "chatview.h"
#include "profile.h"
#include "chatbubble.h"
#include "userpatcher.h"

#include <QPainter>
#include <QTextEdit>
#include <QLabel>

ChatView::ChatView(QWidget *parent)
    : QWidget{parent}
{
    this->vlayout=new QVBoxLayout(this);
    vlayout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Ignored,QSizePolicy::Expanding));
    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
}

void ChatView::paintEvent(QPaintEvent *ev)
{
    Q_UNUSED(ev);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(this->rect(),QColor(244,234,42,50));
}

void ChatView::init(User user_receiver, User user_sender)
{
    this->m_user = user_receiver;
    this->o_user = user_sender;
    if(m_user.isEmpty()){
        UserPatcher* userPatcher=new UserPatcher;
        userPatcher->patchUser(m_user);
        userPatcher->cleanUp();
    }
    if(o_user.isEmpty()){
        UserPatcher* userPatcher=new UserPatcher;
        userPatcher->patchUser(o_user);
        userPatcher->cleanUp();
    }
}

void ChatView::init(User my_user, Group group)
{
    this->m_user = my_user;
    this->m_group = group;
    if(m_user.isEmpty()){
        UserPatcher* userPatcher=new UserPatcher;
        userPatcher->patchUser(m_user);
        userPatcher->cleanUp();
    }
    if(m_group.isEmpty()){
        UserPatcher* userPatcher=new UserPatcher;
        userPatcher->patchGroup(m_group);
        userPatcher->cleanUp();
    }

}

void ChatView::addMsg(Message message, bool my)
{
    QWidget* contain=new QWidget(this);
    QHBoxLayout* hl=new QHBoxLayout(contain);
    QVBoxLayout* vl=new QVBoxLayout;
    Profile* profile=new Profile(contain);
    // QTextEdit* edit=new QTextEdit(contain);
    ChatBubble* bubble=new ChatBubble(contain);

    profile->setFixedSize(48,48);
    contain->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    // contain->setMinimumHeight(64);
    // contain->setMaximumHeight(128);
    bubble->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    connect(bubble->edit,&AutoHeightTextEdit::updateSize,this,[=](){
        int new_height=qMax(profile->height(),bubble->edit->height());
        bubble->setFixedHeight(new_height);
        contain->setFixedHeight(new_height);
    });

    QIcon icon=my?m_user.icon:o_user.icon;
    profile->setIcon(icon);

    if(message.type==Message::MessageType::Text){
        bubble->setText(message.msg);
    }else if(message.type==Message::MessageType::Picture){
        QPixmap pxp;
        pxp.loadFromData(message.msg);
        bubble->setPximap(pxp);
    }else if(message.type==Message::MessageType::File){
        qDebug()<<"文件";
    }else{
        qDebug()<<"格式错误";
    }

    hl->setContentsMargins(0,0,0,0);
    // hl->setSpacing(0);
    if(my){
        hl->addWidget(bubble,6);
        hl->addLayout(vl,1);
    }else{
        hl->addLayout(vl,1);
        hl->addWidget(bubble,6);
    }

    vl->addWidget(profile);
    vl->addItem(new QSpacerItem(0,0,QSizePolicy::Ignored,QSizePolicy::Expanding));
    this->vlayout->insertWidget(vlayout->count()-1,contain);
}

void ChatView::addMsg(Message message, User sender)
{
    QWidget* contain=new QWidget(this);
    QHBoxLayout* hl=new QHBoxLayout(contain);
    QVBoxLayout* vl=new QVBoxLayout;
    Profile* profile=new Profile(contain);
    // QTextEdit* edit=new QTextEdit(contain);
    ChatBubble* bubble=new ChatBubble(contain);

    profile->setFixedSize(48,48);
    contain->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    // contain->setMinimumHeight(64);
    // contain->setMaximumHeight(128);
    bubble->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    connect(bubble->edit,&AutoHeightTextEdit::updateSize,this,[=](){
        int new_height=qMax(profile->height(),bubble->edit->height());
        bubble->setFixedHeight(new_height);
        contain->setFixedHeight(new_height);
    });

    QIcon icon = sender.icon;
    profile->setIcon(icon);

    if(message.type==Message::MessageType::Text){
        bubble->setText(message.msg);
    }else if(message.type==Message::MessageType::Picture){
        QPixmap pxp;
        pxp.loadFromData(message.msg);
        bubble->setPximap(pxp);
    }else if(message.type==Message::MessageType::File){
        qDebug()<<"文件";
    }else{
        qDebug()<<"格式错误";
    }

    hl->setContentsMargins(0,0,0,0);
    if(sender == m_user){
        hl->addWidget(bubble,6);
        hl->addLayout(vl,1);
    }else{
        hl->addLayout(vl,1);
        hl->addWidget(bubble,6);
    }

    vl->addWidget(profile);
    vl->addItem(new QSpacerItem(0,0,QSizePolicy::Ignored,QSizePolicy::Expanding));
    this->vlayout->insertWidget(vlayout->count()-1,contain);
}

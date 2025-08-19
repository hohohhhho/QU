#include "chatview.h"
#include "profile.h"
#include "chatbubble.h"
#include "userpatcher.h"

#include <QPainter>
#include <QTextEdit>
#include <QLabel>
#include <QResizeEvent>

#define PROFILESIZE 48

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

void ChatView::resizeEvent(QResizeEvent *ev)
{
    for(QWidget*& container : list_container){
        container->setMaximumWidth(ev->size().width());
    }

    // QWidget::resizeEvent(ev);
}

void ChatView::init(User user_receiver, User user_sender)
{
    this->m_user = user_receiver;
    this->o_user = user_sender;
    if(m_user.isEmpty()){
        UserPatcher* userPatcher=new UserPatcher;
        connect(userPatcher,&UserPatcher::userPatchFinished,this,[=](User user_patcherd){
            m_user = user_patcherd;

            userPatcher->cleanUp();
            userPatcher->deleteLater();
        });
        userPatcher->patchUser(m_user);
    }
    if(o_user.isEmpty()){
        UserPatcher* userPatcher=new UserPatcher;
        connect(userPatcher,&UserPatcher::userPatchFinished,this,[=](User user_patcherd){
            o_user = user_patcherd;

            userPatcher->cleanUp();
            userPatcher->deleteLater();
        });
        userPatcher->patchUser(o_user);
    }
}

void ChatView::init(User my_user, Group group)
{
    this->m_user = my_user;
    this->m_group = group;
    if(m_user.isEmpty()){
        UserPatcher* userPatcher=new UserPatcher;
        connect(userPatcher,&UserPatcher::userPatchFinished,this,[=](User user_patcherd){
            m_user = user_patcherd;

            userPatcher->cleanUp();
            userPatcher->deleteLater();
        });
        userPatcher->patchUser(m_user);
    }
    if(m_group.isEmpty()){
        UserPatcher* userPatcher=new UserPatcher;
        connect(userPatcher,&UserPatcher::groupPatchFinished,this,[=](Group group_patched){
            m_group = group_patched;

            userPatcher->cleanUp();
            userPatcher->deleteLater();
        });
        userPatcher->patchGroup(m_group);
    }

}

void ChatView::addMsg(Message message, bool my)
{
    QWidget* container=new QWidget(this);//气泡一整行的容器（包含头像）
    QHBoxLayout* hl=new QHBoxLayout(container);
    QVBoxLayout* vl=new QVBoxLayout;
    Profile* profile=new Profile(container);
    ChatBubble* bubble=new ChatBubble(container);

    profile->setFixedSize(PROFILESIZE,PROFILESIZE);
    container->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    connect(bubble->edit,&AutoHeightTextEdit::updateSize,this,[=](){
        int new_height=qMax(profile->height(),bubble->edit->height());
        bubble->setFixedHeight(new_height);
        container->setFixedHeight(new_height);
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
    if(my){
        hl->addWidget(bubble,6);
        hl->addLayout(vl,1);
    }else{
        hl->addLayout(vl,1);
        hl->addWidget(bubble,6);
    }

    vl->addWidget(profile);
    vl->addItem(new QSpacerItem(0,0,QSizePolicy::Ignored,QSizePolicy::Expanding));//给头像控件下方添加弹簧填满多余空间
    this->vlayout->insertWidget(vlayout->count()-1,container);

    list_container.append(container);//加入列表方便管理
}

void ChatView::addMsg(Message message, User sender)
{
    QWidget* container=new QWidget(this);
    QHBoxLayout* hl=new QHBoxLayout(container);
    QVBoxLayout* vl=new QVBoxLayout;
    Profile* profile=new Profile(container);
    ChatBubble* bubble=new ChatBubble(container);

    profile->setFixedSize(PROFILESIZE,PROFILESIZE);
    container->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    connect(bubble->edit,&AutoHeightTextEdit::updateSize,this,[=](){
        int new_height=qMax(profile->height(),bubble->edit->height());
        bubble->setFixedHeight(new_height);
        container->setFixedHeight(new_height);
    });

    if(sender.isEmpty()){
        UserPatcher* userPatcher=new UserPatcher;
        connect(userPatcher,&UserPatcher::userPatchFinished,this,[=](User user_patcherd)mutable{
            sender = user_patcherd;
            QIcon icon = sender.icon;
            profile->setIcon(icon);

            userPatcher->cleanUp();
            userPatcher->deleteLater();
        });
        userPatcher->patchUser(m_user);
    }else{
        QIcon icon = sender.icon;
        profile->setIcon(icon);
    }

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
    this->vlayout->insertWidget(vlayout->count()-1,container);

    list_container.append(container);
}

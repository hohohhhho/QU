#include "chatview.h"
#include "profile.h"
#include "chatbubble.h"
#include "userpatcherfactory.h"
#include "userdetail.h"

#include <QPainter>
#include <QTextEdit>
#include <QLabel>
#include <QResizeEvent>

#define PROFILESIZE 48
#define PADDING 10

ChatView::ChatView(QWidget *parent)
    : QWidget{parent}
{
    this->m_vlayout=new QVBoxLayout(this);
    //弹簧，把消息控件压到最上面显示
    m_vlayout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Ignored,QSizePolicy::Expanding));
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
    adjustSize(ev->size());
}

void ChatView::init(User user_receiver, User user_sender)
{
    this->m_user = user_receiver;
    this->o_user = user_sender;
    if(m_user.isEmpty()){
        user_patcher_factory->patchUser(this, m_user,true,[=](User user_patched)mutable{
            m_user = user_patched;
        });
    }
    if(o_user.isEmpty()){
        user_patcher_factory->patchUser(this, o_user,true,[=](User user_patched)mutable{
            o_user = user_patched;
        });
    }
}

void ChatView::init(User my_user, Group group)
{
    this->m_user = my_user;
    this->m_group = group;
    if(m_user.isEmpty()){
        user_patcher_factory->patchUser(this, m_user,false,[=](User user_patched)mutable{
            m_user = user_patched;
        });
    }
    if(m_group.isEmpty()){
        user_patcher_factory->patchGroup(this, m_group,false,[=](Group group_patched)mutable{
            m_group = group_patched;
        });
    }

}

// void ChatView::addMsg(Message message, bool my)
// {
//     QWidget* container=new QWidget(this);//气泡一整行的容器（包含头像）
//     QHBoxLayout* hl=new QHBoxLayout(container);
//     QVBoxLayout* vl=new QVBoxLayout;
//     Profile* profile=new Profile(container);
//     ChatBubble* bubble=new ChatBubble(container);

//     profile->setFixedSize(PROFILESIZE,PROFILESIZE);
//     container->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Fixed);
//     container->setMaximumWidth(this->width());
//     connect(bubble->edit,&AutoHeightTextEdit::updateSize,this,[=](){
//         int new_height=qMax(profile->height(),bubble->edit->height());
//         bubble->setFixedHeight(new_height);
//         container->setFixedHeight(new_height);
//     });
//     connect(profile,&QPushButton::clicked,this,[=](){
//         UserDetail* detail=new UserDetail(my?m_user:o_user,nullptr,true,my);
//         detail->setPopWidget();
//         detail->move(container->mapToGlobal(profile->pos()+QPoint(profile->width()/2,profile->height()/2)));
//         detail->show();
//     });

//     User& user_msg = my ? m_user : o_user;
//     if(user_msg.isEmpty()){
//         user_patcher_factory->patchUser(this, user_msg, false, [&user_msg,profile](User user_patched)mutable{
//             user_msg = user_patched;
//             profile->setIcon(user_msg.icon);
//         });
//     }else{
//         profile->setIcon(user_msg.icon);
//     }

//     if(message.type == Message::MessageType::Text){
//         bubble->setText(message.msg);
//     }else if(message.type == Message::MessageType::Picture){
//         QPixmap pxp;
//         pxp.loadFromData(message.msg);
//         bubble->setPicture(message.filename, pxp);
//     }else if(message.type == Message::MessageType::Video){
//         bubble->setVideo(message.filename, message.msg);
//     }else if(message.type == Message::MessageType::File){
//         bubble->setNormalFile(message.filename, message.msg);
//     }else{
//         qDebug()<<"格式错误";
//     }

//     hl->setContentsMargins(0,0,0,0);
//     if(my){
//         hl->addWidget(bubble,6);
//         hl->addLayout(vl,1);
//     }else{
//         hl->addLayout(vl,1);
//         hl->addWidget(bubble,6);
//     }

//     vl->addWidget(profile);
//     vl->addItem(new QSpacerItem(0,0,QSizePolicy::Ignored,QSizePolicy::Expanding));//给头像控件下方添加弹簧填满多余空间
//     this->vlayout->insertWidget(vlayout->count()-1,container);

//     list_container.append(container);//加入列表方便管理
// }

void ChatView::addMsg(Message message, User sender)
{
    QWidget* container=new QWidget(this);
    QHBoxLayout* hl=new QHBoxLayout(container);
    QVBoxLayout* vl=new QVBoxLayout;
    Profile* profile=new Profile(container);
    ChatBubble* bubble=new ChatBubble(container);

    profile->setFixedSize(PROFILESIZE,PROFILESIZE);
    container->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Fixed);
    container->setMaximumWidth(this->width());
    bubble->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Fixed);
    container->setMaximumWidth(this->width() - PADDING - PROFILESIZE);

    connect(bubble->edit,&AutoHeightTextEdit::updateSize,this,[=](){
        int new_height=qMax(profile->height(),bubble->edit->height());
        bubble->setFixedHeight(new_height);
        container->setFixedHeight(new_height);
    });
    connect(profile,&QPushButton::clicked,this,[=](){
        UserDetail* detail=new UserDetail(sender, nullptr, true, sender==m_user);
        detail->setPopWidget();
        detail->move(container->mapToGlobal(profile->pos()+QPoint(profile->width()/2,profile->height()/2)));
        detail->show();
    });

    if(sender.icon.isNull()){
        user_patcher_factory->patchUser(this, sender,false,[=](User user_patched)mutable{
            QIcon icon = user_patched.icon;
            profile->setIcon(icon);
            profile->update();
        });
    }else{
        QIcon icon = sender.icon;
        profile->setIcon(icon);
    }

    if(message.type==Message::MessageType::Text){
        bubble->setText(message.msg);
    }else if(message.type==Message::MessageType::Picture){
        QPixmap pxp;
        pxp.loadFromData(message.msg);
        bubble->setPicture(message.filename, pxp);
    }else if(message.type==Message::MessageType::Video){
        bubble->setVideo(message.filename, message.msg);
    }else if(message.type==Message::MessageType::File){
        bubble->setNormalFile(message.filename, message.msg);
    }else{
        qDebug()<<"格式错误";
    }

    hl->setContentsMargins(0,0,0,0);
    hl->setSpacing(PADDING);
    if(sender == m_user){
        hl->addWidget(bubble,6);
        hl->addLayout(vl,1);
    }else{
        hl->addLayout(vl,1);
        hl->addWidget(bubble,6);
    }

    vl->addWidget(profile);
    vl->addItem(new QSpacerItem(0,0,QSizePolicy::Ignored,QSizePolicy::Expanding));
    this->m_vlayout->insertWidget(m_vlayout->count()-1,container);

    list_bubble.append(bubble);
    list_container.append(container);
    adjustSize(size());//给新添加子控件调整大小
}

void ChatView::adjustSize(QSize size)
{
    // qDebug()<<"ChatView:resizeEvent size"<<size;
    for(QWidget*& container : list_container){
        container->setMaximumWidth(size.width());
    }
    for(ChatBubble*& bubble : list_bubble){
        int width = size.width() - PROFILESIZE - PADDING;
        // qDebug()<<"ChatView::resizeEvent:width"<<width;
        bubble->setMaximumWidth(width);
    }
}

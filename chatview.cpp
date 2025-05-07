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
    // painter.setPen(Qt::white);
    // painter.setBrush(Qt::gray);
    // painter.drawRect(this->rect());
}

void ChatView::init(User user_receiver, User user_sender)
{
    if(user_receiver.nickname.isEmpty() || user_receiver.icon.isNull()){
        UserPatcher* userPatcher=new UserPatcher;
        userPatcher->patchUser(user_receiver);
        userPatcher->cleanUp();
    }
    if(user_sender.nickname.isEmpty() || user_sender.icon.isNull()){
        UserPatcher* userPatcher=new UserPatcher;
        userPatcher->patchUser(user_sender);
        userPatcher->cleanUp();
    }
    this->m_user=user_receiver;
    this->o_user=user_sender;
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
    }else if(message.type==Message::MessageType::Picture){
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

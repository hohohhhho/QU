#include "chatwidget.h"
#include "ui_chatwidget.h"
#include "userpatcher.h"

#include <QBuffer>
#include <QFileDialog>
#include <QMessageBox>
#include <QMutex>
#include <QPainter>
#include <QScrollBar>

extern QMutex mutex_chat;
extern QMap<int,QList<Message>> map_userchat_history;
extern QMap<int,QList<Message>> map_userchat_unread;
extern QMap<int,QList<Message>> map_groupchat_history;
extern QMap<int,QList<Message>> map_groupchat_unread;

ChatWidget::ChatWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChatWidget)
{
    ui->setupUi(this);
    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    this->animation=new QVariantAnimation(this);
    this->w_emo=new EmotionWidget(this);

    animation->setStartValue(0);
    animation->setEndValue(180);
    animation->setDuration(200);
    animation->setEasingCurve(QEasingCurve::OutQuad);

    w_emo->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint);


    connect(w_emo,&EmotionWidget::addEmoji,this,[=](const QByteArray& emo){
        // QTextDocument* document=new QTextDocument(ui->edit_send->document()->toPlainText()+emo,ui->edit_send);
        // ui->edit_send->setDocument(document);
        QTextCursor cursor(ui->edit_send->document());
        cursor.movePosition(QTextCursor::End);
        cursor.insertText(emo);
    });
    connect(ui->btn_send,&QPushButton::clicked,this,[=](){
        QString text=ui->edit_send->toPlainText();
        if(!text.isEmpty()){
            ui->edit_send->clear();
            if(type == user){
                addMsg(text.toUtf8(),true);
            }else if(type == group){
                addMsg(text.toUtf8(),m_user);
            }

            QScrollBar* bar=ui->scrollArea_history->verticalScrollBar();
            bar->setValue(bar->maximum());
            emit sendMsg(text);
        }
    });
    connect(ui->btn_delete,&QPushButton::clicked,this,[=](){
        emit toDelete();
    });
    connect(ui->btn_emo,&QPushButton::clicked,this,[=](){
        w_emo->show();
        QPoint pos( (ui->btn_emo->width()-w_emo->width())/2 , -w_emo->height());
        w_emo->move(ui->btn_emo->mapToGlobal(pos));
    });
    connect(ui->btn_picture,&QPushButton::clicked,this,[=](){
        QString filter="图片(*.png *.jpg)";
        QStringList list=QFileDialog::getOpenFileNames(this,"打开图片","",filter);
        for(QString& filename:list){
            QPixmap pxp(filename);
            QByteArray data;
            QBuffer buffer(&data);
            buffer.open(QIODevice::WriteOnly);
            if(pxp.save(&buffer,"PNG")){
                if(data.size()>4*1024*1024){
                    QMessageBox::warning(this,"警告","文件不能超过4MB");
                    return;
                }
                emit sendFile(data);
                qDebug()<<"ChatWidget:data"<<data;
                if(type == user){
                    addMsg(data,true);
                }else if(type == group){
                    addMsg(data,m_user);
                }
            }else{
                qDebug()<<"写入缓冲区失败";
            }

        }
    });
    connect(ui->btn_call,&QPushButton::clicked,this,[=](){
        if(type == user){
            emit call(o_user.id);
        }
    });
    connect(ui->btn_refresh,&QPushButton::clicked,this,[=](){
        if(animation->state() != QVariantAnimation::Running){
            emit refresh();
            animation->start();
        }
    });
    connect(animation,&QVariantAnimation::valueChanged,this,[=](const QVariant& value){
        // QPixmap pxp = QPixmap(":/res/refresh.png");
        // QTransform transform;
        // QPoint center = QPoint(pxp.width()/2 , pxp.height()/2);
        // transform = transform.translate(center.x() , center.y());
        // transform= transform.rotate(value.toInt());
        // transform = transform.translate(-center.x() , -center.y());
        // pxp = pxp.transformed(transform);
        // ui->btn_refresh->setIcon(QIcon(pxp));
        QPixmap origin = QPixmap(":/res/refresh.png");
        QPixmap canvas(origin.size());
        QTransform transform = QTransform().rotate(value.toInt());
        QPixmap pxp = origin.transformed(transform);
        canvas.fill(Qt::transparent);
        QPainter painter(&canvas);
        painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
        QPoint dp( origin.width()-pxp.width(),origin.height()-pxp.height() );
        painter.drawPixmap(dp.x()/2 , dp.y()/2 , pxp/*.scaled(canvas.size(),Qt::KeepAspectRatio,Qt::SmoothTransformation)*/);
        ui->btn_refresh->setIcon(QIcon(canvas));
    });
}

ChatWidget::~ChatWidget()
{
    delete ui;
}

void ChatWidget::init(User my_user, User other_user, QList<Message> list_msg)
{
    type = Type::user;
    this->m_user = my_user;
    this->o_user = other_user;
    if(m_user.isEmpty()){
        UserPatcher* userPatcher=new UserPatcher;
        userPatcher->patchUser(m_user);
        userPatcher->cleanUp();
        userPatcher->deleteLater();
    }
    if(o_user.isEmpty()){
        UserPatcher* userPatcher=new UserPatcher;
        userPatcher->patchUser(o_user);
        userPatcher->cleanUp();
        userPatcher->deleteLater();
    }

    ui->chat_view->init(m_user,o_user);
    ui->label_nickname->setText(o_user.nickname);

    for(auto& msg:list_msg){
        if(msg.sender.id==m_user.id && msg.receiver_user.id==o_user.id){
            addMsg(msg.msg,true,false,false);
        }else if(msg.sender.id==o_user.id && msg.receiver_user.id==m_user.id){
            addMsg(msg.msg,false,false,false);
        }else{
            qDebug()<<"私聊消息：消息对象错误";
        }
    }
}

void ChatWidget::init(User my_user, Group group, QList<Message> list_msg)
{
    type = Type::group;
    this->m_user = my_user;
    this->m_group = group;
    if(m_user.isEmpty()){
        UserPatcher* userPatcher=new UserPatcher;
        userPatcher->patchUser(m_user);
        userPatcher->cleanUp();
        userPatcher->deleteLater();
    }
    if(m_group.isEmpty()){
        UserPatcher* userPatcher=new UserPatcher;
        userPatcher->patchGroup(m_group);
        userPatcher->cleanUp();
        userPatcher->deleteLater();
    }


    ui->chat_view->init(m_user,m_group);
    ui->label_nickname->setText(m_group.name);
    ui->btn_call->setVisible(false);

    for(auto& msg:list_msg){
        if(msg.sender == m_user && msg.receiver_group == m_group){
            addMsg(msg.msg,msg.sender,false,false);
        }else if(!(msg.sender == m_user) && msg.receiver_group == m_group){
            addMsg(msg.msg,msg.sender,false,false);
        }else{
            qDebug()<<"群聊消息：消息对象错误";
        }
    }
}

void ChatWidget::addMsg(const QByteArray& msg, bool my ,bool unread,bool save)
{
    if(type != user){
        return;
    }
    Message message;
    message.type=Message::getType(msg);
    message.sender=my?m_user:o_user;
    message.receiver_user=my?o_user:m_user;
    message.msg=msg;

    ui->chat_view->addMsg(message,my);

    if(save){
        if(unread){
            mutex_chat.lock();
            map_userchat_unread[o_user.id].append(message);
            mutex_chat.unlock();
        }else{
            mutex_chat.lock();
            map_userchat_history[o_user.id].append(message);
            mutex_chat.unlock();
        }
    }

    emit updatePreviewState();
}

void ChatWidget::addMsg(const QByteArray &msg, User sender, bool unread, bool save)
{
    if(type != group){
        return;
    }
    if(sender.isEmpty()){
        UserPatcher* userPatcher=new UserPatcher;
        userPatcher->patchUser(sender);
        userPatcher->cleanUp();
        userPatcher->deleteLater();
    }
    Message message;
    message.type = Message::getType(msg);
    message.sender = sender;
    message.receiver_group = m_group;
    message.msg = msg;

    ui->chat_view->addMsg(message,sender);

    if(save){
        if(unread){
            mutex_chat.lock();
            map_groupchat_unread[m_group.id].append(message);
            mutex_chat.unlock();
        }else{
            mutex_chat.lock();
            map_groupchat_history[m_group.id].append(message);
            mutex_chat.unlock();
        }
    }

    emit updatePreviewState();
}

#include "chatwidget.h"
#include "ui_chatwidget.h"
#include "userpatcher.h"

#include <QBuffer>
#include <QFileDialog>
#include <QMessageBox>
#include <QMutex>
#include <QScrollBar>

extern QMutex mutex_chat;
extern QMap<int,QList<Message>> map_chat_history;
extern QMap<int,QList<Message>> map_chat_unread;

ChatWidget::ChatWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChatWidget)
{
    ui->setupUi(this);
    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    w_emo=new EmotionWidget(this);
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
            addMsg(text.toUtf8(),true);
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
                addMsg(data,true);
            }else{
                qDebug()<<"写入缓冲区失败";
            }

        }
    });
}

ChatWidget::~ChatWidget()
{
    delete ui;
}

void ChatWidget::init(User m_user, User o_user, QList<Message> list_msg)
{
    if(m_user.nickname.isEmpty()){
        UserPatcher* userPatcher=new UserPatcher;
        userPatcher->patchUser(m_user);
        userPatcher->cleanUp();
    }
    if(o_user.nickname.isEmpty()){
        UserPatcher* userPatcher=new UserPatcher;
        userPatcher->patchUser(o_user);
        userPatcher->cleanUp();
    }
    this->m_user=m_user;
    this->o_user=o_user;

    ui->chat_view->init(m_user,o_user);
    ui->label_nickname->setText(o_user.nickname);

    for(auto& msg:list_msg){
        if(msg.sender.id==m_user.id && msg.receiver.id==o_user.id){
            addMsg(msg.msg,true,false,false);
        }else if(msg.sender.id==o_user.id && msg.receiver.id==m_user.id){
            addMsg(msg.msg,false,false,false);
        }else{
            qDebug()<<"消息对象错误";
        }
    }
}

void ChatWidget::addMsg(const QByteArray& msg, bool my ,bool unread,bool save)
{
    Message message;
    message.type=Message::getType(msg);
    message.sender=my?m_user:o_user;
    message.receiver=my?o_user:m_user;
    message.msg=msg;

    ui->chat_view->addMsg(message,my);

    // if(unread){
    //     mutex_chat.lock();
    //     auto it=map_chat_unread.find(o_user.id);
    //     if(it!=map_chat_unread.end()){
    //         it->append(message);
    //     }else{
    //         qDebug()<<"map_chat_unread";
    //     }
    //     mutex_chat.unlock();
    // }else{
    //     mutex_chat.lock();
    //     auto it=map_chat_history.find(o_user.id);
    //     if(it!=map_chat_history.end()){
    //         it->append(message);
    //     }else{
    //         qDebug()<<"map_chat_history未找到正确值:o_user.id"<<o_user.id;
    //         qDebug()<<map_chat_history.keys();
    //     }
    //     mutex_chat.unlock();
    // }
    if(save){
        if(unread){
            mutex_chat.lock();
            map_chat_unread[o_user.id].append(message);
            mutex_chat.unlock();
        }else{
            mutex_chat.lock();
            map_chat_history[o_user.id].append(message);
            mutex_chat.unlock();
        }
    }

    emit updatePreviewState();
}

#include "userpatcher.h"

#include <QApplication>
#include <QEventLoop>
#include <QIcon>
#include <QPixmap>
#include <QTcpSocket>
#include <QThread>

UserPatcher::UserPatcher(QObject *parent)
    : QObject{parent}
{
    this->m_thread=new QThread(this);
    this->moveToThread(m_thread);
    m_thread->start();
}

UserPatcher::~UserPatcher()
{
    if (QThread::currentThread() != m_thread) {
        QMetaObject::invokeMethod(this, "cleanUp", Qt::BlockingQueuedConnection);
    } else {
        cleanUp();
    }
}

bool UserPatcher::patchUser(User &user){
    mutex_patch_loop.lock();

    QTcpSocket* socket=new QTcpSocket;
    QEventLoop* loop=new QEventLoop;
    QByteArray buffer;
    auto processData = [=,&user](const QByteArray& profile,const QByteArray& data){
        // qDebug()<<"profile"<<profile<<"data"<<data;
        QPixmap pxp;
        pxp.loadFromData(profile);
        user.icon=QIcon(pxp);
        QStringList qstr_list=QString(data).split('/');
        if(qstr_list.size()<2){
            qDebug()<<"macro qstr_list"<<qstr_list;
        }else if(qstr_list[1]=='s'){
            if(qstr_list.size()==5){
                QString nickname=qstr_list[2];
                user.nickname=nickname;

                QString state=qstr_list[3];
                user.state=state;

                int likes=qstr_list[4].toInt();
                user.likes=likes;
            }else{
                qDebug()<<"macro qstr_list"<<qstr_list;
            }
        }else{
            qDebug()<<"macro qstr_list"<<qstr_list;
        }
        loop->quit();
        loop->deleteLater();
    };
    connect(socket, &QTcpSocket::readyRead, [=]()mutable{
        buffer += socket->readAll();

        QDataStream in(&buffer, QIODevice::ReadOnly);
        in.setVersion(QDataStream::Qt_6_8);

        qDebug()<<"buffer.size"<<buffer.size();
        in.startTransaction();  // 记录事务开始位置

        QByteArray profile, content;
        in >> profile >> content;  // 尝试解析

        if (in.commitTransaction()) {  // 成功提交
            processData(profile, content);

            // 截断缓冲区
            buffer = buffer.mid(in.device()->pos());
        } else {  // 数据不足
            in.rollbackTransaction();  // in回滚到尝试读取前的状态,还原数据,等待buffer接取更多数据（in是操作buffer的流对象)
        }

        // while (true) {
        //     in.startTransaction(); // 每次循环重新开始事务
        //     QByteArray profile, content;
        //     in >> profile >> content;
        //     if(buffer.size()==0){
        //         break;
        //     }

        //     if (in.commitTransaction()) {
        //         processData(profile, content);

        //         buffer = buffer.mid(in.device()->pos()); // 截断已处理数据
        //         in.device()->seek(0);                    // 重置流到新的缓冲区头部

        //     } else {
        //         in.rollbackTransaction();
        //         break;
        //     }
        // }
    });

    connect(socket,&QTcpSocket::errorOccurred,this,[=](QAbstractSocket::SocketError error)mutable {
        qDebug() <<"patcher Socket Error:"<< error;
        socket->deleteLater();
        loop->quit();
        loop->deleteLater();
    });
    mutex_ip.lockForRead();
    socket->connectToHost(QHostAddress(hostip),hostport);
    mutex_ip.unlock();
    {
        QByteArray content=QString("/m/patch_user*%1*").arg(user.id).toUtf8();
        // content = QString("*%1*%2").arg(content.size()).arg(content).toUtf8();
        QByteArray buffer;
        QDataStream out(&buffer,QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_6_8);
        out<<content;
        // qDebug()<<"patcher buffer"<<buffer;
        if(!socket->waitForConnected(5000)){
            qWarning()<<"patcher 连接超时";
        }else{
            socket->write(buffer);
        }
        QApplication::processEvents();
    }
    loop->exec();
    socket->deleteLater();

    mutex_patch_loop.unlock();
    return true;
}

void UserPatcher::cleanUp()
{
    if(m_thread->isRunning()){
        m_thread->quit();
        m_thread->wait();
    }
}

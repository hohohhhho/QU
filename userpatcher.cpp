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

void UserPatcher::patchGroup(Group group)
{
    auto processData = [=,&group](const QByteArray& profile,const QByteArray& data){

        if(profile.isEmpty() && data.isEmpty()){
            group.name="群聊不存在";
            group.id=-1;
            return;
        }
        QPixmap pxp;
        pxp.loadFromData(profile);
        group.icon=QIcon(pxp);
        QStringList qstr_list=QString(data).split('/');
        if(qstr_list.size()<2){
            qDebug()<<"patchGroup qstr_list"<<qstr_list;
        }else if(qstr_list[1]=='s'){
            if(qstr_list.size()==5){
                QString nickname=qstr_list[2];
                group.name=nickname;

                QString intro=qstr_list[3];
                group.intro=intro;

                int owner = qstr_list[4].toInt();
                group.owner = owner;

                emit groupPatchFinished(group);
            }else{
                qDebug()<<"patchGroup qstr_list"<<qstr_list;
            }
        }else{
            qDebug()<<"patchGroup qstr_list"<<qstr_list;
        }
    };
    QByteArray submit_content = QString("/m/patch_group*%1*").arg(group.id).toUtf8();
    if(submit(submit_content,processData)){
        return;
    }
    qDebug()<<"patchGroup加载失败";
    return;
}

void UserPatcher::patchUser(User user){
    auto processData = [=,&user](const QByteArray& profile,const QByteArray& data){

        if(profile.isEmpty() && data.isEmpty()){
            user.nickname="用户不存在";
            user.id=-1;
            return;
        }
        QPixmap pxp;
        pxp.loadFromData(profile);
        user.icon=QIcon(pxp);
        QStringList qstr_list=QString(data).split('/');
        if(qstr_list.size()<2){
            qDebug()<<"patchUser qstr_list"<<qstr_list;
        }else if(qstr_list[1]=='s'){
            if(qstr_list.size()==5){
                QString nickname=qstr_list[2];
                user.nickname=nickname;

                QString state=qstr_list[3];
                user.state=state;

                int likes=qstr_list[4].toInt();
                user.likes=likes;

                emit userPatchFinished(user);
            }else{
                qDebug()<<"patchUser qstr_list"<<qstr_list;
            }
        }else{
            qDebug()<<"patchUser qstr_list"<<qstr_list;
        }
    };
    QByteArray submit_content = QString("/m/patch_user*%1*").arg(user.id).toUtf8();
    if(submit(submit_content,processData)){
        return;
    }
    qDebug()<<"patchUser失败";
    return;
}

bool UserPatcher::submit(QByteArray submit_content, std::function<void (const QByteArray &, const QByteArray &)> func_if_success)
{
    mutex_patch_loop.lock();

    auto socket = QSharedPointer<QTcpSocket>::create();
    auto loop = QSharedPointer<QEventLoop>::create();
    QByteArray buffer;

    connect(socket.get(), &QTcpSocket::readyRead, socket.get(),[&]()mutable{
        buffer += socket->readAll();

        QDataStream in(&buffer, QIODevice::ReadOnly);
        in.setVersion(QDataStream::Qt_6_8);

        in.startTransaction();

        QByteArray profile, content;
        in >> profile >> content;

        if (in.commitTransaction()) {
            func_if_success(profile, content);
            loop->quit();
            loop->deleteLater();

            buffer = buffer.mid(in.device()->pos());
        } else {
            if (in.status() == QDataStream::ReadPastEnd) {
                qDebug()<<"正常等待更多数据";
            } else if (in.status() == QDataStream::Ok) {
                qDebug()<<"事务为空";
            } else {
                //发生错误，回滚
                in.rollbackTransaction();
            }
        }
    });
    connect(socket.get(),&QTcpSocket::errorOccurred,this,[&](QAbstractSocket::SocketError error)mutable {
        qDebug() <<"patcher Socket Error:"<< error;
        socket->deleteLater();
        loop->quit();
        loop->deleteLater();
    });
    // QTcpSocket* socket = new QTcpSocket;
    // QEventLoop* loop = new QEventLoop;
    // QByteArray buffer;

    // // 使用原始的连接方式，但改进数据处理
    // connect(socket, &QTcpSocket::readyRead, socket,[=]() mutable {
    //     buffer += socket->readAll();

    //     QDataStream in(&buffer, QIODevice::ReadOnly);
    //     in.setVersion(QDataStream::Qt_6_8);

    //     in.startTransaction();

    //     QByteArray profile, content;
    //     in >> profile >> content;

    //     if (in.commitTransaction()) {

    //         func_if_success(loop, profile, content);
    //         loop->quit();
    //         loop->deleteLater();

    //         buffer = buffer.mid(in.device()->pos());
    //     } else {
    //         in.rollbackTransaction();
    //     }
    // });
    // connect(socket,&QTcpSocket::errorOccurred,this,[=](QAbstractSocket::SocketError error)mutable {
    //     qDebug() <<"patcher Socket Error:"<< error;
    //     socket->deleteLater();
    //     loop->quit();
    //     loop->deleteLater();
    // });

    mutex_ip.lockForRead();
    socket->connectToHost(QHostAddress(hostip),hostport);
    mutex_ip.unlock();
    {
        QByteArray content = submit_content;
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

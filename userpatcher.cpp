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

bool UserPatcher::patchGroup(Group &group)
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
            }else{
                qDebug()<<"patchGroup qstr_list"<<qstr_list;
            }
        }else{
            qDebug()<<"patchGroup qstr_list"<<qstr_list;
        }
    };
    QByteArray submit_content = QString("/m/patch_group*%1*").arg(group.id).toUtf8();
    if(submit(submit_content,processData)){
        return true;
    }
    return false;
}

bool UserPatcher::patchUser(User &user){
    auto processData = [=,&user](const QByteArray& profile,const QByteArray& data){

        if(profile.isEmpty() && data.isEmpty()){
            user.nickname="用户不存在";
            user.id=-1;
            // loop->quit();
            // loop->deleteLater();
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
            }else{
                qDebug()<<"patchUser qstr_list"<<qstr_list;
            }
        }else{
            qDebug()<<"patchUser qstr_list"<<qstr_list;
        }
        // loop->quit();
        // loop->deleteLater();
    };
    QByteArray submit_content = QString("/m/patch_user*%1*").arg(user.id).toUtf8();
    if(submit(submit_content,processData)){
        return true;
    }
    return false;
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
            // QByteArray profile_copy = profile;  // 深拷贝
            // QByteArray content_copy = content;
            // QMetaObject::invokeMethod(qApp, [=]() {
            //     func_if_success(loop.get(), profile_copy, content_copy);  // 主线程执行
            // }, Qt::BlockingQueuedConnection);  // 阻塞工作线程
            loop->quit();
            loop->deleteLater();

            buffer = buffer.mid(in.device()->pos());
        } else {
            in.rollbackTransaction();
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

// bool UserPatcher::submit(QByteArray submit_content, std::function<void(QEventLoop*, const QByteArray&, const QByteArray&)> func_if_success) {
//     // 使用智能指针管理生命周期
//     // auto socket = std::make_unique<QTcpSocket>();
//     // auto loop = std::make_unique<QEventLoop>();
//     auto socket = QSharedPointer<QTcpSocket>::create();
//     auto loop = QSharedPointer<QEventLoop>::create();

//     // 使用 QScopedPointer 或 std::unique_ptr 确保资源正确释放
//     QByteArray buffer;

//     connect(socket.get(), &QTcpSocket::readyRead, [&]() {
//         buffer += socket->readAll();

//         QDataStream in(&buffer, QIODevice::ReadOnly);
//         in.setVersion(QDataStream::Qt_6_8);

//         in.startTransaction();

//         QByteArray profile, content;
//         in >> profile >> content;

//         if (in.commitTransaction()) {
//             // 确保在主线程调用
//             QMetaObject::invokeMethod(loop.get(), [&, profile, content]() {
//                 func_if_success(loop.get(), profile, content);
//             }, Qt::QueuedConnection);
//         } else {
//             in.rollbackTransaction();
//         }
//     });

//     // 错误处理
//     connect(socket.get(), &QTcpSocket::errorOccurred,[&loop](QAbstractSocket::SocketError error) {
//                                        qDebug() << "Socket Error:" << error;
//                                        loop->quit();
//                                    }
//                                    );

//     // 网络连接和数据发送
//     socket->connectToHost(QHostAddress(hostip), hostport);

//     {
//         QByteArray buffer;
//         QDataStream out(&buffer, QIODevice::WriteOnly);
//         out.setVersion(QDataStream::Qt_6_8);
//         out << submit_content;

//         if (socket->waitForConnected(5000)) {
//             socket->write(buffer);
//         }
//     }

//     // 事件循环
//     loop->exec();

//     return true;
// }

// bool UserPatcher::patchUser(User &user){
//     mutex_patch_loop.lock();

//     QTcpSocket* socket=new QTcpSocket;
//     QEventLoop* loop=new QEventLoop;
//     QByteArray buffer;
//     auto processData = [=,&user](const QByteArray& profile,const QByteArray& data){

//         if(profile.isEmpty() && data.isEmpty()){
//             user.nickname="用户不存在";
//             user.id=-1;
//             loop->quit();
//             loop->deleteLater();
//             return;
//         }
//         QPixmap pxp;
//         pxp.loadFromData(profile);
//         user.icon=QIcon(pxp);
//         QStringList qstr_list=QString(data).split('/');
//         if(qstr_list.size()<2){
//             qDebug()<<"macro qstr_list"<<qstr_list;
//         }else if(qstr_list[1]=='s'){
//             if(qstr_list.size()==5){
//                 QString nickname=qstr_list[2];
//                 user.nickname=nickname;

//                 QString state=qstr_list[3];
//                 user.state=state;

//                 int likes=qstr_list[4].toInt();
//                 user.likes=likes;
//             }else{
//                 qDebug()<<"macro qstr_list"<<qstr_list;
//             }
//         }else{
//             qDebug()<<"macro qstr_list"<<qstr_list;
//         }
//         loop->quit();
//         loop->deleteLater();
//     };
//     connect(socket, &QTcpSocket::readyRead, [=]()mutable{
//         buffer += socket->readAll();

//         QDataStream in(&buffer, QIODevice::ReadOnly);
//         in.setVersion(QDataStream::Qt_6_8);

//         qDebug()<<"buffer.size"<<buffer.size();
//         in.startTransaction();  // 记录事务开始位置

//         QByteArray profile, content;
//         in >> profile >> content;  // 尝试解析

//         if (in.commitTransaction()) {  // 成功提交
//             processData(profile, content);

//             // 截断缓冲区
//             buffer = buffer.mid(in.device()->pos());
//         } else {  // 数据不足
//             in.rollbackTransaction();  // in回滚到尝试读取前的状态,还原数据,等待buffer接取更多数据（in是操作buffer的流对象)
//         }
//     });

//     connect(socket,&QTcpSocket::errorOccurred,this,[=](QAbstractSocket::SocketError error)mutable {
//         qDebug() <<"patcher Socket Error:"<< error;
//         socket->deleteLater();
//         loop->quit();
//         loop->deleteLater();
//     });
//     mutex_ip.lockForRead();
//     socket->connectToHost(QHostAddress(hostip),hostport);
//     mutex_ip.unlock();
//     {
//         QByteArray content=QString("/m/patch_user*%1*").arg(user.id).toUtf8();
//         // content = QString("*%1*%2").arg(content.size()).arg(content).toUtf8();
//         QByteArray buffer;
//         QDataStream out(&buffer,QIODevice::WriteOnly);
//         out.setVersion(QDataStream::Qt_6_8);
//         out<<content;
//         // qDebug()<<"patcher buffer"<<buffer;
//         if(!socket->waitForConnected(5000)){
//             qWarning()<<"patcher 连接超时";
//         }else{
//             socket->write(buffer);
//         }
//         QApplication::processEvents();
//     }
//     loop->exec();
//     socket->deleteLater();

//     mutex_patch_loop.unlock();
//     return true;
// }

void UserPatcher::cleanUp()
{
    if(m_thread->isRunning()){
        m_thread->quit();
        m_thread->wait();
    }
}

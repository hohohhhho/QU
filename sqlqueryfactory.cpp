#include "sqlqueryfactory.h"
#include "macro.h"

#include <QEventLoop>
#include <QTcpSocket>

SqlQueryFactory::SqlQueryFactory(int max_thread_num, QObject *parent)
    : QObject{parent}
{
    for(int i=0; i<max_thread_num; i++){
        SqlQuery* query = new SqlQuery();
        connect(query,&SqlQuery::finished,this,[=](){
            mutex_task_queue.lock();
            if(!m_task_queue.empty()){
                auto task = m_task_queue.dequeue();
                mutex_task_queue.unlock();
                // qDebug()<<"新的空闲线程，处理任务队列:"<<task.sql;
                // auto run = [=](){
                //     query->run(task);
                // };
                // QMetaObject::invokeMethod(query,run);
                QMetaObject::invokeMethod(query,"run",Q_ARG(SqlQueryTask,task));
            }else{
                mutex_available_queue.lock();
                m_available.enqueue(query);
                mutex_available_queue.unlock();
                mutex_task_queue.unlock();
            }
        });
        m_available.enqueue(query);
    }
}

SqlQueryFactory::~SqlQueryFactory()
{
    mutex_available_queue.lock();
    qDeleteAll(this->m_available);
    mutex_available_queue.unlock();
}

void SqlQueryFactory::addTask(const QByteArray &sql, std::function<void (QTcpSocket *)> ready_read)
{
    SqlQueryTask task(sql, ready_read);
    SqlQuery* query = nullptr;
    mutex_available_queue.lock();
    if(m_available.empty()){
        mutex_available_queue.unlock();
        // qDebug()<<"SqlQueryFactory:无空闲线程,加入任务队列:"<<sql;
        mutex_task_queue.lock();
        m_task_queue.enqueue(task);
        mutex_task_queue.unlock();
    }else{
        // qDebug()<<"SqlQueryFactory:有空闲线程,立即执行:"<<sql;
        query = m_available.dequeue();
        mutex_available_queue.unlock();
        // auto run = [=](){
        //     query->run(task);
        // };
        // QMetaObject::invokeMethod(query,run);
        QMetaObject::invokeMethod(query,"run",Q_ARG(SqlQueryTask,task));
    }
}

void SqlQueryFactory::newSql(const QByteArray &sql, std::function<void (QStringList&)> func_success, std::function<void()> func_fail)
{
    addTask(sql, [=](QTcpSocket* socket){
        QByteArray data = readSocket(socket);
        QStringList list = QString(data).split("/");
        if(list.size() < 2){
            qDebug()<<"SqlQueryFactory:newSql list"<<list;
            return;
        }
        if(list[1] == "s"){

            // qDebug()<<"SqlQueryFactory:newSql sql查询成功";
            if(func_success){
                func_success(list);
            }

        }else if(list[1] == "f"){
            if(func_fail){
                func_fail();
            }
        }else{
            qDebug()<<"接收到了意外的回复"<<data;
        }
    });
}

void SqlQueryFactory::processTask()
{
    // if(!mutex_task_queue.tryLock())return;
    mutex_task_queue.lock();
    if(!m_task_queue.empty()){
        auto task = m_task_queue.dequeue();
        mutex_task_queue.unlock();
        qDebug()<<"处理任务队列"<<task.sql;
        addTask(task.sql, task.ready_read);
    }else{
        mutex_task_queue.unlock();
    }

}

QByteArray SqlQueryFactory::readSocket(QTcpSocket *socket)
{
    m_tcp_buffer += socket->readAll();

    QByteArray content;
    QDataStream in(&m_tcp_buffer,QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_5_15);

    in.startTransaction();
    in>>content;
    if(in.commitTransaction()){
        m_tcp_buffer = m_tcp_buffer.mid(in.device()->pos());
        return content;
    }else{
        if (in.status() == QDataStream::ReadPastEnd) {
            // qDebug()<<"正常等待更多数据";
        }else if (in.status() == QDataStream::Ok) {
            qDebug()<<"事务为空";
        }else {
            //发生错误，回滚
            in.rollbackTransaction();
        }
        return "failed";
    }
}

SqlQuery::SqlQuery(QObject *parent):QObject{parent}{
    this->m_thread = new QThread;
    this->moveToThread(m_thread);
    m_thread->start();
    // QMetaObject::invokeMethod(this,[=](){

    // },Qt::QueuedConnection);
}

SqlQuery::~SqlQuery()
{
    if(m_socket){
        m_socket->deleteLater();
    }
    if(m_loop){
        m_loop->deleteLater();
    }
}

QByteArray SqlQuery::readSocket()
{
    QByteArray content;
    QDataStream in(m_socket);
    in.setVersion(QDataStream::Qt_5_15);

    in.startTransaction();
    in>>content;
    if(in.commitTransaction()){
        return content;
    }else{
        if (in.status() == QDataStream::ReadPastEnd) {
            // qDebug()<<"正常等待更多数据";
        }else if (in.status() == QDataStream::Ok) {
            qDebug()<<"事务为空";
        }else {
            //发生错误，回滚
            in.rollbackTransaction();
        }
        return "failed";
    }
}

void SqlQuery::run(SqlQueryTask task)
{
    if(!m_socket){
        m_socket = new QTcpSocket;
        m_socket->connectToHost(QHostAddress(hostip),hostport);
        if(m_socket->state()==QTcpSocket::ConnectingState && !m_socket->waitForConnected(5000)){
            qDebug()<<"连接超时";
        }
    }
    if(!m_loop){
        m_loop = new QEventLoop;
    }
    connect(m_socket,&QTcpSocket::readyRead,this,[=](){
        m_loop->quit();
        task.ready_read(m_socket);
    });
    connect(m_socket,&QTcpSocket::errorOccurred,this,[=](QAbstractSocket::SocketError error) {
        qDebug() <<"Socket Error:"<< error;
        m_loop->quit();
    });

    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_15);
    out<<task.sql;

    m_socket->write(buffer);
    // QApplication::processEvents();
    m_loop->exec();
    // qDebug()<<"finished";
    emit finished();
}

#ifndef SQLQUERYFACTORY_H
#define SQLQUERYFACTORY_H

#include <QEventLoop>
#include <QMutex>
#include <QObject>
#include <QTcpSocket>
#include <QThread>
#include <Qqueue>

struct SqlQueryTask{
    SqlQueryTask(){};
    SqlQueryTask(QByteArray sql, std::function<void(QTcpSocket*)> ready_read):sql(sql), ready_read(ready_read){}
    QByteArray sql;
    std::function<void(QTcpSocket*)> ready_read;
};
Q_DECLARE_METATYPE(SqlQueryTask);

class SqlQuery : public QObject{
    Q_OBJECT
public:
    SqlQuery(QObject *parent = nullptr);
    ~SqlQuery();
    QByteArray readSocket();
    // void init(SqlQueryTask task){
    //     m_task = task;
    // }
    // void clear(){//清除缓存
    //     m_task.sql = "";
    //     m_task.ready_read = NULL;
    // }
public slots:
    void run(SqlQueryTask task);
signals:
    void finished();
private:
    QThread* m_thread;
    QTcpSocket* m_socket = nullptr;
    QEventLoop* m_loop = nullptr;
    // SqlQueryTask m_task;
};

class SqlQueryFactory : public QObject
{
    Q_OBJECT
public:
    explicit SqlQueryFactory(int max_thread_num, QObject *parent = nullptr);
    ~SqlQueryFactory();
    void addTask(const QByteArray &sql, std::function<void(QTcpSocket*)> ready_read);
    void newSql(const QByteArray &sql, std::function<void (QStringList &)> func_success, std::function<void ()> func_fail = NULL);
    void processTask();

signals:
private:
    QMutex mutex_available_queue;
    QQueue<SqlQuery*> m_available;
    QMutex mutex_task_queue;
    QQueue<SqlQueryTask> m_task_queue;
    QByteArray m_tcp_buffer;

    QByteArray readSocket(QTcpSocket *socket);
};

inline QMutex mutex_sql_query_factory;
inline SqlQueryFactory* sql_query_factory = nullptr;

#endif // SQLQUERYFACTORY_H

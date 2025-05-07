#ifndef MACRO_H
#define MACRO_H

#include <QObject>
#include <QDateTime>
#include <QIcon>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QMutex>
#include <QReadWriteLock>
#include <QTcpSocket>
#include <QEventLoop>

#define HOSTPORT 8899

inline QReadWriteLock mutex_ip;
inline QMutex mutex_patch_loop;
inline QString hostip="192.168.163.137";
inline quint16 hostport=HOSTPORT;
// inline QString hostip="13.115.131.56";
// inline quint16 hostport=12236;

enum ServerMod{
    Linux,
    Windows,
    Cloud,
    Custom
};
inline ServerMod server_mod=ServerMod::Linux;

inline void static patchDatabase(QSqlDatabase& db){
    static QString setDatabaseName("work5_qq");
    static QString setHostName(hostip);
    // static quint16 setPort(hostport);
    static QString setUserName("testuser");
    static QString setPassword("222222");
    mutex_ip.lockForRead();
    if(setHostName!=hostip){
        setHostName=hostip;
    }
    // if(setPort!=hostport){
    //     setPort=hostport;
    //     qDebug()<<"更新端口"<<setPort;
    // }
    mutex_ip.unlock();
    db.setDatabaseName(setDatabaseName);
    db.setHostName(setHostName);
    // db.setPort(setPort);
    db.setUserName(setUserName);
    db.setPassword(setPassword);
}

inline QByteArray static defaultReadSocket(QTcpSocket *socket)
{
    QByteArray content;
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_8);
    in>>content;

    return content;
}

class User{
public:
    int id=-1;
    QString nickname="";
    QIcon icon;
    QString state="在线";
    int likes=0;
    QList<User> friends;
    QList<QPair<User,QString>> friend_request;
    // User(int id=0,QString nickname="",QIcon icon=QIcon()):id(id),nickname(nickname),icon(icon){
    //     QSqlDatabase::addDatabase("QMYSQL","load");
    // }
    // ~User(){
    //     QSqlDatabase::removeDatabase("load");
    // }

    bool operator==(const User& other)const{
        return this->id==other.id;
    }
    // bool patchUser();
};

class Message{
public:
    enum MessageType{
        Text,
        Picture,
        File
    }type;

    Message(){type=MessageType::Text;}

    MessageType static getType(QByteArray array){
        QPixmap pxp;
        pxp.loadFromData(array);
        if(!pxp.isNull()){
            return MessageType::Picture;
        }
        return MessageType::Text;
    }

    User sender;
    User receiver;
    QDateTime time;
    QByteArray msg="";
    QVector<User> vt_group_user;
};

#endif // MACRO_H

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
#include <QCryptographicHash>

#define HOSTPORT 8899
#define WINDOWSIP "127.0.0.1"
#define LINUXIP "192.168.163.137"
#define CLOUDIP "57.180.185.238"

inline QReadWriteLock mutex_ip;
inline QMutex mutex_patch_loop;
// inline quint16 hostport=HOSTPORT;
inline QString hostip = CLOUDIP ;
inline quint16 hostport = 12745;

enum ServerMod{
    Linux,
    Windows,
    Cloud,
    Custom
};
inline ServerMod server_mod=ServerMod::Windows;

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
    in.setVersion(QDataStream::Qt_5_15);
    in>>content;

    return content;
}

inline QByteArray static calculateHash(const QByteArray& data)
{
    QCryptographicHash hash(QCryptographicHash::Sha1);
    hash.addData(data);
    return hash.result().toHex();
}

class Group{
public:
    int id = -1;
    QString name;
    QIcon icon;
    QString intro;
    int owner;
    bool operator==(const Group& other)const{
        return this->id==other.id;
    }
    bool isEmpty(){
        return name.isEmpty() || icon.isNull();
    }
};

class User{
public:
    int id=-1;
    QString nickname="";
    QIcon icon;
    QString state="在线";
    int likes=0;
    QList<User> friends;
    QList<Group> groups;
    QList<QPair<User,QString>> friend_request;

    bool operator==(const User& other)const{
        return this->id==other.id;
    }
    bool isEmpty()const{
        return nickname.isEmpty() || icon.isNull();
    }
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
    User receiver_user;
    Group receiver_group;
    QDateTime time;
    QByteArray msg="";
    QVector<User> vt_group_user;
};

inline const static QColor color_blue(42,72,160);//蓝色
inline const static QColor color_light_blue(42,72,160,30);//浅蓝色

#endif // MACRO_H

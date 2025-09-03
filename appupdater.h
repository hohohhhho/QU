#ifndef APPUPDATER_H
#define APPUPDATER_H

#include <QFile>
#include <QObject>

class AppUpdater : public QObject
{
    Q_OBJECT
public:
    explicit AppUpdater(QObject *parent = nullptr,QString packetname = "Windows");

    void getUpdate(QString path_install);
    QByteArray calculateFileHash(const QByteArray &file_data)const;
signals:
    void progress(qreal progress);
private:
    QString packetname;
    // void installPacket(const QByteArray& packet);
};

#endif // APPUPDATER_H

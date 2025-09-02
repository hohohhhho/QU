#include "appupdater.h"
#include "macro.h"
#include "loadwidget.h"

#include <QApplication>
#include <QDesktopServices>
#include <QDir>
#include <QEventLoop>
#include <QIcon>
#include <QMessageBox>
#include <QPixmap>
#include <QProcess>
#include <QTcpSocket>
#include <QThread>
#include <QUrl>

AppUpdater::AppUpdater(QObject *parent, QString packetname)
    : QObject{parent},packetname(packetname)
{

}

void AppUpdater::getUpdate(QString path_install)
{
    LoadWidget* load = new LoadWidget;
    load->changeText("程序更新中");
    load->show();
    auto socket = QSharedPointer<QTcpSocket>::create();
    auto loop = QSharedPointer<QEventLoop>::create();
    QByteArray buffer;
    quint32 size_packet = 0;

    connect(socket.get(), &QTcpSocket::readyRead, socket.get(),[&]()mutable{
        buffer += socket->readAll();

        QDataStream in(&buffer, QIODevice::ReadOnly);
        in.setVersion(QDataStream::Qt_5_15);

        in.startTransaction();

        if(size_packet <= 0){
            in>>size_packet;
            qDebug()<<"size_packet"<<size_packet;
        }
        QByteArray data;
        in >> data;


        // if(size_packet <= 0 && buffer.size() >= (qint64)sizeof(quint64)){
        //     QByteArray size_data = buffer.left(sizeof(quint64));

        //     size_packet = QString(size_data).toUInt();
        //     qDebug()<<"QString(size_data)"<<QString(size_data);
        // }

        if (in.commitTransaction()) {

            QDir dir(path_install);
            if(!dir.exists()){
                dir.mkdir(path_install);
            }
            QString filename(path_install + "/update.zip");
            QFile file_packet(filename);
            if(!file_packet.open(QIODevice::WriteOnly)){
                qDebug()<<"软件压缩包写入失败";
            }
            file_packet.write(data);
            file_packet.close();
            qDebug()<<"file_packet创建并写入成功"<<file_packet.fileName();

            QProcess process;
            QString program("powershell");
            QStringList args1;
            process.setProcessChannelMode(QProcess::MergedChannels);
            args1 << "-NoProfile" << "-NonInteractive" << "-Command"
                      << QString("Expand-Archive -Path %1 -DestinationPath %2")
                             .arg("\"" + filename + "\"" , "\"" + path_install + "\"");
            process.start(program,args1);
            if(!process.waitForFinished(30000)) {
                QMessageBox::warning(nullptr,"提示","软件解压缩失败，请自行解压缩\n"+process.readAllStandardError());
                process.kill();
                return;
            }
            QStringList args2;
            args2<<"del" <<filename;
            process.start(program,args2);
            if(!process.waitForFinished(5000)) {
                QMessageBox::warning(nullptr,"提示","压缩包删除失败，请自行删除\n"+process.readAllStandardError());
                process.kill();
                return;
            }

            load->setVisible(false);
            auto result = QMessageBox::information(nullptr,"提示","软件更新完成\n点击Ok打开该文件",
                                     QMessageBox::StandardButtons(QMessageBox::StandardButton::Ok|
                                                                  QMessageBox::StandardButton::Close));
            if(result == QMessageBox::StandardButton::Ok){
                QDesktopServices::openUrl(QUrl::fromLocalFile(path_install));
            }

            loop->quit();
            loop->deleteLater();

            buffer = buffer.mid(in.device()->pos());
        } else {
            if (in.status() == QDataStream::ReadPastEnd) {
                qreal progress = (qreal)buffer.size()/size_packet;
                progress = qBound(0.0f,progress,1.0f);
                QString text("程序更新中" + QString::number(progress*100,'f',2) + '%');
                load->changeProgress(progress,text);
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

    mutex_ip.lockForRead();
    socket->connectToHost(QHostAddress(hostip),hostport);
    mutex_ip.unlock();
    {
        QByteArray content = "/z";
        QByteArray buffer;
        QDataStream out(&buffer,QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_6_8);
        out<<content;
        if(!socket->waitForConnected(5000)){
            qWarning()<<"updater 连接超时";
        }else{
            socket->write(buffer);
        }
        QApplication::processEvents();
    }
    loop->exec();
    socket->deleteLater();
    load->deleteLater();
}

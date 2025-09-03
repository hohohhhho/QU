#include "appupdater.h"
#include "macro.h"
#include "loadwidget.h"

#include <QApplication>
#include <QCryptographicHash>
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


    connect(socket.get(), &QTcpSocket::readyRead, socket.get(),[&]()mutable{
        buffer += socket->readAll();

        QDataStream in(&buffer, QIODevice::ReadOnly);
        in.setVersion(QDataStream::Qt_5_15);

        in.startTransaction();

        QByteArray data, filename, hash;
        quint64 size_packet = 0;
        in >>size_packet >> filename >>data >>hash;


        // if(size_packet <= 0 && buffer.size() >= (qint64)sizeof(quint64)){
        //     QByteArray size_data = buffer.left(sizeof(quint64));

        //     size_packet = QString(size_data).toUInt();
        //     qDebug()<<"QString(size_data)"<<QString(size_data);
        // }

        if (in.commitTransaction()) {

            auto finish = [=, &in]()mutable{//结束该栈区需要进行的收尾操作
                loop->quit();
                loop->deleteLater();

                buffer = buffer.mid(in.device()->pos());
            };

            load->changeProgress(1.0f,"校验文件哈希值");
            auto hash_result = calculateFileHash(data);
            if( hash != hash_result){
                load->setVisible(false);
                QMessageBox::warning(nullptr,"提示",QString("安装包哈希值校验失败%1\n请重新下载更新")
                                                          .arg(hash_result));
                finish();
                return;
            }

            load->changeProgress(1.0f,"安装文件至本地");
            QDir dir(path_install);
            if(!dir.exists()){
                dir.mkdir(path_install);
            }
            QString filepath(path_install + "/update.zip");
            QFile file_packet(filepath);
            if(!file_packet.open(QIODevice::WriteOnly)){
                qDebug()<<"软件压缩包写入失败";
            }
            file_packet.write(data);
            file_packet.close();

            load->changeProgress(1.0f,"解压缩文件");
            QProcess process;
            QString program("powershell");
            QStringList args1;
            process.setProcessChannelMode(QProcess::MergedChannels);
            args1 << "-NoProfile" << "-NonInteractive" << "-Command"
                      << QString("Expand-Archive -Path %1 -DestinationPath %2")
                             .arg("\"" + filepath + "\"" , "\"" + path_install + "\"");
            process.start(program,args1);
            if(!process.waitForFinished(30000)) {
                QMessageBox::warning(nullptr,"提示","软件解压缩失败，请自行解压缩\n"+process.readAllStandardError());
                process.kill();
                finish();
                return;
            }

            load->changeProgress(1.0f,"删除压缩包");
            QStringList args2;
            args2<<"del" <<filepath;
            process.start(program,args2);
            if(!process.waitForFinished(5000)) {
                QMessageBox::warning(nullptr,"提示","压缩包删除失败，请自行删除\n"+process.readAllStandardError());
                process.kill();
                finish();
                return;
            }

            load->setVisible(false);
            auto result = QMessageBox::information(nullptr,"提示","软件更新完成\n点击Ok打开该文件",
                                     QMessageBox::StandardButtons(QMessageBox::StandardButton::Ok|
                                                                  QMessageBox::StandardButton::Close));
            if(result == QMessageBox::StandardButton::Ok){
                QDir dir(path_install);
                if(!QDesktopServices::openUrl(QUrl::fromLocalFile(dir.filePath(filename)))){
                    QMessageBox::warning(nullptr,"提示","文件打开失败");
                }
            }

            finish();
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

QByteArray AppUpdater::calculateFileHash(const QByteArray &file_data) const
{
    QCryptographicHash hash(QCryptographicHash::Sha1);
    hash.addData(file_data);
    qDebug()<<"hash.result()";
    return hash.result().toHex();
}

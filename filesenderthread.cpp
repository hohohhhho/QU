#include "filesenderthread.h"
#include "macro.h"

#include <QFileInfo>

FileSenderThread::FileSenderThread(OBJ oj, int receiveID, int senderID, QString fileID, QString filePath, qint64 offset, qint64 chunkSize, qint64 totalSize)
    : m_receiver_type(oj), m_receiveID(receiveID),  m_senderID(senderID), m_fileID(fileID),
    m_filePath(filePath), m_offset(offset), m_chunkSize(chunkSize), m_totalSize(totalSize) {}

void FileSenderThread::run() {
    QTcpSocket socket;
    socket.connectToHost(hostip, hostport);

    if (!socket.waitForConnected(5000)) return;

    QFile file(m_filePath);
    if (file.open(QIODevice::ReadOnly)) {
        file.seek(m_offset);
        QByteArray fileData = file.read(m_chunkSize);

        // 发送的格式：/s*[receiveID]**[senderID]**[fileID]**[filename]**[offset]**[totalSize]**[数据]

        QByteArray buffer;
        QDataStream out(&buffer, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_15);

        // 组装包头
        QByteArray header;
        if(m_receiver_type == OBJ::user){
            header = "/S";
        }else if(m_receiver_type == OBJ::group){
            header = "/G";
        }else{
            qDebug()<<"FileSenderThread:对象错误";
            return;
        }
        header.append(QString("*%1**%2**%3**%4**%5**%6*")
                                .arg(m_receiveID)
                                .arg(m_senderID)
                                .arg(m_fileID)
                                .arg(QFileInfo(m_filePath).fileName())
                                .arg(m_offset)
                                .arg(m_totalSize)
                                .toUtf8());
        qDebug()<<"FileSenderThread:filename:"<<QFileInfo(m_filePath).fileName();

        out << (header + fileData);
        socket.write(buffer);
        socket.waitForBytesWritten();
        socket.disconnectFromHost();
    }
}

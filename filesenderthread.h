#ifndef FILESENDERTHREAD_H
#define FILESENDERTHREAD_H

// FileSenderThread.h
#include "macro.h"

#include <QThread>
#include <QTcpSocket>
#include <QFile>
#include <QDataStream>

class FileSenderThread : public QThread {
    Q_OBJECT
public:
    // 参数：接收者ID, 发送者ID, 文件ID, 文件路径, 偏移量, 块大小, 文件总大小
    FileSenderThread(OBJ oj, int receiveID, int senderID, QString fileID,
                     QString filePath, qint64 offset, qint64 chunkSize, qint64 totalSize);

protected:
    void run() override;

private:
    OBJ m_receiver_type;
    int m_receiveID, m_senderID;
    QString m_fileID, m_filePath;
    qint64 m_offset, m_chunkSize, m_totalSize;
};



#endif // FILESENDERTHREAD_H

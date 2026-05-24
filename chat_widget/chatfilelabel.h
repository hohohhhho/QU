#ifndef CHATFILELABEL_H
#define CHATFILELABEL_H

#include <QObject>
#include <QLabel>
#include "macro.h"

class ChatFileLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ChatFileLabel(QWidget *parent = nullptr);

    void resizeEvent(QResizeEvent* ev)override;
    void mousePressEvent(QMouseEvent* ev)override;
    void mouseDoubleClickEvent(QMouseEvent* ev)override;
    void paintEvent(QPaintEvent* ev)override;

    void setPicture(const QString& filename, const QPixmap& pxp);
    void setVideo(const QString& filename, const QByteArray& data);
    void setNormalFile(const QString& filename, const QByteArray& data);

    void adjustSize();
signals:
private:
    Message::MessageType m_type = Message::MessageType::File;
    QByteArray m_data;
    QString m_filename = "未知文件";
};

#endif // CHATFILELABEL_H

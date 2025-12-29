#ifndef CHATPICTURELABEL_H
#define CHATPICTURELABEL_H

#include <QLabel>

class ChatPictureLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ChatPictureLabel(QWidget *parent = nullptr);
    void resizeEvent(QResizeEvent* ev)override;

    void setPicture(QPixmap pxp);
signals:
private:
    QPixmap m_pxp;
};

#endif // CHATPICTURELABEL_H

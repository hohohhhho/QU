#ifndef CHATVIEW_H
#define CHATVIEW_H

#include "macro.h"
#include <QVBoxLayout>
#include <QWidget>

class ChatView : public QWidget
{
    Q_OBJECT
public:
    explicit ChatView(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent* ev)override;
    void init(User m_user, User o_user);

    // void addMyMsg(QString message);
    // void addTheOtherMsg(QString message);
    void addMsg(Message message, bool my);

    User m_user;
    User o_user;

signals:
private:
    QVBoxLayout* vlayout;
};

#endif // CHATVIEW_H

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
    void init(User my_user, Group group);

    // void addMyMsg(QString message);
    // void addTheOtherMsg(QString message);
    void addMsg(Message message, bool my);
    void addMsg(Message message, User sender);

signals:
private:
    QVBoxLayout* vlayout;
    User m_user;
    User o_user;
    Group m_group;
};

#endif // CHATVIEW_H

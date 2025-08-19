#ifndef CHATVIEW_H
#define CHATVIEW_H

#include "macro.h"
#include <QVBoxLayout>
#include <QWidget>

class ChatView : public QWidget//聊天气泡显示的区域
{
    Q_OBJECT
public:
    explicit ChatView(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent* ev)override;
    void resizeEvent(QResizeEvent* ev)override;

    void init(User m_user, User o_user);
    void init(User my_user, Group group);

    void addMsg(Message message, bool my);
    void addMsg(Message message, User sender);

signals:
private:
    QVBoxLayout* vlayout;
    User m_user;
    User o_user;
    Group m_group;
    QList<QWidget*> list_container;
};

#endif // CHATVIEW_H

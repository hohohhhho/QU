#ifndef CHATVIEW_H
#define CHATVIEW_H

#include "chatbubble.h"
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

    // void addMsg(Message message, bool my);
    void addMsg(Message message, User sender);
    void adjustSize(QSize size);

signals:
private:
    QVBoxLayout* m_vlayout;//窗口主体布局
    User m_user;
    User o_user;
    Group m_group;

    QList<ChatBubble*> list_bubble;
    QList<QWidget*> list_container;
};

#endif // CHATVIEW_H

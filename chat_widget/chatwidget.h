#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QQueue>
#include <QVariantAnimation>
#include <QWidget>
#include "macro.h"
#include "emotion_widget/emotionwidget.h"

namespace Ui {
class ChatWidget;
}

class ChatWidget : public QWidget
{
    Q_OBJECT

public:
    enum Type{
        user,
        group
    }type;
    explicit ChatWidget(QWidget *parent = nullptr);
    ~ChatWidget();

    void init(User my_user, User other_user, QList<Message> list_msg={});//初始化为私聊聊天窗口
    void init(User my_user, Group group, QList<Message> list_msg={});//初始化为群聊聊天窗口
    void addMsg(const QByteArray &msg, bool my, bool unread=false, bool save=true);//添加私聊消息
    void addMsg(const QByteArray &msg, User sender, bool unread=false, bool save=true);//添加群聊消息
    void updateScrollBar();//更新滚动条到最下方

signals:
    void sendMsg(const QString& text);
    void sendFile(const QByteArray& data);
    void call(const int& id);
    void toDelete();
    void refresh();
    void updatePreviewState();
private:
    Ui::ChatWidget *ui;
    EmotionWidget* w_emo;
    QVariantAnimation* animation;

    QSet<User> members;//群聊成员
    Group m_group;//群聊
    User m_user;//本用户
    User o_user;//对方
};

#endif // CHATWIDGET_H

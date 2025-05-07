#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QQueue>
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
    explicit ChatWidget(QWidget *parent = nullptr);
    ~ChatWidget();

    void init(User m_user, User o_user, QList<Message> list_msg={});
    void addMsg(const QByteArray &msg, bool my, bool unread=false, bool save=true);

    User m_user;
    User o_user;

signals:
    void sendMsg(const QString& text);
    void sendFile(const QByteArray& data);
    void toDelete();
    void updatePreviewState();
private:
    Ui::ChatWidget *ui;
    EmotionWidget* w_emo;
};

#endif // CHATWIDGET_H

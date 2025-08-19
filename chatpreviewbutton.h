#ifndef CHATPREVIEWBUTTON_H
#define CHATPREVIEWBUTTON_H

#include <Profile.h>
#include <QDateTime>
#include <QHBoxLayout>
#include <QLabel>
#include <QMutex>
#include <QQueue>
#include <QWidget>
#include "macro.h"

class ChatPreviewButton : public QWidget
{
    Q_OBJECT
public:
    enum Type{
        user,
        group
    }type;
    explicit ChatPreviewButton(User user,QWidget *parent = nullptr);
    explicit ChatPreviewButton(Group group, QWidget *parent = nullptr);

    void paintEvent(QPaintEvent* ev)override;
    void mousePressEvent(QMouseEvent* ev)override;

    void choose(bool choose=true);
    void updateState();

    User m_user;
    Group m_group;
    bool isChecked();

    QString unique_text;//设置了文字后不再显示消息预览而是显示该文字


    QList<Message> list_message;
    QList<Message> list_message_unread;
signals:
    void clicked(bool pre_has_hecked);
    void readMsgNum(int num);
private:
    QColor color_bk=QColor(244,234,42,100);
    QMutex mutex_checked;
    bool checked=false;

    QHBoxLayout* m_hl;
    Profile* profile;
    QVBoxLayout* m_vl1;
    QLabel* label_nickname;
    QLabel* label_msg;
    QVBoxLayout* m_vl2;
    QLabel* label_time;
    QLabel* label_num_msg;

    // void init(const QIcon& icon,const QString& name);
    void init();
};

#endif // CHATPREVIEWBUTTON_H

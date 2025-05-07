#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "chatpreviewbutton.h"
#include "chatwidget.h"
#include "roundlabel.h"

#include <QMainWindow>
#include <QTcpSocket>
#include <QVariantAnimation>
#include <QSoundEffect>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum AdjustPreviewButtonSize{
        ScrollFriend,
        ScrollPreview,
        All
    };
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void init(int id, QString account, QString password);

    void paintEvent(QPaintEvent* ev)override;
    void resizeEvent(QResizeEvent* ev)override;
    void moveEvent(QMoveEvent* ev)override;
    void closeEvent(QCloseEvent* ev)override;

    // void sendMsg(QTcpSocket *socket, const QByteArray &msg);//给服务器端发送请求
    void sendMsg(int id_receiver, const QString &msg, const QChar &style_head='s');//给其他用户发送消息
    void sendFile(int id_receiver, const QByteArray &data, const QChar &style_head='s');
    void showTip(const QString& tip);
    void adjustTipPos(QPoint dpos=QPoint(0,0));
    QByteArray readSocket(QTcpSocket *socket);
    QPair<int, QByteArray> readMsg(const QByteArray& msg);
    // void newSql(const QByteArray& sql="/m/业务类型*参数*",void(*func_success)()=nullptr);
    void newSql(const QByteArray& sql="/m/业务类型*参数*", std::function<void (QStringList &)> func_success=nullptr
                , std::function<void()> func_fail=nullptr);

    void addUserDetailWidget(User user);
    void addChatWidget(User user_friend);
    ChatPreviewButton *addPreviewButton(User user_friend);
    bool addFriend(User user_friend,bool save_to_sql=true);
    void updateFriendRequest();
    void updateFriendList();
    void adjustPreviewButtonSize(AdjustPreviewButtonSize mod=AdjustPreviewButtonSize::All
                                 ,ChatPreviewButton* btn=nullptr);


signals:
    void initProgress(qreal progress,QString text);
private:
    Ui::MainWindow *ui;

    User m_user;
    QTcpSocket* socket;
    QList<ChatPreviewButton*> list_chatpreview;
    QList<ChatPreviewButton*> list_firend;
    QString m_account;
    QString m_password;
    QQueue<QString> queue_tip;
    QVariantAnimation* aniamtion_tip;

    QButtonGroup* btn_group_main;
    QButtonGroup* btn_group_set;
    QVBoxLayout* vl_user_detail;
    QVBoxLayout* vl_chatwith;
    ChatWidget* chatwidget;
    RoundLabel* label_tip;
    QLabel* label_wait;
    // QMutex mutex_friend_request_delete;
    QMutex mutex_read_socket;
    QSoundEffect* sound_msg;
};
#endif // MAINWINDOW_H

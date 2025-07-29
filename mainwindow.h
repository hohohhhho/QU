#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "chatpreviewbutton.h"
#include "chatwidget.h"
#include "roundlabel.h"

#include <QMainWindow>
#include <QTcpSocket>
#include <QVariantAnimation>
#include <QSoundEffect>
#include <QPointer>
#include <camerawidget.h>

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

    // void sendMsg(QTcpSocket *socket, const QByteArray &msg);//给服务器端发送请求
    void sendMsg(int id_receiver, const QString &msg, const QChar &style_head='s');//给其他用户发送消息
    void sendFile(int id_receiver, const QByteArray &data, const QChar &style_head='s');
    void sendVideoOverMsg(int id_receiver,const QTime& time);
    void showTip(const QString& tip);
    void adjustTipPos(QPoint dpos=QPoint(0,0));
    QByteArray readSocket(QTcpSocket *socket);
    QPair<int, QByteArray> readMsg(const QByteArray& msg);
    // void newSql(const QByteArray& sql="/m/业务类型*参数*",void(*func_success)()=nullptr);
    void newSql(const QByteArray& sql="/m/业务类型*参数*", std::function<void (QStringList &)> func_success=nullptr
                , std::function<void()> func_fail=nullptr);

    void addUserDetailWidget(User user);
    void addGroupDetailWidget(Group group);
    void addChatWidget(User user_friend);
    void addChatWidget(Group group);
    ChatPreviewButton *addPreviewButton(User user_friend);
    ChatPreviewButton *addPreviewButton(Group group);
    bool addFriend(User user_friend,bool save_to_sql=true);
    bool addGroup(const Group& group, bool save_to_sql=true);
    void updateFriendRequest();
    void updateFriendList();
    void updateGroupList();
    void adjustPreviewButtonSize(AdjustPreviewButtonSize mod=AdjustPreviewButtonSize::All
                                 ,ChatPreviewButton* btn=nullptr);
    void showCameraWidget(const int &id_sender);
    void createGroup();

    QString handleDataHead(QByteArray &data, const QChar &split='*');
public slots:
    void handleSocket();
signals:
    void initProgress(qreal progress,QString text);
private:
    Ui::MainWindow *ui;
    QPointer<CameraWidget> m_camera_widget;//视频通话窗口

    User m_user;
    QTcpSocket* socket;//与服务器通信套接字
    QList<ChatPreviewButton*> list_chatpreview;//聊天选择好友 按钮列表
    QList<ChatPreviewButton*> list_friend;//好友 按钮列表
    QList<ChatPreviewButton*> list_group;//群聊 按钮列表
    QString m_account;
    QString m_password;
    QQueue<QString> queue_tip;//消息队列
    QVariantAnimation* aniamtion_tip;//消息弹窗弹出动画
    QTimer* timer_msg_clear;

    QButtonGroup* btn_group_main;//左侧主按钮组
    QButtonGroup* btn_group_set;//设置界面按钮组
    QVBoxLayout* vl_user_detail;//用户信息布局
    QVBoxLayout* vl_group_detail;//群聊信息布局
    QVBoxLayout* vl_chatwith;
    QPointer<ChatWidget> chatwidget;//具体的聊天窗口
    RoundLabel* label_tip;//消息弹窗
    QLabel* label_wait;//等待加载标签
    // QMutex mutex_friend_request_delete;
    QMutex mutex_read_socket;
    QSoundEffect* sound_msg;//收到消息音效
};
#endif // MAINWINDOW_H

#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QTcpSocket>
#include <QVariantAnimation>
#include <QWidget>
#include "SetDialog.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class LoginWidget;
}
QT_END_NAMESPACE

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();
    void paintEvent(QPaintEvent* ev)override;

    QByteArray readSocket(QTcpSocket *socket);
    void sendMsg(QTcpSocket *socket, const QByteArray& msg);
signals:
    void login(int id);
    void registered(int id);

private:
    Ui::LoginWidget *ui;
    QVariantAnimation* animation;
    SetDialog* dlg_set;
    bool playing=false;
    bool real_time_detection=true;
};
#endif // LOGINWIDGET_H

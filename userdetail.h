#ifndef UserDetail_H
#define UserDetail_H

#include <QWidget>
#include "macro.h"

namespace Ui {
class UserDetail;
}

class UserDetail : public QWidget
{
    Q_OBJECT

public:
    explicit UserDetail(User user,QWidget *parent = nullptr,bool isfriend=false,bool myself=false);
    ~UserDetail();
    User m_user;
    bool init();
signals:
    void updateUserInfo(User new_user_info,QByteArray data=NULL);
    void showTip(const QString& tip);
    void chatWith();
    void addFriend(QString request_msg);
    void deleteFriend(QString delete_msg);
private:
    Ui::UserDetail *ui;
    void newSql(const QByteArray &sql, std::function<void (QStringList &)> func_success=nullptr, std::function<void ()> func_fail=nullptr);
};

#endif // UserDetail_H

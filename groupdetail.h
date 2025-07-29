#ifndef GROUPDETAIL_H
#define GROUPDETAIL_H

#include "macro.h"

#include <QWidget>

namespace Ui {
class GroupDetail;
}

class GroupDetail : public QWidget
{
    Q_OBJECT

public:
    explicit GroupDetail(const User& user,const Group &group, QWidget *parent = nullptr);
    ~GroupDetail();


signals:
    void showTip(const QString& tip);
    void updateGroupList();
    void chat();
private:
    Ui::GroupDetail *ui;
    User m_user;
    Group m_group;
    int role = 0;
    bool edit_mod = false;
    void newSql(const QByteArray &sql, std::function<void (QStringList &)> func_success, std::function<void ()> func_fail=NULL);
    void modifyGroup();
    void modifyGroupIcon();
    void leaveGroup();
};

#endif // GROUPDETAIL_H

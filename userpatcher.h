#ifndef USERPATCHER_H
#define USERPATCHER_H

#include <QObject>
#include "macro.h"

class UserPatcher : public QObject
{
    Q_OBJECT
public:
    explicit UserPatcher(QObject *parent = nullptr);
    ~UserPatcher();
    User m_user;
    bool patchUser(User &user);
public slots:
    void cleanUp();
signals:
private:
    QThread* m_thread;
};

#endif // USERPATCHER_H

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
    bool patchGroup(Group& group);
    bool submit(QByteArray submit_content,
                std::function<void (const QByteArray &, const QByteArray &)> func_if_success);
public slots:
    void cleanUp();
signals:
private:
    QThread* m_thread;
};

#endif // USERPATCHER_H

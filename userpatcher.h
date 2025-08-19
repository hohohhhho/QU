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
    void patchUser(User user);
    void patchGroup(Group group);
    bool submit(QByteArray submit_content,
                std::function<void (const QByteArray &, const QByteArray &)> func_if_success);
public slots:
    void cleanUp();
signals:
    void userPatchFinished(User user_patched);
    void groupPatchFinished(Group group_patched);
private:
    QThread* m_thread;
};

#endif // USERPATCHER_H

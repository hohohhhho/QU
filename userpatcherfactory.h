#ifndef USERPATCHERFACTORY_H
#define USERPATCHERFACTORY_H

#include <QObject>
#include <QQueue>
#include "userpatcher.h"

class UserPatcherFactory : public QObject
{
    Q_OBJECT
public:
    explicit UserPatcherFactory(int max_thread_num, QObject *parent = nullptr);
    ~UserPatcherFactory();
    //任务类，兼容User和Group
    struct Task{
        Task(User user, QObject* oj, bool blocking, std::function<void(User)> callback)
            :type(OBJ::user), oj(oj), user(user), blocking(blocking), callback_user(callback){}
        Task(Group group, QObject* oj, bool blocking, std::function<void(Group)> callback)
            :type(OBJ::group), oj(oj), group(group), blocking(blocking), callback_group(callback){}

        OBJ::Type type;
        QObject* oj;
        User user;
        Group group;
        bool blocking;
        std::function<void(User)> callback_user;
        std::function<void(Group)> callback_group;
    };

    // void patch(OBJ obj, bool blocking, std::function<void(OBJ)> callback);
    void patchUser(QObject* oj, User user, bool blocking, std::function<void(User)> callback);
    void patchGroup(QObject* oj, Group group, bool blocking, std::function<void(Group)> callback);
signals:
private:
    int max_thread_num = 0;
    std::atomic<int> thread_working = 0;
    QMutex mutex_available_queue;
    QQueue<UserPatcher*> m_available;
    QMutex mutex_task_queue;
    QQueue<Task> m_task_queue;

    UserPatcher* getPatcher();
    void taskFinished(UserPatcher *patcher);
    void setTask(UserPatcher *patcher, QObject *oj, std::function<void (User)> callback);
    void setTask(UserPatcher *patcher, QObject *oj, std::function<void (Group)> callback);
};

inline QMutex mutex_user_patcher_factory;
inline UserPatcherFactory* user_patcher_factory = nullptr;

#endif // USERPATCHERFACTORY_H

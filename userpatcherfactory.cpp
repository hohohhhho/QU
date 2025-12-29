#include "userpatcherfactory.h"
#include <QThread>
#include <QTimer>

UserPatcherFactory::UserPatcherFactory(int max_thread_num, QObject *parent)
    : QObject{parent}, max_thread_num(max_thread_num)
{
    for(int i=0;i<max_thread_num;i++){
        UserPatcher* patcher = new UserPatcher;
        m_available.enqueue(patcher);
    }
}

UserPatcherFactory::~UserPatcherFactory()
{
    if(thread_working.load() > 0){//当前仍有线程在工作则等待10秒
        QThread::sleep(10000);
    }
    qDeleteAll(m_available);//释放所有队列的内存
}

UserPatcher *UserPatcherFactory::getPatcher()
{
    UserPatcher* result = nullptr;
    mutex_available_queue.lock();
    // QMutexLocker locker(&mutex_available_queue);
    if(!m_available.empty()){
        result = m_available.dequeue();
    }
    mutex_available_queue.unlock();
    return result;
}

void UserPatcherFactory::taskFinished(UserPatcher* patcher)
{
    static int num = 0;
    patcher->disconnect();

    //mutex_available_queue.lock();
    //m_available.enqueue(patcher);
    //mutex_available_queue.unlock();
    //mutex_task_queue.lock();
    //if (!m_task_queue.empty()) {
    //    auto task = m_task_queue.dequeue();
    //    mutex_task_queue.unlock();
    //    auto type = task.type;
    //    if (type == OBJ::user) {
    //        patchUser(task.user, false, task.callback_user);
    //    }
    //    else if (type == OBJ::group) {
    //        patchGroup(task.group, false, task.callback_group);
    //    }
    //}
    //else {
    //    mutex_task_queue.unlock();
    //}
    
    
    mutex_task_queue.lock();
    if(!m_task_queue.empty()){//如果任务队列有任务则继续做新的任务

        // qDebug() << "完善信息任务完成" << ++num << "处理任务队列";
        auto task = m_task_queue.dequeue();
        mutex_task_queue.unlock();

        auto type = task.type;
        if(type == OBJ::user){
            setTask(patcher, task.oj, task.callback_user);
            patcher->patchUser(task.user, false);
        }else if(type == OBJ::group){
            setTask(patcher, task.oj, task.callback_group);
            patcher->patchGroup(task.group, false);
        }
    }else{//如果没有任务则加入到空闲队列中
        // qDebug() << "完善信息任务完成" << ++num << "加入空闲队列";
        mutex_task_queue.unlock();

        mutex_available_queue.lock();
        m_available.enqueue(patcher);
        mutex_available_queue.unlock();
        thread_working--;
    }

    mutex_available_queue.lock();
    mutex_task_queue.lock();
    qDebug()<<"m_available size"<<m_available.size()<<"m_task_queue size"<<m_task_queue.size();
    mutex_task_queue.unlock();
    mutex_available_queue.unlock();
}

void UserPatcherFactory::setTask(UserPatcher* patcher, QObject* oj, std::function<void(User)> callback)
{
    QObject* context = new QObject;//临时上下文对象
    connect(patcher, &UserPatcher::userPatchFinished, oj, [=](User user_patched) {
        callback(user_patched);
        taskFinished(patcher);
        context->deleteLater();
    });
   //当对象被删除时，回调信号槽不执行，但是taskFinished需要在线程完成工作后执行
   connect(oj, &QObject::destroyed, context, [=]() {
        //由于接收方对象已经被删除，旧的工作线程已经无效了
        patcher->cleanUp();
        patcher->deleteLater();
        //创建新的工作对象
        UserPatcher* new_patcher = new UserPatcher;
        taskFinished(new_patcher);
        //taskFinished(patcher);
        context->deleteLater();
    });
}

void UserPatcherFactory::setTask(UserPatcher *patcher, QObject *oj, std::function<void (Group)> callback)
{
    QObject* context = new QObject;//临时上下文对象
    connect(patcher, &UserPatcher::groupPatchFinished, oj, [=](Group group_patched) {
        callback(group_patched);
        taskFinished(patcher);
        context->deleteLater();
    });
    //当对象被删除时，回调信号槽不执行，但是taskFinished需要在线程完成工作后执行
    connect(oj, &QObject::destroyed, context, [=]() {
        //由于接收方对象已经被删除，旧的工作线程已经无效了
        patcher->cleanUp();
        patcher->deleteLater();
        //创建新的工作对象
        UserPatcher* new_patcher = new UserPatcher;
        taskFinished(new_patcher);
        //taskFinished(patcher);
        context->deleteLater();
    });
}

void UserPatcherFactory::patchUser(QObject* oj, User user, bool blocking, std::function<void (User)> callback)
{
    // qDebug()<<"申请新任务";
    // mutex_available_queue.lock();
    // mutex_task_queue.lock();
    // qDebug()<<"m_available size"<<m_available.size()<<"m_task_queue size"<<m_task_queue.size();
    // mutex_task_queue.unlock();
    // mutex_available_queue.unlock();

    auto patcher = getPatcher();
    if(!patcher){
        //如果当前没有可用的线程，则加入到任务队列等待其他线程空闲下来
        // qDebug() << "UserPatcherFactory::无空闲线程，加入任务队列";
        mutex_task_queue.lock();
        m_task_queue.enqueue(Task(user, oj, blocking, callback));
        mutex_task_queue.unlock();
        return;
    }
    // qDebug() << "UserPatcherFactory::有空闲线程，接取新的任务";
    thread_working++;
    
    setTask(patcher, oj, callback);

    patcher->patchUser(user, blocking);
}

void UserPatcherFactory::patchGroup(QObject* oj, Group group, bool blocking, std::function<void (Group)> callback)
{
    auto patcher = getPatcher();
    if(!patcher){
        //如果当前没有可用的线程，则加入到任务队列等待其他线程空闲下来
        mutex_task_queue.lock();
        m_task_queue.enqueue(Task(group, oj, blocking, callback));
        mutex_task_queue.unlock();
        return;
    }
    thread_working++;

    setTask(patcher, oj, callback);

    patcher->patchGroup(group, blocking);
}

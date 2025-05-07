// #ifndef ABSTRACTTHREAD_H
// #define ABSTRACTTHREAD_H

// #include <QObject>
// #include <QVariant>

// class AbstractThread : public QObject
// {
//     Q_OBJECT
// public:
//     explicit AbstractThread(QObject *parent = nullptr);
//     ~AbstractThread();


//     // template<class ReturnType>
//     // void execute(std::function<ReturnType()> task)
//     // {
//     //     qRegisterMetaType<ReturnType>(); // 注册返回类型元数据
//     //     QMetaObject::invokeMethod(this,"runTask",Qt::QueuedConnection,Q_ARG(std::function<ReturnType ()>,task));
//     // }
//     template<class ReturnType>
//     void execute(std::function<ReturnType ()> task) {
//         // 将任务包装为 void 类型函数
//         auto wrappedTask = [this, task]() {
//             runTaskInternal<ReturnType>(task);
//         };

//         // 通过类型擦除传递
//         QMetaObject::invokeMethod(this, "handleGenericTask",
//                                   Qt::QueuedConnection,
//                                   Q_ARG(QVariant, QVariant::fromValue(wrappedTask))
//                                   );
//     }
// signals:
//     void threadCompleted(QVariant result);
// private:
//     QThread* m_thread;
//     template<class ReturnType>
//     void runTask(std::function<ReturnType()> task)
//     {
//         ReturnType result=task();
//         emit threadCompleted(QVariant::fromValue(result));
//     }
//     void handleGenericTask(QVariant taskWrapper) {
//         if (taskWrapper.canConvert<std::function<void()>>()) {
//             auto task = taskWrapper.value<std::function<void()>>();
//             task();
//         }
//     }
//     template<class ReturnType>
//     void runTaskInternal(std::function<ReturnType ()> task) {
//         ReturnType result = task();
//         emit threadCompleted(QVariant::fromValue(result));
//     }
// };

// #endif // ABSTRACTTHREAD_H

#ifndef ABSTRACTTHREAD_H
#define ABSTRACTTHREAD_H

#include <QObject>
#include <QThread>
#include <functional>
#include <QVariant>

class AbstractThread : public QObject {
    Q_OBJECT
public:
    explicit AbstractThread(QObject *parent = nullptr);
    ~AbstractThread();

    template<class ReturnType>
    void execute(std::function<ReturnType()> task) {
        // 将任务包装为 void 函数
        auto wrappedTask = [this, task]() {
            ReturnType result = task();
            qDebug()<<"wrappedTask:task return";
            emit threadCompleted(QVariant::fromValue(result));
        };

        // 跨线程提交任务
        qDebug() << "Sending task of type:" << typeid(wrappedTask).name();
        QMetaObject::invokeMethod(this, "handleGenericTask",
                                  Qt::QueuedConnection,
                                  Q_ARG(QVariant, QVariant::fromValue(wrappedTask))
                                  );
    }

signals:
    void threadCompleted(QVariant result);

private slots:
    void handleGenericTask(QVariant taskWrapper) {
        qDebug() << "Received task type:" << taskWrapper.typeName();
        if (taskWrapper.canConvert<std::function<void()>>()) {
            auto task = taskWrapper.value<std::function<void()>>();
            task();
        }else{
            qDebug()<<"taskWrapper.canConvert<std::function<void()>>() = false";
        }
    }

private:
    QThread* m_thread;
};

#endif // ABSTRACTTHREAD_H

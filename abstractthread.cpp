#include "abstractthread.h"

#include <QThread>
#include <QVariant>

AbstractThread::AbstractThread(QObject *parent)
    : QObject{parent}
{
    this->m_thread=new QThread;
    this->moveToThread(m_thread);

    m_thread->start();
}

AbstractThread::~AbstractThread() {
    if (m_thread->isRunning()) {
        m_thread->quit();
        m_thread->wait();
    }
    delete m_thread;
}


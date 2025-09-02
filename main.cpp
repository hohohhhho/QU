#include "loginwidget.h"

#include <QApplication>

Q_DECLARE_METATYPE(std::function<void()>)

int main(int argc, char *argv[])
{
    QApplication::setApplicationVersion("1.3.2");
    // qApp->setQuitOnLastWindowClosed(false);

    qRegisterMetaType<std::function<void()>>("std::function<void()>");
    qRegisterMetaType<QAbstractSocket::SocketError>("QAbstractSocket::SocketError");
    QApplication a(argc, argv);
    LoginWidget w;
    w.show();
    return a.exec();
}

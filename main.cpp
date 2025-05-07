#include "loginwidget.h"

#include <QApplication>

Q_DECLARE_METATYPE(std::function<void()>)

int main(int argc, char *argv[])
{
    qRegisterMetaType<std::function<void()>>("std::function<void()>");
    qRegisterMetaType<QAbstractSocket::SocketError>("QAbstractSocket::SocketError");
    QApplication a(argc, argv);
    LoginWidget w;
    w.show();
    return a.exec();
}

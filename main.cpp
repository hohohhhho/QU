#include "loginwidget.h"

#include <QApplication>
#include <QStyleFactory>

Q_DECLARE_METATYPE(std::function<void()>)

int main(int argc, char *argv[])
{
    // qDebug()<<"available style:"<<QStyleFactory::keys();
    QApplication::setApplicationVersion("1.3.5");
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    QPalette palette;
    palette.setColor(QPalette::Window, QColor(240,240,240));
    palette.setColor(QPalette::WindowText, Qt::black);
    palette.setColor(QPalette::Base, Qt::white);
    palette.setColor(QPalette::Text, Qt::black);
    palette.setColor(QPalette::Button, QColor(240,240,240));
    palette.setColor(QPalette::ButtonText, Qt::black);
    palette.setColor(QPalette::ToolTipBase, QColor(240,240,240));
    palette.setColor(QPalette::ToolTipText, Qt::black);
    QApplication::setPalette(palette);

    qApp->setStyleSheet("QRadioButton{"
                        "font-size:15px;"
                        "color:black;"
                        "}");

    qRegisterMetaType<std::function<void()>>("std::function<void()>");
    qRegisterMetaType<QAbstractSocket::SocketError>("QAbstractSocket::SocketError");
    QApplication a(argc, argv);
    LoginWidget w;
    w.show();
    return a.exec();
}

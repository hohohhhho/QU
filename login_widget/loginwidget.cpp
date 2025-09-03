#include "loginwidget.h"
#include "ui_loginwidget.h"
#include "mainwindow.h"
#include "loadwidget.h"
#include "macro.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QTcpSocket>
#include <QTimer>
#include <QPointer>
#include <QPainter>
#include <QScrollBar>
#include <QButtonGroup>
#include <QThread>
#include <QCryptographicHash>

LoginWidget::LoginWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginWidget)
{
    ui->setupUi(this);

    this->setWindowIcon(QIcon(":/res/login.png"));
    this->setWindowTitle("登录界面");
    const int fixed_size=250;

    ui->widget_login->setFixedSize(fixed_size,fixed_size);
    ui->widget_register->setFixedSize(fixed_size,fixed_size);
    this->setFixedSize(fixed_size+18+2,fixed_size+18+2);
    // this->setAutoFillBackground(true);
    this->setStyleSheet("QScrollArea>QWidget>QWidget{"
                        "background-color:rgba(42,72,160,50);"//(42,72,160,50)
                        "}"
                        "QLineEdit{"
                        "font-size:25px;"
                        "font-family:微软雅黑;"
                        "background-color:white;"
                        "}"
                        "QLineEdit::placeholder{"
                        "font-color:red;"
                        "}"
                        "QPushButton{"
                        "font-size:20px;"
                        "font-family:微软雅黑;"
                        "}");
    ui->label_account->setStyleSheet("QLabel{"
                                     "color:red;"
                                     "}");
    ui->label_password->setStyleSheet("QLabel{"
                                     "color:red;"
                                     "}");
    ui->edit_password->setEchoMode(QLineEdit::Password);
    ui->label_account->setVisible(false);
    ui->label_password->setVisible(false);

    this->animation=nullptr;
    this->dlg_set=new SetDialog(this);
    dlg_set->setWindowTitle("设置");
    dlg_set->setFixedSize(this->size());

    //设置窗口
    {
        static QString temp_host_ip;
        static quint16 temp_host_port;
        static ServerMod temp_server_mod;

        mutex_ip.lockForRead();
        temp_host_ip=hostip;
        temp_host_port=hostport;
        temp_server_mod=server_mod;
        mutex_ip.unlock();
        QButtonGroup* btn_group_connect_mod=new QButtonGroup(this);
        btn_group_connect_mod->addButton(dlg_set->radio_linux);
        btn_group_connect_mod->addButton(dlg_set->radio_windows);
        btn_group_connect_mod->addButton(dlg_set->radio_cloud);
        btn_group_connect_mod->addButton(dlg_set->radio_custom);


        auto reset=[=](){
            if(dlg_set->radio_linux->isChecked()){
                temp_server_mod=ServerMod::Linux;
                dlg_set->edit_ip->setReadOnly(true);
                dlg_set->edit_port->setReadOnly(true);
                dlg_set->edit_ip->setText("192.168.163.137");
                dlg_set->edit_port->setText(QString::number(HOSTPORT));
            }else if(dlg_set->radio_windows->isChecked()){
                temp_server_mod=ServerMod::Windows;
                dlg_set->edit_ip->setReadOnly(true);
                dlg_set->edit_port->setReadOnly(true);
                dlg_set->edit_ip->setText("127.0.0.1");
                dlg_set->edit_port->setText(QString::number(HOSTPORT));
            }else if(dlg_set->radio_cloud->isChecked()){
                temp_server_mod=ServerMod::Cloud;
                dlg_set->edit_ip->setReadOnly(true);
                dlg_set->edit_port->setReadOnly(true);
                dlg_set->edit_ip->setText("8.148.78.104");
                dlg_set->edit_port->setText(QString::number(HOSTPORT));
            }else if(dlg_set->radio_custom->isChecked()){
                temp_server_mod=ServerMod::Custom;
                dlg_set->edit_ip->setReadOnly(false);
                dlg_set->edit_port->setReadOnly(false);
                dlg_set->edit_ip->setText(temp_host_ip);
                dlg_set->edit_port->setText(QString::number(temp_host_port));
            }
        };

        switch (temp_server_mod) {
        case ServerMod::Linux:
            dlg_set->radio_linux->setChecked(true);
            break;
        case ServerMod::Windows:
            dlg_set->radio_windows->setChecked(true);
            break;
        case ServerMod::Cloud:
            dlg_set->radio_cloud->setChecked(true);
            break;
        default:
            dlg_set->radio_custom->setChecked(true);
            break;
        }

        reset();

        connect(btn_group_connect_mod,&QButtonGroup::buttonClicked,this,[=](QAbstractButton* btn){
            Q_UNUSED(btn);
            reset();
        });
        connect(dlg_set->btn_save,&QPushButton::clicked,this,[=](){
            QString text_ip=dlg_set->edit_ip->text();
            QString text_port=dlg_set->edit_port->text();
            mutex_ip.lockForWrite();
            hostip=text_ip;
            hostport=text_port.toUInt();
            server_mod=temp_server_mod;
            mutex_ip.unlock();
            dlg_set->close();
        });
        connect(dlg_set->btn_cancel,&QPushButton::clicked,this,[=](){
            dlg_set->close();
            // dlg_set->edit_ip->setText(temp_host_ip);
            // dlg_set->edit_port->setText(QString::number(temp_host_port));
        });
        connect(dlg_set->box,&QCheckBox::clicked,this,[=](bool isChecked){
            if(isChecked){
                this->real_time_detection=true;
            }else{
                this->real_time_detection=false;
            }
        });
        connect(ui->btn_set,&QPushButton::clicked,this,[=](){
            dlg_set->show();
        });
        connect(ui->btn_set_2,&QPushButton::clicked,this,[=](){
            dlg_set->show();
        });
    }

    // QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL","query_same");
    // patchDatabase(db);

    connect(ui->btn_toregister,&QPushButton::clicked,this,[=](){
        if(!animation){
            animation=new QVariantAnimation(this);
            animation->setDuration(300);
            animation->setEasingCurve(QEasingCurve::Linear);
            animation->setStartValue(0);
            animation->setEndValue(ui->scrollArea->horizontalScrollBar()->maximum());
            connect(animation,&QVariantAnimation::valueChanged,this,[=](const QVariant& value){
                ui->scrollArea->horizontalScrollBar()->setValue(value.toInt());
                update();
            });
            connect(animation,&QVariantAnimation::finished,this,[=](){
                this->setWindowTitle("注册界面");
                delete animation;
                animation=nullptr;
            });
            animation->start();
        }
    });
    connect(ui->btn_tologin,&QPushButton::clicked,this,[=](){
        if(!animation){
            animation=new QVariantAnimation(this);
            animation->setDuration(300);
            animation->setEasingCurve(QEasingCurve::Linear);
            animation->setStartValue(ui->scrollArea->horizontalScrollBar()->maximum());
            animation->setEndValue(0);
            connect(animation,&QVariantAnimation::valueChanged,this,[=](const QVariant& value){
                ui->scrollArea->horizontalScrollBar()->setValue(value.toInt());
                update();
            });
            connect(animation,&QVariantAnimation::finished,this,[=](){
                this->setWindowTitle("登录界面");
                delete animation;
                animation=nullptr;
            });
            animation->start();
        }
    });




    connect(ui->edit_account_register,&QLineEdit::textEdited,this,[=](const QString& text){
        auto endFunc = [=](QString _tip){
            ui->label_account->setText(_tip);
            ui->label_account->show();
        };
        if(text.isEmpty()){
            endFunc("账号不能为空");
            return;
        }
        for(const QChar& c:text){
            if( c<'0' || ( c>'9' && c<'A' ) || (c>'Z' && c<'a' && c!='_') || c>'z'){
                endFunc("只能使用大小写字母和数字");
                return;
            }
        }

        if(real_time_detection){
            QString tip;
            QTcpSocket* socket_same=new QTcpSocket;
            QEventLoop* loop=new QEventLoop;
            auto finish = [=](){
                loop->quit();
                loop->deleteLater();
                socket_same->deleteLater();
            };
            connect(socket_same,&QTcpSocket::readyRead,socket_same,[=,&tip]()mutable{
                QString data=readSocket(socket_same);
                QStringList list=data.split('/');
                if(list.size()<2){
                    qDebug()<<"socket_same list.size()"<<list.size();
                    return;
                }
                if(list[1]=="s"){
                    tip="账号已存在";
                }else if(list[1]=="f"){
                    tip="账号可用";
                }else{
                    qDebug()<<"data"<<data;
                }
                finish();
            });
            connect(socket_same,&QTcpSocket::errorOccurred,socket_same,[=](QAbstractSocket::SocketError error) {
                qDebug() <<"Socket Error:"<< error;
                finish();
            });
            socket_same->connectToHost(QHostAddress(hostip),hostport);
            QByteArray content=QString("/m/same_account*%1*").arg(text).toUtf8();
            if(socket_same->state()==QTcpSocket::ConnectingState && !socket_same->waitForConnected(5000)){
                tip="连接超时";
                real_time_detection = false;//将自动查询账户功能关闭
                finish();
            }else{
                sendMsg(socket_same,content);
            }
            loop->exec();
            // qDebug()<<"tip"<<tip;
            endFunc(tip);
        }
        if(ui->label_account->text().isEmpty()){
            ui->label_account->setVisible(false);
        }
    });

    connect(ui->edit_password_register,&QLineEdit::textEdited,this,[=](const QString& text){
        QString tip("密码最好包含");
        bool num=false;
        bool character=false;
        bool Character=false;
        for(const QChar& c:text){
            if(!num && '0'<=c && c<='9'){
                num=true;
            }else if(!character && 'a'<=c && c<='z'){
                character=true;
            }else if(!Character && 'A'<=c && c<='Z'){
                Character=true;
            }
        }
        if(!num){
            tip.append("数字");
            if(!character|| !Character){
                tip.append("、");
            }
        }
        if(!character||!Character){
            if(!Character){
                tip.append("大");
            }
            if(!character){
                tip.append("小");
            }
            tip.append("写字母");
        }
        ui->label_password->setText(tip);
        bool show=!num+!character+!Character;
        // qDebug()<<"num"<<num<<"character"<<character<<"Character"<<Character;
        // qDebug()<<"show"<<show;
        ui->label_password->setVisible(show);
    });

    connect(ui->btn_password,&QPushButton::clicked,this,[=](){
        if(ui->btn_password->isChecked()==false){
            ui->edit_password->setEchoMode(QLineEdit::Password);
        }else{
            ui->edit_password->setEchoMode(QLineEdit::Normal);
        }
    });
    connect(ui->btn_password_register,&QPushButton::clicked,this,[=](){
        if(ui->btn_password_register->isChecked()==false){
            ui->edit_password_register->setEchoMode(QLineEdit::Password);
        }else{
            ui->edit_password_register->setEchoMode(QLineEdit::Normal);
        }
    });

    connect(ui->btn_register,&QPushButton::clicked,this,[=](){
        QString account=ui->edit_account_register->text();
        QString password=ui->edit_password_register->text();
        QByteArray password_hash = calculateHash(password.toUtf8());
        if(account==""||password==""){
            QMessageBox::information(this,"提示","账号或密码不能为空");
            return;
        }
        for(QChar& c:account+password){
            if( c<'0' || ( c>'9' && c<'A' ) || (c>'Z' && c<'a' && c!='_') || c>'z'){
                QMessageBox::information(this,"提示","只能使用大小写字母,下划线和数字");
                return;
            }
        }
        QTcpSocket* socket=new QTcpSocket;
        QEventLoop* loop=new QEventLoop;
        connect(socket,&QTcpSocket::readyRead,socket,[=](){
            QString data=readSocket(socket);
            QStringList list=data.split('/');
            qDebug()<<"注册中:list"<<list;
            if(list.size()<2){
                return;
            }
            if(list[1]=="s"){
                int id=list[2].toInt();

                this->close();
                QMessageBox::information(this,"提示","注册成功！");
                MainWindow* w=new MainWindow;
                LoadWidget* l=new LoadWidget;
                l->show();
                QTimer::singleShot(50,this,[=](){
                    connect(w,&MainWindow::initProgress,l,&LoadWidget::changeProgress);
                    connect(l,&LoadWidget::finished,this,[=](){
                        w->show();
                        l->deleteLater();
                    });
                    w->init(id,account,password_hash);
                });
            }else if(list[1]=="f"){
                QMessageBox::warning(this,"提示","注册失败:"+data.split("/").last());
            }else{
                qDebug()<<"data"<<data;
            }
            loop->quit();
            loop->deleteLater();
        });
        connect(socket,&QTcpSocket::errorOccurred,socket,[loop](QAbstractSocket::SocketError error) {
            qDebug() <<"Socket Error:"<< error;
            loop->quit();
            loop->deleteLater();
        });
        socket->connectToHost(QHostAddress(hostip),hostport);
        QByteArray content=QString("/m/register*%1**").arg(account).toUtf8() + password_hash +'*';

        if(socket->state()==QTcpSocket::ConnectingState && !socket->waitForConnected(5000)){
            QMessageBox::warning(this,"提示","连接超时");
        }else{
            sendMsg(socket,content);
        }
        loop->exec();
        socket->deleteLater();
    });

    connect(ui->btn_login,&QPushButton::clicked,this,[=](){
        QString account=ui->edit_account->text();
        QString password=ui->edit_password->text();
        QByteArray password_hash = calculateHash(password.toUtf8());
        if(account==""||password==""){
            QMessageBox::information(this,"提示","账号或密码不能为空");
            return;
        }
        for(QChar& c:account+password){
            if( c<'0' || ( c>'9' && c<'A' ) || (c>'Z' && c<'a' && c!='_') || c>'z'){
                QMessageBox::information(this,"提示","只能使用大小写字母,下划线和数字");
                return;
            }
        }

        QTcpSocket* socket=new QTcpSocket;
        QEventLoop* loop=new QEventLoop(this);
        auto finish = [=](){
            loop->quit();
            loop->deleteLater();
            socket->deleteLater();
        };
        connect(socket,&QTcpSocket::readyRead,socket,[=](){
            QString data=QString::fromUtf8(readSocket(socket));
            QStringList list=data.split('/');
            if(list.size()<2){
                qDebug()<<"list"<<list;
                return;
            }
            if(list[1]=="s"){
                int id=list[2].toInt();

                if(id>0){
                    qDebug()<<"id:"<<id;
                    this->close();
                    MainWindow* w=new MainWindow;
                    LoadWidget* l=new LoadWidget;
                    l->show();
                    QTimer::singleShot(50,this,[=](){
                        connect(w,&MainWindow::initProgress,l,&LoadWidget::changeProgress);
                        connect(l,&LoadWidget::finished,this,[=](){
                            w->show();
                            l->deleteLater();
                        });
                        w->init(id,account,password_hash);
                    });
                }
            }else if(list[1]=="f"){
                QMessageBox::warning(this,"提示","登录失败\n账号或密码错误");
            }else{
                qDebug()<<"意外的list"<<list;
            }
            finish();
        });
        connect(socket,&QTcpSocket::errorOccurred,socket,[=](QAbstractSocket::SocketError error) {
            qDebug() <<"Socket Error:"<< error;
            QMessageBox::warning(this,"提示","连接服务器失败");
            finish();
        });
        socket->connectToHost(QHostAddress(hostip),hostport);
        qDebug()<<"login-hostip"<<hostip<<"hostport"<<hostport;
        QByteArray content=QString("/m/login*%1**").arg(account).toUtf8() + password_hash +'*';
        if(socket->state()==QTcpSocket::ConnectingState && !socket->waitForConnected(5000)){
            finish();
            QMessageBox::warning(this,"提示","连接超时");
        }else{
            sendMsg(socket,content);
        }

        loop->exec();
    });
}

LoginWidget::~LoginWidget()
{
    QSqlDatabase::removeDatabase("query_same");
    delete ui;
}

void LoginWidget::paintEvent(QPaintEvent *ev)
{
    Q_UNUSED(ev);
    QPainter painter(this);
    painter.fillRect(this->rect(),QColor(42,72,160,80));
}

QByteArray LoginWidget::readSocket(QTcpSocket *socket)
{
    static QHash<QTcpSocket*, quint32> expectedSizes;  // 跟踪每个socket的待接收长度

    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_15);

    // // 阶段1：读取长度头
    // if (!expectedSizes.contains(socket)) {
    //     if (socket->bytesAvailable() < static_cast<qint64>(sizeof(quint32)))
    //         return QByteArray();  // 数据不足，等待下次

    //     in >> expectedSizes[socket];  // 读取8字节长度头
    // }

    // // 阶段2：读取内容
    // if (socket->bytesAvailable() < static_cast<qint32>(expectedSizes[socket]))
    //     return QByteArray();  // 数据不足，等待下次

    QByteArray content;
    in>>content;

    expectedSizes.remove(socket);
    return content;
}

void LoginWidget::sendMsg(QTcpSocket* socket,const QByteArray &msg)
{
    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_15);
    out<<msg;

    socket->write(buffer);
}

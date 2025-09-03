#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "userdetail.h"
#include "chatwidget.h"
#include "userpatcher.h"
#include "camerawidget.h"
#include "groupdetail.h"
#include "appupdater.h"

#include <QBuffer>
#include <QFileDialog>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QResizeEvent>
#include <QButtonGroup>
#include <QPainter>
#include <LoginWidget.h>
#include <QTimer>
#include <QMovie>
#include <QThread>
#include <QUdpSocket>
#include <QVersionNumber>
#include <QComboBox>

QMutex mutex_chat;
QMap<int,QList<Message>> map_userchat_history={};
QMap<int,QList<Message>> map_userchat_unread={};
QMap<int,QList<Message>> map_groupchat_history={};
QMap<int,QList<Message>> map_groupchat_unread={};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{}

MainWindow::~MainWindow()
{
    qDebug()<<"析构";
    delete ui;
}

void MainWindow::init(int id,QString account,QString password)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/res/chat.png"));
    this->setWindowTitle("QU");

    if(id<1){
        QMessageBox::critical(this,"提示","id非法,请重试");
        return;
    }
    this->m_user.id=id;
    this->m_account=account;
    this->m_password=password;
    this->m_socket_tcp=new QTcpSocket(this);
    this->m_socket_udp=new QUdpSocket(this);
    this->btn_group_main=new QButtonGroup(this);
    this->btn_group_set=new QButtonGroup(this);
    this->label_tip=new RoundLabel;
    this->label_wait=new QLabel;
    this->aniamtion_tip=new QVariantAnimation(this);
    this->sound_msg=new QSoundEffect(this);
    this->chatwidget=nullptr;
    this->vl_user_detail=new QVBoxLayout(ui->page_user_detail);
    this->vl_group_detail=new QVBoxLayout(ui->page_group_detail);
    this->vl_chatwith=new QVBoxLayout(ui->page_chatwith);
    this->m_camera_widget=nullptr;
    // this->timer_msg_clear = new QTimer(this);

    this->setStyleSheet("*{"
                        "font-size:20px;"
                        "}");


    ui->btn_friend_request->setNotSquare();
    ui->stackedWidget_main->setCurrentWidget(ui->page_chat);
    ui->stacked_set->setCurrentWidget(ui->page_set_null);
    label_tip->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    label_tip->setAttribute(Qt::WA_TranslucentBackground);
    label_tip->setFixedHeight(50);
    label_tip->setMinimumWidth(200);
    label_tip->setAlignment(Qt::AlignCenter);
    label_tip->setStyleSheet("QLabel{"
                             "font-size:20px;"
                             "font-family:微软雅黑;"
                             "}");
                             // "background-color:rgba(42,72,160,0.3);"
                             // "background-color:white;"
                             // "border:1px;"
                             // "border-top-color:rgba(255,255,255,0.2);"
                             // "border-left-color:rgba(255,255,255,0.2);"
                             // "border-right-color:rgba(0,0,0,0.6);"
                             // "border-bottom-color:rgba(0,0,0,0.6);"
                             // "border-radius:25px;"
    label_wait->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    label_wait->setAttribute(Qt::WA_TranslucentBackground);
    label_wait->setStyleSheet("QLabel{"
                              "border:none;"
                              "}");
    label_wait->setFixedSize(64,64);
    label_wait->setText("加载中");
    QMovie* movie=new QMovie(this);
    movie->setFileName(":/res/loading2.gif");
    movie->setScaledSize(QSize(64,64));
    movie->setSpeed(200);
    movie->start();
    label_wait->setMovie(movie);
    this->sound_msg->setSource(QUrl("qrc:/res/sound/msg.wav"));
    sound_msg->setVolume(0.5);

    aniamtion_tip->setDuration(300);
    aniamtion_tip->setEasingCurve(QEasingCurve::Linear);
    this->aniamtion_tip->setStartValue(0);
    this->aniamtion_tip->setEndValue(60);
    connect(aniamtion_tip,&QVariantAnimation::valueChanged,this,[=](const QVariant& value){
        label_tip->move(label_tip->x(),value.toInt());
    });
    connect(aniamtion_tip,&QVariantAnimation::finished,this,[=](){
        auto handle=[=](){
            if(queue_tip.isEmpty()){
                label_tip->setVisible(false);
                label_tip->move(label_tip->x(),this->mapToGlobal(QPoint(0,0)).y());
            }else{
                label_tip->setText(queue_tip.dequeue());
                adjustTipPos();
                label_tip->show();
                aniamtion_tip->start();
            }
        };
        if(!queue_tip.isEmpty()){
            handle();
        }
        else{
            QTimer::singleShot(1000,this,[=](){
                handle();
            });
        }
    });

    btn_group_main->addButton(ui->btn_chat);
    btn_group_main->addButton(ui->btn_friend);
    btn_group_main->addButton(ui->btn_group);
    btn_group_main->addButton(ui->btn_set);
    btn_group_main->addButton(ui->btn_test);
    connect(ui->btn_chat,&QPushButton::clicked,this,[=](bool isChecked){
        if(isChecked){
            ui->btn_chat->setChecked(true);
            ui->stackedWidget_main->setCurrentWidget(ui->page_chat);
        }
    });
    connect(ui->btn_friend,&QPushButton::clicked,this,[=](bool isChecked){
        if(isChecked){
            ui->btn_friend->setChecked(true);
            ui->stackedWidget_main->setCurrentWidget(ui->page_friend);
        }
    });
    connect(ui->btn_group,&QPushButton::clicked,this,[=](bool isChecked){
        if(isChecked){
            ui->btn_group->setChecked(true);
            ui->stackedWidget_main->setCurrentWidget(ui->page_group);
        }
    });
    connect(ui->btn_set,&QPushButton::clicked,this,[=](bool isChecked){
        if(isChecked){
            ui->btn_set->setChecked(true);
            ui->stackedWidget_main->setCurrentWidget(ui->page_set);
        }
    });
    connect(ui->btn_test,&QPushButton::clicked,this,[=](bool isChecked){
        if(isChecked){
            ui->btn_test->setChecked(true);
            ui->stackedWidget_main->setCurrentWidget(ui->page_test);
        }
    });

    //设置页面
    {
        btn_group_set->addButton(ui->btn_custom);
        btn_group_set->addButton(ui->btn_connect);
        btn_group_set->addButton(ui->btn_msg);
        btn_group_set->addButton(ui->btn_account);
        btn_group_set->addButton(ui->btn_video_call);
        btn_group_set->addButton(ui->btn_about);
        connect(btn_group_set,&QButtonGroup::buttonClicked,this,[=](QAbstractButton* btn){
            if(btn==ui->btn_custom){
                ui->stacked_set->setCurrentWidget(ui->page_set_custom);
            }else if(btn==ui->btn_connect){
                ui->stacked_set->setCurrentWidget(ui->page_set_connect);
            }else if(btn==ui->btn_msg){
                ui->stacked_set->setCurrentWidget(ui->page_set_msg);
            }else if(btn==ui->btn_account){
                ui->stacked_set->setCurrentWidget(ui->page_set_account);
            }else if(btn==ui->btn_video_call){
                ui->stacked_set->setCurrentWidget(ui->page_set_video_call);
            }else if(btn==ui->btn_about){
                QString current_version = QApplication::applicationVersion();
                QString latest_version;
                newSql("/@",[=](QStringList& list)mutable{
                    latest_version = list[2];
                    ui->label_latest_version->setText("最新版本:" + latest_version);
                    if(current_version == latest_version){
                        ui->btn_update->setEnabled(false);
                    }
                });
                ui->label_current_version->setText("当前版本:" + current_version);
                ui->stacked_set->setCurrentWidget(ui->page_set_about);
            }
        });

        emit initProgress(0.1f,"加载设置界面");

        //服务器设置页面
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
            btn_group_connect_mod->addButton(ui->radio_linux);
            btn_group_connect_mod->addButton(ui->radio_windows);
            btn_group_connect_mod->addButton(ui->radio_cloud);
            btn_group_connect_mod->addButton(ui->radio_custom);


            auto reset=[=](){
                if(ui->radio_linux->isChecked()){
                    temp_server_mod=ServerMod::Linux;
                    ui->edit_ip->setReadOnly(true);
                    ui->edit_port->setReadOnly(true);
                    ui->edit_ip->setText(LINUXIP);
                    ui->edit_port->setText(QString::number(HOSTPORT));
                }else if(ui->radio_windows->isChecked()){
                    temp_server_mod=ServerMod::Windows;
                    ui->edit_ip->setReadOnly(true);
                    ui->edit_port->setReadOnly(true);
                    ui->edit_ip->setText(WINDOWSIP);
                    ui->edit_port->setText(QString::number(HOSTPORT));
                }else if(ui->radio_cloud->isChecked()){
                    temp_server_mod=ServerMod::Cloud;
                    ui->edit_ip->setReadOnly(true);
                    ui->edit_port->setReadOnly(true);
                }else if(ui->radio_custom->isChecked()){
                    temp_server_mod=ServerMod::Custom;
                    ui->edit_ip->setReadOnly(false);
                    ui->edit_port->setReadOnly(false);
                    ui->edit_ip->setText(temp_host_ip);
                    ui->edit_port->setText(QString::number(temp_host_port));
                }
            };

            switch (temp_server_mod) {
            case ServerMod::Linux:
                ui->radio_linux->setChecked(true);
                break;
            case ServerMod::Windows:
                ui->radio_windows->setChecked(true);
                break;
            case ServerMod::Cloud:
                ui->radio_cloud->setChecked(true);
                break;
            default:
                ui->radio_custom->setChecked(true);
                break;
            }
            reset();

            auto relogin=[=]()->int{
                int id_result=-1;
                auto sqlFunc=[&id_result](QStringList list)mutable{
                    id_result=list[2].toInt();
                };
                QByteArray content=QString("/m/login*%1**%2*").arg(m_account,m_password).toUtf8();
                newSql(content,sqlFunc);
                return id_result;
            };

            connect(btn_group_connect_mod,&QButtonGroup::buttonClicked,this,[=](QAbstractButton* btn){
                Q_UNUSED(btn);
                reset();
            });
            connect(ui->btn_connect_save,&QPushButton::clicked,this,[=](){
                QString text_ip=ui->edit_ip->text();
                QString text_port=ui->edit_port->text();
                mutex_ip.lockForWrite();
                hostip=text_ip;
                hostport=text_port.toUInt();
                server_mod=temp_server_mod;
                mutex_ip.unlock();
            });
            connect(ui->btn_connect_reset,&QPushButton::clicked,this,[=](){
                ui->edit_ip->setText(temp_host_ip);
                ui->edit_port->setText(QString::number(temp_host_port));
            });
            connect(ui->btn_connect_relogin,&QPushButton::clicked,this,[=](){
                emit ui->btn_connect_save->clicked();
                int new_id=relogin();
                if(new_id>1){
                    init(new_id,m_account,m_password);
                }else{
                    showTip("重登录失败");
                }
            });
            connect(ui->btn_connect_restart,&QPushButton::clicked,this,[=](){
                emit ui->btn_connect_save->clicked();
                int new_id=relogin();
                if(new_id>1){
                    MainWindow* w=new MainWindow();
                    w->init(new_id,m_account,m_password);
                    w->show();
                    this->deleteLater();
                }else{
                    showTip("账号或密码错误");
                }
            });
        }

        //账户安全设置页面
        {
            connect(ui->radio_seek_by_noway,&QRadioButton::clicked,this,[=](bool isChecked){
                bool action=!isChecked;
                ui->radio_seek_by_id->setChecked(action);
                ui->radio_seek_by_nickname->setChecked(action);
                ui->radio_seek_by_rand->setChecked(action);
            });
            connect(ui->btn_update_password,&QPushButton::clicked,this,[=](){
                bool passed=false;//先填密码，密码对了才能改
                QDialog* dlg=new QDialog(this);
                QHBoxLayout* hl=new QHBoxLayout(dlg);
                QLineEdit* edit=new QLineEdit("",dlg);
                edit->setPlaceholderText("填写旧密码");
                QPushButton* btn=new QPushButton("确定",dlg);
                connect(btn,&QPushButton::clicked,this,[=]()mutable{
                    if(passed){
                        QString new_password=edit->text();
                        if(new_password.isEmpty()){
                            showTip("密码不能为空");
                            return;
                        }
                        if(new_password==m_password){
                            showTip("新密码不能与旧密码相同");
                            return;
                        }
                        for(QChar& c:new_password){
                            if( c<'0' || ( c>'9' && c<'A' ) || (c>'Z' && c<'a' && c!='_') || c>'z'){
                                showTip("只能使用大小写字母和数字");
                                return;
                            }
                        }

                        auto sqlFunc=[=](QStringList list){
                            Q_UNUSED(list);
                            dlg->close();
                            showTip("密码保存成功");
                        };
                        QByteArray content=QString("/m/update_password*%1**%2*").arg(new_password).arg(m_user.id).toUtf8();
                        newSql(content,sqlFunc,[=]{
                            showTip("操作失败");
                        });
                        this->m_password=new_password;
                    }else if(edit->text()==m_password){
                        passed=true;
                        edit->clear();
                        edit->setPlaceholderText("填写新密码");
                    }else{
                        QMessageBox::information(this,"提示","密码错误");
                        return;
                    }
                });
                hl->addWidget(edit);
                hl->addWidget(btn);
                dlg->exec();
            });
            connect(ui->btn_logout,&QPushButton::clicked,this,[=](){
                LoginWidget* l=new LoginWidget;
                l->show();
                this->deleteLater();
            });
        }

        //关于软件设置页面
        {
            connect(ui->btn_update,&QPushButton::clicked,this,[=](){

                QDialog* dlg=new QDialog(this);
                QHBoxLayout* hl=new QHBoxLayout(dlg);
                QLineEdit* edit=new QLineEdit("",dlg);
                QPushButton* btn_choose=new QPushButton("选择",dlg);
                QComboBox* box = new QComboBox(dlg);
                QPushButton* btn_confirm=new QPushButton("下载",dlg);
                dlg->setWindowTitle("选择");
                dlg->setAttribute(Qt::WA_DeleteOnClose);
                edit->setPlaceholderText("输入安装地址");

                QString current_path = QApplication::applicationDirPath();
                QDir dir(current_path);
                dir.cdUp();
                current_path = dir.absolutePath();

                edit->setText(current_path);
                QStringList list = {"Windows","Linux","macOS"};
                box->addItems(list);
                hl->addWidget(edit,8);
                hl->addWidget(btn_choose,2);
                hl->addWidget(box,3);
                hl->addWidget(btn_confirm,3);
                connect(btn_choose,&QPushButton::clicked,this,[=]()mutable{
                    QString path = QFileDialog::getExistingDirectory(dlg,"",current_path);
                    edit->setText(path);
                });
                connect(btn_confirm,&QPushButton::clicked,this,[=]()mutable{
                    QString path = edit->text();
                    if(!QDir(path).exists()){
                        showTip("请输入有效地址");
                        return;
                    }
                    AppUpdater* updater = new AppUpdater(this, box->currentText());
                    dlg->close();
                    updater->getUpdate(path);
                });
                dlg->exec();
            });
        }
    }

    // connect(timer_msg_clear,&QTimer::timeout,this,&MainWindow::handleSocket);
    // timer_msg_clear->start(5000);

    emit initProgress(0.2f,"连接至服务器");

    m_socket_tcp->connectToHost(QHostAddress(hostip),hostport);
    connect(this->m_socket_tcp,&QTcpSocket::readyRead,this,&MainWindow::handleSocket);
    m_socket_udp->bind(7788);
    connect(this->m_socket_udp,&QUdpSocket::readyRead,this,[=](){
        QByteArray data;
        data.resize(m_socket_udp->pendingDatagramSize());
        m_socket_udp->readDatagram(data.data(),data.size());
        qDebug()<<"收到udp消息大小"<<data.size();
        //处理数据报
        QString type = handleDataHead(data);
        if(type == 'i'){
            if(m_camera_widget){
                QImage image = QImage::fromData(data);
                m_camera_widget->setImage(image);
            }
        }
    });


    connect(ui->btn,&QPushButton::clicked,this,[=](){
        sendMsg(id,ui->edit->text());
    });

    connect(ui->btn_user,&QPushButton::clicked,this,[=](){
        // ui->btn_friend->setChecked(true);
        emit ui->btn_friend->clicked(true);
        // emit btn_group_main->buttonClicked(ui->btn_friend);
        addUserDetailWidget(m_user);
    });
    connect(ui->edit_seek_friend,&QLineEdit::returnPressed,this,[=](){
        emit ui->btn_seek_friend->clicked();
    });
    connect(ui->btn_seek_friend,&QPushButton::clicked,this,[=](){
        int id_f=ui->edit_seek_friend->text().toInt();
        if(id_f>0){
            User user;
            user.id=id_f;
            addUserDetailWidget(user);
        }else{
            showTip("未找到用户");
        }
    });
    connect(ui->btn_friend_request,&QPushButton::clicked,this,[=](){
        ui->stackedWidget_friend->setCurrentWidget(ui->page_friend_request);
    });
    connect(ui->edit_seek_group,&QLineEdit::returnPressed,this,[=](){
        emit ui->btn_seek_group->clicked();
    });
    connect(ui->btn_seek_group,&QPushButton::clicked,this,[=](){
        int id_f = ui->edit_seek_group->text().toInt();
        if(id_f>0){
            Group group;
            group.id=id_f;
            addGroupDetailWidget(group);
        }else{
            showTip("未找到群聊");
        }
    });
    connect(ui->btn_create_group,&QPushButton::clicked,this,[=](){
        createGroup();
    });

    QString login_cookie=QString("/l*%1*").arg(id);
    // login_cookie=QString("*%1*").arg(login_cookie.size())+login_cookie;
    QByteArray buffer;
    QDataStream out(&buffer,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_15);
    out<<login_cookie.toUtf8();
    m_socket_tcp->write(buffer);

    emit initProgress(0.3f,"初始化用户信息");

    UserPatcher* userPatcher=new UserPatcher;
    connect(userPatcher,&UserPatcher::userPatchFinished,this,[=](User user_patched){
        m_user = user_patched;
        ui->btn_user->setToolTip(m_user.nickname);
        ui->btn_user->setIcon(m_user.icon);
        userPatcher->cleanUp();
        userPatcher->deleteLater();
    });
    userPatcher->patchUser(m_user,true);


    emit initProgress(0.4f,"加载好友列表");
    qreal progress=0.4f;//当前进度
    //加载好友列表
    {
        // int sum=0;//好友数量
        // QString text("加载好友列表:%1/%2");
        // int num_dealed=0;//已加载的好友数量
        // qreal per_one=0.1f;//每加载完成一个好友信息推进的进度
        // auto func_friend_num=[&](QStringList& list)mutable{
        //     if(list.size()>=3){
        //         sum=list[2].toInt();
        //         per_one=(0.9f-progress)/sum;
        //         emit initProgress(progress+ num_dealed*per_one ,text.arg(num_dealed).arg(sum));
        //     }else{
        //         qDebug()<<"func_friend_num error list"<<list;
        //     }
        // };
        // QString sql=QString("/m/num_friends*%1*").arg(m_user.id);
        // newSql(sql.toUtf8(),func_friend_num);
        // if(sum!=0){

        // }
        QString sql=QString("/m/load_friends*%1*").arg(m_user.id);
        newSql(sql.toUtf8(),[=,&progress](QStringList& list){
            int sum = list.size()-2;//好友总数量
            qreal per_one = 0.25f/sum;//每加载好一个好友增加的进度

            for(int i=2;i<list.size();i++){
                User user_friend;
                user_friend.id=list[i].toInt();
                addFriend(user_friend,false);

                progress += per_one;
                emit initProgress(progress,QString("加载好友列表%1/%2").arg(i-1).arg(sum));
            }
            updateFriendList();
        });
    }
    emit initProgress(progress,"加载群聊列表");
    //加载群聊
    {
        QString sql = QString("/m/load_groups*%1*").arg(m_user.id);
        newSql(sql.toUtf8(),[=,&progress](QStringList& list){
            int sum = list.size()-2;//加入的群聊总数量
            qreal per_one = 0.25f/sum;//每加载好一个群聊增加的进度

            for(int i=2; i<list.size(); i++){
                Group group;
                group.id=list[i].toInt();
                addGroup(group,false);

                progress += per_one;
                emit initProgress(progress,QString("加载群聊列表%1/%2").arg(i-1).arg(sum));
            }
            updateGroupList();
        });
    }
    emit initProgress(1.0f,"初始化完成");
    QTimer::singleShot(50,this,[=](){
        showTip("欢迎!");
    });
}

void MainWindow::paintEvent(QPaintEvent *ev)
{
    Q_UNUSED(ev);
    QPainter painter(this);
    painter.fillRect(this->rect(),QColor(42,72,160,30));
}

void MainWindow::resizeEvent(QResizeEvent *ev)
{
    Q_UNUSED(ev);
    adjustPreviewButtonSize();
    adjustTipPos();
}

void MainWindow::moveEvent(QMoveEvent *ev)
{
    QPoint dpos=ev->pos()-ev->oldPos();
    adjustTipPos(dpos);
}

void MainWindow::handleSocket()
{
    while(m_socket_tcp->bytesAvailable() > 0){
        QByteArray content = readSocket(m_socket_tcp);
        if(content!="failed"){
            readMsg(content);//处理读到的信息
        }else{
            qDebug()<<"handleSocket:failed";
            return ;
        }
    }
}

void MainWindow::readUdpMsg(const QByteArray &msg)
{

}

void MainWindow::sendMsg(int id_receiver, const QString &msg,const QChar& style_head)
{
    QByteArray buffer;//临时数据存储
    QDataStream out(&buffer,QIODevice::WriteOnly);//创建数据流写入buffer
    out.setVersion(QDataStream::Qt_5_15);
    QByteArray packet=QString("/%1*%2**%3*%4").arg(style_head).arg(id_receiver).arg(m_user.id).arg(msg).toUtf8();
    out<<packet;
    m_socket_tcp->write(buffer);
}

void MainWindow::sendFile(int id_receiver, const QByteArray &data, const QChar &style_head)
{
    QByteArray buffer;//临时数据存储
    QDataStream out(&buffer,QIODevice::WriteOnly);//创建数据流写入buffer
    out.setVersion(QDataStream::Qt_5_15);
    QByteArray packet=QString("/%1*%2**%3*").arg(style_head).arg(id_receiver).arg(m_user.id).toUtf8()+data;
    out<<packet;
    m_socket_tcp->write(buffer);
}

void MainWindow::sendVideoOverMsg(int id_receiver, const QTime &time)
{
    if(!m_camera_widget){
        return;
    }
    if(m_camera_widget->getIsCaller()){

        QString s_time = time.toString("hh:mm:ss");
        QString text = QString("视频通话已结束[%1]").arg(s_time);
        chatwidget->addMsg(text.toUtf8(),true);
        sendMsg(id_receiver , text , 's');
    }
}

void MainWindow::showTip(const QString &tip)
{
    queue_tip.append(tip);
    if(label_tip->isVisible()){
        return;
    }else{
        label_tip->setText(queue_tip.dequeue());
        adjustTipPos();
        label_tip->show();
        aniamtion_tip->start();
    }
}

void MainWindow::adjustTipPos(QPoint dpos)
{
    label_tip->adjustSize();
    this->label_tip->move(QPoint(this->mapToGlobal( QPoint( (width()-label_tip->width() )/2 , 0 )).x(),0) + dpos);

    this->label_wait->move(this->mapToGlobal(rect().center())-QPoint(label_wait->width()/2,label_wait->height()/2));
    // this->aniamtion_tip->setStartValue(label_tip->y());
    // this->aniamtion_tip->setEndValue(label_tip->y()+60);
    // if(new_pos!=this->mapToGlobal(QPoint(0,0))){

    // }
}

// QByteArray MainWindow::readSocket(QTcpSocket *socket)
// {
//     QByteArray content;
//     QDataStream in(socket);
//     in.setVersion(QDataStream::Qt_5_15);
//     in>>content;

//     return content;
// }

QByteArray MainWindow::readSocket(QTcpSocket *socket)
{
    static QByteArray buffer;
    buffer += socket->readAll();

    QByteArray content;
    QDataStream in(&buffer,QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_5_15);

    in.startTransaction();
    in>>content;
    if(in.commitTransaction()){
        buffer = buffer.mid(in.device()->pos());
        return content;
    }else{
        if (in.status() == QDataStream::ReadPastEnd) {
            // qDebug()<<"正常等待更多数据";
        }else if (in.status() == QDataStream::Ok) {
            qDebug()<<"事务为空";
        }else {
            //发生错误，回滚
            in.rollbackTransaction();
        }
        return "failed";
    }
}

void MainWindow::readMsg(const QByteArray &msg)
{
    if(msg.size()<1024){
        qDebug()<<"readMsg msg"<<msg;
    }else{
        qDebug()<<"readMsg msg size"<<msg.size();
    }

    if(msg.isEmpty()){
        return;
    }
    QByteArray data(msg);
    int id_sender;
    QChar first_char=data[0];
    QChar second_char=data[1];
    if(first_char=="/"){
        data = data.mid(2);//移除/s等类型头
        if(data[0]=='*'){

            id_sender=handleDataHead(data).toInt();
            if(second_char=='s'){//send被发送消息
                loop_user_send:
                bool had_preview_btn=false;    
                for(ChatPreviewButton*& btn:list_chatpreview){
                    if(btn->m_user.id==id_sender){
                        had_preview_btn=true;
                        User user_sender;
                        user_sender.id=id_sender;
                        Message message;
                        message.type=Message::getType(data);
                        message.sender=user_sender;
                        message.receiver_user=m_user;
                        message.msg=data;
                        if(sound_msg->status()==QSoundEffect::Ready){
                            sound_msg->play();
                        }else{
                            qDebug()<<sound_msg->status();
                        }

                        if(btn->isChecked() && ui->stackedWidget_main->currentWidget()==ui->page_chat){
                            if(chatwidget){
                                qDebug()<<"收到"<<id_sender<<"的消息";
                                chatwidget->addMsg(data,false);
                            }
                        }else{
                            mutex_chat.lock();
                            map_userchat_unread[id_sender].append(message);
                            mutex_chat.unlock();

                            ui->btn_chat->setNum(ui->btn_chat->getNum()+1);
                            btn->updateState();

                        }
                        break;
                    }
                }
                if(!had_preview_btn){
                    User user;
                    user.id=id_sender;
                    addPreviewButton(user);
                    goto loop_user_send;
                }
            }else if(second_char=='g'){//group群内消息
                    int id_group;
                    id_group = handleDataHead(data).toInt();
                loop_group_send:
                    bool had_preview_btn = false;
                    for(ChatPreviewButton*& btn : list_chatpreview){
                        if(btn->m_group.id == id_group){
                            had_preview_btn=true;

                            User user_sender;
                            user_sender.id = id_sender;
                            Group group_receive;
                            group_receive.id = id_group;
                            Message message;
                            message.type=Message::getType(data);
                            message.sender = user_sender;
                            message.receiver_group = group_receive;
                            message.msg = data;
                            if(sound_msg->status()==QSoundEffect::Ready){
                                sound_msg->play();
                            }else{
                                qDebug()<<sound_msg->status();
                            }

                            if(btn->isChecked() && ui->stackedWidget_main->currentWidget()==ui->page_chat){
                                if(chatwidget){
                                    // qDebug()<<QString("群聊%1收到%2的消息:%3").arg(id_group).arg(id_sender).arg(data);
                                    chatwidget->addMsg(data,user_sender);
                                }
                            }else{
                                mutex_chat.lock();
                                map_groupchat_unread[id_group].append(message);
                                mutex_chat.unlock();
                                qDebug()<<"未直接显示聊天窗口";

                                ui->btn_chat->setNum(ui->btn_chat->getNum()+1);
                                btn->updateState();
                            }
                            break;
                        }else{
                            qDebug()<<"userid"<<btn->m_user.id<<"id_sender"<<id_sender;
                        }
                    }
                    if(!had_preview_btn){
                        Group group;
                        group.id = id_group;


                        addPreviewButton(group);
                        goto loop_group_send;
                    }
                }else if(second_char=='a'){//add添加好友
                for(auto& pair:this->m_user.friend_request){
                    if(pair.first.id==id_sender){
                        return;
                    }
                }
                User user_sender;
                user_sender.id=id_sender;

                this->m_user.friend_request.append(qMakePair(user_sender,data));
                int new_num=ui->btn_friend_request->getNum()+1;
                ui->btn_friend_request->setNum(new_num);
                ui->btn_friend->setNum(new_num);
                updateFriendRequest();
            }else if(second_char=='f'){//friend被接受好友
                User user_sender;
                user_sender.id=id_sender;

                addFriend(user_sender,false);
                updateFriendList();
            }else if(second_char=='d'){//delete被删除好友
                for(QObject*oj:ui->scrollAreaWidgetContents_friend->children()){
                    ChatPreviewButton* w=dynamic_cast<ChatPreviewButton*>(oj);
                    if(w){
                        if(w->m_user.id==id_sender){
                            w->deleteLater();
                            break;
                        }
                    }
                }
                User user_sender;
                user_sender.id=id_sender;
                m_user.friends.removeOne(user_sender);

                data="(解除了和你的好友关系)"+data;
                goto loop_user_send;
            }else if(second_char=='v'){//request申请视频通话
                showCameraWidget(id_sender);
            }else if(second_char=='h'){//被挂断
                if(m_camera_widget){
                    showTip("对方已挂断");
                    sendVideoOverMsg(id_sender,m_camera_widget->getTime());
                    delete m_camera_widget;
                }
            }else if(second_char=='u'){//被同意视频通话
                if(m_camera_widget){
                    qDebug()<<"被同意视频通话";
                    m_camera_widget->setConnected(true);
                }
            }else if(second_char=='i'){//image传输通话图片
                if(m_camera_widget && m_camera_widget->isConnected()){
                    qDebug()<<"收到视频通话帧";
                    QImage image = QImage::fromData(data);
                    m_camera_widget->setImage(image);
                }
            }else{
                qDebug()<<"未定义的second_char"<<second_char;
            }
        }else{
            qWarning()<<"意外的字符fmsg[0]:"<<data[0];
        }

    }else{
        qWarning()<<"意外的字符first_char:"<<first_char;
    }
    return;
}

void MainWindow::newSql(const QByteArray &sql, std::function<void (QStringList&)> func_success,std::function<void()> func_fail)
{
    QTcpSocket* socket=new QTcpSocket;
    QEventLoop* loop=new QEventLoop;
    connect(socket,&QTcpSocket::readyRead,this,[=]()mutable{
        QByteArray data=readSocket(socket);
        QStringList list=QString(data).split("/");
        if(list.size()<2){
            qDebug()<<"newSql list"<<list;
            return;
        }
        if(list[1]=="s"){

            qDebug()<<"newSql sql查询成功";
            if(func_success){
                func_success(list);
            }

        }else if(list[1]=="f"){
            if(func_fail){
                func_fail();
            }
        }else{
            qDebug()<<"接收到了意外的回复"<<data;
        }
        socket->deleteLater();
        loop->quit();
        loop->deleteLater();
    });
    connect(socket,&QTcpSocket::errorOccurred,this,[=](QAbstractSocket::SocketError error) {
        qDebug() <<"Socket Error:"<< error;
        socket->deleteLater();
        loop->quit();
        loop->deleteLater();
    });
    socket->connectToHost(QHostAddress(hostip),hostport);

    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_15);
    out<<sql;
    if(socket->state()==QTcpSocket::ConnectingState && !socket->waitForConnected(5000)){
        qDebug()<<"连接超时";
    }
    socket->write(buffer);
    QApplication::processEvents();
    loop->exec();
}
// void MainWindow::sendMsg(QTcpSocket* socket,const QByteArray &msg)
// {
//     QByteArray buffer;
//     QDataStream out(&buffer, QIODevice::WriteOnly);
//     out.setVersion(QDataStream::Qt_5_15);
//     out<<msg;
//     socket->write(buffer);
// }
void MainWindow::addUserDetailWidget(User user)
{
    for(QObject* oj:ui->page_user_detail->children()){
        QWidget* w=dynamic_cast<QWidget*>(oj);
        if(w){
            vl_user_detail->removeWidget(w);
            w->deleteLater();
        }
    }
    bool isfriend=false;
    for(User& user_friend:m_user.friends){
        if(user_friend.id==user.id){
            isfriend=true;
        }
    }
    UserDetail* w=new UserDetail(user,ui->page_user_detail, isfriend, user==m_user);
    ui->stackedWidget_friend->setCurrentWidget(ui->page_user_detail);
    if(w->init()){
        vl_user_detail->addWidget(w);
    }else{
        w->deleteLater();
    }


    connect(w,&UserDetail::updateUserInfo,this,[=](const User& new_user,const QIcon& icon){
        if(!new_user.isEmpty()){
            this->m_user.nickname = new_user.nickname;
            this->m_user.state = new_user.state;
        }
        if(!icon.isNull()){
            ui->btn_user->setIcon(icon);
            qDebug()<<"icon 不为空";
        }
        update();
    });
    connect(w,&UserDetail::chatWith,this,[=](){
        ChatPreviewButton* btn=addPreviewButton(w->m_user);//此处增加历史聊天记录
        if(btn!=nullptr){
            emit btn->clicked(false);
        }

        emit ui->btn_chat->clicked(true);
    });
    connect(w,&UserDetail::addFriend,this,[=](QString request_message){
        sendMsg(user.id,request_message,'a');
    });
    connect(w,&UserDetail::showTip,this,[=](QString tip){
        showTip(tip);
    });
    connect(w,&UserDetail::deleteFriend,this,[=](QString delete_msg){
        if(QMessageBox::StandardButton(QMessageBox::Yes)==QMessageBox::question(this,"提示",QString("确定解除与%1的好友关系吗").arg(w->m_user.nickname))){
            int id_friend=w->m_user.id;
            for(QObject*oj:ui->scrollAreaWidgetContents_friend->children()){
                ChatPreviewButton* w=dynamic_cast<ChatPreviewButton*>(oj);
                if(w){
                    if(w->m_user.id==id_friend){
                        w->deleteLater();
                        break;
                    }
                }
            }
            m_user.friends.removeOne(w->m_user);
            addUserDetailWidget(w->m_user);
            sendMsg(id_friend,delete_msg,'d');
        }
    });
}

void MainWindow::addGroupDetailWidget(Group group)
{
    if(!mutex_page_group_detail.tryLock()){
        return;
    }
    for(QObject* oj:ui->page_group_detail->children()){//清除旧的详情窗口
        QWidget* w=dynamic_cast<QWidget*>(oj);
        if(w){
            vl_group_detail->removeWidget(w);
            delete w;
            w = nullptr;
        }
    }
    GroupDetail* w = new GroupDetail(m_user,group,ui->page_group_detail);
    ui->stackedWidget_group->setCurrentWidget(ui->page_group_detail);
    vl_group_detail->addWidget(w);
    connect(w,&GroupDetail::updateGroupList,w,[=](){
        m_user.groups.clear();//重新加载群聊
        QString sql = QString("/m/load_groups*%1*").arg(m_user.id);
        newSql(sql.toUtf8(),[=](QStringList& list){
            for(int i=2; i<list.size(); i++){
                Group group;
                group.id=list[i].toInt();
                addGroup(group,false);
            }
        });
        updateGroupList();
        // addGroupDetailWidget(group);
    });
    connect(w,&GroupDetail::chat,w,[=](){
        ChatPreviewButton* btn = addPreviewButton(w->m_group);//此处增加历史聊天记录
        if(btn!=nullptr){
            emit btn->clicked(false);
        }

        emit ui->btn_chat->clicked(true);
    });
    connect(w,&GroupDetail::showTip,w,[=](QString tip){
        showTip(tip);
    });
    mutex_page_group_detail.unlock();
}

void MainWindow::addChatWidget(User user_friend)
{
    if(this->chatwidget){
        vl_chatwith->removeWidget(chatwidget);
        delete chatwidget;
    }
    ui->stackedWidget_chat->setCurrentWidget(ui->page_chatwith);
    this->chatwidget = new ChatWidget(ui->page_chatwith);

    mutex_chat.lock();
    auto it = map_userchat_history.find(user_friend.id);
    bool is_valid= (it != map_userchat_history.end());
    // qDebug()<<"is_valid"<<is_valid;
    QList<Message> list_history;
    if(is_valid){
        list_history=*it;
    }
    mutex_chat.unlock();
    if(is_valid){
        chatwidget->init(m_user,user_friend,list_history);
    }else{
        chatwidget->init(m_user,user_friend);
    }

    vl_chatwith->addWidget(chatwidget);
    connect(chatwidget,&ChatWidget::sendMsg,this,[=](const QString& text){
        sendMsg(user_friend.id,text);
        adjustPreviewButtonSize(AdjustPreviewButtonSize::ScrollPreview);

        Message message;
        message.type=Message::MessageType::Text;
        message.receiver_user=user_friend;
        message.sender=m_user;
        message.msg=text.toUtf8();
    });
    connect(chatwidget,&ChatWidget::sendFile,this,[=](const QByteArray& data){
        sendFile(user_friend.id,data);
        adjustPreviewButtonSize(AdjustPreviewButtonSize::ScrollPreview);

        Message message;
        message.type=Message::MessageType::Picture;
        message.receiver_user=user_friend;
        message.sender=m_user;
        message.msg=data;
    });
    connect(chatwidget,&ChatWidget::call,this,[=](const int& id){
        if(m_camera_widget){
            showTip("已经在通话中了");
        }else{
            // int sender = m_user.id;
            int receiver = id;
            // QByteArray packet = QString("*r**%1**%2*").arg(sender).arg(receiver).toUtf8();
            // mutex_ip.lockForRead();
            // m_socket_udp->writeDatagram(packet,QHostAddress(hostip),hostport);
            // mutex_ip.unlock();
            sendMsg(receiver,"",'v');
            qDebug()<<"申请通话成功";
            showCameraWidget(receiver);
            m_camera_widget->setCaller(true);
        }
    });
    connect(chatwidget,&ChatWidget::toDelete,this,[=]()mutable{
        delete chatwidget;
    });
    connect(chatwidget,&ChatWidget::refresh,this,&MainWindow::handleSocket);
    connect(chatwidget,&ChatWidget::updatePreviewState,this,[=](){
        for(ChatPreviewButton*& btn:list_chatpreview){
            if(btn->m_user==user_friend){
                btn->updateState();
                break;
            }else{
                qDebug()<<"btn->m_user:"<<btn->m_user.id<<"user_friend:"<<user_friend.id;
            }
        }
    });
}

void MainWindow::addChatWidget(Group group)
{
    if(this->chatwidget){
        vl_chatwith->removeWidget(chatwidget);
        delete chatwidget;
    }
    ui->stackedWidget_chat->setCurrentWidget(ui->page_chatwith);
    this->chatwidget = new ChatWidget(ui->page_chatwith);

    mutex_chat.lock();
    auto it = map_groupchat_history.find(group.id);
    bool is_valid= (it != map_groupchat_history.end());
    QList<Message> list_history;
    if(is_valid){
        list_history=*it;
    }
    mutex_chat.unlock();
    if(is_valid){
        chatwidget->init(m_user,group,list_history);
    }else{
        chatwidget->init(m_user,group);
    }

    vl_chatwith->addWidget(chatwidget);
    connect(chatwidget,&ChatWidget::sendMsg,this,[=](const QString& text){
        sendMsg(group.id,text,'g');
        adjustPreviewButtonSize(AdjustPreviewButtonSize::ScrollPreview);
    });
    connect(chatwidget,&ChatWidget::sendFile,this,[=](const QByteArray& data){
        sendFile(group.id,data,'g');
        adjustPreviewButtonSize(AdjustPreviewButtonSize::ScrollPreview);
    });
    connect(chatwidget,&ChatWidget::toDelete,this,[=]()mutable{
        delete chatwidget;
    });
    connect(chatwidget,&ChatWidget::refresh,this,&MainWindow::handleSocket);
    connect(chatwidget,&ChatWidget::updatePreviewState,this,[=](){
        for(ChatPreviewButton*& btn:list_chatpreview){
            if(btn->m_group == group){
                btn->updateState();
                break;
            }
        }
    });
}

ChatPreviewButton* MainWindow::addPreviewButton(User user_friend)
{
    for(ChatPreviewButton*& btn:list_chatpreview){
        if(btn->m_user.id == user_friend.id){
            emit btn->clicked(btn->isChecked());
            return nullptr;
        }
    }

    ChatPreviewButton* btn=new ChatPreviewButton(user_friend,ui->scrollArea_preview);
    // adjustPreviewButtonSize(AdjustPreviewButtonSize::ScrollPreview,btn);
    btn->updateState();
    connect(btn,&ChatPreviewButton::clicked,this,[=](bool has_checked){
        btn->choose(true);
        for(ChatPreviewButton*& btn_list:list_chatpreview){
            if(btn_list!=btn){
                btn_list->choose(false);
            }
        }
        // qDebug()<<"ui->page_chatwith->children().size()"<<ui->page_chatwith->children().size();
        if(!has_checked || ui->page_chatwith->children().size()==1){//只有一个子对象的话就是只有布局，没有聊天窗口，此时需要创建
            addChatWidget(btn->m_user);
        }
    });
    connect(btn,&ChatPreviewButton::readMsgNum,this,[=](int num){
        int original_num=ui->btn_chat->getNum();
        int new_num=qBound(0,original_num-num,original_num);
        ui->btn_chat->setNum(new_num);
    });
    list_chatpreview.append(btn);
    QVBoxLayout* l=dynamic_cast<QVBoxLayout*>(ui->scrollAreaWidgetContents_preview->layout());
    if(l){
        l->insertWidget(1,btn);
    }else{
        qDebug()<<"ui->scrollArea->layout()类型转换失败";
    }

    return btn;
}

ChatPreviewButton *MainWindow::addPreviewButton(Group group)
{
    for(ChatPreviewButton*& btn:list_chatpreview){
        if(btn->m_group.id == group.id){
            emit btn->clicked(btn->isChecked());
            return nullptr;
        }
    }

    ChatPreviewButton* btn=new ChatPreviewButton(group,ui->scrollArea_preview);
    btn->updateState();
    connect(btn,&ChatPreviewButton::clicked,this,[=](bool has_checked){
        btn->choose(true);
        for(ChatPreviewButton*& btn_list : list_chatpreview){
            if(btn_list!=btn){
                btn_list->choose(false);
            }
        }
        if(!has_checked || ui->page_chatwith->children().size()==1){//只有一个子对象的话就是只有布局，没有聊天窗口，此时需要创建
            addChatWidget(btn->m_group);
        }
    });
    connect(btn,&ChatPreviewButton::readMsgNum,this,[=](int num){
        int original_num = ui->btn_chat->getNum();
        int new_num = qBound(0,original_num-num,original_num);
        ui->btn_chat->setNum(new_num);
    });
    list_chatpreview.append(btn);
    QVBoxLayout* l=dynamic_cast<QVBoxLayout*>(ui->scrollAreaWidgetContents_preview->layout());
    if(l){
        l->insertWidget(1,btn);
    }else{
        qDebug()<<"ui->scrollArea->layout()类型转换失败";
    }

    return btn;
}

bool MainWindow::addFriend(User user_friend,bool save_to_sql)
{
    bool had=false;
    for(User& user:m_user.friends){
        if(user.id==user_friend.id){
            had=true;
            break;
        }
    }
    if(!had){
        m_user.friends.append(user_friend);
        if(save_to_sql){
            sendMsg(user_friend.id,"",'f');
            QByteArray content=QString("/m/make_friend*%1**%2*").arg(m_user.id,user_friend.id).toUtf8();
            newSql(content,[=](QStringList&){
                return true;
            });
        }
    }
    return false;
}

bool MainWindow::addGroup(const Group &group, bool save_to_sql)
{
    for(Group& it:m_user.groups){
        if(it == group){
            return false;
        }
    }
    m_user.groups.append(group);
    if(save_to_sql){
        QByteArray content=QString("/m/join_chatgroup*%1**%2*").arg(m_user.id,group.id).toUtf8();
        newSql(content,[=](QStringList&){
            return true;
        });
    }
    return false;
}

void MainWindow::updateFriendRequest()
{
    QList<QWidget*> list_will_delete;
    for(QObject*oj:ui->scrollAreaWidgetContents_friend_request->children()){
        QWidget* w=dynamic_cast<QWidget*>(oj);
        if(w){
            list_will_delete.append(w);
        }
    }
    qDeleteAll(list_will_delete);
    // // qDebug()<<QString("剩余%1个申请").arg(m_user.friend_request.size());

    for(auto& pair:m_user.friend_request){
        User user_friend=pair.first;
        QString lmsg=pair.second;
        QWidget* contain=new QWidget(ui->scrollAreaWidgetContents_friend_request);
        QHBoxLayout* hl=new QHBoxLayout(contain);
        ChatPreviewButton* preview=new ChatPreviewButton(user_friend,contain);
        QPushButton* btn_refuse=new QPushButton("拒绝",contain);
        QPushButton* btn_accept=new QPushButton("同意",contain);

        hl->addWidget(preview);
        hl->addWidget(btn_refuse);
        hl->addWidget(btn_accept);
        ui->vlayout_friend_request->insertWidget(0,contain);

        contain->setStyleSheet("QWidget{"
                               "background-color:lightgray;"
                               "}");
        btn_refuse->setStyleSheet("QPushButton{"
                                  "border:none;"
                                  "background-color:rgba(90,180,100,200);"
                                  "color:white;"
                                  "}"
                                  "QPushButton:hover{"
                                  "background-color:rgba(90,180,100,160);"
                                  "}"
                                  "QPushButton:pressed{"
                                  "background-color:rgb(90,180,100);"
                                  "}"
                                  );
        btn_accept->setStyleSheet("QPushButton{"
                                  "border:none;"
                                  "background-color:rgba(90,180,100,200);"
                                  "color:white;"
                                  "}"
                                  "QPushButton:hover{"
                                  "background-color:rgba(90,180,100,160);"
                                  "}"
                                  "QPushButton:pressed{"
                                  "background-color:rgb(90,180,100);"
                                  "}"
                                  );
        auto redPointReduceOne=[=](){
            int original_num=ui->btn_chat->getNum();
            int new_num=qBound(0,original_num-1,original_num);
            ui->btn_friend_request->setNum(new_num);
            ui->btn_friend->setNum(new_num);
        };
        connect(btn_accept,&QPushButton::clicked,this,[=](){
            for(auto& pair:this->m_user.friend_request){
                if(pair.first.id==user_friend.id){
                    m_user.friend_request.removeOne(pair);

                    addFriend(pair.first);

                    updateFriendRequest();
                    updateFriendList();

                    redPointReduceOne();
                    // qDebug()<<QString("剩余%1个申请").arg(m_user.friend_request.size());
                }
            }
        });
        connect(btn_refuse,&QPushButton::clicked,this,[=](){
            for(auto& pair:this->m_user.friend_request){
                if(pair.first.id==user_friend.id){
                    m_user.friend_request.removeOne(pair);
                    updateFriendRequest();

                    redPointReduceOne();
                }
            }
        });

        Message message;
        message.type=Message::MessageType::Text;
        message.sender=user_friend;
        message.receiver_user=m_user;
        message.msg=lmsg.toUtf8();
        preview->list_message.append(message);
        preview->updateState();
    }
}

void MainWindow::updateFriendList()
{
    QList<QWidget*> list_will_delete;
    for(QObject*oj:ui->scrollAreaWidgetContents_friend->children()){
        ChatPreviewButton* w=dynamic_cast<ChatPreviewButton*>(oj);
        if(w){
            list_will_delete.append(w);
        }
    }
    qDeleteAll(list_will_delete);

    QVBoxLayout* vl=dynamic_cast<QVBoxLayout*>(ui->scrollAreaWidgetContents_friend->layout());
    if(vl){
        for(User& user_friend:m_user.friends){
            if(user_friend.isEmpty()){
                UserPatcher* userPatcher=new UserPatcher;//修改
                connect(userPatcher,&UserPatcher::userPatchFinished,this,[=](User user_patcherd)mutable{
                    user_friend = user_patcherd;

                    userPatcher->cleanUp();
                    userPatcher->deleteLater();
                });
                userPatcher->patchUser(user_friend);
            }
            ChatPreviewButton* preview=new ChatPreviewButton(user_friend,ui->scrollAreaWidgetContents_friend);
            // adjustPreviewButtonSize(AdjustPreviewButtonSize::ScrollFriend,preview);
            preview->unique_text=user_friend.state;
            preview->updateState();
            vl->insertWidget(2,preview);
            connect(preview,&ChatPreviewButton::clicked,this,[=](){
                addUserDetailWidget(preview->m_user);
            });
        }
    }else{
        qDebug()<<"ui->scrollAreaWidgetContents_friend->layout()类型转换失败";
    }

}

void MainWindow::updateGroupList()
{
    qDebug()<<"updateGroupList";
    QList<QWidget*> list_will_delete;
    for(QObject*oj:ui->scrollAreaWidgetContents_group->children()){
        ChatPreviewButton* w=dynamic_cast<ChatPreviewButton*>(oj);
        if(w){
            list_will_delete.append(w);
        }
    }
    qDeleteAll(list_will_delete);

    QVBoxLayout* vl=dynamic_cast<QVBoxLayout*>(ui->scrollAreaWidgetContents_group->layout());
    if(vl){
        for(Group& group:m_user.groups){
            if(group.isEmpty() ){
                UserPatcher* userPatcher=new UserPatcher;
                connect(userPatcher,&UserPatcher::groupPatchFinished,this,[=](Group group_patched)mutable{
                    group = group_patched;

                    userPatcher->cleanUp();
                    userPatcher->deleteLater();
                });
                userPatcher->patchGroup(group);
            }
            ChatPreviewButton* preview=new ChatPreviewButton(group,ui->scrollAreaWidgetContents_group);
            preview->unique_text = group.intro;
            preview->updateState();
            vl->insertWidget(2,preview);
            connect(preview,&ChatPreviewButton::clicked,preview,[=](){
                addGroupDetailWidget(group);
            });
        }
    }else{
        qDebug()<<"ui->scrollAreaWidgetContents_group->layout()类型转换失败";
    }
}

void MainWindow::adjustPreviewButtonSize(AdjustPreviewButtonSize mod, ChatPreviewButton *btn)
{
    QSize target_size;
    if(mod==AdjustPreviewButtonSize::ScrollPreview){
        if(btn){
            target_size=ui->scrollAreaWidgetContents_preview->size();
            btn->setMaximumSize(target_size);
            btn->setFixedSize(target_size.width(),btn->height());
        }
    }else if(mod==AdjustPreviewButtonSize::ScrollFriend){
        if(btn){
            target_size=ui->scrollAreaWidgetContents_friend->size();
            btn->setMaximumSize(target_size);
            btn->setFixedSize(target_size.width(),btn->height());
        }
    }else if(mod==AdjustPreviewButtonSize::All){

        target_size=ui->scrollAreaWidgetContents_preview->size();
        for(ChatPreviewButton*& btn:list_chatpreview){
            btn->setMaximumSize(target_size);
            btn->setFixedSize(target_size.width(),btn->height());
        }

        target_size=ui->scrollAreaWidgetContents_friend->size();
        for(ChatPreviewButton*& btn:list_friend){
            btn->setMaximumSize(target_size);
            btn->setFixedSize(target_size.width(),btn->height());
        }
    }
}

void MainWindow::showCameraWidget(const int& id_sender)
{
    if(m_camera_widget){
        delete m_camera_widget;
    }
    m_camera_widget = new CameraWidget;
    m_camera_widget->setAttribute(Qt::WA_DeleteOnClose);
    connect(m_camera_widget,&CameraWidget::outputImage,this,[=](const QImage& image){
        QByteArray data;
        QBuffer buffer(&data);
        buffer.open(QIODevice::WriteOnly);
        if(image.save(&buffer,"JPEG")){
            // qDebug()<<"outputImage size"<<data.size();
            if(m_camera_widget->isConnected()){
                sendFile(id_sender,data,'i');
            }

            // QByteArray packet = QString("*i**%1*").arg(id_sender).toUtf8() + data;
            // mutex_ip.lockForRead();
            // m_socket_udp->writeDatagram(packet,QHostAddress(hostip),hostport);
            // mutex_ip.unlock();
        }else{
            qDebug()<<"缓冲区写入失败";
        }
    });
    connect(m_camera_widget,&CameraWidget::acceptVideo,this,[=](){
        showTip("视频通话已接通");
        sendMsg(id_sender,"",'u');
    });
    connect(m_camera_widget,&CameraWidget::hangUp,this,[=](const QTime& time){
        sendMsg(id_sender,"",'h');
        sendVideoOverMsg(id_sender,time);
    });
    m_camera_widget->show();
}

void MainWindow::createGroup()
{
    QDialog* dlg = new QDialog(this);
    QHBoxLayout* layout = new QHBoxLayout(dlg);
    QLineEdit* edit =new QLineEdit(dlg);
    QPushButton* btn = new QPushButton("确定",dlg);
    layout->addWidget(edit,9);
    layout->addWidget(btn,1);
    edit->setPlaceholderText("输入群聊名称");
    connect(btn,&QPushButton::clicked,this,[=](){
        QString name = edit->text();
        int owner = m_user.id;
        QByteArray sql = QString("/m/create_chatgroup*%1**%2*").arg(name).arg(owner).toUtf8();
        if(!name.isEmpty()){
            newSql(sql,[=](QStringList& list){
                showTip("创建成功");
                Group newGroup;
                newGroup.id = list[2].toInt();
                newGroup.name = name;
                newGroup.owner = owner;
                m_user.groups.append(newGroup);
                qDebug()<<"id"<<newGroup.id;

                updateGroupList();

                dlg->close();
            },[=](){
                showTip("创建失败");
            });
        }
    });

    dlg->setStyleSheet("*{"
                       "font-size:20px;"
                       "}");
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->show();
}


QString MainWindow::handleDataHead(QByteArray &data, const QChar &split)
{
    QString result;
    int counter=0;

    data = data.mid(1);//移除"*"
    for(char& c:data){
        if(c == split){
            data=data.mid(counter+1);//移除所有参与了计数的字符再移除“*”
            break;
        }else{
            counter++;
            result.append(c);
        }
    }
    return result;
}


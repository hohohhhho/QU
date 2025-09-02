#include "chatpreviewbutton.h"
#include "groupdetail.h"
#include "ui_groupdetail.h"
#include "userpatcher.h"

#include <QBuffer>
#include <QFileDialog>
#include <QTcpSocket>
#include <QTimer>

GroupDetail::GroupDetail(const User& user,const Group &group, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GroupDetail)
{
    ui->setupUi(this);
    this->setStyleSheet("*{"
                        "font-size:20px;"
                        "}"
                        "QLineEdit#edit_id{"
                        "font-size:15px;"
                        "}"
                        "QLineEdit#edit_intro{"
                        "font-size:15px;"
                        "}");
    QVBoxLayout* layout_scroll = new QVBoxLayout(ui->scrollAreaWidgetContents);
    layout_scroll->addItem(new QSpacerItem(0,0,QSizePolicy::Ignored,QSizePolicy::Expanding));

    this->m_user = user;
    this->m_group = group;

    auto updateUi = [=](){
        ui->edit_name->setText(m_group.name);
        ui->edit_intro->setText(m_group.intro);
        ui->btn_profile->setIcon(m_group.icon);
    };
    if(m_group.isEmpty()){
        UserPatcher* userPatcher=new UserPatcher;
        connect(userPatcher,&UserPatcher::groupPatchFinished,this,[=](Group group_patched){
            m_group = group_patched;
            updateUi();

            userPatcher->cleanUp();
            userPatcher->deleteLater();
        });
        userPatcher->patchGroup(m_group);
    }else{
        updateUi();
    }

    ui->edit_id->setText("群号:"+QString::number(m_group.id));

    //获取用户在该群聊中的权限
    {
        QString sql = QString("/m/role_of_chatgroup*%1**%2*").arg(m_user.id).arg(group.id);
        newSql(sql.toUtf8(),[=](QStringList& list){
            this->role = list[2].toInt();
            qDebug()<<"群权限"<<role;
        });
    }

    QString name_origin = ui->edit_name->text();
    QString intro_origin = ui->edit_intro->text();

    switch (role) {
    case 0://非群员
        ui->btn1->setText("加入群聊");
        ui->btn2->setVisible(false);
        ui->btn3->setVisible(false);
        ui->btn_profile->setPictureCheckable(true);
        connect(ui->btn1,&QPushButton::clicked,this,[=](){
            int id_user = m_user.id;
            int id_group = group.id;
            QString sql = QString("/m/join_chatgroup*%1**%2*").arg(id_user).arg(id_group);
            newSql(sql.toUtf8(),[=](QStringList&){
                showTip("加入成功");
                emit updateGroupList();
            },[=](){
                showTip("加入失败");
            });
        });
        break;
    case 1://群员
        ui->btn1->setText("退出群聊");
        ui->btn2->setText("发送消息");
        ui->btn3->setVisible(false);
        ui->btn_profile->setPictureCheckable(true);
        connect(ui->btn1,&QPushButton::clicked,this,[=](){
            leaveGroup();
        });
        connect(ui->btn2,&QPushButton::clicked,this,[=](){
            emit chat();
        });
        break;
    case 2://管理员
        ui->btn1->setText("退出群聊");
        ui->btn2->setText("编辑群聊");
        ui->btn3->setText("发送消息");
        connect(ui->btn_profile,&QPushButton::clicked,this,[=](){
            modifyGroupIcon();
        });
        connect(ui->btn1,&QPushButton::clicked,this,[=](){
            leaveGroup();
        });
        connect(ui->btn2,&QPushButton::clicked,this,[=]()mutable{
            if(ui->btn2->text() == "编辑群聊"){
                ui->edit_name->setReadOnly(false);
                ui->edit_intro->setReadOnly(false);
                ui->btn2->setText("保存");
                ui->btn3->setText("取消");
                name_origin = ui->edit_name->text();
                intro_origin = ui->edit_intro->text();
            }else if(ui->btn2->text() == "保存"){
                ui->edit_name->setReadOnly(true);
                ui->edit_intro->setReadOnly(true);
                ui->btn2->setText("编辑群聊");
                ui->btn3->setText("发送消息");

                modifyGroup();
            }
        });
        connect(ui->btn3,&QPushButton::clicked,this,[=](){
            if(ui->btn3->text() == "发送消息"){
                emit chat();
            }else if(ui->btn3->text() == "取消"){
                ui->edit_name->setReadOnly(true);
                ui->edit_intro->setReadOnly(true);
                ui->edit_name->setText(name_origin);
                ui->edit_intro->setText(intro_origin);
                ui->btn2->setText("编辑群聊");
                ui->btn3->setText("发送消息");
            }
        });
        break;
    case 3://群主
        ui->btn1->setText("解散群聊");
        ui->btn2->setText("编辑群聊");
        ui->btn3->setText("发送消息");
        connect(ui->btn_profile,&QPushButton::clicked,this,[=](){
            modifyGroupIcon();
        });
        connect(ui->btn1,&QPushButton::clicked,this,[=](){

        });
        connect(ui->btn2,&QPushButton::clicked,this,[=]()mutable{
            if(ui->btn2->text() == "编辑群聊"){
                ui->edit_name->setReadOnly(false);
                ui->edit_intro->setReadOnly(false);
                ui->btn2->setText("保存");
                ui->btn3->setText("取消");
            }else if(ui->btn2->text() == "保存"){
                ui->edit_name->setReadOnly(true);
                ui->edit_intro->setReadOnly(true);
                ui->btn2->setText("编辑群聊");
                ui->btn3->setText("发送消息");
                name_origin = ui->edit_name->text();
                intro_origin = ui->edit_intro->text();

                modifyGroup();
            }
        });
        connect(ui->btn3,&QPushButton::clicked,this,[=](){
            if(ui->btn3->text() == "发送消息"){
                emit chat();
            }else if(ui->btn3->text() == "取消"){
                ui->edit_name->setReadOnly(true);
                ui->edit_intro->setReadOnly(true);
                ui->edit_name->setText(name_origin);
                ui->edit_intro->setText(intro_origin);
                ui->btn2->setText("编辑群聊");
                ui->btn3->setText("发送消息");
            }
        });
        break;
    default:
        qDebug()<<"权限错误"<<role;
        break;
    }

    //加载成员列表
    {
        QString sql = QString("/m/members_of_chatgroup*%1*").arg(group.id);
        // QMap<int,int> map_member;//成员表<id,role>
        newSql(sql.toUtf8(),[=](QStringList& list)mutable{
            for(int i=2; i+1 < list.size(); i+=2){
                int id = list[i].toInt();
                int role = list[i+1].toInt();

                // map_member.insert(id,role);
                User user;
                user.id = id;

                if(id > 0){
                    qDebug()<<"加载ChatPreviewButton";
                    ChatPreviewButton* btn = new ChatPreviewButton(user,ui->scrollAreaWidgetContents);
                    layout_scroll->insertWidget(layout_scroll->count()-1,btn);

                    QString unique_text;
                    switch(role){
                    case 1:
                        unique_text = "成员";
                        break;
                    case 2:
                        unique_text = "管理员";
                        break;
                    case 3:
                        unique_text = "群主";
                        break;
                    }
                    btn->unique_text = unique_text;
                    btn->updateState();

                    QApplication::processEvents();
                }
            }
        });
        // QTimer::singleShot(10,this,[=](){
        //     qDebug()<<"map_member size"<<map_member.size();
        //     for(auto it=map_member.begin() ; it!=map_member.constEnd() ;++it){//map的键即为id
        //         int id = it.key();
        //         int role = it.value();
        //         User user;
        //         user.id = id;

        //         if(id > 0){
        //             qDebug()<<"加载ChatPreviewButton";
        //             ChatPreviewButton* btn = new ChatPreviewButton(user,ui->scrollAreaWidgetContents);
        //             layout_scroll->insertWidget(layout_scroll->count()-1,btn);

        //             QString unique_text;
        //             switch(role){
        //             case 1:
        //                 unique_text = "成员";
        //                 break;
        //             case 2:
        //                 unique_text = "管理员";
        //                 break;
        //             case 3:
        //                 unique_text = "群主";
        //                 break;
        //             }
        //             btn->unique_text = unique_text;
        //             btn->updateState();
        //         }
        //     }
        // });
    }
    qDebug()<<"GroupDetail构建完成";
}

GroupDetail::~GroupDetail()
{
    delete ui;
}

void GroupDetail::newSql(const QByteArray &sql, std::function<void (QStringList&)> func_success,std::function<void()> func_fail)
{
    QTcpSocket* socket=new QTcpSocket;
    QEventLoop* loop=new QEventLoop;
    QTimer* timer =new QTimer(this);
    auto clear = [=](){
        socket->deleteLater();
        timer->stop();
        timer->deleteLater();
        loop->quit();
        loop->deleteLater();
    };
    connect(socket,&QTcpSocket::readyRead,this,[=]()mutable{
        QByteArray data = defaultReadSocket(socket);
        QStringList list = QString(data).split("/");
        if(list.size()<2){
            qDebug()<<"newSql list"<<list;
            return;
        }
        if(list[1]=="s"){

            qDebug()<<"GroupDetail::newSql sql查询成功";
            if(func_success){
                func_success(list);
            }

        }else if(list[1]=="f"){
            if(func_fail){
                func_fail();
            }
            qDebug()<<"GroupDetail::newSql sql查询失败";
        }else{
            qDebug()<<"接收到了意外的回复"<<data;
        }

        clear();
    });
    connect(socket,&QTcpSocket::errorOccurred,this,[=](QAbstractSocket::SocketError error) {
        qDebug() <<"Socket Error:"<< error;
        clear();
    });
    socket->connectToHost(QHostAddress(hostip),hostport);

    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_8);
    out<<sql;
    if(socket->state()==QTcpSocket::ConnectingState && !socket->waitForConnected(5000)){
        qDebug()<<"连接超时";
    }
    socket->write(buffer);
    QApplication::processEvents();
    loop->exec();
}

void GroupDetail::modifyGroup()
{
    QString name = ui->edit_name->text();
    QString intro = ui->edit_intro->text();
    int id = m_group.id;
    QString sql = QString("/m/modify_chatgroup*%1**%2**%3*").arg(name,intro).arg(id);
    newSql(sql.toUtf8(),[=](QStringList&){
        showTip("修改成功");
        emit updateGroupList();
    },[=](){
        showTip("修改失败");
   });
}

void GroupDetail::modifyGroupIcon()
{
    QString filename=QFileDialog::getOpenFileName(this,"打开图片");
    QPixmap pxp(filename);
    if(pxp.isNull()){
        return;
    }
    QIcon icon(pxp);
    ui->btn_profile->setIcon(icon);

    QByteArray data;
    QBuffer buffer(&data);
    buffer.open(QIODevice::WriteOnly);
    pxp.save(&buffer,"PNG");
    QByteArray head("/q");// [size](/p([size]id)([size]profile))
    QByteArray packet;
    QDataStream out_packet(&packet,QIODevice::WriteOnly);
    out_packet.writeRawData(head.data(),head.size());
    out_packet<<m_group.id<<data;
    newSql(packet,[=](QStringList&){
        showTip("保存成功");
        emit updateGroupList();
    },[=](){
        showTip("保存失败");
   });
}

void GroupDetail::leaveGroup()
{
    int id_user = m_user.id;
    int id_group = m_group.id;
    QString sql = QString("/m/leave_chatgroup*%1**%2*").arg(id_user).arg(id_group);
    newSql(sql.toUtf8(),[=](QStringList&){
        showTip("已退出群聊");
        emit updateGroupList();
    },[=](){
        showTip("退出失败");
   });
}

#include "userdetail.h"
#include "ui_userdetail.h"
#include "userpatcher.h"

#include <QBuffer>
#include <QFileDialog>
#include <QLineEdit>
#include <QMessageBox>
#include <QPainter>
#include <QPainterPath>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

UserDetail::UserDetail(const User &user, QWidget *parent, bool isfriend, bool myself)
    : QWidget(parent)
    , ui(new Ui::UserDetail)
{
    ui->setupUi(this);
    ui->stacked_user_info->setCurrentWidget(ui->page_read);

    this->m_user=user;
    this->setAttribute(Qt::WA_TranslucentBackground);

    ui->btn_like->setText(QString::number(m_user.likes));

    connect(ui->btn_chat,&QPushButton::clicked,this,[=](){
        emit chatWith();
    });
    if(myself){
        ui->btn_left->setText("编辑信息");
        connect(ui->btn_prefile,&QPushButton::clicked,this,[=](){
            QString filename=QFileDialog::getOpenFileName(this,"打开图片");
            QPixmap pxp(filename);
            if(pxp.isNull()){
                return;
            }
            QIcon icon(pxp);
            m_user.icon = icon;
            ui->btn_prefile->setIcon(icon);

            emit updateUserInfo(User(),icon);

            QByteArray data;
            QBuffer buffer(&data);
            buffer.open(QIODevice::WriteOnly);
            pxp.save(&buffer,"PNG");
            QByteArray head("/p");// [size](/p([size]id)([size]profile))
            QByteArray packet;
            QDataStream out_packet(&packet,QIODevice::WriteOnly);
            out_packet.writeRawData(head.data(),head.size());
            out_packet<<m_user.id<<data;
            newSql(packet,[=](QStringList list){
                Q_UNUSED(list);
                showTip("保存成功");
            },[=](){
                showTip("保存失败");
            });
        });
        connect(ui->btn_left,&QPushButton::clicked,this,[=](){
            ui->stacked_user_info->setCurrentWidget(ui->page_write);
            ui->stacked_btn->setCurrentWidget(ui->page_edit);
            ui->edit_id->setText(QString::number(this->m_user.id));
            ui->edit_nickname->setText(this->m_user.nickname);
            ui->edit_state->setText(this->m_user.state);
        });
        connect(ui->btn_save,&QPushButton::clicked,this,[=](){
            ui->stacked_user_info->setCurrentWidget(ui->page_read);
            ui->stacked_btn->setCurrentWidget(ui->page_normal);

            QString nickname=ui->edit_nickname->text();
            QString state=ui->edit_state->text();

            this->m_user.nickname=nickname;
            this->m_user.state=state;
            QByteArray content=QString("/m/update_user_info*%1**%2**%3*").arg(nickname,state).arg(m_user.id).toUtf8();
            newSql(content,[=](QStringList list){
                Q_UNUSED(list);
                init();
                emit updateUserInfo(m_user);
                showTip("保存成功");
            },[=](){
                showTip("保存失败");
            });
        });
        connect(ui->btn_cancel,&QPushButton::clicked,this,[=](){
            ui->stacked_user_info->setCurrentWidget(ui->page_read);
            ui->stacked_btn->setCurrentWidget(ui->page_normal);
        });
    }else if(isfriend){
        ui->btn_left->setText("删除好友");
        ui->btn_prefile->setPictureCheckable(true);

        connect(ui->btn_left,&QPushButton::clicked,this,[=](){
            QDialog* dlg=new QDialog(this);
            QHBoxLayout* hl=new QHBoxLayout(dlg);
            QLineEdit* edit=new QLineEdit("",dlg);
            edit->setPlaceholderText("告别语(可不填)");
            QPushButton* btn=new QPushButton("确定",dlg);
            connect(btn,&QPushButton::clicked,this,[=](){
                dlg->close();
                QString delete_msg=edit->text();
                emit deleteFriend(delete_msg);
                // if(!delete_msg.isEmpty()){

                // }
            });
            hl->addWidget(edit);
            hl->addWidget(btn);
            dlg->exec();
        });
        connect(ui->btn_like,&QPushButton::clicked,this,[=](){
            int num = ui->btn_like->text().toInt();
            num++;
            ui->btn_like->setText(QString::number(num));
            QByteArray sql = QString("/m/like_user*%1*").arg(m_user.id).toUtf8();
            newSql(sql,[=](QStringList){});
        });

    }else{
        ui->btn_prefile->setPictureCheckable(true);
        connect(ui->btn_left,&QPushButton::clicked,this,[=](){
            QDialog* dlg=new QDialog(this);
            QHBoxLayout* hl=new QHBoxLayout(dlg);
            QLineEdit* edit=new QLineEdit("请求添加你为好友",dlg);
            QPushButton* btn=new QPushButton("确定",dlg);
            connect(btn,&QPushButton::clicked,this,[=](){
                dlg->close();
                QString request_msg=edit->text();
                if(!request_msg.isEmpty()){
                    emit addFriend(request_msg);
                }
            });
            hl->addWidget(edit);
            hl->addWidget(btn);
            dlg->exec();
        });
    }
}

UserDetail::~UserDetail()
{
    delete ui;
}

void UserDetail::paintEvent(QPaintEvent *ev)
{
    Q_UNUSED(ev);
    QPainter painter(this);
    painter.fillRect(rect(),Qt::transparent);
    painter.setPen(Qt::NoPen);
    QPainterPath path;
    path.addRoundedRect(rect(),20,20);

    painter.setBrush(Qt::white);
    painter.drawPath(path);
    painter.setBrush(color_light_blue);
    painter.drawPath(path);
}

bool UserDetail::init()
{
    if(this->m_user.id <= 0){
        return  false;
    }

    auto updateUi = [=](){
        ui->btn_prefile->setIcon(m_user.icon);
        ui->label_nickname->setText(m_user.nickname);
        ui->label_id->setText("id:"+QString::number(m_user.id));
        ui->label_state->setText(m_user.state);
        ui->btn_like->setText(QString::number(m_user.likes));
    };
    if(m_user.isEmpty()){
        UserPatcher* userPatcher=new UserPatcher;
        connect(userPatcher,&UserPatcher::userPatchFinished,this,[=](User user_patcherd){
            m_user = user_patcherd;
            updateUi();

            userPatcher->cleanUp();
            userPatcher->deleteLater();
        });
        userPatcher->patchUser(m_user);

    }else{
        updateUi();
    }
    return true;
}

void UserDetail::setPopWidget()
{
    ui->stacked_btn->setVisible(false);
    QVBoxLayout* l = qobject_cast<QVBoxLayout*>(this->layout());
    if(l){
        l->setStretch(l->count()-1,0);
    }else{
        qDebug()<<"UserDetail::setPopWidget::l为空";
    }
    this->setFont(QFont("微软雅黑",15));
    // this->setStyleSheet("QWidget#UserDetail{"
    //                     "border:2px solid white;"
    //                     "border-radius:10px;"
    //                     "font-size:15px;"
    //                     "}");
    this->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->resize(447,250);
    this->init();
}
void UserDetail::newSql(const QByteArray &sql, std::function<void (QStringList&)> func_success,std::function<void()> func_fail)
{
    QTcpSocket* socket=new QTcpSocket;
    QEventLoop* loop=new QEventLoop;
    connect(socket,&QTcpSocket::readyRead,this,[=]()mutable{
        QByteArray data=defaultReadSocket(socket);
        QStringList list=QString(data).split("/");
        if(list.size()<2){
            qDebug()<<"newSql list"<<list;
            return;
        }
        if(list[1]=="s"){

            qDebug()<<"UserDetail::newSql sql查询成功";
            if(func_success){
                func_success(list);
            }

        }else if(list[1]=="f"){
            if(func_fail){
                func_fail();
            }
            qDebug()<<"UserDetail::newSql sql查询失败";
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
    out.setVersion(QDataStream::Qt_6_8);
    out<<sql;
    if(socket->state()==QTcpSocket::ConnectingState && !socket->waitForConnected(5000)){
        qDebug()<<"连接超时";
    }
    socket->write(buffer);
    QApplication::processEvents();
    loop->exec();
}

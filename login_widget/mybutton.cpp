#include "mybutton.h"
//#include "./ui_mybutton.h"
#include <QPainter>
#include <QDebug>
#include <QFont>
#include <QPropertyAnimation>
#include <QTimer>

MyButton::MyButton(QWidget *parent)
    : QWidget(parent)
    //, ui(new Ui::Widget)
{
    //ui->setupUi(this);
    resize(80,40);
    //this->timer=new QTimer(this);

    this->setMouseTracking(true);


    this->animation1=new QPropertyAnimation(this);
    animation1->setTargetObject(this);
    animation1->setDuration(100);
    animation1->setEasingCurve(QEasingCurve::OutCubic);
    connect(animation1,&QPropertyAnimation::valueChanged,this,[=](const QVariant value){
        this->circle_radius1=value.toInt();
        //this->circle_radius2=value.toInt()/2;
        //qDebug()<<value.toInt();
        update();
        if(circle_radius1==h/3){
            emit animation1->finished();
            circle_radius1=0;
            //circle_radius2=0;
        }
    });
}

MyButton::~MyButton()
{
    //delete ui;
}

void MyButton::paintEvent(QPaintEvent *ev)
{
    Q_UNUSED(ev);
    QPainter painter(this);
    QFont font("微软雅黑",h/12+w/12);
    painter.setBrush(this->BkColor);
    painter.setPen(this->BkColor);
    painter.drawRoundedRect(0,0,w,h,radius,radius);


    painter.setPen(QPen(this->BkColor));
    painter.setBrush(QBrush(this->BkColor));
    // QList<int>::Iterator it1=this->circle_x_list.begin();
    // QList<int>::Iterator it2=this->circle_y_list.begin();
    // QList<int>::Iterator it3=this->circle_radius_list.begin();
    // for(;it1!=circle_x_list.end();++it1,++it2,++it3){
    //     painter.drawEllipse(*it1-*it3/2,*it2-*it3/2,*it3,*it3);
    // }
    painter.drawEllipse(circle_x-circle_radius1/2,circle_y-circle_radius1/2,circle_radius1,circle_radius1);

    // int tempr;
    // if(circle_radius==0)
    //     tempr=0;
    // else
    //     tempr=circle_radius-h/30;
    // painter.setBrush(Qt::NoBrush);
    // painter.drawEllipse(circle_x-tempr/2,circle_y-tempr/2,tempr,tempr);

    painter.setPen(QPen(this->TextColor));
    painter.setFont(font);
    painter.drawText(0,0,w,h,Qt::AlignCenter,text);
}

// void Widget::mouseMoveEvent(QMouseEvent *ev)
// {
//     static int num=0;
//     QPoint point=ev->pos();
//     if(point.x()<w&&point.y()<h){
//         BkColor=qRgb(9,230,230);qDebug()<<num++;
//     }
//     else
//         BkColor=qRgb(9,100,225);
//     update();

// }

void MyButton::resizeEvent(QResizeEvent *ev)
{
    QSize size=ev->size();
    w=size.width();
    h=size.height();
    radius=h/10;
}

void MyButton::enterEvent(QEnterEvent *ev)
{
    //BkColor=qRgb(9,230,230);//青色
    QColor temp=BkColor;
    BkColor=TempColor;
    TempColor=temp;
    //qDebug<<"enter";
    QWidget::enterEvent(ev);
    update();
}

void MyButton::leaveEvent(QEvent *ev)
{
    QColor temp=BkColor;
    BkColor=TempColor;
    TempColor=temp;
    //qDebug<<"leave";
    QWidget::leaveEvent(ev);
    update();
}

void MyButton::mousePressEvent(QMouseEvent *ev)
{
    //QList<int>::Iterator it1=this->circle_x_list.begin();
    //QList<int>::Iterator it2=this->circle_y_list.begin();
    //QList<int>::Iterator it3=this->circle_radius_list.begin();
    //QList<QPropertyAnimation*>::Iterator it4=this->animation_list.begin();
    // for(int i=0;i<pointer;i++,++it1,++it2,++it3,++it4){
    //     *it1=ev->pos().x();
    //     *it2=ev->pos().y();
    //     *it3=h/2;
    //     *it4
    // }

    // this->circle_x_list.append( pos().x() );
    // this->circle_y_list.append( pos().y() );
    // this->circle_radius_list.append( h/2 );
    // QPropertyAnimation* animation=new QPropertyAnimation(this);
    // animation->setTargetObject(this);
    // animation->setDuration(500);
    // animation->setEasingCurve(QEasingCurve::OutCubic);
    // connect(animation,&QPropertyAnimation::valueChanged,this,[=](const QVariant value)mutable{
    //     QList<int>::Iterator it=this->circle_radius_list.begin();
    //     for(int i=0;i<pointer;i++,++it){
    //         *it=value.toInt();
    //         update();
    //         if(*it==h/2){
    //             emit animation->finished();
    //             *it=0;
    //         }
    //     }
    // });
    // animation->setStartValue(0);
    // animation->setEndValue(h/2);
    // //this->animation_list.append(animation);
    // this->group->addAnimation(animation);
    // group->start();

    this->circle_x=ev->pos().x();
    this->circle_y=ev->pos().y();

    // this->TempColor=this->BkColor;


    // timer->start(500);
    // connect(timer,&QTimer::timeout,this,[=](){this->BkColor=TempColor;});
    this->BkColor=qRgb(9,230,230);

    animation1->setStartValue(0);
    animation1->setEndValue(h/3);
    animation1->start();

    emit clicked();
}

void MyButton::mouseReleaseEvent(QMouseEvent *ev)
{
    Q_UNUSED(ev);
    // static int num=0;
    // qDebug()<<num++;
    BkColor=qRgb(30,140,230);
    update();
}

// void MyButton::setText(QString text)
// {
//     this->text=text;
// }


/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "myhintpushbutton.h"
#include "profile.h"
#include "redpointbutton.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QWidget *widget_tool;
    QVBoxLayout *verticalLayout_3;
    Profile *btn_user;
    RedPointButton *btn_chat;
    RedPointButton *btn_friend;
    MyHintPushButton *btn_group;
    MyHintPushButton *btn_set;
    MyHintPushButton *btn_test;
    QSpacerItem *verticalSpacer;
    QStackedWidget *stackedWidget_main;
    QWidget *page_test;
    QHBoxLayout *horizontalLayout;
    QLineEdit *edit;
    QPushButton *btn;
    QWidget *page_friend;
    QHBoxLayout *horizontalLayout_6;
    QScrollArea *scrollArea_friend;
    QWidget *scrollAreaWidgetContents_friend;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_5;
    QLineEdit *edit_seek_friend;
    QPushButton *btn_seek_friend;
    RedPointButton *btn_friend_request;
    QSpacerItem *verticalSpacer_3;
    QStackedWidget *stackedWidget_friend;
    QWidget *page_seek_result;
    QWidget *page_friend_request;
    QVBoxLayout *verticalLayout_5;
    QScrollArea *scrollArea_friend_request;
    QWidget *scrollAreaWidgetContents_friend_request;
    QVBoxLayout *verticalLayout_7;
    QVBoxLayout *vlayout_friend_request;
    QSpacerItem *verticalSpacer_4;
    QWidget *page_user_detail;
    QWidget *page_chat;
    QHBoxLayout *horizontalLayout_2;
    QScrollArea *scrollArea_preview;
    QWidget *scrollAreaWidgetContents_preview;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *edit_seek;
    QPushButton *btn_seek;
    QSpacerItem *verticalSpacer_2;
    QStackedWidget *stackedWidget_chat;
    QWidget *page_chatwith;
    QWidget *page_2;
    QWidget *page_set;
    QHBoxLayout *horizontalLayout_9;
    QHBoxLayout *horizontalLayout_7;
    QScrollArea *scrollArea_set;
    QWidget *scrollAreaWidgetContents_set;
    QVBoxLayout *verticalLayout_10;
    QVBoxLayout *vl_set;
    QPushButton *btn_custom;
    QPushButton *btn_connect;
    QPushButton *btn_msg;
    QPushButton *btn_account;
    QSpacerItem *verticalSpacer_7;
    QStackedWidget *stacked_set;
    QWidget *page_set_connect;
    QVBoxLayout *verticalLayout_13;
    QVBoxLayout *verticalLayout_12;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *edit_ip;
    QLabel *label_2;
    QLineEdit *edit_port;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_11;
    QRadioButton *radio_linux;
    QRadioButton *radio_windows;
    QRadioButton *radio_cloud;
    QRadioButton *radio_custom;
    QHBoxLayout *horizontalLayout_11;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btn_connect_save;
    QPushButton *btn_connect_reset;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_10;
    QSpacerItem *horizontalSpacer;
    QPushButton *btn_connect_relogin;
    QPushButton *btn_connect_restart;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_8;
    QWidget *page_set_custom;
    QWidget *page_set_account;
    QVBoxLayout *verticalLayout_15;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_14;
    QRadioButton *radio_seek_by_id;
    QRadioButton *radio_seek_by_nickname;
    QRadioButton *radio_seek_by_rand;
    QRadioButton *radio_seek_by_noway;
    QCheckBox *checkBox_likes;
    QCheckBox *checkBox_group;
    QPushButton *btn_update_password;
    QPushButton *btn_logout;
    QSpacerItem *verticalSpacer_9;
    QWidget *page_set_msg;
    QWidget *page_set_null;
    QWidget *page_group;
    QWidget *layoutWidget;
    QHBoxLayout *vl_group;
    QScrollArea *scrollArea_group;
    QWidget *scrollAreaWidgetContents_group;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_8;
    QLineEdit *edit_seek_group;
    QPushButton *btn_seek_group;
    QPushButton *btn_create_group;
    QSpacerItem *verticalSpacer_5;
    QStackedWidget *stackedWidget_group;
    QWidget *page_seek_result_2;
    QWidget *page_friend_request_2;
    QVBoxLayout *verticalLayout_8;
    QScrollArea *scrollArea_friend_request_2;
    QWidget *scrollAreaWidgetContents_friend_request_2;
    QVBoxLayout *verticalLayout_9;
    QVBoxLayout *vlayout_friend_request_2;
    QSpacerItem *verticalSpacer_6;
    QWidget *page_group_detail;
    QWidget *widget;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout_3 = new QHBoxLayout(centralwidget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        widget_tool = new QWidget(centralwidget);
        widget_tool->setObjectName("widget_tool");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget_tool->sizePolicy().hasHeightForWidth());
        widget_tool->setSizePolicy(sizePolicy);
        verticalLayout_3 = new QVBoxLayout(widget_tool);
        verticalLayout_3->setSpacing(10);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        btn_user = new Profile(widget_tool);
        btn_user->setObjectName("btn_user");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(btn_user->sizePolicy().hasHeightForWidth());
        btn_user->setSizePolicy(sizePolicy1);

        verticalLayout_3->addWidget(btn_user);

        btn_chat = new RedPointButton(widget_tool);
        btn_chat->setObjectName("btn_chat");
        sizePolicy1.setHeightForWidth(btn_chat->sizePolicy().hasHeightForWidth());
        btn_chat->setSizePolicy(sizePolicy1);
        btn_chat->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color:rgb(255,255,255);\n"
"	border: 1px solid rgb(255, 255, 255);\n"
"	border-top-color: rgba(255, 255, 255, 0.6);\n"
"    border-left-color: rgba(255, 255, 255, 0.6);\n"
"    border-right-color: rgba(0, 0, 0, 0.2);\n"
"    border-bottom-color: rgba(0, 0, 0, 0.2);\n"
"	border-radius: 5px;\n"
"}\n"
"QPushButton:checked{\n"
"	background-color:rgba(244,234,42,200);\n"
"	border: 1px solid rgba(244, 234, 42, 200);\n"
"	border-top-color: rgba(255, 255, 255, 0.6);\n"
"    border-left-color: rgba(255, 255, 255, 0.6);\n"
"    border-right-color: rgba(0, 0, 0, 0.2);\n"
"    border-bottom-color: rgba(0, 0, 0, 0.2);\n"
"	border-radius: 5px;\n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/res/chat.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btn_chat->setIcon(icon);
        btn_chat->setCheckable(true);
        btn_chat->setChecked(true);

        verticalLayout_3->addWidget(btn_chat);

        btn_friend = new RedPointButton(widget_tool);
        btn_friend->setObjectName("btn_friend");
        sizePolicy1.setHeightForWidth(btn_friend->sizePolicy().hasHeightForWidth());
        btn_friend->setSizePolicy(sizePolicy1);
        btn_friend->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color:rgb(255,255,255);\n"
"	border: 1px solid rgb(255, 255, 255);\n"
"	border-top-color: rgba(255, 255, 255, 0.6);\n"
"    border-left-color: rgba(255, 255, 255, 0.6);\n"
"    border-right-color: rgba(0, 0, 0, 0.2);\n"
"    border-bottom-color: rgba(0, 0, 0, 0.2);\n"
"	border-radius: 5px;\n"
"}\n"
"QPushButton:checked{\n"
"	background-color:rgba(244,234,42,200);\n"
"	border: 1px solid rgba(244, 234, 42, 200);\n"
"	border-top-color: rgba(255, 255, 255, 0.6);\n"
"    border-left-color: rgba(255, 255, 255, 0.6);\n"
"    border-right-color: rgba(0, 0, 0, 0.2);\n"
"    border-bottom-color: rgba(0, 0, 0, 0.2);\n"
"	border-radius: 5px;\n"
"}"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/res/friend.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btn_friend->setIcon(icon1);
        btn_friend->setCheckable(true);

        verticalLayout_3->addWidget(btn_friend);

        btn_group = new MyHintPushButton(widget_tool);
        btn_group->setObjectName("btn_group");
        sizePolicy1.setHeightForWidth(btn_group->sizePolicy().hasHeightForWidth());
        btn_group->setSizePolicy(sizePolicy1);
        btn_group->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color:rgb(255,255,255);\n"
"	border: 1px solid rgb(255, 255, 255);\n"
"	border-top-color: rgba(255, 255, 255, 0.6);\n"
"    border-left-color: rgba(255, 255, 255, 0.6);\n"
"    border-right-color: rgba(0, 0, 0, 0.2);\n"
"    border-bottom-color: rgba(0, 0, 0, 0.2);\n"
"	border-radius: 5px;\n"
"}\n"
"QPushButton:checked{\n"
"	background-color:rgba(244,234,42,200);\n"
"	border: 1px solid rgba(244, 234, 42, 200);\n"
"	border-top-color: rgba(255, 255, 255, 0.6);\n"
"    border-left-color: rgba(255, 255, 255, 0.6);\n"
"    border-right-color: rgba(0, 0, 0, 0.2);\n"
"    border-bottom-color: rgba(0, 0, 0, 0.2);\n"
"	border-radius: 5px;\n"
"}"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/res/group.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btn_group->setIcon(icon2);
        btn_group->setCheckable(true);

        verticalLayout_3->addWidget(btn_group);

        btn_set = new MyHintPushButton(widget_tool);
        btn_set->setObjectName("btn_set");
        sizePolicy1.setHeightForWidth(btn_set->sizePolicy().hasHeightForWidth());
        btn_set->setSizePolicy(sizePolicy1);
        btn_set->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color:rgb(255,255,255);\n"
"	border: 1px solid rgb(255, 255, 255);\n"
"	border-top-color: rgba(255, 255, 255, 0.6);\n"
"    border-left-color: rgba(255, 255, 255, 0.6);\n"
"    border-right-color: rgba(0, 0, 0, 0.2);\n"
"    border-bottom-color: rgba(0, 0, 0, 0.2);\n"
"	border-radius: 5px;\n"
"}\n"
"QPushButton:checked{\n"
"	background-color:rgba(244,234,42,200);\n"
"	border: 1px solid rgba(244, 234, 42, 200);\n"
"	border-top-color: rgba(255, 255, 255, 0.6);\n"
"    border-left-color: rgba(255, 255, 255, 0.6);\n"
"    border-right-color: rgba(0, 0, 0, 0.2);\n"
"    border-bottom-color: rgba(0, 0, 0, 0.2);\n"
"	border-radius: 5px;\n"
"}"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/res/set.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btn_set->setIcon(icon3);
        btn_set->setCheckable(true);

        verticalLayout_3->addWidget(btn_set);

        btn_test = new MyHintPushButton(widget_tool);
        btn_test->setObjectName("btn_test");
        sizePolicy1.setHeightForWidth(btn_test->sizePolicy().hasHeightForWidth());
        btn_test->setSizePolicy(sizePolicy1);
        btn_test->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color:rgb(255,255,255);\n"
"	border: 1px solid rgb(255, 255, 255);\n"
"	border-top-color: rgba(255, 255, 255, 0.6);\n"
"    border-left-color: rgba(255, 255, 255, 0.6);\n"
"    border-right-color: rgba(0, 0, 0, 0.2);\n"
"    border-bottom-color: rgba(0, 0, 0, 0.2);\n"
"	border-radius: 5px;\n"
"}\n"
"QPushButton:checked{\n"
"	background-color:rgba(244,234,42,200);\n"
"	border: 1px solid rgba(244, 234, 42, 200);\n"
"	border-top-color: rgba(255, 255, 255, 0.6);\n"
"    border-left-color: rgba(255, 255, 255, 0.6);\n"
"    border-right-color: rgba(0, 0, 0, 0.2);\n"
"    border-bottom-color: rgba(0, 0, 0, 0.2);\n"
"	border-radius: 5px;\n"
"}"));
        btn_test->setCheckable(true);

        verticalLayout_3->addWidget(btn_test);

        verticalLayout_3->setStretch(0, 1);
        verticalLayout_3->setStretch(1, 1);
        verticalLayout_3->setStretch(2, 1);
        verticalLayout_3->setStretch(3, 1);
        verticalLayout_3->setStretch(4, 1);
        verticalLayout_3->setStretch(5, 1);

        verticalLayout->addWidget(widget_tool);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        verticalLayout->setStretch(0, 5);
        verticalLayout->setStretch(1, 1);

        horizontalLayout_3->addLayout(verticalLayout);

        stackedWidget_main = new QStackedWidget(centralwidget);
        stackedWidget_main->setObjectName("stackedWidget_main");
        stackedWidget_main->setStyleSheet(QString::fromUtf8("QScrollArea>QWidget>QWidget{\n"
"	background-color:rgba(42,72,160,80);\n"
"}"));
        page_test = new QWidget();
        page_test->setObjectName("page_test");
        horizontalLayout = new QHBoxLayout(page_test);
        horizontalLayout->setObjectName("horizontalLayout");
        edit = new QLineEdit(page_test);
        edit->setObjectName("edit");

        horizontalLayout->addWidget(edit);

        btn = new QPushButton(page_test);
        btn->setObjectName("btn");

        horizontalLayout->addWidget(btn);

        stackedWidget_main->addWidget(page_test);
        page_friend = new QWidget();
        page_friend->setObjectName("page_friend");
        horizontalLayout_6 = new QHBoxLayout(page_friend);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        scrollArea_friend = new QScrollArea(page_friend);
        scrollArea_friend->setObjectName("scrollArea_friend");
        scrollArea_friend->setWidgetResizable(true);
        scrollAreaWidgetContents_friend = new QWidget();
        scrollAreaWidgetContents_friend->setObjectName("scrollAreaWidgetContents_friend");
        scrollAreaWidgetContents_friend->setGeometry(QRect(0, 0, 229, 580));
        verticalLayout_4 = new QVBoxLayout(scrollAreaWidgetContents_friend);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        edit_seek_friend = new QLineEdit(scrollAreaWidgetContents_friend);
        edit_seek_friend->setObjectName("edit_seek_friend");
        edit_seek_friend->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_5->addWidget(edit_seek_friend);

        btn_seek_friend = new QPushButton(scrollAreaWidgetContents_friend);
        btn_seek_friend->setObjectName("btn_seek_friend");

        horizontalLayout_5->addWidget(btn_seek_friend);


        verticalLayout_4->addLayout(horizontalLayout_5);

        btn_friend_request = new RedPointButton(scrollAreaWidgetContents_friend);
        btn_friend_request->setObjectName("btn_friend_request");

        verticalLayout_4->addWidget(btn_friend_request);

        verticalSpacer_3 = new QSpacerItem(20, 527, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_3);

        scrollArea_friend->setWidget(scrollAreaWidgetContents_friend);

        horizontalLayout_6->addWidget(scrollArea_friend);

        stackedWidget_friend = new QStackedWidget(page_friend);
        stackedWidget_friend->setObjectName("stackedWidget_friend");
        page_seek_result = new QWidget();
        page_seek_result->setObjectName("page_seek_result");
        stackedWidget_friend->addWidget(page_seek_result);
        page_friend_request = new QWidget();
        page_friend_request->setObjectName("page_friend_request");
        verticalLayout_5 = new QVBoxLayout(page_friend_request);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        scrollArea_friend_request = new QScrollArea(page_friend_request);
        scrollArea_friend_request->setObjectName("scrollArea_friend_request");
        scrollArea_friend_request->setWidgetResizable(true);
        scrollAreaWidgetContents_friend_request = new QWidget();
        scrollAreaWidgetContents_friend_request->setObjectName("scrollAreaWidgetContents_friend_request");
        scrollAreaWidgetContents_friend_request->setGeometry(QRect(0, 0, 98, 28));
        verticalLayout_7 = new QVBoxLayout(scrollAreaWidgetContents_friend_request);
        verticalLayout_7->setObjectName("verticalLayout_7");
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        vlayout_friend_request = new QVBoxLayout();
        vlayout_friend_request->setObjectName("vlayout_friend_request");
        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        vlayout_friend_request->addItem(verticalSpacer_4);


        verticalLayout_7->addLayout(vlayout_friend_request);

        scrollArea_friend_request->setWidget(scrollAreaWidgetContents_friend_request);

        verticalLayout_5->addWidget(scrollArea_friend_request);

        stackedWidget_friend->addWidget(page_friend_request);
        page_user_detail = new QWidget();
        page_user_detail->setObjectName("page_user_detail");
        stackedWidget_friend->addWidget(page_user_detail);

        horizontalLayout_6->addWidget(stackedWidget_friend);

        horizontalLayout_6->setStretch(0, 1);
        horizontalLayout_6->setStretch(1, 2);
        stackedWidget_main->addWidget(page_friend);
        page_chat = new QWidget();
        page_chat->setObjectName("page_chat");
        horizontalLayout_2 = new QHBoxLayout(page_chat);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        scrollArea_preview = new QScrollArea(page_chat);
        scrollArea_preview->setObjectName("scrollArea_preview");
        scrollArea_preview->setStyleSheet(QString::fromUtf8(""));
        scrollArea_preview->setWidgetResizable(true);
        scrollAreaWidgetContents_preview = new QWidget();
        scrollAreaWidgetContents_preview->setObjectName("scrollAreaWidgetContents_preview");
        scrollAreaWidgetContents_preview->setGeometry(QRect(0, 0, 229, 580));
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(scrollAreaWidgetContents_preview->sizePolicy().hasHeightForWidth());
        scrollAreaWidgetContents_preview->setSizePolicy(sizePolicy2);
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents_preview);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        edit_seek = new QLineEdit(scrollAreaWidgetContents_preview);
        edit_seek->setObjectName("edit_seek");
        edit_seek->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_4->addWidget(edit_seek);

        btn_seek = new QPushButton(scrollAreaWidgetContents_preview);
        btn_seek->setObjectName("btn_seek");

        horizontalLayout_4->addWidget(btn_seek);


        verticalLayout_2->addLayout(horizontalLayout_4);

        verticalSpacer_2 = new QSpacerItem(20, 527, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        scrollArea_preview->setWidget(scrollAreaWidgetContents_preview);

        horizontalLayout_2->addWidget(scrollArea_preview);

        stackedWidget_chat = new QStackedWidget(page_chat);
        stackedWidget_chat->setObjectName("stackedWidget_chat");
        page_chatwith = new QWidget();
        page_chatwith->setObjectName("page_chatwith");
        stackedWidget_chat->addWidget(page_chatwith);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        stackedWidget_chat->addWidget(page_2);

        horizontalLayout_2->addWidget(stackedWidget_chat);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 2);
        stackedWidget_main->addWidget(page_chat);
        page_set = new QWidget();
        page_set->setObjectName("page_set");
        horizontalLayout_9 = new QHBoxLayout(page_set);
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalLayout_7->setContentsMargins(-1, -1, 0, -1);
        scrollArea_set = new QScrollArea(page_set);
        scrollArea_set->setObjectName("scrollArea_set");
        scrollArea_set->setWidgetResizable(true);
        scrollAreaWidgetContents_set = new QWidget();
        scrollAreaWidgetContents_set->setObjectName("scrollAreaWidgetContents_set");
        scrollAreaWidgetContents_set->setGeometry(QRect(0, 0, 64, 98));
        verticalLayout_10 = new QVBoxLayout(scrollAreaWidgetContents_set);
        verticalLayout_10->setObjectName("verticalLayout_10");
        verticalLayout_10->setContentsMargins(0, 0, 0, 0);
        vl_set = new QVBoxLayout();
        vl_set->setObjectName("vl_set");
        btn_custom = new QPushButton(scrollAreaWidgetContents_set);
        btn_custom->setObjectName("btn_custom");
        btn_custom->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color:rgb(255,255,255);\n"
"	border: 1px solid rgb(255, 255, 255);\n"
"	border-top-color: rgba(255, 255, 255, 0.6);\n"
"    border-left-color: rgba(255, 255, 255, 0.6);\n"
"    border-right-color: rgba(0, 0, 0, 0.2);\n"
"    border-bottom-color: rgba(0, 0, 0, 0.2);\n"
"	border-radius: 5px;\n"
"}\n"
"QPushButton:checked{\n"
"	background-color:rgba(244,234,42,200);\n"
"	border: 1px solid rgba(244, 234, 42, 200);\n"
"	border-top-color: rgba(255, 255, 255, 0.6);\n"
"    border-left-color: rgba(255, 255, 255, 0.6);\n"
"    border-right-color: rgba(0, 0, 0, 0.2);\n"
"    border-bottom-color: rgba(0, 0, 0, 0.2);\n"
"	border-radius: 5px;\n"
"}"));
        btn_custom->setCheckable(true);

        vl_set->addWidget(btn_custom);

        btn_connect = new QPushButton(scrollAreaWidgetContents_set);
        btn_connect->setObjectName("btn_connect");
        btn_connect->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color:rgb(255,255,255);\n"
"	border: 1px solid rgb(255, 255, 255);\n"
"	border-top-color: rgba(255, 255, 255, 0.6);\n"
"    border-left-color: rgba(255, 255, 255, 0.6);\n"
"    border-right-color: rgba(0, 0, 0, 0.2);\n"
"    border-bottom-color: rgba(0, 0, 0, 0.2);\n"
"	border-radius: 5px;\n"
"}\n"
"QPushButton:checked{\n"
"	background-color:rgba(244,234,42,200);\n"
"	border: 1px solid rgba(244, 234, 42, 200);\n"
"	border-top-color: rgba(255, 255, 255, 0.6);\n"
"    border-left-color: rgba(255, 255, 255, 0.6);\n"
"    border-right-color: rgba(0, 0, 0, 0.2);\n"
"    border-bottom-color: rgba(0, 0, 0, 0.2);\n"
"	border-radius: 5px;\n"
"}"));
        btn_connect->setCheckable(true);

        vl_set->addWidget(btn_connect);

        btn_msg = new QPushButton(scrollAreaWidgetContents_set);
        btn_msg->setObjectName("btn_msg");
        btn_msg->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color:rgb(255,255,255);\n"
"	border: 1px solid rgb(255, 255, 255);\n"
"	border-top-color: rgba(255, 255, 255, 0.6);\n"
"    border-left-color: rgba(255, 255, 255, 0.6);\n"
"    border-right-color: rgba(0, 0, 0, 0.2);\n"
"    border-bottom-color: rgba(0, 0, 0, 0.2);\n"
"	border-radius: 5px;\n"
"}\n"
"QPushButton:checked{\n"
"	background-color:rgba(244,234,42,200);\n"
"	border: 1px solid rgba(244, 234, 42, 200);\n"
"	border-top-color: rgba(255, 255, 255, 0.6);\n"
"    border-left-color: rgba(255, 255, 255, 0.6);\n"
"    border-right-color: rgba(0, 0, 0, 0.2);\n"
"    border-bottom-color: rgba(0, 0, 0, 0.2);\n"
"	border-radius: 5px;\n"
"}"));
        btn_msg->setCheckable(true);

        vl_set->addWidget(btn_msg);

        btn_account = new QPushButton(scrollAreaWidgetContents_set);
        btn_account->setObjectName("btn_account");
        btn_account->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color:rgb(255,255,255);\n"
"	border: 1px solid rgb(255, 255, 255);\n"
"	border-top-color: rgba(255, 255, 255, 0.6);\n"
"    border-left-color: rgba(255, 255, 255, 0.6);\n"
"    border-right-color: rgba(0, 0, 0, 0.2);\n"
"    border-bottom-color: rgba(0, 0, 0, 0.2);\n"
"	border-radius: 5px;\n"
"}\n"
"QPushButton:checked{\n"
"	background-color:rgba(244,234,42,200);\n"
"	border: 1px solid rgba(244, 234, 42, 200);\n"
"	border-top-color: rgba(255, 255, 255, 0.6);\n"
"    border-left-color: rgba(255, 255, 255, 0.6);\n"
"    border-right-color: rgba(0, 0, 0, 0.2);\n"
"    border-bottom-color: rgba(0, 0, 0, 0.2);\n"
"	border-radius: 5px;\n"
"}"));
        btn_account->setCheckable(true);

        vl_set->addWidget(btn_account);

        verticalSpacer_7 = new QSpacerItem(20, 408, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        vl_set->addItem(verticalSpacer_7);


        verticalLayout_10->addLayout(vl_set);

        scrollArea_set->setWidget(scrollAreaWidgetContents_set);

        horizontalLayout_7->addWidget(scrollArea_set);

        stacked_set = new QStackedWidget(page_set);
        stacked_set->setObjectName("stacked_set");
        page_set_connect = new QWidget();
        page_set_connect->setObjectName("page_set_connect");
        verticalLayout_13 = new QVBoxLayout(page_set_connect);
        verticalLayout_13->setObjectName("verticalLayout_13");
        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setObjectName("verticalLayout_12");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        label = new QLabel(page_set_connect);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        edit_ip = new QLineEdit(page_set_connect);
        edit_ip->setObjectName("edit_ip");

        formLayout->setWidget(0, QFormLayout::FieldRole, edit_ip);

        label_2 = new QLabel(page_set_connect);
        label_2->setObjectName("label_2");

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        edit_port = new QLineEdit(page_set_connect);
        edit_port->setObjectName("edit_port");

        formLayout->setWidget(1, QFormLayout::FieldRole, edit_port);


        verticalLayout_12->addLayout(formLayout);

        groupBox = new QGroupBox(page_set_connect);
        groupBox->setObjectName("groupBox");
        verticalLayout_11 = new QVBoxLayout(groupBox);
        verticalLayout_11->setObjectName("verticalLayout_11");
        radio_linux = new QRadioButton(groupBox);
        radio_linux->setObjectName("radio_linux");
        radio_linux->setChecked(true);

        verticalLayout_11->addWidget(radio_linux);

        radio_windows = new QRadioButton(groupBox);
        radio_windows->setObjectName("radio_windows");

        verticalLayout_11->addWidget(radio_windows);

        radio_cloud = new QRadioButton(groupBox);
        radio_cloud->setObjectName("radio_cloud");

        verticalLayout_11->addWidget(radio_cloud);

        radio_custom = new QRadioButton(groupBox);
        radio_custom->setObjectName("radio_custom");

        verticalLayout_11->addWidget(radio_custom);


        verticalLayout_12->addWidget(groupBox);


        verticalLayout_13->addLayout(verticalLayout_12);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_3);

        btn_connect_save = new QPushButton(page_set_connect);
        btn_connect_save->setObjectName("btn_connect_save");

        horizontalLayout_11->addWidget(btn_connect_save);

        btn_connect_reset = new QPushButton(page_set_connect);
        btn_connect_reset->setObjectName("btn_connect_reset");

        horizontalLayout_11->addWidget(btn_connect_reset);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_4);


        verticalLayout_13->addLayout(horizontalLayout_11);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer);

        btn_connect_relogin = new QPushButton(page_set_connect);
        btn_connect_relogin->setObjectName("btn_connect_relogin");

        horizontalLayout_10->addWidget(btn_connect_relogin);

        btn_connect_restart = new QPushButton(page_set_connect);
        btn_connect_restart->setObjectName("btn_connect_restart");

        horizontalLayout_10->addWidget(btn_connect_restart);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_2);


        verticalLayout_13->addLayout(horizontalLayout_10);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_13->addItem(verticalSpacer_8);

        stacked_set->addWidget(page_set_connect);
        page_set_custom = new QWidget();
        page_set_custom->setObjectName("page_set_custom");
        stacked_set->addWidget(page_set_custom);
        page_set_account = new QWidget();
        page_set_account->setObjectName("page_set_account");
        verticalLayout_15 = new QVBoxLayout(page_set_account);
        verticalLayout_15->setObjectName("verticalLayout_15");
        groupBox_2 = new QGroupBox(page_set_account);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setFlat(false);
        groupBox_2->setCheckable(false);
        verticalLayout_14 = new QVBoxLayout(groupBox_2);
        verticalLayout_14->setObjectName("verticalLayout_14");
        radio_seek_by_id = new QRadioButton(groupBox_2);
        radio_seek_by_id->setObjectName("radio_seek_by_id");
        radio_seek_by_id->setChecked(true);
        radio_seek_by_id->setAutoExclusive(false);

        verticalLayout_14->addWidget(radio_seek_by_id);

        radio_seek_by_nickname = new QRadioButton(groupBox_2);
        radio_seek_by_nickname->setObjectName("radio_seek_by_nickname");
        radio_seek_by_nickname->setChecked(true);
        radio_seek_by_nickname->setAutoExclusive(false);

        verticalLayout_14->addWidget(radio_seek_by_nickname);

        radio_seek_by_rand = new QRadioButton(groupBox_2);
        radio_seek_by_rand->setObjectName("radio_seek_by_rand");
        radio_seek_by_rand->setChecked(true);
        radio_seek_by_rand->setAutoExclusive(false);

        verticalLayout_14->addWidget(radio_seek_by_rand);

        radio_seek_by_noway = new QRadioButton(groupBox_2);
        radio_seek_by_noway->setObjectName("radio_seek_by_noway");
        radio_seek_by_noway->setAutoExclusive(false);

        verticalLayout_14->addWidget(radio_seek_by_noway);


        verticalLayout_15->addWidget(groupBox_2);

        checkBox_likes = new QCheckBox(page_set_account);
        checkBox_likes->setObjectName("checkBox_likes");

        verticalLayout_15->addWidget(checkBox_likes);

        checkBox_group = new QCheckBox(page_set_account);
        checkBox_group->setObjectName("checkBox_group");

        verticalLayout_15->addWidget(checkBox_group);

        btn_update_password = new QPushButton(page_set_account);
        btn_update_password->setObjectName("btn_update_password");

        verticalLayout_15->addWidget(btn_update_password);

        btn_logout = new QPushButton(page_set_account);
        btn_logout->setObjectName("btn_logout");

        verticalLayout_15->addWidget(btn_logout);

        verticalSpacer_9 = new QSpacerItem(20, 289, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_15->addItem(verticalSpacer_9);

        stacked_set->addWidget(page_set_account);
        page_set_msg = new QWidget();
        page_set_msg->setObjectName("page_set_msg");
        stacked_set->addWidget(page_set_msg);
        page_set_null = new QWidget();
        page_set_null->setObjectName("page_set_null");
        stacked_set->addWidget(page_set_null);

        horizontalLayout_7->addWidget(stacked_set);

        horizontalLayout_7->setStretch(0, 1);
        horizontalLayout_7->setStretch(1, 2);

        horizontalLayout_9->addLayout(horizontalLayout_7);

        stackedWidget_main->addWidget(page_set);
        page_group = new QWidget();
        page_group->setObjectName("page_group");
        layoutWidget = new QWidget(page_group);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(0, 0, 701, 581));
        vl_group = new QHBoxLayout(layoutWidget);
        vl_group->setObjectName("vl_group");
        vl_group->setContentsMargins(0, 0, 0, 0);
        scrollArea_group = new QScrollArea(layoutWidget);
        scrollArea_group->setObjectName("scrollArea_group");
        scrollArea_group->setWidgetResizable(true);
        scrollAreaWidgetContents_group = new QWidget();
        scrollAreaWidgetContents_group->setObjectName("scrollAreaWidgetContents_group");
        scrollAreaWidgetContents_group->setGeometry(QRect(0, 0, 229, 577));
        verticalLayout_6 = new QVBoxLayout(scrollAreaWidgetContents_group);
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        edit_seek_group = new QLineEdit(scrollAreaWidgetContents_group);
        edit_seek_group->setObjectName("edit_seek_group");
        edit_seek_group->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_8->addWidget(edit_seek_group);

        btn_seek_group = new QPushButton(scrollAreaWidgetContents_group);
        btn_seek_group->setObjectName("btn_seek_group");

        horizontalLayout_8->addWidget(btn_seek_group);


        verticalLayout_6->addLayout(horizontalLayout_8);

        btn_create_group = new QPushButton(scrollAreaWidgetContents_group);
        btn_create_group->setObjectName("btn_create_group");

        verticalLayout_6->addWidget(btn_create_group);

        verticalSpacer_5 = new QSpacerItem(20, 527, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_5);

        scrollArea_group->setWidget(scrollAreaWidgetContents_group);

        vl_group->addWidget(scrollArea_group);

        stackedWidget_group = new QStackedWidget(layoutWidget);
        stackedWidget_group->setObjectName("stackedWidget_group");
        page_seek_result_2 = new QWidget();
        page_seek_result_2->setObjectName("page_seek_result_2");
        stackedWidget_group->addWidget(page_seek_result_2);
        page_friend_request_2 = new QWidget();
        page_friend_request_2->setObjectName("page_friend_request_2");
        verticalLayout_8 = new QVBoxLayout(page_friend_request_2);
        verticalLayout_8->setObjectName("verticalLayout_8");
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        scrollArea_friend_request_2 = new QScrollArea(page_friend_request_2);
        scrollArea_friend_request_2->setObjectName("scrollArea_friend_request_2");
        scrollArea_friend_request_2->setWidgetResizable(true);
        scrollAreaWidgetContents_friend_request_2 = new QWidget();
        scrollAreaWidgetContents_friend_request_2->setObjectName("scrollAreaWidgetContents_friend_request_2");
        scrollAreaWidgetContents_friend_request_2->setGeometry(QRect(0, 0, 98, 28));
        verticalLayout_9 = new QVBoxLayout(scrollAreaWidgetContents_friend_request_2);
        verticalLayout_9->setObjectName("verticalLayout_9");
        verticalLayout_9->setContentsMargins(0, 0, 0, 0);
        vlayout_friend_request_2 = new QVBoxLayout();
        vlayout_friend_request_2->setObjectName("vlayout_friend_request_2");
        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        vlayout_friend_request_2->addItem(verticalSpacer_6);


        verticalLayout_9->addLayout(vlayout_friend_request_2);

        scrollArea_friend_request_2->setWidget(scrollAreaWidgetContents_friend_request_2);

        verticalLayout_8->addWidget(scrollArea_friend_request_2);

        stackedWidget_group->addWidget(page_friend_request_2);
        page_group_detail = new QWidget();
        page_group_detail->setObjectName("page_group_detail");
        widget = new QWidget(page_group_detail);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(90, 150, 120, 80));
        stackedWidget_group->addWidget(page_group_detail);

        vl_group->addWidget(stackedWidget_group);

        vl_group->setStretch(0, 1);
        vl_group->setStretch(1, 2);
        stackedWidget_main->addWidget(page_group);

        horizontalLayout_3->addWidget(stackedWidget_main);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 9);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        stackedWidget_main->setCurrentIndex(4);
        stacked_set->setCurrentIndex(0);
        stackedWidget_group->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        btn_user->setText(QString());
#if QT_CONFIG(tooltip)
        btn_chat->setToolTip(QCoreApplication::translate("MainWindow", "\350\201\212\345\244\251", nullptr));
#endif // QT_CONFIG(tooltip)
        btn_chat->setText(QString());
#if QT_CONFIG(tooltip)
        btn_friend->setToolTip(QCoreApplication::translate("MainWindow", "\345\245\275\345\217\213", nullptr));
#endif // QT_CONFIG(tooltip)
        btn_friend->setText(QString());
#if QT_CONFIG(tooltip)
        btn_group->setToolTip(QCoreApplication::translate("MainWindow", "\347\276\244\350\201\212", nullptr));
#endif // QT_CONFIG(tooltip)
        btn_group->setText(QString());
#if QT_CONFIG(tooltip)
        btn_set->setToolTip(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256", nullptr));
#endif // QT_CONFIG(tooltip)
        btn_set->setText(QString());
#if QT_CONFIG(tooltip)
        btn_test->setToolTip(QCoreApplication::translate("MainWindow", "\346\265\213\350\257\225", nullptr));
#endif // QT_CONFIG(tooltip)
        btn_test->setText(QCoreApplication::translate("MainWindow", "\346\265\213\350\257\225", nullptr));
        btn->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
        edit_seek_friend->setPlaceholderText(QCoreApplication::translate("MainWindow", "\346\220\234\347\264\242\345\245\275\345\217\213id", nullptr));
        btn_seek_friend->setText(QCoreApplication::translate("MainWindow", "\346\220\234\347\264\242", nullptr));
        btn_friend_request->setText(QCoreApplication::translate("MainWindow", "\345\245\275\345\217\213\347\224\263\350\257\267", nullptr));
        edit_seek->setPlaceholderText(QCoreApplication::translate("MainWindow", "\346\220\234\347\264\242\345\216\206\345\217\262\350\256\260\345\275\225", nullptr));
        btn_seek->setText(QCoreApplication::translate("MainWindow", "\346\220\234\347\264\242", nullptr));
        btn_custom->setText(QCoreApplication::translate("MainWindow", "\344\270\252\346\200\247\345\214\226\350\256\276\347\275\256", nullptr));
        btn_connect->setText(QCoreApplication::translate("MainWindow", "\346\234\215\345\212\241\345\231\250", nullptr));
        btn_msg->setText(QCoreApplication::translate("MainWindow", "\346\266\210\346\201\257\350\256\276\347\275\256", nullptr));
        btn_account->setText(QCoreApplication::translate("MainWindow", "\350\264\246\345\217\267\344\270\216\345\256\211\345\205\250", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\346\234\215\345\212\241\345\231\250ip\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\347\253\257\345\217\243\357\274\232", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\346\234\215\345\212\241\345\231\250\350\277\236\346\216\245\347\261\273\345\236\213\357\274\232", nullptr));
        radio_linux->setText(QCoreApplication::translate("MainWindow", "\346\234\254\345\234\260Linux(Ubuntu)", nullptr));
        radio_windows->setText(QCoreApplication::translate("MainWindow", "\346\234\254\345\234\260Windows", nullptr));
        radio_cloud->setText(QCoreApplication::translate("MainWindow", "\351\230\277\351\207\214\344\272\221\346\234\215\345\212\241\345\231\250", nullptr));
        radio_custom->setText(QCoreApplication::translate("MainWindow", "\350\207\252\345\256\232\344\271\211(\344\273\205\346\265\213\350\257\225\347\224\250\357\274\211", nullptr));
        btn_connect_save->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230", nullptr));
        btn_connect_reset->setText(QCoreApplication::translate("MainWindow", "\351\207\215\347\275\256", nullptr));
        btn_connect_relogin->setText(QCoreApplication::translate("MainWindow", "\351\207\215\346\226\260\347\231\273\345\275\225", nullptr));
        btn_connect_restart->setText(QCoreApplication::translate("MainWindow", "\351\207\215\345\220\257\345\272\224\347\224\250", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "\345\205\201\350\256\270\350\242\253\345\217\221\347\216\260\347\232\204\346\226\271\345\274\217", nullptr));
        radio_seek_by_id->setText(QCoreApplication::translate("MainWindow", "\351\200\232\350\277\207id\346\237\245\346\211\276", nullptr));
        radio_seek_by_nickname->setText(QCoreApplication::translate("MainWindow", "\351\200\232\350\277\207\346\230\265\347\247\260\346\237\245\346\211\276", nullptr));
        radio_seek_by_rand->setText(QCoreApplication::translate("MainWindow", "\351\200\232\350\277\207\346\211\251\345\210\227\345\212\237\350\203\275\346\237\245\346\211\276", nullptr));
        radio_seek_by_noway->setText(QCoreApplication::translate("MainWindow", "\344\270\215\345\205\201\350\256\270\350\242\253\344\273\273\344\275\225\346\226\271\345\274\217\346\211\276\345\210\260", nullptr));
        checkBox_likes->setText(QCoreApplication::translate("MainWindow", "\345\261\225\347\244\272\346\210\221\347\232\204\350\242\253\347\202\271\350\265\236\346\225\260", nullptr));
        checkBox_group->setText(QCoreApplication::translate("MainWindow", "\345\205\201\350\256\270\350\242\253\345\245\275\345\217\213\346\213\211\350\277\233\347\276\244\350\201\212", nullptr));
        btn_update_password->setText(QCoreApplication::translate("MainWindow", "\346\233\264\346\224\271\345\257\206\347\240\201", nullptr));
        btn_logout->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272\347\231\273\345\275\225", nullptr));
        edit_seek_group->setPlaceholderText(QCoreApplication::translate("MainWindow", "\346\220\234\347\264\242\347\276\244\350\201\212", nullptr));
        btn_seek_group->setText(QCoreApplication::translate("MainWindow", "\346\220\234\347\264\242", nullptr));
        btn_create_group->setText(QCoreApplication::translate("MainWindow", "\345\210\233\345\273\272\346\226\260\347\232\204\347\276\244\350\201\212", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

/********************************************************************************
** Form generated from reading UI file 'chatwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATWIDGET_H
#define UI_CHATWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "chatview.h"
#include "myhintpushbutton.h"

QT_BEGIN_NAMESPACE

class Ui_ChatWidget
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_nickname;
    QSpacerItem *horizontalSpacer_3;
    MyHintPushButton *btn_refresh;
    MyHintPushButton *btn_delete;
    QScrollArea *scrollArea_history;
    QWidget *scrollAreaWidgetContents_history;
    QVBoxLayout *verticalLayout_4;
    ChatView *chat_view;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    MyHintPushButton *btn_emo;
    MyHintPushButton *btn_picture;
    MyHintPushButton *btn_file;
    MyHintPushButton *btn_call;
    QSpacerItem *horizontalSpacer_2;
    MyHintPushButton *btn_more;
    QScrollArea *scrollArea_send;
    QWidget *scrollAreaWidgetContents_send;
    QVBoxLayout *verticalLayout_3;
    QPlainTextEdit *edit_send;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout;
    QPushButton *btn_send;
    QPushButton *btn_send_mod;

    void setupUi(QWidget *ChatWidget)
    {
        if (ChatWidget->objectName().isEmpty())
            ChatWidget->setObjectName("ChatWidget");
        ChatWidget->resize(447, 570);
        verticalLayout_2 = new QVBoxLayout(ChatWidget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_nickname = new QLabel(ChatWidget);
        label_nickname->setObjectName("label_nickname");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_nickname->sizePolicy().hasHeightForWidth());
        label_nickname->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(label_nickname);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        btn_refresh = new MyHintPushButton(ChatWidget);
        btn_refresh->setObjectName("btn_refresh");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/res/refresh.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btn_refresh->setIcon(icon);
        btn_refresh->setIconSize(QSize(16, 16));

        horizontalLayout_4->addWidget(btn_refresh);

        btn_delete = new MyHintPushButton(ChatWidget);
        btn_delete->setObjectName("btn_delete");

        horizontalLayout_4->addWidget(btn_delete);


        verticalLayout_2->addLayout(horizontalLayout_4);

        scrollArea_history = new QScrollArea(ChatWidget);
        scrollArea_history->setObjectName("scrollArea_history");
        scrollArea_history->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOn);
        scrollArea_history->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        scrollArea_history->setWidgetResizable(true);
        scrollAreaWidgetContents_history = new QWidget();
        scrollAreaWidgetContents_history->setObjectName("scrollAreaWidgetContents_history");
        scrollAreaWidgetContents_history->setGeometry(QRect(0, 0, 431, 416));
        verticalLayout_4 = new QVBoxLayout(scrollAreaWidgetContents_history);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        chat_view = new ChatView(scrollAreaWidgetContents_history);
        chat_view->setObjectName("chat_view");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(chat_view->sizePolicy().hasHeightForWidth());
        chat_view->setSizePolicy(sizePolicy1);

        verticalLayout_4->addWidget(chat_view);

        scrollArea_history->setWidget(scrollAreaWidgetContents_history);

        verticalLayout_2->addWidget(scrollArea_history);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        btn_emo = new MyHintPushButton(ChatWidget);
        btn_emo->setObjectName("btn_emo");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/res/emo.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btn_emo->setIcon(icon1);

        horizontalLayout_3->addWidget(btn_emo);

        btn_picture = new MyHintPushButton(ChatWidget);
        btn_picture->setObjectName("btn_picture");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/res/picture.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btn_picture->setIcon(icon2);

        horizontalLayout_3->addWidget(btn_picture);

        btn_file = new MyHintPushButton(ChatWidget);
        btn_file->setObjectName("btn_file");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/res/file.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btn_file->setIcon(icon3);

        horizontalLayout_3->addWidget(btn_file);

        btn_call = new MyHintPushButton(ChatWidget);
        btn_call->setObjectName("btn_call");
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/res/call.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btn_call->setIcon(icon4);

        horizontalLayout_3->addWidget(btn_call);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        btn_more = new MyHintPushButton(ChatWidget);
        btn_more->setObjectName("btn_more");
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/res/more.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btn_more->setIcon(icon5);

        horizontalLayout_3->addWidget(btn_more);


        verticalLayout->addLayout(horizontalLayout_3);

        scrollArea_send = new QScrollArea(ChatWidget);
        scrollArea_send->setObjectName("scrollArea_send");
        scrollArea_send->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        scrollArea_send->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        scrollArea_send->setWidgetResizable(true);
        scrollAreaWidgetContents_send = new QWidget();
        scrollAreaWidgetContents_send->setObjectName("scrollAreaWidgetContents_send");
        scrollAreaWidgetContents_send->setGeometry(QRect(0, 0, 443, 68));
        verticalLayout_3 = new QVBoxLayout(scrollAreaWidgetContents_send);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        edit_send = new QPlainTextEdit(scrollAreaWidgetContents_send);
        edit_send->setObjectName("edit_send");
        edit_send->setStyleSheet(QString::fromUtf8("QPlainTextEdit{\n"
"	border:none;\n"
"}"));

        verticalLayout_3->addWidget(edit_send);

        scrollArea_send->setWidget(scrollAreaWidgetContents_send);

        verticalLayout->addWidget(scrollArea_send);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        btn_send = new QPushButton(ChatWidget);
        btn_send->setObjectName("btn_send");
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/res/send.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btn_send->setIcon(icon6);

        horizontalLayout->addWidget(btn_send);

        btn_send_mod = new QPushButton(ChatWidget);
        btn_send_mod->setObjectName("btn_send_mod");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(btn_send_mod->sizePolicy().hasHeightForWidth());
        btn_send_mod->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(btn_send_mod);

        horizontalLayout->setStretch(0, 5);
        horizontalLayout->setStretch(1, 1);

        horizontalLayout_2->addLayout(horizontalLayout);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(verticalLayout);

        verticalLayout_2->setStretch(1, 4);
        verticalLayout_2->setStretch(2, 1);

        retranslateUi(ChatWidget);

        QMetaObject::connectSlotsByName(ChatWidget);
    } // setupUi

    void retranslateUi(QWidget *ChatWidget)
    {
        ChatWidget->setWindowTitle(QCoreApplication::translate("ChatWidget", "Form", nullptr));
        label_nickname->setText(QCoreApplication::translate("ChatWidget", "\346\230\265\347\247\260", nullptr));
        btn_refresh->setText(QString());
        btn_delete->setText(QCoreApplication::translate("ChatWidget", "\303\227", nullptr));
        btn_emo->setText(QString());
        btn_picture->setText(QString());
        btn_file->setText(QString());
        btn_call->setText(QString());
        btn_more->setText(QString());
        btn_send->setText(QCoreApplication::translate("ChatWidget", "\345\217\221\351\200\201", nullptr));
        btn_send_mod->setText(QCoreApplication::translate("ChatWidget", "\342\206\223", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChatWidget: public Ui_ChatWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATWIDGET_H

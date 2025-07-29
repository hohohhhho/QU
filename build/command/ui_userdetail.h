/********************************************************************************
** Form generated from reading UI file 'userdetail.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERDETAIL_H
#define UI_USERDETAIL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "myhintpushbutton.h"
#include "profile.h"

QT_BEGIN_NAMESPACE

class Ui_UserDetail
{
public:
    QVBoxLayout *verticalLayout_6;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_4;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_2;
    Profile *btn_prefile;
    QSpacerItem *verticalSpacer_2;
    QStackedWidget *stacked_user_info;
    QWidget *page_read;
    QVBoxLayout *verticalLayout_3;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QLabel *label_nickname;
    QLabel *label_id;
    QLabel *label_state;
    QWidget *page_write;
    QVBoxLayout *verticalLayout_5;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_4;
    QLineEdit *edit_nickname;
    QLineEdit *edit_id;
    QLineEdit *edit_state;
    MyHintPushButton *btn_like;
    QStackedWidget *stacked_btn;
    QWidget *page_normal;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btn_left;
    QPushButton *btn_chat;
    QSpacerItem *horizontalSpacer_2;
    QWidget *page_edit;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btn_save;
    QPushButton *btn_cancel;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *UserDetail)
    {
        if (UserDetail->objectName().isEmpty())
            UserDetail->setObjectName("UserDetail");
        UserDetail->resize(447, 570);
        verticalLayout_6 = new QVBoxLayout(UserDetail);
        verticalLayout_6->setObjectName("verticalLayout_6");
        widget_4 = new QWidget(UserDetail);
        widget_4->setObjectName("widget_4");
        horizontalLayout_4 = new QHBoxLayout(widget_4);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        widget_2 = new QWidget(widget_4);
        widget_2->setObjectName("widget_2");
        verticalLayout_2 = new QVBoxLayout(widget_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        btn_prefile = new Profile(widget_2);
        btn_prefile->setObjectName("btn_prefile");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btn_prefile->sizePolicy().hasHeightForWidth());
        btn_prefile->setSizePolicy(sizePolicy);
        btn_prefile->setMinimumSize(QSize(128, 128));
        btn_prefile->setMaximumSize(QSize(64, 64));

        verticalLayout_2->addWidget(btn_prefile);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        horizontalLayout_4->addWidget(widget_2);

        stacked_user_info = new QStackedWidget(widget_4);
        stacked_user_info->setObjectName("stacked_user_info");
        stacked_user_info->setMinimumSize(QSize(0, 0));
        page_read = new QWidget();
        page_read->setObjectName("page_read");
        verticalLayout_3 = new QVBoxLayout(page_read);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(page_read);
        widget->setObjectName("widget");
        widget->setMinimumSize(QSize(0, 0));
        widget->setMaximumSize(QSize(16777215, 16777215));
        horizontalLayout_3 = new QHBoxLayout(widget);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label_nickname = new QLabel(widget);
        label_nickname->setObjectName("label_nickname");

        verticalLayout->addWidget(label_nickname);

        label_id = new QLabel(widget);
        label_id->setObjectName("label_id");

        verticalLayout->addWidget(label_id);

        label_state = new QLabel(widget);
        label_state->setObjectName("label_state");

        verticalLayout->addWidget(label_state);


        horizontalLayout_3->addLayout(verticalLayout);


        verticalLayout_3->addWidget(widget);

        stacked_user_info->addWidget(page_read);
        page_write = new QWidget();
        page_write->setObjectName("page_write");
        verticalLayout_5 = new QVBoxLayout(page_write);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        widget_3 = new QWidget(page_write);
        widget_3->setObjectName("widget_3");
        verticalLayout_4 = new QVBoxLayout(widget_3);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        edit_nickname = new QLineEdit(widget_3);
        edit_nickname->setObjectName("edit_nickname");

        verticalLayout_4->addWidget(edit_nickname);

        edit_id = new QLineEdit(widget_3);
        edit_id->setObjectName("edit_id");
        edit_id->setReadOnly(true);

        verticalLayout_4->addWidget(edit_id);

        edit_state = new QLineEdit(widget_3);
        edit_state->setObjectName("edit_state");

        verticalLayout_4->addWidget(edit_state);

        verticalLayout_4->setStretch(0, 1);
        verticalLayout_4->setStretch(1, 1);
        verticalLayout_4->setStretch(2, 1);

        verticalLayout_5->addWidget(widget_3);

        stacked_user_info->addWidget(page_write);

        horizontalLayout_4->addWidget(stacked_user_info);

        btn_like = new MyHintPushButton(widget_4);
        btn_like->setObjectName("btn_like");
        sizePolicy.setHeightForWidth(btn_like->sizePolicy().hasHeightForWidth());
        btn_like->setSizePolicy(sizePolicy);
        btn_like->setMinimumSize(QSize(64, 64));
        btn_like->setMaximumSize(QSize(32, 32));

        horizontalLayout_4->addWidget(btn_like);


        verticalLayout_6->addWidget(widget_4);

        stacked_btn = new QStackedWidget(UserDetail);
        stacked_btn->setObjectName("stacked_btn");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Ignored);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(stacked_btn->sizePolicy().hasHeightForWidth());
        stacked_btn->setSizePolicy(sizePolicy1);
        page_normal = new QWidget();
        page_normal->setObjectName("page_normal");
        horizontalLayout = new QHBoxLayout(page_normal);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btn_left = new QPushButton(page_normal);
        btn_left->setObjectName("btn_left");

        horizontalLayout->addWidget(btn_left);

        btn_chat = new QPushButton(page_normal);
        btn_chat->setObjectName("btn_chat");

        horizontalLayout->addWidget(btn_chat);

        horizontalSpacer_2 = new QSpacerItem(58, 21, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        stacked_btn->addWidget(page_normal);
        page_edit = new QWidget();
        page_edit->setObjectName("page_edit");
        horizontalLayout_5 = new QHBoxLayout(page_edit);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalSpacer_3 = new QSpacerItem(114, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);

        btn_save = new QPushButton(page_edit);
        btn_save->setObjectName("btn_save");

        horizontalLayout_5->addWidget(btn_save);

        btn_cancel = new QPushButton(page_edit);
        btn_cancel->setObjectName("btn_cancel");

        horizontalLayout_5->addWidget(btn_cancel);

        horizontalSpacer_4 = new QSpacerItem(113, 21, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);

        stacked_btn->addWidget(page_edit);

        verticalLayout_6->addWidget(stacked_btn);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_6->addItem(verticalSpacer);

        verticalLayout_6->setStretch(0, 6);
        verticalLayout_6->setStretch(1, 2);
        verticalLayout_6->setStretch(2, 9);

        retranslateUi(UserDetail);

        stacked_user_info->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(UserDetail);
    } // setupUi

    void retranslateUi(QWidget *UserDetail)
    {
        UserDetail->setWindowTitle(QCoreApplication::translate("UserDetail", "Form", nullptr));
        btn_prefile->setText(QString());
        label_nickname->setText(QCoreApplication::translate("UserDetail", "\346\230\265\347\247\260", nullptr));
        label_id->setText(QCoreApplication::translate("UserDetail", "id", nullptr));
        label_state->setText(QCoreApplication::translate("UserDetail", "\345\234\250\347\272\277", nullptr));
        edit_nickname->setPlaceholderText(QCoreApplication::translate("UserDetail", "\346\230\265\347\247\260", nullptr));
        edit_id->setPlaceholderText(QCoreApplication::translate("UserDetail", "id", nullptr));
        edit_state->setPlaceholderText(QCoreApplication::translate("UserDetail", "\347\212\266\346\200\201", nullptr));
        btn_like->setText(QCoreApplication::translate("UserDetail", "\347\202\271\350\265\236", nullptr));
        btn_left->setText(QCoreApplication::translate("UserDetail", "\346\267\273\345\212\240\345\245\275\345\217\213", nullptr));
        btn_chat->setText(QCoreApplication::translate("UserDetail", "\345\217\221\351\200\201\346\266\210\346\201\257", nullptr));
        btn_save->setText(QCoreApplication::translate("UserDetail", "\344\277\235\345\255\230", nullptr));
        btn_cancel->setText(QCoreApplication::translate("UserDetail", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserDetail: public Ui_UserDetail {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERDETAIL_H

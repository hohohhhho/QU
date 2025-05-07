/********************************************************************************
** Form generated from reading UI file 'loginwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWIDGET_H
#define UI_LOGINWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWidget
{
public:
    QHBoxLayout *horizontalLayout_6;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QHBoxLayout *horizontalLayout_3;
    QWidget *widget_login;
    QVBoxLayout *verticalLayout;
    QLineEdit *edit_account;
    QHBoxLayout *horizontalLayout;
    QLineEdit *edit_password;
    QPushButton *btn_password;
    QPushButton *btn_login;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *btn_set;
    QPushButton *btn_toregister;
    QWidget *widget_register;
    QVBoxLayout *verticalLayout_3;
    QLineEdit *edit_account_register;
    QLabel *label_account;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *edit_password_register;
    QPushButton *btn_password_register;
    QLabel *label_password;
    QPushButton *btn_register;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *btn_tologin;
    QPushButton *btn_set_2;

    void setupUi(QWidget *LoginWidget)
    {
        if (LoginWidget->objectName().isEmpty())
            LoginWidget->setObjectName("LoginWidget");
        LoginWidget->resize(270, 270);
        LoginWidget->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_6 = new QHBoxLayout(LoginWidget);
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        scrollArea = new QScrollArea(LoginWidget);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 250, 250));
        horizontalLayout_3 = new QHBoxLayout(scrollAreaWidgetContents);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        widget_login = new QWidget(scrollAreaWidgetContents);
        widget_login->setObjectName("widget_login");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget_login->sizePolicy().hasHeightForWidth());
        widget_login->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(widget_login);
        verticalLayout->setSpacing(9);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        edit_account = new QLineEdit(widget_login);
        edit_account->setObjectName("edit_account");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(edit_account->sizePolicy().hasHeightForWidth());
        edit_account->setSizePolicy(sizePolicy1);
        edit_account->setMaxLength(12);
        edit_account->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(edit_account);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName("horizontalLayout");
        edit_password = new QLineEdit(widget_login);
        edit_password->setObjectName("edit_password");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);
        sizePolicy2.setHorizontalStretch(50);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(edit_password->sizePolicy().hasHeightForWidth());
        edit_password->setSizePolicy(sizePolicy2);
        edit_password->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout->addWidget(edit_password);

        btn_password = new QPushButton(widget_login);
        btn_password->setObjectName("btn_password");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Minimum);
        sizePolicy3.setHorizontalStretch(20);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(btn_password->sizePolicy().hasHeightForWidth());
        btn_password->setSizePolicy(sizePolicy3);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/res/eye_open.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        icon.addFile(QString::fromUtf8(":/res/eye_close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::On);
        btn_password->setIcon(icon);
        btn_password->setIconSize(QSize(48, 48));
        btn_password->setCheckable(true);

        horizontalLayout->addWidget(btn_password);

        horizontalLayout->setStretch(0, 4);
        horizontalLayout->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout);

        btn_login = new QPushButton(widget_login);
        btn_login->setObjectName("btn_login");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(btn_login->sizePolicy().hasHeightForWidth());
        btn_login->setSizePolicy(sizePolicy4);

        verticalLayout->addWidget(btn_login);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        btn_set = new QPushButton(widget_login);
        btn_set->setObjectName("btn_set");
        QSizePolicy sizePolicy5(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Ignored);
        sizePolicy5.setHorizontalStretch(20);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(btn_set->sizePolicy().hasHeightForWidth());
        btn_set->setSizePolicy(sizePolicy5);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/res/set.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btn_set->setIcon(icon1);
        btn_set->setIconSize(QSize(16, 16));
        btn_set->setCheckable(false);

        horizontalLayout_4->addWidget(btn_set);

        btn_toregister = new QPushButton(widget_login);
        btn_toregister->setObjectName("btn_toregister");
        sizePolicy4.setHeightForWidth(btn_toregister->sizePolicy().hasHeightForWidth());
        btn_toregister->setSizePolicy(sizePolicy4);

        horizontalLayout_4->addWidget(btn_toregister);

        horizontalLayout_4->setStretch(0, 1);
        horizontalLayout_4->setStretch(1, 9);

        verticalLayout->addLayout(horizontalLayout_4);

        verticalLayout->setStretch(0, 3);
        verticalLayout->setStretch(1, 3);
        verticalLayout->setStretch(2, 2);
        verticalLayout->setStretch(3, 1);

        horizontalLayout_3->addWidget(widget_login);

        widget_register = new QWidget(scrollAreaWidgetContents);
        widget_register->setObjectName("widget_register");
        sizePolicy.setHeightForWidth(widget_register->sizePolicy().hasHeightForWidth());
        widget_register->setSizePolicy(sizePolicy);
        verticalLayout_3 = new QVBoxLayout(widget_register);
        verticalLayout_3->setSpacing(9);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        edit_account_register = new QLineEdit(widget_register);
        edit_account_register->setObjectName("edit_account_register");
        sizePolicy1.setHeightForWidth(edit_account_register->sizePolicy().hasHeightForWidth());
        edit_account_register->setSizePolicy(sizePolicy1);
        edit_account_register->setMaxLength(12);
        edit_account_register->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_3->addWidget(edit_account_register);

        label_account = new QLabel(widget_register);
        label_account->setObjectName("label_account");

        verticalLayout_3->addWidget(label_account);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        edit_password_register = new QLineEdit(widget_register);
        edit_password_register->setObjectName("edit_password_register");
        sizePolicy2.setHeightForWidth(edit_password_register->sizePolicy().hasHeightForWidth());
        edit_password_register->setSizePolicy(sizePolicy2);
        edit_password_register->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_2->addWidget(edit_password_register);

        btn_password_register = new QPushButton(widget_register);
        btn_password_register->setObjectName("btn_password_register");
        sizePolicy3.setHeightForWidth(btn_password_register->sizePolicy().hasHeightForWidth());
        btn_password_register->setSizePolicy(sizePolicy3);
        btn_password_register->setIcon(icon);
        btn_password_register->setIconSize(QSize(48, 48));
        btn_password_register->setCheckable(true);

        horizontalLayout_2->addWidget(btn_password_register);

        horizontalLayout_2->setStretch(0, 4);
        horizontalLayout_2->setStretch(1, 1);

        verticalLayout_3->addLayout(horizontalLayout_2);

        label_password = new QLabel(widget_register);
        label_password->setObjectName("label_password");

        verticalLayout_3->addWidget(label_password);

        btn_register = new QPushButton(widget_register);
        btn_register->setObjectName("btn_register");
        sizePolicy4.setHeightForWidth(btn_register->sizePolicy().hasHeightForWidth());
        btn_register->setSizePolicy(sizePolicy4);

        verticalLayout_3->addWidget(btn_register);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        btn_tologin = new QPushButton(widget_register);
        btn_tologin->setObjectName("btn_tologin");
        sizePolicy4.setHeightForWidth(btn_tologin->sizePolicy().hasHeightForWidth());
        btn_tologin->setSizePolicy(sizePolicy4);

        horizontalLayout_5->addWidget(btn_tologin);

        btn_set_2 = new QPushButton(widget_register);
        btn_set_2->setObjectName("btn_set_2");
        sizePolicy5.setHeightForWidth(btn_set_2->sizePolicy().hasHeightForWidth());
        btn_set_2->setSizePolicy(sizePolicy5);
        btn_set_2->setIcon(icon1);
        btn_set_2->setIconSize(QSize(16, 16));
        btn_set_2->setCheckable(false);

        horizontalLayout_5->addWidget(btn_set_2);

        horizontalLayout_5->setStretch(0, 9);
        horizontalLayout_5->setStretch(1, 1);

        verticalLayout_3->addLayout(horizontalLayout_5);

        verticalLayout_3->setStretch(0, 3);
        verticalLayout_3->setStretch(2, 3);
        verticalLayout_3->setStretch(4, 2);

        horizontalLayout_3->addWidget(widget_register);

        scrollArea->setWidget(scrollAreaWidgetContents);

        horizontalLayout_6->addWidget(scrollArea);


        retranslateUi(LoginWidget);

        QMetaObject::connectSlotsByName(LoginWidget);
    } // setupUi

    void retranslateUi(QWidget *LoginWidget)
    {
        LoginWidget->setWindowTitle(QCoreApplication::translate("LoginWidget", "LoginWidget", nullptr));
        edit_account->setText(QString());
        edit_account->setPlaceholderText(QCoreApplication::translate("LoginWidget", "\350\264\246\345\217\267", nullptr));
        edit_password->setText(QString());
        edit_password->setPlaceholderText(QCoreApplication::translate("LoginWidget", "\345\257\206\347\240\201", nullptr));
        btn_password->setText(QString());
        btn_login->setText(QCoreApplication::translate("LoginWidget", "\347\231\273\345\275\225", nullptr));
        btn_set->setText(QString());
        btn_toregister->setText(QCoreApplication::translate("LoginWidget", "\345\216\273\346\263\250\345\206\214->", nullptr));
        edit_account_register->setText(QString());
        edit_account_register->setPlaceholderText(QCoreApplication::translate("LoginWidget", "\350\264\246\345\217\267", nullptr));
        label_account->setText(QCoreApplication::translate("LoginWidget", "\346\217\220\347\244\2721", nullptr));
        edit_password_register->setText(QString());
        edit_password_register->setPlaceholderText(QCoreApplication::translate("LoginWidget", "\345\257\206\347\240\201", nullptr));
        btn_password_register->setText(QString());
        label_password->setText(QCoreApplication::translate("LoginWidget", "\346\217\220\347\244\2722", nullptr));
        btn_register->setText(QCoreApplication::translate("LoginWidget", "\346\263\250\345\206\214", nullptr));
        btn_tologin->setText(QCoreApplication::translate("LoginWidget", "<-\345\216\273\347\231\273\345\275\225", nullptr));
        btn_set_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class LoginWidget: public Ui_LoginWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWIDGET_H

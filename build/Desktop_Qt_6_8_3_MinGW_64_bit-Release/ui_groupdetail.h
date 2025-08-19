/********************************************************************************
** Form generated from reading UI file 'groupdetail.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GROUPDETAIL_H
#define UI_GROUPDETAIL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "profile.h"

QT_BEGIN_NAMESPACE

class Ui_GroupDetail
{
public:
    QVBoxLayout *verticalLayout_3;
    QWidget *widget_2;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *edit_name;
    QLineEdit *edit_id;
    QLineEdit *edit_intro;
    Profile *btn_profile;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btn1;
    QPushButton *btn2;
    QPushButton *btn3;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *GroupDetail)
    {
        if (GroupDetail->objectName().isEmpty())
            GroupDetail->setObjectName("GroupDetail");
        GroupDetail->resize(447, 570);
        verticalLayout_3 = new QVBoxLayout(GroupDetail);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        widget_2 = new QWidget(GroupDetail);
        widget_2->setObjectName("widget_2");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy);
        widget_2->setMinimumSize(QSize(429, 146));
        widget = new QWidget(widget_2);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(150, 10, 261, 128));
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        edit_name = new QLineEdit(widget);
        edit_name->setObjectName("edit_name");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(edit_name->sizePolicy().hasHeightForWidth());
        edit_name->setSizePolicy(sizePolicy1);
        edit_name->setReadOnly(true);

        verticalLayout_2->addWidget(edit_name);

        edit_id = new QLineEdit(widget);
        edit_id->setObjectName("edit_id");
        sizePolicy1.setHeightForWidth(edit_id->sizePolicy().hasHeightForWidth());
        edit_id->setSizePolicy(sizePolicy1);
        edit_id->setReadOnly(true);

        verticalLayout_2->addWidget(edit_id);

        edit_intro = new QLineEdit(widget);
        edit_intro->setObjectName("edit_intro");
        sizePolicy1.setHeightForWidth(edit_intro->sizePolicy().hasHeightForWidth());
        edit_intro->setSizePolicy(sizePolicy1);
        edit_intro->setReadOnly(true);

        verticalLayout_2->addWidget(edit_intro);

        btn_profile = new Profile(widget_2);
        btn_profile->setObjectName("btn_profile");
        btn_profile->setGeometry(QRect(10, 10, 128, 128));
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(btn_profile->sizePolicy().hasHeightForWidth());
        btn_profile->setSizePolicy(sizePolicy2);
        btn_profile->setMinimumSize(QSize(128, 128));
        btn_profile->setMaximumSize(QSize(64, 64));

        verticalLayout_3->addWidget(widget_2);

        widget_3 = new QWidget(GroupDetail);
        widget_3->setObjectName("widget_3");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(widget_3->sizePolicy().hasHeightForWidth());
        widget_3->setSizePolicy(sizePolicy3);
        verticalLayout = new QVBoxLayout(widget_3);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        scrollArea = new QScrollArea(widget_3);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 427, 323));
        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        widget_4 = new QWidget(widget_3);
        widget_4->setObjectName("widget_4");
        horizontalLayout = new QHBoxLayout(widget_4);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(113, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btn1 = new QPushButton(widget_4);
        btn1->setObjectName("btn1");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(btn1->sizePolicy().hasHeightForWidth());
        btn1->setSizePolicy(sizePolicy4);

        horizontalLayout->addWidget(btn1);

        btn2 = new QPushButton(widget_4);
        btn2->setObjectName("btn2");
        sizePolicy4.setHeightForWidth(btn2->sizePolicy().hasHeightForWidth());
        btn2->setSizePolicy(sizePolicy4);

        horizontalLayout->addWidget(btn2);

        btn3 = new QPushButton(widget_4);
        btn3->setObjectName("btn3");
        sizePolicy4.setHeightForWidth(btn3->sizePolicy().hasHeightForWidth());
        btn3->setSizePolicy(sizePolicy4);

        horizontalLayout->addWidget(btn3);

        horizontalSpacer_2 = new QSpacerItem(114, 21, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addWidget(widget_4);

        verticalLayout->setStretch(0, 4);
        verticalLayout->setStretch(1, 1);

        verticalLayout_3->addWidget(widget_3);

        verticalLayout_3->setStretch(0, 1);
        verticalLayout_3->setStretch(1, 2);

        retranslateUi(GroupDetail);

        QMetaObject::connectSlotsByName(GroupDetail);
    } // setupUi

    void retranslateUi(QWidget *GroupDetail)
    {
        GroupDetail->setWindowTitle(QCoreApplication::translate("GroupDetail", "Form", nullptr));
        edit_name->setPlaceholderText(QCoreApplication::translate("GroupDetail", "\347\276\244\345\220\215", nullptr));
        edit_id->setPlaceholderText(QCoreApplication::translate("GroupDetail", "\347\276\244\345\217\267", nullptr));
        edit_intro->setPlaceholderText(QCoreApplication::translate("GroupDetail", "\347\276\244\344\273\213\347\273\215", nullptr));
        btn_profile->setText(QString());
        btn1->setText(QCoreApplication::translate("GroupDetail", "\351\200\200\345\207\272\347\276\244\350\201\212", nullptr));
        btn2->setText(QCoreApplication::translate("GroupDetail", "\347\274\226\350\276\221\347\276\244\350\201\212", nullptr));
        btn3->setText(QCoreApplication::translate("GroupDetail", "\345\217\221\351\200\201\346\266\210\346\201\257", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GroupDetail: public Ui_GroupDetail {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GROUPDETAIL_H

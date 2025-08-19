/********************************************************************************
** Form generated from reading UI file 'camerawidget.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERAWIDGET_H
#define UI_CAMERAWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "clocklabel.h"
#include "pictureview.h"

QT_BEGIN_NAMESPACE

class Ui_CameraWidget
{
public:
    QWidget *widget_tool;
    QHBoxLayout *horizontalLayout;
    QPushButton *btn_onlyVoice;
    QPushButton *btn_accept;
    QPushButton *btn_volume;
    PictureView *subWidget;
    ClockLabel *label_time;

    void setupUi(QWidget *CameraWidget)
    {
        if (CameraWidget->objectName().isEmpty())
            CameraWidget->setObjectName("CameraWidget");
        CameraWidget->resize(800, 600);
        widget_tool = new QWidget(CameraWidget);
        widget_tool->setObjectName("widget_tool");
        widget_tool->setGeometry(QRect(245, 480, 310, 100));
        widget_tool->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color:transparent;\n"
"	border:none;\n"
"}"));
        horizontalLayout = new QHBoxLayout(widget_tool);
        horizontalLayout->setSpacing(5);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        btn_onlyVoice = new QPushButton(widget_tool);
        btn_onlyVoice->setObjectName("btn_onlyVoice");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btn_onlyVoice->sizePolicy().hasHeightForWidth());
        btn_onlyVoice->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/res/voice_only.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btn_onlyVoice->setIcon(icon);
        btn_onlyVoice->setIconSize(QSize(64, 64));

        horizontalLayout->addWidget(btn_onlyVoice);

        btn_accept = new QPushButton(widget_tool);
        btn_accept->setObjectName("btn_accept");
        sizePolicy.setHeightForWidth(btn_accept->sizePolicy().hasHeightForWidth());
        btn_accept->setSizePolicy(sizePolicy);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/res/accept.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btn_accept->setIcon(icon1);
        btn_accept->setIconSize(QSize(64, 64));

        horizontalLayout->addWidget(btn_accept);

        btn_volume = new QPushButton(widget_tool);
        btn_volume->setObjectName("btn_volume");
        sizePolicy.setHeightForWidth(btn_volume->sizePolicy().hasHeightForWidth());
        btn_volume->setSizePolicy(sizePolicy);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/res/volume2.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btn_volume->setIcon(icon2);
        btn_volume->setIconSize(QSize(64, 64));

        horizontalLayout->addWidget(btn_volume);

        subWidget = new PictureView(CameraWidget);
        subWidget->setObjectName("subWidget");
        subWidget->setGeometry(QRect(600, 0, 200, 150));
        label_time = new ClockLabel(CameraWidget);
        label_time->setObjectName("label_time");
        label_time->setGeometry(QRect(350, 0, 100, 40));

        retranslateUi(CameraWidget);

        QMetaObject::connectSlotsByName(CameraWidget);
    } // setupUi

    void retranslateUi(QWidget *CameraWidget)
    {
        CameraWidget->setWindowTitle(QCoreApplication::translate("CameraWidget", "CameraWidget", nullptr));
        btn_onlyVoice->setText(QString());
        btn_accept->setText(QString());
        btn_volume->setText(QString());
        label_time->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CameraWidget: public Ui_CameraWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERAWIDGET_H

/********************************************************************************
** Form generated from reading UI file 'emotionwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EMOTIONWIDGET_H
#define UI_EMOTIONWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EmotionWidget
{
public:
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *vl_emotion;

    void setupUi(QWidget *EmotionWidget)
    {
        if (EmotionWidget->objectName().isEmpty())
            EmotionWidget->setObjectName("EmotionWidget");
        EmotionWidget->resize(405, 300);
        verticalLayout = new QVBoxLayout(EmotionWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        scrollArea = new QScrollArea(EmotionWidget);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 403, 298));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        vl_emotion = new QVBoxLayout();
        vl_emotion->setSpacing(5);
        vl_emotion->setObjectName("vl_emotion");

        verticalLayout_2->addLayout(vl_emotion);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);


        retranslateUi(EmotionWidget);

        QMetaObject::connectSlotsByName(EmotionWidget);
    } // setupUi

    void retranslateUi(QWidget *EmotionWidget)
    {
        EmotionWidget->setWindowTitle(QCoreApplication::translate("EmotionWidget", "EmotionWidget", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EmotionWidget: public Ui_EmotionWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EMOTIONWIDGET_H

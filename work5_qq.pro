QT       += core gui network sql multimedia
RC_ICONS += chat.ico
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    abstractthread.cpp \
    autoheighttextedit.cpp \
    chatbubble.cpp \
    chatpreviewbutton.cpp \
    chatview.cpp \
    chatwidget.cpp \
    loadwidget.cpp \
    loginwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    mybutton.cpp \
    myhintpushbutton.cpp \
    profile.cpp \
    redpointbutton.cpp \
    roundlabel.cpp \
    setdialog.cpp \
    userdetail.cpp \
    userpatcher.cpp

HEADERS += \
    abstractthread.h \
    autoheighttextedit.h \
    chatbubble.h \
    chatpreviewbutton.h \
    chatview.h \
    chatwidget.h \
    loadwidget.h \
    loginwidget.h \
    macro.h \
    mainwindow.h \
    mybutton.h \
    myhintpushbutton.h \
    profile.h \
    redpointbutton.h \
    roundlabel.h \
    setdialog.h \
    userdetail.h \
    userpatcher.h

FORMS += \
    chatwidget.ui \
    loginwidget.ui \
    mainwindow.ui \
    userdetail.ui

INCLUDEPATH += $$PWD/emotion_widget
include($$PWD/emotion_widget/emotion.pri)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

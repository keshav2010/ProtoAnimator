#-------------------------------------------------
#
# Project created by QtCreator 2018-01-14T19:17:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProtoAnimator
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    animatable.cpp \
    frame.cpp \
    frameseditor.cpp \
    servicedockwidget.cpp \
    spritemanager.cpp \
    framemanager.cpp \
    animatablespriteitem.cpp \
    spritepropertyeditordialog.cpp \
    spritedata.cpp \
    animationdriver.cpp \
    timelineview.cpp \
    timelinemodel.cpp \
    timelinedelegate.cpp \
    timelinedockwidget.cpp \
    sceneitemsdockwidget.cpp

HEADERS += \
        mainwindow.h \
    animatable.h \
    frame.h \
    frameseditor.h \
    servicedockwidget.h \
    spritemanager.h \
    framemanager.h \
    animatablespriteitem.h \
    spritepropertyeditordialog.h \
    spritedata.h \
    animationdriver.h \
    timelineview.h \
    timelinemodel.h \
    timelinedelegate.h \
    timelinedockwidget.h \
    sceneitemsdockwidget.h

FORMS += \
        mainwindow.ui \
    spritepropertyeditordialog.ui

RESOURCES += \
    appresource.qrc

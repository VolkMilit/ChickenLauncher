#-------------------------------------------------
#
# Project created by QtCreator 2015-04-26T21:25:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChickenLauncher
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11 -g

SOURCES += ./scr/main.cpp\
        ./scr/mainwindow.cpp \
    scr/baseconfig.cpp \
    scr/gzdoom.cpp \
    scr/prboom.cpp \
    scr/listsfill.cpp \
    scr/functions.cpp \
    scr/configdialog.cpp \
    scr/colors.cpp

HEADERS  += ./scr/mainwindow.h \
    scr/baseconfig.h \
    scr/gzdoom.h \
    scr/prboom.h \
    scr/listsfill.h \
    scr/functions.h \
    scr/configdialog.h \
    scr/colors.h

FORMS    += ./scr/mainwindow.ui \
    scr/configdialog.ui

RESOURCES += \
    ./scr/icon.qrc

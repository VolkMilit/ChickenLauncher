#-------------------------------------------------
#
# Project created by QtCreator 2015-04-26T21:25:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChickenLauncher
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11 -O3

SOURCES += ./scr/main.cpp\
        ./scr/mainwindow.cpp

HEADERS  += ./scr/mainwindow.h

FORMS    += ./scr/mainwindow.ui

RESOURCES += \
    ./scr/icon.qrc

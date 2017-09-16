#-------------------------------------------------
#
# Project created by QtCreator 2015-04-26T21:25:04
#
#-------------------------------------------------

QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets core gui

TARGET = ChickenLauncher
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11
#QMAKE_LFLAGS += -llibquazip

SOURCES += ./scr/main.cpp\
        ./scr/mainwindow.cpp \
    scr/baseconfig.cpp \
    scr/gzdoom.cpp \
    scr/prboom.cpp \
    scr/listsfill.cpp \
    scr/configdialog.cpp \
    scr/colors.cpp \
    scr/archives.cpp \
    scr/descriptionshandler.cpp \
    scr/outputreader.cpp \
    scr/util.cpp

HEADERS  += ./scr/mainwindow.h \
    scr/baseconfig.h \
    scr/gzdoom.h \
    scr/prboom.h \
    scr/listsfill.h \
    scr/configdialog.h \
    scr/colors.h \
    scr/archives.h \
    scr/descriptionshandler.h \
    scr/outputreader.h \
    scr/util.h

FORMS    += ./scr/mainwindow.ui \
    scr/configdialog.ui

RESOURCES += \
    ./scr/icon.qrc

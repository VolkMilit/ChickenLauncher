#-------------------------------------------------
#
# Project created by QtCreator 2015-04-26T21:25:04
#
#-------------------------------------------------

QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets core gui

TARGET = ChickenLauncher
TARGET.files	 = chickenlauncher
TARGET.path	 = /usr/games
INSTALLS	+= TARGET desktop icons

TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11
QMAKE_LFLAGS += -lquazip

SOURCES += main.cpp\
    ui/mainwindow.cpp \
    ui/profiles.cpp \
    ui/wad.cpp \
    ui/configdialog.cpp \
    ui/settings.cpp \
    ui/multiplayer.cpp \
    ui/advanced.cpp \
    games/gzdoom.cpp \
    games/prboom.cpp \
    games/darkplaces.cpp \
    utils/baseconfig.cpp \
    utils/listsfill.cpp \
    utils/colors.cpp \
    utils/archives.cpp \
    utils/descriptionshandler.cpp \
    utils/util.cpp \
    utils/process.cpp

HEADERS  += ui/mainwindow.h \
    ui/configdialog.h \
    games/gzdoom.h \
    games/prboom.h \
    games/darkplaces.h \
    utils/listsfill.h \
    utils/colors.h \
    utils/archives.h \
    utils/descriptionshandler.h \
    utils/util.h \
    utils/baseconfig.h \
    utils/process.h

FORMS    += ui/mainwindow.ui \
    ui/configdialog.ui

RESOURCES += \
    icon.qrc

desktop.files = *.desktop
desktop.path  = /usr/share/applications

icons.files   = images/chickenlauncher.png
icons.path    = /usr/share/icons/hicolor/32x32/apps

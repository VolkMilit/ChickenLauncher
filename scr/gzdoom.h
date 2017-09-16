/*
 * Most important part of code :D err, I mean yes, other parts ARE important, but this part
 * parsing port parametrs. In this BIG comment I discribe the parametrs, that launcher are
 * support.
 * Of couse you always may see documentation at (http://zdoom.org/wiki/command_line_parameters)
 *
 *
 *
  ___ _______
 / __|_  /   \ ___  ___ _ __
| (_ |/ /| |) / _ \/ _ \ '  \
 \___/___|___/\___/\___/_|_|_|

*
*/

#ifndef GZDOOM_H
#define GZDOOM_H

#include <QListWidgetItem>
#include <QString>
#include <QDateTime>
#include <QProcess>
#include <QDebug>
#include <QMessageBox>
#include <QThread>

#include <cstdio>

#include "ui_mainwindow.h"
#include "baseconfig.h"
#include "outputreader.h"

namespace Launcher
{
    class gzdoom : public QWidget
    {
    public:
        explicit gzdoom(Ui::MainWindow *ui);
        virtual ~gzdoom();

        void startGzdoom();
        void startDemo();
        void networkGame();
        QString getGzdoomHomeDir();
        QProcess *process;

    private:
        Ui::MainWindow *myUi;

        config::baseConfig *VbaseConfig;

        QListWidgetItem *item;

        void parametrParser();

        /*
         ___ _       _
        / __| |_ _ _(_)_ _  __ _ ___
        \__ \  _| '_| | ' \/ _` (_-<
        |___/\__|_| |_|_||_\__, /__/
                           |___/
        */

        QString map;            //specify map, launch game with THIS map
        QString skill;          //specify skill, launch game with THIS skill (if map not specify, load first map)
        QString nomusic;        //Prevents the playback of music.
        QString nosound;        //play no sound
        QString nosfx;          //Prevents the playback of sound effects.
        QString demo;           //record demo file in specific directory as yyyy-MM-dd_H:mm:s.lmp
        QString oldsprites;     //Disables sprite renaming. Unless you are playing a mod for Heretic, Hexen or Strife that replaced a few select sprites, you do not need this.
        QString noautoload;     //Prevents files from being autoloaded based on the “AutoLoad” sections in the user's configuration file.
        QString nostartup;      //Disables the startup screens used by Heretic, Hexen and Strife, and use the Doom text-mode startup instead.
        QString loadgame;       //load games files, but need -iwad and -file =/

        QString iwad;
        QString pwad;

        QString exe;            //specify executable file (I use my own gzdoom installation)
        QString term;           //(Linux specific) run in terminal to see output, like in Windows version
        QString log;  //todo          //(Linux specific) recording log from terminal
        QString config;         //launch with specific settings\profile\config port file

        QString home;           //gzdoom home dir
    };
}

#endif // GZDOOM_H

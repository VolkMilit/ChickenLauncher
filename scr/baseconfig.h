#ifndef BASECONFIG_H
#define BASECONFIG_H

#include <QWidget>
#include <QMessageBox>
#include <QString>
#include <QDir>
#include <QSettings>

#include "ui_mainwindow.h"

class baseConfig : public QWidget
{
    public:
        baseConfig(Ui::MainWindow *ui);
        virtual ~baseConfig();

        bool fileExist(QString file);

        QString getProfilesDir();
        QString getLauncherSettingsFile();

        void readAllSettings(QString file);
        void writeAllSettings(QString file);

        /***settings.ini***/
        /*[settings]*/

        //profile
        void setCurrentProfile(QString profile);
        QString getCurrentProfile();
        QString getDefaultProfileName();

        //off_wad_path
        void setOffWadPath(int value);
        int getOffWadPath();

        //foreground_color
        void setForegroundColor(QString value);
        QString getForegroundColor();

        //hide program instead of close
        void setHide(int value);
        int getHide();

        //hide program when game start
        void setHideGame(int value);
        int getHideGame();

        //default_tab
        void setDefaultTab(int value);
        int getDefaultTab();

        //last_iwas_dir
        void setLastIwadDir(QString value);
        QString getLastIwadDir();

        //last_pwad_dir
        void setLastPwadDir(QString value);
        QString getLastPwadDir();


        /***${profile_name}.ini***/
        /*[WAD]*/

        //last_iwad
        void setLastIwad(QString value);
        QString getLastIwad();

        //last_pwad
        void setLastPwad(QString value);
        QString getLastPwad();

        //iwad_dir
        void setIwadDir(QString value);
        QString getIwadDir();

        //pwad_dir
        void setPwadDir(QString value);
        QString getPwadDir();

        /*[Port]*/
        //port_exe
        void setExePath(QString value);
        QString getExePath();

        //adv_exe_param
        void setAdvExeParam(QString value);
        QString getAdvExeParam();

        //adv_cmd_param
        void setAdvCmdParam(QString value);
        QString getAdvCmdParam();

        //config
        void setConfigFile(QString value);
        QString getConfigFile();

        /*[Network]*/
        //enabled
        void setNetworkEnabled(int value);
        int getNetworkEnabled();

        //ip
        void setIpAdress(QString value);
        QString getIpAdress();

        //port
        void setIpPort(QString value);
        QString getIpPort();

    private:
        Ui::MainWindow *myUi;

        QString home;
        QString defaultSettings;
        QString profilesDir;
        QString defaultProfile;

        void getValues();
        void writeSettings(QString file, QString group, QString value, QString var);
        void writeSettings(QString file, QString group, QString value, int var);
        QString readSettings(QString file, QString group, QString value);
        int readIntSettings(QString file, QString group, QString value);
};

#endif // BASECONFIG_H

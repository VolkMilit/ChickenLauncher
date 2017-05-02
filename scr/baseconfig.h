#ifndef BASECONFIG_H
#define BASECONFIG_H

#include <QWidget>
#include <QMessageBox>
#include <QString>
#include <QDir>
#include <QSettings>

#include "functions.h"
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
    void setOffWadPath(QString file, int value);
    int getOffWadPath(QString file);

    //foreground_color
    void setForegroundColor(QString file, QString value);
    QString getForegroundColor(QString file);

    //hide program instead of close
    void setHide(QString file, int value);
    int getHide(QString file);

    //hide program when game start
    void setHideGame(QString file, int value);
    int getHideGame(QString file);

    //default_tab
    void setDefaultTab(QString file, int value);
    int getDefaultTab(QString file);

    //last_iwas_dir
    void setLastIwadDir(QString file, QString value);
    QString getLastIwadDir(QString file);

    //last_pwad_dir
    void setLastPwadDir(QString file, QString value);
    QString getLastPwadDir(QString file);


    /***${profile_name}.ini***/
    /*[WAD]*/

    //last_iwad
    void setLastIwad(QString file, QString value);
    QString getLastIwad(QString file);

    //last_pwad_num
    //little tmp (no) ducktape
    void setLastPwadNum(QString file, int value);
    int getLastPwadNum(QString file);

    //last_pwad
    void setLastPwad(QString file, QString value);
    QString getLastPwad(QString file);

    //iwad_dir
    void setIwadDir(QString file, QString value);
    QString getIwadDir(QString file);

    //pwad_dir
    void setPwadDir(QString file, QString value);
    QString getPwadDir(QString file);

    /*[Port]*/
    //port_exe
    void setExePath(QString file, QString value);
    QString getExePath(QString file);

    //adv_exe_param
    void setAdvExeParam(QString file, QString value);
    QString getAdvExeParam(QString file);

    //adv_cmd_param
    void setAdvCmdParam(QString file, QString value);
    QString getAdvCmdParam(QString file);

    //config
    void setConfigFile(QString file, QString value);
    QString getConfigFile(QString file);

private:
    Ui::MainWindow *myUi;
    functions *Vfunctions;

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

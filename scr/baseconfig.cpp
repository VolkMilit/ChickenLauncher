#include "baseconfig.h"

baseConfig::baseConfig(Ui::MainWindow *ui)
{
    this->myUi = ui;
    getValues();
}

baseConfig::~baseConfig()
{
    delete myUi;
}

/* ___     _                            _
  | _ \___| |_ _  _ _ _ _ _   __ ____ _| |_  _ ___
  |   / -_)  _| || | '_| ' \  \ V / _` | | || / -_)
  |_|_\___|\__|\_,_|_| |_||_|  \_/\__,_|_|\_,_\___|
*/

void baseConfig::getValues()
{
    #ifdef Q_OS_WIN32
        home = QDir::homePath() + "\\ApplicationData\\ChickenLauncher\\";
    #else
        home = QDir::homePath() + "/.config/ChickenLauncher/";
    #endif

    defaultSettings = home + "settings.ini";
    profilesDir = home + "profiles/";
}

QString baseConfig::getProfilesDir()
{
    return profilesDir;
}

QString baseConfig::getDefaultSettings()
{
    return defaultSettings;
}

/***settings.ini***/
/*[settings]*/

//profile
QString baseConfig::getDefaultProfile()
{
    getValues();
    defaultProfile = readSettings(defaultSettings, "settings", "profile");
    return profilesDir + defaultProfile;
}

void baseConfig::setDefaultProfile(QString profile)
{
    getValues();
    writeSettings(defaultSettings, "settings", "profile", profile);
}

QString baseConfig::getDefaultProfileName()
{
    getValues();
    defaultProfile = readSettings(defaultSettings, "settings", "profile");
    return defaultProfile;
}

//off_wad_path
void baseConfig::setOffWadPath(QString file, QString value)
{
    writeSettings(file, "settings", "off_wad_path", value);
}

QString baseConfig::getOffWadPath(QString file)
{
    QString ret = readSettings(file, "settings", "off_wad_path");
    return ret;
}

//foreground_color
void baseConfig::setForegroundColor(QString file, QString value)
{
    writeSettings(file, "settings", "foreground_color", value);
}

QString baseConfig::getForegroundColor(QString file)
{
    QString ret = readSettings(file, "settings", "foreground_color");
    return ret;
}

//hide
void baseConfig::setHide(QString file, QString value)
{
    writeSettings(file, "settings", "hide", value);
}

QString baseConfig::getHide(QString file)
{
    QString ret = readSettings(file, "settings", "hide");
    return ret;
}

/***[profile_name].ini***/
/*[WAD]*/

//last_iwad
void baseConfig::setLastIwad(QString file, QString value)
{
    writeSettings(file, "WAD", "last_iwad", value);
}

QString baseConfig::getLastIwad(QString file)
{
    QString ret = readSettings(file, "WAD", "last_iwad");
    return ret;
}

//last_pwad
void baseConfig::setLastPwad(QString file, QString value)
{
    writeSettings(file, "WAD", "last_pwads", value);
}

QString baseConfig::getLastPwad(QString file)
{
    QString ret = readSettings(file, "WAD", "last_pwads");
    return ret;
}

//iwad_dir
void baseConfig::setIwadDir(QString file, QString value)
{
    writeSettings(file, "WAD", "iwad_dir", value);
}

QString baseConfig::getIwadDir(QString file)
{
    QString ret = readSettings(file, "WAD", "iwad_dir");
    return ret;
}

//pwad_dir
void baseConfig::setPwadDir(QString file, QString value)
{
    writeSettings(file, "WAD", "pwad_dir", value);
}

QString baseConfig::getPwadDir(QString file)
{
    QString ret = readSettings(file, "WAD", "pwad_dir");
    return ret;
}

//exe_path
void baseConfig::setExePath(QString file, QString value)
{
    writeSettings(file, "Port", "port_exe", value);
}

QString baseConfig::getExePath(QString file)
{
    QString ret = readSettings(file, "Port", "port_exe");
    return ret;
}

//adv_exe_param
void baseConfig::setAdvExeParam(QString file, QString value)
{
    writeSettings(file, "Port", "additional_port_param", value);
}

QString baseConfig::getAdvExeParam(QString file)
{
    QString ret = readSettings(file, "WAD", "additional_port_param");
    return ret;
}

//adv_cmd_param
void baseConfig::setAdvCmdParam(QString file, QString value)
{
    writeSettings(file, "Port", "additional_cmd_param", value);
}

QString baseConfig::getAdvCmdParam(QString file)
{
    QString ret = readSettings(file, "WAD", "additional_cmd_param");
    return ret;
}

/* ___             _   _
  | __|  _ _ _  __| |_(_)___ _ _  ___
  | _| || | ' \/ _|  _| / _ \ ' \(_-<
  |_| \_,_|_||_\__|\__|_\___/_||_/__/
*/

bool baseConfig::fileExist(QString file)
{
    QFile f(file);
    if (!f.exists())
    {
        QMessageBox::critical(this, "", "Nobody, but us chicken! File does'n exist!");

        //delete item, don't know, if it's ugly code, but working
        QListWidgetItem *it = myUi->lw_profile->item(myUi->lw_profile->currentRow());
        delete it;

        return false;
    }

    return true;
}

void baseConfig::writeAllSettings(QString file)
{
    //[WAD]
    setIwadDir(file, myUi->le_iwad->text());
    setPwadDir(file, myUi->le_pwad->text());

    //[Port]
    setExePath(file, myUi->le_exe->text());
    setAdvExeParam(file, myUi->le_adv_port_param->text());
    setAdvCmdParam(file, myUi->le_adv_cmd_param->text());
}

void baseConfig::readAllSettings(QString file)
{
    //[WAD]
    myUi->le_iwad->setText(getIwadDir(file));
    myUi->le_pwad->setText(getPwadDir(file));

    //[Port]
    myUi->le_exe->setText(getExePath(file));
    myUi->le_adv_port_param->setText(getAdvExeParam(file));
    myUi->le_adv_cmd_param->setText(getAdvCmdParam(file));
}

void baseConfig::writeSettings(QString file, QString group, QString value, QString var)
{
    if (!fileExist(file))
        return;

    QSettings settings(file, QSettings::IniFormat);
    settings.beginGroup(group);
    settings.setValue(value, var);
    settings.endGroup();
}

QString baseConfig::readSettings(QString file, QString group, QString value)
{
    if (!fileExist(file))
        return "";

    QString rv;

    QSettings settings(file, QSettings::IniFormat);
    settings.beginGroup(group);
    rv = settings.value(value).toString();
    settings.endGroup();

    return rv;
}


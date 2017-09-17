#include "baseconfig.h"

config::baseConfig::baseConfig(Ui::MainWindow *ui)
{
    this->myUi = ui;
    getValues();
}

config::baseConfig::~baseConfig(){}

/* ___     _                            _
  | _ \___| |_ _  _ _ _ _ _   __ ____ _| |_  _ ___
  |   / -_)  _| || | '_| ' \  \ V / _` | | || / -_)
  |_|_\___|\__|\_,_|_| |_||_|  \_/\__,_|_|\_,_\___|
*/

void config::baseConfig::getValues()
{
    #ifdef _WIN32
        home = QDir::homePath() + "\\ApplicationData\\ChickenLauncher\\";
    #else
        home = QDir::homePath() + "/.config/ChickenLauncher/";
    #endif

    defaultSettings = home + "settings.ini";
    profilesDir = home + "profiles/";
}

QString config::baseConfig::getProfilesDir()
{
    return profilesDir;
}

QString config::baseConfig::getLauncherSettingsFile()
{
    return defaultSettings;
}

/***settings.ini***/
/*[settings]*/

//profile
QString config::baseConfig::getCurrentProfile()
{
    getValues();
    defaultProfile = readSettings(defaultSettings, "settings", "profile");
    return profilesDir + defaultProfile;
}

void config::baseConfig::setCurrentProfile(QString profile)
{
    getValues();
    writeSettings(defaultSettings, "settings", "profile", profile);
}

QString config::baseConfig::getDefaultProfileName()
{
    getValues();
    defaultProfile = readSettings(defaultSettings, "settings", "profile");
    return defaultProfile;
}

//off_wad_path
void config::baseConfig::setOffWadPath(int value)
{
    writeSettings(defaultSettings, "settings", "off_wad_path", value);
}

int config::baseConfig::getOffWadPath()
{
    int ret = readIntSettings(defaultSettings, "settings", "off_wad_path");
    return ret;
}

//foreground_color
void config::baseConfig::setForegroundColor(QString file, QString value)
{
    writeSettings(file, "settings", "foreground_color", value);
}

QString config::baseConfig::getForegroundColor(QString file)
{
    QString ret = readSettings(file, "settings", "foreground_color");
    return ret;
}

//hide program instead of close
void config::baseConfig::setHide(QString file, int value)
{
    writeSettings(file, "settings", "hide", value);
}

int config::baseConfig::getHide(QString file)
{
    int ret = readIntSettings(file, "settings", "hide");
    return ret;
}

//hide program when game start
void config::baseConfig::setHideGame(QString file, int value)
{
    writeSettings(file, "settings", "hide_game", value);
}

int config::baseConfig::getHideGame(QString file)
{
    int ret = readIntSettings(file, "settings", "hide_game");
    return ret;
}

//default tab
// 0 - profiles, 1 - wads
void config::baseConfig::setDefaultTab(QString file, int value)
{
    writeSettings(file, "settings", "default_tab", value);
}

int config::baseConfig::getDefaultTab(QString file)
{
    int ret = readIntSettings(file, "settings", "default_tab");
    return ret;
}

//last iwad dir
void config::baseConfig::setLastIwadDir(QString file, QString value)
{
    writeSettings(file, "settings", "last_iwad_dir", value);
}

QString config::baseConfig::getLastIwadDir(QString file)
{
    QString ret = readSettings(file, "settings", "last_iwad_dir");
    return ret;
}

//last pwad dir
void config::baseConfig::setLastPwadDir(QString file, QString value)
{
    writeSettings(file, "settings", "last_pwad_dir", value);
}

QString config::baseConfig::getLastPwadDir(QString file)
{
    QString ret = readSettings(file, "settings", "last_pwad_dir");
    return ret;
}

/***${profile_name}.ini***/
/*[WAD]*/

//last_iwad
void config::baseConfig::setLastIwad(QString file, QString value)
{
    writeSettings(file, "WAD", "last_iwad", value);
}

QString config::baseConfig::getLastIwad(QString file)
{
    QString ret = readSettings(file, "WAD", "last_iwad");
    return ret;
}

//last_pwad
void config::baseConfig::setLastPwad(QString file, QString value)
{
    writeSettings(file, "WAD", "last_pwads", value);
}

QString config::baseConfig::getLastPwad(QString file)
{
    QString ret = readSettings(file, "WAD", "last_pwads");
    return ret;
}

//iwad_dir
void config::baseConfig::setIwadDir(QString file, QString value)
{
    writeSettings(file, "WAD", "iwad_dir", value);
}

QString config::baseConfig::getIwadDir(QString file)
{
    QString ret = readSettings(file, "WAD", "iwad_dir");
    return ret;
}

//pwad_dir
void config::baseConfig::setPwadDir(QString file, QString value)
{
    writeSettings(file, "WAD", "pwad_dir", value);
}

QString config::baseConfig::getPwadDir(QString file)
{
    QString ret = readSettings(file, "WAD", "pwad_dir");
    return ret;
}

//exe_path
void config::baseConfig::setExePath(QString file, QString value)
{
    writeSettings(file, "Port", "port_exe", value);
}

QString config::baseConfig::getExePath(QString file)
{
    QString ret = readSettings(file, "Port", "port_exe");
    return ret;
}

//adv_exe_param
void config::baseConfig::setAdvExeParam(QString file, QString value)
{
    writeSettings(file, "Port", "additional_port_param", value);
}

QString config::baseConfig::getAdvExeParam(QString file)
{
    QString ret = readSettings(file, "Port", "additional_port_param");
    return ret;
}

//adv_cmd_param
void config::baseConfig::setAdvCmdParam(QString file, QString value)
{
    writeSettings(file, "Port", "additional_cmd_param", value);
}

QString config::baseConfig::getAdvCmdParam(QString file)
{
    QString ret = readSettings(file, "Port", "additional_cmd_param");
    return ret;
}

//config
void config::baseConfig::setConfigFile(QString file, QString value)
{
    writeSettings(file, "Port", "config", value);
}

QString config::baseConfig::getConfigFile(QString file)
{
    QString ret = readSettings(file, "Port", "config");
    return ret;
}

/* ___             _   _
  | __|  _ _ _  __| |_(_)___ _ _  ___
  | _| || | ' \/ _|  _| / _ \ ' \(_-<
  |_| \_,_|_||_\__|\__|_\___/_||_/__/
*/

bool config::baseConfig::fileExist(QString file)
{
    QFile f(file);

    QFile settings(defaultSettings);
    QString defaultProfileFile = getCurrentProfile();
    QFile profile(defaultProfileFile);

    if (!f.exists())
    {
        QMessageBox::critical(this, "", "Seams to file " + file
                              + " doesn't exist. Launcher create new settings.ini and new default.ini if they missig.");

        //settings.ini
        if (!settings.exists())
        {
            setForegroundColor(defaultSettings, "Blue");
            setHide(defaultSettings, 1);
            setOffWadPath(0);
            setCurrentProfile("default.ini");
        }

        //default.ini
        if (!profile.exists())
        {
            setAdvCmdParam(defaultProfileFile, "");
            setAdvExeParam(defaultProfileFile, "");
            setExePath(defaultProfileFile, "gzdoom");
            setIwadDir(defaultProfileFile, "$HOME/games/DOOM/IWAD");
            setPwadDir(defaultProfileFile, "$HOME/games/DOOM/PWAD");
            setLastIwad(defaultProfileFile, "DOOM.WAD");
        }

        return false;
    }

    return true;
}

void config::baseConfig::writeAllSettings(QString file)
{
    //[WAD]
    setIwadDir(file, myUi->le_iwad->text());
    setPwadDir(file, myUi->le_pwad->text());

    //[Port]
    setExePath(file, myUi->le_exe->text());
    setAdvExeParam(file, myUi->le_adv_port_param->text());
    setAdvCmdParam(file, myUi->le_adv_cmd_param->text());
}

void config::baseConfig::readAllSettings(QString file)
{
    //[WAD]
    myUi->le_iwad->setText(getIwadDir(file));
    myUi->le_pwad->setText(getPwadDir(file));

    //[Port]
    myUi->le_exe->setText(getExePath(file));
    myUi->le_adv_port_param->setText(getAdvExeParam(file));
    myUi->le_adv_cmd_param->setText(getAdvCmdParam(file));
}

void config::baseConfig::writeSettings(QString file, QString group, QString value, QString var)
{
    QSettings settings(file, QSettings::IniFormat);
    settings.beginGroup(group);
    settings.setValue(value, var);
    settings.endGroup();
}

QString config::baseConfig::readSettings(QString file, QString group, QString value)
{
    QString rv;

    QSettings settings(file, QSettings::IniFormat);
    settings.beginGroup(group);
    rv = settings.value(value).toString();
    settings.endGroup();

    return rv;
}

void config::baseConfig::writeSettings(QString file, QString group, QString value, int var)
{
    QSettings settings(file, QSettings::IniFormat);
    settings.beginGroup(group);
    settings.setValue(value, var);
    settings.endGroup();
}

int config::baseConfig::readIntSettings(QString file, QString group, QString value)
{
    int rv;

    QSettings settings(file, QSettings::IniFormat);
    settings.beginGroup(group);
    rv = settings.value(value).toInt();
    settings.endGroup();

    return rv;
}

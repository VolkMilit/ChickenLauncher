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
void config::baseConfig::setForegroundColor(QString value)
{
    writeSettings(defaultSettings, "settings", "foreground_color", value);
}

QString config::baseConfig::getForegroundColor()
{
    QString ret = readSettings(defaultSettings, "settings", "foreground_color");
    return ret;
}

//hide program instead of close
void config::baseConfig::setHide(int value)
{
    writeSettings(defaultSettings, "settings", "hide", value);
}

int config::baseConfig::getHide()
{
    int ret = readIntSettings(defaultSettings, "settings", "hide");
    return ret;
}

//hide program when game start
void config::baseConfig::setHideGame(int value)
{
    writeSettings(defaultSettings, "settings", "hide_game", value);
}

int config::baseConfig::getHideGame()
{
    int ret = readIntSettings(defaultSettings, "settings", "hide_game");
    return ret;
}

//default tab
// 0 - profiles, 1 - wads
void config::baseConfig::setDefaultTab(int value)
{
    writeSettings(defaultSettings, "settings", "default_tab", value);
}

int config::baseConfig::getDefaultTab()
{
    int ret = readIntSettings(defaultSettings, "settings", "default_tab");
    return ret;
}

//last iwad dir
void config::baseConfig::setLastIwadDir(QString value)
{
    writeSettings(defaultSettings, "settings", "last_iwad_dir", value);
}

QString config::baseConfig::getLastIwadDir()
{
    QString ret = readSettings(defaultSettings, "settings", "last_iwad_dir");
    return ret;
}

//last pwad dir
void config::baseConfig::setLastPwadDir(QString value)
{
    writeSettings(defaultSettings, "settings", "last_pwad_dir", value);
}

QString config::baseConfig::getLastPwadDir()
{
    QString ret = readSettings(defaultSettings, "settings", "last_pwad_dir");
    return ret;
}

/***${profile_name}.ini***/
/*[WAD]*/

//last_iwad
void config::baseConfig::setLastIwad(QString value)
{
    writeSettings(getCurrentProfile(), "WAD", "last_iwad", value);
}

QString config::baseConfig::getLastIwad()
{
    QString ret = readSettings(getCurrentProfile(), "WAD", "last_iwad");
    return ret;
}

//last_pwad
void config::baseConfig::setLastPwad(QString value)
{
    writeSettings(getCurrentProfile(), "WAD", "last_pwads", value);
}

QString config::baseConfig::getLastPwad()
{
    QString ret = readSettings(getCurrentProfile(), "WAD", "last_pwads");
    return ret;
}

//iwad_dir
void config::baseConfig::setIwadDir(QString value)
{
    writeSettings(getCurrentProfile(), "WAD", "iwad_dir", value);
}

QString config::baseConfig::getIwadDir()
{
    QString ret = readSettings(getCurrentProfile(), "WAD", "iwad_dir");
    return ret;
}

//pwad_dir
void config::baseConfig::setPwadDir(QString value)
{
    writeSettings(getCurrentProfile(), "WAD", "pwad_dir", value);
}

QString config::baseConfig::getPwadDir()
{
    QString ret = readSettings(getCurrentProfile(), "WAD", "pwad_dir");
    return ret;
}

//exe_path
void config::baseConfig::setExePath(QString value)
{
    writeSettings(getCurrentProfile(), "Port", "port_exe", value);
}

QString config::baseConfig::getExePath()
{
    QString ret = readSettings(getCurrentProfile(), "Port", "port_exe");
    return ret;
}

//adv_exe_param
void config::baseConfig::setAdvExeParam(QString value)
{
    writeSettings(getCurrentProfile(), "Port", "additional_port_param", value);
}

QString config::baseConfig::getAdvExeParam()
{
    QString ret = readSettings(getCurrentProfile(), "Port", "additional_port_param");
    return ret;
}

//adv_cmd_param
void config::baseConfig::setAdvCmdParam(QString value)
{
    writeSettings(getCurrentProfile(), "Port", "additional_cmd_param", value);
}

QString config::baseConfig::getAdvCmdParam()
{
    QString ret = readSettings(getCurrentProfile(), "Port", "additional_cmd_param");
    return ret;
}

//config
void config::baseConfig::setConfigFile(QString value)
{
    writeSettings(getCurrentProfile(), "Port", "config", value);
}

QString config::baseConfig::getConfigFile()
{
    QString ret = readSettings(getCurrentProfile(), "Port", "config");
    return ret;
}

/*[Network]*/
//enabled
void config::baseConfig::setNetworkEnabled(int value)
{
    writeSettings(getCurrentProfile(), "Network", "enabled", value);
}

int config::baseConfig::getNetworkEnabled()
{
    int ret = readIntSettings(getCurrentProfile(), "Network", "enabled");
    return ret;
}

//ip
void config::baseConfig::setIpAdress(QString value)
{
    writeSettings(getCurrentProfile(), "Network", "ip", value);
}

QString config::baseConfig::getIpAdress()
{
    QString ret = readSettings(getCurrentProfile(), "Network", "ip");
    return ret;
}

//ip_port
void config::baseConfig::setIpPort(QString value)
{
    writeSettings(getCurrentProfile(), "Network", "ip_port", value);
}

QString config::baseConfig::getIpPort()
{
    QString ret = readSettings(getCurrentProfile(), "Network", "ip_port");
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
            setForegroundColor("Blue");
            setHide(1);
            setOffWadPath(0);
            setCurrentProfile("default.ini");
        }

        //default.ini
        if (!profile.exists())
        {
            setAdvCmdParam("");
            setAdvExeParam("");
            setExePath("gzdoom");
            setIwadDir("$HOME/games/DOOM/IWAD");
            setPwadDir("$HOME/games/DOOM/PWAD");
            setLastIwad("DOOM.WAD");
        }

        return false;
    }

    return true;
}

void config::baseConfig::writeAllSettings(QString file)
{
    //[WAD]
    writeSettings(file, "WAD", "iwad_dir", myUi->le_iwad->text());
    writeSettings(file, "WAD", "iwad_dir", myUi->le_pwad->text());

    //[Port]
    writeSettings(file, "Port", "port_exe", myUi->le_exe->text());
    writeSettings(file, "Port", "additional_port_param", myUi->le_adv_port_param->text());
    writeSettings(file, "Port", "additional_cmd_param", myUi->le_adv_cmd_param->text());
}

void config::baseConfig::readAllSettings(QString file)
{
    //[WAD]
    myUi->le_iwad->setText(readSettings(file, "WAD", "iwad_dir"));
    myUi->le_pwad->setText(readSettings(file, "WAD", "pwad_dir"));

    //[Port]
    myUi->le_exe->setText(readSettings(file, "Port", "port_exe"));
    myUi->le_adv_port_param->setText(readSettings(file, "Port", "additional_port_param"));
    myUi->le_adv_cmd_param->setText(readSettings(file, "Port", "additional_cmd_param"));

    //[Network]
    if (readIntSettings(file, "Network", "enabled") == 1)
        myUi->gb_join->setChecked(true);

    myUi->le_ip->setText(readSettings(file, "Network", "ip"));
    myUi->le_port->setText(readSettings(file, "Network", "ip_port"));
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

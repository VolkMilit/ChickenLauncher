#include "baseconfig.h"

Utils::baseConfig::baseConfig(Ui::MainWindow *ui)
{
    this->myUi = ui;

    #ifdef _WIN32
        home = QDir::homePath() + "\\ApplicationData\\ChickenLauncher\\";
    #else
        home = QDir::homePath() + "/.config/ChickenLauncher/";
    #endif

    defaultSettings = home + "settings.ini";
    profilesDir = home + "profiles/";
}

Utils::baseConfig::~baseConfig(){}

/* ___     _                            _
  | _ \___| |_ _  _ _ _ _ _   __ ____ _| |_  _ ___
  |   / -_)  _| || | '_| ' \  \ V / _` | | || / -_)
  |_|_\___|\__|\_,_|_| |_||_|  \_/\__,_|_|\_,_\___|
*/

QString Utils::baseConfig::getLauncherHomeDir()
{
    return home;
}

QString Utils::baseConfig::getProfilesDir()
{
    return profilesDir;
}

QString Utils::baseConfig::getLauncherSettingsFile()
{
    return defaultSettings;
}

/***settings.ini***/
/*[settings]*/

//profile
QString Utils::baseConfig::getCurrentProfile()
{
    defaultProfile = readSettings(defaultSettings, "settings", "profile");
    return profilesDir + defaultProfile;
}

void Utils::baseConfig::setCurrentProfile(const QString &profile)
{
    writeSettings(defaultSettings, "settings", "profile", profile);
}

QString Utils::baseConfig::getDefaultProfileName()
{
    defaultProfile = readSettings(defaultSettings, "settings", "profile");
    return defaultProfile;
}

//off_wad_path
void Utils::baseConfig::setOffWadPath(const short value)
{
    writeSettings(defaultSettings, "settings", "off_wad_path", value);
}

short Utils::baseConfig::getOffWadPath()
{
    short ret = readIntSettings(defaultSettings, "settings", "off_wad_path");
    return ret;
}

//foreground_color
void Utils::baseConfig::setForegroundColor(const QString &value)
{
    writeSettings(defaultSettings, "settings", "foreground_color", value);
}

QString Utils::baseConfig::getForegroundColor()
{
    QString ret = readSettings(defaultSettings, "settings", "foreground_color");
    return ret;
}

//hide program instead of close
void Utils::baseConfig::setHide(const short value)
{
    writeSettings(defaultSettings, "settings", "hide", value);
}

short Utils::baseConfig::getHide()
{
    short ret = readIntSettings(defaultSettings, "settings", "hide");
    return ret;
}

//hide program when game start
void Utils::baseConfig::setHideGame(const short value)
{
    writeSettings(defaultSettings, "settings", "hide_game", value);
}

short Utils::baseConfig::getHideGame()
{
    short ret = readIntSettings(defaultSettings, "settings", "hide_game");
    return ret;
}

//default tab
// 0 - profiles, 1 - wads
void Utils::baseConfig::setDefaultTab(const short value)
{
    writeSettings(defaultSettings, "settings", "default_tab", value);
}

short Utils::baseConfig::getDefaultTab()
{
    short ret = readIntSettings(defaultSettings, "settings", "default_tab");
    return ret;
}

//last iwad dir
void Utils::baseConfig::setLastIwadDir(const QString &value)
{
    writeSettings(defaultSettings, "settings", "last_iwad_dir", value);
}

QString Utils::baseConfig::getLastIwadDir()
{
    QString ret = readSettings(defaultSettings, "settings", "last_iwad_dir");
    return ret;
}

//last pwad dir
void Utils::baseConfig::setLastPwadDir(const QString &value)
{
    writeSettings(defaultSettings, "settings", "last_pwad_dir", value);
}

QString Utils::baseConfig::getLastPwadDir()
{
    QString ret = readSettings(defaultSettings, "settings", "last_pwad_dir");
    return ret;
}

/***${profile_name}.ini***/
/*[WAD]*/

//last_iwad
void Utils::baseConfig::setLastIwad(const QString &value)
{
    writeSettings(getCurrentProfile(), "WAD", "last_iwad", value);
}

QString Utils::baseConfig::getLastIwad()
{
    QString ret = readSettings(getCurrentProfile(), "WAD", "last_iwad");
    return ret;
}

//last_pwad
void Utils::baseConfig::setLastPwad(const QString &value)
{
    writeSettings(getCurrentProfile(), "WAD", "last_pwads", value);
}

QString Utils::baseConfig::getLastPwad()
{
    QString ret = readSettings(getCurrentProfile(), "WAD", "last_pwads");
    return ret;
}

//iwad_dir
void Utils::baseConfig::setIwadDir(const QString &value)
{
    writeSettings(getCurrentProfile(), "WAD", "iwad_dir", value);
}

QString Utils::baseConfig::getIwadDir()
{
    QString ret = readSettings(getCurrentProfile(), "WAD", "iwad_dir");
    return ret;
}

//pwad_dir
void Utils::baseConfig::setPwadDir(const QString &value)
{
    writeSettings(getCurrentProfile(), "WAD", "pwad_dir", value);
}

QString Utils::baseConfig::getPwadDir()
{
    QString ret = readSettings(getCurrentProfile(), "WAD", "pwad_dir");
    return ret;
}

//exe_path
void Utils::baseConfig::setExePath(const QString &value)
{
    writeSettings(getCurrentProfile(), "Port", "port_exe", value);
}

QString Utils::baseConfig::getExePath()
{
    QString ret = readSettings(getCurrentProfile(), "Port", "port_exe");
    return ret;
}

//adv_exe_param
void Utils::baseConfig::setAdvExeParam(const QString &value)
{
    writeSettings(getCurrentProfile(), "Port", "additional_port_param", value);
}

QString Utils::baseConfig::getAdvExeParam()
{
    QString ret = readSettings(getCurrentProfile(), "Port", "additional_port_param");
    return ret;
}

//adv_cmd_param
void Utils::baseConfig::setAdvCmdParam(const QString &value)
{
    writeSettings(getCurrentProfile(), "Port", "additional_cmd_param", value);
}

QString Utils::baseConfig::getAdvCmdParam()
{
    QString ret = readSettings(getCurrentProfile(), "Port", "additional_cmd_param");
    return ret;
}

//config
void Utils::baseConfig::setConfigFile(const QString &value)
{
    writeSettings(getCurrentProfile(), "Port", "config", value);
}

QString Utils::baseConfig::getConfigFile()
{
    QString ret = readSettings(getCurrentProfile(), "Port", "config");
    return ret;
}

//game_port
void Utils::baseConfig::setGamePort(const short value)
{
    writeSettings(getCurrentProfile(), "Port", "game_port", value);
}

short Utils::baseConfig::getGamePort()
{
    short ret = readIntSettings(getCurrentProfile(), "Port", "game_port");
    return ret;
}

//water (dakrplaces specific)
void Utils::baseConfig::setDarkplacesWater(const short value)
{
    writeSettings(getCurrentProfile(), "Port", "water", value);
}

short Utils::baseConfig::getDarkplacesWater()
{
    short ret = readIntSettings(getCurrentProfile(), "Port", "water");
    return ret;
}

/*[Network]*/
//enabled
void Utils::baseConfig::setNetworkEnabled(const short value)
{
    writeSettings(getCurrentProfile(), "Network", "enabled", value);
}

short Utils::baseConfig::getNetworkEnabled()
{
    short ret = readIntSettings(getCurrentProfile(), "Network", "enabled");
    return ret;
}

//ip
void Utils::baseConfig::setIpAdress(const QString &value)
{
    writeSettings(getCurrentProfile(), "Network", "ip", value);
}

QString Utils::baseConfig::getIpAdress()
{
    QString ret = readSettings(getCurrentProfile(), "Network", "ip");
    return ret;
}

//ip_port
void Utils::baseConfig::setIpPort(const QString &value)
{
    writeSettings(getCurrentProfile(), "Network", "ip_port", value);
}

QString Utils::baseConfig::getIpPort()
{
    QString ret = readSettings(getCurrentProfile(), "Network", "ip_port");
    return ret;
}

/* ___             _   _
  | __|  _ _ _  __| |_(_)___ _ _  ___
  | _| || | ' \/ _|  _| / _ \ ' \(_-<
  |_| \_,_|_||_\__|\__|_\___/_||_/__/
*/

bool Utils::baseConfig::fileExist(const QString &file)
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

void Utils::baseConfig::writeAllSettings(const QString &file)
{
    //[WAD]
    writeSettings(file, "WAD", "iwad_dir", myUi->le_iwad->text());
    writeSettings(file, "WAD", "iwad_dir", myUi->le_pwad->text());

    //[Port]
    writeSettings(file, "Port", "port_exe", myUi->le_exe->text());
    writeSettings(file, "Port", "additional_port_param", myUi->le_adv_port_param->text());
    writeSettings(file, "Port", "additional_cmd_param", myUi->le_adv_cmd_param->text());
}

void Utils::baseConfig::readAllSettings(const QString &file)
{
    //[WAD]
    myUi->le_iwad->setText(readSettings(file, "WAD", "iwad_dir"));
    myUi->le_pwad->setText(readSettings(file, "WAD", "pwad_dir"));

    //[Port]
    myUi->le_exe->setText(readSettings(file, "Port", "port_exe"));
    myUi->le_adv_port_param->setText(readSettings(file, "Port", "additional_port_param"));
    myUi->le_adv_cmd_param->setText(readSettings(file, "Port", "additional_cmd_param"));

    if (readIntSettings(file, "Port", "water") == 1)
        myUi->cb_darkplaces_water->setChecked(true);

    //[Network]
    if (readIntSettings(file, "Network", "enabled") == 1)
        myUi->gb_join->setChecked(true);

    myUi->le_ip->setText(readSettings(file, "Network", "ip"));
    myUi->le_port->setText(readSettings(file, "Network", "ip_port"));
}

void Utils::baseConfig::writeSettings(const QString &file, const QString &group, const QString &value, const QString &var)
{
    QSettings settings(file, QSettings::IniFormat);
    settings.beginGroup(group);
    settings.setValue(value, var);
    settings.endGroup();
}

QString Utils::baseConfig::readSettings(const QString &file, const QString &group, const QString &value)
{
    QString rv;

    QSettings settings(file, QSettings::IniFormat);
    settings.beginGroup(group);
    rv = settings.value(value).toString();
    settings.endGroup();

    return rv;
}

void Utils::baseConfig::writeSettings(const QString &file, const QString &group, const QString &value, const short var)
{
    QSettings settings(file, QSettings::IniFormat);
    settings.beginGroup(group);
    settings.setValue(value, var);
    settings.endGroup();
}

int Utils::baseConfig::readIntSettings(const QString &file, const QString &group, const QString &value)
{
    int rv;

    QSettings settings(file, QSettings::IniFormat);
    settings.beginGroup(group);
    rv = settings.value(value).toInt();
    settings.endGroup();

    return rv;
}

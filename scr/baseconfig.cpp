#include "baseconfig.h"

baseConfig::baseConfig(Ui::MainWindow *ui)
{
    this->myUi = ui;
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

QString baseConfig::getDefaultProfile()
{
    getValues();

    QSettings settings(defaultSettings, QSettings::IniFormat);
    settings.beginGroup("settings");
    defaultProfile = settings.value("profile").toString();
    settings.endGroup();

    return profilesDir + defaultProfile;
}

QString baseConfig::getDefaultProfileName()
{
    getValues();

    QSettings settings(defaultSettings, QSettings::IniFormat);
    settings.beginGroup("settings");
    defaultProfile = settings.value("profile").toString();
    settings.endGroup();

    return defaultProfile;
}


/* ___             _   _
  | __|  _ _ _  __| |_(_)___ _ _  ___
  | _| || | ' \/ _|  _| / _ \ ' \(_-<
  |_| \_,_|_||_\__|\__|_\___/_||_/__/
*/

void baseConfig::setDefaultProfile(QString profile)
{
    getValues();

    QSettings settings(defaultSettings, QSettings::IniFormat);
    settings.beginGroup("Settings");
    settings.setValue("profile", profile);
    settings.endGroup();
}

void baseConfig::writeSettings(QString file)
{
    QSettings settings(file, QSettings::IniFormat);

    settings.beginGroup("WAD");
    settings.setValue("iwad_dir", myUi->le_iwad->text());
    settings.setValue("pwad_dir", myUi->le_pwad->text());
    settings.setValue("last_iwad",  iwad);
    settings.setValue("last_pwads", pwad);
    settings.endGroup();

    settings.beginGroup("Port");
    settings.setValue("port_exe", myUi->le_exe->text());
    settings.setValue("additional_port_param", myUi->le_adv_port_param->text());
    settings.setValue("additional_cmd_param", myUi->le_adv_cmd_param->text());
    settings.endGroup();
}

void baseConfig::readSettings(QString file)
{
    QFile f(file);
    if (!f.exists())
    {
        QMessageBox::critical(this, "", "Nobody, but us chicken! File does'n exist!");

        //delete item, don't know, if it's ugly code, but working
        QListWidgetItem *it = myUi->lw_profile->item(myUi->lw_profile->currentRow());
        delete it;

        return;
    }

    QSettings settings(file, QSettings::IniFormat);

    settings.beginGroup("WAD");
    myUi->le_iwad->setText(settings.value("iwad_dir").toString());
    myUi->le_pwad->setText(settings.value("pwad_dir").toString());
    iwad = settings.value("last_iwad").toString();
    pwad = settings.value("last_pwads").toString();
    settings.endGroup();

    settings.beginGroup("Port");
    myUi->le_exe->setText(settings.value("port_exe").toString());
    myUi->le_adv_port_param->setText(settings.value("additional_port_param").toString());
    myUi->le_adv_cmd_param->setText(settings.value("additional_cmd_param").toString());
    settings.endGroup();
}

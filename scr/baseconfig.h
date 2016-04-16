#ifndef BASECONFIG_H
#define BASECONFIG_H

#include <QWidget>
#include <QString>
#include <QDir>
#include <QSettings>
#include <QMessageBox>

#include "ui_mainwindow.h"

class baseConfig : public QWidget
{
public:
    baseConfig(Ui::MainWindow *ui);

    QString getDefaultProfile();
    QString getDefaultProfileName();
    QString getProfilesDir();
    QString getDefaultSettings();
    void setDefaultProfile(QString profile);
    void writeSettings(QString file);
    void readSettings(QString file);

    QString iwad;
    QString pwad;

private:
    Ui::MainWindow *myUi;

    QString home;
    QString defaultSettings;
    QString profilesDir;
    QString defaultProfile;

    void getValues();
};

#endif // BASECONFIG_H

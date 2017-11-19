#ifndef DESCRIPTIONSHANDLER_H
#define DESCRIPTIONSHANDLER_H

#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QFileInfo>
#include <QDebug>
#include <QDir>

#include "archives.h"
#include "ui_mainwindow.h"

class descriptionsHandler : protected utils::archives
{
public:
    explicit descriptionsHandler(Ui::MainWindow *ui);
    virtual ~descriptionsHandler();

    void readFromArchive(QString filePath);
    void getFullDescriptionFromFile(QString filePath);

    /*QString getPrimaryPurpose();

    QString getTitle();
    QString getRealiseDate();
    QString getVersion();
    QString getAuthor();
    QString getDiscription();*/

    //* What is included *
    /*QString getLevelsNumber();
    QString getNewSounds();
    QString getNewMusic();
    QString getNewGraphics();
    QString getDehackedBEXPatch();
    QString getDemos();
    QString getOther();
    QString getOtherFileRequired();*/

    //* Play Information *
    /*QString getGame(QString filePath);
    QString getMap();
    QString getSinglePlayer();
    QString getCooperative();
    QString getDeathmatch();
    QString getOtherGamesStyles();
    QString getDifficultySettings();*/

    QString readString(QString filePath, QString str);

private:
    Ui::MainWindow *myUi;
};

#endif // DESCRIPTIONSHANDLER_H

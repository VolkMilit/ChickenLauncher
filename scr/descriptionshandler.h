#ifndef DESCRIPTIONSHANDLER_H
#define DESCRIPTIONSHANDLER_H

#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

#include "archives.h"
#include "descriptionpopup.h"

class descriptionsHandler : private descriptionpopup
{
public:
    explicit descriptionsHandler();
    virtual ~descriptionsHandler();

    void readFromArchive(QString filePath);
    void getFullDescriptionFromFile(QString filePath);

private:
    QString getPrimaryPurpose();

    QString getTitle();
    QString getRealiseDate();
    QString getVersion();
    QString getAuthor();
    QString getDiscription();

    //* What is included *
    QString getLevelsNumber();
    QString getNewSounds();
    QString getNewMusic();
    QString getNewGraphics();
    QString getDehackedBEXPatch();
    QString getDemos();
    QString getOther();
    QString getOtherFileRequired();

    //* Play Information *
    QString getGame();
    QString getMap();
    QString getSinglePlayer();
    QString getCooperative();
    QString getDeathmatch();
    QString getOtherGamesStyles();
    QString getDifficultySettings();

    archives *Varchives;
};

#endif // DESCRIPTIONSHANDLER_H

#include "descriptionshandler.h"

descriptionsHandler::descriptionsHandler(Ui::MainWindow *ui)
{
    this->myUi = ui;
    Varchives = new archives();
}

descriptionsHandler::~descriptionsHandler()
{
    delete Varchives;
}

void descriptionsHandler::readFromArchive(QString filePath)
{
}

void descriptionsHandler::getFullDescriptionFromFile(QString filePath)
{
    myUi->pt_description->clear();

    const QStringList filter = QStringList() << ".zip" << ".wad" << ".pk7" << ".pk3"\
                                       << ".7z" << ".rar" << ".tar.*";

    for (auto i = 0; i < filter.length(); i++)
        filePath.remove(filter.at(i));

    QFile descr(filePath + ".txt");

    if(!descr.open(QIODevice::ReadOnly))
    {
        if (descr.errorString() == "No such file or directory")
            myUi->pt_description->appendPlainText("No description found for this wad, sorry about that :( *snob*");
        return;
    }

    QTextStream stream(&descr);

    myUi->pt_description->appendPlainText(stream.readAll());
    myUi->pt_description->moveCursor(QTextCursor::Start);

    descr.close();
}

QString descriptionsHandler::readString(QString filePath, QString str)
{
    QFile file(filePath);
    QString fileName = QFileInfo(file).dir().absolutePath() + "/" + QFileInfo(file).baseName() + ".txt";
    QFile descr(fileName);
    descr.open(QIODevice::ReadOnly);
    QTextStream stream(&descr);

    QString flines = stream.readAll();
    QStringList line = flines.split("\n");

    QString ret;

    foreach (QString s, line)
    {
       if (s.contains(str))
       {
            ret = s;
            break;
       }
    }

    file.close();
    descr.close();

    return ret;
}

/*QString descriptionsHandler::getPrimaryPurpose()
{

}

QString descriptionsHandler::getTitle()
{

}

QString descriptionsHandler::getRealiseDate()
{

}

QString descriptionsHandler::getVersion()
{

}

QString descriptionsHandler::getAuthor()
{

}

QString descriptionsHandler::getDiscription()
{

}

QString descriptionsHandler::getLevelsNumber()
{

}

QString descriptionsHandler::getNewSounds()
{

}

QString descriptionsHandler::getNewMusic()
{

}

QString descriptionsHandler::getNewGraphics()
{

}

QString descriptionsHandler::getDehackedBEXPatch()
{

}

QString descriptionsHandler::getDemos()
{

}

QString descriptionsHandler::getOther()
{

}

QString descriptionsHandler::getOtherFileRequired()
{

}

QString descriptionsHandler::getGame(QString filePath)
{

}

QString descriptionsHandler::getMap()
{

}

QString descriptionsHandler::getSinglePlayer()
{

}

QString descriptionsHandler::getCooperative()
{

}

QString descriptionsHandler::getDeathmatch()
{

}

QString descriptionsHandler::getOtherGamesStyles()
{

}

QString descriptionsHandler::getDifficultySettings()
{

}*/



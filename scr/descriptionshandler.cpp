#include "descriptionshandler.h"

descriptionsHandler::descriptionsHandler() : descriptionpopup()
{
    Varchives = new archives();
}

descriptionsHandler::~descriptionsHandler()
{
    delete Varchives;
}

void descriptionsHandler::readFromArchive(QString filePath)
{
    //if (Varchives->open(filePath, filePath))
    //{
        showFullDescription(filePath, Varchives->returnText());
        show();
    /*}
    else
    {
        QMessageBox::information(this, "Chicken Launcher", "There is a problem opening archive file.", QMessageBox::Ok);
    }*/
}

void descriptionsHandler::getFullDescriptionFromFile(QString filePath)
{
    QFile file(filePath);

    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(0, "Error reading description. File doesn't\
                exist or you don't have permitions to read.", file.errorString());
        return;
    }

    QTextStream in(&file);

    showFullDescription(filePath, in.readAll());
    show();

    file.close();
}

QString descriptionsHandler::getPrimaryPurpose()
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

QString descriptionsHandler::getGame()
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

}



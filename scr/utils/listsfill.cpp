#include "listsfill.h"
#include <QDebug>

Utils::listFill::listFill(Ui::MainWindow *ui) :
    VbaseConfig(new baseConfig(ui)),
    Vcolors(new Utils::colors()),
    Vgzdoom(new gzdoom(ui))
{
    this->myUi = ui;

    //       name      idTechLevel      idEngine
    //       name of the port, that was been displayed
    //       idTechLevel idTech engine using: 1 - DOOM, Hexen, Heretic, etc;
    //                                        2 - Quake 1,2; Hexen II;
    //                                        3 - Quake 3, Wolfenstein: Enimy Territory;
    //                                        4 - Doom 3, Quake 4, Enemy Territory: Quake Wars;
    //                                        5 - Rage;
    //                                        6 - Doom (2016);
    //       This need if programmers want to add some port, that have some futures, that for example id Tech 1
    //       doesn't supporting.
    //       Chart here: https://upload.wikimedia.org/wikipedia/commons/8/85/Quake_-_family_tree_2.svg
    //       Sadly we don't have open source and free alternative for levels 5 and 6, since ZiniMax not that
    //       open for community. Fuck you, ZiniMax!

    games.push_back(QPair<QString, short>("GZDoom", 1));
    games.push_back(QPair<QString, short>("DarkPlaces", 2));
    games.push_back(QPair<QString, short>("UHexen2", 2));
}

Utils::listFill::~listFill()
{
    delete Vcolors;
    delete VbaseConfig;
    delete Vgzdoom;
}

inline QString Utils::listFill::pathHelper(const QString &widgetpath)
{
    QString path = "";
    if (!VbaseConfig->getOffWadPath())
    {
        path = widgetpath;
        if (!QString(path.at(path.length()-1)).contains("/"))
            path += "/";
    }

    return path;
}

QVector<QPair<QString, short>> Utils::listFill::getGamesList()
{
    return games;
}

void Utils::listFill::getIWadList()
{
    myUi->lw_iwad->clear();

    const QString path = pathHelper(myUi->le_iwad->text());
    const QColor color = Vcolors->getColor();
    const QStringList filter = QStringList() << "*.zip" << "*.wad" << "*.pk7" << "*.pk3"\
                                       << "*.7z" << "*.rar" << "*.tar.*";
    const QString lastIwad = VbaseConfig->getLastIwad();

    QDir iwad_dir(VbaseConfig->getIwadDir());
    if(!iwad_dir.exists())
        iwad_dir = QDir::currentPath();

    const QStringList IWAD_files = iwad_dir.entryList(filter, QDir::Files);
    for (auto ifiles : IWAD_files)
    {
        QListWidgetItem *item = new QListWidgetItem(myUi->lw_iwad);
        item->setText(path + ifiles);

        if (item->text() == path + lastIwad)
            item->setForeground(color);
    }
}

void Utils::listFill::getPWadList()
{
    myUi->lw_pwad->clear();
    QStringList PWAD_files;

    const QString path = pathHelper(myUi->le_pwad->text());
    QStringList pwad_list = VbaseConfig->getLastPwad().split("#");
    const QColor color = Vcolors->getColor();
    const QStringList filter = QStringList() << "*.zip" << "*.wad" << "*.pk7" << "*.pk3"\
                                       << "*.7z" << "*.rar" << "*.tar.*";

    QDir pwad_dir(VbaseConfig->getPwadDir());
    if(!pwad_dir.exists())
        pwad_dir = QDir::currentPath();

    if (VbaseConfig->getGamePort() >= 1) // darkplaces, uhexen, other idTech games
        PWAD_files = pwad_dir.entryList(QStringList(), QDir::Dirs | QDir::NoDotAndDotDot);
    else // gzdoom, zdoom, qzdoom, and forks
        PWAD_files = pwad_dir.entryList(filter, QDir::Files);

    for (auto pfiles : PWAD_files)
    {
        QListWidgetItem *item = new QListWidgetItem(myUi->lw_pwad);
        item->setText(path + pfiles);
        item->setCheckState(Qt::Unchecked);

        for (auto lastpwad : pwad_list)
        {
            if (item->text() == path + lastpwad)
            {
                item->setCheckState(Qt::Checked);
                item->setForeground(color);
            }
        }
    }
}

void Utils::listFill::getProfiles()
{
    myUi->lw_profile->clear();
    myUi->ltw_profile->clear();

    QDir dir(VbaseConfig->getProfilesDir());
    const QStringList ini_files = dir.entryList(QStringList() << "*.ini", QDir::Files);
    const QColor color = Vcolors->getColor();
    const QString getCurrentProfileName = VbaseConfig->getDefaultProfileName();

    if (ini_files.isEmpty())
        VbaseConfig->readAllSettings(dir.absolutePath() + "/default.ini");

    for (int i = 0; i < ini_files.length(); i++)
    {
        QTableWidgetItem *item0 = new QTableWidgetItem;
        item0->setText(ini_files.at(i));

        QTableWidgetItem *item1 = new QTableWidgetItem;
        const short game = VbaseConfig->readIntSettings(dir.absolutePath() + "/" + ini_files.at(i), "Port", "game_port");
        item1->setText(games.at(game).first);

        myUi->ltw_profile->insertRow(i);

        myUi->ltw_profile->setItem(i, 0, item0);
        myUi->ltw_profile->setItem(i, 1, item1);

        myUi->lw_profile->addItem(ini_files.at(i));

        if (myUi->lw_profile->item(i)->text() == getCurrentProfileName)
        {
            myUi->lw_profile->item(i)->setForeground(color);
            myUi->ltw_profile->item(i, 0)->setForeground(color);
        }
    }
}

void Utils::listFill::getPortConfigFile()
{
    myUi->lw_port_configs_files->clear();
    myUi->lw_port_configs_files->addItem("default");

    QDir dir(Vgzdoom->getGzdoomHomeDir());
    QStringList ini_files = dir.entryList(QStringList() << "*.ini", QDir::Files);
    ini_files.removeOne("gzdoom.ini");
    ini_files.removeOne("zdoom.ini");

    const QColor color = Vcolors->getColor();
    const QString getCurrentConfigFile = VbaseConfig->getConfigFile();

    for (int i = 0; i < ini_files.length(); i++)
    {
        myUi->lw_port_configs_files->addItem(ini_files.at(i));

        if (myUi->lw_port_configs_files->item(i)->text() == getCurrentConfigFile)
            myUi->lw_port_configs_files->item(i)->setForeground(color);
    }
}

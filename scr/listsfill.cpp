#include "listsfill.h"
#include <QDebug>

utils::listFill::listFill(Ui::MainWindow *ui)
{
    this->myUi = ui;
    VbaseConfig = new config::baseConfig(ui);
    Vcolors = new utils::colors();
    Vgzdoom = new Launcher::gzdoom(ui);
}

utils::listFill::~listFill(){}

void utils::listFill::setOffPathWad(bool set)
{
    if (set)
        offPathWad = 1;
    else
        offPathWad = 0;

    VbaseConfig->setOffWadPath(VbaseConfig->getLauncherSettingsFile(), offPathWad);
}

int utils::listFill::getOffPathWad()
{
    return offPathWad;
}

void utils::listFill::getIWadList()
{
    myUi->lw_iwad->clear();

    QString path = "";
    const QString profile = VbaseConfig->getCurrentProfile();
    const QColor color = Vcolors->getColor();
    const QStringList filter = QStringList() << "*.zip" << "*.wad" << "*.pk7" << "*.pk3"\
                                       << "*.7z" << "*.rar" << "*.tar.*";
    const QString lastIwad = VbaseConfig->getLastIwad(profile);

    QDir iwad_dir(VbaseConfig->getIwadDir(profile));
    if(!iwad_dir.exists())
        iwad_dir = QDir::currentPath();

    if (VbaseConfig->getOffWadPath(VbaseConfig->getLauncherSettingsFile()) == 0) //see comment in listfill.h
        path = iwad_dir.absolutePath() + "/";

    const QStringList IWAD_files = iwad_dir.entryList(filter, QDir::Files);
    for (int i = 0; i < IWAD_files.length(); i++)
    {
        myUi->lw_iwad->addItem(path + IWAD_files.at(i));

        if (myUi->lw_iwad->item(i)->text() == lastIwad)
            myUi->lw_iwad->item(i)->setForeground(color);
    }
}

void utils::listFill::getPWadList()
{
    myUi->lw_pwad->clear();

    QString path = "";
    const QString profile = VbaseConfig->getCurrentProfile();
    QStringList pwad_list = VbaseConfig->getLastPwad(profile).split("#");
    const QColor color = Vcolors->getColor();
    const QStringList filter = QStringList() << "*.zip" << "*.wad" << "*.pk7" << "*.pk3"\
                                       << "*.7z" << "*.rar" << "*.tar.*";

    QDir pwad_dir(VbaseConfig->getPwadDir(profile));
    if(!pwad_dir.exists())
        pwad_dir = QDir::currentPath();

    if (VbaseConfig->getOffWadPath(VbaseConfig->getLauncherSettingsFile()) == 0) //see comment in listfill.h
        path = pwad_dir.absolutePath() + "/";

    const QStringList PWAD_files = pwad_dir.entryList(filter, QDir::Files);

    for (auto i = 0; i < PWAD_files.length(); i++)
    {
        myUi->lw_pwad->addItem(PWAD_files.at(i));
        myUi->lw_pwad->item(i)->setCheckState(Qt::Unchecked);
    }

    for (auto i = 0; i < myUi->lw_pwad->count(); i++)
    {
        for (auto j = 0; j < pwad_list.length()-1; j++)
        {
            QListWidgetItem *item = myUi->lw_pwad->item(i);

            if (item->text() == pwad_list.at(j))
                delete myUi->lw_pwad->takeItem(i);
        }
    }

    for (auto i = 0; i < pwad_list.length()-1; i++)
    {
        myUi->lw_pwad->insertItem(i, pwad_list.at(i));
        myUi->lw_pwad->item(i)->setCheckState(Qt::Checked);
        myUi->lw_pwad->item(i)->setForeground(color);
    }
}

void utils::listFill::getProfiles()
{
    myUi->lw_profile->clear();

    QDir dir(VbaseConfig->getProfilesDir());
    const QStringList ini_files = dir.entryList(QStringList() << "*.ini", QDir::Files);
    const QColor color = Vcolors->getColor();
    const QString getCurrentProfileName = VbaseConfig->getDefaultProfileName();

    if (ini_files.isEmpty())
        VbaseConfig->readAllSettings(dir.absolutePath() + "/default.ini");

    for (int i = 0; i < ini_files.length(); i++)
    {
        myUi->lw_profile->addItem(ini_files.at(i));

        if (myUi->lw_profile->item(i)->text() == getCurrentProfileName)
            myUi->lw_profile->item(i)->setForeground(color);
    }
}

void utils::listFill::getPortConfigFile()
{
    myUi->lw_port_configs_files->clear();
    myUi->lw_port_configs_files->addItem("default");

    QDir dir(Vgzdoom->getGzdoomHomeDir());
    QStringList ini_files = dir.entryList(QStringList() << "*.ini", QDir::Files);
    ini_files.removeOne("gzdoom.ini");
    ini_files.removeOne("zdoom.ini");

    const QColor color = Vcolors->getColor();
    const QString getCurrentConfigFile = VbaseConfig->getConfigFile(VbaseConfig->getCurrentProfile());

    for (int i = 0; i < ini_files.length(); i++)
    {
        myUi->lw_port_configs_files->addItem(ini_files.at(i));

        if (myUi->lw_port_configs_files->item(i)->text() == getCurrentConfigFile)
            myUi->lw_port_configs_files->item(i)->setForeground(color);
    }
}

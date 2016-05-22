#include "listsfill.h"

listFill::listFill(Ui::MainWindow *ui)
{
    this->myUi = ui;
    VbaseConfig = new baseConfig(ui);
    Vcolors = new colors(ui);
}

listFill::~listFill()
{
    delete VbaseConfig;
    delete Vcolors;
    delete myUi;
}

void listFill::setOffPathWad(bool set)
{
    if (set)
        offPathWad = "true";
    else
        offPathWad = "false";

    VbaseConfig->setOffWadPath(VbaseConfig->getDefaultSettings(), offPathWad);
}

QString listFill::getOffPathWad()
{
    return offPathWad;
}

void listFill::getIWadList()
{
    QString path = "";
    QString profile = VbaseConfig->getDefaultProfile();

    myUi->lw_iwad->clear();

    QStringList filter = QStringList() << "*.zip" << "*.wad" << "*.pk7" << "*.pk3" << "*.7z" << "*.rar" << "*.tar.*";

    QDir iwad_dir(VbaseConfig->getIwadDir(profile));
    if(!iwad_dir.exists())
        iwad_dir = QDir::currentPath();

    if (VbaseConfig->getOffWadPath(VbaseConfig->getDefaultSettings()) == "false") //see comment in listfill.h
        path = iwad_dir.absolutePath() + "/";

    QStringList IWAD_files = iwad_dir.entryList(filter, QDir::Files);
    for (int i = 0; i < IWAD_files.length(); i++)
    {
        myUi->lw_iwad->addItem(path + IWAD_files.at(i));

        if (myUi->lw_iwad->item(i)->text() == VbaseConfig->getLastIwad(profile))        
            myUi->lw_iwad->item(i)->setForeground(Vcolors->getColor());
    }
}

void listFill::getPWadList()
{
    QString path = "";
    QString profile = VbaseConfig->getDefaultProfile();
    QStringList pwad_list = VbaseConfig->getLastPwad(profile).split(" ");

    myUi->lw_pwad->clear();

    QStringList filter = QStringList() << "*.zip" << "*.wad" << "*.pk7" << "*.pk3" << "*.7z" << "*.rar" << "*.tar.*";

    QDir pwad_dir(VbaseConfig->getPwadDir(profile));
    if(!pwad_dir.exists())
        pwad_dir = QDir::currentPath();

    if (VbaseConfig->getOffWadPath(VbaseConfig->getDefaultSettings()) == "false") //see comment in listfill.h
        path = pwad_dir.absolutePath() + "/";

    QStringList PWAD_files = pwad_dir.entryList(filter, QDir::Files);
    for (int i = 0; i < PWAD_files.length(); i++)
    {
        myUi->lw_pwad->addItem(path + PWAD_files.at(i));
        myUi->lw_pwad->item(i)->setCheckState(Qt::Unchecked);

        for (int j = 0; j < pwad_list.length(); j++)
        {
            if (myUi->lw_pwad->item(i)->text() == pwad_list.at(j))
            {
                myUi->lw_pwad->item(i)->setCheckState(Qt::Checked);
                myUi->lw_pwad->item(i)->setForeground(Vcolors->getColor());
            }
        }
    }
}

void listFill::getProfiles()
{
    myUi->lw_profile->clear();

    QDir dir(VbaseConfig->getProfilesDir());
    QStringList ini_files = dir.entryList(QStringList() << "*.ini", QDir::Files);

    if (ini_files.isEmpty())
        VbaseConfig->readAllSettings(VbaseConfig->getProfilesDir() + "default.ini");

    for (int i = 0; i < ini_files.length(); i++)
    {
        myUi->lw_profile->addItem(ini_files.at(i));

        if (myUi->lw_profile->item(i)->text() == VbaseConfig->getDefaultProfileName())
            myUi->lw_profile->item(i)->setForeground(Vcolors->getColor());
    }
}

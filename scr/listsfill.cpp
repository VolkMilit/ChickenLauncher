#include "listsfill.h"

listFill::listFill(Ui::MainWindow *ui)
{
    this->myUi = ui;
    VbaseConfig = new baseConfig(ui);
}

listFill::~listFill()
{
    delete VbaseConfig;
}

void listFill::getWadList()
{
    VbaseConfig->readSettings(VbaseConfig->getDefaultProfile());

    myUi->lw_iwad->clear();
    myUi->lw_pwad->clear();

    QStringList filter = QStringList() << "*.zip" << "*.wad" << "*.pk7" << "*.pk3" << "*.7z" << "*.rar" << "*.tar.*";

    QDir iwad_dir(myUi->le_iwad->text());
    if(!iwad_dir.exists())
        iwad_dir = QDir::currentPath();

    QDir pwad_dir(myUi->le_pwad->text());
    if(!pwad_dir.exists())
        pwad_dir = QDir::currentPath();

    QStringList IWAD_files = iwad_dir.entryList(filter, QDir::Files);
    for (int i = 0; i < IWAD_files.length(); i++)
    {
        myUi->lw_iwad->addItem(iwad_dir.absolutePath() + "/" + IWAD_files.at(i));

        if (myUi->lw_iwad->item(i)->text() == VbaseConfig->iwad)
            myUi->lw_iwad->item(i)->setForeground(Qt::green);
    }

    QStringList pwad_list = VbaseConfig->pwad.split(" ");

    QStringList PWAD_files = pwad_dir.entryList(filter, QDir::Files);
    for (int i = 0; i < PWAD_files.length(); i++)
    {
        myUi->lw_pwad->addItem(pwad_dir.absolutePath() + "/" + PWAD_files.at(i));

        for (int j = 0; j < pwad_list.length(); j++)
            if (myUi->lw_pwad->item(i)->text() == pwad_list.at(j))
                myUi->lw_pwad->item(i)->setForeground(Qt::green);
    }
}

void listFill::getProfiles()
{
    VbaseConfig->readSettings(VbaseConfig->getDefaultProfile());

    myUi->lw_profile->clear();

    QDir dir(VbaseConfig->getProfilesDir());
    QStringList ini_files = dir.entryList(QStringList() << "*.ini", QDir::Files);

    if (ini_files.isEmpty())
        VbaseConfig->writeSettings(VbaseConfig->getProfilesDir() + "default.ini");

    for (int i = 0; i < ini_files.length(); i++)
    {
        myUi->lw_profile->addItem(ini_files.at(i));

        if (myUi->lw_profile->item(i)->text() == VbaseConfig->getDefaultProfileName())
            myUi->lw_profile->item(i)->setForeground(Qt::green);
    }
}

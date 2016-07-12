#include "listsfill.h"
#include <QDebug>

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
    myUi->lw_iwad->clear();

    QString path = "";
    const QString profile = VbaseConfig->getDefaultProfile();
    const QColor color = Vcolors->getColor();
    const QStringList filter = QStringList() << "*.zip" << "*.wad" << "*.pk7" << "*.pk3"\
                                       << "*.7z" << "*.rar" << "*.tar.*";
    const QString lastIwad = VbaseConfig->getLastIwad(profile);

    QDir iwad_dir(VbaseConfig->getIwadDir(profile));
    if(!iwad_dir.exists())
        iwad_dir = QDir::currentPath();

    if (VbaseConfig->getOffWadPath(VbaseConfig->getDefaultSettings()) == "false") //see comment in listfill.h
        path = iwad_dir.absolutePath() + "/";

    const QStringList IWAD_files = iwad_dir.entryList(filter, QDir::Files);
    for (int i = 0; i < IWAD_files.length(); i++)
    {
        myUi->lw_iwad->addItem(path + IWAD_files.at(i));

        if (myUi->lw_iwad->item(i)->text() == lastIwad)
            myUi->lw_iwad->item(i)->setForeground(color);
    }
}

void listFill::getPWadList()
{
    myUi->lw_pwad->clear();

    QString path = "";
    const QString profile = VbaseConfig->getDefaultProfile();
    pwad_list = VbaseConfig->getLastPwad(profile).split(" ");
    const QColor color = Vcolors->getColor();
    const QStringList filter = QStringList() << "*.zip" << "*.wad" << "*.pk7" << "*.pk3"\
                                       << "*.7z" << "*.rar" << "*.tar.*";
    int index = -1;

    QDir pwad_dir(VbaseConfig->getPwadDir(profile));
    if(!pwad_dir.exists())
        pwad_dir = QDir::currentPath();

    if (VbaseConfig->getOffWadPath(VbaseConfig->getDefaultSettings()) == "false") //see comment in listfill.h
        path = pwad_dir.absolutePath() + "/";

    const QStringList PWAD_files = pwad_dir.entryList(filter, QDir::Files);
    QListWidgetItem *temp;
    for (int i = 0; i < PWAD_files.length(); i++)
    {
        myUi->lw_pwad->addItem(path + PWAD_files.at(i));
        myUi->lw_pwad->item(i)->setCheckState(Qt::Unchecked);

        for (int j = 0; j < pwad_list.length(); j++)
        {
            if (myUi->lw_pwad->item(i)->text() == pwad_list.at(j))
            {
                myUi->lw_pwad->item(i)->setCheckState(Qt::Checked);
                myUi->lw_pwad->item(i)->setForeground(color);

                // sort, all item from pwad_list on top
                temp = myUi->lw_pwad->takeItem(i);
                myUi->lw_pwad->insertItem(index++, temp);
            }
        }
    }
}

void listFill::getProfiles()
{
    myUi->lw_profile->clear();

    QDir dir(VbaseConfig->getProfilesDir());
    const QStringList ini_files = dir.entryList(QStringList() << "*.ini", QDir::Files);
    const QColor color = Vcolors->getColor();
    const QString getDefaultProfileName = VbaseConfig->getDefaultProfileName();

    if (ini_files.isEmpty())
        VbaseConfig->readAllSettings(VbaseConfig->getProfilesDir() + "default.ini");

    for (int i = 0; i < ini_files.length(); i++)
    {
        myUi->lw_profile->addItem(ini_files.at(i));

        if (myUi->lw_profile->item(i)->text() == getDefaultProfileName)
            myUi->lw_profile->item(i)->setForeground(color);
    }
}

void listFill::updateColors()
{
    // not inplemented yet
}

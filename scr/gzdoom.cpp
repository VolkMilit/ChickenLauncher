#include "gzdoom.h"

gzdoom::gzdoom(Ui::MainWindow *ui)
{
    this->myUi = ui;

    VbaseConfig = new baseConfig(ui);
    Vfunctions = new functions();

    process = new QProcess(this);
}

gzdoom::~gzdoom()
{
    delete VbaseConfig;
}

void gzdoom::parametrParser()
{
    if (myUi->lw_iwad->currentItem() != nullptr && VbaseConfig->iwad.isEmpty())
    {
        VbaseConfig->pwad = "";
        foreach(QListWidgetItem *item, myUi->lw_pwad->selectedItems())
            VbaseConfig->pwad += item->text() + " ";

        VbaseConfig->iwad = "";
        if (myUi->lw_iwad->currentItem() != nullptr)
            VbaseConfig->iwad = myUi->lw_iwad->currentItem()->text();

        VbaseConfig->writeSettings(VbaseConfig->getDefaultProfile());
    }
    else
        VbaseConfig->readSettings(VbaseConfig->getDefaultProfile());

    skill = "";
    if (myUi->cb_skill->isChecked())
        skill = QString::number(myUi->cob_skill->currentIndex());

    exe = "";
    if (!myUi->le_exe->text().isEmpty())
        exe = myUi->le_exe->text();
    else
        exe = "gzdoom";

    if (!myUi->le_exe->text().isEmpty())
        exe = myUi->le_exe->text();

    nomusic = "";
    if (myUi->cb_nomusic->isChecked())
        nomusic = " -nomusic ";

    nosound = "";
    if (myUi->cb_nosound->isChecked())
        nosound = " -nosound ";

    nosfx = "";
    if (myUi->cb_nosfx->isChecked())
        nosfx = " -nosfx ";

    map = "";
    if (!myUi->le_map->text().isEmpty())
    {
        map = " -warp " + myUi->le_map->text();
        if (myUi->le_map->text().at(0) == QChar('E', false) && myUi->le_map->text().at(2) == QChar('M', false))
            map = " -warp " + myUi->le_map->text().mid(1,1) + " " + myUi->le_map->text().mid(3,3);
    }

    demo = "";
    QDateTime dt;
    if (myUi->cb_recorddemo->isChecked())
        demo = " -record " + dt.currentDateTime().toString("yyyy-MM-dd_H:mm:s") + ".lmp";

    oldsprites = "";
    if (myUi->cb_oldsprites->isChecked())
        oldsprites = " -oldsprites ";

    noautoload = "";
    if (myUi->cb_noautoload->isChecked())
        noautoload = " -noautoload ";

    nostartup = "";
    if (myUi->cb_nostartup->isChecked())
        nostartup = " -nostartup ";
}

void gzdoom::startDemo()
{
    if (!myUi->le_playdemo->text().isEmpty())
        process->start(exe + " -playdemo " + myUi->le_playdemo->text());
    else if (!myUi->le_playdemo_2->text().isEmpty())
        process->start(exe + " -timedemo " + myUi->le_playdemo_2->text());
}

void gzdoom::networkGame()
{
    process->start(exe + " -join " + myUi->le_ip->text() + ":" + myUi->le_port->text());
}

void gzdoom::startGzdoom()
{
    parametrParser();

    if (myUi->lw_iwad->currentItem() == nullptr && VbaseConfig->iwad.isEmpty())
    {
        myUi->tabWidget->setCurrentIndex(1);
        QMessageBox::information(this, "", tr("Choose at least one IWAD."));
    }
    else
    {
        term = "";
        if (!Vfunctions->isNT())
            term = "x-terminal-emulator -e ";

        loadgame = "";
        if (!myUi->le_loadgame->text().isEmpty())
            loadgame = " -loadgame " + myUi->le_loadgame->text();

        process->start(
                       term +\
                       myUi->le_adv_cmd_param->text() + " " +\
                       exe +\
                       " -iwad " + VbaseConfig->iwad +\
                       " -file " + VbaseConfig->pwad +\
                       "-skill " + skill +\
                       map + " " +\
                       myUi->le_adv_port_param->text() +\
                       nomusic +\
                       nosound +\
                       nosfx +\
                       demo +\
                       oldsprites +\
                       noautoload +\
                       nostartup +\
                       loadgame\
                      );

        /*Vfunctions->showHideMainWindow();

        if (process->waitForFinished())
            Vfunctions->showHideMainWindow();*/

        //deяrp! 6_9
    }
}

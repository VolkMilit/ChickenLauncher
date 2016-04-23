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
    delete Vfunctions;
    delete process;
    delete myUi;
}

void gzdoom::parametrParser()
{
    QString profile = VbaseConfig->getDefaultProfile();

    iwad = VbaseConfig->getLastIwad(profile);
    if (iwad.isEmpty())
    {
        QMessageBox::critical(this, "Chicken Launcher", "IWad is not set!", QMessageBox::Ok);
        return;
    }

    pwad = "";
    skill = "";
    exe = "";
    nomusic = "";
    nosound = "";
    nosfx = "";
    map = "";
    demo = "";
    oldsprites = "";
    noautoload = "";
    nostartup = "";

    //FILE
    if (!VbaseConfig->getLastPwad(profile).isEmpty())
         pwad = " -file " + VbaseConfig->getLastPwad(profile);

    //SKILL
    if (myUi->cb_skill->isChecked())
        skill = "-skill " + QString::number(myUi->cob_skill->currentIndex());

    //EXE
    if (myUi->le_exe->text().isEmpty())
        exe = "gzdoom";
    else
        exe = myUi->le_exe->text();

    //NOMUSIC
    if (myUi->cb_nomusic->isChecked())
        nomusic = " -nomusic ";

    //NOSOUND
    if (myUi->cb_nosound->isChecked())
        nosound = " -nosound ";

    //NOSFX
    if (myUi->cb_nosfx->isChecked())
        nosfx = " -nosfx ";

    //MAP
    if (!myUi->le_map->text().isEmpty())
    {
        map = " -warp " + myUi->le_map->text();
        if (myUi->le_map->text().at(0) == QChar('E', false) && myUi->le_map->text().at(2) == QChar('M', false))
            map = " -warp " + myUi->le_map->text().mid(1,1) + " " + myUi->le_map->text().mid(3,3);
    }

    //RECORD
    QDateTime dt;
    if (myUi->cb_recorddemo->isChecked())
        demo = " -record " + dt.currentDateTime().toString("yyyy-MM-dd_H:mm:s") + ".lmp";

    //OLDSPRITES
    if (myUi->cb_oldsprites->isChecked())
        oldsprites = " -oldsprites ";

    //NOAUTOLOAD
    if (myUi->cb_noautoload->isChecked())
        noautoload = " -noautoload ";

    //NOSTARTUP
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

    if (myUi->lw_iwad->currentItem() == nullptr && \
            VbaseConfig->getLastIwad(VbaseConfig->getDefaultProfile()).isEmpty())
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
                       " -iwad " + iwad +\
                       pwad +\
                       skill +\
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
    }
}

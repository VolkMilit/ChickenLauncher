#include "gzdoom.h"
#include <QDebug>

gzdoom::gzdoom(Ui::MainWindow *ui) :
    VbaseConfig(new Utils::baseConfig(myUi))
{
    this->myUi = ui;
    process = new QProcess(this);
}

gzdoom::~gzdoom()
{
    delete process;
    delete VbaseConfig;
}

QString gzdoom::getGzdoomHomeDir()
{
    QString home = "";

    #ifdef _WIN32
        home = QDir::homePath() + "\\ApplicationData\\gzdoom\\";
    #else
        home = QDir::homePath() + "/.config/gzdoom/";
    #endif

    return home;
}

void gzdoom::parametrParser()
{
    if (VbaseConfig->getOffWadPath() == 1)
        iwad = VbaseConfig->getIwadDir() + "/" + VbaseConfig->getLastIwad();
    else
        iwad = VbaseConfig->getLastIwad();

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
    config = "";
    advport = "";
    advcmd = "";

    //FILE
    if (!VbaseConfig->getLastPwad().isEmpty())
    {
        const QStringList pfile = VbaseConfig->getLastPwad().split("#");

        for(int i = 0; i < pfile.length()-1; i++)
            pwad = pwad + " -file " + VbaseConfig->getPwadDir() + "/" + pfile.at(i);
    }

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

    //CONFIG
    if (VbaseConfig->getConfigFile() == "default")
        config = "";
    else
        config = " -config " + getGzdoomHomeDir() + VbaseConfig->getConfigFile();

    //
    advcmd = myUi->le_adv_cmd_param->text() + " ";
    advport = myUi->le_adv_port_param->text();
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
    QString app = "";

    parametrParser();

    if (myUi->lw_iwad->currentItem() == nullptr && \
            VbaseConfig->getLastIwad().isEmpty()
       )
    {
        myUi->tabWidget->setCurrentIndex(1);
        QMessageBox::information(this, "", "Choose at least one IWAD.");
    }
    else
    {
        term = "";
        #ifdef _WIN32
            term = "";
        #else
            term = "x-terminal-emulator -e ";
        #endif

        loadgame = "";
        if (!myUi->le_loadgame->text().isEmpty())
            loadgame = " -loadgame " + myUi->le_loadgame->text();

        app = term + advcmd + exe + " -iwad " + iwad + " "\
                + pwad + skill + map + nomusic + nosfx\
                + demo + oldsprites + noautoload + nostartup\
                + loadgame + config + advport;

        qDebug() << app;

        process->start(app);
    }
}

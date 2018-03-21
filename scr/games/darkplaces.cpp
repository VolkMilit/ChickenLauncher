#include "darkplaces.h"
#include <QDebug>

Games::darkplaces::darkplaces(Ui::MainWindow *ui) :
    VbaseConfig(new Utils::baseConfig(myUi))
{
    this->myUi = ui;
    process = new QProcess(this);
}

Games::darkplaces::~darkplaces()
{
    delete process;
    delete VbaseConfig;
}

void Games::darkplaces::parametrParser()
{
    basedir = myUi->le_pwad->text();

    if (!VbaseConfig->getLastPwad().isEmpty())
    {
        const QStringList pfile = VbaseConfig->getLastPwad().split("#");

        for(int i = 0; i < pfile.length()-1; i++)
            games += " -game " + pfile.at(i);
    }

    if (myUi->le_exe->text().isEmpty())
        exe = "darkplaces";
    else
        exe = myUi->le_exe->text();

    if (myUi->cb_darkplaces_water->isChecked())
        consolecomm += " +r_water \"1\" ";
    else
        consolecomm += " +r_water \"0\" ";
}

void Games::darkplaces::startDarkplaces()
{
    QString app = "";

    parametrParser();

    term = "";
    #ifdef _WIN32
        term = "";
    #else
        term = "x-terminal-emulator -e ";
    #endif

    app = term + exe + " -basedir " + basedir + games + consolecomm;
    process->start(app);
}

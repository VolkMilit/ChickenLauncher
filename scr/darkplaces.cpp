#include "darkplaces.h"
#include <QDebug>

Launcher::darkplaces::darkplaces(Ui::MainWindow *ui) :
    VbaseConfig(new baseConfig(myUi))
{
    this->myUi = ui;
    process = new QProcess(this);
}

Launcher::darkplaces::~darkplaces()
{
    delete process;
}

void Launcher::darkplaces::parametrParser()
{
    basedir = myUi->le_pwad->text();

    if (!VbaseConfig->getLastPwad().isEmpty())
    {
        const QStringList pfile = VbaseConfig->getLastPwad().split("#");

        for(int i = 0; i < pfile.length()-1; i++)
            games = games + " -game " + pfile.at(i);
    }

    if (myUi->le_exe->text().isEmpty())
        exe = "darkplaces";
    else
        exe = myUi->le_exe->text();
}

void Launcher::darkplaces::startDarkplaces()
{
    QString app = "";

    parametrParser();

    term = "";
    #ifdef _WIN32
        term = "";
    #else
        term = "x-terminal-emulator -e ";
    #endif

    app = term + exe + " -basedir " + basedir + games;
    process->start(app);
}

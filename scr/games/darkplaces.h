#ifndef DARKPLACES_H
#define DARKPLACES_H

#include <QProcess>
#include <QMessageBox>

#include "ui_mainwindow.h"
#include "utils/baseconfig.h"

namespace Games
{
    class darkplaces : public QWidget
    {
        public:
            explicit darkplaces(Ui::MainWindow *ui);
            virtual ~darkplaces();
            QProcess *process;

            void startDarkplaces();

        private:
            Ui::MainWindow *myUi;
            Utils::baseConfig *VbaseConfig;

            void parametrParser();

            QString basedir;
            QString games;
            QString term;
            QString exe;
            QString consolecomm;
    };
}

#endif // DARKPLACES_H

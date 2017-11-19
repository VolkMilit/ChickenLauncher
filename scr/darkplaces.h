#ifndef DARKPLACES_H
#define DARKPLACES_H

#include <QProcess>
#include <QMessageBox>

#include "ui_mainwindow.h"
#include "baseconfig.h"
#include "outputreader.h"

namespace Launcher
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
            baseConfig *VbaseConfig;

            void parametrParser();

            QString basedir;
            QString games;
            QString term;
            QString exe;
    };
}

#endif // DARKPLACES_H

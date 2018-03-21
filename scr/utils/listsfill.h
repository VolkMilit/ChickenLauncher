#ifndef LISTSFILL_H
#define LISTSFILL_H

#include <QStandardItemModel>
#include <QDir>

#include "ui_mainwindow.h"
#include "utils/baseconfig.h"
#include "utils/colors.h"
#include "games/gzdoom.h"

namespace Utils
{
    class listFill
    {
        public:
            listFill(Ui::MainWindow *ui);
            virtual ~listFill();

            void getIWadList();
            void getPWadList();
            void getProfiles();
            void getPortConfigFile();
            void updateColors();

            QVector<QPair<QString, short>> getGamesList();

        private:
            QString pathHelper(const QString &widgetpath);

            Ui::MainWindow *myUi;
            gzdoom *Vgzdoom;
            baseConfig *VbaseConfig;
            Utils::colors *Vcolors;

            QVector<QPair<QString, short>> games;

            int offPathWad;
    };
}

#endif // LISTSFILL_H

#ifndef LISTSFILL_H
#define LISTSFILL_H

#include <QStandardItemModel>

#include "ui_mainwindow.h"
#include "baseconfig.h"
#include "colors.h"
#include "gzdoom.h"

namespace utils
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

        private:
        Ui::MainWindow *myUi;
        baseConfig *VbaseConfig;
        colors *Vcolors;
        Launcher::gzdoom *Vgzdoom;

        int offPathWad;
    };
}

#endif // LISTSFILL_H

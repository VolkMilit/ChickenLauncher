#ifndef UTIL_H
#define UTIL_H

#include "ui_mainwindow.h"
#include "utils/baseconfig.h"

namespace Utils
{
    class util
    {
        public:
        util(Ui::MainWindow *ui);
        virtual ~util();

        QString getPwadChecked();
        void moveItem(bool backward, QListWidget *widget);
        void moveItemTo(bool top, QListWidget *widget);
        QString getLabel();
        QString getMauntsFromFile(QString file);
        bool checkGame();

        protected:


        private:

        Ui::MainWindow *myUi;
        baseConfig *vbaseconfig;
    };
}

#endif // UTIL_H

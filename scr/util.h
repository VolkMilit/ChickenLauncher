#ifndef UTIL_H
#define UTIL_H

#include "ui_mainwindow.h"
#include "baseconfig.h"

namespace utils
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

        protected:


        private:

        Ui::MainWindow *myUi;
        baseConfig *vbaseconfig;
    };
}

#endif // UTIL_H

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
        void moveItem(bool backward);
        void moveItemTo(bool top);

        private:
        Ui::MainWindow *myUi;
        config::baseConfig *baseconfig;
    };
}

#endif // UTIL_H

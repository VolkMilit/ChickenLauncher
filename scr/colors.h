#ifndef COLORS_H
#define COLORS_H

#include <QListWidgetItem>

#include "baseconfig.h"

namespace utils
{
    class colors
    {
        public:
        colors();
        virtual ~colors();

        QColor getColor();
        void clearColor(QListWidget *widget);

        private:
        config::baseConfig *VbaseConfig;
        Ui::MainWindow *ui;
        QString color;
    };
}


#endif // COLORS_H

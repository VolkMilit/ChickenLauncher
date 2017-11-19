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
        void updateColors();

        private:
        baseConfig *VbaseConfig;
        Ui::MainWindow *ui;
    };
}


#endif // COLORS_H

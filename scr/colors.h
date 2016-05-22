#ifndef COLORS_H
#define COLORS_H

#include <QListWidgetItem>

#include "ui_mainwindow.h"
#include "baseconfig.h"

class colors : public QWidget
{
public:
    colors(Ui::MainWindow *ui);
    virtual ~colors();

    QColor getColor();
    void clearColor(QListWidget *widget);

private:
    Ui::MainWindow *myUi;
    baseConfig *VbaseConfig;
    QString color;
};

#endif // COLORS_H

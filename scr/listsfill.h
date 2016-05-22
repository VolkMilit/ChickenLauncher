#ifndef LISTSFILL_H
#define LISTSFILL_H

#include <QSortFilterProxyModel>

#include "ui_mainwindow.h"
#include "baseconfig.h"
#include "colors.h"

class listFill
{
public:
    listFill(Ui::MainWindow *ui);
    virtual ~listFill();

    void getIWadList();
    void getPWadList();
    void getProfiles();

    void setOffPathWad(bool set);
    QString getOffPathWad();

private:
    Ui::MainWindow *myUi;
    baseConfig *VbaseConfig;
    colors *Vcolors;

    QString offPathWad; //QVariant not work, boost too overhead, qt5 is not in my distribution
};

#endif // LISTSFILL_H

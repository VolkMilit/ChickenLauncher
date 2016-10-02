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
    void updateColors();

    void setOffPathWad(bool set);
    int getOffPathWad();

private:
    Ui::MainWindow *myUi;
    baseConfig *VbaseConfig;
    colors *Vcolors;

    int offPathWad; //QVariant not work, hmm...
    QStringList pwad_list;
};

#endif // LISTSFILL_H

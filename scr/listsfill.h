#ifndef LISTSFILL_H
#define LISTSFILL_H

#include "ui_mainwindow.h"
#include "baseconfig.h"

class listFill
{
public:
    listFill(Ui::MainWindow *ui);
    ~listFill();

    void getWadList();
    void getProfiles();

private:
    Ui::MainWindow *myUi;
    baseConfig *VbaseConfig;
};

#endif // LISTSFILL_H

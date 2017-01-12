#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include "baseconfig.h"
#include "listsfill.h"
#include "colors.h"
#include "ui_mainwindow.h"

namespace Ui {class configDialog;}

class configDialog : public QDialog
{
     Q_OBJECT

public:
    explicit configDialog(QWidget *parent = 0);
    ~configDialog();

public slots:

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void settingsInit();

    void on_rb_default_tab_profiles_clicked();

    void on_rb_default_tab_wads_clicked();

private:
    Ui::configDialog *ui;
    Ui::MainWindow *myUi;

    baseConfig *VbaseConfig;
    listFill *VlistFill;
    colors *Vcolor;

    QString color;
    int offPathWad;
    int hide;
    int default_tab;
};

#endif // CONFIGDIALOG_H

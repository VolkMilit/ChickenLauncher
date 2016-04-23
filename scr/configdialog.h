#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include "baseconfig.h"
#include "listsfill.h"
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

    void settingsInit();

    void on_buttonBox_rejected();

private:
    Ui::configDialog *ui;
    Ui::MainWindow *myUi;

    baseConfig *VbaseConfig;
    listFill *VlistFill;

    QString color;
    QString offPathWad;
};

#endif // CONFIGDIALOG_H

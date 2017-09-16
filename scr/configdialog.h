#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include "baseconfig.h"
#include "listsfill.h"
#include "colors.h"
#include "ui_mainwindow.h"

namespace Ui {class configDialog;}

namespace config
{
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
        Ui::configDialog *configDialogUi;
        Ui::MainWindow *myUi;

        config::baseConfig *VbaseConfig;
        utils::listFill *VlistFill;
        utils::colors *Vcolor;

        QString color;
        int offPathWad;
        int hide;
        int default_tab;
        int hide_game;
    };
}

#endif // CONFIGDIALOG_H

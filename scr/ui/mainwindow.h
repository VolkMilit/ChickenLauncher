#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSystemTrayIcon>
#include <QFileDialog>
#include <QInputDialog>
#include <QDir>
#include <QFile>
#include <QShortcut>
#include <QVector>

// libraries
#include "utils/baseconfig.h"
#include "utils/listsfill.h"
#include "utils/colors.h"
#include "utils/descriptionshandler.h"
#include "utils/util.h"
#include "games/gzdoom.h"
#include "games/darkplaces.h"

#include "configdialog.h"


//namespace Ui {class MainWindow;}

class MainWindow : public QMainWindow
{
    Q_OBJECT


    public:
        explicit MainWindow(QWidget *parent = 0);
        virtual ~MainWindow();

    private slots:

/*
    ___             _   _
   | __|  _ _ _  __| |_(_)___ _ _  ___
   | _| || | ' \/ _|  _| / _ \ ' \(_-<
   |_| \_,_|_||_\__|\__|_\___/_||_/__/

*/

        void trayIcon();
        void exitApp();
        void startApp();
        void iconActivated(QSystemTrayIcon::ActivationReason reason);
        void windowInit();
        void mainWindowShowHide();

        void setLastPwadHelper();
        void setLastPwadHelper(bool backward);
        void setLastPwadHelperTo(bool top);

        void setGame(const short idTechLevel, const short idEngine);

/*
    ___ _                _
   / __(_)__ _ _ _  __ _| |___
   \__ \ / _` | ' \/ _` | (_-<
   |___/_\__, |_||_\__,_|_/__/
         |___/
*/

        void on_btn_start_clicked();

        //PROFILE TAB
        void on_btn_new_clicked();
        void on_btn_load_clicked();
        void on_btn_delete_clicked();
        void on_btn_rename_clicked();
        void on_btn_clone_clicked();

        //WAD TAB
        void on_btn_clear_selected_pwad_clicked();
        void on_btn_pwad_up_clicked();
        void on_btn_pwad_top_clicked();
        void on_btn_pwad_bottom_clicked();
        void on_btn_pwad_down_clicked();
        void on_lw_iwad_itemClicked(QListWidgetItem *item);
        void on_btn_refresh_clicked();
        void on_lw_pwad_itemChanged(QListWidgetItem *item);
        void on_lw_pwad_itemSelectionChanged();

        //NETWORK TAB
        void on_gb_join_toggled();
        void on_btn_clear_ip_clicked();
        void on_btn_clear_port_clicked();
        void on_le_ip_textChanged(const QString &arg1);
        void on_le_port_textChanged(const QString &arg1);

        //ADVANCED TAB
        void on_le_playdemo_textChanged();
        void on_le_playdemo_2_textChanged();
        void on_le_loadgame_textChanged();
        void on_btn_loadgame_clicked();
        void on_btn_clear_loadgame_clicked();
        void on_btn_clear_playdemo_clicked();
        void on_btn_clear_playdemo2_clicked();
        void on_btn_pick_demo_file_clicked();
        void on_btn_pick_demo_file_2_clicked();
        void on_cb_recorddemo_clicked();
        void on_le_map_textChanged(const QString &arg1);
        void on_cb_darkplaces_water_toggled(bool checked);

        //SETTINGS TAB
        void on_btn_clear_advancedparam_clicked();
        void on_btn_exe_clicked();
        void on_btn_iwad_path_clicked();
        void on_btn_pwad_path_clicked();
        void on_le_exe_textChanged();
        void on_le_iwad_textChanged();
        void on_le_pwad_textChanged();
        void on_le_adv_cmd_param_textChanged();
        void on_le_adv_port_param_textChanged();
        void on_btn_new_config_clicked();
        void on_btn_load_config_clicked();
        void on_btn_delete_config_clicked();
        void on_lw_port_configs_files_itemSelectionChanged();

        //MENU
        void on_actionAbout_QT_triggered();
        void on_actionAbout_Chicken_Launcher_triggered();
        void on_actionPreferences_triggered();
        void on_actionSearch_PWAD_triggered();
        void on_actionGZDoom_triggered();
        void on_actionDarkPlaces_triggered();

        //SHORTCURTS
        void on_actionExit_Ctrl_Q_triggered();
        void on_actionMinimize_to_tray_Ctrl_T_triggered();

    private:

        Ui::MainWindow *ui;
        Utils::util *vutil;
        gzdoom *vgzdoom;
        Games::darkplaces *vdarkplaces;

        Utils::baseConfig *VbaseConfig;

        Utils::listFill *VlistFill;
        Utils::colors *Vcolors;

        descriptionsHandler *VdescriptionsHandler;

        QFileDialog *fileDialog;

        configDialog *VconfigDialog;
};

#endif // MAINWINDOW_H

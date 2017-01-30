#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QSystemTrayIcon>
#include <QFileDialog>
#include <QInputDialog>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QtAlgorithms>

// std headers
#include <algorithm>

// libraries
#include "baseconfig.h"
#include "listsfill.h"
#include "gzdoom.h"
#include "configdialog.h"
#include "colors.h"
#include "descriptionshandler.h"

namespace Ui {class MainWindow;}


class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

/*
    ___             _   _
   | __|  _ _ _  __| |_(_)___ _ _  ___
   | _| || | ' \/ _|  _| / _ \ ' \(_-<
   |_| \_,_|_||_\__|\__|_\___/_||_/__/

*/

    void trayIcon();
    void exitApp();
    void startApp(); //Todo other doom ports. I mean prboom works, anyway, but WTF guyzz, -files not working ;(
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void windowInit();
    void mainWindowShowHide();
    void setLastPwadFunc();
    void updateColors();

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
    void on_lw_iwad_itemClicked();
    void on_btn_refresh_clicked();
    void on_lw_pwad_itemChanged(QListWidgetItem *item);
    void on_pushButton_clicked();

    //NETWORK TAB
    void on_gb_join_toggled();
    void on_btn_clear_ip_clicked();
    void on_btn_clear_port_clicked();

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
    void on_cb_config_activated();

    //MENU
    void on_actionAbout_QT_triggered();
    void on_actionAbout_Chicken_Launcher_triggered();
    void on_actionPreferences_triggered();

    //SHORTCURTS
    void on_actionExit_Ctrl_Q_triggered();
    void on_actionMinimize_to_tray_Ctrl_T_triggered();

private:

/*
    ___ _
   / __| |__ _ ______ ___ ___
  | (__| / _` (_-<_-</ -_|_-<
   \___|_\__,_/__/__/\___/__/
*/

    Ui::MainWindow *ui;

    baseConfig *VbaseConfig;
    listFill *VlistFill;
    gzdoom *Vgzdoom;
    configDialog *VconfigDialog;
    colors *Vcolors;
    descriptionsHandler *VdescriptionsHandler;

    QListWidgetItem* item;
    QFileDialog *fileDialog;
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QSystemTrayIcon>
#include <QFileDialog>
#include <QInputDialog>

#include "baseconfig.h"
#include "listsfill.h"
#include "gzdoom.h"

namespace Ui {class MainWindow;}


class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void mainWindowShowHide();

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
    void on_btn_clear_selected_iwad_clicked();
    void on_btn_clear_selected_pwad_clicked();

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

    //MENU
    void on_actionAbout_QT_triggered();
    void on_actionAbout_Chicken_Launcher_triggered();

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

    QListWidgetItem* item;
    QFileDialog *fileDialog;
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QProcess>
#include <QSystemTrayIcon>
#include <QFileDialog>
#include <QSettings>
#include <QInputDialog>
#include <QProgressDialog>
#include <QDateTime>
#include <QStringListModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    //functions
    void getWadList();
    void trayIcon();
    void exitApp();
    void mainWindowShowHide();
    void writeSettings(QString file);
    void readSettings(QString file);
    void getProfiles();
    void parametrParser();
    void startApp(); //todo other doom ports
    void iconActivated(QSystemTrayIcon::ActivationReason reason);

    //signals
    void on_btn_about_clicked();
    void on_le_iwad_textChanged();
    void on_le_pwad_textChanged();
    void on_btn_start_clicked();
    void on_btn_iwad_path_clicked();
    void on_btn_pwad_path_clicked();
    void on_btn_new_clicked();
    void on_btn_load_clicked();
    void on_btn_exe_clicked();
    void on_btn_pick_demo_file_clicked();
    void on_btn_pick_demo_file_2_clicked();
    void on_btn_loadgame_clicked();
    void on_btn_help_clicked();
    void on_btn_delete_clicked();
    void on_gb_join_toggled();
    void on_cb_recorddemo_clicked();
    void on_le_playdemo_textChanged();
    void on_le_playdemo_2_textChanged();
    void on_btn_clear_loadgame_clicked();
    void on_btn_clear_playdemo_clicked();
    void on_btn_clear_playdemo2_clicked();
    void on_le_loadgame_textChanged();
    void on_btn_clear_advancedparam_clicked();
    void on_btn_clear_ip_clicked();
    void on_btn_clear_port_clicked();
    void on_btn_clear_selected_pwad_clicked();    
    void on_btn_load_last_wads_clicked();
    void on_actionExit_Ctrl_Q_triggered();
    void on_actionMinimize_to_tray_Ctrl_T_triggered();

private:
    Ui::MainWindow *ui;
    QListWidgetItem* item;
    QFileDialog fileDialog;

    QString pwad;
    QString iwad;
    QString map;
    QString skill;
    QString exe;
    QString nomusic;
    QString nosound;
    QString nosfx;
    QString demo;
    QString oldsprites;
    QString noautoload;
    QString nostartup;
};

#endif // MAINWINDOW_H

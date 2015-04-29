#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QProcess>
#include <QPixmap>
#include <QSystemTrayIcon>

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
    void getWadList();
    void trayIcon();
    void exitApp();
    void mainWindowShowHide();
    void on_btn_about_clicked();
    void on_le_iwad_textChanged();
    void on_le_pwad_textChanged();

    void on_btn_start_clicked();

private:
    Ui::MainWindow *ui;
    QListWidgetItem* item;
};

#endif // MAINWINDOW_H

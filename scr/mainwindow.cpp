#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    VbaseConfig = new baseConfig(ui);
    VlistFill = new listFill(ui);
    Vgzdoom = new gzdoom(ui);
    VconfigDialog = new configDialog();
    Vcolors = new colors(ui);

    windowInit();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete VbaseConfig;
    delete VlistFill;
    delete Vgzdoom;
    delete VconfigDialog;
    delete Vcolors;
}


/*
 ___             _   _
| __|  _ _ _  __| |_(_)___ _ _  ___
| _| || | ' \/ _|  _| / _ \ ' \(_-<
|_| \_,_|_||_\__|\__|_\___/_||_/__/

*/

void MainWindow::updateColors()
{
    for (int i = 0; i < ui->lw_iwad->count(); i++)
    {
        if (ui->lw_iwad->item(i)->text() == VbaseConfig->getLastIwad(VbaseConfig->getDefaultProfile()))
        {
            ui->lw_iwad->item(i)->setForeground(Qt::black);
        }
    }
    qDebug() << VbaseConfig->getLastIwad(VbaseConfig->getDefaultProfile());
}

void MainWindow::windowInit()
{
    VbaseConfig->readAllSettings(VbaseConfig->getDefaultProfile());

    VlistFill->getIWadList();
    VlistFill->getPWadList();
    VlistFill->getProfiles();

    trayIcon();

    //shortcurts
    ui->actionExit_Ctrl_Q->setShortcut(tr("CTRL+Q"));
    ui->actionMinimize_to_tray_Ctrl_T->setShortcut(tr("CTRL+T"));    
}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger)
    {
        mainWindowShowHide();
    }
}

void MainWindow::trayIcon()
{
    //    _____ _____  ____  __ _____
    //   |  ___|_ _\ \/ /  \/  | ____|
    //   | |_   | | \  /| |\/| |  _|
    //   |  _|  | | /  \| |  | | |___
    //   |_|   |___/_/\_\_|  |_|_____|
    //

    QSystemTrayIcon *trIcon = new QSystemTrayIcon(this);
    trIcon->setIcon(windowIcon());
    trIcon->setToolTip("Chicken Launcher");
    trIcon->show();

    QMenu *trayMenu = new QMenu (this);
    QAction *actionPlayDoom = new QAction (tr("PLAY DOOM!"), this);
    QAction *actionShowHide = new QAction (tr("Show\\Hide"), this);
    QAction *actionExit = new QAction (tr("Exit"), this);

    trayMenu->addAction(actionPlayDoom);
    trayMenu->addAction(actionShowHide);
    trayMenu->addAction(actionExit);

    connect(trIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this,\
            SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
    connect(actionPlayDoom, SIGNAL(triggered()), this, SLOT(startApp()));
    connect(actionExit, SIGNAL(triggered()), this, SLOT(exitApp()));
    connect(actionShowHide, SIGNAL(triggered()), this, SLOT(mainWindowShowHide()));

    trIcon->setContextMenu(trayMenu);
}

void MainWindow::exitApp()
{
    QApplication::quit();
}

void MainWindow::mainWindowShowHide()
{
    setVisible(!isVisible());
    this->setWindowState(Qt::WindowActive);
}

void MainWindow::startApp()
{
    /*
    _____        _     _       _   _                            _
   |_   _|__  __| |___(_)  ___| |_| |_  ___ _ _   _ __  ___ _ _| |_ ___
     | |/ _ \/ _` / _ \_  / _ \  _| ' \/ -_) '_| | '_ \/ _ \ '_|  _(_-<
     |_|\___/\__,_\___(_) \___/\__|_||_\___|_|   | .__/\___/_|  \__/__/
                                                 |_|
    */

    if (!ui->le_playdemo->text().isEmpty())
        Vgzdoom->startDemo();
    else if (ui->gb_join->isChecked())
        Vgzdoom->networkGame();
    else
        Vgzdoom->startGzdoom();
}

/*
 ___ _                _
/ __(_)__ _ _ _  __ _| |___
\__ \ / _` | ' \/ _` | (_-<
|___/_\__, |_||_\__,_|_/__/
     |___/
*/


void MainWindow::on_lw_iwad_itemClicked()
{       
    VbaseConfig->setLastIwad(VbaseConfig->getDefaultProfile(), ui->lw_iwad->currentItem()->text());
    Vcolors->clearColor(ui->lw_iwad);
    ui->lw_iwad->currentItem()->setForeground(Vcolors->getColor());
    ui->lw_iwad->currentItem()->setSelected(false);
}

void MainWindow::on_lw_pwad_clicked()
{
    /*QString last_pwad = VbaseConfig->getLastPwad(VbaseConfig->getDefaultProfile())\
            + ui->lw_pwad->currentItem()->text() + " ";
    VbaseConfig->setLastPwad(VbaseConfig->getDefaultProfile(), last_pwad);*/
}


void MainWindow::on_lw_pwad_itemChanged(QListWidgetItem *item)
{
    if (item->checkState())
    {
        QString last_pwad = VbaseConfig->getLastPwad(VbaseConfig->getDefaultProfile())\
                    + item->text() + " ";
        VbaseConfig->setLastPwad(VbaseConfig->getDefaultProfile(), last_pwad);
    }
    else
    {
        QString last_pwad = VbaseConfig->getLastPwad(VbaseConfig->getDefaultProfile());
        last_pwad.remove(item->text());
        last_pwad.remove("  ");
        VbaseConfig->setLastPwad(VbaseConfig->getDefaultProfile(), last_pwad);
    }
}

void MainWindow::on_btn_pick_demo_file_clicked()
{
    QString fileName = fileDialog->getOpenFileName(this, tr("Open recording demo"), QDir::currentPath());
    ui->le_playdemo->setText(fileName);
}

void MainWindow::on_btn_pick_demo_file_2_clicked()
{
    QString fileName = fileDialog->getOpenFileName(this, tr("Open recording demo"), QDir::currentPath());
    ui->le_playdemo_2->setText(fileName);
}

void MainWindow::on_btn_loadgame_clicked()
{
    QString fileName = fileDialog->getOpenFileName(this, tr("Open save file"), QDir::currentPath());
    ui->le_loadgame->setText(fileName);
}


void MainWindow::on_btn_load_clicked()
{
    VbaseConfig->setDefaultProfile(ui->lw_profile->item(ui->lw_profile->currentRow())->text());

    VlistFill->getIWadList();
    VlistFill->getPWadList();

    if (ui->lw_profile->currentItem() != nullptr)
    {
        Vcolors->clearColor(ui->lw_profile);
        VbaseConfig->readAllSettings(VbaseConfig->getDefaultProfile());
        ui->lw_profile->currentItem()->setForeground(Vcolors->getColor());
    }
}

void MainWindow::on_btn_exe_clicked()
{
    QString fileName = fileDialog->getOpenFileName(this, tr("Open Port Exe"),
                        QDir::currentPath(),
                        "Any file *.* (*)");
    ui->le_exe->setText(fileName);
}

void MainWindow::on_btn_new_clicked()
{    
    bool ok;
    QString text = QInputDialog::getText(this, tr("Chicken Launcher"),
                                            tr("Add profile"), QLineEdit::Normal,
                                            "", &ok);

    if (ok && !text.isEmpty())
    {
        QFile f(VbaseConfig->getProfilesDir() + text + ".ini");
        f.open(QIODevice::WriteOnly);
        ui->lw_profile->addItem(text + ".ini");
        VbaseConfig->writeAllSettings(VbaseConfig->getProfilesDir() + text + ".ini");
    }
}

void MainWindow::on_le_iwad_textChanged()
{
    VbaseConfig->setIwadDir(VbaseConfig->getDefaultProfile(), ui->le_iwad->text());
    VlistFill->getIWadList();
}

void MainWindow::on_le_pwad_textChanged()
{
    VbaseConfig->setPwadDir(VbaseConfig->getDefaultProfile(), ui->le_pwad->text());
    VlistFill->getPWadList();
}

void MainWindow::on_btn_start_clicked()
{
    startApp();
}

void MainWindow::on_btn_iwad_path_clicked()
{
    QString fileName = fileDialog->getExistingDirectory(this, tr("Open iwad folder"), QDir::currentPath());
    ui->le_iwad->setText(fileName);
}

void MainWindow::on_btn_pwad_path_clicked()
{
    QString fileName = fileDialog->getExistingDirectory(this, tr("Open pwad folder"), QDir::currentPath());
    ui->le_pwad->setText(fileName);
}

void MainWindow::on_btn_delete_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Chicken Launcher", tr("Are you shure you want delete this profile?"),
            QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes && ui->lw_profile->count() != 0)
    {
        QString file = VbaseConfig->getProfilesDir() + ui->lw_profile->item(ui->lw_profile->currentRow())->text();

        QFile f(file);
        f.remove();

        VlistFill->getProfiles();

        if (VbaseConfig->getDefaultProfile() == file)
            VbaseConfig->setDefaultProfile(ui->lw_profile->item(0)->text());
    }
    else
    {
        return;
    }
}

void MainWindow::on_btn_rename_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Chicken Launcher"),
                                            tr("Rename profile"), QLineEdit::Normal,
                                            "", &ok);

    QFile f(ui->lw_profile->item(ui->lw_profile->currentRow())->text());

    if (ok && !text.isEmpty())
        f.rename(VbaseConfig->getProfilesDir() + ui->lw_profile->item(ui->lw_profile->currentRow())->text(),\
                 VbaseConfig->getProfilesDir() + text + ".ini");

    VlistFill->getProfiles();
}

void MainWindow::on_btn_clone_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Chicken Launcher"),
                                            tr("Clone profile"), QLineEdit::Normal,
                                            "", &ok);

    QFile f(ui->lw_profile->item(ui->lw_profile->currentRow())->text());

    if (ok && !text.isEmpty())
        f.copy(VbaseConfig->getProfilesDir() + ui->lw_profile->item(ui->lw_profile->currentRow())->text(),\
               VbaseConfig->getProfilesDir() + text + ".ini");

    VlistFill->getProfiles();
}

void MainWindow::on_le_exe_textChanged()
{
    VbaseConfig->setExePath(VbaseConfig->getDefaultProfile(),\
                              ui->le_exe->text());
}

void MainWindow::setLastPwadFunc()
{
    QString last_pwad;
    foreach(QListWidgetItem *item, ui->lw_pwad->selectedItems())
        last_pwad += item->text() + " ";
    VbaseConfig->setLastPwad(VbaseConfig->getDefaultProfile(), last_pwad);
}

//moving item up and down, http://www.qtcentre.org/threads/17996-Move-items-up-and-down-in-QListWidget
void MainWindow::on_btn_pwad_up_clicked()
{
    QListWidgetItem *current = ui->lw_pwad->currentItem();
    int currIndex = ui->lw_pwad->row(current);

    QListWidgetItem *prev = ui->lw_pwad->item(ui->lw_pwad->row(current) - 1);
    int prevIndex = ui->lw_pwad->row(prev);

    QListWidgetItem *temp = ui->lw_pwad->takeItem(prevIndex);
    ui->lw_pwad->insertItem(prevIndex, current);
    ui->lw_pwad->insertItem(currIndex, temp);

    setLastPwadFunc();
}

void MainWindow::on_btn_pwad_down_clicked()
{
    QListWidgetItem *current = ui->lw_pwad->currentItem();
    int currIndex = ui->lw_pwad->row(current);

    QListWidgetItem *next = ui->lw_pwad->item(ui->lw_pwad->row(current) + 1);
    int nextIndex = ui->lw_pwad->row(next);

    QListWidgetItem *temp = ui->lw_pwad->takeItem(nextIndex);
    ui->lw_pwad->insertItem(currIndex, temp);
    ui->lw_pwad->insertItem(nextIndex, current);

    setLastPwadFunc();
}

void MainWindow::on_btn_pwad_top_clicked()
{
}

void MainWindow::on_btn_pwad_bottom_clicked()
{
}

void MainWindow::on_gb_join_toggled()
{
    QVector<int> vec;
    vec << 1 << 2 << 4;

    bool off = true;
    ui->btn_start->setText(tr("PLAY DOOM!"));

    if (ui->gb_join->isChecked())
    {
        off = false;
        ui->btn_start->setText(tr("Join game"));
    }

    for (int i = 0; i < vec.size(); i++)
        ui->tabWidget->setTabEnabled(vec.at(i), off);
}

void MainWindow::on_cb_recorddemo_clicked()
{
    bool off = true;

    if (ui->cb_recorddemo->isChecked())
        off = false;

    ui->le_playdemo->setEnabled(off);
    ui->le_playdemo_2->setEnabled(off);
    ui->lb_playdemo->setEnabled(off);
    ui->lb_playdemo2->setEnabled(off);
    ui->btn_pick_demo_file->setEnabled(off);
    ui->btn_pick_demo_file_2->setEnabled(off);
}

void MainWindow::on_le_playdemo_textChanged()
{
    bool off = true;
    ui->btn_start->setText(tr("PLAY DOOM!"));

    if (!ui->le_playdemo->text().isEmpty())
    {
        off = false;
        ui->btn_start->setText(tr("Play demo file"));
    }

    ui->gb_game->setEnabled(off);
    ui->cb_recorddemo->setEnabled(off);
    ui->le_playdemo_2->setEnabled(off);
    ui->btn_clear_playdemo2->setEnabled(off);
    ui->btn_pick_demo_file_2->setEnabled(off);
    ui->lb_playdemo2->setEnabled(off);
    ui->tabWidget->setTabEnabled(1, off);
    ui->tabWidget->setTabEnabled(3, off);
}

void MainWindow::on_le_playdemo_2_textChanged()
{
    bool off = true;
    ui->btn_start->setText(tr("PLAY DOOM!"));

    if (!ui->le_playdemo_2->text().isEmpty())
    {
        off = false;
        ui->btn_start->setText(tr("Play demo file"));
    }

    ui->gb_game->setEnabled(off);
    ui->cb_recorddemo->setEnabled(off);
    ui->le_playdemo->setEnabled(off);
    ui->btn_clear_playdemo->setEnabled(off);
    ui->btn_pick_demo_file->setEnabled(off);
    ui->lb_playdemo->setEnabled(off);
    ui->tabWidget->setTabEnabled(1, off);
    ui->tabWidget->setTabEnabled(3, off);
}

void MainWindow::on_btn_clear_loadgame_clicked()
{
    ui->le_loadgame->clear();
    ui->le_loadgame->setFocus();
}

void MainWindow::on_btn_clear_playdemo_clicked()
{
    ui->le_playdemo->clear();
    ui->le_playdemo->setFocus();
}

void MainWindow::on_btn_clear_playdemo2_clicked()
{
    ui->le_playdemo_2->clear();
    ui->le_playdemo_2->setFocus();
}

void MainWindow::on_le_loadgame_textChanged()
{
    QVector<int> vec;
    vec << 0 << 2 << 3;

    bool off = true;
    ui->btn_start->setText(tr("PLAY DOOM!"));

    if (!ui->le_loadgame->text().isEmpty())
    {
        off = false;
        ui->btn_start->setText(tr("LOAD GAME!"));
    }

    for (int i = 0; i < vec.size(); i++)
        ui->tabWidget->setTabEnabled(vec.at(i), off);
    ui->gb_game->setEnabled(off);
    ui->gb_demos->setEnabled(off);
}

void MainWindow::on_btn_clear_advancedparam_clicked()
{
    ui->le_adv_port_param->clear();
    ui->le_adv_port_param->setFocus();
}

void MainWindow::on_btn_clear_ip_clicked()
{
    ui->le_ip->clear();
    ui->le_ip->setFocus();
}

void MainWindow::on_btn_clear_port_clicked()
{
    ui->le_port->clear();
    ui->le_port->setFocus();
}

void MainWindow::on_btn_clear_selected_pwad_clicked()
{
    ui->lw_pwad->reset();
    for(int i = 0; i < ui->lw_pwad->count(); i++)
        ui->lw_pwad->item(i)->setForeground(Qt::black);
}

void MainWindow::on_btn_clear_selected_iwad_clicked()
{
    ui->lw_iwad->reset();
}

void MainWindow::on_actionExit_Ctrl_Q_triggered()
{
    QString hide = VbaseConfig->getHide(VbaseConfig->getDefaultProfile());
    if (hide == "true")
        mainWindowShowHide();
    else
        QApplication::quit();
}

void MainWindow::on_actionMinimize_to_tray_Ctrl_T_triggered()
{
    mainWindowShowHide();
}

void MainWindow::on_actionAbout_QT_triggered()
{
    QMessageBox::aboutQt(this, tr("About Qt"));
}

void MainWindow::on_actionPreferences_triggered()
{
    connect(VconfigDialog, SIGNAL(accepted()), this, SLOT(updateColors()));
    VconfigDialog->show();
}

void MainWindow::on_btn_refresh_clicked()
{
    VlistFill->getPWadList();
}

void MainWindow::on_actionAbout_Chicken_Launcher_triggered()
{
    QMessageBox *msgBox = new QMessageBox(this);
    msgBox->setText(tr("<font size=\"5\" color=\"#FDBC5F\" align=\"center\"><b>Chicken <font color=\"#C959A2\">Launcher</font> <font color=\"#000\">v1.1</font></b></font>"));
    msgBox->setInformativeText(tr("SCOOTALOO! SCOOT-SCOOTALOO!\n\nChicken Launcher writen to be simple and powerfull.\
 Cross-platform and funny. Meme belong to Apple Bloom.\n\n\
Licensed under the Apache License, Version 2.0 (the \"License\"). \
You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0 or see LICENSE file."));
    msgBox->setStandardButtons(QMessageBox::Ok);
    msgBox->setIconPixmap(QPixmap(":/chicken.png"));
    msgBox->exec();
}

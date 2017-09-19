#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "archive.h"

Launcher::MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    vutil(new utils::util(ui)),
    vgzdoom(new gzdoom(ui))
{
    ui->setupUi(this);
    VbaseConfig = new config::baseConfig(ui);
    VconfigDialog = new config::configDialog();
    VlistFill = new utils::listFill(ui);
    Vcolors = new utils::colors();
    VdescriptionsHandler = new descriptionsHandler(ui);

    windowInit();
}

Launcher::MainWindow::~MainWindow()
{
    delete Vcolors;
    delete VlistFill;
    delete VconfigDialog;
    delete VdescriptionsHandler;
    delete VbaseConfig;

    delete vgzdoom;
    delete vutil;
    delete ui;
}

/*
                  __ _ _
 _ __  _ __ ___  / _(_) | ___  ___
| '_ \| '__/ _ \| |_| | |/ _ \/ __|
| |_) | | | (_) |  _| | |  __/\__ \
| .__/|_|  \___/|_| |_|_|\___||___/
|_|
*/

void Launcher::MainWindow::on_btn_new_clicked()
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
        VbaseConfig->setCurrentProfile(text + ".ini");
        Vcolors->clearColor(ui->lw_profile);

        //tmp ducktape, but I, actually, too lazy to fix this
        ui->lw_profile->item(ui->lw_profile->count() - 1)->setForeground(Vcolors->getColor());
    }
}

void Launcher::MainWindow::on_btn_load_clicked()
{
    QListWidgetItem *item = ui->lw_profile->currentItem();

    if (!item)
        return;

    VbaseConfig->setCurrentProfile(item->text());

    Vcolors->clearColor(ui->lw_profile);
    VbaseConfig->readAllSettings(VbaseConfig->getCurrentProfile()); // this fill exe, iwad, pwad path's
    ui->lw_profile->currentItem()->setForeground(Vcolors->getColor());

    VlistFill->getIWadList();
    VlistFill->getPWadList();
    VlistFill->getPortConfigFile();

    const QString label = vutil->getLabel();
    ui->btn_start->setText(label);
}

void Launcher::MainWindow::on_btn_rename_clicked()
{
    QListWidgetItem *item = ui->lw_profile->currentItem();

    if (!item)
        return;

    bool ok;
    QString text = QInputDialog::getText(this, tr("Chicken Launcher"),
                                            tr("Rename profile"), QLineEdit::Normal,
                                            item->text().remove(".ini"), &ok);

    QFile f(item->text());

    if (ok && !text.isEmpty())
    {
        f.rename(VbaseConfig->getProfilesDir() + item->text(),\
                 VbaseConfig->getProfilesDir() + text + ".ini");

        item->setText(text + ".ini");
    }
}

void Launcher::MainWindow::on_btn_delete_clicked()
{
    QListWidgetItem *item = ui->lw_profile->currentItem();

    if (!item)
        return;

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Chicken Launcher", tr("Are you shure you want delete this profile?"),
            QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes && ui->lw_profile->count() != 0)
    {
        QString file = VbaseConfig->getProfilesDir() + item->text();

        QFile f(file);
        f.remove();

        delete ui->lw_profile->takeItem(ui->lw_profile->currentRow());

        if (VbaseConfig->getCurrentProfile() == file)
            VbaseConfig->setCurrentProfile(ui->lw_profile->item(0)->text());
    }
    else
    {
        return;
    }
}

void Launcher::MainWindow::on_btn_clone_clicked()
{
    QListWidgetItem *item = ui->lw_profile->currentItem();

    if (!item)
        return;

    bool ok;
    QString text = QInputDialog::getText(this, tr("Chicken Launcher"),
                                            tr("Clone profile"), QLineEdit::Normal,
                                            "", &ok);

    QFile f(item->text());

    if (ok && !text.isEmpty())
        f.copy(VbaseConfig->getProfilesDir() + item->text(), \
               VbaseConfig->getProfilesDir() + text + ".ini");

    VlistFill->getProfiles();
}

void Launcher::MainWindow::on_btn_clear_selected_pwad_clicked()
{
    //ui->lw_pwad->currentItem()->setSelected(false);

    for(int i = 0; i < ui->lw_pwad->count(); i++)
    {
        if (ui->lw_pwad->item(i)->checkState() == Qt::Checked)
            ui->lw_pwad->item(i)->setCheckState(Qt::Unchecked);
        ui->lw_pwad->item(i)->setForeground(Qt::black);
    }
}


/*
                   _
__      ____ _  __| |___
\ \ /\ / / _` |/ _` / __|
 \ V  V / (_| | (_| \__ \
  \_/\_/ \__,_|\__,_|___/

*/

void Launcher::MainWindow::on_btn_pwad_up_clicked()
{
    vutil->moveItem(true);

    VbaseConfig->setLastPwad("");
    VbaseConfig->setLastPwad(vutil->getPwadChecked());
}

void Launcher::MainWindow::on_btn_pwad_down_clicked()
{
    vutil->moveItem(false);

    VbaseConfig->setLastPwad("");
    VbaseConfig->setLastPwad(vutil->getPwadChecked());
}

void Launcher::MainWindow::on_btn_pwad_top_clicked()
{
    vutil->moveItemTo(true);

    VbaseConfig->setLastPwad("");
    VbaseConfig->setLastPwad(vutil->getPwadChecked());
}

void Launcher::MainWindow::on_btn_pwad_bottom_clicked()
{
    vutil->moveItemTo(false);

    VbaseConfig->setLastPwad("");
    VbaseConfig->setLastPwad(vutil->getPwadChecked());
}

void Launcher::MainWindow::on_btn_refresh_clicked()
{
    VlistFill->getPWadList();
}

void Launcher::MainWindow::on_lw_iwad_itemClicked(QListWidgetItem *item)
{
    VbaseConfig->setLastIwad(item->text().remove(ui->le_iwad->text()));
    Vcolors->clearColor(ui->lw_iwad);
    item->setForeground(Vcolors->getColor());
    item->setSelected(false);

    const QString label = vutil->getLabel();
    ui->btn_start->setText(label);
}

void Launcher::MainWindow::on_lw_pwad_itemChanged(QListWidgetItem *item)
{
    if (item->checkState())        
        item->setForeground(Vcolors->getColor());    
    else
        item->setForeground(Qt::black);

    VbaseConfig->setLastPwad("");
    VbaseConfig->setLastPwad(vutil->getPwadChecked());
}

void Launcher::MainWindow::on_lw_pwad_itemSelectionChanged()
{
    QListWidgetItem *item = ui->lw_pwad->currentItem();

    if (!item)
        return;

    VdescriptionsHandler->getFullDescriptionFromFile(ui->le_pwad->text() + "/" + item->text());
}


/*
          _   _   _
 ___  ___| |_| |_(_)_ __   __ _ ___
/ __|/ _ \ __| __| | '_ \ / _` / __|
\__ \  __/ |_| |_| | | | | (_| \__ \
|___/\___|\__|\__|_|_| |_|\__, |___/
                          |___/
*/

void Launcher::MainWindow::on_btn_iwad_path_clicked()
{
    QString last = VbaseConfig->getLastIwadDir();

    if (last.isEmpty())
        last = QDir::currentPath();

    QString fileName = fileDialog->getExistingDirectory(this, tr("Open iwad folder"), last);

    if (!fileName.isEmpty())
    {
        ui->le_iwad->setText(fileName);
        VbaseConfig->setLastIwadDir(fileName);
    }
}

void Launcher::MainWindow::on_btn_pwad_path_clicked()
{
    QString last = VbaseConfig->getLastPwadDir();

    if (last.isEmpty())
        last = QDir::currentPath();

    QString fileName = fileDialog->getExistingDirectory(this, tr("Open pwad folder"), last);

    if (!fileName.isEmpty())
    {
        ui->le_pwad->setText(fileName);
        VbaseConfig->setLastPwadDir(fileName);
    }
}

void Launcher::MainWindow::on_le_iwad_textChanged()
{
    VbaseConfig->setIwadDir(ui->le_iwad->text());
    VlistFill->getIWadList();
}

void Launcher::MainWindow::on_le_pwad_textChanged()
{
    VbaseConfig->setPwadDir(ui->le_pwad->text());
    VlistFill->getPWadList();
}

void Launcher::MainWindow::on_btn_exe_clicked()
{
    QString fileName = fileDialog->getOpenFileName(this, tr("Open Port Exe"),
                        ui->le_exe->text(),
                        "Any file *.* (*)");

    if (!fileName.isNull()) ui->le_exe->setText(fileName);
}

void Launcher::MainWindow::on_le_exe_textChanged()
{
    VbaseConfig->setExePath(ui->le_exe->text());
}

void Launcher::MainWindow::on_le_adv_cmd_param_textChanged()
{
    VbaseConfig->setAdvCmdParam(ui->le_adv_cmd_param->text());
}

void Launcher::MainWindow::on_le_adv_port_param_textChanged()
{
    VbaseConfig->setAdvExeParam(ui->le_adv_port_param->text());
}

void Launcher::MainWindow::on_btn_clear_advancedparam_clicked()
{
    ui->le_adv_port_param->clear();
    ui->le_adv_port_param->setFocus();
}

void Launcher::MainWindow::on_btn_new_config_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Chicken Launcher"),
                                            tr("Add port config"), QLineEdit::Normal,
                                            "", &ok);

    if (ok && !text.isEmpty())
    {
        QFile f(vgzdoom->getGzdoomHomeDir() + text + ".ini");
        f.open(QIODevice::WriteOnly);
        ui->lw_port_configs_files->addItem(text + ".ini");
    }
}

void Launcher::MainWindow::on_btn_load_config_clicked()
{
    QListWidgetItem *item = ui->lw_port_configs_files->currentItem();

    if (!item)
        return;

    VbaseConfig->setConfigFile(item->text());
    Vcolors->clearColor(ui->lw_port_configs_files);
    item->setForeground(Vcolors->getColor());
    item->setSelected(false);
}

void Launcher::MainWindow::on_btn_delete_config_clicked()
{
    QListWidgetItem *item = ui->lw_port_configs_files->currentItem();

    if (!item)
        return;

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Chicken Launcher", tr("Are you shure you want delete this config?"),
            QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes && ui->lw_port_configs_files->count() != 1)
    {
        QString file = vgzdoom->getGzdoomHomeDir() + item->text();

        QFile f(file);
        f.remove();

        delete ui->lw_port_configs_files->takeItem(ui->lw_port_configs_files->row(item));
    }
    else
    {
        return;
    }
}

void Launcher::MainWindow::on_lw_port_configs_files_itemSelectionChanged()
{
    ui->btn_delete_config->setDisabled(false);

    QListWidgetItem *item = ui->lw_port_configs_files->currentItem();

    if (item->text() == "default")
        ui->btn_delete_config->setDisabled(true);
}


/*
                 _ _   _       _
 _ __ ___  _   _| | |_(_)_ __ | | __ _ _   _  ___ _ __
| '_ ` _ \| | | | | __| | '_ \| |/ _` | | | |/ _ \ '__|
| | | | | | |_| | | |_| | |_) | | (_| | |_| |  __/ |
|_| |_| |_|\__,_|_|\__|_| .__/|_|\__,_|\__, |\___|_|
                        |_|            |___/
*/

void Launcher::MainWindow::on_gb_join_toggled()
{
    bool off = true;
    if (ui->gb_join->isChecked())
        off = false;

    ui->btn_start->setText(vutil->getLabel());

    ui->gb_game->setDisabled(!off);

    if (off)
        VbaseConfig->setNetworkEnabled(0);
    else
        VbaseConfig->setNetworkEnabled(1);
}

void Launcher::MainWindow::on_btn_clear_ip_clicked()
{
    ui->le_ip->clear();
    ui->le_ip->setFocus();
}

void Launcher::MainWindow::on_btn_clear_port_clicked()
{
    ui->le_port->clear();
    ui->le_port->setFocus();
}


void Launcher::MainWindow::on_le_ip_textChanged(const QString &arg1)
{
    VbaseConfig->setIpAdress(arg1);
}

void Launcher::MainWindow::on_le_port_textChanged(const QString &arg1)
{
    VbaseConfig->setIpPort(arg1);
}


/*
           _                               _
  __ _  __| |_   ____ _ _ __   ___ ___  __| |
 / _` |/ _` \ \ / / _` | '_ \ / __/ _ \/ _` |
| (_| | (_| |\ V / (_| | | | | (_|  __/ (_| |
 \__,_|\__,_| \_/ \__,_|_| |_|\___\___|\__,_|
*/

void Launcher::MainWindow::on_cb_recorddemo_clicked()
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

void Launcher::MainWindow::on_le_playdemo_textChanged()
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

void Launcher::MainWindow::on_le_playdemo_2_textChanged()
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

void Launcher::MainWindow::on_btn_clear_loadgame_clicked()
{
    ui->le_loadgame->clear();
    ui->le_loadgame->setFocus();
}

void Launcher::MainWindow::on_btn_clear_playdemo_clicked()
{
    ui->le_playdemo->clear();
    ui->le_playdemo->setFocus();
}

void Launcher::MainWindow::on_btn_clear_playdemo2_clicked()
{
    ui->le_playdemo_2->clear();
    ui->le_playdemo_2->setFocus();
}

void Launcher::MainWindow::on_le_loadgame_textChanged()
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

void Launcher::MainWindow::on_btn_pick_demo_file_clicked()
{
    QString fileName = fileDialog->getOpenFileName(this, tr("Open recording demo"), vgzdoom->getGzdoomHomeDir());
    ui->le_playdemo->setText(fileName);
}

void Launcher::MainWindow::on_btn_pick_demo_file_2_clicked()
{
    QString fileName = fileDialog->getOpenFileName(this, tr("Open recording demo"), vgzdoom->getGzdoomHomeDir());
    ui->le_playdemo_2->setText(fileName);
}

void Launcher::MainWindow::on_btn_loadgame_clicked()
{
    QString fileName = fileDialog->getOpenFileName(this, tr("Open save file"), vgzdoom->getGzdoomHomeDir());
    ui->le_loadgame->setText(fileName);
}

void Launcher::MainWindow::on_le_map_textChanged(const QString &arg1)
{
    const QString last_iwad = VbaseConfig->getLastIwad();
    if (last_iwad.contains("DOOM.WAD", Qt::CaseInsensitive) \
            || last_iwad.contains("heretic", Qt::CaseInsensitive) \
            || last_iwad.contains("wolf", Qt::CaseInsensitive))
    {
        if (!arg1.isEmpty())
        {
            if (arg1.at(0).isDigit())
                ui->le_map->setText("E" + QString(arg1.at(0)).toUtf8());

            if (arg1.length() >= 3)
                if (arg1.at(2).isDigit())
                    ui->le_map->setText("E" + QString(arg1.at(1)).toUtf8() + "M" + QString(arg1.at(2)).toUtf8());
        }
    }
}

/*
 _ __ ___   ___ _ __  _   _
| '_ ` _ \ / _ \ '_ \| | | |
| | | | | |  __/ | | | |_| |
|_| |_| |_|\___|_| |_|\__,_|

*/

void Launcher::MainWindow::on_actionAbout_QT_triggered()
{
    QMessageBox::aboutQt(this, tr("About Qt"));
}

void Launcher::MainWindow::on_actionPreferences_triggered()
{
    connect(VconfigDialog, SIGNAL(accepted()), this, SLOT(updateColors()));
    VconfigDialog->show();
}

void Launcher::MainWindow::on_actionAbout_Chicken_Launcher_triggered()
{
    QMessageBox *msgBox = new QMessageBox(this);
    msgBox->setText(tr("<font size=\"5\" color=\"#FDBC5F\" align=\"center\"><b>Chicken <font color=\"#C959A2\">Launcher</font> <font color=\"#000\">v1.3.1</font></b></font>"));
    msgBox->setInformativeText(tr("SCOOTALOO! SCOOT-SCOOTALOO!\n\nChicken Launcher writen to be simple and powerfull.\
 Cross-platform and funny. Meme belong to Apple Bloom.\n\n\
Licensed under the Apache License, Version 2.0 (the \"License\"). \
You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0 or see LICENSE file."));
    msgBox->setStandardButtons(QMessageBox::Ok);
    msgBox->setIconPixmap(QPixmap(":/chicken.png"));
    msgBox->exec();
}

void Launcher::MainWindow::on_actionSearch_PWAD_triggered()
{
    const int currentTab = ui->tabWidget->currentIndex();
    QString headerText = "";

    if (currentTab == 0)
    {
        headerText = "Search for profile...";
    }
    else
    {
        headerText = "Search for PWAD...";
        ui->tabWidget->setCurrentIndex(1);
    }

    bool ok;
    QString text = QInputDialog::getText(this, "Chicken Launcher",
                                            headerText, QLineEdit::Normal,
                                            "", &ok);

    if (ok && !text.isEmpty())
    {
        if (currentTab == 0)
        {
            for (int i = 0; i < ui->lw_profile->count(); ++i)
            {
                if (ui->lw_profile->item(i)->text().contains(text))
                {
                     ui->lw_profile->item(i)->setSelected(true);
                     ui->lw_profile->scrollToItem(ui->lw_pwad->item(i));
                }
            }
        }
        else
        {
            for (int i = 0; i < ui->lw_pwad->count(); ++i)
            {
                if (ui->lw_pwad->item(i)->text().contains(text))
                {
                     ui->lw_pwad->item(i)->setSelected(true);
                     ui->lw_pwad->scrollToItem(ui->lw_pwad->item(i));
                }
            }
        }
    }
}

/*
 ___             _   _
| __|  _ _ _  __| |_(_)___ _ _  ___
| _| || | ' \/ _|  _| / _ \ ' \(_-<
|_| \_,_|_||_\__|\__|_\___/_||_/__/

*/

void Launcher::MainWindow::updateColors()
{
    for (int i = 0; i < ui->lw_iwad->count(); i++)
        if (ui->lw_iwad->item(i)->text() == VbaseConfig->getLastIwad())
            ui->lw_iwad->item(i)->setForeground(Qt::black);
}

void Launcher::MainWindow::windowInit()
{
    VbaseConfig->readAllSettings(VbaseConfig->getCurrentProfile());

    if (VbaseConfig->fileExist(VbaseConfig->getLauncherSettingsFile())
            && VbaseConfig->fileExist(VbaseConfig->getCurrentProfile()))
    {
            VlistFill->getIWadList();
            VlistFill->getPWadList();
            VlistFill->getProfiles();
            VlistFill->getPortConfigFile();

            int default_tab = VbaseConfig->getDefaultTab();

            if (VbaseConfig->getNetworkEnabled())
                ui->tabWidget->setCurrentIndex(3);
            else
                ui->tabWidget->setCurrentIndex(default_tab);
    }

    if (VbaseConfig->getHideGame() == 1)
    {
        connect(vgzdoom->process, SIGNAL(started()), this, SLOT(mainWindowShowHide()));
        connect(vgzdoom->process, SIGNAL(finished(int)), this, SLOT(mainWindowShowHide()));
    }

    trayIcon();

    //shortcurts
    ui->actionExit_Ctrl_Q->setShortcut(tr("CTRL+Q"));
    ui->actionMinimize_to_tray_Ctrl_T->setShortcut(tr("CTRL+T"));
    ui->actionSearch_PWAD->setShortcut(tr("CTRL+F"));
}

void Launcher::MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger)
        mainWindowShowHide();
}

void Launcher::MainWindow::trayIcon()
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

void Launcher::MainWindow::exitApp()
{
    QApplication::quit();
}

void Launcher::MainWindow::mainWindowShowHide()
{
    setVisible(!isVisible());
    this->setWindowState(Qt::WindowActive);
}

void Launcher::MainWindow::startApp()
{
    /*
    _____        _     _       _   _                            _
   |_   _|__  __| |___(_)  ___| |_| |_  ___ _ _   _ __  ___ _ _| |_ ___
     | |/ _ \/ _` / _ \_  / _ \  _| ' \/ -_) '_| | '_ \/ _ \ '_|  _(_-<
     |_|\___/\__,_\___(_) \___/\__|_||_\___|_|   | .__/\___/_|  \__/__/
                                                 |_|
    */

    if (!ui->le_playdemo->text().isEmpty())
        vgzdoom->startDemo();
    else if (ui->gb_join->isChecked())
        vgzdoom->networkGame();
    else
        vgzdoom->startGzdoom();
}

void Launcher::MainWindow::on_btn_start_clicked()
{
    startApp();
}

void Launcher::MainWindow::on_actionExit_Ctrl_Q_triggered()
{
    int hide = VbaseConfig->getHide();

    if (hide == 1)
        mainWindowShowHide();
    else
        QApplication::quit();
}

void Launcher::MainWindow::on_actionMinimize_to_tray_Ctrl_T_triggered()
{
    mainWindowShowHide();
}

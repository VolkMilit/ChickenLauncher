#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    vutil(new Utils::util(ui)),
    vgzdoom(new gzdoom(ui)),
    vdarkplaces(new Games::darkplaces(ui)),
    VbaseConfig(new Utils::baseConfig(ui)),
    VlistFill(new Utils::listFill(ui)),
    Vcolors(new Utils::colors()),
    VdescriptionsHandler(new descriptionsHandler(ui)),
    VconfigDialog(new configDialog())
{
    ui->setupUi(this);
    windowInit();

}

MainWindow::~MainWindow()
{
    delete vdarkplaces;
    delete Vcolors;
    delete VlistFill;
    delete VdescriptionsHandler;
    delete VbaseConfig;
    delete vgzdoom;
    delete vutil;
    delete ui;
}

/*
 _ __ ___   ___ _ __  _   _
| '_ ` _ \ / _ \ '_ \| | | |
| | | | | |  __/ | | | |_| |
|_| |_| |_|\___|_| |_|\__,_|

*/

void MainWindow::on_actionAbout_QT_triggered()
{
    QMessageBox::aboutQt(this, tr("About Qt"));
}

void MainWindow::on_actionPreferences_triggered()
{
    //connect(VconfigDialog, SIGNAL(accepted()), this, SLOT(updateColors()));
    VconfigDialog->show();
}

void MainWindow::on_actionAbout_Chicken_Launcher_triggered()
{
    QMessageBox *msgBox = new QMessageBox(this);
    msgBox->setText(
            "<font size=\"5\" color=\"#FDBC5F\" align=\"center\">"
            "<b>Chicken <font color=\"#C959A2\">Launcher</font>"
            "<font color=\"#000\">v1.4.0</font></b></font>"
        );

    msgBox->setInformativeText(
                    "SCOOTALOO! SCOOT-SCOOTALOO!\n\nChicken Launcher (trying to be) written to be simple, "
                    "powerfull and cross-platform.\n\nLicensed under WTFPL v2.0 (see LICENSE file)"
                );
    msgBox->setStandardButtons(QMessageBox::Ok);
    msgBox->setIconPixmap(QPixmap(":/chicken.png"));
    msgBox->exec();

    delete msgBox;
}

void MainWindow::on_actionGZDoom_triggered()
{
    setGame(1, 0);
}

void MainWindow::on_actionDarkPlaces_triggered()
{
    setGame(3, 1);
}

/*
 ___             _   _
| __|  _ _ _  __| |_(_)___ _ _  ___
| _| || | ' \/ _|  _| / _ \ ' \(_-<
|_| \_,_|_||_\__|\__|_\___/_||_/__/

*/

void MainWindow::setGame(const short idTechLevel, const short idEngine)
{
    // see description in listfill.cpp

    bool hide = false;

    if (idTechLevel >= 3)
        hide = true;

    ui->gb_game_darkplaces->setHidden(!hide);
    ui->lw_port_configs_files->setHidden(hide);
    ui->label_10->setHidden(hide);
    ui->gb_game->setHidden(hide);
    ui->gb_demos->setHidden(hide);
    ui->le_pwad->setHidden(hide);
    ui->label_4->setHidden(hide);
    ui->btn_pwad_path->setHidden(hide);
    ui->btn_new_config->setHidden(hide);
    ui->btn_load_config->setHidden(hide);
    ui->btn_delete_config->setHidden(hide);
    ui->label->setHidden(hide);
    ui->lw_iwad->setHidden(hide);
    ui->tabWidget->setTabEnabled(3, !hide);

    VbaseConfig->setGamePort(idEngine);

    // here you can disable all stuff that doesn't need for particular engine
    // all common stuff already disabled, since it doesn't needed for QuakeEngine and above

    switch (idEngine)
    {
        case 0: // gzdoom (DOOM I, II; Hexen (beyond heretic), Heretic, and other games)
            ui->actionGZDoom->setChecked(true);
            ui->label_2->setText("IWAD:");
            ui->label_3->setText("Path to IWADs dir:");
            break;

        case 1: // darkplaces (Quake 1, and other games)
            ui->actionDarkPlaces->setChecked(true);
            ui->label_2->setText("Game:");
            ui->label_3->setText("Path to basedir:");
            break;

        default: // fallback to gzdoom
            ui->actionGZDoom->setChecked(true);
            ui->label_2->setText("IWAD:");
            ui->label_3->setText("Path to IWADs dir:");
            VbaseConfig->setGamePort(0);
            break;
    }
}

inline void MainWindow::windowInit()
{
    ui->ltw_profile->horizontalHeader()->setResizeMode(0, QHeaderView::ResizeToContents);
    ui->ltw_profile->horizontalHeader()->setResizeMode(1, QHeaderView::ResizeToContents);

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

    QFileInfo title(VbaseConfig->getCurrentProfile());
    setWindowTitle(title.baseName() + ".ini - Chicken Launcher");

    this->setGame(VbaseConfig->getGamePort() ? 3 : 1, VbaseConfig->getGamePort());
}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger)
        mainWindowShowHide();
}

inline void MainWindow::trayIcon()
{
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

inline void MainWindow::startApp()
{
    if (ui->actionGZDoom->isChecked())
    {
        if (!ui->le_playdemo->text().isEmpty())
            vgzdoom->startDemo();
        else if (ui->gb_join->isChecked())
            vgzdoom->networkGame();
        else
            vgzdoom->startGzdoom();
    }
    else if (ui->actionDarkPlaces->isChecked())
    {
        vdarkplaces->startDarkplaces();
    }
    else
    {
        QMessageBox::information(this, "ChickenLauncher", "Set game first.", QMessageBox::Ok);
    }
}

void MainWindow::on_btn_start_clicked()
{
    startApp();
}

void MainWindow::on_actionExit_Ctrl_Q_triggered()
{
    int hide = VbaseConfig->getHide();

    if (hide == 1)
        mainWindowShowHide();
    else
        QApplication::quit();
}

void MainWindow::on_actionMinimize_to_tray_Ctrl_T_triggered()
{
    mainWindowShowHide();
}

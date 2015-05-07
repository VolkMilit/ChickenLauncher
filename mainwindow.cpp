#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    getWadList();
    trayIcon();
    readSettings("default.ini");
    getProfiles();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**********************************Functions***************************************************/
void MainWindow::trayIcon()
{
    QSystemTrayIcon *trIcon = new QSystemTrayIcon(this);
    trIcon->setIcon(windowIcon());
    trIcon->setToolTip("Chicken Launcher");
    trIcon->show();

    QMenu *trayMenu = new QMenu (this);

    QAction *actionShowHide = new QAction (tr("Show\\Hide"), this);
    QAction *actionExit = new QAction (tr("Exit"), this);

    trayMenu->addAction(actionShowHide);
    trayMenu->addAction(actionExit);

                                /*I'm not sure, but it's working...*/
    connect(trIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(mainWindowShowHide()));
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

void MainWindow::getWadList()
{
    ui->lw_iwad->clear();
    ui->lw_pwad->clear();
    QStringList filter = QStringList() << "*.zip" << "*.wad" << "*.pk7" << "*.pk3" << "*.7z" << "*.rar";
    //QDir iwad_dir(dir);

    //if (dir.isEmpty())
    //{
        QDir iwad_dir(ui->le_iwad->text());
        if(!iwad_dir.exists())
            iwad_dir = QDir::currentPath();
    //}

    QDir pwad_dir(ui->le_pwad->text());
    if(!pwad_dir.exists())
        pwad_dir = QDir::currentPath();

    QStringList IWAD_files = iwad_dir.entryList(filter, QDir::Files /*| QDir::Dirs*/);
    for (int i = 0; i < IWAD_files.size(); i++)
    {
       // if (IWAD_files.at(i) == "." || IWAD_files.at(i) == "..")
         //   continue;

        ui->lw_iwad->addItem(iwad_dir.absolutePath() + "/" + IWAD_files.at(i));
    }

    QStringList PWAD_files = pwad_dir.entryList(filter, QDir::Files /*| QDir::Dirs*/);
    for (int i = 0; i < PWAD_files.size(); i++)
    {
        //if (PWAD_files.at(i) == "." || PWAD_files.at(i) == "..")
          //  continue;

        ui->lw_pwad->addItem(pwad_dir.absolutePath() + "/" + PWAD_files.at(i));
    }

}

void MainWindow::writeSettings(QString file)
{
    QSettings settings(file, QSettings::IniFormat);

    settings.beginGroup("WAD");
    settings.setValue("iwad", ui->le_iwad->text());
    settings.setValue("pwad", ui->le_pwad->text());
    settings.setValue("last_iwad",  iwad);
    settings.setValue("last_pwads", pwad);
    settings.endGroup();

    settings.beginGroup("Port");
    //settings.setValue("port_name", NULL); //todo
    settings.setValue("port_exe", ui->le_exe->text());
    settings.setValue("additional_port_param", ui->le_param->text());
    settings.endGroup();

    /*settings.beginGroup("Profile");
    settings.setValue("custom_profile", ui->lw_profile->currentItem()->text());
    settings.endGroup();*/
}

void MainWindow::readSettings(QString file)
{
    QFile f(file);
    if (!f.exists())
    {
        QMessageBox::critical(this, "", "Nobody, but us chicken! File does'n exist!");

        //delete item, don't know, if it's ugly code, but working
        QListWidgetItem *it = ui->lw_profile->item(ui->lw_profile->currentRow());
        delete it;

        return;
    }

    QSettings settings(file, QSettings::IniFormat);

    settings.beginGroup("WAD");
    ui->le_iwad->setText(settings.value("iwad").toString());
    ui->le_pwad->setText(settings.value("pwad").toString());
    iwad = settings.value("last_iwad").toString();
    pwad = settings.value("last_pwads").toString();
    settings.endGroup();

    settings.beginGroup("Port");
    //settings.setValue("port_name", NULL); //todo
    ui->le_exe->setText(settings.value("port_exe").toString());
    ui->le_param->setText(settings.value("additional_port_param").toString());
    settings.endGroup();

    /*settings.beginGroup("Profile");
    readSettings(settings.value("custom_profile").toString());
    settings.endGroup();*/
}

void MainWindow::getProfiles()
{
    ui->lw_profile->clear();
    QDir dir(QDir::currentPath());
    QStringList ini_files = dir.entryList(QStringList() << "*.ini", QDir::Files);
    for (int i = 0; i < ini_files.size(); i++)
        ui->lw_profile->addItem(ini_files.at(i));
}

void MainWindow::parametrParser()
{
    if (!ui->cb_load_last_wads->isChecked())
    {
        pwad = "";
        foreach(QListWidgetItem *item,  ui->lw_pwad->selectedItems())
            pwad += item->text() + " ";

        iwad = "";
        if (ui->lw_iwad->currentItem() != nullptr)
            iwad = ui->lw_iwad->currentItem()->text();

        writeSettings("default.ini");
    }

    skill = "";
    if (ui->cb_skill->isChecked())
        skill = QString::number(ui->cob_skill->currentIndex());

    exe = "";
    if (!ui->le_exe->text().isEmpty())
        exe = ui->le_exe->text();
    else if (ui->lw_port->currentItem() != nullptr)
        exe = ui->lw_port->currentItem()->text().toLower();
    else
        exe = "gzdoom";

    if (!ui->le_exe->text().isEmpty())
        exe = ui->le_exe->text();

    nomusic = "";
    if (ui->cb_nomusic->isChecked())
        nomusic = " -nomusic ";

    nosound = "";
    if (ui->cb_nosound->isChecked())
        nosound = " -nosound ";

    nosfx = "";
    if (ui->cb_nosfx->isChecked())
        nosfx = " -nosfx ";

    map = "";
    if (!ui->le_map->text().isEmpty())
    {
        map = " -warp " + ui->le_map->text();
        if (ui->le_map->text().at(0) == QChar('E', false) && ui->le_map->text().at(2) == QChar('M', false))
            map = " -warp " + ui->le_map->text().mid(1,1) + " " + ui->le_map->text().mid(3,3);
    }

    demo = "";
    QDateTime dt;
    if (ui->cb_recorddemo->isChecked())
        demo = " -record " + dt.currentDateTime().toString("yyyy-MM-dd_H:mm:s") + ".lmp";

    oldsprites = "";
    if (ui->cb_oldsprites->isChecked())
        oldsprites = " -oldsprites ";

    noautoload = "";
    if (ui->cb_noautoload->isChecked())
        noautoload = " -noautoload ";

    nostartup = "";
    if (ui->cb_nostartup->isChecked())
        nostartup = " -nostartup ";
}

void MainWindow::startApp()
{
    QProcess *process1 = new QProcess(this);

    if (!ui->le_loadgame->text().isEmpty())
        process1->start(exe + " -loadgame " + ui->le_loadgame->text());
    else if (!ui->le_playdemo->text().isEmpty())
        process1->start(exe + " -playdemo " + ui->le_playdemo->text());
    else if (!ui->le_playdemo_2->text().isEmpty())
        process1->start(exe + " -timedemo " + ui->le_playdemo_2->text());
    else if (ui->gb_join->isChecked())
        process1->start(exe + " -join " + ui->le_ip->text() + ":" + ui->le_port->text());
    else
        process1->start(exe + " -iwad " + iwad + " -file " + pwad + "-skill " + skill\
                    + map + " " + ui->le_param->text() + nomusic + nosound + nosfx + demo\
                    + oldsprites + noautoload + nostartup);

    mainWindowShowHide();
    if (process1->waitForFinished())
        mainWindowShowHide();
}

/**********************************Signals***************************************************/
void MainWindow::on_btn_pick_demo_file_clicked()
{
    QString fileName = fileDialog.getOpenFileName(this, tr("Open recording demo"), QDir::currentPath());
    ui->le_playdemo->setText(fileName);
}

void MainWindow::on_btn_pick_demo_file_2_clicked()
{
    QString fileName = fileDialog.getOpenFileName(this, tr("Open recording demo"), QDir::currentPath());
    ui->le_playdemo_2->setText(fileName);
}

void MainWindow::on_btn_loadgame_clicked()
{
    QString fileName = fileDialog.getOpenFileName(this, tr("Open save file"), QDir::currentPath());
    ui->le_loadgame->setText(fileName);
}


void MainWindow::on_btn_load_clicked()
{
    if (ui->lw_profile->currentItem() != nullptr)
        readSettings(ui->lw_profile->currentItem()->text());
}

void MainWindow::on_btn_exe_clicked()
{
    QString fileName = fileDialog.getOpenFileName(this, tr("Open Port Exe"),
                        QDir::currentPath(),
                        "Any file *.* (*)");
    ui->le_exe->setText(fileName);
    writeSettings("default.ini");
}

void MainWindow::on_cb_load_last_wads_clicked()
{
    if (ui->cb_load_last_wads->isChecked())
    {
        ui->lw_iwad->setEnabled(false);
        ui->lw_pwad->setEnabled(false);
        ui->tabWidget->setTabEnabled(3, false);
        ui->tabWidget->setTabEnabled(4, false);
    }
    else
    {
        ui->lw_iwad->setEnabled(true);
        ui->lw_pwad->setEnabled(true);
        ui->tabWidget->setTabEnabled(3, true);
        ui->tabWidget->setTabEnabled(4, true);
    }
}


void MainWindow::on_btn_new_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                            tr("Add profile"), QLineEdit::Normal,
                                            "", &ok);

    if (ok && !text.isEmpty())
    {
        ui->lw_profile->addItem(text + ".ini");
        writeSettings(text + ".ini");
    }
}

void MainWindow::on_btn_about_clicked()
{
    QMessageBox *msgBox = new QMessageBox(this);
    msgBox->setText("SCOOTALOO! SCOOT-SCOOTALOO!");
    msgBox->setInformativeText("Chicken Launcher writen to be simple and powerfull.\
 Cross-platform and funny. Meme belong to Apple Bloom.\n\n\
Licensed under the Apache License, Version 2.0 (the \"License\"). \
You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0 or see LICENSE file.");
    msgBox->setStandardButtons(QMessageBox::Ok);
    msgBox->setIconPixmap(QPixmap(":/chicken.png"));
    msgBox->exec();
    QMessageBox::aboutQt(this, "About Qt");
}

void MainWindow::on_le_iwad_textChanged()
{
    getWadList();
}

void MainWindow::on_le_pwad_textChanged()
{
    getWadList();
}

void MainWindow::on_btn_start_clicked()
{
    parametrParser();
    startApp();
}

void MainWindow::on_btn_iwad_path_clicked()
{
    QString fileName = fileDialog.getExistingDirectory(this, tr("Open iwad folder"), QDir::currentPath());
    ui->le_iwad->setText(fileName);
    writeSettings("default.ini");
}

void MainWindow::on_btn_pwad_path_clicked()
{
    QString fileName = fileDialog.getExistingDirectory(this, tr("Open pwad folder"), QDir::currentPath());
    ui->le_pwad->setText(fileName);
    writeSettings("default.ini");
}

void MainWindow::on_btn_help_clicked()
{
    QMessageBox::information(this, "", "See docs on <a href=\"https://github.com/VolkMilit/ChickenLauncher\">github</a> or\
                                       in downloaded repository in DOCS directory.");
}

void MainWindow::on_btn_delete_clicked()
{
    QListWidgetItem *it = ui->lw_profile->item(ui->lw_profile->currentRow());
    delete it;
}

void MainWindow::on_gb_join_toggled()
{
    if (ui->gb_join->isChecked())
    {
        ui->tabWidget->setTabEnabled(1, false);
        ui->tabWidget->setTabEnabled(2, false);
        ui->tabWidget->setTabEnabled(4, false);
    }
    else
    {
        ui->tabWidget->setTabEnabled(1, true);
        ui->tabWidget->setTabEnabled(2, true);
        ui->tabWidget->setTabEnabled(4, true);
    }
}

void MainWindow::on_cb_recorddemo_clicked()
{
    if (ui->cb_recorddemo->isChecked())
    {
        ui->le_playdemo->setEnabled(false);
        ui->le_playdemo_2->setEnabled(false);
        ui->lb_playdemo->setEnabled(false);
        ui->lb_playdemo2->setEnabled(false);
        ui->btn_pick_demo_file->setEnabled(false);
        ui->btn_pick_demo_file_2->setEnabled(false);

    }
    else
    {
        ui->le_playdemo->setEnabled(true);
        ui->le_playdemo_2->setEnabled(true);
        ui->lb_playdemo->setEnabled(true);
        ui->lb_playdemo2->setEnabled(true);
        ui->btn_pick_demo_file->setEnabled(true);
        ui->btn_pick_demo_file_2->setEnabled(true);
    }
}

void MainWindow::on_le_playdemo_textChanged()
{
    if (!ui->le_playdemo->text().isEmpty())
    {
        ui->gb_game->setEnabled(false);
        ui->cb_recorddemo->setEnabled(false);
        ui->le_playdemo_2->setEnabled(false);
        ui->btn_clear_playdemo2->setEnabled(false);
        ui->btn_pick_demo_file_2->setEnabled(false);
        ui->lb_playdemo2->setEnabled(false);
        ui->tabWidget->setTabEnabled(1, false);
        ui->tabWidget->setTabEnabled(3, false);
    }
    else
    {
        ui->gb_game->setEnabled(true);
        ui->cb_recorddemo->setEnabled(true);
        ui->le_playdemo_2->setEnabled(true);
        ui->btn_clear_playdemo2->setEnabled(true);
        ui->btn_pick_demo_file_2->setEnabled(true);
        ui->lb_playdemo2->setEnabled(true);
        ui->tabWidget->setTabEnabled(1, true);
        ui->tabWidget->setTabEnabled(3, true);
    }
}

void MainWindow::on_le_playdemo_2_textChanged()
{
    if (!ui->le_playdemo_2->text().isEmpty())
    {
        ui->gb_game->setEnabled(false);
        ui->cb_recorddemo->setEnabled(false);
        ui->le_playdemo->setEnabled(false);
        ui->btn_clear_playdemo->setEnabled(false);
        ui->btn_pick_demo_file->setEnabled(false);
        ui->lb_playdemo->setEnabled(false);
        ui->tabWidget->setTabEnabled(1, false);
        ui->tabWidget->setTabEnabled(3, false);
    }
    else
    {
        ui->gb_game->setEnabled(true);
        ui->cb_recorddemo->setEnabled(true);
        ui->le_playdemo->setEnabled(true);
        ui->btn_clear_playdemo->setEnabled(true);
        ui->btn_pick_demo_file->setEnabled(true);
        ui->lb_playdemo->setEnabled(true);
        ui->tabWidget->setTabEnabled(1, true);
        ui->tabWidget->setTabEnabled(3, true);
    }
}

void MainWindow::on_btn_clear_loadgame_clicked()
{
    ui->le_loadgame->clear();
}

void MainWindow::on_btn_clear_playdemo_clicked()
{
    ui->le_playdemo->clear();
}

void MainWindow::on_btn_clear_playdemo2_clicked()
{
    ui->le_playdemo_2->clear();
}

void MainWindow::on_le_loadgame_textChanged()
{
    if (!ui->le_loadgame->text().isEmpty())
    {
        for (int i=0;i<4;i++)
            ui->tabWidget->setTabEnabled(i, false);
        ui->gb_game->setEnabled(false);
        ui->gb_demos->setEnabled(false);
    }
    else
    {
        for (int i=0;i<4;i++)
            ui->tabWidget->setTabEnabled(i, true);
        ui->gb_game->setEnabled(true);
        ui->gb_demos->setEnabled(true);
    }
}

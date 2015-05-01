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
    loadProfiles();
}

MainWindow::~MainWindow()
{
    delete ui;
}

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

    QDir iwad_dir(ui->le_iwad->text());
    if(!iwad_dir.exists())
        iwad_dir = QDir::currentPath();

    QDir pwad_dir(ui->le_pwad->text());
    if(!pwad_dir.exists())
        pwad_dir = QDir::currentPath();

    QStringList IWAD_files = iwad_dir.entryList(filter, QDir::Files);
    for (int i = 0; i < IWAD_files.size(); i++)
        ui->lw_iwad->addItem(iwad_dir.absolutePath() + "/" + IWAD_files.at(i));

    QStringList PWAD_files = pwad_dir.entryList(filter, QDir::Files);
    for (int i = 0; i < PWAD_files.size(); i++)
        ui->lw_pwad->addItem(pwad_dir.absolutePath() + "/" + PWAD_files.at(i));

}

void MainWindow::on_btn_about_clicked()
{
    QMessageBox *msgBox = new QMessageBox(this);
    msgBox->setText("SCOOTALOO! SCOOT-SCOOTALOO!");
    msgBox->setInformativeText("Chicken Launcher writen to be simple and powerfull.\
                               Cross-platform and funny. Meme belong to Apple Bloom.");
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

    QString skill = "";
    if (ui->cb_skill->isChecked())
        skill = QString::number(ui->cob_skill->currentIndex());

    QString exe = "";
    if (!ui->le_exe->text().isEmpty())
        exe = ui->le_exe->text();
    else if (ui->lw_port->currentItem() != nullptr)
        exe = ui->lw_port->currentItem()->text().toLower();
    else
        exe = "gzdoom";

    if (!ui->le_exe->text().isEmpty())
        exe = ui->le_exe->text();

    QString nomusic = "";
    if (ui->cb_nomusic->isChecked())
        nomusic = " -nomusic ";

    QString nosound = "";
    if (ui->cb_nosound->isChecked())
        nosound = " -nosound ";

    QString nosfx = "";
    if (ui->cb_nosfx->isChecked())
        nosfx = " -nosfx ";

    QString map = "";
    if (!ui->le_map->text().isEmpty())
        map = " -warp " + ui->le_map->text();

    QString demo = "";
    QDateTime dt;
    if (ui->cb_recorddemo->isChecked())
        demo = " -record " + dt.currentDateTime().toString("yyyy-MM-dd_H:mm:s") + ".lmp";

    QProcess *process1 = new QProcess(this);
    process1->start(exe + " -iwad " + iwad + " -file " + pwad + "-skill " + skill\
                    + map + " " + ui->le_param->text() + nomusic + nosound + nosfx + demo);
    mainWindowShowHide();
    if (process1->waitForFinished()) mainWindowShowHide();
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

void MainWindow::writeSettings(QString file)
{
    QSettings settings(file, QSettings::IniFormat);

    settings.beginGroup("WAD");
    settings.setValue("iwad", ui->le_iwad->text());
    settings.setValue("pwad", ui->le_pwad->text());
    settings.setValue("last_iwad", iwad);
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

void MainWindow::loadProfiles()
{
    ui->lw_profile->clear();
    QDir dir(QDir::currentPath());
    QStringList ini_files = dir.entryList(QStringList() << "*.ini", QDir::Files);
    for (int i = 0; i < ini_files.size(); i++)
        ui->lw_profile->addItem(ini_files.at(i));
}

void MainWindow::on_btn_new_clicked()
{    
    bool ok;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                            tr("Add profile"), QLineEdit::Normal,
                                            "", &ok);
    QString txt = text + ".ini"; //magic
    if (ok && !text.isEmpty())
    {
        ui->lw_profile->addItem(text);
        writeSettings(txt);
        loadProfiles();
    }
}

void MainWindow::on_btn_load_clicked()
{
    //segfault... FUCK!
    if (ui->lw_profile->currentItem() != nullptr)
        readSettings(ui->lw_iwad->currentItem()->text());
}

void MainWindow::on_btn_exe_clicked()
{
    QString fileName = fileDialog.getOpenFileName(this, tr("Open Port Exe"),
                        QDir::currentPath(),
                        "Any file *.* (*)");
    ui->le_exe->setText(fileName);
    writeSettings("default.ini");
}

void MainWindow::on_lw_profile_clicked()
{
    QMessageBox::information(this, "", "Profiles NOT WORKING YET! Loading custom profile CAUSING SEGFAULT!");
}

void MainWindow::on_cb_load_last_wads_clicked()
{
    if (ui->cb_load_last_wads->isChecked())
    {
        ui->lw_iwad->setEnabled(false);
        ui->lw_pwad->setEnabled(false);
    }
    else
    {
        ui->lw_iwad->setEnabled(true);
        ui->lw_pwad->setEnabled(true);
    }
}

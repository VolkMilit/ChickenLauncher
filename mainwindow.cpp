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
    msgBox->setInformativeText("Chicken Launcher writen to be simple and powerfull. Cross-platform and funny. Meme belong to Apple Bloom.");
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
    QString pwad = ""; //DON'T DELETE: magic
    foreach(QListWidgetItem *item,  ui->lw_pwad->selectedItems())
        pwad += item->text() + " ";

    /*FIX ME!*/
    QString skill = "";
    if (ui->cb_skill->isChecked())
        switch(ui->cob_skill->currentIndex())
        {
            case 1:
            skill = "1";
            break;

            case 2:
            skill = "2";
            break;

            case 3:
            skill = "3";
            break;

            case 4:
            skill = "4";
            break;

            case 5:
            skill = "5";
            break;
        }

    QString exe = "doom";
    if (!ui->le_exe->text().isEmpty())
        exe = ui->le_exe->text();

    QString map = "";
    if (!ui->le_map->text().isEmpty())
        map = ui->le_map->text();

    QProcess *process1 = new QProcess();
    process1->start(exe + " -IWAD " + ui->lw_iwad->currentItem()->text() + " -file " + pwad + "-skill " + skill\
                    + " -warp " + map + " " + ui->le_param->text());
    mainWindowShowHide();
    if (process1->waitForFinished())
        mainWindowShowHide();
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
    settings.endGroup();

    settings.beginGroup("Port");
    //settings.setValue("port_name", NULL); //todo
    settings.setValue("port_exe", ui->le_exe->text());
    settings.setValue("additional_port_param", ui->le_param->text());
    settings.endGroup();
}

void MainWindow::readSettings(QString file)
{
    QSettings settings(file, QSettings::IniFormat);

    settings.beginGroup("WAD");
    ui->le_iwad->setText(settings.value("iwad").toString());
    ui->le_pwad->setText(settings.value("pwad").toString());
    settings.endGroup();

    settings.beginGroup("Port");
    //settings.setValue("port_name", NULL); //todo
    ui->le_exe->setText(settings.value("port_exe").toString());
    ui->le_param->setText(settings.value("additional_port_param").toString());
    settings.endGroup();
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
    if (ui->lw_profile->currentItem() != nullptr) {
        readSettings(ui->lw_iwad->currentItem()->text());
    }

    /*signal(SIGSEGV, 13);
    QMessageBox::information(this, "FUCK IT!", "FUCKING QT SEGFAULT AGAIN! ALL HAIL DIGIA! Code is: 13");*/

}

void MainWindow::on_btn_exe_clicked()
{
    QString fileName = fileDialog.getOpenFileName(this, tr("Open Port Exe"),
                        QDir::currentPath(),
                        "Any file *.* (*)");
    ui->le_exe->setText(fileName);
    writeSettings("default.ini");
}

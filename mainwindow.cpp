#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    getWadList();
    trayIcon();
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
    {
        pwad += item->text() + " ";
    }

    QProcess *process1 = new QProcess();
    process1->start("doom -IWAD " + ui->lw_iwad->currentItem()->text() + " -file " + pwad);
    mainWindowShowHide();
    if (process1->waitForFinished())
        mainWindowShowHide();
}

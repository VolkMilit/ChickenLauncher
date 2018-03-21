#include "mainwindow.h"

/*
                 _ _   _       _
 _ __ ___  _   _| | |_(_)_ __ | | __ _ _   _  ___ _ __
| '_ ` _ \| | | | | __| | '_ \| |/ _` | | | |/ _ \ '__|
| | | | | | |_| | | |_| | |_) | | (_| | |_| |  __/ |
|_| |_| |_|\__,_|_|\__|_| .__/|_|\__,_|\__, |\___|_|
                        |_|            |___/
*/

void MainWindow::on_gb_join_toggled()
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


void MainWindow::on_le_ip_textChanged(const QString &arg1)
{
    VbaseConfig->setIpAdress(arg1);
}

void MainWindow::on_le_port_textChanged(const QString &arg1)
{
    VbaseConfig->setIpPort(arg1);
}

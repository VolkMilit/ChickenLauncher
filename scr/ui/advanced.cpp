#include "mainwindow.h"

/*
           _                               _
  __ _  __| |_   ____ _ _ __   ___ ___  __| |
 / _` |/ _` \ \ / / _` | '_ \ / __/ _ \/ _` |
| (_| | (_| |\ V / (_| | | | | (_|  __/ (_| |
 \__,_|\__,_| \_/ \__,_|_| |_|\___\___|\__,_|
*/

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

void MainWindow::on_btn_pick_demo_file_clicked()
{
    QString fileName = fileDialog->getOpenFileName(this, tr("Open recording demo"), vgzdoom->getGzdoomHomeDir());
    ui->le_playdemo->setText(fileName);
}

void MainWindow::on_btn_pick_demo_file_2_clicked()
{
    QString fileName = fileDialog->getOpenFileName(this, tr("Open recording demo"), vgzdoom->getGzdoomHomeDir());
    ui->le_playdemo_2->setText(fileName);
}

void MainWindow::on_btn_loadgame_clicked()
{
    QString fileName = fileDialog->getOpenFileName(this, tr("Open save file"), vgzdoom->getGzdoomHomeDir());
    ui->le_loadgame->setText(fileName);
}

void MainWindow::on_le_map_textChanged(const QString &arg1)
{
    if (vutil->checkGame())
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

void MainWindow::on_cb_darkplaces_water_toggled(bool checked)
{
    VbaseConfig->setDarkplacesWater(checked ? 1 : 0);
}

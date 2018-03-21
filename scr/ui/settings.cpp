#include "mainwindow.h"

/*
          _   _   _
 ___  ___| |_| |_(_)_ __   __ _ ___
/ __|/ _ \ __| __| | '_ \ / _` / __|
\__ \  __/ |_| |_| | | | | (_| \__ \
|___/\___|\__|\__|_|_| |_|\__, |___/
                          |___/
*/

// change iwad path button
void MainWindow::on_btn_iwad_path_clicked()
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

// change pwad path button
void MainWindow::on_btn_pwad_path_clicked()
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

// iwad path changed
void MainWindow::on_le_iwad_textChanged()
{
    VbaseConfig->setIwadDir(ui->le_iwad->text());
    VlistFill->getIWadList();
}

// pwad path changed
void MainWindow::on_le_pwad_textChanged()
{
    VbaseConfig->setPwadDir(ui->le_pwad->text());
    VlistFill->getPWadList();
}

void MainWindow::on_btn_exe_clicked()
{
    QString fileName = fileDialog->getOpenFileName(this, tr("Open Port Exe"),
                        ui->le_exe->text(),
                        "Any file *.* (*)");

    if (!fileName.isNull()) ui->le_exe->setText(fileName);
}

void MainWindow::on_le_exe_textChanged()
{
    VbaseConfig->setExePath(ui->le_exe->text());
}

void MainWindow::on_le_adv_cmd_param_textChanged()
{
    VbaseConfig->setAdvCmdParam(ui->le_adv_cmd_param->text());
}

void MainWindow::on_le_adv_port_param_textChanged()
{
    VbaseConfig->setAdvExeParam(ui->le_adv_port_param->text());
}

void MainWindow::on_btn_clear_advancedparam_clicked()
{
    ui->le_adv_port_param->clear();
    ui->le_adv_port_param->setFocus();
}

void MainWindow::on_btn_new_config_clicked()
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

void MainWindow::on_btn_load_config_clicked()
{
    QListWidgetItem *item = ui->lw_port_configs_files->currentItem();

    if (!item)
        return;

    VbaseConfig->setConfigFile(item->text());
    Vcolors->clearColor(ui->lw_port_configs_files);
    item->setForeground(Vcolors->getColor());
    item->setSelected(false);
}

void MainWindow::on_btn_delete_config_clicked()
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

void MainWindow::on_lw_port_configs_files_itemSelectionChanged()
{
    ui->btn_delete_config->setDisabled(false);

    QListWidgetItem *item = ui->lw_port_configs_files->currentItem();

    if (item->text() == "default")
        ui->btn_delete_config->setDisabled(true);
}

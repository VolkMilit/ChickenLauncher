#include "mainwindow.h"

/*
                  __ _ _
 _ __  _ __ ___  / _(_) | ___  ___
| '_ \| '__/ _ \| |_| | |/ _ \/ __|
| |_) | | | (_) |  _| | |  __/\__ \
| .__/|_|  \___/|_| |_|_|\___||___/
|_|
*/

// new profile clicked
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
        VbaseConfig->setCurrentProfile(text + ".ini");
        Vcolors->clearColor(ui->lw_profile);

        //tmp ducktape, but I, actually, too lazy to fix this
        ui->lw_profile->item(ui->lw_profile->count() - 1)->setForeground(Vcolors->getColor());
    }
}

// load profile clicked
void MainWindow::on_btn_load_clicked()
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

    QFileInfo title(VbaseConfig->getCurrentProfile());
    setWindowTitle(title.baseName() + ".ini - Chicken Launcher");

    setGame(VbaseConfig->getGamePort() ? 3 : 1, VbaseConfig->getGamePort());
}

// rename profile clicked
void MainWindow::on_btn_rename_clicked()
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

// delete profile clicked
void MainWindow::on_btn_delete_clicked()
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

// clone profile clicked
void MainWindow::on_btn_clone_clicked()
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

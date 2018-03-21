#include "mainwindow.h"

/*
                   _
__      ____ _  __| |___
\ \ /\ / / _` |/ _` / __|
 \ V  V / (_| | (_| \__ \
  \_/\_/ \__,_|\__,_|___/

*/

// -========== functions ==========- //
void MainWindow::setLastPwadHelper(bool backward)
{
    vutil->moveItem(backward, ui->lw_pwad);
    VbaseConfig->setLastPwad("");
    VbaseConfig->setLastPwad(vutil->getPwadChecked());
}

void MainWindow::setLastPwadHelperTo(bool top)
{
    vutil->moveItemTo(top, ui->lw_pwad);
    VbaseConfig->setLastPwad("");
    VbaseConfig->setLastPwad(vutil->getPwadChecked());
}

void MainWindow::setLastPwadHelper()
{
    VbaseConfig->setLastPwad("");
    VbaseConfig->setLastPwad(vutil->getPwadChecked());
}

// search in pwad menu item
void MainWindow::on_actionSearch_PWAD_triggered()
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

// -========== slots ==========- //

// clear pwad button clicked
void MainWindow::on_btn_clear_selected_pwad_clicked()
{
    //ui->lw_pwad->currentItem()->setSelected(false);

    for(int i = 0; i < ui->lw_pwad->count(); i++)
    {
        if (ui->lw_pwad->item(i)->checkState() == Qt::Checked)
            ui->lw_pwad->item(i)->setCheckState(Qt::Unchecked);
        ui->lw_pwad->item(i)->setForeground(Qt::black);
    }
}

// pwad upwards
void MainWindow::on_btn_pwad_up_clicked()
{
    this->setLastPwadHelper(true);
}

// pwad downwards
void MainWindow::on_btn_pwad_down_clicked()
{
    this->setLastPwadHelper(false);
}

// pwad to top
void MainWindow::on_btn_pwad_top_clicked()
{
    this->setLastPwadHelperTo(true);
}

// pwad to bottom
void MainWindow::on_btn_pwad_bottom_clicked()
{
    this->setLastPwadHelperTo(false);
}

// refresh pwad list
void MainWindow::on_btn_refresh_clicked()
{
    VlistFill->getPWadList();
}

// iwad item clicked
void MainWindow::on_lw_iwad_itemClicked(QListWidgetItem *item)
{
    VbaseConfig->setLastIwad(item->text().remove(ui->le_iwad->text()));
    Vcolors->clearColor(ui->lw_iwad);
    item->setForeground(Vcolors->getColor());
    item->setSelected(false);

    const QString label = vutil->getLabel();
    ui->btn_start->setText(label);
}

// pwad list changed (i.e. new item added)
void MainWindow::on_lw_pwad_itemChanged(QListWidgetItem *item)
{
    if (item->checkState())
        item->setForeground(Vcolors->getColor());
    else
        item->setForeground(Qt::black);

    this->setLastPwadHelper();
}

// selection of pwad changed, show decription
void MainWindow::on_lw_pwad_itemSelectionChanged()
{
    QListWidgetItem *item = ui->lw_pwad->currentItem();

    if (!item)
        return;

    VdescriptionsHandler->getFullDescriptionFromFile(ui->le_pwad->text() + "/" + item->text());
}

#include "configdialog.h"
#include "ui_configdialog.h"

configDialog::configDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::configDialog)
{
    ui->setupUi(this);
    VbaseConfig = new baseConfig(myUi);
    VlistFill = new listFill(myUi);

    settingsInit();
}

configDialog::~configDialog()
{
    delete ui;
    delete VbaseConfig;
    delete VlistFill;
}

void configDialog::settingsInit()
{
    QString profile = VbaseConfig->getDefaultSettings();

    //hide program instead of closing
    hide = VbaseConfig->getHide(profile);
    if (hide == 1)
        ui->cb_hide->setChecked(true);

    //hide IWAD\PWAD full path
    offPathWad = VbaseConfig->getOffWadPath(profile);
    if (offPathWad == 1)
        ui->cb_hide_iwad_pwad_full_path->setChecked(true);

    //default tab
    default_tab = VbaseConfig->getDefaultTab(profile);
    if (default_tab == 1)
        ui->rb_default_tab_wads->setChecked(true);
    else
        ui->rb_default_tab_profiles->setChecked(true);

    //foreground color
    color = VbaseConfig->getForegroundColor(profile);

    if (color == "Red")
        ui->comb_foreground_color->setCurrentIndex(0);
    else if (color == "Orange")
        ui->comb_foreground_color->setCurrentIndex(1);
    else if (color == "Yellow")
        ui->comb_foreground_color->setCurrentIndex(2);
    else if (color == "Green")
        ui->comb_foreground_color->setCurrentIndex(3);
    else if (color == "Blue")
        ui->comb_foreground_color->setCurrentIndex(4);
    else if (color == "Dark blue")
        ui->comb_foreground_color->setCurrentIndex(5);
    else if (color == "Purple")
        ui->comb_foreground_color->setCurrentIndex(6);
    else if (color == "Black")
        ui->comb_foreground_color->setCurrentIndex(7);
    else if (color.isEmpty())
        ui->comb_foreground_color->setCurrentIndex(7);
}

void configDialog::on_buttonBox_accepted()
{
    QString profile = VbaseConfig->getDefaultSettings();

    if (ui->cb_hide->isChecked())
        VbaseConfig->setHide(profile, 1);
    else
        VbaseConfig->setHide(profile, 0);

    if (ui->cb_hide_iwad_pwad_full_path->isChecked())
        VbaseConfig->setOffWadPath(profile, 1);
    else
        VbaseConfig->setOffWadPath(profile, 0);

    VbaseConfig->setForegroundColor(profile, ui->comb_foreground_color->currentText().remove(" (off)"));

    if (ui->rb_default_tab_profiles->isChecked())
        VbaseConfig->setDefaultTab(profile, 0);
    else
        VbaseConfig->setDefaultTab(profile, 1);
}

void configDialog::on_buttonBox_rejected()
{
    return;
}

void configDialog::on_rb_default_tab_profiles_clicked()
{
    ui->rb_default_tab_wads->setChecked(false);
}

void configDialog::on_rb_default_tab_wads_clicked()
{
    ui->rb_default_tab_profiles->setChecked(false);
}

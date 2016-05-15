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
    if (hide == "true")
        ui->cb_hide->setChecked(true);

    //hide IWAD\PWAD full path
    offPathWad = VbaseConfig->getOffWadPath(profile);
    if (offPathWad == "true")
        ui->cb_hide_iwad_pwad_full_path->setChecked(true);

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
        VbaseConfig->setHide(profile, "true");
    else
        VbaseConfig->setHide(profile, "false");

    if (ui->cb_hide_iwad_pwad_full_path->isChecked())
        VbaseConfig->setOffWadPath(profile, "true");
    else
        VbaseConfig->setOffWadPath(profile, "false");

    VbaseConfig->setForegroundColor(profile, ui->comb_foreground_color->currentText().remove(" (off)"));

    //FIXME
    /*VlistFill->getIWadList();
    VlistFill->getPWadList();
    VlistFill->getProfiles();*/
}

void configDialog::on_buttonBox_rejected()
{
    return;
}

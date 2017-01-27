#include "configdialog.h"
#include "ui_configdialog.h"

configDialog::configDialog(QWidget *parent) :
    QDialog(parent),
    configDialogUi(new Ui::configDialog)
{
    configDialogUi->setupUi(this);
    VbaseConfig = new baseConfig(myUi);
    VlistFill = new listFill(myUi);

    settingsInit();
}

configDialog::~configDialog()
{
    delete configDialogUi;
    /*delete VbaseConfig;
    delete VlistFill;*/
}

void configDialog::settingsInit()
{
    QString profile = VbaseConfig->getLauncherSettingsFile();

    //hide program instead of closing
    hide = VbaseConfig->getHide(profile);
    if (hide == 1)
        configDialogUi->cb_hide->setChecked(true);

    //hide IWAD\PWAD full path
    offPathWad = VbaseConfig->getOffWadPath(profile);
    if (offPathWad == 1)
        configDialogUi->cb_hide_iwad_pwad_full_path->setChecked(true);

    //default tab
    default_tab = VbaseConfig->getDefaultTab(profile);
    if (default_tab == 1)
        configDialogUi->rb_default_tab_wads->setChecked(true);
    else
        configDialogUi->rb_default_tab_profiles->setChecked(true);

    //foreground color
    color = VbaseConfig->getForegroundColor(profile);

    if (color == "Red")
        configDialogUi->comb_foreground_color->setCurrentIndex(0);
    else if (color == "Orange")
        configDialogUi->comb_foreground_color->setCurrentIndex(1);
    else if (color == "Yellow")
        configDialogUi->comb_foreground_color->setCurrentIndex(2);
    else if (color == "Green")
        configDialogUi->comb_foreground_color->setCurrentIndex(3);
    else if (color == "Blue")
        configDialogUi->comb_foreground_color->setCurrentIndex(4);
    else if (color == "Dark blue")
        configDialogUi->comb_foreground_color->setCurrentIndex(5);
    else if (color == "Purple")
        configDialogUi->comb_foreground_color->setCurrentIndex(6);
    else if (color == "Black")
        configDialogUi->comb_foreground_color->setCurrentIndex(7);
    else if (color.isEmpty())
        configDialogUi->comb_foreground_color->setCurrentIndex(7);
}

void configDialog::on_buttonBox_accepted()
{
    QString profile = VbaseConfig->getLauncherSettingsFile();

    if (configDialogUi->cb_hide->isChecked())
        VbaseConfig->setHide(profile, 1);
    else
        VbaseConfig->setHide(profile, 0);

    if (configDialogUi->cb_hide_iwad_pwad_full_path->isChecked())
        VbaseConfig->setOffWadPath(profile, 1);
    else
        VbaseConfig->setOffWadPath(profile, 0);

    VbaseConfig->setForegroundColor(profile, configDialogUi->comb_foreground_color->currentText().remove(" (off)"));

    if (configDialogUi->rb_default_tab_profiles->isChecked())
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
    configDialogUi->rb_default_tab_wads->setChecked(false);
}

void configDialog::on_rb_default_tab_wads_clicked()
{
    configDialogUi->rb_default_tab_profiles->setChecked(false);
}

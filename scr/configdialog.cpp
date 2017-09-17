#include "configdialog.h"
#include "ui_configdialog.h"

config::configDialog::configDialog(QWidget *parent) :
    QDialog(parent),
    configDialogUi(new Ui::configDialog)
{
    configDialogUi->setupUi(this);
    VbaseConfig = new config::baseConfig(myUi);
    VlistFill = new utils::listFill(myUi);

    configDialogUi->comb_foreground_color->setItemData(0, QBrush(Qt::red), Qt::TextColorRole);
    configDialogUi->comb_foreground_color->setItemData(1, QBrush(QColor(255, 160, 0)), Qt::TextColorRole);
    configDialogUi->comb_foreground_color->setItemData(2, QBrush(Qt::yellow), Qt::TextColorRole);
    configDialogUi->comb_foreground_color->setItemData(3, QBrush(QColor(185, 214, 55)), Qt::TextColorRole);
    configDialogUi->comb_foreground_color->setItemData(4, QBrush(Qt::blue), Qt::TextColorRole);
    configDialogUi->comb_foreground_color->setItemData(5, QBrush(Qt::darkBlue), Qt::TextColorRole);
    configDialogUi->comb_foreground_color->setItemData(6, QBrush(QColor(173, 0, 255)), Qt::TextColorRole);

    settingsInit();
}

config::configDialog::~configDialog()
{
    delete configDialogUi;
}

void config::configDialog::settingsInit()
{
    //hide program instead of closing
    hide = VbaseConfig->getHide();
    if (hide == 1)
        configDialogUi->cb_hide->setChecked(true);

    //hide program when game start
    hide_game = VbaseConfig->getHideGame();
    if (hide_game == 1)
        configDialogUi->cb_hide_game->setChecked(true);

    //hide IWAD\PWAD full path
    offPathWad = VbaseConfig->getOffWadPath();
    if (offPathWad == 1)
        configDialogUi->cb_hide_iwad_pwad_full_path->setChecked(true);

    //default tab
    default_tab = VbaseConfig->getDefaultTab();
    if (default_tab == 1)
        configDialogUi->rb_default_tab_wads->setChecked(true);
    else
        configDialogUi->rb_default_tab_profiles->setChecked(true);

    //foreground color
    color = VbaseConfig->getForegroundColor();

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

void config::configDialog::on_buttonBox_accepted()
{
    if (configDialogUi->cb_hide->isChecked())
        VbaseConfig->setHide(1);
    else
        VbaseConfig->setHide(0);

    if (configDialogUi->cb_hide_game->isChecked())
        VbaseConfig->setHideGame(1);
    else
        VbaseConfig->setHideGame(0);

    if (configDialogUi->cb_hide_iwad_pwad_full_path->isChecked())
        VbaseConfig->setOffWadPath(1);
    else
        VbaseConfig->setOffWadPath(0);

    VbaseConfig->setForegroundColor(configDialogUi->comb_foreground_color->currentText().remove(" (off)"));

    if (configDialogUi->rb_default_tab_profiles->isChecked())
        VbaseConfig->setDefaultTab(0);
    else
        VbaseConfig->setDefaultTab(1);

    //VlistFill->getIWadList();
    //VlistFill->getPWadList();
}

void config::configDialog::on_buttonBox_rejected()
{
    return;
}

void config::configDialog::on_rb_default_tab_profiles_clicked()
{
    configDialogUi->rb_default_tab_wads->setChecked(false);
}

void config::configDialog::on_rb_default_tab_wads_clicked()
{
    configDialogUi->rb_default_tab_profiles->setChecked(false);
}

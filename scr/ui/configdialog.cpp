#include "configdialog.h"
#include "ui_configdialog.h"

configDialog::configDialog(QWidget *parent) :
    QDialog(parent),
    cdUi(new Ui::configDialog),
    VbaseConfig(new Utils::baseConfig(ui)),
    VlistFill(new Utils::listFill(ui))
{
    cdUi->setupUi(this);

    settingsInit();
}

configDialog::~configDialog()
{
    delete cdUi;
}

void configDialog::settingsInit()
{
    cdUi->comb_foreground_color->setItemData(0, QBrush(Qt::red), Qt::TextColorRole);
    cdUi->comb_foreground_color->setItemData(1, QBrush(QColor(255, 160, 0)), Qt::TextColorRole);
    cdUi->comb_foreground_color->setItemData(2, QBrush(Qt::yellow), Qt::TextColorRole);
    cdUi->comb_foreground_color->setItemData(3, QBrush(QColor(185, 214, 55)), Qt::TextColorRole);
    cdUi->comb_foreground_color->setItemData(4, QBrush(Qt::blue), Qt::TextColorRole);
    cdUi->comb_foreground_color->setItemData(5, QBrush(Qt::darkBlue), Qt::TextColorRole);
    cdUi->comb_foreground_color->setItemData(6, QBrush(QColor(173, 0, 255)), Qt::TextColorRole);

    //hide program instead of closing
    hide = VbaseConfig->getHide();
    if (hide == 1)
        cdUi->cb_hide->setChecked(true);

    //hide program when game start
    hide_game = VbaseConfig->getHideGame();
    if (hide_game == 1)
        cdUi->cb_hide_game->setChecked(true);

    //hide IWAD\PWAD full path
    offPathWad = VbaseConfig->getOffWadPath();
    if (offPathWad == 1)
        cdUi->cb_hide_iwad_pwad_full_path->setChecked(true);

    //default tab
    default_tab = VbaseConfig->getDefaultTab();
    if (default_tab == 1)
        cdUi->rb_default_tab_wads->setChecked(true);
    else
        cdUi->rb_default_tab_profiles->setChecked(true);

    //foreground color
    color = VbaseConfig->getForegroundColor();

    if (color == "Red")
        cdUi->comb_foreground_color->setCurrentIndex(0);
    else if (color == "Orange")
        cdUi->comb_foreground_color->setCurrentIndex(1);
    else if (color == "Yellow")
        cdUi->comb_foreground_color->setCurrentIndex(2);
    else if (color == "Green")
        cdUi->comb_foreground_color->setCurrentIndex(3);
    else if (color == "Blue")
        cdUi->comb_foreground_color->setCurrentIndex(4);
    else if (color == "Dark blue")
        cdUi->comb_foreground_color->setCurrentIndex(5);
    else if (color == "Purple")
        cdUi->comb_foreground_color->setCurrentIndex(6);
    else if (color == "Black")
        cdUi->comb_foreground_color->setCurrentIndex(7);
    else if (color.isEmpty())
        cdUi->comb_foreground_color->setCurrentIndex(7);
}

void configDialog::on_buttonBox_accepted()
{
    if (cdUi->cb_hide->isChecked())
        VbaseConfig->setHide(1);
    else
        VbaseConfig->setHide(0);

    if (cdUi->cb_hide_game->isChecked())
        VbaseConfig->setHideGame(1);
    else
        VbaseConfig->setHideGame(0);

    if (cdUi->cb_hide_iwad_pwad_full_path->isChecked())
        VbaseConfig->setOffWadPath(1);
    else
        VbaseConfig->setOffWadPath(0);

    VbaseConfig->setForegroundColor(cdUi->comb_foreground_color->currentText().remove(" (off)"));

    if (cdUi->rb_default_tab_profiles->isChecked())
        VbaseConfig->setDefaultTab(0);
    else
        VbaseConfig->setDefaultTab(1);

    //VlistFill->getIWadList();
    //VlistFill->getPWadList();
}

void configDialog::on_buttonBox_rejected()
{
    return;
}

void configDialog::on_rb_default_tab_profiles_clicked()
{
    cdUi->rb_default_tab_wads->setChecked(false);
}

void configDialog::on_rb_default_tab_wads_clicked()
{
    cdUi->rb_default_tab_profiles->setChecked(false);
}

#include "util.h"

utils::util::util(Ui::MainWindow *ui) :
    vbaseconfig(new config::baseConfig(myUi))
{
    this->myUi = ui;
}

utils::util::~util()
{
    delete vbaseconfig;
}

QString utils::util::getPwadChecked()
{
    QVector<QString> files;
    QString str;

    for (auto i = 0; i < myUi->lw_pwad->count(); i++)
    {
        QListWidgetItem *item = myUi->lw_pwad->item(i);

        if (item->checkState())
            files.push_back(item->text().remove(myUi->le_pwad->text())); //instead of using basename function
                                                                         //better to remove path, cuz if file
                                                                         //name will be somethin like wad_name.v1.2.wad
                                                                         //basename will be something like:
                                                                         //2.wad
    }

    for (auto i = 0; i < files.count(); i++)
        str.append(files.at(i) + "#");

    return str;
}

//moving item up and down, http://www.qtcentre.org/threads/17996-Move-items-up-and-down-in-QListWidget
void utils::util::moveItem(bool backward)
{
    int in = 0;

    QListWidgetItem *current = myUi->lw_pwad->currentItem();
    int currIndex = myUi->lw_pwad->row(current);

    if (backward)
        in = currIndex - 1;
    else
        in = currIndex + 1;

    QListWidgetItem *item = myUi->lw_pwad->item(in);
    int index = myUi->lw_pwad->row(item);

    QListWidgetItem *temp = myUi->lw_pwad->takeItem(index);

    if (backward)
    {
        myUi->lw_pwad->insertItem(index, current);
        myUi->lw_pwad->insertItem(currIndex, temp);
    }
    else
    {
        myUi->lw_pwad->insertItem(currIndex, temp);
        myUi->lw_pwad->insertItem(index, current);
    }
}

void utils::util::moveItemTo(bool top)
{
    QListWidgetItem *current = myUi->lw_pwad->currentItem();

    if (current->checkState() == Qt::Unchecked)
        return;

    QString str = vbaseconfig->getLastPwad();
    QStringList pwad_list = str.split("#");

    int index = myUi->lw_pwad->row(current);

    if (pwad_list.length() - 1 == index) // item in bottom
        return;

    myUi->lw_pwad->takeItem(index);

    if (top)
        myUi->lw_pwad->insertItem(0, current);
    else
        myUi->lw_pwad->insertItem(pwad_list.length() - 2, current); // i dunno why this is working, srsly    
}

QString utils::util::getLabel()
{
    QVector<QString> label_vec;
    label_vec << "RIP AND TEAR!" << "JOIN GAME AND RIP THEM ALL!" << "RIP UND TEAR!" <<\
             "GIVE ME YOUR SOUL!" << "THE TREND IS DEAD!";

    QString label = "";

    if (myUi->gb_join->isChecked())
    {
        label = label_vec.at(1);
        return label;
    }

    QString item_text = vbaseconfig->getLastIwad().remove(myUi->le_iwad->text());

    if (item_text.contains("doom", Qt::CaseInsensitive))
        label = label_vec.at(0);
    else if (item_text.contains("wolf", Qt::CaseInsensitive))
        label = label_vec.at(2);
    else if (item_text.contains("heretic", Qt::CaseInsensitive) || item_text.contains("hexen", Qt::CaseInsensitive))
        label = label_vec.at(3);
    else
        label = label_vec.at(4);

    return label;
}

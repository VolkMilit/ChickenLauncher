#include "util.h"
#include <QDebug>

utils::util::util(Ui::MainWindow *ui) :
    vbaseconfig(new baseConfig(myUi))
{
    this->myUi = ui;
}

utils::util::~util()
{
    delete vbaseconfig;
}

QString utils::util::getPwadChecked()
{
    const bool offWadPath = vbaseconfig->getOffWadPath();
    QVector<QString> files;
    QString str;

    for (auto i = 0; i < myUi->lw_pwad->count(); i++)
    {
        QListWidgetItem *item = myUi->lw_pwad->item(i);

        if (item->checkState())
        {
            if (offWadPath)
                files.push_back(item->text().remove(myUi->le_pwad->text())); //instead of using basename function
                                                                         //better to remove path, cuz if file
                                                                         //name will be somethin like wad_name.v1.2.wad
                                                                         //basename will be something like:
                                                                         //2.wad
            else
                files.push_back(item->text());
        }
    }

    for (auto i = 0; i < files.count(); i++)
        str.append(files.at(i) + "#");

    return str;
}

//moving item up and down, http://www.qtcentre.org/threads/17996-Move-items-up-and-down-in-QListWidget
void utils::util::moveItem(bool backward, QListWidget *widget)
{
    int in = 0;

    QListWidgetItem *current = widget->currentItem();
    int currIndex = widget->row(current);

    if (backward)
        in = currIndex - 1;
    else
        in = currIndex + 1;

    QListWidgetItem *item = widget->item(in);
    int index = widget->row(item);

    QListWidgetItem *temp = widget->takeItem(index);

    if (backward)
    {
        widget->insertItem(index, current);
        widget->insertItem(currIndex, temp);
    }
    else
    {
        widget->insertItem(currIndex, temp);
        widget->insertItem(index, current);
    }    
}

void utils::util::moveItemTo(bool top, QListWidget *widget)
{
    QListWidgetItem *current = widget->currentItem();

    if (current->checkState() == Qt::Unchecked)
        return;

    QString str = vbaseconfig->getLastPwad();
    QStringList pwad_list = str.split("#");

    int index = widget->row(current);

    if (pwad_list.length() - 1 == index) // item in bottom
        return;

    widget->takeItem(index);

    if (top)
        widget->insertItem(0, current);
    else
        widget->insertItem(pwad_list.length() - 2, current); // i dunno why this is working, srsly
}

QString utils::util::getLabel()
{
    QVector<QString> label_vec;
    label_vec << "RIP AND TEAR!" << "JOIN GAME AND RIP 'EM ALL!" << "RIP UND TEAR!" <<\
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
    else if (item_text.contains("heretic", Qt::CaseInsensitive))
        label = label_vec.at(3);
    else if (item_text.contains("hexen", Qt::CaseInsensitive))
        label = label_vec.at(3);
    else
        label = label_vec.at(4);

    return label;
}

QString utils::util::getMauntsFromFile(QString f)
{
    QFile file("/home/volk/.config/ChickenLauncher/mounts");
    QString ret = "";

    if (file.open(QIODevice::ReadOnly |QIODevice::Text))
    {
        while (!file.atEnd())
        {
            QString str = file.readLine();
            QStringList tmp = str.split(":");

            if (tmp.at(0).contains(f, Qt::CaseInsensitive))
            {
                ret = tmp.at(1);
                break;
            }
        }
    }

    return ret;
}

#include "colors.h"

colors::colors(Ui::MainWindow *ui)
{
    this->myUi = ui;
    VbaseConfig = new baseConfig(ui);
}

colors::~colors()
{
    //delete VbaseConfig;
    //delete myUi;
}

QColor colors::getColor()
{
    QColor ret;

    color = VbaseConfig->getForegroundColor(VbaseConfig->getLauncherSettingsFile());

    if (color == "Red")
        ret = Qt::red;
    else if (color == "Orange")
        ret = QColor(255, 160, 0);
    else if (color == "Yellow")
        ret = Qt::yellow;
    else if (color == "Green")
        ret = QColor(185, 214, 55);
    else if (color == "Blue")
        ret = Qt::blue;
    else if (color == "Dark blue")
        ret = Qt::darkBlue;
    else if (color == "Purple")
        ret = QColor(173, 0, 255);
    else if (color.isEmpty() || color == "Black")
        ret = Qt::black;

    return ret;
}

void colors::clearColor(QListWidget *widget)
{
    for (int i = 0; i < widget->count(); i++)
        widget->item(i)->setForeground(Qt::black);
}

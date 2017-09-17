#include "colors.h"

utils::colors::colors()
{
    ui = new Ui::MainWindow;
    VbaseConfig = new config::baseConfig(ui);
}

utils::colors::~colors(){}

QColor utils::colors::getColor()
{
    QColor ret;

    QString color = VbaseConfig->getForegroundColor();

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

void utils::colors::clearColor(QListWidget *widget)
{
    for (int i = 0; i < widget->count(); i++)
        widget->item(i)->setForeground(Qt::black);
}

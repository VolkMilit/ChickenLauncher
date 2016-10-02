#include "mainwindow.h"

// Qt 4 headers
//#include <QApplication>

// Qt 5 headers
#include <QtGui>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

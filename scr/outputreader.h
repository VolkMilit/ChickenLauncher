#ifndef OUTPUTREADER_H
#define OUTPUTREADER_H

#include <QObject>
#include <QFile>
#include <QTextStream>

#include "ui_mainwindow.h"

class outputReader : public QObject
{
    Q_OBJECT

public:
    outputReader(Ui::MainWindow *ui);
    virtual ~outputReader();

signals:
    void finished();
    void error(QString err);

public slots:
    void run();
    void cleanup();
    void errorString(QString string);

private:
    Ui::MainWindow *myUi;
    //QFile file;
};

#endif // OUTPUTREADER_H

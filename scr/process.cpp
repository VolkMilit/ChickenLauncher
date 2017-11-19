#include "process.h"
#include <QDebug>

/*utils::process::process(QObject *parent = 0) : QObject(parent)
{
    proc = new QProcess(parent);
}

utils::process::~process()
{
    delete proc;
}

void utils::process::start(QString program, QStringList arguments)
{
    proc->start(program, arguments);

    QObject::connect(&proc, SIGNAL(readyReadStandardOutput()), this, SLOT(readyReadStandardOutput()));
    QObject::connect(&proc, SIGNAL(readyReadStandardError()), this, SLOT(readyReadStandardError()));
}

void utils::process::readyReadStandardError()
{
    qDebug() << proc->readAllStandardOutput();
}

void utils::process::readyReadStandardOutput()
{
    qDebug() << proc->readAllStandardError();
}*/

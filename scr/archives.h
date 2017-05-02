#ifndef ARCHIVES_H
#define ARCHIVES_H

#include <QString>
#include <quazip/quazipfile.h>

class archives
{
public:
    archives();
    virtual ~archives();

    int open(QString archivePath, QString file);
    QString returnText();

private:
    QString str;
};

#endif // ARCHIVES_H

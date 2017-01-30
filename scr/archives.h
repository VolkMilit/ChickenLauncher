#ifndef ARCHIVES_H
#define ARCHIVES_H

#include <QString>
#include <libzppp/libzippp.h>

class archives
{
public:
    archives();
    virtual ~archives();

    void open(QString archivePath, QString file);
    QString returnText();

private:
    QString str;
};

#endif // ARCHIVES_H

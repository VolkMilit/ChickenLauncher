#include "archives.h"

utils::archives::archives(){}
utils::archives::~archives(){}

QString utils::archives::findTxt(QString file)
{
    QString found = "";

    QStringList lfiles;
    QuaZip archive(file);
    archive.open(QuaZip::mdUnzip);

    if (archive.isOpen())
    {
        lfiles = archive.getFileNameList();
        found = lfiles.filter("txt").at(0);
    }

    archive.close();

    return found;
}

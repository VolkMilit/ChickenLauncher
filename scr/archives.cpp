#include "archives.h"

archives::archives(){}
archives::~archives(){}

void archives::open(QString archivePath, QString file)
{
    libzippp::ZipArchive zf(archivePath.toStdString());
    zf.open(libzippp::ZipArchive::READ_ONLY);

    libzippp::ZipEntry entry = zf.getEntry(file.toStdString());
    str = QString::fromUtf8(entry.readAsText().c_str());

    zf.close();
}

QString archives::returnText()
{
    return str;
}

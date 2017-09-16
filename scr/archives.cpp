#include "archives.h"

archives::archives(){}
archives::~archives(){}

int archives::open(QString archivePath, QString file)
{
    QFile infile(archivePath);
    QFile outfile(file);
    infile.open(QIODevice::ReadOnly);
    outfile.open(QIODevice::WriteOnly);
    QByteArray uncompressed_data = infile.readAll();
    QByteArray compressed_data = qUncompress(uncompressed_data);
    outfile.write(compressed_data);
    infile.close();
    outfile.close();
}

QString archives::returnText()
{
    return str;
}

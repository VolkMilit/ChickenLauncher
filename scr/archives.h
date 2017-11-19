#ifndef ARCHIVES_H
#define ARCHIVES_H

#include <QString>
#include <quazip/quazipfile.h>

namespace utils
{
    class archives
    {
        protected:
        archives();
        virtual ~archives();

        QString findTxt(QString file);
    };
}

#endif // ARCHIVES_H

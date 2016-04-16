#include "functions.h"
#include <QMessageBox>

functions::functions()
{
}

bool functions::isNT()
{
    /*
     * QT 4.8 support QSysInfo class, but this one don't return operation system =/
     */
    #ifdef Q_OS_WIN32
        return true;
    #endif

    return false;
}

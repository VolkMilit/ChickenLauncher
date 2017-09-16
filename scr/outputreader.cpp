#include "outputreader.h"
#include <QDebug>

outputReader::outputReader(Ui::MainWindow *ui){}
outputReader::~outputReader(){}

void outputReader::run()
{
    QFile file("/tmp/brutal.txt");

    /*if (file.exists())
        file.remove();*/

    /*if(!file.open(QIODevice::ReadOnly))
        return;
    else
    {*/
        QTextStream in(&file);

        while(!in.atEnd())
        {
            QString line = in.readLine();
            //myUi->teb_proc_output->append(line);
            qDebug() << line;
        }
    //}

    emit finished();

    file.close();
}

void outputReader::cleanup()
{

}

void outputReader::errorString(QString string)
{
    qDebug() << "Твой код говно)))00000)): " + string;
}

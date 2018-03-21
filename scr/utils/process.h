#ifndef PROCESS_H
#define PROCESS_H

#include <QObject>
#include <QProcess>

/*namespace utils
{
    class process : public QObject
    {
        Q_OBJECT

        private:
            QProcess *proc;

        protected:
            process(QObject *parent = 0);
            virtual ~process();

            void start(QString program, QStringList arguments);

        private slots:
            void readyReadStandardOutput();
            void readyReadStandardError();
    };
}*/

#endif // PROCESS_H

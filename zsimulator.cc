#include <iostream>

#include <QString>
#include <QStringList>
#include <QDir>
#include <QDebug>
#include <QElapsedTimer>
#include <QCoreApplication>
#include <QProcess>

QString vision_prog("bin/zvision");
QString comm_prog("bin/zcommunication");
QStringList vision_args(QString("nothing"));
QStringList comm_args(QString("nothing"));

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
	
	QElapsedTimer timer;
	timer.start();

    QProcess* pvision = new QProcess();
    pvision->start(vision_prog);

    // QProcess* pcomm = new QProcess();
    // pcomm->start(comm_prog);

    pvision->waitForFinished();
    // pcomm->waitForFinished();

    delete pvision;
    // delete pcomm;

    qDebug() << "timer" << timer.elapsed()/1000.0 << "seconds";

    return 1;
}

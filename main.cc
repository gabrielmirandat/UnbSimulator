#include <iostream>
#include "Controller.h"

#include <QString>
#include <QStringList>
#include <QDir>
#include <QDebug>
#include <QElapsedTimer>
#include <QCoreApplication>

QString vision_prog("bin/avision");
QString comm_prog("bin/acommunication");
QStringList vision_args(QString("nothing"));
QStringList comm_args(QString("nothing"));

int main(int argc, char *argv[])
{
    QDir::setCurrent("/home/gabriel/Dropbox/5.Recente/Desktop/BOOST_THREADS/simulator_process");
    QCoreApplication a(argc, argv);
	
	QElapsedTimer timer;
	timer.start();
	
    Controller comm_control(comm_prog, comm_args);
    Controller vision_control(vision_prog, vision_args);
    
    emit comm_control.operate();
    emit vision_control.operate();
    
    qDebug() << "timer" << timer.elapsed()/1000.0 << "seconds";

    return 1;
}

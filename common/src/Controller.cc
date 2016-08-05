#include "Controller.h"

Controller::Controller(const QString &program, const QStringList &argList)
{
	worker_ = new Worker(program, argList);
    worker_->moveToThread(&workerThread_);
        
    connect(&workerThread_, &QThread::finished, worker_, &QObject::deleteLater);
    connect(this, &Controller::operate, worker_, &Worker::doWork);
    connect(worker_, &Worker::resultReady, this, &Controller::handleResults);
        
    workerThread_.start();
}

Controller::~Controller()
{
	workerThread_.quit();
    workerThread_.wait();
}

//public slot
void Controller::handleResults(const QString &results)
{
	//add what to do here
}

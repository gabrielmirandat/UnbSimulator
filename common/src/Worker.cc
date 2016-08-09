#include "Worker.h"

Worker::Worker(const QString &program, const QStringList &argList)
: program_(program), argList_(argList)
{
    launcher_ = new Launcher(this);
}

Worker::~Worker()
{
    delete launcher_;
}

//public slot
void Worker::doWork()
{
    QString result;
    this->launcher_->launch(this->program_, this->argList_);

    result = "Deu";
    emit resultReady(result);
}

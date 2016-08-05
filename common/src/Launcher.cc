#include "Launcher.h"
#include <QtDebug>

Launcher::Launcher(QObject* parent)
: QObject(parent), started_(false)
{
    process_ = new QProcess(this);
    //process_->setProcessChannelMode(QProcess::MergedChannels);

    connect(process_,
            SIGNAL(error(QProcess::ProcessError)),
            SLOT(error(QProcess::ProcessError)));
    connect(process_,
            SIGNAL(finished(int, QProcess::ExitStatus)),
            SLOT(finished(int, QProcess::ExitStatus)));
    connect(process_,
            SIGNAL(stateChanged(QProcess::ProcessState)),
            SLOT(stateChanged(QProcess::ProcessState)));
    connect(this,
            SIGNAL(feedbackLog(QString)),
            SLOT(printLog(QString)));
} // end_ctor(ExternalLauncher)

Launcher::~Launcher()
{
    if (started_ && process_->state() != QProcess::NotRunning)
        process_->kill();
}// end_dtor(Launcher)

void Launcher::launch(QString program, QStringList argList)
{
    qDebug() << "Launcher::launch";
    started_ = true;
    process_->start(program, argList);
    process_->waitForStarted(-1);
    qDebug() << (int) process_->pid();
    process_->waitForFinished(-1); // (c)
    //Q_EMIT feedbackLog(process_->readAllStandardOutput());
    process_->close();
} // end Launcher::launch()

void Launcher::error(QProcess::ProcessError error)
{
    qDebug() << "Launcher::error" << error;
} // end_slot(Launcher::error)

void Launcher::finished(int exitCode, QProcess::ExitStatus status)
{
    started_ = false;
    qDebug() << "Launcher::finished" << exitCode << status;
} // end_slot (Launcher::finished)

void Launcher::stateChanged(QProcess::ProcessState state)
{
    qDebug() << "Launcher::stateChanged" << state;
}

void Launcher::printLog(QString log)
{
    qDebug() << log;
}

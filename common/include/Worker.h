#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QProcess>
#include <QDebug>
#include "Launcher.h"

class Worker : public QObject
{
    Q_OBJECT

private:
    Launcher* launcher_;
	QString program_; 
	QStringList argList_;

public:
    Worker(const QString &program, const QStringList &argList);
    ~Worker();

signals:
    void resultReady(const QString &result);

public slots:
    void doWork();
};

#endif // WORKER_H

#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <iostream>
#include <QObject>
#include <QProcess>
#include <QString>
#include <QStringList>
#include <QDebug>

class Launcher : public QObject
{
    Q_OBJECT

private:
    QProcess* process_;
    bool started_;

private slots:
    void error(QProcess::ProcessError error);
    void finished(int exitCode, QProcess::ExitStatus status);
    void stateChanged(QProcess::ProcessState state);

public:
    explicit Launcher(QObject *parent = 0);
    virtual ~Launcher();
    
signals:
    void feedbackLog(QString log);

public slots:
    void launch(QString program, QStringList argList);
    void printLog(QString log);
};

#endif // LAUNCHER_H

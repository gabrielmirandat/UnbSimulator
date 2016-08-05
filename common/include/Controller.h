#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include "Worker.h"

class Controller : public QObject
{
    Q_OBJECT

private:
    QThread workerThread_;
    Worker* worker_;
    
public:
    Controller(const QString &program, const QStringList &argList);
    ~Controller();

signals:
    void operate();

public slots:
    void handleResults(const QString &);
};

#endif // CONTROLLER_H

#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_

#include <iostream>
#include <QThread>

//for shared access
#include <QSharedMemory>
#include <QBuffer>
#include <QDataStream>
#include <QFile>
#include <QTextStream>
#include "../common/data/visionData.h"

class Communication
{
private:
	int comm_counter;

    //for shared access
    QSharedMemory vision_shm;
    visionData vision_data;
    QBuffer buffer;
    QDataStream in;

    //singletone constructor
    explicit Communication();
    static Communication* instance;

    void listen();
    void receive();
    void send();
    void run();

    //for shared access
    void updateData();
    void updateBuffer();
    void getFromSharedMem();

    //for log file
    QFile out_file_;
    QTextStream out_stream_;

public:
	virtual ~Communication();
    static Communication* getInstance();
};

#endif //COMMUNICATION_H_

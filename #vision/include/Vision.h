
#ifndef VISION_H_
#define VISION_H_

#include <iostream>
#include <opencv2/core/core.hpp>
#include <QThread>
#include <QDebug>

//for shared access
#include <QSharedMemory>
#include <QBuffer>
#include <QDataStream>
#include <QFile>
#include <QTextStream>

#include "visionData.h"

class Vision  : public QThread
{

private:
	int vision_counter;
    cv::Point ball_position, goal_position, center_position;
	int bi, gi, ci;

    //singletone constructor
    explicit Vision();
    static Vision* instance;

    //for log file
    QFile out_file_;
    QTextStream out_stream_;

    //shared memory
    visionData write_vision_data_;
    visionData read_vision_data_;
    QSharedMemory shared_memory_;

    void ball();
    void goal();
    void center();
    void run();

    //for shared access
    void updateData();
    void sendData();
    void loadData();

public:
    virtual ~Vision();
    static Vision* getInstance();
};

#endif //VISION_H_

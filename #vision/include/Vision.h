
#ifndef VISION_H_
#define VISION_H_

#include <iostream>
#include <opencv2/core/core.hpp>
#include <QThread>

//for shared access
#include <QSharedMemory>
#include <QBuffer>
#include <QDataStream>
#include "../common/data/visionData.h"

class Vision
{

private:
	int vision_counter;
	// cv::Point ball_position, goal_position, center_position;
    int ball_position, goal_position, center_position;
	int bi, gi, ci;

    //for shared access
    QSharedMemory vision_shm;
    visionData vision_data;
    QBuffer buffer;
    QDataStream out;

    //singletone constructor
    explicit Vision();
    static Vision* instance;

    void ball();
    void goal();
    void center();
    void run();

    //for shared access
    void updateData();
    void updateBuffer();
    void sendToSharedMem();

public:
    virtual ~Vision();
    static Vision* getInstance();
};

#endif //VISION_H_

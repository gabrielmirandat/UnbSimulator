#include "Vision.h"

Vision::Vision()
:vision_counter(0), ball_position(-1,-1), goal_position(-1,-1), center_position(-1,-1),
out_file_("process_output/output_vision.txt")
{
    //three seconds to configure tail file output_vision.txt
    QThread::msleep(3000);

    if (out_file_.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        out_stream_.setDevice(&out_file_);
        out_stream_ << "vision file created" << "\n"; out_stream_.flush();

        run();
    }
    else
    {
        std::cout << "error creating vision file" << std::endl;
    }
}

Vision* Vision::instance = NULL;

Vision* Vision::getInstance() 
{
    if(!instance) {
        instance = new Vision();
    }
    return instance;
}

Vision::~Vision()
{
    delete this->instance;
}

void Vision::ball()
{
    this->bi = (++this->bi%4 == 0) ? this->bi : -1;
    this->ball_position = cv::Point(this->bi,this->bi);

    out_stream_ << "	vision::ball" << "\n"; out_stream_.flush();
}

void Vision::goal()
{
    this->gi = (++this->gi%7 == 0) ? this->gi : -1;
    this->goal_position = cv::Point(this->gi,this->gi);

    out_stream_ << "	vision::goal" << "\n"; out_stream_.flush();
}

void Vision::center()
{
    this->ci = (++this->ci%5 == 0) ? this->ci : -1;
    this->center_position = cv::Point(this->ci,this->ci);

    out_stream_ << "	vision::center" << "\n"; out_stream_.flush();
}

void Vision::updateData()
{
    this->vision_data.ball_position =this->ball_position.x;
    this->vision_data.goal_position =this->goal_position.x;
    this->vision_data.center_position =this->center_position.x;
}

void Vision::run()
{
    for(this->vision_counter=0;this->vision_counter<100;this->vision_counter++)
    {
        ball();
        if(this->vision_counter%4==0) goal();
        if(this->vision_counter%11==0) center();
        QThread::msleep(60);
    }
    
    out_stream_ << "end of process" << "\n"; out_stream_.flush();
}

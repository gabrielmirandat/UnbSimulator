#include "Vision.h"

Vision::Vision()
// :vision_counter(0), ball_position(-1,-1), goal_position(-1,-1), center_position(-1,-1), vision_shm("visionBoard")
:vision_counter(0), ball_position(-1), goal_position(-1), center_position(-1), vision_shm("visionBoard"),
out_file_("../process_output/output_vision.txt")
{
    //three seconds to configure tail file output_vision.txt
    QThread::msleep(3000);

    if (out_file_.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        out_stream_.setDevice(&out_file_);
        out_stream_ << "vision file created" << "\n"; out_stream_.flush();


        //force sharedMemory to not already be attached
        if(vision_shm.isAttached())
           vision_shm.detach();

        buffer.open(QBuffer::ReadWrite);
        out.setDevice(&buffer);
        updateBuffer();

        if (!vision_shm.create(buffer.size()))
        {
           out_stream_ << "could not create vision_shm" << "\n"; out_stream_.flush();

        }else
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
    vision_shm.deleteLater();
    delete this->instance;
}

void Vision::ball()
{
    this->bi = (++this->bi%4 == 0) ? this->bi : -1;
    // this->ball_position = cv::Point(this->bi,this->bi);
    this->ball_position = this->bi;
    sendToSharedMem();

    out_stream_ << "	vision::ball" << "\n"; out_stream_.flush();
}

void Vision::goal()
{
    this->gi = (++this->gi%7 == 0) ? this->gi : -1;
    // this->goal_position = cv::Point(this->gi,this->gi);
    this->goal_position = this->gi;
    sendToSharedMem();

    out_stream_ << "	vision::goal" << "\n"; out_stream_.flush();
}

void Vision::center()
{
    this->ci = (++this->ci%5 == 0) ? this->ci : -1;
    // this->center_position = cv::Point(this->ci,this->ci);
    this->center_position = this->ci;
    sendToSharedMem();

    out_stream_ << "	vision::center" << "\n"; out_stream_.flush();
}

void Vision::updateData()
{
    this->vision_data.ball_position =this->ball_position;
    this->vision_data.goal_position =this->goal_position;
    this->vision_data.center_position =this->center_position;
}

void Vision::updateBuffer()
{
    updateData();
    out << vision_data.ball_position;
    out << vision_data.goal_position;
    out << vision_data.center_position;
}

void Vision::sendToSharedMem()
{
    // Send data to buffer
    updateBuffer();
    // Write into the shared memory
    vision_shm.lock();
    char *to = (char*) vision_shm.data();
    const char *from = buffer.data().data();
    memcpy( to, from, qMin(vision_shm.size(), (int) buffer.size() ) );
    vision_shm.unlock();
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
}

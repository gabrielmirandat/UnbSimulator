#include "Vision.h"

Vision::Vision()
:vision_counter(0), ball_position(-1,-1), goal_position(-1,-1), center_position(-1,-1),
out_file_("process_output/output_vision.txt"), shared_memory_("Qshared_memory_Example")
{
    //three seconds to configure tail file output_vision.txt
    qDebug() << "Waiting 3 secs.";
    QThread::msleep(3000);

    if (out_file_.open(QIODevice::WriteOnly | QIODevice::Text))
        out_stream_.setDevice(&out_file_);
    else
    {
        qDebug() << "Could not open output file.";
        return;
    }

    if (shared_memory_.isAttached())
    {
        qDebug() << "Memory already attached.";
        shared_memory_.detach();
    }

    if (!shared_memory_.create(sizeof(write_vision_data_)))
    {
        qDebug() << shared_memory_.errorString();
        return;
    }


    out_stream_ << "vision file created" << "\n"; out_stream_.flush();
    run();
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
    if(shared_memory_.detach())
        qDebug() << "Memory detashed.";
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
    this->write_vision_data_.ball_position      =this->ball_position.x;
    this->write_vision_data_.goal_position      =this->goal_position.x;
    this->write_vision_data_.center_position    =this->center_position.x;
}

void Vision::sendData()
{
    //load into shared memory
    QBuffer buffer;
    buffer.open(QBuffer::ReadWrite);
    QDataStream out(&buffer);

    out << this->write_vision_data_.ball_position;
    out << this->write_vision_data_.center_position;
    out << this->write_vision_data_.goal_position;

    int size = buffer.size();

    // send to shared memory
    shared_memory_.lock();
    char *to = (char*) shared_memory_.data();
    const char *from = buffer.data().data();
    memcpy(to, from, qMin(shared_memory_.size(), size));
    shared_memory_.unlock();
}

void Vision::loadData()
{
    QBuffer buffer;
    QDataStream in(&buffer);

    shared_memory_.lock();
    buffer.setData((char*) shared_memory_.constData(), shared_memory_.size());
    buffer.open(QBuffer::ReadOnly);

    in >> read_vision_data_.ball_position;
    in >> read_vision_data_.center_position;
    in >> read_vision_data_.goal_position;

    shared_memory_.unlock();

    out_stream_ << "\n"; out_stream_.flush();
    out_stream_ << "LOADED DATA:" << "\n"; out_stream_.flush();
    out_stream_ << "ball_position: " << read_vision_data_.ball_position << "\n"; out_stream_.flush();
    out_stream_ << "goal_position: " << read_vision_data_.goal_position << "\n"; out_stream_.flush();
    out_stream_ << "center_position: " << read_vision_data_.center_position << "\n"; out_stream_.flush();
    out_stream_ << "\n"; out_stream_.flush();
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
    qDebug() << "END";
}

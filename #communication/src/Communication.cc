#include "Communication.h"

Communication::Communication()
:comm_counter(0), vision_shm("visionBoard"),
out_file_("../process_output/output_comm.txt")
{
    //three seconds to configure tail file output_comm.txt
    QThread::msleep(3000);

    if (out_file_.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        out_stream_.setDevice(&out_file_);
        out_stream_ << "communication file created" << "\n"; out_stream_.flush();

        //wait vision begin for sharedMemory access
        QThread::msleep(60);

        if (!vision_shm.attach())
        {
            out_stream_ << "could not create vision_shm" << "\n"; out_stream_.flush();
        }else
        {
            run();
        }

    }
    else
    {
        std::cout << "error creating communication file" << std::endl;
    }
}

Communication* Communication::instance = NULL;

Communication* Communication::getInstance() 
{
    if(!instance) {
        instance = new Communication();
    }
    return instance;
}

Communication::~Communication()
{
    delete this->instance;
}

void Communication::listen()
{
    out_stream_ << "          communication::listen" << "\n"; out_stream_.flush();
}

void Communication::receive()
{
    out_stream_ << "          communication::receive" << "\n"; out_stream_.flush();
}

void Communication::send()
{
    getFromSharedMem();
    out_stream_ << "          communication::send" << "\n"; out_stream_.flush();
}

void Communication::updateData()
{
    buffer.open(QIODevice::ReadOnly);
    in.setDevice(&buffer);
    in >> vision_data.ball_position;
    in >> vision_data.goal_position;
    in >> vision_data.center_position;
    buffer.close();
}

void Communication::updateBuffer()
{
    vision_shm.lock();
    buffer.setData((char*) vision_shm.constData(), vision_shm.size());
    vision_shm.unlock();
}

void Communication::getFromSharedMem()
{
    // Send data to buffer
    updateBuffer();
    // read into local visionData
    updateData();
}

void Communication::run()
{
    for(this->comm_counter=0;this->comm_counter<100;this->comm_counter++)
    {
        listen();
        if(this->comm_counter%5==0) receive();
        if(this->comm_counter%7==0) send();
        QThread::msleep(60);
    }
    out_stream_ << "end of process" << "\n"; out_stream_.flush();
}

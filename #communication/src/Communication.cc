#include "Communication.h"

Communication::Communication()
:comm_counter(0), vision_shm("visionBoard")
{
    //five seconds to configure tail file output_comm.txt
    QThread::msleep(3000);

    //wait vision begin for sharedMemory access
    QThread::msleep(60);

    if (!vision_shm.attach())
    {
        std::cout << "Could not create vision_shm" << std::endl;
    }else
    {
        run();
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
    std::cout << "          Communication::listen" << std::endl;
}

void Communication::receive()
{
    std::cout << "          Communication::receive" << std::endl;
}

void Communication::send()
{
    getFromSharedMem();
    std::cout << "          Communication::send" << std::endl;
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
}

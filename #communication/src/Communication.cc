#include "Communication.h"

Communication::Communication()
:comm_counter(0),
out_file_("process_output/output_comm.txt")
{
    //three seconds to configure tail file output_comm.txt
    QThread::msleep(3000);

    if (out_file_.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        out_stream_.setDevice(&out_file_);
        out_stream_ << "communication file created" << "\n"; out_stream_.flush();
        
        run();

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
    out_stream_ << "          communication::send" << "\n"; out_stream_.flush();
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

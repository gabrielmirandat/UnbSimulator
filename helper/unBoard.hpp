//Boost.Interprocess allows multiple processes to use shared memory concurrently. Because shared memory is, by 
//definition, shared between processes, Boost.Interprocess needs to support some kind of synchronization.

//Thinking about synchronization, classes from the C++11 standard library or Boost.Thread come to mind. But these 
//classes can only be used to synchronize threads within the same process; they do not support synchronization of 
//different processes. 

//While synchronization objects such as mutexes and condition variables reside in the same address space in 
//multithreaded applications, and therefore are available to all threads, the challenge with shared memory is 
//that independent processes need to share these objects.

#ifndef _UNBOARD_HPP_
#define _UNBOARD_HPP_

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>

using namespace boost::interprocess;

template < class T >

class unBoard
{
	T* data;
	managed_shared_memory managed_shm;
	named_mutex mtx;

public:
	unBoard()//:managed_shm(open_or_create, "unBoard", 1048576 /*1MB*/), mtx(open_or_create, typeid(T).name())
	{
		shared_memory_object::remove("unBoard");
		
		managed_shm(open_or_create, "unBoard", 1048576 /*1MB*/);
		mtx(open_or_create, typeid(T).name());
		
		data = managed_shm.find_or_construct<T>(typeid(T).name())();
        mtx.unlock();
	}
    
    ~unBoard()
    {
        mtx.remove(typeid(T).name());
        //delete object in shared memory
        managed_shm.destroy<T>(typeid(T).name());
        //just to check if was correctly deleted
        std::pair<T*, std::size_t> p = managed_shm.find<T>(typeid(T).name());
  		std::cout << p.first << '\n'; //
    }

	void save(T teste)
	{
		mtx.lock();
		*data = teste;
		mtx.unlock();
	}

	T load()
	{
		return *data;
	}

};
/*
* g++ -c -Wall teste.cpp -lpthread
* g++ -L /lib -lpthread teste.o -o teste -lrt -lpthread
*/
#endif

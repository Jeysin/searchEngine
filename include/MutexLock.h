#ifndef __MUTEXLOCK_H__
#define __MUTEXLOCK_H__

#include"Noncopyable.h"
#include<pthread.h>

namespace jjx
{
class MutexLock : private Noncopyable
{
public:
	MutexLock();
	~MutexLock();
	void lock();
	void unlock();
	bool isLock();
	pthread_mutex_t * getMutex();
private:
	bool _isLock;
	pthread_mutex_t _mutex;
};	
}//end of namespace jjx

#endif

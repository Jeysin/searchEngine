#ifndef __CONDITION_H__
#define __CONDITION_H__

#include"Noncopyable.h"
#include<pthread.h>

namespace jjx
{
class MutexLock;
class Condition : private Noncopyable
{
public:
	Condition(MutexLock &mutexlock);
	~Condition();
	void wait();
	void notify();
	void notifyAll();
private:
	pthread_cond_t _cond;
	pthread_mutex_t *_pmutex; 
};
}//end of namespace jjx

#endif

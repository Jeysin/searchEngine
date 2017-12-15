#include"../include/MutexLock.h"
#include"../include/Condition.h"

namespace jjx
{
Condition::Condition(MutexLock &mutexlock)
: _pmutex(mutexlock.getMutex())
{
	pthread_cond_init(&_cond, NULL);
}
Condition::~Condition()
{
	pthread_cond_destroy(&_cond);
}
void Condition::wait()
{
	pthread_cond_wait(&_cond, _pmutex);
}
void Condition::notify()
{
	pthread_cond_signal(&_cond);
}
void Condition::notifyAll()
{
	pthread_cond_broadcast(&_cond);
}
}//end of namespace jjx

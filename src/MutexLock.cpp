#include"../include/MutexLock.h"

namespace jjx
{
MutexLock::MutexLock()
: _isLock(false)
{
	pthread_mutex_init(&_mutex, NULL);
}
MutexLock::~MutexLock()
{
	pthread_mutex_destroy(&_mutex);
}
void MutexLock::lock()
{
	_isLock=true;
	pthread_mutex_lock(&_mutex);
}
void MutexLock::unlock()
{
	pthread_mutex_unlock(&_mutex);
	_isLock=false;
}
bool MutexLock::isLock()
{
	return _isLock;
}
pthread_mutex_t * MutexLock::getMutex()
{
	return &_mutex;
}
}//end of namespace jjx

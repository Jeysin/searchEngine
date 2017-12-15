#ifndef __MUTEXLOCKGUARD_H__
#define __MUTEXLOCKGUARD_H__

#include"MutexLock.h"

namespace jjx
{
class MutexLockGuard
{
public:
	MutexLockGuard(MutexLock &mutexLock)
	: _mutexLock(mutexLock)
	{
		_mutexLock.lock();
	}
	~MutexLockGuard()
	{
		_mutexLock.unlock();
	}
private:
	MutexLock &_mutexLock;
};
}//end of namespace jjx

#endif

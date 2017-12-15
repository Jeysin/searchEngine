#include"../include/TaskQueue.h"

namespace jjx
{
TaskQueue::TaskQueue(int size)
: _queSize(0)
, _queCapacity(size)
, _notFullCond(_mutexlock)
, _notEmptyCond(_mutexlock)
, _flag(true)
{}
TaskQueue::~TaskQueue()
{}
bool TaskQueue::isFull()
{
	return _queSize==_queCapacity;
}
bool TaskQueue::isEmpty()
{
	return !_queSize;
}
void TaskQueue::push(ElemType &elem)
{
	_mutexlock.lock();
	while(isFull())
	{
		_notFullCond.wait();
	}
	_que.push(elem);
	++_queSize;
	_notEmptyCond.notify();
	_mutexlock.unlock();
}
TaskQueue::ElemType TaskQueue::pop()
{
	_mutexlock.lock();
	while(_flag && isEmpty())
	{
		_notEmptyCond.wait();
	}
	if(_flag)
	{
		ElemType ret=_que.front();
		_que.pop();
		--_queSize;
		_notFullCond.notify();
		_mutexlock.unlock();
		return ret;
	}else{
		_mutexlock.unlock();
		return NULL;
	}
}
int TaskQueue::size()
{
	return _queSize;
}
void TaskQueue::wakeup()
{
	_flag=false;
	_notEmptyCond.notifyAll();
}
}//end of namespace jjx

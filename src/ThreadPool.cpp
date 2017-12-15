#include"../include/ThreadPool.h"
#include"../include/Thread.h"
#include"../include/Mylog.h"
#include"../include/int2str.h"
#include<unistd.h>
#include<sys/syscall.h>
#include<iostream>
using std::cout;
using std::endl;

namespace jjx
{
ThreadPool::ThreadPool(int pthSize, int taskSize)
: _isExit(false)
, _pthNum(pthSize)
, _taskNum(taskSize)
, _taskQue(_taskNum)
{
	_vecPth.reserve(_pthNum);
}
void ThreadPool::start()
{
	for(int idx=0; idx!=_pthNum; ++idx)
	{
		std::shared_ptr<Thread> pth(new Thread(*this, int2str(idx)));
		_vecPth.push_back(pth);
	}
	for(auto pElem : _vecPth)
	{
		pElem->start();
	}
}
void ThreadPool::stop()
{
	while(_taskQue.size())
	{
		sleep(1);
	}
	_isExit=true;
	_taskQue.wakeup();
	for(auto pelem : _vecPth)
	{
		pelem->join();
	}
}
void ThreadPool::addTask(CallBack &cb)
{
	_taskQue.push(cb);
}
ThreadPool::CallBack ThreadPool::getTask()
{
	return _taskQue.pop();
}
void ThreadPool::threadFun()
{
	while(!_isExit)
	{
		CallBack cb=getTask();
		cout<<"I am wakeup : "<<::syscall(SYS_gettid)<<","<<::pthread_self()<<endl;
		//多线程打日志有异常
		//Mylog::getInstance()->_root.debug("I am wakeup : %ld,%ld", ::syscall(SYS_gettid), ::pthread_self());
		if(cb)cb();
	}
}
}//end of namespace jjx

#include"../include/Thread.h"
#include"../include/ThreadPool.h"
#include"../include/Mylog.h"
#include"../include/int2str.h"
#include<unistd.h>
#include<sys/syscall.h>
#include<iostream>
using std::cout;
using std::endl;


namespace jjx
{

__thread int threadIndex=0;//线程特有数据

Thread::Thread(ThreadPool &threadPool, const string &threadName)
: _isRunning(false)
, _threadPool(threadPool)
, _threadName(threadName)
{}
Thread::~Thread()
{
	if(_isRunning)pthread_detach(_pthid);
}
void Thread::start()
{
	pthread_create(&_pthid, NULL, threadFunc, (void *)this);
	_isRunning=true;
}
void Thread::join()
{
	pthread_join(_pthid, NULL);
	_isRunning=false;
}
void * Thread::threadFunc(void *p)
{
	Thread *pth=static_cast<Thread *>(p);
	threadIndex=str2int(pth->_threadName);
	cout<<"I am pthread"<<threadIndex<<": "<<::syscall(SYS_gettid)<<","<<::pthread_self()<<endl;
	//多线程打日志有异常
	//Mylog::getInstance()->_root.debug("I am pthread: %ld,%ld", ::syscall(SYS_gettid), ::pthread_self());
	pth->run();
	return NULL;
}
void Thread::run()
{
	_threadPool.threadFun();
}
}//end of namespace jj,

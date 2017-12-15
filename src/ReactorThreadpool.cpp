#include"../include/ReactorThreadpool.h"
namespace jjx
{
ReactorThreadpool::ReactorThreadpool(Acceptor &acceptor, int pthSize, int taskSize)
: _rea(acceptor, _eventFd.getEventfd())
, _thr(pthSize, taskSize)
{}
int ReactorThreadpool::setHandleNewCon(CallbackType &&cb)
{
	_handleNewCon=cb;
	return 0;
}
int ReactorThreadpool::setBusinessRecvData(CallbackBusinessRecvType &&cb)
{
	_businessRecvData=std::bind(cb, this, std::placeholders::_1);
	return 0;
}
int ReactorThreadpool::setBusinessSendData(CallbackBusinessSendType &&cb)
{
	_businessSendData=std::bind(cb, this);
	return 0;
}
int ReactorThreadpool::setCompute(CallbackComputeType &&cb)
{
	_compute=std::bind(cb, std::ref(*this), std::placeholders::_1);
	return 0;
}
int ReactorThreadpool::setWriteCacheToFile(function<int(void*)> &&cb)
{
	_writeCacheToFile=std::bind(cb, this);
	return 0;
}
int ReactorThreadpool::setDisConnect(CallbackType &&cb)
{
	_disConnect=cb;
	return 0;
}
int ReactorThreadpool::start()
{
	_rea.setHandleNewCon(_handleNewCon);
	_rea.setBusinessRecvData(_businessRecvData);
	_rea.setBusinessSendData(_businessSendData);
	_rea.setWriteCacheToFile(_writeCacheToFile);
	_rea.setDisConnect(_disConnect);
	_thr.start();//开启线程池
	_rea.loop();//开启Reactor循环
	return 0;
}
int ReactorThreadpool::addTaskToThreadPool(ThreadPool::CallBack &&cb)
{
	_thr.addTask(cb);
	return 0;
}
int ReactorThreadpool::addTaskToVeactor(shared_ptr<Task> pTask)
{
	MutexLockGuard lockGuard(_mutexLock);
	_vecTask.push_back(pTask);
	return 0;
}
shared_ptr<vector<shared_ptr<Task>>> ReactorThreadpool::copyTaskFromVeactor()
{
	shared_ptr<vector<shared_ptr<Task>>> pVectorTaskCopy(new vector<shared_ptr<Task>>);
	{
		MutexLockGuard lockGuard(_mutexLock);
		pVectorTaskCopy->swap(_vecTask);//用副本换出任务，解锁再返回
	}
	return pVectorTaskCopy;
}
int ReactorThreadpool::readEventfd()
{
	_eventFd.readEventfd();
	return 0;
}
int ReactorThreadpool::writeEventfd()
{
	_eventFd.writeEventfd();
	return 0;
}
}//end of namespace jjx

#ifndef __REACTORTHREADPOOL_H__
#define __REACTORTHREADPOOL_H__

#include"Reactor.h"
#include"ThreadPool.h"
#include"MutexLock.h"
#include"MutexLockGuard.h"
#include"Eventfd.h"
#include<memory>
#include<functional>
#include<string>
using std::shared_ptr;
using std::function;
using std::string;

namespace jjx
{
class Connection;
class Acceptor;
typedef struct task
{
	string _message;
	shared_ptr<Connection> _pCon;
}Task;

class ReactorThreadpool
{
	typedef function<int(shared_ptr<Connection>)> CallbackType;
	typedef function<int(void*, shared_ptr<Connection>)> CallbackBusinessRecvType;
	typedef function<int(void*)> CallbackBusinessSendType;
	typedef function<int(ReactorThreadpool &, shared_ptr<Task>)> CallbackComputeType;
public:
	ReactorThreadpool(Acceptor &acceptor, int pthSize, int taskSize);
	int setHandleNewCon(CallbackType &&cb);
	int setBusinessRecvData(CallbackBusinessRecvType &&cb);
	int setBusinessSendData(CallbackBusinessSendType &&cb);
	int setCompute(CallbackComputeType &&cb);
	int setWriteCacheToFile(function<int(void*)> &&cb);
	int setDisConnect(CallbackType &&cb);
	int start();
	int addTaskToThreadPool(ThreadPool::CallBack &&cb);
	int addTaskToVeactor(shared_ptr<Task> pTask);
	shared_ptr<vector<shared_ptr<Task>>> copyTaskFromVeactor();
	int readEventfd();
	int writeEventfd();
	function<int(shared_ptr<Task>)> _compute;
private:
	Eventfd _eventFd;
	Reactor _rea;
	ThreadPool _thr;
	MutexLock _mutexLock;
	vector<shared_ptr<Task>> _vecTask;
	CallbackType _handleNewCon;
	CallbackType _businessRecvData;
	function<int(void)> _businessSendData;
	function<int(void)> _writeCacheToFile;
	CallbackType _disConnect;
};

}//end of namespace jjx
#endif

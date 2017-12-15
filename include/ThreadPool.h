#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include"Thread.h"
#include"TaskQueue.h"
#include<functional>
#include<memory>
#include<vector>
using std::shared_ptr;
using std::vector;

namespace jjx
{
class Connection;
class ThreadPool
{
public:
	typedef std::function<int(void)> CallBack;
	ThreadPool(int pthSize, int taskSize);
	void start();
	void stop();
	void addTask(CallBack &cb);
	CallBack getTask();
	void threadFun();
private:
	bool _isExit;
	int _pthNum;
	int _taskNum;
	vector<shared_ptr<Thread>> _vecPth;
	TaskQueue _taskQue;
};
}//end of namespace jjx

#endif

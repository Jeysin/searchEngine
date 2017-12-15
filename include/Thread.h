#ifndef __THREAD_H__
#define __THREAD_H__

#include"Noncopyable.h"
#include<pthread.h>
#include<string>
using std::string;

namespace jjx
{

extern __thread int threadIndex;

class ThreadPool;
class Thread : private Noncopyable
{
public:
	Thread(ThreadPool &threadPool, const string &threadName);
	virtual ~Thread();
	void start();
	void join();
protected:
	void run();
	static void * threadFunc(void *);
private:
	bool _isRunning;
	pthread_t _pthid;
	ThreadPool &_threadPool;
	string _threadName;
};
}//end of namespace jjx

#endif

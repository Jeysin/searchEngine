#ifndef __TASKFUNC_H__
#define __TASKFUNC_H__

#include"Connection.h"
#include"ReactorThreadpool.h"
#include<memory>
#include<cppjieba/Jieba.hpp>
using std::shared_ptr;
namespace jjx
{
class Corrector;
class CacheManager;
class WebQuery;
class ReactorThreadpool;
int HandleNewCon(shared_ptr<Connection> pCon);

int BusinessRecvData(void *p, shared_ptr<Connection> pCon);

int Compute(Corrector &corr, CacheManager &cachManag, WebQuery &webQue, cppjieba::Jieba &jieba, ReactorThreadpool &reaThr, shared_ptr<Task> pTask);

int BusinessSendData(void *p);

int WriteCacheToFile(void *pCachManag, void *p);

int DisConnect(shared_ptr<Connection> pCon);
}//end of namespace jjx
#endif

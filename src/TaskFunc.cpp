#include"../include/GlobalVariable.h"
#include"../include/TaskFunc.h"
#include"../include/Mylog.h"
#include"../include/CacheManager.h"
#include"../include/Corrector.h"
#include"../include/StopWordDict.h"
#include"../include/WebQuery.h"
#include<string.h>
#include<json/json.h>

namespace jjx
{
int HandleNewCon(shared_ptr<Connection> pCon)
{
	//char buf[]="Welcome, I am Server";
	//pCon->send(buf, strlen(buf));
	pCon->getNewFd();//do nothing
	return 0;
}
int BusinessRecvData(void *p, shared_ptr<Connection> pCon)
{
	char buf[256];
	memset(buf, 0, sizeof(buf));
	Json::Value elemJson;
	int ret=pCon->recv(buf, sizeof(buf));//接收对端传来的数据
	if(ret<=0)return -1;
	Mylog::getInstance()->_root.debug("recv from : %s:%d: %s",
					  pCon->getPeerIp().c_str(),
					  pCon->getPeerPort(),
					  buf);
	shared_ptr<Task> pTask(new Task);//将数据打包成任务
	pTask->_message=buf;
	size_t pos=pTask->_message.find('\n');//去除换行符
	pTask->_message=pTask->_message.substr(0, pos);
	pTask->_pCon=pCon;
	ReactorThreadpool *pReaThrPool=(ReactorThreadpool*)p;
	//将任务绑定到_compute函数上，并将函数交给线程池处理
	pReaThrPool->addTaskToThreadPool(std::bind(pReaThrPool->_compute, pTask));
	return 0;
}
int Compute(Corrector &corr, CacheManager &cachManag, WebQuery &webQue, cppjieba::Jieba &jieba, ReactorThreadpool &reaThr, shared_ptr<Task> pTask)
{
	//计算线程的任务：将传过来的数据先用jieba分成若干关键词，去停用词
	//传递给WebQuery，其根据关键词查询网页，返回string，再将string打包成
	//结果放到发送任务对列，通知IO线程将其发送给客户端
	Cache &myCache=cachManag.getCacheByIndex(jjx::threadIndex);
	shared_ptr<vector<string>> pVec=myCache.findWord(pTask->_message);
	if(pVec->size()==0)//如果cache中没有找到
	{
		pVec=corr.findWord(pTask->_message, 1);//在词典中查找最优的一个单词
	}
	if(pVec->size()==0)//如果词典中也没有找到,说明用户输入的很可能是多个关键词
	{
		vector<string> words;
		jieba.Cut(pTask->_message, words);//先分词
		shared_ptr<vector<string>> pWords(new vector<string>);
		StopWordDict * pStopWord=StopWordDict::getInstance(STOP_WORD_PATH);
		for(size_t idx=0; idx<words.size(); ++idx)
		{
			if(!(pStopWord->isStopWordDict(words[idx])))//去停用词
			{
				pWords->push_back(words[idx]);
			}
		}
		webQue.queryWord(pWords, pTask->_message);//查找网页
	}else{//如果词典中找到了，说明用户输入的是一个关键词
		myCache.addWord(pTask->_message, pVec);//先添加进缓存
		webQue.queryWord(pVec, pTask->_message);//查找网页
	}
	//将结果放到任务队列
	reaThr.addTaskToVeactor(pTask);
	//通过eventfd通知IO线程
	reaThr.writeEventfd();
	return 0;
}
int BusinessSendData(void *p)
{
	ReactorThreadpool *pReaThrPool=(ReactorThreadpool*)p;
	//将eventfd读空
	pReaThrPool->readEventfd();
	//从vector中用副本换出任务
	shared_ptr<vector<shared_ptr<Task>>> pVectorTaskCopy=pReaThrPool->copyTaskFromVeactor();
	//将每个任务发送至目的地
	for(size_t i=0; i<(*pVectorTaskCopy).size(); ++i)
	{
		shared_ptr<Task> pTask=(*pVectorTaskCopy)[i];
		pTask->_pCon->send(pTask->_message.c_str(), pTask->_message.size());
		pTask->_pCon->shutdownNewfd();//发送完数据后调用shutdown方法而不是close关闭newfd
					      //因为调用close后newfd无法读到0，故无法从epoll中解注册
		//Mylog::getInstance()->_root.debug("send to   : %s:%d: %s",
		//				  pTask->_pCon->getPeerIp().c_str(),
		//				  pTask->_pCon->getPeerPort(),
		//				  pTask->_message.c_str());
	}
	return 0;
}
int WriteCacheToFile(void *pCachManag, void *p)
{
	CacheManager *pCachM=(CacheManager *)pCachManag;
	ReactorThreadpool *pReaThrPool=(ReactorThreadpool *)p;
	//将写缓存的函数打包丢给线程池处理
	pReaThrPool->addTaskToThreadPool(std::bind(&CacheManager::updateCache, pCachM));
	return 0;
}
int DisConnect(shared_ptr<Connection> pCon)
{
	Mylog::getInstance()->_root.debug("DisConnect: %s:%d",
					  pCon->getPeerIp().c_str(),
					  pCon->getPeerPort());
	return 0;
}
}//end of namespace jjx

#include"../include/GlobalVariable.h"
#include"../include/TaskFunc.h"
#include"../include/int2str.h"
#include"../include/Socket.h"
#include"../include/Acceptor.h"
#include"../include/ReactorThreadpool.h"
#include"../include/CreateEnDict.h"
#include"../include/CreateCnDict.h"
#include"../include/Corrector.h"
#include"../include/Cache.h"
#include"../include/CacheManager.h"
#include"../include/RssParse.h"
#include"../include/InvertIndex.h"
#include"../include/WebQuery.h"
#include<cppjieba/Jieba.hpp>
using namespace jjx;

int main()
{
	Socket soc(IP, PORT);
	soc.reuseAddr();//重用地址
	soc.bind();
	soc.listen();
	Acceptor acc(soc);
	ReactorThreadpool reaThrPool(acc, PTH_NUM, PTH_TASKSIZE);

	CreateEnDict creEnDict;
	CreateCnDict creCnDict;
	if(IS_RELOADCORPUS)//如果不用重新加载语料库则直接使用已有词典
	{
		creEnDict.loadFile(LIB_EN, ".txt");//创建英文词典
		creEnDict.dumpFile(DICT_EN);//输出英文词典到文件
		creCnDict.loadFile(LIB_CN, ".txt");//创建中文词典
		creCnDict.dumpFile(DICT_CN);//输出中文词典到文件
	}
	Corrector corr;
	corr.loadDictionary(DICT_EN);//加载英文词典
	corr.loadDictionary(DICT_CN);//加载中文词典
	corr.createIndex();//建立索引

	CacheManager cachManag;
	cachManag.initCache(CACHE_FILE, PTH_NUM);//初始化缓存

	RssParse rssPar;
	InvertIndex invertIdx;
	if(IS_RELOADWEBPAGE)//如果不用重新计算生成文件，则直接使用已有文件
	{
		rssPar.loadFile(WEBPAGE_DIR, ".xml");//加载xml文件
		rssPar.dumpFile(PAGE_LIB, OFFSET_LIB);//生成网页库和偏移库
		invertIdx.loadFile(PAGE_LIB, OFFSET_LIB);//加载网页库和偏移库
		invertIdx.dumpFile(INVERTINDEX_LIB);//生成倒排索引文件
	}

	WebQuery webQue(PAGE_LIB, OFFSET_LIB, INVERTINDEX_LIB);//初始化网页查询类
	cppjieba::Jieba jieba(DICT_PATH, HMM_PATH, USER_DICT_PATH, IDF_PATH, STOP_WORD_PATH);//初始化jieba分词工具

	reaThrPool.setHandleNewCon(HandleNewCon);
	reaThrPool.setBusinessRecvData(BusinessRecvData);

	reaThrPool.setCompute(std::bind(Compute,
					std::ref(corr),//将词典绑定给计算线程函数
					std::ref(cachManag),//将缓存绑定给计算线程函数
					std::ref(webQue),//将网页查询类绑定给计算线程函数
					std::ref(jieba),//将jieba分词工具绑定给计算线程函数
				        std::placeholders::_1,
					std::placeholders::_2));
	reaThrPool.setBusinessSendData(BusinessSendData);
	reaThrPool.setWriteCacheToFile(std::bind(WriteCacheToFile, &cachManag, std::placeholders::_1));
	reaThrPool.setDisConnect(DisConnect);
	reaThrPool.start();
	return 0;
}

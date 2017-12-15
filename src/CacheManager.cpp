#include"../include/GlobalVariable.h"
#include"../include/CacheManager.h"
#include"../include/Mylog.h"
#include<fstream>
#include<sstream>
using std::ifstream;
using std::ofstream;
using std::istringstream;

namespace jjx
{
int CacheManager::initCache(const string &filename, int size)
{
	Mylog::getInstance()->_root.debug("initialize cache ...");
	ifstream ifs(filename);
	if(ifs.is_open())
	{
		Cache tmpCache;
		string line;
		string word;
		string candidate;
		while(std::getline(ifs, line))
		{
			istringstream iss(line);
			iss>>word;
			iss>>candidate;
			shared_ptr<vector<string>> tmp(new vector<string>);
			tmp->push_back(candidate);
			tmpCache.addWord(word, tmp);
		}
		ifs.close();
		//tmpCache.printMap();
		for(int i=0; i<size; ++i)_cacheVec.push_back(tmpCache);//复制size个cache
		return 0;
	}else{
		Mylog::getInstance()->_root.debug("CacheManager: cache file is not exist");
		ifs.close();
		Cache tmpCache;
		for(int i=0; i<size; ++i)_cacheVec.push_back(tmpCache);//如果没有cache文件，也复制size个空cache
		return -1;
	}
}
Cache & CacheManager::getCacheByIndex(int index)
{
	return _cacheVec[index];
}
int CacheManager::updateCache()
{
	Mylog::getInstance()->_root.debug("update cache ...");
	unordered_map<string, shared_ptr<vector<string>>> &wordMap1=_cacheVec[0].getMap();
	for(size_t idx=1; idx<_cacheVec.size(); ++idx)//将所有cache中条目插入_cacheVec[0]中
	{
		unordered_map<string, shared_ptr<vector<string>>> &wordMap2=_cacheVec[idx].getMap();
		for(auto it=wordMap2.begin(); it!=wordMap2.end(); ++it)
		{
			auto resIt=wordMap1.find(it->first);
			if(resIt==wordMap1.end())//如果wordMap2的单词在wordMap1中没有找到，就在wordMap1中新增
			{
				shared_ptr<vector<string>> tmp(new vector<string>);//深拷贝
				(*tmp)=(*(it->second));
				wordMap1.insert(std::make_pair(it->first, tmp));
			}
		}
	}
	for(size_t idx=1; idx<_cacheVec.size(); ++idx)//同步所有cache
	{
		_cacheVec[idx]=_cacheVec[0];
	}
	writeCacheToFile(CACHE_FILE);//同步完后写入文件
	Mylog::getInstance()->_root.debug("write cache to file successful");
	return 0;
}
int CacheManager::writeCacheToFile(const string &filename)
{
	ofstream ofs(filename);
	if(!ofs.is_open())
	{
		Mylog::getInstance()->_root.debug("CacheManager: open cache file error");
		ofs.close();
		return -1;
	}
	unordered_map<string, shared_ptr<vector<string>>> &wordMap1=_cacheVec[0].getMap();
	for(auto it=wordMap1.begin(); it!=wordMap1.end(); ++it)
	{
		ofs<<it->first;
		for(size_t idx=0; idx<it->second->size(); ++idx)
		{
			ofs<<" "<<(*(it->second))[idx];
		}
		ofs<<std::endl;
	}
	ofs.close();
	return 0;
}
int CacheManager::printCacheVec()
{
	for(size_t idx=0; idx<_cacheVec.size(); ++idx)
	{
		std::cout<<"cacheVec["<<idx<<"]"<<"--------"<<std::endl;
		_cacheVec[idx].printMap();
	}
	return 0;
}
}//end of namespace jjx

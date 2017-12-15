#ifndef __CACHEMANAGER_H__
#define __CACHEMANAGER_H__

#include"Cache.h"
#include<vector>
#include<string>
using std::vector;
using std::string;

namespace jjx
{
class CacheManager
{
public:
	int initCache(const string &filename, int size);
	Cache & getCacheByIndex(int index);
	int updateCache();
	int writeCacheToFile(const string &filename);
	int printCacheVec();//for debug
private:
	vector<Cache> _cacheVec;
};
}//end of namespace jjx

#endif

#ifndef __CACHE_H__
#define __CACHE_H__

#include<unordered_map>
#include<memory>
#include<vector>
#include<string>
using std::unordered_map;
using std::shared_ptr;
using std::string;
using std::vector;

namespace jjx
{
class Cache
{
public:
	Cache(){};
	Cache(const Cache &rhs);//重载复制构造函数
	shared_ptr<vector<string>> findWord(const string &word);
	int addWord(string &word, shared_ptr<vector<string>> candidate);
	unordered_map<string, shared_ptr<vector<string>>> & getMap();
	int printMap();//for debug
	Cache & operator=(const Cache &rhs);//重载复制运算符函数
private:
	unordered_map<string, shared_ptr<vector<string>>> _wordMap;
};
}//end of namespace jjx
#endif

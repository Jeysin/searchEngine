#ifndef __CORRECTOR_H__
#define __CORRECTOR_H__

#include<string>
#include<memory>
#include<map>
#include<set>
#include<vector>
using std::string;
using std::shared_ptr;
using std::vector;
using std::map;
using std::set;
using std::pair;

namespace jjx
{
typedef struct
{
	string _word;
	int _minDistance;
	int _frequency;
}WordItem;
class cmp
{
public:
	bool operator()(WordItem &lhs, WordItem &rhs)
	{
		if(lhs._minDistance>rhs._minDistance)return true;//最小编辑距离越小，优先级越高
		else if(lhs._minDistance<rhs._minDistance)return false;
		else return lhs._frequency<rhs._frequency;//最小编辑距离相同， 词频越高，优先级越高
	}
};
class Corrector
{
public:
	int loadDictionary(const string &dictPath);
	int createIndex();
	shared_ptr<vector<string>> findWord(const string &word, int wordNum);
	int printVector(); //for debug
	int printMap();	//for debug
private:
	vector<pair<string, int>> _dictionary;
	map<string, set<int>> _indexMap;
};
}//end of namespace jjx

#endif

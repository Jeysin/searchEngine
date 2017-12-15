#include"../include/Corrector.h"
#include"../include/Mylog.h"
#include"../include/minEditDistance.h"
#include"../include/Mysplit.h"
#include<stdlib.h>
#include<fstream>
#include<iostream>
#include<algorithm>
#include<queue>
using std::ifstream;
using std::cout;
using std::endl;
using std::priority_queue;

namespace jjx
{
int Corrector::loadDictionary(const string &dictPath)
{
	ifstream ifs(dictPath);
	if(!ifs.is_open())
	{
		Mylog::getInstance()->_root.error("Corrector: open file error");
		exit(EXIT_FAILURE);
	}
	Mylog::getInstance()->_root.debug("loadFile '%s'",dictPath.c_str());
	string word;
	int num;
	while(!ifs.eof())
	{
		ifs>>word;
		ifs>>num;
		_dictionary.push_back(std::make_pair(word, num));
	}
	ifs.close();
	return 0;
}
int Corrector::createIndex()
{
	Mylog::getInstance()->_root.debug("Create Index ...");
	vector<string> character;
	for(size_t index=0; index<_dictionary.size(); ++index)
	{
		Mysplit(_dictionary[index].first, character);//把词分成字
		for(size_t i=0; i<character.size(); ++i)
		{
			set<int> numbers;
			numbers.insert(index);
			pair<map<string, set<int>>::iterator, bool> ret=
				_indexMap.insert(std::make_pair(character[i], numbers));
			if(!ret.second)
			{
				ret.first->second.insert(index);
			}
		}
		character.clear();//注意每次清空character
	}
	return 0;
}
shared_ptr<vector<string>> Corrector::findWord(const string &word, int wordNum)
{
	set<int> numbersSet1;
	set<int> numbersSet2;
	vector<string> character;
	Mysplit(word, character);
	for(size_t i=0; i<character.size(); ++i)
	{
		map<string, set<int>>::iterator ret=_indexMap.find(character[i]);
		if(ret!=_indexMap.end())
		{
			if(0==i)numbersSet1=ret->second;//第一次不做交集运算，以后的每一次都和前一次结果做交集
			else{
				std::set_intersection(numbersSet1.begin(),
						      numbersSet1.end(),
						      ret->second.begin(),
						      ret->second.end(),
						      std::inserter(numbersSet2, numbersSet2.begin()));
				numbersSet1=numbersSet2;
				numbersSet2.clear();
			}
		}
	}
	priority_queue<WordItem, vector<WordItem>, cmp> priQue;//创建一个优先队列
	WordItem wItem;
	set<int>::iterator it;
	for(it=numbersSet1.begin(); it!=numbersSet1.end(); ++it)//将单词计算最小编辑距离后放入优先队列
	{
		wItem._word=_dictionary[*it].first;
		wItem._frequency=_dictionary[*it].second;
		wItem._minDistance=minEditDistance(word, wItem._word);
		priQue.push(wItem);
	}
	shared_ptr<vector<string>> pstr(new vector<string>);
	for(int i=0; i<wordNum && priQue.size()>0; ++i)//从优先队列中取出特定个数的单词
	{
		(*pstr).push_back(priQue.top()._word);
		priQue.pop();
	}
	return pstr;
}
int Corrector::printVector()
{
	for(size_t i=0; i<_dictionary.size(); ++i)
	{
		cout<<"("<<_dictionary[i].first<<","<<_dictionary[i].second<<")";
	}
	return 0;
}
int Corrector::printMap()
{
	map<string, set<int>>::iterator it;
	for(it=_indexMap.begin(); it!=_indexMap.end(); ++it)
	{
		cout<<it->first<<": ";
		set<int>::iterator sit=it->second.begin();
		for(int i=0; i<10 && sit!=it->second.end(); ++i, ++sit)//只打印一部分
		{
			cout<<*sit<<" ";
		}
		cout<<endl;
	}
	return 0;
}
}//end of namespace jjx

#include"../include/Cache.h"
#include<iostream>

namespace jjx
{
Cache::Cache(const Cache &rhs)
{
	for(auto it=rhs._wordMap.begin(); it!=rhs._wordMap.end(); ++it)
	{
		shared_ptr<vector<string>> tmp(new vector<string>);
		(*tmp)=(*(it->second));//深拷贝
		this->_wordMap.insert(std::make_pair(it->first, tmp));
	}
}
shared_ptr<vector<string>> Cache::findWord(const string &word)
{
	unordered_map<string, shared_ptr<vector<string>>>::iterator it=_wordMap.find(word);
	if(it==_wordMap.end())//如果找不到单词，就返回一个指向空vector的智能指针
	{
		shared_ptr<vector<string>> tmp(new vector<string>);
		return tmp;
	}
	else
		return it->second;
}
int Cache::addWord(string &word, shared_ptr<vector<string>> candidate)
{
	_wordMap.insert(std::make_pair(word, candidate));
	return 0;
}
unordered_map<string, shared_ptr<vector<string>>> & Cache::getMap()
{
	return _wordMap;
}
int Cache::printMap()
{
	for(auto it=_wordMap.begin(); it!=_wordMap.end(); ++it)
	{
		std::cout<<it->first;
		for(size_t idx=0; idx<it->second->size(); ++idx)
		{
			std::cout<<" "<<(*(it->second))[idx];
		}
		std::cout<<std::endl;
	}
	return 0;
}
Cache & Cache::operator=(const Cache &rhs)
{
	this->_wordMap.clear();
	for(auto it=rhs._wordMap.begin(); it!=rhs._wordMap.end(); ++it)
	{
		shared_ptr<vector<string>> tmp(new vector<string>);
		(*tmp)=(*(it->second));//深拷贝
		this->_wordMap.insert(std::make_pair(it->first, tmp));
	}
	return *this;
}
}//end of namespace jjx

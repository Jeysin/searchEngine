#include"../include/RmRepeat.h"
#include"../include/Mylog.h"
#include"../include/ReadConfigFile.h"
#include<simhash/Simhasher.hpp>
#include<fstream>
#include<iostream>
using std::cout;
using std::endl;
using std::ofstream;
using std::ifstream;
using simhash::Simhasher;

namespace jjx
{
const string &DICT_PATH = ReadConfigFile::getInstance()->find("DICT_PATH:");
const string &HMM_PATH = ReadConfigFile::getInstance()->find("HMM_PATH:");
const string &IDF_PATH = ReadConfigFile::getInstance()->find("IDF_PATH:");
const string &STOP_WORD_PATH = ReadConfigFile::getInstance()->find("STOP_WORD_PATH:");

int RmRepeat::loadFile(const string &pageFile, const string &offsetFile)
{
	ifstream ifsOffset(offsetFile);
	ifstream ifsPage(pageFile);
	if(!ifsOffset.is_open() || !ifsPage.is_open())
	{
		Mylog::getInstance()->_root.debug("RmRepeat: loadFile error!");
		return -1;
	}
	Mylog::getInstance()->_root.debug("RmRepeat: removing redupliction webpage ...");
	int docid, begin, length;
	Simhasher shasher(DICT_PATH, HMM_PATH, IDF_PATH, STOP_WORD_PATH);
	while(ifsOffset)
	{
		ifsOffset>>docid>>begin>>length;
		shared_ptr<string> pStr(new string(length+1, '\0'));
		ifsPage.seekg(begin);
		ifsPage.read(&((*pStr)[0]), length);
		uint64_t u64=0;
		//vector<std::pair<string, double>> res;
		//shasher.extract((*pStr), res, 10);//topN取10计算simHash
		//cout<<u64<<endl;
		shasher.make((*pStr), 10, u64);
		if(isFit(u64))//将u64与已有比对，如果海明距离大于3，则认为网页不重复
		{
			_newPage.push_back(pStr);
			_simHash.push_back(u64);
		}
	}
	ifsOffset.close();
	ifsPage.close();
	return 0;
}
int RmRepeat::dumpFile(const string &newPage, const string &newOffset)
{
	ofstream ofsOffset(newOffset);
	ofstream ofsPage(newPage);
	if(!ofsOffset.is_open() || !ofsPage.is_open())
	{
		Mylog::getInstance()->_root.debug("RmRepeat: dumpFile error!");
		return -1;
	}
	Mylog::getInstance()->_root.debug("RmRepeat: dumpFile ...");
	int begin;
	int end;
	for(size_t idx=0; idx<_newPage.size(); ++idx)
	{
		begin=ofsPage.tellp();
		ofsPage<<*(_newPage[idx]);
		end=ofsPage.tellp();
		ofsOffset<<idx+1<<" "<<begin<<" "<<end-begin<<endl;
	}
	_newPage.clear();//释放内存
	return 0;
}
bool RmRepeat::isFit(uint64_t u64)
{
	for(size_t idx=0; idx<_simHash.size(); ++idx)
	{
		if(Simhasher::isEqual(_simHash[idx], u64))return false;
	}
	return true;
}
}//end of namespace jjx

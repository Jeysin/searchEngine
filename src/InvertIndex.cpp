#include"../include/GlobalVariable.h"
#include"../include/InvertIndex.h"
#include"../include/Mylog.h"
#include"../include/StopWordDict.h"
#include<cppjieba/Jieba.hpp>
#include<math.h>
#include<fstream>
#include<vector>
using std::vector;
using std::ifstream;
using std::ofstream;
using cppjieba::Jieba;

namespace jjx
{

int InvertIndex::loadFile(const string &pageFile, const string &offsetFile)
{
	ifstream ifsPage(pageFile);
	ifstream ifsOffset(offsetFile);
	if(!ifsPage.is_open() || !ifsOffset.is_open())
	{
		Mylog::getInstance()->_root.debug("InvertIndex: open file error!");
		return -1;
	}
	Mylog::getInstance()->_root.debug("InvertIndex: create invert index ...");
	Jieba jieba(DICT_PATH, HMM_PATH, USER_DICT_PATH, IDF_PATH, STOP_WORD_PATH);
	StopWordDict *pStopWord=StopWordDict::getInstance(STOP_WORD_PATH);
	vector<string> words;
	int docid, begin, length;
	DocInfo docinfo;
	while(ifsOffset)
	{
		ifsOffset>>docid>>begin>>length;
		string str(length, '\0');
		ifsPage.seekg(begin);
		ifsPage.read(&str[0], length);
		jieba.Cut(str, words);//分词
		for(size_t idx=0; idx<words.size(); ++idx)
		{
			if(!(pStopWord->isStopWordDict(words[idx])))//去停用词
			{
				docinfo.frequency=1;
				docinfo.length=length;
				map<int, DocInfo> tmpMap;
				tmpMap.insert(std::make_pair(docid, docinfo));
				auto ret=_invertIndex.insert(std::make_pair(words[idx], tmpMap));
				if(!ret.second)
				{
					auto tmpRet=ret.first->second.insert(std::make_pair(docid, docinfo));
					if(!tmpRet.second)
					{
						++((tmpRet.first->second).frequency);
					}
				}
			}
		}
		words.clear();//words清零
	}
	_docNum=docid;//记录下文档总数N
	ifsPage.close();
	ifsOffset.close();
	return 0;
}
int InvertIndex::dumpFile(const string &indexFile)
{
	ofstream ofs(indexFile);
	if(!ofs.is_open())
	{
		Mylog::getInstance()->_root.debug("InvertIndex: dumpFile error!");
		return -1;
	}
	Mylog::getInstance()->_root.debug("InvertIndex: dumpFile ...");
	double tf;
	double idf;
	double weight;
	for(auto it=_invertIndex.begin(); it!=_invertIndex.end(); ++it)
	{
		ofs<<it->first<<"\t";
		double tmp=(_docNum*1.0)/(it->second.size());
		//idf=::log10(tmp);
		idf=tmp;
		for(auto tmpIt=it->second.begin(); tmpIt!=it->second.end(); ++tmpIt)
		{
			tf=(tmpIt->second.frequency*1.0)/(tmpIt->second.length);
			weight=tf*idf;
			ofs<<tmpIt->first<<"\t"<<weight<<"\t";
		}
		ofs<<'\n';
	}
	ofs.close();
	return 0;
}
int InvertIndex::printMap()
{
	int sum=0;
	for(auto it=_invertIndex.begin(); it!=_invertIndex.end() && sum<100; ++it, ++sum)
	{
		std::cout<<it->first<<std::endl;
	}
	return 0;
}
}//end of namespace jjx

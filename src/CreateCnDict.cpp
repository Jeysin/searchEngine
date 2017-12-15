#include"../include/GlobalVariable.h"
#include"../include/CreateCnDict.h"
#include"../include/GetFilenameFromDir.h"
#include"../include/Mylog.h"
#include"../include/ReadConfigFile.h"
#include<cppjieba/Jieba.hpp>
#include<fstream>
#include<regex>
#include<iostream>
using std::ifstream;
using std::ofstream;
using std::regex;
using std::cout;
using std::endl;
using jjx::ReadConfigFile;

namespace jjx
{
int CreateCnDict::loadFile(const string &dir, const string &suffx)
{
	shared_ptr<GetFilenameFromDir> pGetFilenames(new GetFilenameFromDir(dir, suffx));
	vector<string>::iterator it;
	string filePath;
	regex reg("[\u4e00-\u9fa5]+");//匹配中文
	cppjieba::Jieba jieba(DICT_PATH, HMM_PATH, USER_DICT_PATH, IDF_PATH, STOP_WORD_PATH);
	vector<string> words;
	string line;
	ifstream ifs;
	for(it=pGetFilenames->begin(); it!=pGetFilenames->end(); ++it)
	{
		Mylog::getInstance()->_root.debug("loadFile '%s'", it->c_str());
		filePath=dir+"/"+(*it);
		ifs.open(filePath);
		if(!ifs.is_open())
		{
			Mylog::getInstance()->_root.error("CreateCnDict: open file error");
			exit(EXIT_FAILURE);
		}
		while(std::getline(ifs, line))
		{
			auto word_begin=std::sregex_iterator(line.begin(), line.end(), reg);//正则匹配中文
			auto word_end=std::sregex_iterator();
			for(auto it=word_begin; it!=word_end; ++it)
			{
				jieba.Cut((*it).str(), words, true);//jieba分词
				for(size_t idx=0; idx<words.size(); ++idx)
				{
					std::pair<map<string, int>::iterator, bool> ret=
						_dictionary.insert(std::make_pair(words[idx], 1));
					if(!ret.second)++(ret.first->second);
				}
				words.clear();
			}
		}
		ifs.close();
	}
	return 0;
}
int CreateCnDict::dumpFile(const string &path)
{
	ofstream ofs(path);
	if(!ofs.is_open())
	{
		Mylog::getInstance()->_root.error("CreateCnDict: open file error");
		exit(EXIT_FAILURE);
	}
	Mylog::getInstance()->_root.debug("dumpFile '%s'", path.c_str());
	map<string, int>::iterator it;
	for(it=_dictionary.begin(); it!=_dictionary.end(); ++it)
	{
		ofs<<it->first<<" "<<it->second<<'\n';
	}
	ofs.close();
	cleanMap();//将文件dump到磁盘后调用clean将map中的内存归还给内存池
	return 0;
}
int CreateCnDict::cleanMap()
{
	_dictionary.clear();
	return 0;
}
int CreateCnDict::printMap()
{
	map<string, int>::iterator it;
	for(it=_dictionary.begin(); it!=_dictionary.end(); ++it)
	{
		cout<<it->first<<" "<<it->second<<endl;
	}
	return 0;
}
}//end of namespace jjx

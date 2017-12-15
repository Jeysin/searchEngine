#include"../include/CreateEnDict.h"
#include"../include/GetFilenameFromDir.h"
#include"../include/Mylog.h"
#include<fstream>
#include<regex>
#include<iostream>
using std::ifstream;
using std::ofstream;
using std::regex;
using std::cout;
using std::endl;

namespace jjx
{
CreateEnDict::CreateEnDict()
{}
int CreateEnDict::loadFile(const string &dir, const string &suffx)
{
	shared_ptr<GetFilenameFromDir> pGetFilenames(new GetFilenameFromDir(dir, suffx));
	vector<string>::iterator it;
	string filePath;
	regex reg("[A-Za-z]+");
	string line;
	string word;
	ifstream ifs;
	for(it=pGetFilenames->begin(); it!=pGetFilenames->end(); ++it)
	{
		Mylog::getInstance()->_root.debug("loadFile '%s'", it->c_str());
		filePath=dir+"/"+(*it);
		ifs.open(filePath);
		if(!ifs.is_open())
		{
			Mylog::getInstance()->_root.error("CreateEnDict: open file error");
			exit(EXIT_FAILURE);
		}
		while(std::getline(ifs, line))
		{
			auto word_begin=std::sregex_iterator(line.begin(), line.end(), reg);
			auto word_end=std::sregex_iterator();
			for(auto it=word_begin; it!=word_end; ++it)
			{
				word=(*it).str();
				for(size_t idx=0; idx<word.size(); ++idx)//大写转小写
				{
					if(word[idx]>='A' && word[idx]<='Z')word[idx]=word[idx]+32;
				}
				std::pair<map<string, int>::iterator, bool> ret=
					_dictionary.insert(std::make_pair(word, 1));
				if(!ret.second)++(ret.first->second);
			}
		}
		ifs.close();
	}
	return 0;
}
int CreateEnDict::dumpFile(const string &path)
{
	ofstream ofs(path);
	if(!ofs.is_open())
	{
		Mylog::getInstance()->_root.error("CreateEnDict: open file error");
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
int CreateEnDict::cleanMap()
{
	_dictionary.clear();
	return 0;
}
int CreateEnDict::printMap()
{
	map<string, int>::iterator it;
	for(it=_dictionary.begin(); it!=_dictionary.end(); ++it)
	{
		cout<<it->first<<" "<<it->second<<endl;
	}
	return 0;
}
}//end of namespace jjx

#include"../include/ReadConfigFile.h"
#include"../include/Mylog.h"
#include<fstream>
#include<sstream>
#include<iostream>
using std::cout;
using std::endl;
using std::ifstream;
using std::getline;
using std::istringstream;
using std::make_pair;
using jjx::Mylog;

namespace jjx
{
ReadConfigFile * ReadConfigFile::_pInstance=NULL;
ReadConfigFile::Recycle ReadConfigFile::rec;
ReadConfigFile * ReadConfigFile::getInstance()
{
	if(!_pInstance)_pInstance=new ReadConfigFile(CONFIGFILEPATH);
	return _pInstance;
}
ReadConfigFile::ReadConfigFile(const string &filename)
{
	ifstream ifs(filename);
	if(!ifs.is_open())
	{
		Mylog::getInstance()->_root.error(" ReadConfigFile: open ConfigFile error");
		exit(EXIT_FAILURE);
	}
	string line;
	string key;
	string value;
	while(getline(ifs, line))
	{
		istringstream oss(line);
		oss>>key;
		oss>>value;
		_content.insert(make_pair(key, value));
	}
	ifs.close();
}
const string & ReadConfigFile::find(const string &key)
{
	map<string, string>::iterator it=_content.find(key);
	if(it!=_content.end())
	{
		return it->second;
	}else{
		return key;
	}
}
int ReadConfigFile::printMap()
{
	map<string, string>::iterator it;
	for(it=_content.begin(); it!=_content.end(); ++it)
	{
		cout<<it->first<<" "<<it->second<<endl;
	}
	return 0;
}
}//end of namespace jjx

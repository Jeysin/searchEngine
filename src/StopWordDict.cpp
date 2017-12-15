#include"../include/StopWordDict.h"
#include"../include/Mylog.h"
#include<fstream>
using std::ifstream;

namespace jjx
{
StopWordDict * StopWordDict::_pInstance=NULL;
StopWordDict::Recycle StopWordDict::_rec;

StopWordDict::StopWordDict(const string &filename)
{
	ifstream ifs(filename);
	if(!ifs.is_open())
	{
		Mylog::getInstance()->_root.debug("StopWordDict: open file error");
		return;
	}
	string word;
	while(ifs)
	{
		ifs>>word;
		_stopWord.insert(word);
	}
	ifs.close();
}
StopWordDict * StopWordDict::getInstance(const string &filename)
{
	if(_pInstance==NULL)
		_pInstance=new StopWordDict(filename);
	return _pInstance;
}
bool StopWordDict::isStopWordDict(const string &word)
{
	if(word==" " || word=="\n" || word=="\t")return true;
	if(_stopWord.find(word)!=_stopWord.end())return true;
	else return false;
}
}//end of namespace jjx

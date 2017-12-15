#ifndef __STOPWORDDICT_H__
#define __STOPWORDDICT_H__

#include<string>
#include<set>
using std::string;
using std::set;

namespace jjx
{
class StopWordDict
{
public:
	static StopWordDict * getInstance(const string &filename);
	bool isStopWordDict(const string &word);
private:
	StopWordDict(const string &filename);
	static StopWordDict * _pInstance;
	set<string> _stopWord;
	class Recycle
	{
	public:
		Recycle(){}
		~Recycle()
		{
			delete _pInstance;
		}
	};
	static Recycle _rec;
};
}//end of namespace jjx

#endif

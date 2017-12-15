#ifndef __CREATECNDICT_H__
#define __CREATECNDICT_H__

#include<string>
#include<memory>
#include<map>
using std::map;
using std::string;
using std::shared_ptr;
namespace jjx
{
class CreateCnDict
{
public:
	int loadFile(const string &dir, const string &suffx);
	int dumpFile(const string &path);
	int cleanMap();
	int printMap();	//for debug
private:
	map<string, int> _dictionary;
};
}//end of namespace jjx

#endif

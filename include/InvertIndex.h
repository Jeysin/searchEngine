#ifndef __INVERTINDEX_H__
#define __INVERTINDEX_H__

#include<string>
#include<map>
using std::string;
using std::map;

namespace jjx
{
typedef struct
{
	int frequency;
	int length;
}DocInfo;
class InvertIndex
{
public:
	int loadFile(const string &pageFile, const string &offsetFile);
	int dumpFile(const string &indexFile);
	int printMap();//for debug
private:
	int _docNum;
	map<string, map<int, DocInfo>> _invertIndex;
};
}//end of namespace jjx

#endif

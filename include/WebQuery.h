#ifndef __WEBQUERY_H__
#define __WEBQUERY_H__

#include<string>
#include<memory>
#include<vector>
#include<map>
using std::string;
using std::vector;
using std::shared_ptr;
using std::map;

namespace jjx
{
class WebQuery
{
public:
	WebQuery(const string &pageFile, const string &offsetFile, const string &indexFile);
	int loadOffsetFile(const string &offsetFile);
	int loadIndexFile(const string &indexFile);
	int queryWord(shared_ptr<vector<string>> pWords, string &res);
private:
	string _pageFileName;
	vector<std::pair<int, int>> _offset;
	map<string, map<int, double>> _invertIndex;
};
}//end of namespace jjx

#endif

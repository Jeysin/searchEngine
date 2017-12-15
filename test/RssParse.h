#ifndef __RSSPARSE_H__
#define __RSSPARSE_H__

#include<string>
#include<vector>
#include<memory>
using std::string;
using std::vector;
using std::shared_ptr;

namespace jjx
{
struct RssItem
{
	string title;
	string link;
	string description;
	string content;
};
class RssParse
{
public:
	RssParse();
	int loadAndDumpFile(const string &dir, const string &suffix, const string &pageLib, const string &offsetLib);
private:
	int _count;
	int parseRss(const string &filename);
	bool isFit(uint64_t u64);
	int dumpFile(const string &filename, const string &indexFile);
	vector<shared_ptr<RssItem>> _rssVec;
	vector<uint64_t> _simHash;//网页去重
};
}//end of namespace jjx
#endif

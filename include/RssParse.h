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
	int loadFile(const string &dir, const string &suffix);
	int dumpFile(const string &filename, const string &indexFile);
private:
	int parseRss(const string &filename);
	bool isFit(uint64_t u64);
	vector<shared_ptr<RssItem>> _rssVec;
	vector<uint64_t> _simHash;//网页去重
};
}//end of namespace jjx
#endif

#ifndef __RMREPEAT_H__
#define __RMREPEAT_H__

#include<string>
#include<vector>
#include<memory>
#include<set>
using std::set;
using std::vector;
using std::shared_ptr;
using std::string;

namespace jjx
{
class RmRepeat
{
public:
	int loadFile(const string &pageFile, const string &offsetFile);
	int dumpFile(const string &newPage, const string &newOffset);
private:
	bool isFit(uint64_t u64);
	vector<shared_ptr<string>> _newPage;
	vector<uint64_t> _simHash;
};
}//end of namespace jjx

#endif

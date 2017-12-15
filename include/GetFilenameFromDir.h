#ifndef __GETFILENAMEFROMDIR_H__
#define __GETFILENAMEFROMDIR_H__

#include<string>
#include<vector>
using std::string;
using std::vector;

namespace jjx
{
class GetFilenameFromDir
{
public:
	GetFilenameFromDir(const string &path, const string &suffix);
	vector<string>::iterator begin();
	vector<string>::iterator end();
	int printFilename();//for debug
private:
	vector<string> _filenames;
};
}//end of namespace jjx

#endif

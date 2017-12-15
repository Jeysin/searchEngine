#include"../include/GetFilenameFromDir.h"
#include"../include/Mylog.h"
#include<sys/types.h>
#include<dirent.h>
#include<regex>
#include<iostream>
using std::cout;
using std::endl;
using jjx::Mylog;
namespace jjx
{

GetFilenameFromDir::GetFilenameFromDir(const string &path, const string &suffix)
{
	string regExp="[A-Za-z0-9_-]+\\"+suffix;
	std::regex reg(regExp);
	DIR *dir=::opendir(path.c_str());
	if(NULL==dir){Mylog::getInstance()->_root.error("GetFilenameFromDir: opendir error");exit(EXIT_FAILURE);}
	struct dirent *p;
	while((p=readdir(dir))!=NULL)
	{
		if(regex_match(p->d_name, reg))
		{
			_filenames.push_back(p->d_name);
		}
	}
}
vector<string>::iterator GetFilenameFromDir::begin()
{
	return _filenames.begin();
}
vector<string>::iterator GetFilenameFromDir::end()
{
	return _filenames.end();
}
int GetFilenameFromDir::printFilename()
{
	vector<string>::iterator it;
	for(it=_filenames.begin(); it!=_filenames.end(); ++it)
	{
		cout<<*it<<endl;
	}
	return 0;
}
}//end of namespace jjx

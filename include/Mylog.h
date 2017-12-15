#ifndef __MYLOG_H__
#define __MYLOG_H__

#include<log4cpp/OstreamAppender.hh>
#include<log4cpp/FileAppender.hh>
#include<log4cpp/RollingFileAppender.hh>
#include<log4cpp/Category.hh>
#include<log4cpp/PatternLayout.hh>
#include<log4cpp/Priority.hh>
using namespace log4cpp;

namespace jjx
{
class Mylog
{
public:
	static Mylog *getInstance();
	Category &_root;
private:
	Mylog(const char *filename);
	const char *_filename;
	static Mylog *_pMylog;
	class Recycle
	{
	public:
		~Recycle()
		{
			delete _pMylog;
			_pMylog=NULL;
			Category::shutdown();
		}
	};
	static Recycle rec;
};
}//end of namespace jjx

#endif

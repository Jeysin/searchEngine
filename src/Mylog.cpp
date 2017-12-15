#include"../include/GlobalVariable.h"
#include"../include/Mylog.h"
#include"../include/int2str.h"
#include<stdlib.h>
#include<iostream>
using std::cout;
using std::endl;

namespace jjx
{
Mylog * Mylog::_pMylog=NULL;
Mylog::Recycle Mylog::rec;
Mylog * Mylog::getInstance()
{
	if(NULL==_pMylog)_pMylog=new Mylog(LOG_FILENAME.c_str());
	return _pMylog;
}
Mylog::Mylog(const char *filename)
: _root(Category::getRoot())
, _filename(filename)
{
	if(LOG_ISCOUT)
	{
		OstreamAppender *fAppender=new OstreamAppender("fAppender",&std::cout);
		PatternLayout *pLayout=new PatternLayout();
		pLayout->setConversionPattern("%d: [%p]: %m%n");
		fAppender->setLayout(pLayout);
		_root.addAppender(fAppender);
		_root.setPriority(Priority::DEBUG);
	}
	else if(LOG_ISROLLINGFILE)
	{
		RollingFileAppender *fAppender=new RollingFileAppender
			("fAppender",
		 	_filename, 
			LOG_ROLLINGFILESIZE,
			LOG_ROLLINGFILENUM);
		PatternLayout *pLayout=new PatternLayout();
		pLayout->setConversionPattern("%d: [%p]: %m%n");
		fAppender->setLayout(pLayout);
		_root.addAppender(fAppender);
		_root.setPriority(Priority::DEBUG);
	}else{
		FileAppender *fAppender=new FileAppender("fAppender",_filename);
		PatternLayout *pLayout=new PatternLayout();
		pLayout->setConversionPattern("%d: [%p]: %m%n");
		fAppender->setLayout(pLayout);
		_root.addAppender(fAppender);
		_root.setPriority(Priority::DEBUG);
	}
};
}//end of namespace jjx

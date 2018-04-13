#ifndef __GLOBALVARIABLE_H__
#define __GLOBALVARIABLE_H__

#include<string>
using std::string;

namespace jjx
{
extern const string IP;
extern const int PORT;
extern const int PTH_NUM;
extern const int PTH_TASKSIZE;
extern const int IS_RELOADCORPUS;
extern const int IS_RELOADWEBPAGE;
extern const string LIB_EN;
extern const string LIB_CN;
extern const string DICT_EN;
extern const string DICT_CN;
extern const string CACHE_FILE;
extern const int CACHE_TIME;
extern const string WEBPAGE_DIR;
extern const string PAGE_LIB;
extern const string OFFSET_LIB;
extern const string INVERTINDEX_LIB;
extern const int LOG_ISCOUT;
extern const string LOG_FILENAME;
extern const int LOG_ISROLLINGFILE;
extern const int LOG_ROLLINGFILESIZE;
extern const int LOG_ROLLINGFILENUM;
extern const string DICT_PATH;
extern const string HMM_PATH;
extern const string USER_DICT_PATH;
extern const string IDF_PATH;
extern const string STOP_WORD_PATH;
}//enf of namespace jjx

#endif

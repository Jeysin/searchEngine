#include"../include/GlobalVariable.h"
#include"../include/ReadConfigFile.h"
#include"../include/int2str.h"
#include<string>
using std::string;
using jjx::ReadConfigFile;
using jjx::str2int;

namespace jjx
{
ReadConfigFile *pReadConf=ReadConfigFile::getInstance();

const string IP = pReadConf->find("IP:");
const int PORT = str2int(pReadConf->find("PORT:"));
const int PTH_NUM = str2int(pReadConf->find("PTH_NUM:"));
const int PTH_TASKSIZE = str2int(pReadConf->find("PTH_TASKSIZE:"));
const int IS_RELOADCORPUS = str2int(pReadConf->find("IS_RELOADCORPUS:"));
const int IS_RELOADWEBPAGE = str2int(pReadConf->find("IS_RELOADWEBPAGE:"));
const string LIB_EN = pReadConf->find("LIB_EN:");
const string LIB_CN = pReadConf->find("LIB_CN:");
const string DICT_EN = pReadConf->find("DICT_EN:");
const string DICT_CN = pReadConf->find("DICT_CN:");
const string CACHE_FILE = pReadConf->find("CACHE_FILE:");
const int CACHE_TIME = str2int(pReadConf->find("CACHE_TIME:"));
const string WEBPAGE_DIR = pReadConf->find("WEBPAGE_DIR:");
const string PAGE_LIB = pReadConf->find("PAGE_LIB:");
const string OFFSET_LIB = pReadConf->find("OFFSET_LIB:");
const string INVERTINDEX_LIB = pReadConf->find("INVERTINDEX_LIB:");
const int LOG_ISCOUT = str2int(pReadConf->find("LOG_ISCOUT:"));
const string LOG_FILENAME = pReadConf->find("LOG_FILENAME:");
const int LOG_ISROLLINGFILE = str2int(pReadConf->find("LOG_ISROLLINGFILE:"));
const int LOG_ROLLINGFILESIZE = str2int(pReadConf->find("LOG_ROLLINGFILESIZE:"));
const int LOG_ROLLINGFILENUM = str2int(pReadConf->find("LOG_ROLLINGFILENUM:"));
const string DICT_PATH = pReadConf->find("DICT_PATH:");
const string HMM_PATH = pReadConf->find("HMM_PATH:");
const string USER_DICT_PATH = pReadConf->find("USER_DICT_PATH:");
const string IDF_PATH = pReadConf->find("IDF_PATH:");
const string STOP_WORD_PATH = pReadConf->find("STOP_WORD_PATH:");
}//end of namespace jjx;

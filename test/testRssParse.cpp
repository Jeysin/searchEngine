#include"../include/RssParse.h"
#include"../include/ReadConfigFile.h"
#include<string.h>
using std::string;
using jjx::RssParse;
using jjx::ReadConfigFile;

const string WEBPAGE_DIR = ReadConfigFile::getInstance()->find("WEBPAGE_DIR:");
const string PAGE_LIB = ReadConfigFile::getInstance()->find("PAGE_LIB:");
const string OFFSET_LIB = ReadConfigFile::getInstance()->find("OFFSET_LIB:");

int main()
{
	RssParse rp;
	rp.loadFile(WEBPAGE_DIR, ".xml");
	rp.dumpFile(PAGE_LIB, OFFSET_LIB);
	return 0;
}

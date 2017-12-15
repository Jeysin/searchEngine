#include"../include/RmRepeat.h"
#include"../include/ReadConfigFile.h"
#include<string>
using std::string;
using jjx::RmRepeat;
using jjx::ReadConfigFile;

const string &PAGE_LIB = ReadConfigFile::getInstance()->find("PAGE_LIB:");
const string &OFFSET_LIB = ReadConfigFile::getInstance()->find("OFFSET_LIB:");
const string &NEWPAGE_LIB = ReadConfigFile::getInstance()->find("NEWPAGE_LIB:");
const string &NEWOFFSET_LIB = ReadConfigFile::getInstance()->find("NEWOFFSET_LIB:");
int main()
{
	RmRepeat rmRep;
	rmRep.loadFile(PAGE_LIB, OFFSET_LIB);
	rmRep.dumpFile(NEWPAGE_LIB, NEWOFFSET_LIB);
	return 0;
}

#include"../include/GlobalVariable.h"
#include"../include/InvertIndex.h"
#include<string>
using std::string;
using jjx::InvertIndex;
using jjx::PAGE_LIB;
using jjx::OFFSET_LIB;
using jjx::INVERTINDEX_LIB;

int main()
{
	InvertIndex invertIdx;
	invertIdx.loadFile(PAGE_LIB, OFFSET_LIB);
	invertIdx.dumpFile(INVERTINDEX_LIB);
	return 0;
}


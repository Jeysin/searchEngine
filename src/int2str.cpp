#include"../include/int2str.h"
#include<sstream>
using std::ostringstream;
using std::istringstream;

namespace jjx
{
string int2str(int val)
{
	ostringstream oss;
	oss<<val;
	return oss.str();
}
int str2int(const string &str)
{
	int val;
	istringstream iss(str);
	iss>>val;
	return val;
}
}//end of namespace jjx

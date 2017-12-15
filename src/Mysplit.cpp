#include"../include/Mysplit.h"

namespace jjx
{
int Mysplit(const string &str, vector<string> &character)
{
	size_t cur=0;
	while(cur<str.size())
	{
		int length=0;
		for(int i=7; i>=0; --i)
		{
			if(str[cur] & 1<<i)++length;
			else break;
		}
		if(0==length)++length;
		character.push_back(str.substr(cur, length));
		cur=cur+length;
	}
	return 0;
}
}//end of namespace jjx

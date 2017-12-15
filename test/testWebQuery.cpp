#include"../include/WebQuery.h"
#include"../include/GlobalVariable.h"
#include<iostream>
#include<vector>
#include<string>
using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::cin;
using jjx::WebQuery;
int main()
{
	WebQuery webQue(jjx::PAGE_LIB, jjx::OFFSET_LIB, jjx::INVERTINDEX_LIB);
	shared_ptr<vector<string>> pWords(new vector<string>);
	pWords->push_back("程序员");
	string res;
	webQue.queryWord(pWords, res);
	return 0;
}

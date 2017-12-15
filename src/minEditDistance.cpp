#include"../include/minEditDistance.h"
#include"../include/Mysplit.h"

namespace jjx
{
int minInThreeNum(int a, int b, int c)
{
	int tmp=(a<b)?a:b;
	return (tmp<c)?tmp:c;
}
//计算由word2变为word1的最小编辑距离
int minEditDistance(const string &word1, const string &word2)
{
	vector<string> charcater1;
	vector<string> character2;
	Mysplit(word1, charcater1);//分字
	Mysplit(word2, character2);
	int edit[50][50];
	//初始化矩阵
	//edit[0][0]=0
	//edit[0][j]=j
	//edit[i][0]=i
	for(size_t i=0; i<character2.size()+1; ++i)
	{
		edit[i][0]=i;
	}
	for(size_t j=0; j<charcater1.size()+1; ++j)
	{
		edit[0][j]=j;
	}
	//填矩阵
	for(size_t i=1; i<character2.size()+1; ++i)
	{
		for(size_t j=1; j<charcater1.size()+1; ++j)
		{
			if(character2[i-1]==charcater1[j-1])edit[i][j]=edit[i-1][j-1];
			else edit[i][j]=minInThreeNum(edit[i-1][j]+1, edit[i][j-1]+1, edit[i-1][j-1]+1);
		}
	}
	return edit[character2.size()][charcater1.size()];
}
}//end of namespace jjx

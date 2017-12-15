#include"../include/StopWordDict.h"
#include<cppjieba/Jieba.hpp>
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
using std::cout;
using std::cin;
using std::endl;
using std::ofstream;
using std::ifstream;
using std::string;
using std::vector;
using jjx::StopWordDict;

const char* const DICT_PATH="../data/jieba/jieba.dict.utf8";
const char* const HMM_PATH="../data/jieba/hmm_model.utf8";
const char* const USER_DICT_PATH="../data/jieba/user.dict.utf8";
const char* const IDF_PATH="../data/jieba/idf.utf8";
const char* const STOP_WORD_PATH="../data/jieba/stop_words.utf8";

int main()
{
	cppjieba::Jieba jieba(DICT_PATH, HMM_PATH, USER_DICT_PATH, IDF_PATH, STOP_WORD_PATH);
	vector<string> words;
	string s="我是中国人I am    chinese   man, <content>I love you</content>, 我是一名学生，我喜欢中华传统文化。我未来想当一名程序员。";
	jieba.Cut(s, words);
	StopWordDict *pStopWord=StopWordDict::getInstance(STOP_WORD_PATH);
	ofstream ofs("note.txt");
	for(size_t idx=0; idx<words.size(); ++idx)
	{
		if(!pStopWord->isStopWordDict(words[idx]))ofs<<words[idx]<<'\n';
	}
	ofs.close();
	return 0;
}

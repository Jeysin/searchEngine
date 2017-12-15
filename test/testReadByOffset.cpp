#include"../include/RssParse.h"
#include"../include/ReadConfigFile.h"
#include"../include/StopWordDict.h"
#include<cppjieba/Jieba.hpp>
#include<fstream>
#include<iostream>
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using jjx::ReadConfigFile;
using jjx::StopWordDict;

const string PAGE_LIB = ReadConfigFile::getInstance()->find("PAGE_LIB:");
const string OFFSET_LIB = ReadConfigFile::getInstance()->find("OFFSET_LIB:");
const char* const DICT_PATH="../data/jieba/jieba.dict.utf8";
const char* const HMM_PATH="../data/jieba/hmm_model.utf8";
const char* const USER_DICT_PATH="../data/jieba/user.dict.utf8";
const char* const IDF_PATH="../data/jieba/idf.utf8";
const char* const STOP_WORD_PATH="../data/jieba/stop_words.utf8";

int main()
{
	//int docid, begin, length;
	//ifstream ifs;
	//ifs.open(OFFSET_LIB);
	//ifs>>docid>>begin>>length;
	//ifs.close();
	
	ifstream ifs("C3-Art0002.txt");
	int length=1000;
	string str(length, '\0');
	ifs.seekg(1000);
	ifs.read(&str[0], length);
	ifs.close();
	cout<<str<<endl;
	cout<<endl;

	cppjieba::Jieba jieba(DICT_PATH, HMM_PATH, USER_DICT_PATH, IDF_PATH, STOP_WORD_PATH);
	vector<string> words;
	jieba.Cut(str, words);
	StopWordDict *pStopWord=StopWordDict::getInstance(STOP_WORD_PATH);
	ofstream ofs("note1.txt");
	for(size_t idx=0; idx<words.size(); ++idx)
	{
		if(!pStopWord->isStopWordDict(words[idx]))
		{
			cout<<words[idx]<<" ";
			ofs<<words[idx]<<'\n';
		}
	}
	ofs.close();
	cout<<endl;
	return 0;
}

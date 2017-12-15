#include"../include/RssParse.h"
#include"../include/GetFilenameFromDir.h"
#include"../include/tinyxml2.h"
#include"../include/Mylog.h"
#include"../include/ReadConfigFile.h"
#include<regex>
#include<fstream>
#include<simhash/Simhasher.hpp>
using namespace tinyxml2;
using std::regex;
using std::ofstream;
using simhash::Simhasher;

namespace jjx
{
RssParse::RssParse()
: _count(0)
{}
int RssParse::loadAndDumpFile(const string &dir, const string &suffix, const string &pageLib, const string &offsetLib)
{
	GetFilenameFromDir getFilename(dir, suffix);
	vector<string>::iterator it;
	string filename;
	for(it=getFilename.begin(); it!=getFilename.end(); ++it)
	{
		Mylog::getInstance()->_root.debug("RssParse: parse '%s'...", (*it).c_str());
		filename=dir+"/"+(*it);
		parseRss(filename);
		dumpFile(pageLib, offsetLib);
	}
	return 0;
}
int RssParse::dumpFile(const string &filename, const string &indexFile)
{
	Mylog::getInstance()->_root.debug("RssParse: dumpFile ...");
	std::ofstream ofs;
	std::ofstream ofsIndex;
	if(_count==0)
	{
		ofs.open(filename);
		ofsIndex.open(indexFile);
	}else{
		ofs.open(filename, std::ios::app);
		ofsIndex.open(indexFile, std::ios::app);
	}
	int begin;
	int end;
	for(size_t idx=0; idx<_rssVec.size(); ++idx)
	{
		++_count;
		begin=ofs.tellp();
		ofs<<"<doc>\n"
		  <<"<docid>"<<_count<<"</docid>\n"
		  <<"<title>"<<_rssVec[idx]->title<<"</title>\n"
		  <<"<link>"<<_rssVec[idx]->link<<"</link>\n"
		  <<"<description>"<<_rssVec[idx]->description<<"</description>\n"
		  <<"<content>"<<_rssVec[idx]->content<<"</content>\n"
		  <<"</doc>\n";
		end=ofs.tellp();
		ofsIndex<<_count<<" "<<begin<<" "<<end-begin<<std::endl;
	}
	ofs.close();
	ofsIndex.close();
	_rssVec.clear();//释放内存
	return 0;
}

const string &DICT_PATH = ReadConfigFile::getInstance()->find("DICT_PATH:");
const string &HMM_PATH = ReadConfigFile::getInstance()->find("HMM_PATH:");
const string &IDF_PATH = ReadConfigFile::getInstance()->find("IDF_PATH:");
const string &STOP_WORD_PATH = ReadConfigFile::getInstance()->find("STOP_WORD_PATH:");

int RssParse::parseRss(const string &filename)
{
	std::regex reg("<.+?>");
	XMLDocument doc;	
	doc.LoadFile(filename.c_str());
	XMLElement *rss=doc.FirstChildElement("rss");
	if(NULL==rss)return -1;
	XMLElement *channel=rss->FirstChildElement("channel");
	if(NULL==channel)return -1;
	XMLElement *item=channel->FirstChildElement("item");
	XMLElement *xtmp;
	Simhasher shasher(DICT_PATH, HMM_PATH, IDF_PATH, STOP_WORD_PATH);
	while(item)
	{
		shared_ptr<RssItem> pTmp(new RssItem);
		xtmp=item->FirstChildElement("title");
		if(NULL==xtmp)pTmp->title="";
		else {
			const char *cstr=xtmp->GetText();
			if(NULL==cstr)pTmp->title="";
			else pTmp->title=cstr;
		}
		xtmp=item->FirstChildElement("link");
		if(NULL==xtmp)pTmp->link="";
		else {
			const char *cstr=xtmp->GetText();
			if(NULL==cstr)pTmp->link="";
			else pTmp->link=cstr;
		}
		xtmp=item->FirstChildElement("description");
		if(NULL==xtmp)pTmp->description="";
		else {
			const char *cstr=xtmp->GetText();
			if(NULL==cstr)pTmp->description="";
			else pTmp->description=std::regex_replace(cstr, reg, "");
		}
		xtmp=item->FirstChildElement("content:encoded");
		if(NULL==xtmp)pTmp->content=pTmp->description;
		else {
			const char *cstr=xtmp->GetText();
			if(NULL==cstr)pTmp->content=pTmp->description;
			else pTmp->content=std::regex_replace(cstr, reg, "");
		}
		uint64_t u64;
		shasher.make(pTmp->content, 10, u64);//对网页内容求simhash值,topN取10
		if(isFit(u64))//如果海明距离大于3，认为不重复，加入vector, 并记录其simhash
		{
			_rssVec.push_back(pTmp);
			_simHash.push_back(u64);
		}
		item=item->NextSiblingElement("item");
	}
	return 0;
}
bool RssParse::isFit(uint64_t u64)
{
	for(size_t idx=0; idx<_simHash.size(); ++idx)
	{
		if(Simhasher::isEqual(_simHash[idx], u64))return false;
	}
	return true;
}
}//end of namespace jjx

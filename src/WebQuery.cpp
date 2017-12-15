#include"../include/WebQuery.h"
#include"../include/Mylog.h"
#include<json/json.h>
#include<fstream>
#include<sstream>
#include<algorithm>
using std::ifstream;
using std::istringstream;

namespace jjx
{
WebQuery::WebQuery(const string &pageFile, const string &offsetFile, const string &indexFile)
: _pageFileName(pageFile)
{
	loadOffsetFile(offsetFile);
	loadIndexFile(indexFile);
}
int WebQuery::loadOffsetFile(const string &offsetFile)
{
	ifstream ifs(offsetFile);
	if(!ifs.is_open())
	{
		Mylog::getInstance()->_root.debug("WebQuery: load offset file error!");
		return -1;
	}
	Mylog::getInstance()->_root.debug("WebQuery: load offset file ...");
	int docid, begin, length;
	while(ifs)
	{
		ifs>>docid>>begin>>length;
		_offset.push_back(std::make_pair(begin, length));
	}
	ifs.close();
	return 0;
}
int WebQuery::loadIndexFile(const string &indexFile)
{
	ifstream ifs(indexFile);
	if(!ifs.is_open())
	{
		Mylog::getInstance()->_root.debug("WebQuery: load index file error!");
		return -1;
	}
	Mylog::getInstance()->_root.debug("WebQuery: load index file ...");
	string line;
	string word;
	int docid;
	double weight;
	while(std::getline(ifs, line))
	{
		istringstream iss(line);
		iss>>word;
		map<int, double> tmpMap;
		while(iss)
		{
			iss>>docid>>weight;
			tmpMap.insert(std::make_pair(docid, weight));
		}
		_invertIndex.insert(std::make_pair(word, tmpMap));
	}
	ifs.close();
	return 0;
}
int WebQuery::queryWord(shared_ptr<vector<string>> pWords, string &res)
{
	map<int, double> resMap;//用于存储包含关键字的docid和其权重加和
	for(size_t idx=0; idx<pWords->size(); ++idx)
	{
		auto ret=_invertIndex.find((*pWords)[idx]);
		if(ret!=_invertIndex.end())//如果在倒排索引中找到关键字，则遍历其map
		{
			map<int, double>::iterator it;
			for(it=ret->second.begin(); it!=ret->second.end(); ++it)
			{
				auto tmpRet=resMap.insert(*it);
				if(!tmpRet.second)//如果插入失败，则把权重加到对应docid上
				{
					tmpRet.first->second = tmpRet.first->second + it->second;
				}
			}
		}
	}
	Json::Value root;
	Json::Value arrJson;
	if(resMap.size()==0)//如果集合是空的，说明没有符合关键词的文章
	{
		Json::Value elemJson;
		elemJson["title"]="404 Not Found";
		elemJson["summary"]="Sorry, we can't find what you want.";
		elemJson["url"]="https://www.baidu.com";
		arrJson.append(elemJson);
		root["files"]=arrJson;
		Json::StyledWriter sWriter;
		res=sWriter.write(root);
		return -1;//返回-1表示没有找到
	}
	vector<std::pair<double, int>> resVec;
	for(auto it=resMap.begin(); it!=resMap.end(); ++it)
	{
		resVec.push_back(std::make_pair(it->second, it->first));
	}
	std::sort(resVec.begin(), resVec.end(), std::greater<std::pair<double, int>>());//对文章按权重由大到小排序
	//for(size_t idx=0; idx<resVec.size(); ++idx)//for debug
	//{
	//	std::cout<<resVec[idx].first<<" "<<resVec[idx].second<<std::endl;
	//}
	int docid, begin, length;
	ifstream ifs(_pageFileName);
	if(!ifs.is_open())
	{
		Mylog::getInstance()->_root.debug("WebQuery: open web page file error!");
		return -1;
	}
	for(size_t idx=0; idx<resVec.size(); ++idx)
	{
		docid=resVec[idx].second;//获取文章id, 起始位置和长度
		begin=_offset[docid-1].first;
		length=_offset[docid-1].second;
		string docStr(length, '\0');
		ifs.seekg(begin);
		ifs.read(&docStr[0], length);//读取文章

		Json::Value elemJson;
		int titlePos1=docStr.find("<title>")+7;
		int titlePos2=docStr.find("</title>");
		elemJson["title"]=docStr.substr(titlePos1, titlePos2-titlePos1);
		int summaryPos1=docStr.find("<description>")+13;
		int summaryPos2=docStr.find("</description>");
		elemJson["summary"]=docStr.substr(summaryPos1, summaryPos2-summaryPos1);
		int urlPos1=docStr.find("<link>")+6;
		int urlPos2=docStr.find("</link>");
		elemJson["url"]=docStr.substr(urlPos1, urlPos2-urlPos1);
		arrJson.append(elemJson);
	}
	ifs.close();
	root["files"]=arrJson;
	Json::StyledWriter sWriter;
	res=sWriter.write(root);
	return 0;
}
}//end of namespace jjx

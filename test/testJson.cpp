#include<json/json.h>
#include<string>
using std::string;
using std::endl;
using std::cout;
int test0()
{
	Json::Value json_object;
	string str="{\"age\":26, \"name\":\"abc\"}";
	Json::Reader reader;
	reader.parse(str, json_object);
	cout<<str<<endl;
	cout<<json_object["age"];
	cout<<json_object["name"];
	cout<<endl;
	for(Json::ValueIterator it=json_object.begin(); it!=json_object.end(); ++it)
	{
		cout<<*it;
	}
	return 0;
}
int test1()
{
	Json::Value elemJson;
	Json::Value arrJson;
	elemJson["title"]="jiaxian";
	elemJson["summary"]="jiangjiaxian hello word";
	elemJson["url"]="https://www.baidu.com";
	arrJson.append(elemJson);
	//for(Json::ValueIterator it=arrJson.begin(); it!=arrJson.end(); ++it)
	//{
	//	cout<<*it<<endl;
	//}
	for(Json::ValueIterator it=elemJson.begin(); it!=elemJson.end(); ++it)
	{
		cout<<*it;
	}
	cout<<elemJson["title"];
	cout<<elemJson["summary"];
	cout<<elemJson["url"];
	cout<<elemJson<<endl;
	return 0;
}
int main()
{
	//test0();
	test1();
	return 0;
}

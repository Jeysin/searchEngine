#include<iostream>
#include<string>
using std::cout;
using std::cin;
using std::endl;
using std::string;
int main()
{
	string str="<docid>12</docid>\n<content>我是中国人，我热爱中国传统文化</content>";
	int pos1=str.find("<content>")+9;
	int pos2=str.find("</content>");
	cout<<str.substr(pos1, pos2-pos1)<<endl;;
	return 0;
}

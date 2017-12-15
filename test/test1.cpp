#include<iostream>
using std::cout;
using std::endl;
#define N 100
int main()
{
	char *p=new char[N]();
	for(int i=0; i<N; ++i)
	{
		cout<<*(p+i)<<" ";
	}
	cout<<endl;
	return 0;
}

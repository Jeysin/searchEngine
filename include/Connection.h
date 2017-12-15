#ifndef __CONNECTION_H__
#define __CONNECTION_H__

#include<string>
using std::string;

namespace jjx
{
class Connection
{
public:
	Connection(int newfd, const string &peerIp, int peerPort);
	~Connection();
	int send(const char *buf, int length);
	int recv(char *buf, int length);
	int getNewFd();
	const string & getPeerIp();
	int getPeerPort();
	int shutdownNewfd();
private:
	int _newfd;
	string _peerIp;
	int _peerPort;
};
}//end of namespace jjx

#endif

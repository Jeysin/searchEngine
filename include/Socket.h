#ifndef __SOCKET_H__
#define __SOCKET_H__

#include<string>
using std::string;

namespace jjx
{
class Socket
{
public:
	Socket(const string &localIp, int localPort);
	~Socket();
	int reuseAddr();
	int reusePort();
	int bind();
	int listen();
	int getSockFd();
	const string & getLocalIp();
	int getLocalPort();
private:
	int _sfd;
	string _localIp;
	int _localPort;
};
}//end of namespace jjx

#endif

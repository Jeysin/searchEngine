#include"../include/Socket.h"
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define MAXLINK 10

namespace jjx
{
Socket::Socket(const string &localIp, int localPort)
: _localIp(localIp)
, _localPort(localPort)
{
	_sfd=::socket(AF_INET, SOCK_STREAM, 0);
	if(-1==_sfd){perror("::socket");exit(EXIT_FAILURE);}
}
Socket::~Socket()
{
	::close(_sfd);
}
int Socket::reuseAddr()
{
	int reuse=1;
	int ret=::setsockopt(_sfd, SOL_SOCKET, SO_REUSEADDR, (const void*)&reuse, sizeof(int));
	if(-1==ret){perror("::setsockopt");exit(EXIT_FAILURE);}
	return ret;
}
int Socket::reusePort()
{
	int reuse=1;
	int ret=::setsockopt(_sfd, SOL_SOCKET, SO_REUSEPORT, (const void*)&reuse, sizeof(int));
	if(-1==ret){perror("::setsockopt");exit(EXIT_FAILURE);}
	return ret;
}
int Socket::bind()
{
	struct sockaddr_in localAddr;
	localAddr.sin_family=AF_INET;
	localAddr.sin_addr.s_addr=::inet_addr(_localIp.c_str());
	localAddr.sin_port=::htons(_localPort);
	int ret=::bind(_sfd, (struct sockaddr*)&localAddr, sizeof(localAddr));
	if(-1==ret){perror("::bind");exit(EXIT_FAILURE);}
	return ret;
}
int Socket::listen()
{
	int ret=::listen(_sfd, MAXLINK);
	if(-1==ret){perror("::listen");exit(EXIT_FAILURE);}
	return ret;
}
int Socket::getSockFd()
{
	return _sfd;
}
const string & Socket::getLocalIp()
{
	return _localIp;
}
int Socket::getLocalPort()
{
	return _localPort;
}
}//end of namespae jjx

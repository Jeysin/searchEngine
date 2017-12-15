#include"../include/Connection.h"
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>

namespace jjx
{
Connection::Connection(int newfd, const string &peerIp, int peerPort)
: _newfd(newfd)
, _peerIp(peerIp)
, _peerPort(peerPort)
{}
Connection::~Connection()
{
	::close(_newfd);
}
int Connection::send(const char *buf, int length)
{
	return ::send(_newfd, buf, length, 0);
}
int Connection::recv(char *buf, int length)
{
	return ::recv(_newfd, buf, length, 0);
}
int Connection::getNewFd()
{
	return _newfd;
}
const string & Connection::getPeerIp()
{
	return _peerIp;
}
int Connection::getPeerPort()
{
	return _peerPort;
}
int Connection::shutdownNewfd()
{
	return ::shutdown(_newfd, SHUT_WR);
}
}//end of namespae jjx

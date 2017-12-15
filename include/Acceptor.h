#ifndef __ACCEPTOR_H__
#define __ACCEPTOR_H__

#include<string>
#include<memory>
using std::string;
using std::shared_ptr;

namespace jjx
{
class Socket;
class Connection;
class Acceptor
{
public:
	Acceptor(Socket &socket);
	shared_ptr<Connection> accept();
	int getSockFd();
	const string & getLocalIp();
	int getLocalPort();
private:
	Socket &_socket;
};
}//end namespace jjx
#endif

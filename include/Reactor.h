#ifndef __REACTOR_H__
#define __REACTOR_H__

#include"Timerfd.h"
#include<sys/epoll.h>
#include<map>
#include<memory>
#include<vector>
#include<functional>
using std::string;
using std::map;
using std::vector;
using std::shared_ptr;
using std::function;

namespace jjx
{
class Acceptor;
class Connection;
class Reactor;

class Reactor
{
typedef function<int(shared_ptr<Connection>)> CallbackType;
public:
	Reactor(Acceptor &acceptor, int etfd);
	~Reactor();
	int loop();
	int unloop();
	int addEpollinFd(int fd);
	int delEpollinFd(int fd);
	int setHandleNewCon(CallbackType &cb);
	int setBusinessRecvData(CallbackType &cb);
	int setBusinessSendData(function<int(void)> &cb);
	int setWriteCacheToFile(function<int(void)> &cb);
	int setDisConnect(CallbackType &cb);
	const string & getLocalIp();
	int getLocalPort();
private:
	bool _isLooping;
	int _epfd;
	Acceptor &_acceptor;
	int _sfd;
	int _etfd;//eventfd
	Timerfd _timerfd;
	vector<struct epoll_event> _eventsList;
	map<int, shared_ptr<Connection>> _lisenMap;
	CallbackType _handleNewCon;
	CallbackType _businessRecvData;
	function<int(void)> _businessSendData;
	function<int(void)> _writeCacheToFile;
	CallbackType _disConnect;
};
}//end of namespace jjx

#endif

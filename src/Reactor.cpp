#include"../include/GlobalVariable.h"
#include"../include/Reactor.h"
#include"../include/Acceptor.h"
#include"../include/Connection.h"
#include"../include/Mylog.h"
#include"../include/int2str.h"
#include<unistd.h>
#include<string.h>
#include<utility>

namespace jjx
{
Reactor::Reactor(Acceptor &acceptor, int etfd)
: _isLooping(false)
, _acceptor(acceptor)
, _sfd(_acceptor.getSockFd())
, _etfd(etfd)
, _eventsList(10)
{
	_epfd=::epoll_create(1);
	if(-1==_epfd){perror("::epoll_create");exit(EXIT_FAILURE);}
	addEpollinFd(_sfd);//注册sfd
	addEpollinFd(_etfd);//注册eventfd
	_timerfd.setTime(60, CACHE_TIME);//1分钟后开始，间隔time时间后触发
	addEpollinFd(_timerfd.getTfd());//注册timerfd
}
Reactor::~Reactor()
{
	::close(_epfd);
}
int Reactor::loop()
{
	_isLooping=true;
	while(_isLooping)
	{
		int ret;
		do{
			ret=::epoll_wait(_epfd, &(*_eventsList.begin()), _eventsList.size(), 5000);
		}while(-1==ret && errno==EINTR);
		if(-1==ret)
		{
			perror("::epoll_wait");
			exit(EXIT_FAILURE);
		}else if(ret==(int)_eventsList.size())
		{
			_eventsList.resize(2*ret);//扩容
		}else if(0==ret)
		{
			//cout<<"::epoll_wait: timeout(5s)"<<endl;
			//Mylog::getInstance()->_root.debug("::epoll_wait: timeout(5s)");
		}else if(ret>0)
		for(int i=0; i<ret; ++i)
		{
			if(_eventsList[i].data.fd==_sfd)//如果有新连接请求
			{
				shared_ptr<Connection> pCon=_acceptor.accept();
				Mylog::getInstance()->_root.debug("%s:%d--->%s:%d",
								  _acceptor.getLocalIp().c_str(),
								  _acceptor.getLocalPort(),
								  pCon->getPeerIp().c_str(),
								  pCon->getPeerPort());
				_lisenMap.insert(std::make_pair(pCon->getNewFd(), pCon));//添加新Connection
				addEpollinFd(pCon->getNewFd());//将新的newfd注册至_epfd;
				_handleNewCon(pCon);//执行处理新连接的回调函数
			}
			else if(_eventsList[i].data.fd==_etfd)//如果是计算线程发来的信号
			{
				_businessSendData();//执行发送数据的业务逻辑函数
			}
			else if(_eventsList[i].data.fd==_timerfd.getTfd())//如果是到了缓存写入时间
			{
				_timerfd.readTimerfd();//将timerfd读空
				_writeCacheToFile();//执行将缓存写入文件的函数
			}else{
				if(_eventsList[i].events & EPOLLIN)//如果是有业务请求
				{
					int fd=_eventsList[i].data.fd;
					map<int, shared_ptr<Connection>>::iterator it=_lisenMap.find(fd);
					int ret=0;
					if(it!=_lisenMap.end())
					{
						ret=_businessRecvData(it->second);//执行接收数据的业务逻辑函数
					}
					if(ret<0)//如果对端关闭或连接断开，从epoll解注册，并从_listenMap中移除newfd
					{
						shared_ptr<Connection> pCon=it->second;
						Mylog::getInstance()->_root.debug("%s:%d-x->%s:%d",
										  _acceptor.getLocalIp().c_str(),
										  _acceptor.getLocalPort(),
										  pCon->getPeerIp().c_str(),
										  pCon->getPeerPort());
						delEpollinFd(fd);
						_disConnect(it->second);
						_lisenMap.erase(it);
					}
				}
			}
		}
	}
	return 0;
}
int Reactor::unloop()
{
	_isLooping=false;
	return 0;
}
int Reactor::addEpollinFd(int fd)
{
	struct epoll_event event;
	memset(&event, 0, sizeof(event));
	event.events=EPOLLIN;
	event.data.fd=fd;
	int ret=::epoll_ctl(_epfd, EPOLL_CTL_ADD, fd, &event);
	if(-1==ret){perror("::epoll_ctl");exit(EXIT_FAILURE);}
	return ret;
}
int Reactor::delEpollinFd(int fd)
{
	struct epoll_event event;
	memset(&event, 0, sizeof(event));
	event.events=EPOLLIN;
	event.data.fd=fd;
	int ret=::epoll_ctl(_epfd, EPOLL_CTL_DEL, fd, &event);
	if(-1==ret){perror("::epoll_ctl");exit(EXIT_FAILURE);}
	return ret;
}
int Reactor::setBusinessRecvData(CallbackType &cb)
{
	_businessRecvData=cb;
	return 0;
}
int Reactor::setBusinessSendData(function<int(void)> &cb)
{
	_businessSendData=cb;
	return 0;
}
int Reactor::setHandleNewCon(CallbackType &cb)
{
	_handleNewCon=cb;
	return 0;
}
int Reactor::setWriteCacheToFile(function<int(void)> &cb)
{
	_writeCacheToFile=cb;
	return 0;
}
int Reactor::setDisConnect(CallbackType &cb)
{
	_disConnect=cb;
	return 0;
}
const string & Reactor::getLocalIp()
{
	return _acceptor.getLocalIp();
}
int Reactor::getLocalPort()
{
	return _acceptor.getLocalPort();
}
}//end of namespace jjx

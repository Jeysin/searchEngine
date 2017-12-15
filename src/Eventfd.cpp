#include"../include/Eventfd.h"
#include<sys/eventfd.h>
#include<unistd.h>
#include<stdio.h>

namespace jjx
{
Eventfd::Eventfd()
{
	_efd=::eventfd(0, 0);
	if(_efd<0)perror("::eventfd");
}
Eventfd::~Eventfd()
{
	::close(_efd);
}
int Eventfd::readEventfd()
{
	uint64_t buf;
	int ret=::read(_efd, &buf, sizeof(buf));
	if(ret<0)perror("::read");
	return ret;
}
int Eventfd::writeEventfd()
{
	uint64_t buf=1;
	int ret=::write(_efd, &buf, sizeof(buf));
	if(ret<0)perror("::write");
	return ret;
}
int Eventfd::getEventfd()
{
	return _efd;
}
}//end of namespace jjx

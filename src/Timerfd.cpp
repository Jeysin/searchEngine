#include"../include/Timerfd.h"
#include<unistd.h>
#include<sys/timerfd.h>

namespace jjx
{
Timerfd::Timerfd()
: _tfd(timerfd_create(CLOCK_REALTIME, 0))
{}
Timerfd::~Timerfd()
{
	::close(_tfd);
}
int Timerfd::setTime(int valTime, int inteTime)
{
	struct itimerspec new_time;
	new_time.it_value.tv_sec=valTime;
	new_time.it_value.tv_nsec=0;
	new_time.it_interval.tv_sec=inteTime;
	new_time.it_interval.tv_nsec=0;
	_isStart=true;
	return timerfd_settime(_tfd, 0, &new_time, NULL);
}
int Timerfd::stop()
{
	_isStart=false;
	return setTime(0, 0);
}
int Timerfd::getTfd()
{
	return _tfd;
}
bool Timerfd::isStart()
{
	return _isStart;
}
int Timerfd::readTimerfd()
{
	long int buf;
	::read(_tfd, &buf, sizeof(buf));
	return 0;
}
}//end of namespace jjx

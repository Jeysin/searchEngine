#ifndef __TIMERFD_H__
#define __TIMERFD_H__

namespace jjx
{
class Timerfd
{
public:
	Timerfd();
	~Timerfd();
	int setTime(int valTime, int inteTime);
	int stop();
	bool isStart();
	int getTfd();
	int readTimerfd();
private:
	int _tfd;
	bool _isStart;
};
}//end of namespace jjx

#endif

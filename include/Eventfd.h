#ifndef __EVENTFD_H__
#define __EVENTFD_H__

namespace jjx
{
class Eventfd
{
public:
	Eventfd();
	~Eventfd();
	int readEventfd();
	int writeEventfd();
	int getEventfd();
private:
	int _efd;
};
}//end of namespace jjx

#endif

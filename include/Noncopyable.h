#ifndef __NONCOPYABLE_H__
#define __NONCOPYABLE_H__

namespace jjx
{
class Noncopyable
{
public:
	Noncopyable(){};
private:
	Noncopyable(const Noncopyable &);
	Noncopyable & operator=(const Noncopyable &);
};
}//end of namespace jjx

#endif

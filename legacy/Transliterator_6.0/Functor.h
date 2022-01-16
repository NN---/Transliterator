#ifndef __FUNCTOR_H__
#define __FUNCTOR_H__

template<int N, typename T>
struct TupleShorter
{
	bool operator()(const T& l, const T& r) const
	{ return l.get<N>().size() < r.get<N>().size(); }
};

#endif // __FUNCTOR_H__
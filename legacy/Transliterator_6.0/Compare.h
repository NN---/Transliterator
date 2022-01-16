#ifndef __COMPARE_H__
#define __COMPARE_H__

#pragma once

#include "types.h"

template<bool t_bLangTop>
inline bool CompareLangType(const LangType& l, const LangType& r)
{
	return l.get<!t_bLangTop>() == r.get<!t_bLangTop>() &&
		 l.get<t_bLangTop>() == r.get<t_bLangTop>();
}

inline bool CompareIgnore(const IgnoreTextType& l, const IgnoreTextType& r)
{ return l.get<IgnoreTextPos::String>() == r.get<IgnoreTextPos::String>(); }

template<typename TType>
struct CompareSearchTraits;

template<>
struct CompareSearchTraits<LangType> 
{ typedef LangString::traits_type traits_type; };

template<>
struct CompareSearchTraits<IgnoreTextType> 
{ typedef IgnoreTextString::traits_type traits_type; };

template<typename TType, int N>
class CompareSearch
{
	const TType& m_r;
	size_t m_len;
public:
	CompareSearch(const TType& r,size_t len) :
	  m_r(r) , m_len(len) {}
	
	bool operator()(const TType& r) const
	{ return cmp(r); }
private:
	bool cmp(const TType& r) const
	{
		return CompareSearchTraits<TType>::traits_type::compare(
			m_r.get<N>().c_str(),
			r.get<N>().c_str(),
			m_len)?false:true;
	}
};

typedef CompareSearch<LangType,0> CompareSearchLangTop;
typedef CompareSearch<LangType,1> CompareSearchLangBottom;
typedef CompareSearch<IgnoreTextType,0> CompareSearchIgnoreText;

#endif // __COMPARE_H__
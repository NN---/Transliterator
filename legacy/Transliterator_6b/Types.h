#ifndef __TYPES_H__
#define __TYPES_H__

#include "translate.h"

typedef NN::wnd_string LangStringA;
typedef NN::wnd_wstring LangStringW;

typedef NN::wnd_char_traits<char> LangStringTraitsA;
typedef NN::wnd_char_traits<wchar_t> LangStringTraitsW;

typedef boost::tuple<
			LangStringA,
			LangStringA,
			Translate::Translation
		>LangTypeA;
typedef boost::tuple<
			LangStringW,
			LangStringW,
			Translate::Translation
		>LangTypeW;

typedef std::list<LangTypeA> LangArrayA;
typedef std::list<LangTypeW> LangArrayW;

typedef NN::wnd_char_traits<char> LangArrayTraitsA;
typedef NN::wnd_char_traits<wchar_t> LangArrayTraitsW;

typedef LangStringW LangString;
typedef LangStringTraitsW LangStringTraits;
typedef LangTypeW LangType;
typedef LangArrayW LangArray;
typedef LangStringTraitsW LangSringTraits;

// Ignore
typedef NN::wnd_wstring IgnoreString;

typedef boost::tuple<
			IgnoreString,
			Translate::Translation
		>IgnoreType;

typedef std::list<IgnoreType> IgnoreArray;

#endif // __TYPES_H__
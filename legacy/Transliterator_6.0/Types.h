#ifndef __TYPES_H__
#define __TYPES_H__

#pragma once

#include "translate.h"

typedef char LangCharA;
typedef wchar_t LangCharW;

typedef boost::tuple<
			const LangCharA*,
			const LangCharA*,
			Translate::Translation
		>LangTypeNSA;

typedef boost::tuple<
			const LangCharW*,
			const LangCharW*,
			Translate::Translation
		>LangTypeNSW;

typedef NN::wnd_string LangStringA;
typedef NN::wnd_wstring LangStringW;
typedef std::basic_string<TCHAR, NN::wnd_char_traits<TCHAR> > LangStringT;

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

struct LangPos
{
	enum LangPos_E
	{
		Top,
		Bottom,
		Translation
	};
};

typedef std::vector<LangTypeA> LangArrayA;
typedef std::vector<LangTypeW> LangArrayW;

typedef LangCharW LangChar;
typedef LangTypeNSW LangTypeNS;
typedef LangStringW LangString;
typedef LangStringTraitsW LangStringTraits;
typedef LangTypeW LangType;
typedef LangArrayW LangArray;
typedef LangStringTraitsW LangSringTraits;

// IgnoreText
typedef NN::wnd_wstring IgnoreTextString;

typedef boost::tuple<
			IgnoreTextString,
			Translate::Translation
		>IgnoreTextType;

struct IgnoreTextPos
{
	enum IgnoreTextPos_E
	{
		String,
		Translation
	};
};


typedef std::vector<IgnoreTextType> IgnoreTextArray;

// Text
typedef std::vector<wchar_t> TextType;

#endif // __TYPES_H__
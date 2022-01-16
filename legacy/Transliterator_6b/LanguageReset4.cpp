#include "stdafx.h"
#include "language.h"

// QWER
void Language::Reset4(LangProfile& rProfile)
{
	// Symbols
	static const LangType aSymbols[]=
	{
		LangType(L"`",L"�",Translate::trnsAll),
		LangType(L"~",L"�",Translate::trnsAll),
		LangType(L"@",L"\"",Translate::trnsAll),
		LangType(L"#",L"�",Translate::trnsAll),
		LangType(L"$",L";",Translate::trnsAll),
		LangType(L"^",L":",Translate::trnsAll),
		LangType(L"&",L"?",Translate::trnsAll),
		LangType(L"|",L"/",Translate::trnsAll),
		LangType(L"q",L"�",Translate::trnsAll),
		LangType(L"w",L"�",Translate::trnsAll),
		LangType(L"e",L"�",Translate::trnsAll),
		LangType(L"r",L"�",Translate::trnsAll),
		LangType(L"t",L"�",Translate::trnsAll),
		LangType(L"y",L"�",Translate::trnsAll),
		LangType(L"u",L"�",Translate::trnsAll),
		LangType(L"i",L"�",Translate::trnsAll),
		LangType(L"o",L"�",Translate::trnsAll),
		LangType(L"p",L"�",Translate::trnsAll),
		LangType(L"[",L"�",Translate::trnsAll),
		LangType(L"{",L"�",Translate::trnsAll),
		LangType(L"]",L"�",Translate::trnsAll),
		LangType(L"}",L"�",Translate::trnsAll),
		LangType(L"a",L"�",Translate::trnsAll),
		LangType(L"s",L"�",Translate::trnsAll),
		LangType(L"d",L"�",Translate::trnsAll),
		LangType(L"f",L"�",Translate::trnsAll),
		LangType(L"g",L"�",Translate::trnsAll),
		LangType(L"h",L"�",Translate::trnsAll),
		LangType(L"j",L"�",Translate::trnsAll),
		LangType(L"k",L"�",Translate::trnsAll),
		LangType(L"l",L"�",Translate::trnsAll),
		LangType(L";",L"�",Translate::trnsAll),
		LangType(L":",L"�",Translate::trnsAll),
		LangType(L"'",L"�",Translate::trnsAll),
		LangType(L"\"",L"�",Translate::trnsAll),
		LangType(L"z",L"�",Translate::trnsAll),
		LangType(L"x",L"�",Translate::trnsAll),
		LangType(L"c",L"�",Translate::trnsAll),
		LangType(L"v",L"�",Translate::trnsAll),
		LangType(L"b",L"�",Translate::trnsAll),
		LangType(L"n",L"�",Translate::trnsAll),
		LangType(L"m",L"�",Translate::trnsAll),
		LangType(L",",L"�",Translate::trnsAll),
		LangType(L"<",L"�",Translate::trnsAll),
		LangType(L".",L"�",Translate::trnsAll),
		LangType(L">",L"�",Translate::trnsAll),
		LangType(L"/",L".",Translate::trnsAll),
		LangType(L"?",L",",Translate::trnsAll),
		LangType(L"Q",L"�",Translate::trnsAll),
		LangType(L"W",L"�",Translate::trnsAll),
		LangType(L"E",L"�",Translate::trnsAll),
		LangType(L"R",L"�",Translate::trnsAll),
		LangType(L"T",L"�",Translate::trnsAll),
		LangType(L"Y",L"�",Translate::trnsAll),
		LangType(L"U",L"�",Translate::trnsAll),
		LangType(L"I",L"�",Translate::trnsAll),
		LangType(L"O",L"�",Translate::trnsAll),
		LangType(L"P",L"�",Translate::trnsAll),
		LangType(L"A",L"�",Translate::trnsAll),
		LangType(L"S",L"�",Translate::trnsAll),
		LangType(L"D",L"�",Translate::trnsAll),
		LangType(L"F",L"�",Translate::trnsAll),
		LangType(L"G",L"�",Translate::trnsAll),
		LangType(L"H",L"�",Translate::trnsAll),
		LangType(L"J",L"�",Translate::trnsAll),
		LangType(L"K",L"�",Translate::trnsAll),
		LangType(L"L",L"�",Translate::trnsAll),
		LangType(L"Z",L"�",Translate::trnsAll),
		LangType(L"X",L"�",Translate::trnsAll),
		LangType(L"C",L"�",Translate::trnsAll),
		LangType(L"V",L"�",Translate::trnsAll),
		LangType(L"B",L"�",Translate::trnsAll),
		LangType(L"N",L"�",Translate::trnsAll),
		LangType(L"M",L"�",Translate::trnsAll),
	};
	rProfile.m_aSymbols.assign(aSymbols,
		aSymbols+sizeof(aSymbols)/sizeof(aSymbols[0]));

	// Name
	static const wchar_t strName[]=L"Symbols";
	rProfile.m_strName=strName;

	// Ignore
	rProfile.ResetIgnore();
}
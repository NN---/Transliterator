#include "stdafx.h"
#include "language.h"

// Standard
void Language::Reset1(LangProfile& rProfile)
{
	// Symbols
	static const LangType aSymbols[]=
	{
		LangType(L"a",L"?",Translate::trnsAll),
		LangType(L"A",L"?",Translate::trnsAll),
		LangType(L"b",L"?",Translate::trnsAll),
		LangType(L"B",L"?",Translate::trnsAll),
		LangType(L"c",L"?",Translate::trnsAll),
		LangType(L"C",L"?",Translate::trnsAll),
		LangType(L"ch",L"?",Translate::trnsAll),
		LangType(L"cH",L"?",Translate::trns1_2),
		LangType(L"CH",L"?",Translate::trnsAll),
		LangType(L"Ch",L"?",Translate::trns1_2),
		LangType(L"d",L"?",Translate::trnsAll),
		LangType(L"D",L"?",Translate::trnsAll),
		LangType(L"e",L"?",Translate::trnsAll),
		LangType(L"E",L"?",Translate::trnsAll),
		LangType(L"e'",L"?",Translate::trnsAll),
		LangType(L"E'",L"?",Translate::trnsAll),
		LangType(L"e`",L"?",Translate::trnsAll),
		LangType(L"E`",L"?",Translate::trnsAll),
		LangType(L"e''",L"?",Translate::trnsAll),
		LangType(L"E''",L"?",Translate::trnsAll),
		LangType(L"f",L"?",Translate::trnsAll),
		LangType(L"F",L"?",Translate::trnsAll),
		LangType(L"g",L"?",Translate::trnsAll),
		LangType(L"G",L"?",Translate::trnsAll),
		LangType(L"g'`",L"?",Translate::trnsAll),
		LangType(L"g`'",L"?",Translate::trns1_2),
		LangType(L"G'`",L"?",Translate::trnsAll),
		LangType(L"G`'",L"?",Translate::trns1_2),
		LangType(L"h",L"?",Translate::trnsAll),
		LangType(L"H",L"?",Translate::trnsAll),
		LangType(L"i",L"?",Translate::trnsAll),
		LangType(L"I",L"?",Translate::trnsAll),
		LangType(L"i'",L"?",Translate::trnsAll),
		LangType(L"I'",L"?",Translate::trnsAll),
		LangType(L"i`",L"?",Translate::trnsAll),
		LangType(L"I`",L"?",Translate::trnsAll),
		LangType(L"j",L"?",Translate::trnsAll),
		LangType(L"J",L"?",Translate::trnsAll),
		LangType(L"k",L"?",Translate::trnsAll),
		LangType(L"K",L"?",Translate::trnsAll),
		LangType(L"l",L"?",Translate::trnsAll),
		LangType(L"L",L"?",Translate::trnsAll),
		LangType(L"m",L"?",Translate::trnsAll),
		LangType(L"M",L"?",Translate::trnsAll),
		LangType(L"n",L"?",Translate::trnsAll),
		LangType(L"N",L"?",Translate::trnsAll),
		LangType(L"o",L"?",Translate::trnsAll),
		LangType(L"O",L"?",Translate::trnsAll),
		LangType(L"p",L"?",Translate::trnsAll),
		LangType(L"P",L"?",Translate::trnsAll),
		LangType(L"q",L"?",Translate::trns1_2),
		LangType(L"Q",L"?",Translate::trns1_2),
		LangType(L"r",L"?",Translate::trnsAll),
		LangType(L"R",L"?",Translate::trnsAll),
		LangType(L"s",L"?",Translate::trnsAll),
		LangType(L"S",L"?",Translate::trnsAll),
		LangType(L"sh",L"?",Translate::trnsAll),
		LangType(L"sH",L"?",Translate::trns1_2),
		LangType(L"SH",L"?",Translate::trnsAll),
		LangType(L"Sh",L"?",Translate::trns1_2),
		LangType(L"sh''",L"?",Translate::trns1_2),
		LangType(L"sH''",L"?",Translate::trns1_2),
		LangType(L"Sh''",L"?",Translate::trns1_2),
		LangType(L"SH''",L"?",Translate::trns1_2),
		LangType(L"sch'",L"?",Translate::trnsAll),
		LangType(L"sCh'",L"?",Translate::trns1_2),
		LangType(L"scH'",L"?",Translate::trns1_2),
		LangType(L"sCH'",L"?",Translate::trns1_2),
		LangType(L"Sch'",L"?",Translate::trns1_2),
		LangType(L"SCh'",L"?",Translate::trns1_2),
		LangType(L"ScH'",L"?",Translate::trns1_2),
		LangType(L"SCH'",L"?",Translate::trnsAll),
		LangType(L"t",L"?",Translate::trnsAll),
		LangType(L"T",L"?",Translate::trnsAll),
		LangType(L"tc'",L"?",Translate::trns1_2),
		LangType(L"tC'",L"?",Translate::trns1_2),
		LangType(L"Tc'",L"?",Translate::trns1_2),
		LangType(L"TC'",L"?",Translate::trns1_2),
		LangType(L"u",L"?",Translate::trnsAll),
		LangType(L"U",L"?",Translate::trnsAll),
		LangType(L"u'",L"?",Translate::trnsAll),
		LangType(L"U'",L"?",Translate::trnsAll),
		LangType(L"v",L"?",Translate::trnsAll),
		LangType(L"V",L"?",Translate::trnsAll),
		LangType(L"w",L"?",Translate::trns1_2),
		LangType(L"W",L"?",Translate::trns1_2),
		LangType(L"w''",L"?",Translate::trns1_2),
		LangType(L"W''",L"?",Translate::trns1_2),
		LangType(L"x",L"?",Translate::trns1_2),
		LangType(L"X",L"?",Translate::trns1_2),
		LangType(L"y",L"?",Translate::trnsAll),
		LangType(L"Y",L"?",Translate::trnsAll),
		LangType(L"ya",L"?",Translate::trnsAll),
		LangType(L"yA",L"?",Translate::trns1_2),
		LangType(L"YA",L"?",Translate::trnsAll),
		LangType(L"Ya",L"?",Translate::trns1_2),
		LangType(L"yu",L"?",Translate::trnsAll),
		LangType(L"yU",L"?",Translate::trns1_2),
		LangType(L"YU",L"?",Translate::trnsAll),
		LangType(L"Yu",L"?",Translate::trns1_2),
		LangType(L"y'",L"?",Translate::trnsAll),
		LangType(L"Y'",L"?",Translate::trnsAll),
		LangType(L"z",L"?",Translate::trnsAll),
		LangType(L"Z",L"?",Translate::trnsAll),
		LangType(L"'",L"?",Translate::trnsAll),
		LangType(L"''",L"?",Translate::trnsAll),
		LangType(L"`",L"?",Translate::trnsAll),
		LangType(L"``",L"?",Translate::trnsAll),
	};
	rProfile.m_aSymbols.assign(aSymbols,
		aSymbols+sizeof(aSymbols)/sizeof(aSymbols[0]));

	// Name
	static const wchar_t strName[]=L"Standard";
	rProfile.m_strName=strName;

	// Ignore
	rProfile.ResetIgnore();
}
#include "stdafx.h"
#include "language.h"

// Symbols
void Language::Reset2(LangProfile& rProfile)
{
	// Symbols
	static const LangType aSymbols[]=
	{
		LangType(L"a",L"�",Translate::trnsAll),
		LangType(L"A",L"�",Translate::trnsAll),
		LangType(L"6",L"�",Translate::trnsAll),
		LangType(L"6",L"�",Translate::trns2_1),
		LangType(L"B",L"�",Translate::trnsAll),
		LangType(L"�",L"�",Translate::trns2_1),
		LangType(L"r",L"�",Translate::trnsAll),
		LangType(L"r",L"�",Translate::trns2_1),
		LangType(L"D",L"�",Translate::trnsAll),
		LangType(L"D",L"�",Translate::trns2_1),
		LangType(L"e",L"�",Translate::trnsAll),
		LangType(L"E",L"�",Translate::trnsAll),
		LangType(L"e",L"�",Translate::trns2_1),
		LangType(L"E",L"�",Translate::trns2_1),
		LangType(L">|<",L"�",Translate::trnsAll),
		LangType(L"}|{",L"�",Translate::trnsAll),
		LangType(L">-|-<",L"�",Translate::trns2_1),
		LangType(L"}-|-{",L"�",Translate::trns1_2),
		LangType(L"3",L"�",Translate::trnsAll),
		LangType(L"3",L"�",Translate::trns2_1),
		LangType(L"u",L"�",Translate::trnsAll),
		LangType(L"U",L"�",Translate::trnsAll),
		LangType(L"u'",L"�",Translate::trnsAll),
		LangType(L"U'",L"�",Translate::trnsAll),
		LangType(L"u`",L"�",Translate::trns1_2),
		LangType(L"U`",L"�",Translate::trns1_2),
		LangType(L"k",L"�",Translate::trnsAll),
		LangType(L"K",L"�",Translate::trnsAll),
		LangType(L"/\\",L"�",Translate::trnsAll),
		LangType(L"JI",L"�",Translate::trnsAll),
		LangType(L"m",L"�",Translate::trnsAll),
		LangType(L"M",L"�",Translate::trnsAll),
		LangType(L"H",L"�",Translate::trnsAll),
		LangType(L"H",L"�",Translate::trns2_1),
		LangType(L"o",L"�",Translate::trnsAll),
		LangType(L"O",L"�",Translate::trnsAll),
		LangType(L"n",L"�",Translate::trnsAll),
		LangType(L"n",L"�",Translate::trns2_1),
		LangType(L"p",L"�",Translate::trnsAll),
		LangType(L"P",L"�",Translate::trnsAll),
		LangType(L"c",L"�",Translate::trnsAll),
		LangType(L"C",L"�",Translate::trnsAll),
		LangType(L"T",L"�",Translate::trnsAll),
		LangType(L"T",L"�",Translate::trns2_1),
		LangType(L"y",L"�",Translate::trnsAll),
		LangType(L"Y",L"�",Translate::trnsAll),
		LangType(L"f",L"�",Translate::trnsAll),
		LangType(L"F",L"�",Translate::trnsAll),
		LangType(L"<|>",L"�",Translate::trnsAll),
		LangType(L"<I>",L"�",Translate::trnsAll),
		LangType(L"x",L"�",Translate::trnsAll),
		LangType(L"X",L"�",Translate::trnsAll),
		LangType(L"L|",L"�",Translate::trnsAll),
		LangType(L"L|",L"�",Translate::trns2_1),
		LangType(L"4",L"�",Translate::trnsAll),
		LangType(L"4",L"�",Translate::trns2_1),
		LangType(L"LLI",L"�",Translate::trnsAll),
		LangType(L"w",L"�",Translate::trnsAll),
		LangType(L"LL|",L"�",Translate::trnsAll),
		LangType(L"LL|",L"�",Translate::trns2_1),
		LangType(L"\\",L"�",Translate::trnsAll),
		LangType(L"\\\\",L"�",Translate::trns2_1),
		LangType(L"bI",L"�",Translate::trnsAll),
		LangType(L"bI",L"�",Translate::trns2_1),
		LangType(L"b",L"�",Translate::trnsAll),
		LangType(L"b",L"�",Translate::trns2_1),
		LangType(L"e",L"�",Translate::trns2_1),
		LangType(L"E",L"�",Translate::trns2_1),
		LangType(L"IO",L"�",Translate::trnsAll),
		LangType(L"IO",L"�",Translate::trns2_1),
		LangType(L"I-O",L"�",Translate::trns1_2),
		LangType(L"I-O",L"�",Translate::trns2_1),
		LangType(L"9I",L"�",Translate::trnsAll),
		LangType(L"9I",L"�",Translate::trns2_1),
	};
	rProfile.m_aSymbols.assign(aSymbols,
		aSymbols+sizeof(aSymbols)/sizeof(aSymbols[0]));

	// Name
	static const wchar_t strName[]=L"Symbols";
	rProfile.m_strName=strName;

	// Ignore
	rProfile.ResetIgnore();
}
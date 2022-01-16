#include "stdafx.h"
#include "language.h"

// Symbols
void Language::Reset2(LangProfile& rProfile)
{
	// Symbols
	static const LangType aSymbols[]=
	{
		LangType(L"a",L"à",Translate::trnsAll),
		LangType(L"A",L"À",Translate::trnsAll),
		LangType(L"6",L"á",Translate::trnsAll),
		LangType(L"6",L"Á",Translate::trns2_1),
		LangType(L"B",L"Â",Translate::trnsAll),
		LangType(L"Â",L"â",Translate::trns2_1),
		LangType(L"r",L"ã",Translate::trnsAll),
		LangType(L"r",L"Ã",Translate::trns2_1),
		LangType(L"D",L"ä",Translate::trnsAll),
		LangType(L"D",L"Ä",Translate::trns2_1),
		LangType(L"e",L"å",Translate::trnsAll),
		LangType(L"E",L"Å",Translate::trnsAll),
		LangType(L"e",L"¸",Translate::trns2_1),
		LangType(L"E",L"¨",Translate::trns2_1),
		LangType(L">|<",L"æ",Translate::trnsAll),
		LangType(L"}|{",L"Æ",Translate::trnsAll),
		LangType(L">-|-<",L"æ",Translate::trns2_1),
		LangType(L"}-|-{",L"Æ",Translate::trns1_2),
		LangType(L"3",L"ç",Translate::trnsAll),
		LangType(L"3",L"Ç",Translate::trns2_1),
		LangType(L"u",L"è",Translate::trnsAll),
		LangType(L"U",L"È",Translate::trnsAll),
		LangType(L"u'",L"é",Translate::trnsAll),
		LangType(L"U'",L"É",Translate::trnsAll),
		LangType(L"u`",L"é",Translate::trns1_2),
		LangType(L"U`",L"É",Translate::trns1_2),
		LangType(L"k",L"ê",Translate::trnsAll),
		LangType(L"K",L"Ê",Translate::trnsAll),
		LangType(L"/\\",L"ë",Translate::trnsAll),
		LangType(L"JI",L"Ë",Translate::trnsAll),
		LangType(L"m",L"ì",Translate::trnsAll),
		LangType(L"M",L"Ì",Translate::trnsAll),
		LangType(L"H",L"í",Translate::trnsAll),
		LangType(L"H",L"Í",Translate::trns2_1),
		LangType(L"o",L"î",Translate::trnsAll),
		LangType(L"O",L"Î",Translate::trnsAll),
		LangType(L"n",L"ï",Translate::trnsAll),
		LangType(L"n",L"Ï",Translate::trns2_1),
		LangType(L"p",L"ð",Translate::trnsAll),
		LangType(L"P",L"Ð",Translate::trnsAll),
		LangType(L"c",L"ñ",Translate::trnsAll),
		LangType(L"C",L"Ñ",Translate::trnsAll),
		LangType(L"T",L"ò",Translate::trnsAll),
		LangType(L"T",L"Ò",Translate::trns2_1),
		LangType(L"y",L"ó",Translate::trnsAll),
		LangType(L"Y",L"Ó",Translate::trnsAll),
		LangType(L"f",L"ô",Translate::trnsAll),
		LangType(L"F",L"Ô",Translate::trnsAll),
		LangType(L"<|>",L"ô",Translate::trnsAll),
		LangType(L"<I>",L"Ô",Translate::trnsAll),
		LangType(L"x",L"õ",Translate::trnsAll),
		LangType(L"X",L"Õ",Translate::trnsAll),
		LangType(L"L|",L"ö",Translate::trnsAll),
		LangType(L"L|",L"Ö",Translate::trns2_1),
		LangType(L"4",L"÷",Translate::trnsAll),
		LangType(L"4",L"×",Translate::trns2_1),
		LangType(L"LLI",L"Ø",Translate::trnsAll),
		LangType(L"w",L"ø",Translate::trnsAll),
		LangType(L"LL|",L"ù",Translate::trnsAll),
		LangType(L"LL|",L"Ù",Translate::trns2_1),
		LangType(L"\\",L"ú",Translate::trnsAll),
		LangType(L"\\\\",L"Ú",Translate::trns2_1),
		LangType(L"bI",L"û",Translate::trnsAll),
		LangType(L"bI",L"Û",Translate::trns2_1),
		LangType(L"b",L"ü",Translate::trnsAll),
		LangType(L"b",L"Ü",Translate::trns2_1),
		LangType(L"e",L"ý",Translate::trns2_1),
		LangType(L"E",L"Ý",Translate::trns2_1),
		LangType(L"IO",L"þ",Translate::trnsAll),
		LangType(L"IO",L"Þ",Translate::trns2_1),
		LangType(L"I-O",L"þ",Translate::trns1_2),
		LangType(L"I-O",L"Þ",Translate::trns2_1),
		LangType(L"9I",L"ÿ",Translate::trnsAll),
		LangType(L"9I",L"ß",Translate::trns2_1),
	};
	rProfile.m_aSymbols.assign(aSymbols,
		aSymbols+sizeof(aSymbols)/sizeof(aSymbols[0]));

	// Name
	static const wchar_t strName[]=L"Symbols";
	rProfile.m_strName=strName;

	// Ignore
	rProfile.ResetIgnore();
}
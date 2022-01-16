#include "stdafx.h"
#include "language.h"

// QWER
void Language::Reset4(LangProfile& rProfile)
{
	// Symbols
	static const LangType aSymbols[]=
	{
		LangType(L"`",L"¸",Translate::trnsAll),
		LangType(L"~",L"¨",Translate::trnsAll),
		LangType(L"@",L"\"",Translate::trnsAll),
		LangType(L"#",L"¹",Translate::trnsAll),
		LangType(L"$",L";",Translate::trnsAll),
		LangType(L"^",L":",Translate::trnsAll),
		LangType(L"&",L"?",Translate::trnsAll),
		LangType(L"|",L"/",Translate::trnsAll),
		LangType(L"q",L"é",Translate::trnsAll),
		LangType(L"w",L"ö",Translate::trnsAll),
		LangType(L"e",L"ó",Translate::trnsAll),
		LangType(L"r",L"ê",Translate::trnsAll),
		LangType(L"t",L"å",Translate::trnsAll),
		LangType(L"y",L"í",Translate::trnsAll),
		LangType(L"u",L"ã",Translate::trnsAll),
		LangType(L"i",L"ø",Translate::trnsAll),
		LangType(L"o",L"ù",Translate::trnsAll),
		LangType(L"p",L"ç",Translate::trnsAll),
		LangType(L"[",L"õ",Translate::trnsAll),
		LangType(L"{",L"Õ",Translate::trnsAll),
		LangType(L"]",L"ú",Translate::trnsAll),
		LangType(L"}",L"Ú",Translate::trnsAll),
		LangType(L"a",L"ô",Translate::trnsAll),
		LangType(L"s",L"û",Translate::trnsAll),
		LangType(L"d",L"â",Translate::trnsAll),
		LangType(L"f",L"à",Translate::trnsAll),
		LangType(L"g",L"ï",Translate::trnsAll),
		LangType(L"h",L"ð",Translate::trnsAll),
		LangType(L"j",L"î",Translate::trnsAll),
		LangType(L"k",L"ë",Translate::trnsAll),
		LangType(L"l",L"ä",Translate::trnsAll),
		LangType(L";",L"æ",Translate::trnsAll),
		LangType(L":",L"Æ",Translate::trnsAll),
		LangType(L"'",L"ý",Translate::trnsAll),
		LangType(L"\"",L"Ý",Translate::trnsAll),
		LangType(L"z",L"ÿ",Translate::trnsAll),
		LangType(L"x",L"÷",Translate::trnsAll),
		LangType(L"c",L"ñ",Translate::trnsAll),
		LangType(L"v",L"ì",Translate::trnsAll),
		LangType(L"b",L"è",Translate::trnsAll),
		LangType(L"n",L"ò",Translate::trnsAll),
		LangType(L"m",L"ü",Translate::trnsAll),
		LangType(L",",L"á",Translate::trnsAll),
		LangType(L"<",L"Á",Translate::trnsAll),
		LangType(L".",L"þ",Translate::trnsAll),
		LangType(L">",L"Þ",Translate::trnsAll),
		LangType(L"/",L".",Translate::trnsAll),
		LangType(L"?",L",",Translate::trnsAll),
		LangType(L"Q",L"É",Translate::trnsAll),
		LangType(L"W",L"Ö",Translate::trnsAll),
		LangType(L"E",L"Ó",Translate::trnsAll),
		LangType(L"R",L"Ê",Translate::trnsAll),
		LangType(L"T",L"Å",Translate::trnsAll),
		LangType(L"Y",L"Í",Translate::trnsAll),
		LangType(L"U",L"Ã",Translate::trnsAll),
		LangType(L"I",L"Ø",Translate::trnsAll),
		LangType(L"O",L"Ù",Translate::trnsAll),
		LangType(L"P",L"Ç",Translate::trnsAll),
		LangType(L"A",L"Ô",Translate::trnsAll),
		LangType(L"S",L"Û",Translate::trnsAll),
		LangType(L"D",L"Â",Translate::trnsAll),
		LangType(L"F",L"À",Translate::trnsAll),
		LangType(L"G",L"Ï",Translate::trnsAll),
		LangType(L"H",L"Ð",Translate::trnsAll),
		LangType(L"J",L"Î",Translate::trnsAll),
		LangType(L"K",L"Ë",Translate::trnsAll),
		LangType(L"L",L"Ä",Translate::trnsAll),
		LangType(L"Z",L"ß",Translate::trnsAll),
		LangType(L"X",L"×",Translate::trnsAll),
		LangType(L"C",L"Ñ",Translate::trnsAll),
		LangType(L"V",L"Ì",Translate::trnsAll),
		LangType(L"B",L"È",Translate::trnsAll),
		LangType(L"N",L"Ò",Translate::trnsAll),
		LangType(L"M",L"Ü",Translate::trnsAll),
	};
	rProfile.m_aSymbols.assign(aSymbols,
		aSymbols+sizeof(aSymbols)/sizeof(aSymbols[0]));

	// Name
	static const wchar_t strName[]=L"Symbols";
	rProfile.m_strName=strName;

	// Ignore
	rProfile.ResetIgnore();
}
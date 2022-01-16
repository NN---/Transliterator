#include "stdafx.h"

#include "language.h"

// QWER
void Language::Reset5(LangProfile& rProfile)
{
	ResetTranslation5(rProfile);
	ResetIgnore5(rProfile);
	ResetIgnoreText5(rProfile);
	ResetName5(rProfile);
}

void Language::ResetTranslation5(LangProfile& rProfile)
{
	static const LangTypeNS aTranslation[] = 
	{
		LangTypeNS(L"`",L"¸",Translate::trnsAll),
		LangTypeNS(L"~",L"¨",Translate::trnsAll),
		LangTypeNS(L"@",L"\"",Translate::trnsAll),
		LangTypeNS(L"#",L"¹",Translate::trnsAll),
		LangTypeNS(L"$",L";",Translate::trnsAll),
		LangTypeNS(L"^",L":",Translate::trnsAll),
		LangTypeNS(L"&",L"?",Translate::trnsAll),
		LangTypeNS(L"|",L"/",Translate::trnsAll),
		LangTypeNS(L"q",L"é",Translate::trnsAll),
		LangTypeNS(L"w",L"ö",Translate::trnsAll),
		LangTypeNS(L"e",L"ó",Translate::trnsAll),
		LangTypeNS(L"r",L"ê",Translate::trnsAll),
		LangTypeNS(L"t",L"å",Translate::trnsAll),
		LangTypeNS(L"y",L"í",Translate::trnsAll),
		LangTypeNS(L"u",L"ã",Translate::trnsAll),
		LangTypeNS(L"i",L"ø",Translate::trnsAll),
		LangTypeNS(L"o",L"ù",Translate::trnsAll),
		LangTypeNS(L"p",L"ç",Translate::trnsAll),
		LangTypeNS(L"[",L"õ",Translate::trnsAll),
		LangTypeNS(L"{",L"Õ",Translate::trnsAll),
		LangTypeNS(L"]",L"ú",Translate::trnsAll),
		LangTypeNS(L"}",L"Ú",Translate::trnsAll),
		LangTypeNS(L"a",L"ô",Translate::trnsAll),
		LangTypeNS(L"s",L"û",Translate::trnsAll),
		LangTypeNS(L"d",L"â",Translate::trnsAll),
		LangTypeNS(L"f",L"à",Translate::trnsAll),
		LangTypeNS(L"g",L"ï",Translate::trnsAll),
		LangTypeNS(L"h",L"ð",Translate::trnsAll),
		LangTypeNS(L"j",L"î",Translate::trnsAll),
		LangTypeNS(L"k",L"ë",Translate::trnsAll),
		LangTypeNS(L"l",L"ä",Translate::trnsAll),
		LangTypeNS(L";",L"æ",Translate::trnsAll),
		LangTypeNS(L":",L"Æ",Translate::trnsAll),
		LangTypeNS(L"'",L"ý",Translate::trnsAll),
		LangTypeNS(L"\"",L"Ý",Translate::trnsAll),
		LangTypeNS(L"z",L"ÿ",Translate::trnsAll),
		LangTypeNS(L"x",L"÷",Translate::trnsAll),
		LangTypeNS(L"c",L"ñ",Translate::trnsAll),
		LangTypeNS(L"v",L"ì",Translate::trnsAll),
		LangTypeNS(L"b",L"è",Translate::trnsAll),
		LangTypeNS(L"n",L"ò",Translate::trnsAll),
		LangTypeNS(L"m",L"ü",Translate::trnsAll),
		LangTypeNS(L",",L"á",Translate::trnsAll),
		LangTypeNS(L"<",L"Á",Translate::trnsAll),
		LangTypeNS(L".",L"þ",Translate::trnsAll),
		LangTypeNS(L">",L"Þ",Translate::trnsAll),
		LangTypeNS(L"/",L".",Translate::trnsAll),
		LangTypeNS(L"?",L",",Translate::trnsAll),
		LangTypeNS(L"Q",L"É",Translate::trnsAll),
		LangTypeNS(L"W",L"Ö",Translate::trnsAll),
		LangTypeNS(L"E",L"Ó",Translate::trnsAll),
		LangTypeNS(L"R",L"Ê",Translate::trnsAll),
		LangTypeNS(L"T",L"Å",Translate::trnsAll),
		LangTypeNS(L"Y",L"Í",Translate::trnsAll),
		LangTypeNS(L"U",L"Ã",Translate::trnsAll),
		LangTypeNS(L"I",L"Ø",Translate::trnsAll),
		LangTypeNS(L"O",L"Ù",Translate::trnsAll),
		LangTypeNS(L"P",L"Ç",Translate::trnsAll),
		LangTypeNS(L"A",L"Ô",Translate::trnsAll),
		LangTypeNS(L"S",L"Û",Translate::trnsAll),
		LangTypeNS(L"D",L"Â",Translate::trnsAll),
		LangTypeNS(L"F",L"À",Translate::trnsAll),
		LangTypeNS(L"G",L"Ï",Translate::trnsAll),
		LangTypeNS(L"H",L"Ð",Translate::trnsAll),
		LangTypeNS(L"J",L"Î",Translate::trnsAll),
		LangTypeNS(L"K",L"Ë",Translate::trnsAll),
		LangTypeNS(L"L",L"Ä",Translate::trnsAll),
		LangTypeNS(L"Z",L"ß",Translate::trnsAll),
		LangTypeNS(L"X",L"×",Translate::trnsAll),
		LangTypeNS(L"C",L"Ñ",Translate::trnsAll),
		LangTypeNS(L"V",L"Ì",Translate::trnsAll),
		LangTypeNS(L"B",L"È",Translate::trnsAll),
		LangTypeNS(L"N",L"Ò",Translate::trnsAll),
		LangTypeNS(L"M",L"Ü",Translate::trnsAll),
	};
	try
	{
		rProfile.m_aTranslation.assign(aTranslation, NN_ARRAY_END(aTranslation));
	}
	catch(...)
	{
		rProfile.ResetTranslation();
	}

}

void Language::ResetIgnore5(LangProfile& rProfile)
{
	rProfile.ResetIgnore();
}

void Language::ResetIgnoreText5(LangProfile& rProfile)
{
	rProfile.ResetIgnoreText();
}

void Language::ResetName5(LangProfile& rProfile)
{
	rProfile.m_astrLang[0] = "QWERTY";
	rProfile.m_astrLang[1] = "YCUKEN";
}
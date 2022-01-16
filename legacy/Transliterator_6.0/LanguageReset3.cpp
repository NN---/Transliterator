#include "stdafx.h"

#include "language.h"

// GOST
void Language::Reset3(LangProfile& rProfile)
{
	ResetTranslation3(rProfile);
	ResetIgnore3(rProfile);
	ResetIgnoreText3(rProfile);
	ResetName3(rProfile);
}

void Language::ResetTranslation3(LangProfile& rProfile)
{
	static const LangTypeNS aTranslation[] = 
	{
		LangTypeNS(L"a",L"à",Translate::trnsAll),
		LangTypeNS(L"A",L"À",Translate::trnsAll),
		LangTypeNS(L"b",L"á",Translate::trnsAll),
		LangTypeNS(L"B",L"Á",Translate::trnsAll),
		LangTypeNS(L"v",L"â",Translate::trnsAll),
		LangTypeNS(L"V",L"Â",Translate::trnsAll),
		LangTypeNS(L"w",L"â",Translate::trnsToptoBottom),
		LangTypeNS(L"W",L"Â",Translate::trnsToptoBottom),
		LangTypeNS(L"g",L"ã",Translate::trnsAll),
		LangTypeNS(L"G",L"Ã",Translate::trnsAll),
		LangTypeNS(L"d",L"ä",Translate::trnsAll),
		LangTypeNS(L"D",L"Ä",Translate::trnsAll),
		LangTypeNS(L"e",L"å",Translate::trnsAll),
		LangTypeNS(L"E",L"Å",Translate::trnsAll),
		LangTypeNS(L"jo",L"¸",Translate::trnsAll),
		LangTypeNS(L"jO",L"¸",Translate::trnsToptoBottom),
		LangTypeNS(L"JO",L"¨",Translate::trnsAll),
		LangTypeNS(L"Jo",L"¸",Translate::trnsToptoBottom),
		LangTypeNS(L"zh",L"æ",Translate::trnsAll),
		LangTypeNS(L"zH",L"æ",Translate::trnsToptoBottom),
		LangTypeNS(L"ZH",L"Æ",Translate::trnsAll),
		LangTypeNS(L"Zh",L"Æ",Translate::trnsToptoBottom),
		LangTypeNS(L"z",L"ç",Translate::trnsAll),
		LangTypeNS(L"Z",L"Ç",Translate::trnsAll),
		LangTypeNS(L"i",L"è",Translate::trnsAll),
		LangTypeNS(L"I",L"È",Translate::trnsAll),
		LangTypeNS(L"jj",L"é",Translate::trnsAll),
		LangTypeNS(L"jJ",L"é",Translate::trnsToptoBottom),
		LangTypeNS(L"JJ",L"É",Translate::trnsAll),
		LangTypeNS(L"Jj",L"É",Translate::trnsToptoBottom),
		LangTypeNS(L"k",L"ê",Translate::trnsAll),
		LangTypeNS(L"K",L"Ê",Translate::trnsAll),
		LangTypeNS(L"l",L"ë",Translate::trnsAll),
		LangTypeNS(L"L",L"Ë",Translate::trnsAll),
		LangTypeNS(L"m",L"ì",Translate::trnsAll),
		LangTypeNS(L"M",L"Ì",Translate::trnsAll),
		LangTypeNS(L"n",L"í",Translate::trnsAll),
		LangTypeNS(L"N",L"Í",Translate::trnsAll),
		LangTypeNS(L"o",L"î",Translate::trnsAll),
		LangTypeNS(L"O",L"Î",Translate::trnsAll),
		LangTypeNS(L"p",L"ï",Translate::trnsAll),
		LangTypeNS(L"P",L"Ï",Translate::trnsAll),
		LangTypeNS(L"r",L"ð",Translate::trnsAll),
		LangTypeNS(L"R",L"Ð",Translate::trnsAll),
		LangTypeNS(L"s",L"ñ",Translate::trnsAll),
		LangTypeNS(L"S",L"Ñ",Translate::trnsAll),
		LangTypeNS(L"t",L"ò",Translate::trnsAll),
		LangTypeNS(L"T",L"Ò",Translate::trnsAll),
		LangTypeNS(L"u",L"ó",Translate::trnsAll),
		LangTypeNS(L"U",L"Ó",Translate::trnsAll),
		LangTypeNS(L"f",L"ô",Translate::trnsAll),
		LangTypeNS(L"F",L"Ô",Translate::trnsAll),
		LangTypeNS(L"kh",L"õ",Translate::trnsAll),
		LangTypeNS(L"kH",L"õ",Translate::trnsToptoBottom),
		LangTypeNS(L"KH",L"Õ",Translate::trnsAll),
		LangTypeNS(L"Kh",L"Õ",Translate::trnsToptoBottom),
		LangTypeNS(L"c",L"ö",Translate::trnsAll),
		LangTypeNS(L"C",L"Ö",Translate::trnsAll),
		LangTypeNS(L"ch",L"÷",Translate::trnsAll),
		LangTypeNS(L"cH",L"÷",Translate::trnsToptoBottom),
		LangTypeNS(L"CH",L"×",Translate::trnsAll),
		LangTypeNS(L"Ch",L"×",Translate::trnsToptoBottom),
		LangTypeNS(L"sh",L"ø",Translate::trnsAll),
		LangTypeNS(L"sH",L"ø",Translate::trnsToptoBottom),
		LangTypeNS(L"SH",L"Ø",Translate::trnsAll),
		LangTypeNS(L"Sh",L"Ø",Translate::trnsToptoBottom),
		LangTypeNS(L"shh",L"ù",Translate::trnsAll),
		LangTypeNS(L"shH",L"ù",Translate::trnsToptoBottom),
		LangTypeNS(L"sHh",L"ù",Translate::trnsToptoBottom),
		LangTypeNS(L"sHH",L"ù",Translate::trnsToptoBottom),
		LangTypeNS(L"SHH",L"Ù",Translate::trnsAll),
		LangTypeNS(L"SHh",L"Ù",Translate::trnsToptoBottom),
		LangTypeNS(L"ShH",L"Ù",Translate::trnsToptoBottom),
		LangTypeNS(L"Shh",L"Ù",Translate::trnsToptoBottom),
		LangTypeNS(L"\"",L"ú",Translate::trnsAll),
		LangTypeNS(L"\"\"",L"Ú",Translate::trnsAll),
		LangTypeNS(L"y",L"û",Translate::trnsAll),
		LangTypeNS(L"Y",L"Û",Translate::trnsAll),
		LangTypeNS(L"'",L"ü",Translate::trnsAll),
		LangTypeNS(L"''",L"Ü",Translate::trnsAll),
		LangTypeNS(L"eh",L"ý",Translate::trnsAll),
		LangTypeNS(L"eH",L"ý",Translate::trnsToptoBottom),
		LangTypeNS(L"EH",L"Ý",Translate::trnsAll),
		LangTypeNS(L"Eh",L"Ý",Translate::trnsToptoBottom),
		LangTypeNS(L"ju",L"þ",Translate::trnsAll),
		LangTypeNS(L"jU",L"þ",Translate::trnsToptoBottom),
		LangTypeNS(L"JU",L"Þ",Translate::trnsAll),
		LangTypeNS(L"Ju",L"Þ",Translate::trnsToptoBottom),
		LangTypeNS(L"ja",L"ÿ",Translate::trnsAll),
		LangTypeNS(L"jA",L"ÿ",Translate::trnsToptoBottom),
		LangTypeNS(L"JA",L"ß",Translate::trnsAll),
		LangTypeNS(L"Ja",L"ß",Translate::trnsToptoBottom),
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

void Language::ResetIgnore3(LangProfile& rProfile)
{
	rProfile.ResetIgnore();
}

void Language::ResetIgnoreText3(LangProfile& rProfile)
{
	rProfile.ResetIgnoreText();
}

void Language::ResetName3(LangProfile& rProfile)
{
	rProfile.m_astrLang[0] = "Translit";
	rProfile.m_astrLang[1] = "Cyrillic";
}
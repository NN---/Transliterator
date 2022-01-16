#include "stdafx.h"

#include "language.h"

// Standard
void Language::Reset1(LangProfile& rProfile)
{
	ResetTranslation1(rProfile);
	ResetIgnore1(rProfile);
	ResetIgnoreText1(rProfile);
	ResetName1(rProfile);
}

void Language::ResetTranslation1(LangProfile& rProfile)
{
	static const LangTypeNS aTranslation[] = 
	{
		LangTypeNS(L"a",L"à",Translate::trnsAll),
		LangTypeNS(L"A",L"À",Translate::trnsAll),
		LangTypeNS(L"b",L"á",Translate::trnsAll),
		LangTypeNS(L"B",L"Á",Translate::trnsAll),
		LangTypeNS(L"c",L"ö",Translate::trnsAll),
		LangTypeNS(L"C",L"Ö",Translate::trnsAll),
		LangTypeNS(L"ch",L"÷",Translate::trnsAll),
		LangTypeNS(L"cH",L"÷",Translate::trnsToptoBottom),
		LangTypeNS(L"CH",L"×",Translate::trnsAll),
		LangTypeNS(L"Ch",L"×",Translate::trnsToptoBottom),
		LangTypeNS(L"d",L"ä",Translate::trnsAll),
		LangTypeNS(L"D",L"Ä",Translate::trnsAll),
		LangTypeNS(L"e",L"å",Translate::trnsAll),
		LangTypeNS(L"E",L"Å",Translate::trnsAll),
		LangTypeNS(L"e'",L"¸",Translate::trnsAll),
		LangTypeNS(L"E'",L"¨",Translate::trnsAll),
		LangTypeNS(L"e`",L"ý",Translate::trnsAll),
		LangTypeNS(L"E`",L"Ý",Translate::trnsAll),
		LangTypeNS(L"e''",L"º",Translate::trnsAll),
		LangTypeNS(L"E''",L"ª",Translate::trnsAll),
		LangTypeNS(L"f",L"ô",Translate::trnsAll),
		LangTypeNS(L"F",L"Ô",Translate::trnsAll),
		LangTypeNS(L"g",L"ã",Translate::trnsAll),
		LangTypeNS(L"G",L"Ã",Translate::trnsAll),
		LangTypeNS(L"g'`",L"´",Translate::trnsAll),
		LangTypeNS(L"g`'",L"´",Translate::trnsToptoBottom),
		LangTypeNS(L"G'`",L"¥",Translate::trnsAll),
		LangTypeNS(L"G`'",L"¥",Translate::trnsToptoBottom),
		LangTypeNS(L"h",L"õ",Translate::trnsAll),
		LangTypeNS(L"H",L"Õ",Translate::trnsAll),
		LangTypeNS(L"i",L"è",Translate::trnsAll),
		LangTypeNS(L"I",L"È",Translate::trnsAll),
		LangTypeNS(L"i'",L"³",Translate::trnsAll),
		LangTypeNS(L"I'",L"²",Translate::trnsAll),
		LangTypeNS(L"i`",L"¿",Translate::trnsAll),
		LangTypeNS(L"I`",L"¯",Translate::trnsAll),
		LangTypeNS(L"j",L"æ",Translate::trnsAll),
		LangTypeNS(L"J",L"Æ",Translate::trnsAll),
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
		LangTypeNS(L"q",L"û",Translate::trnsToptoBottom),
		LangTypeNS(L"Q",L"Û",Translate::trnsToptoBottom),
		LangTypeNS(L"r",L"ð",Translate::trnsAll),
		LangTypeNS(L"R",L"Ð",Translate::trnsAll),
		LangTypeNS(L"s",L"ñ",Translate::trnsAll),
		LangTypeNS(L"S",L"Ñ",Translate::trnsAll),
		LangTypeNS(L"sh",L"ø",Translate::trnsAll),
		LangTypeNS(L"sH",L"ø",Translate::trnsToptoBottom),
		LangTypeNS(L"SH",L"Ø",Translate::trnsAll),
		LangTypeNS(L"Sh",L"Ø",Translate::trnsToptoBottom),
		LangTypeNS(L"sh''",L"ù",Translate::trnsToptoBottom),
		LangTypeNS(L"sH''",L"ù",Translate::trnsToptoBottom),
		LangTypeNS(L"Sh''",L"Ù",Translate::trnsToptoBottom),
		LangTypeNS(L"SH''",L"Ù",Translate::trnsToptoBottom),
		LangTypeNS(L"sch'",L"ù",Translate::trnsAll),
		LangTypeNS(L"sCh'",L"ù",Translate::trnsToptoBottom),
		LangTypeNS(L"scH'",L"ù",Translate::trnsToptoBottom),
		LangTypeNS(L"sCH'",L"ù",Translate::trnsToptoBottom),
		LangTypeNS(L"Sch'",L"Ù",Translate::trnsToptoBottom),
		LangTypeNS(L"SCh'",L"Ù",Translate::trnsToptoBottom),
		LangTypeNS(L"ScH'",L"Ù",Translate::trnsToptoBottom),
		LangTypeNS(L"SCH'",L"Ù",Translate::trnsAll),
		LangTypeNS(L"t",L"ò",Translate::trnsAll),
		LangTypeNS(L"T",L"Ò",Translate::trnsAll),
		LangTypeNS(L"tc'",L"ö",Translate::trnsToptoBottom),
		LangTypeNS(L"tC'",L"ö",Translate::trnsToptoBottom),
		LangTypeNS(L"Tc'",L"Ö",Translate::trnsToptoBottom),
		LangTypeNS(L"TC'",L"Ö",Translate::trnsToptoBottom),
		LangTypeNS(L"u",L"ó",Translate::trnsAll),
		LangTypeNS(L"U",L"Ó",Translate::trnsAll),
		LangTypeNS(L"u'",L"¢",Translate::trnsAll),
		LangTypeNS(L"U'",L"¡",Translate::trnsAll),
		LangTypeNS(L"v",L"â",Translate::trnsAll),
		LangTypeNS(L"V",L"Â",Translate::trnsAll),
		LangTypeNS(L"w",L"ø",Translate::trnsToptoBottom),
		LangTypeNS(L"W",L"Ø",Translate::trnsToptoBottom),
		LangTypeNS(L"w''",L"ù",Translate::trnsToptoBottom),
		LangTypeNS(L"W''",L"Ù",Translate::trnsToptoBottom),
		LangTypeNS(L"x",L"õ",Translate::trnsToptoBottom),
		LangTypeNS(L"X",L"Õ",Translate::trnsToptoBottom),
		LangTypeNS(L"y",L"é",Translate::trnsAll),
		LangTypeNS(L"Y",L"É",Translate::trnsAll),
		LangTypeNS(L"ya",L"ÿ",Translate::trnsAll),
		LangTypeNS(L"yA",L"ÿ",Translate::trnsToptoBottom),
		LangTypeNS(L"YA",L"ß",Translate::trnsAll),
		LangTypeNS(L"Ya",L"ß",Translate::trnsToptoBottom),
		LangTypeNS(L"yu",L"þ",Translate::trnsAll),
		LangTypeNS(L"yU",L"þ",Translate::trnsToptoBottom),
		LangTypeNS(L"YU",L"Þ",Translate::trnsAll),
		LangTypeNS(L"Yu",L"Þ",Translate::trnsToptoBottom),
		LangTypeNS(L"y'",L"û",Translate::trnsAll),
		LangTypeNS(L"Y'",L"Û",Translate::trnsAll),
		LangTypeNS(L"z",L"ç",Translate::trnsAll),
		LangTypeNS(L"Z",L"Ç",Translate::trnsAll),
		LangTypeNS(L"'",L"ü",Translate::trnsAll),
		LangTypeNS(L"''",L"Ü",Translate::trnsAll),
		LangTypeNS(L"`",L"ú",Translate::trnsAll),
		LangTypeNS(L"``",L"Ú",Translate::trnsAll),
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

void Language::ResetIgnore1(LangProfile& rProfile)
{
	rProfile.ResetIgnore();
}

void Language::ResetIgnoreText1(LangProfile& rProfile)
{
	rProfile.ResetIgnoreText();
}

void Language::ResetName1(LangProfile& rProfile)
{
	rProfile.m_astrLang[0] = "Translit";
	rProfile.m_astrLang[1] = "Cyrillic";
}
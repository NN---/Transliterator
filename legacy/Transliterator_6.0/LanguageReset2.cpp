#include "stdafx.h"

#include "language.h"

// Fonetic
void Language::Reset2(LangProfile& rProfile)
{
	ResetTranslation2(rProfile);
	ResetIgnore2(rProfile);
	ResetIgnoreText2(rProfile);
	ResetName2(rProfile);
}

void Language::ResetTranslation2(LangProfile& rProfile)
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
		LangTypeNS(L"e",L"¸",Translate::trnsBottomtoTop),
		LangTypeNS(L"E",L"¨",Translate::trnsBottomtoTop),
		LangTypeNS(L"e",L"ý",Translate::trnsBottomtoTop),
		LangTypeNS(L"E",L"Ý",Translate::trnsBottomtoTop),
		LangTypeNS(L"f",L"ô",Translate::trnsAll),
		LangTypeNS(L"F",L"Ô",Translate::trnsAll),
		LangTypeNS(L"g",L"ã",Translate::trnsAll),
		LangTypeNS(L"G",L"Ã",Translate::trnsAll),
		LangTypeNS(L"h",L"õ",Translate::trnsAll),
		LangTypeNS(L"H",L"Õ",Translate::trnsAll),
		LangTypeNS(L"i",L"è",Translate::trnsAll),
		LangTypeNS(L"I",L"È",Translate::trnsAll),
		LangTypeNS(L"i",L"û",Translate::trnsBottomtoTop),
		LangTypeNS(L"I",L"Û",Translate::trnsBottomtoTop),
		LangTypeNS(L"j",L"æ",Translate::trnsToptoBottom),
		LangTypeNS(L"J",L"Æ",Translate::trnsToptoBottom),
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
		LangTypeNS(L"sh",L"ø",Translate::trnsAll),
		LangTypeNS(L"sH",L"ø",Translate::trnsToptoBottom),
		LangTypeNS(L"SH",L"Ø",Translate::trnsAll),
		LangTypeNS(L"sch",L"ù",Translate::trnsAll),
		LangTypeNS(L"sCh",L"ù",Translate::trnsToptoBottom),
		LangTypeNS(L"scH",L"ù",Translate::trnsToptoBottom),
		LangTypeNS(L"sCH",L"ù",Translate::trnsToptoBottom),
		LangTypeNS(L"Sch",L"Ù",Translate::trnsToptoBottom),
		LangTypeNS(L"SCh",L"Ù",Translate::trnsToptoBottom),
		LangTypeNS(L"ScH",L"Ù",Translate::trnsToptoBottom),
		LangTypeNS(L"SCH",L"Ù",Translate::trnsAll),
		LangTypeNS(L"t",L"ò",Translate::trnsAll),
		LangTypeNS(L"T",L"Ò",Translate::trnsAll),
		LangTypeNS(L"tc",L"ö",Translate::trnsToptoBottom),
		LangTypeNS(L"tC",L"ö",Translate::trnsToptoBottom),
		LangTypeNS(L"Tc",L"Ö",Translate::trnsToptoBottom),
		LangTypeNS(L"TC",L"Ö",Translate::trnsToptoBottom),
		LangTypeNS(L"u",L"ó",Translate::trnsAll),
		LangTypeNS(L"U",L"Ó",Translate::trnsAll),
		LangTypeNS(L"v",L"â",Translate::trnsAll),
		LangTypeNS(L"V",L"Â",Translate::trnsAll),
		LangTypeNS(L"w",L"ø",Translate::trnsToptoBottom),
		LangTypeNS(L"W",L"Ø",Translate::trnsToptoBottom),
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
		LangTypeNS(L"z",L"ç",Translate::trnsAll),
		LangTypeNS(L"Z",L"Ç",Translate::trnsAll),
		LangTypeNS(L"zh",L"æ",Translate::trnsAll),
		LangTypeNS(L"zH",L"æ",Translate::trnsToptoBottom),
		LangTypeNS(L"ZH",L"Æ",Translate::trnsAll),
		LangTypeNS(L"Zh",L"Æ",Translate::trnsToptoBottom),
		LangTypeNS(L"'",L"ü",Translate::trnsAll),
		LangTypeNS(L"'",L"Ü",Translate::trnsBottomtoTop),
		LangTypeNS(L"'",L"ú",Translate::trnsBottomtoTop),
		LangTypeNS(L"'",L"Ú",Translate::trnsBottomtoTop),
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

void Language::ResetIgnore2(LangProfile& rProfile)
{
	rProfile.ResetIgnore();
}

void Language::ResetIgnoreText2(LangProfile& rProfile)
{
	rProfile.ResetIgnoreText();
}

void Language::ResetName2(LangProfile& rProfile)
{
	rProfile.m_astrLang[0] = "Translit";
	rProfile.m_astrLang[1] = "Cyrillic";
}
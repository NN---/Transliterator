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
		LangTypeNS(L"a",L"�",Translate::trnsAll),
		LangTypeNS(L"A",L"�",Translate::trnsAll),
		LangTypeNS(L"b",L"�",Translate::trnsAll),
		LangTypeNS(L"B",L"�",Translate::trnsAll),
		LangTypeNS(L"c",L"�",Translate::trnsAll),
		LangTypeNS(L"C",L"�",Translate::trnsAll),
		LangTypeNS(L"ch",L"�",Translate::trnsAll),
		LangTypeNS(L"cH",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"CH",L"�",Translate::trnsAll),
		LangTypeNS(L"Ch",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"d",L"�",Translate::trnsAll),
		LangTypeNS(L"D",L"�",Translate::trnsAll),
		LangTypeNS(L"e",L"�",Translate::trnsAll),
		LangTypeNS(L"E",L"�",Translate::trnsAll),
		LangTypeNS(L"e",L"�",Translate::trnsBottomtoTop),
		LangTypeNS(L"E",L"�",Translate::trnsBottomtoTop),
		LangTypeNS(L"e",L"�",Translate::trnsBottomtoTop),
		LangTypeNS(L"E",L"�",Translate::trnsBottomtoTop),
		LangTypeNS(L"f",L"�",Translate::trnsAll),
		LangTypeNS(L"F",L"�",Translate::trnsAll),
		LangTypeNS(L"g",L"�",Translate::trnsAll),
		LangTypeNS(L"G",L"�",Translate::trnsAll),
		LangTypeNS(L"h",L"�",Translate::trnsAll),
		LangTypeNS(L"H",L"�",Translate::trnsAll),
		LangTypeNS(L"i",L"�",Translate::trnsAll),
		LangTypeNS(L"I",L"�",Translate::trnsAll),
		LangTypeNS(L"i",L"�",Translate::trnsBottomtoTop),
		LangTypeNS(L"I",L"�",Translate::trnsBottomtoTop),
		LangTypeNS(L"j",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"J",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"k",L"�",Translate::trnsAll),
		LangTypeNS(L"K",L"�",Translate::trnsAll),
		LangTypeNS(L"l",L"�",Translate::trnsAll),
		LangTypeNS(L"L",L"�",Translate::trnsAll),
		LangTypeNS(L"m",L"�",Translate::trnsAll),
		LangTypeNS(L"M",L"�",Translate::trnsAll),
		LangTypeNS(L"n",L"�",Translate::trnsAll),
		LangTypeNS(L"N",L"�",Translate::trnsAll),
		LangTypeNS(L"o",L"�",Translate::trnsAll),
		LangTypeNS(L"O",L"�",Translate::trnsAll),
		LangTypeNS(L"p",L"�",Translate::trnsAll),
		LangTypeNS(L"P",L"�",Translate::trnsAll),
		LangTypeNS(L"r",L"�",Translate::trnsAll),
		LangTypeNS(L"R",L"�",Translate::trnsAll),
		LangTypeNS(L"s",L"�",Translate::trnsAll),
		LangTypeNS(L"S",L"�",Translate::trnsAll),
		LangTypeNS(L"sh",L"�",Translate::trnsAll),
		LangTypeNS(L"sH",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"SH",L"�",Translate::trnsAll),
		LangTypeNS(L"sch",L"�",Translate::trnsAll),
		LangTypeNS(L"sCh",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"scH",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"sCH",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"Sch",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"SCh",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"ScH",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"SCH",L"�",Translate::trnsAll),
		LangTypeNS(L"t",L"�",Translate::trnsAll),
		LangTypeNS(L"T",L"�",Translate::trnsAll),
		LangTypeNS(L"tc",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"tC",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"Tc",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"TC",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"u",L"�",Translate::trnsAll),
		LangTypeNS(L"U",L"�",Translate::trnsAll),
		LangTypeNS(L"v",L"�",Translate::trnsAll),
		LangTypeNS(L"V",L"�",Translate::trnsAll),
		LangTypeNS(L"w",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"W",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"x",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"X",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"y",L"�",Translate::trnsAll),
		LangTypeNS(L"Y",L"�",Translate::trnsAll),
		LangTypeNS(L"ya",L"�",Translate::trnsAll),
		LangTypeNS(L"yA",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"YA",L"�",Translate::trnsAll),
		LangTypeNS(L"Ya",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"yu",L"�",Translate::trnsAll),
		LangTypeNS(L"yU",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"YU",L"�",Translate::trnsAll),
		LangTypeNS(L"Yu",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"z",L"�",Translate::trnsAll),
		LangTypeNS(L"Z",L"�",Translate::trnsAll),
		LangTypeNS(L"zh",L"�",Translate::trnsAll),
		LangTypeNS(L"zH",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"ZH",L"�",Translate::trnsAll),
		LangTypeNS(L"Zh",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"'",L"�",Translate::trnsAll),
		LangTypeNS(L"'",L"�",Translate::trnsBottomtoTop),
		LangTypeNS(L"'",L"�",Translate::trnsBottomtoTop),
		LangTypeNS(L"'",L"�",Translate::trnsBottomtoTop),
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
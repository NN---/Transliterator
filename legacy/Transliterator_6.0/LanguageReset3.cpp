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
		LangTypeNS(L"a",L"�",Translate::trnsAll),
		LangTypeNS(L"A",L"�",Translate::trnsAll),
		LangTypeNS(L"b",L"�",Translate::trnsAll),
		LangTypeNS(L"B",L"�",Translate::trnsAll),
		LangTypeNS(L"v",L"�",Translate::trnsAll),
		LangTypeNS(L"V",L"�",Translate::trnsAll),
		LangTypeNS(L"w",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"W",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"g",L"�",Translate::trnsAll),
		LangTypeNS(L"G",L"�",Translate::trnsAll),
		LangTypeNS(L"d",L"�",Translate::trnsAll),
		LangTypeNS(L"D",L"�",Translate::trnsAll),
		LangTypeNS(L"e",L"�",Translate::trnsAll),
		LangTypeNS(L"E",L"�",Translate::trnsAll),
		LangTypeNS(L"jo",L"�",Translate::trnsAll),
		LangTypeNS(L"jO",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"JO",L"�",Translate::trnsAll),
		LangTypeNS(L"Jo",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"zh",L"�",Translate::trnsAll),
		LangTypeNS(L"zH",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"ZH",L"�",Translate::trnsAll),
		LangTypeNS(L"Zh",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"z",L"�",Translate::trnsAll),
		LangTypeNS(L"Z",L"�",Translate::trnsAll),
		LangTypeNS(L"i",L"�",Translate::trnsAll),
		LangTypeNS(L"I",L"�",Translate::trnsAll),
		LangTypeNS(L"jj",L"�",Translate::trnsAll),
		LangTypeNS(L"jJ",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"JJ",L"�",Translate::trnsAll),
		LangTypeNS(L"Jj",L"�",Translate::trnsToptoBottom),
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
		LangTypeNS(L"t",L"�",Translate::trnsAll),
		LangTypeNS(L"T",L"�",Translate::trnsAll),
		LangTypeNS(L"u",L"�",Translate::trnsAll),
		LangTypeNS(L"U",L"�",Translate::trnsAll),
		LangTypeNS(L"f",L"�",Translate::trnsAll),
		LangTypeNS(L"F",L"�",Translate::trnsAll),
		LangTypeNS(L"kh",L"�",Translate::trnsAll),
		LangTypeNS(L"kH",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"KH",L"�",Translate::trnsAll),
		LangTypeNS(L"Kh",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"c",L"�",Translate::trnsAll),
		LangTypeNS(L"C",L"�",Translate::trnsAll),
		LangTypeNS(L"ch",L"�",Translate::trnsAll),
		LangTypeNS(L"cH",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"CH",L"�",Translate::trnsAll),
		LangTypeNS(L"Ch",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"sh",L"�",Translate::trnsAll),
		LangTypeNS(L"sH",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"SH",L"�",Translate::trnsAll),
		LangTypeNS(L"Sh",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"shh",L"�",Translate::trnsAll),
		LangTypeNS(L"shH",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"sHh",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"sHH",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"SHH",L"�",Translate::trnsAll),
		LangTypeNS(L"SHh",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"ShH",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"Shh",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"\"",L"�",Translate::trnsAll),
		LangTypeNS(L"\"\"",L"�",Translate::trnsAll),
		LangTypeNS(L"y",L"�",Translate::trnsAll),
		LangTypeNS(L"Y",L"�",Translate::trnsAll),
		LangTypeNS(L"'",L"�",Translate::trnsAll),
		LangTypeNS(L"''",L"�",Translate::trnsAll),
		LangTypeNS(L"eh",L"�",Translate::trnsAll),
		LangTypeNS(L"eH",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"EH",L"�",Translate::trnsAll),
		LangTypeNS(L"Eh",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"ju",L"�",Translate::trnsAll),
		LangTypeNS(L"jU",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"JU",L"�",Translate::trnsAll),
		LangTypeNS(L"Ju",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"ja",L"�",Translate::trnsAll),
		LangTypeNS(L"jA",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"JA",L"�",Translate::trnsAll),
		LangTypeNS(L"Ja",L"�",Translate::trnsToptoBottom),
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
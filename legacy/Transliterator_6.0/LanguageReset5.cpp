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
		LangTypeNS(L"`",L"�",Translate::trnsAll),
		LangTypeNS(L"~",L"�",Translate::trnsAll),
		LangTypeNS(L"@",L"\"",Translate::trnsAll),
		LangTypeNS(L"#",L"�",Translate::trnsAll),
		LangTypeNS(L"$",L";",Translate::trnsAll),
		LangTypeNS(L"^",L":",Translate::trnsAll),
		LangTypeNS(L"&",L"?",Translate::trnsAll),
		LangTypeNS(L"|",L"/",Translate::trnsAll),
		LangTypeNS(L"q",L"�",Translate::trnsAll),
		LangTypeNS(L"w",L"�",Translate::trnsAll),
		LangTypeNS(L"e",L"�",Translate::trnsAll),
		LangTypeNS(L"r",L"�",Translate::trnsAll),
		LangTypeNS(L"t",L"�",Translate::trnsAll),
		LangTypeNS(L"y",L"�",Translate::trnsAll),
		LangTypeNS(L"u",L"�",Translate::trnsAll),
		LangTypeNS(L"i",L"�",Translate::trnsAll),
		LangTypeNS(L"o",L"�",Translate::trnsAll),
		LangTypeNS(L"p",L"�",Translate::trnsAll),
		LangTypeNS(L"[",L"�",Translate::trnsAll),
		LangTypeNS(L"{",L"�",Translate::trnsAll),
		LangTypeNS(L"]",L"�",Translate::trnsAll),
		LangTypeNS(L"}",L"�",Translate::trnsAll),
		LangTypeNS(L"a",L"�",Translate::trnsAll),
		LangTypeNS(L"s",L"�",Translate::trnsAll),
		LangTypeNS(L"d",L"�",Translate::trnsAll),
		LangTypeNS(L"f",L"�",Translate::trnsAll),
		LangTypeNS(L"g",L"�",Translate::trnsAll),
		LangTypeNS(L"h",L"�",Translate::trnsAll),
		LangTypeNS(L"j",L"�",Translate::trnsAll),
		LangTypeNS(L"k",L"�",Translate::trnsAll),
		LangTypeNS(L"l",L"�",Translate::trnsAll),
		LangTypeNS(L";",L"�",Translate::trnsAll),
		LangTypeNS(L":",L"�",Translate::trnsAll),
		LangTypeNS(L"'",L"�",Translate::trnsAll),
		LangTypeNS(L"\"",L"�",Translate::trnsAll),
		LangTypeNS(L"z",L"�",Translate::trnsAll),
		LangTypeNS(L"x",L"�",Translate::trnsAll),
		LangTypeNS(L"c",L"�",Translate::trnsAll),
		LangTypeNS(L"v",L"�",Translate::trnsAll),
		LangTypeNS(L"b",L"�",Translate::trnsAll),
		LangTypeNS(L"n",L"�",Translate::trnsAll),
		LangTypeNS(L"m",L"�",Translate::trnsAll),
		LangTypeNS(L",",L"�",Translate::trnsAll),
		LangTypeNS(L"<",L"�",Translate::trnsAll),
		LangTypeNS(L".",L"�",Translate::trnsAll),
		LangTypeNS(L">",L"�",Translate::trnsAll),
		LangTypeNS(L"/",L".",Translate::trnsAll),
		LangTypeNS(L"?",L",",Translate::trnsAll),
		LangTypeNS(L"Q",L"�",Translate::trnsAll),
		LangTypeNS(L"W",L"�",Translate::trnsAll),
		LangTypeNS(L"E",L"�",Translate::trnsAll),
		LangTypeNS(L"R",L"�",Translate::trnsAll),
		LangTypeNS(L"T",L"�",Translate::trnsAll),
		LangTypeNS(L"Y",L"�",Translate::trnsAll),
		LangTypeNS(L"U",L"�",Translate::trnsAll),
		LangTypeNS(L"I",L"�",Translate::trnsAll),
		LangTypeNS(L"O",L"�",Translate::trnsAll),
		LangTypeNS(L"P",L"�",Translate::trnsAll),
		LangTypeNS(L"A",L"�",Translate::trnsAll),
		LangTypeNS(L"S",L"�",Translate::trnsAll),
		LangTypeNS(L"D",L"�",Translate::trnsAll),
		LangTypeNS(L"F",L"�",Translate::trnsAll),
		LangTypeNS(L"G",L"�",Translate::trnsAll),
		LangTypeNS(L"H",L"�",Translate::trnsAll),
		LangTypeNS(L"J",L"�",Translate::trnsAll),
		LangTypeNS(L"K",L"�",Translate::trnsAll),
		LangTypeNS(L"L",L"�",Translate::trnsAll),
		LangTypeNS(L"Z",L"�",Translate::trnsAll),
		LangTypeNS(L"X",L"�",Translate::trnsAll),
		LangTypeNS(L"C",L"�",Translate::trnsAll),
		LangTypeNS(L"V",L"�",Translate::trnsAll),
		LangTypeNS(L"B",L"�",Translate::trnsAll),
		LangTypeNS(L"N",L"�",Translate::trnsAll),
		LangTypeNS(L"M",L"�",Translate::trnsAll),
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
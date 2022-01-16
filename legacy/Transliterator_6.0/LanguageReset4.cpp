#include "stdafx.h"

#include "language.h"

// Symbols
void Language::Reset4(LangProfile& rProfile)
{
	ResetTranslation4(rProfile);
	ResetIgnore4(rProfile);
	ResetIgnoreText4(rProfile);
	ResetName4(rProfile);
}

void Language::ResetTranslation4(LangProfile& rProfile)
{
	// Symbols
	static const LangTypeNS aTranslation[] = 
	{
		LangTypeNS(L"a",L"�",Translate::trnsAll),
		LangTypeNS(L"A",L"�",Translate::trnsAll),
		LangTypeNS(L"6",L"�",Translate::trnsAll),
		LangTypeNS(L"6",L"�",Translate::trnsBottomtoTop),
		LangTypeNS(L"B",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsBottomtoTop),
		LangTypeNS(L"r",L"�",Translate::trnsAll),
		LangTypeNS(L"r",L"�",Translate::trnsBottomtoTop),
		LangTypeNS(L"D",L"�",Translate::trnsAll),
		LangTypeNS(L"D",L"�",Translate::trnsBottomtoTop),
		LangTypeNS(L"e",L"�",Translate::trnsAll),
		LangTypeNS(L"E",L"�",Translate::trnsAll),
		LangTypeNS(L"e",L"�",Translate::trnsBottomtoTop),
		LangTypeNS(L"E",L"�",Translate::trnsBottomtoTop),
		LangTypeNS(L">|<",L"�",Translate::trnsAll),
		LangTypeNS(L"}|{",L"�",Translate::trnsAll),
		LangTypeNS(L">-|-<",L"�",Translate::trnsBottomtoTop),
		LangTypeNS(L"}-|-{",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"3",L"�",Translate::trnsAll),
		LangTypeNS(L"3",L"�",Translate::trnsBottomtoTop),
		LangTypeNS(L"u",L"�",Translate::trnsAll),
		LangTypeNS(L"U",L"�",Translate::trnsAll),
		LangTypeNS(L"u'",L"�",Translate::trnsAll),
		LangTypeNS(L"U'",L"�",Translate::trnsAll),
		LangTypeNS(L"u`",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"U`",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"k",L"�",Translate::trnsAll),
		LangTypeNS(L"K",L"�",Translate::trnsAll),
		LangTypeNS(L"/\\",L"�",Translate::trnsAll),
		LangTypeNS(L"JI",L"�",Translate::trnsAll),
		LangTypeNS(L"m",L"�",Translate::trnsAll),
		LangTypeNS(L"M",L"�",Translate::trnsAll),
		LangTypeNS(L"H",L"�",Translate::trnsAll),
		LangTypeNS(L"H",L"�",Translate::trnsBottomtoTop),
		LangTypeNS(L"o",L"�",Translate::trnsAll),
		LangTypeNS(L"O",L"�",Translate::trnsAll),
		LangTypeNS(L"n",L"�",Translate::trnsAll),
		LangTypeNS(L"n",L"�",Translate::trnsBottomtoTop),
		LangTypeNS(L"p",L"�",Translate::trnsAll),
		LangTypeNS(L"P",L"�",Translate::trnsAll),
		LangTypeNS(L"c",L"�",Translate::trnsAll),
		LangTypeNS(L"C",L"�",Translate::trnsAll),
		LangTypeNS(L"T",L"�",Translate::trnsAll),
		LangTypeNS(L"T",L"�",Translate::trnsBottomtoTop),
		LangTypeNS(L"y",L"�",Translate::trnsAll),
		LangTypeNS(L"Y",L"�",Translate::trnsAll),
		LangTypeNS(L"f",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"F",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"(|)",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"(I)",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"<|>",L"�",Translate::trnsAll),
		LangTypeNS(L"<I>",L"�",Translate::trnsAll),
		LangTypeNS(L"x",L"�",Translate::trnsAll),
		LangTypeNS(L"X",L"�",Translate::trnsAll),
		LangTypeNS(L"L|",L"�",Translate::trnsAll),
		LangTypeNS(L"L|",L"�",Translate::trnsBottomtoTop),
		LangTypeNS(L"4",L"�",Translate::trnsAll),
		LangTypeNS(L"4",L"�",Translate::trnsBottomtoTop),
		LangTypeNS(L"LLI",L"�",Translate::trnsAll),
		LangTypeNS(L"w",L"�",Translate::trnsAll),
		LangTypeNS(L"LL|",L"�",Translate::trnsAll),
		LangTypeNS(L"LL|",L"�",Translate::trnsBottomtoTop),
		LangTypeNS(L"\\",L"�",Translate::trnsAll),
		LangTypeNS(L"\\\\",L"�",Translate::trnsBottomtoTop),
		LangTypeNS(L"bI",L"�",Translate::trnsAll),
		LangTypeNS(L"bI",L"�",Translate::trnsBottomtoTop),
		LangTypeNS(L"b",L"�",Translate::trnsAll),
		LangTypeNS(L"b",L"�",Translate::trnsBottomtoTop),
		LangTypeNS(L"e",L"�",Translate::trnsBottomtoTop),
		LangTypeNS(L"E",L"�",Translate::trnsBottomtoTop),
		LangTypeNS(L"IO",L"�",Translate::trnsAll),
		LangTypeNS(L"IO",L"�",Translate::trnsBottomtoTop),
		LangTypeNS(L"I-O",L"�",Translate::trnsToptoBottom),
		LangTypeNS(L"I-O",L"�",Translate::trnsBottomtoTop),
		LangTypeNS(L"9I",L"�",Translate::trnsAll),
		LangTypeNS(L"9I",L"�",Translate::trnsBottomtoTop),
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

void Language::ResetIgnore4(LangProfile& rProfile)
{
	rProfile.ResetIgnore();
}

void Language::ResetIgnoreText4(LangProfile& rProfile)
{
	rProfile.ResetIgnoreText();
}

void Language::ResetName4(LangProfile& rProfile)
{
	// Lang
	rProfile.m_astrLang[0] = "Symbols";
	rProfile.m_astrLang[1] = "Cyrillic";
}
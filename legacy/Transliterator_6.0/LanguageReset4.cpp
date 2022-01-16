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
		LangTypeNS(L"a",L"à",Translate::trnsAll),
		LangTypeNS(L"A",L"À",Translate::trnsAll),
		LangTypeNS(L"6",L"á",Translate::trnsAll),
		LangTypeNS(L"6",L"Á",Translate::trnsBottomtoTop),
		LangTypeNS(L"B",L"Â",Translate::trnsAll),
		LangTypeNS(L"Â",L"â",Translate::trnsBottomtoTop),
		LangTypeNS(L"r",L"ã",Translate::trnsAll),
		LangTypeNS(L"r",L"Ã",Translate::trnsBottomtoTop),
		LangTypeNS(L"D",L"ä",Translate::trnsAll),
		LangTypeNS(L"D",L"Ä",Translate::trnsBottomtoTop),
		LangTypeNS(L"e",L"å",Translate::trnsAll),
		LangTypeNS(L"E",L"Å",Translate::trnsAll),
		LangTypeNS(L"e",L"¸",Translate::trnsBottomtoTop),
		LangTypeNS(L"E",L"¨",Translate::trnsBottomtoTop),
		LangTypeNS(L">|<",L"æ",Translate::trnsAll),
		LangTypeNS(L"}|{",L"Æ",Translate::trnsAll),
		LangTypeNS(L">-|-<",L"æ",Translate::trnsBottomtoTop),
		LangTypeNS(L"}-|-{",L"Æ",Translate::trnsToptoBottom),
		LangTypeNS(L"3",L"ç",Translate::trnsAll),
		LangTypeNS(L"3",L"Ç",Translate::trnsBottomtoTop),
		LangTypeNS(L"u",L"è",Translate::trnsAll),
		LangTypeNS(L"U",L"È",Translate::trnsAll),
		LangTypeNS(L"u'",L"é",Translate::trnsAll),
		LangTypeNS(L"U'",L"É",Translate::trnsAll),
		LangTypeNS(L"u`",L"é",Translate::trnsToptoBottom),
		LangTypeNS(L"U`",L"É",Translate::trnsToptoBottom),
		LangTypeNS(L"k",L"ê",Translate::trnsAll),
		LangTypeNS(L"K",L"Ê",Translate::trnsAll),
		LangTypeNS(L"/\\",L"ë",Translate::trnsAll),
		LangTypeNS(L"JI",L"Ë",Translate::trnsAll),
		LangTypeNS(L"m",L"ì",Translate::trnsAll),
		LangTypeNS(L"M",L"Ì",Translate::trnsAll),
		LangTypeNS(L"H",L"í",Translate::trnsAll),
		LangTypeNS(L"H",L"Í",Translate::trnsBottomtoTop),
		LangTypeNS(L"o",L"î",Translate::trnsAll),
		LangTypeNS(L"O",L"Î",Translate::trnsAll),
		LangTypeNS(L"n",L"ï",Translate::trnsAll),
		LangTypeNS(L"n",L"Ï",Translate::trnsBottomtoTop),
		LangTypeNS(L"p",L"ð",Translate::trnsAll),
		LangTypeNS(L"P",L"Ð",Translate::trnsAll),
		LangTypeNS(L"c",L"ñ",Translate::trnsAll),
		LangTypeNS(L"C",L"Ñ",Translate::trnsAll),
		LangTypeNS(L"T",L"ò",Translate::trnsAll),
		LangTypeNS(L"T",L"Ò",Translate::trnsBottomtoTop),
		LangTypeNS(L"y",L"ó",Translate::trnsAll),
		LangTypeNS(L"Y",L"Ó",Translate::trnsAll),
		LangTypeNS(L"f",L"ô",Translate::trnsToptoBottom),
		LangTypeNS(L"F",L"Ô",Translate::trnsToptoBottom),
		LangTypeNS(L"(|)",L"ô",Translate::trnsToptoBottom),
		LangTypeNS(L"(I)",L"Ô",Translate::trnsToptoBottom),
		LangTypeNS(L"<|>",L"ô",Translate::trnsAll),
		LangTypeNS(L"<I>",L"Ô",Translate::trnsAll),
		LangTypeNS(L"x",L"õ",Translate::trnsAll),
		LangTypeNS(L"X",L"Õ",Translate::trnsAll),
		LangTypeNS(L"L|",L"ö",Translate::trnsAll),
		LangTypeNS(L"L|",L"Ö",Translate::trnsBottomtoTop),
		LangTypeNS(L"4",L"÷",Translate::trnsAll),
		LangTypeNS(L"4",L"×",Translate::trnsBottomtoTop),
		LangTypeNS(L"LLI",L"Ø",Translate::trnsAll),
		LangTypeNS(L"w",L"ø",Translate::trnsAll),
		LangTypeNS(L"LL|",L"ù",Translate::trnsAll),
		LangTypeNS(L"LL|",L"Ù",Translate::trnsBottomtoTop),
		LangTypeNS(L"\\",L"ú",Translate::trnsAll),
		LangTypeNS(L"\\\\",L"Ú",Translate::trnsBottomtoTop),
		LangTypeNS(L"bI",L"û",Translate::trnsAll),
		LangTypeNS(L"bI",L"Û",Translate::trnsBottomtoTop),
		LangTypeNS(L"b",L"ü",Translate::trnsAll),
		LangTypeNS(L"b",L"Ü",Translate::trnsBottomtoTop),
		LangTypeNS(L"e",L"ý",Translate::trnsBottomtoTop),
		LangTypeNS(L"E",L"Ý",Translate::trnsBottomtoTop),
		LangTypeNS(L"IO",L"þ",Translate::trnsAll),
		LangTypeNS(L"IO",L"Þ",Translate::trnsBottomtoTop),
		LangTypeNS(L"I-O",L"þ",Translate::trnsToptoBottom),
		LangTypeNS(L"I-O",L"Þ",Translate::trnsBottomtoTop),
		LangTypeNS(L"9I",L"ÿ",Translate::trnsAll),
		LangTypeNS(L"9I",L"ß",Translate::trnsBottomtoTop),
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
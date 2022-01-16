#include "stdafx.h"

#include "language.h"

// KOI8-R-Win
void Language::Reset7(LangProfile& rProfile)
{
	ResetTranslation7(rProfile);
	ResetIgnore7(rProfile);
	ResetIgnoreText7(rProfile);
	ResetName7(rProfile);
}

void Language::ResetTranslation7(LangProfile& rProfile)
{
	static const LangTypeNS aTranslation[] = 
	{
		LangTypeNS(L"Á",L"à",Translate::trnsAll),
		LangTypeNS(L"Â",L"á",Translate::trnsAll),
		LangTypeNS(L"×",L"â",Translate::trnsAll),
		LangTypeNS(L"Ç",L"ã",Translate::trnsAll),
		LangTypeNS(L"Ä",L"ä",Translate::trnsAll),
		LangTypeNS(L"Å",L"å",Translate::trnsAll),
		LangTypeNS(L"Ö",L"æ",Translate::trnsAll),
		LangTypeNS(L"Ú",L"ç",Translate::trnsAll),
		LangTypeNS(L"É",L"è",Translate::trnsAll),
		LangTypeNS(L"Ê",L"é",Translate::trnsAll),
		LangTypeNS(L"Ë",L"ê",Translate::trnsAll),
		LangTypeNS(L"Ì",L"ë",Translate::trnsAll),
		LangTypeNS(L"Í",L"ì",Translate::trnsAll),
		LangTypeNS(L"Î",L"í",Translate::trnsAll),
		LangTypeNS(L"Ï",L"î",Translate::trnsAll),
		LangTypeNS(L"Ð",L"ï",Translate::trnsAll),
		LangTypeNS(L"Ò",L"ð",Translate::trnsAll),
		LangTypeNS(L"Ó",L"ñ",Translate::trnsAll),
		LangTypeNS(L"Ô",L"ò",Translate::trnsAll),
		LangTypeNS(L"Õ",L"ó",Translate::trnsAll),
		LangTypeNS(L"Æ",L"ô",Translate::trnsAll),
		LangTypeNS(L"È",L"õ",Translate::trnsAll),
		LangTypeNS(L"Ã",L"ö",Translate::trnsAll),
		LangTypeNS(L"Þ",L"÷",Translate::trnsAll),
		LangTypeNS(L"Û",L"ø",Translate::trnsAll),
		LangTypeNS(L"Ý",L"ù",Translate::trnsAll),
		LangTypeNS(L"ß",L"ú",Translate::trnsAll),
		LangTypeNS(L"Ù",L"û",Translate::trnsAll),
		LangTypeNS(L"Ø",L"ü",Translate::trnsAll),
		LangTypeNS(L"Ü",L"ý",Translate::trnsAll),
		LangTypeNS(L"À",L"þ",Translate::trnsAll),
		LangTypeNS(L"Ñ",L"ÿ",Translate::trnsAll),
		LangTypeNS(L"á",L"À",Translate::trnsAll),
		LangTypeNS(L"â",L"Á",Translate::trnsAll),
		LangTypeNS(L"÷",L"Â",Translate::trnsAll),
		LangTypeNS(L"ç",L"Ã",Translate::trnsAll),
		LangTypeNS(L"ä",L"Ä",Translate::trnsAll),
		LangTypeNS(L"å",L"Å",Translate::trnsAll),
		LangTypeNS(L"ö",L"Æ",Translate::trnsAll),
		LangTypeNS(L"ú",L"Ç",Translate::trnsAll),
		LangTypeNS(L"é",L"È",Translate::trnsAll),
		LangTypeNS(L"ê",L"É",Translate::trnsAll),
		LangTypeNS(L"ë",L"Ê",Translate::trnsAll),
		LangTypeNS(L"ì",L"Ë",Translate::trnsAll),
		LangTypeNS(L"í",L"Ì",Translate::trnsAll),
		LangTypeNS(L"î",L"Í",Translate::trnsAll),
		LangTypeNS(L"ï",L"Î",Translate::trnsAll),
		LangTypeNS(L"ð",L"Ï",Translate::trnsAll),
		LangTypeNS(L"ò",L"Ð",Translate::trnsAll),
		LangTypeNS(L"ó",L"Ñ",Translate::trnsAll),
		LangTypeNS(L"ô",L"Ò",Translate::trnsAll),
		LangTypeNS(L"õ",L"Ó",Translate::trnsAll),
		LangTypeNS(L"æ",L"Ô",Translate::trnsAll),
		LangTypeNS(L"è",L"Õ",Translate::trnsAll),
		LangTypeNS(L"ã",L"Ö",Translate::trnsAll),
		LangTypeNS(L"þ",L"×",Translate::trnsAll),
		LangTypeNS(L"û",L"Ø",Translate::trnsAll),
		LangTypeNS(L"ý",L"Ù",Translate::trnsAll),
		LangTypeNS(L"ÿ",L"Ú",Translate::trnsAll),
		LangTypeNS(L"ù",L"Û",Translate::trnsAll),
		LangTypeNS(L"ø",L"Ü",Translate::trnsAll),
		LangTypeNS(L"ü",L"Ý",Translate::trnsAll),
		LangTypeNS(L"à",L"Þ",Translate::trnsAll),
		LangTypeNS(L"ñ",L"ß",Translate::trnsAll),
		LangTypeNS(L"Ó",L"¸",Translate::trnsAll),
		LangTypeNS(L"Ò",L"¨",Translate::trnsAll),
		LangTypeNS(L"¦",L"¹",Translate::trnsAll),
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

void Language::ResetIgnore7(LangProfile& rProfile)
{
	rProfile.ResetIgnore();
}

void Language::ResetIgnoreText7(LangProfile& rProfile)
{
	rProfile.ResetIgnoreText();
}

void Language::ResetName7(LangProfile& rProfile)
{
	rProfile.m_astrLang[0] = "Cyrillic(KOI8-R)";
	rProfile.m_astrLang[1] = "Cyrillic(Win)";
}
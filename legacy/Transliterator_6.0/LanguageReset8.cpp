#include "stdafx.h"

#include "language.h"

// HebRus
void Language::Reset8(LangProfile& rProfile)
{
	ResetTranslation8(rProfile);
	ResetIgnore8(rProfile);
	ResetIgnoreText8(rProfile);
	ResetName8(rProfile);
}

void Language::ResetTranslation8(LangProfile& rProfile)
{
	static const LangTypeNS aTranslation[] = 
	{
		LangTypeNS(L"\x5d0",L"à",Translate::trnsAll),
		LangTypeNS(L"\x5d1",L"á",Translate::trnsAll),
		LangTypeNS(L"\x5d2",L"â",Translate::trnsAll),
		LangTypeNS(L"\x5d3",L"ã",Translate::trnsAll),
		LangTypeNS(L"\x5d4",L"ä",Translate::trnsAll),
		LangTypeNS(L"\x5d5",L"å",Translate::trnsAll),
		LangTypeNS(L"\x5d6",L"æ",Translate::trnsAll),
		LangTypeNS(L"\x5d7",L"ç",Translate::trnsAll),
		LangTypeNS(L"\x5d8",L"è",Translate::trnsAll),
		LangTypeNS(L"\x5d9",L"é",Translate::trnsAll),
		LangTypeNS(L"\x5da",L"ê",Translate::trnsAll),
		LangTypeNS(L"\x5db",L"ë",Translate::trnsAll),
		LangTypeNS(L"\x5dc",L"ì",Translate::trnsAll),
		LangTypeNS(L"\x5dd",L"í",Translate::trnsAll),
		LangTypeNS(L"\x5de",L"î",Translate::trnsAll),
		LangTypeNS(L"\x5df",L"ï",Translate::trnsAll),
		LangTypeNS(L"\x5e0",L"ð",Translate::trnsAll),
		LangTypeNS(L"\x5e1",L"ñ",Translate::trnsAll),
		LangTypeNS(L"\x5e2",L"ò",Translate::trnsAll),
		LangTypeNS(L"\x5e3",L"ó",Translate::trnsAll),
		LangTypeNS(L"\x5e4",L"ô",Translate::trnsAll),
		LangTypeNS(L"\x5e5",L"õ",Translate::trnsAll),
		LangTypeNS(L"\x5e6",L"ö",Translate::trnsAll),
		LangTypeNS(L"\x5e7",L"÷",Translate::trnsAll),
		LangTypeNS(L"\x5e8",L"ø",Translate::trnsAll),
		LangTypeNS(L"\x5e9",L"ù",Translate::trnsAll),
		LangTypeNS(L"\x5ea",L"ú",Translate::trnsAll),
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

void Language::ResetIgnore8(LangProfile& rProfile)
{
	rProfile.ResetIgnore();
}

void Language::ResetIgnoreText8(LangProfile& rProfile)
{
	rProfile.ResetIgnoreText();
}

void Language::ResetName8(LangProfile& rProfile)
{
	rProfile.m_astrLang[0] = "Hebrew";
	rProfile.m_astrLang[1] = "Russian";
}
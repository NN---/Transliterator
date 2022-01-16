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
		LangTypeNS(L"\x5d0",L"�",Translate::trnsAll),
		LangTypeNS(L"\x5d1",L"�",Translate::trnsAll),
		LangTypeNS(L"\x5d2",L"�",Translate::trnsAll),
		LangTypeNS(L"\x5d3",L"�",Translate::trnsAll),
		LangTypeNS(L"\x5d4",L"�",Translate::trnsAll),
		LangTypeNS(L"\x5d5",L"�",Translate::trnsAll),
		LangTypeNS(L"\x5d6",L"�",Translate::trnsAll),
		LangTypeNS(L"\x5d7",L"�",Translate::trnsAll),
		LangTypeNS(L"\x5d8",L"�",Translate::trnsAll),
		LangTypeNS(L"\x5d9",L"�",Translate::trnsAll),
		LangTypeNS(L"\x5da",L"�",Translate::trnsAll),
		LangTypeNS(L"\x5db",L"�",Translate::trnsAll),
		LangTypeNS(L"\x5dc",L"�",Translate::trnsAll),
		LangTypeNS(L"\x5dd",L"�",Translate::trnsAll),
		LangTypeNS(L"\x5de",L"�",Translate::trnsAll),
		LangTypeNS(L"\x5df",L"�",Translate::trnsAll),
		LangTypeNS(L"\x5e0",L"�",Translate::trnsAll),
		LangTypeNS(L"\x5e1",L"�",Translate::trnsAll),
		LangTypeNS(L"\x5e2",L"�",Translate::trnsAll),
		LangTypeNS(L"\x5e3",L"�",Translate::trnsAll),
		LangTypeNS(L"\x5e4",L"�",Translate::trnsAll),
		LangTypeNS(L"\x5e5",L"�",Translate::trnsAll),
		LangTypeNS(L"\x5e6",L"�",Translate::trnsAll),
		LangTypeNS(L"\x5e7",L"�",Translate::trnsAll),
		LangTypeNS(L"\x5e8",L"�",Translate::trnsAll),
		LangTypeNS(L"\x5e9",L"�",Translate::trnsAll),
		LangTypeNS(L"\x5ea",L"�",Translate::trnsAll),
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
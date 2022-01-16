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
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
		LangTypeNS(L"�",L"�",Translate::trnsAll),
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
#include "stdafx.h"

#include "language.h"

// DOS-Win
void Language::Reset6(LangProfile& rProfile)
{
	ResetTranslation6(rProfile);
	ResetIgnore6(rProfile);
	ResetIgnoreText6(rProfile);
	ResetName6(rProfile);
}

void Language::ResetTranslation6(LangProfile& rProfile)
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

void Language::ResetIgnore6(LangProfile& rProfile)
{
	rProfile.ResetIgnore();
}

void Language::ResetIgnoreText6(LangProfile& rProfile)
{
	rProfile.ResetIgnoreText();
}

void Language::ResetName6(LangProfile& rProfile)
{
	rProfile.m_astrLang[0] = "Cyrillic(DOS)";
	rProfile.m_astrLang[1] = "Cyrillic(Win)";
}
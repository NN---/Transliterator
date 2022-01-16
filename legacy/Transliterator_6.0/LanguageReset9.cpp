#include "stdafx.h"

#include "language.h"

// User
void Language::Reset9(LangProfile& rProfile)
{
	ResetTranslation9(rProfile);
	ResetIgnore9(rProfile);
	ResetIgnoreText9(rProfile);
	ResetName9(rProfile);
}

void Language::ResetTranslation9(LangProfile& rProfile)
{
	rProfile.ResetTranslation();
}

void Language::ResetIgnore9(LangProfile& rProfile)
{
	rProfile.ResetIgnore();
}

void Language::ResetIgnoreText9(LangProfile& rProfile)
{
	rProfile.ResetIgnoreText();
}

void Language::ResetName9(LangProfile& rProfile)
{
	rProfile.m_astrLang[0] = "LangTop";
	rProfile.m_astrLang[1] = "LangBottom";
}
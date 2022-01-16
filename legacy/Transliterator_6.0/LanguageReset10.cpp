#include "stdafx.h"

#include "language.h"

// User
void Language::Reset10(LangProfile& rProfile)
{
	ResetTranslation10(rProfile);
	ResetIgnore10(rProfile);
	ResetIgnoreText10(rProfile);
	ResetName10(rProfile);
}

void Language::ResetTranslation10(LangProfile& rProfile)
{
	rProfile.ResetTranslation();
}

void Language::ResetIgnore10(LangProfile& rProfile)
{
	rProfile.ResetIgnore();
}

void Language::ResetIgnoreText10(LangProfile& rProfile)
{
	rProfile.ResetIgnoreText();
}

void Language::ResetName10(LangProfile& rProfile)
{
	rProfile.m_astrLang[0] = "LangTop";
	rProfile.m_astrLang[1] = "LangBottom";
}
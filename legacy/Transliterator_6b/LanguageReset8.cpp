#include "stdafx.h"
#include "language.h"

// User3
void Language::Reset8(LangProfile& rProfile)
{
	rProfile.ResetUser();
	rProfile.m_strName+=L"3";
}
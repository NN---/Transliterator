#include "stdafx.h"
#include "language.h"

// User1
void Language::Reset6(LangProfile& rProfile)
{
	rProfile.ResetUser();
	rProfile.m_strName+=L"1";
}
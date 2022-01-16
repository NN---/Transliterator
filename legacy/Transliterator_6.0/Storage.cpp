#include "stdafx.h"

#include "language.h"

#include "storage.h"

const TCHAR* const Storage::s_aszLangName[2] = 
{
	_T("TopText.txt"),
	_T("BottomText.txt")
};

const TCHAR* const Storage::s_aszProfileName[Language::nProfiles] = 
{
	_T("Standard"),
	_T("Fonetic"),
	_T("GOST"),
	_T("Symbols"),
	_T("QWER"),
	_T("DOS-Win"),
	_T("KOI8-R-Win"),
	_T("HebRus"),
	_T("User1"),
	_T("User2")
};

void Storage::Reset()
{
	for(size_t i=0; i<nStg; ++i)
		ResetStg(i);

	ResetText();
	ResetProfiles();
}

void Storage::ResetStg(int nStg)
{
	m_stg[nStg] = stgRegistry;
}

void Storage::ResetLang(int nLang)
{
	m_astrLang[nLang] = s_aszLangName[nLang];
}

void Storage::ResetText()
{
	for(size_t i=0; i<2; ++i)
		ResetLang(i);
}

void Storage::ResetProfile(int nProfile)
{
	m_astrProfile[nProfile] = s_aszProfileName[nProfile];
}

void Storage::ResetProfiles()
{
	for(size_t i=0; i<Language::nProfiles; ++i)
		ResetProfile(i);
}

const Storage& Storage::operator = (const Storage& r)
{
	m_stg[stgText] = r.m_stg[stgText];
	m_stg[stgProfiles] = r.m_stg[stgProfiles];

	for(size_t i=0; i<2; ++i)
		m_astrLang[i] = r.m_astrLang[i];
	
	for(size_t i=0; i<Language::nProfiles; ++i)
		m_astrProfile[i] = r.m_astrProfile[i];

	return *this;
}
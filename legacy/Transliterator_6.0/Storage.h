#ifndef __STORAGE_H__
#define __STORAGE_H__

#pragma once

#include "language.h"

struct Storage
{
	enum Stg
	{
		stgRegistry,
		stgFile
	};

	enum
	{
		stgText,
		stgProfiles,
		nStg
	};
	
	Stg m_stg[nStg];

	LangStringT m_astrLang[2];
	LangStringT m_astrProfile[Language::nProfiles];

	static const TCHAR* const s_aszLangName[2];
	static const TCHAR* const s_aszProfileName[Language::nProfiles];
	
	void Reset();
	void ResetStg(int nStg);
	void ResetLang(int nLang);
	void ResetText();
	void ResetProfile(int nProfile);
	void ResetProfiles();
	const Storage& operator = (const Storage& r);
};

#endif // __PROGRAMSTORAGE_H__
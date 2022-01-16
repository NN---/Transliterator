#ifndef __LANGPROFILE_H___
#define __LANGPROFILE_H___

#include "types.h"

struct LangProfile
{
	// Array
	LangArray m_aSymbols;
	// Name
	LangString m_strName;
	// Ignore
	enum
	{
		Begin1,
		End1,
		Begin2,
		End2,
		nIgnore
	};
	LangString m_astrIgnore[nIgnore];
	
	// Default
	static const wchar_t* DefaultUser() { return L"User"; }
	static const wchar_t* DefaultIgnore() {	return L"**"; }

	// Reset
	void ResetSymbols() { m_aSymbols.clear(); }
	void ResetName() { m_strName.clear(); }
	void ResetNameUser() { m_strName=DefaultUser(); }

	void ResetIgnore()
	{
		for(int i=0;i<nIgnore;i++)
			m_astrIgnore[i]=DefaultIgnore();
	}

	void Reset() { Reset_(false); }
	void ResetUser() { Reset_(true); }

	void Reset_(bool bUser)
	{
		ResetSymbols();
		if(bUser)
			ResetNameUser();
		else
			ResetName();
		ResetIgnore();
	}
};

#endif // __LANGPROFILE_H___

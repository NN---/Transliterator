#ifndef __LANGPROFILE_H___
#define __LANGPROFILE_H___

#include "types.h"

struct LangProfile
{
	// Map
	LangMap m_map;
	// Name
	enum { nName = 15 };
	char m_strName[nName];
	// Ignore
	enum BeginEnd { BeginTrns, EndTrns, BeginRus, EndRus, nBeginEnd };
	enum { nIgnore = 4 };
	char m_strIgnore[nBeginEnd][nIgnore];
};

#endif // __LANGPROFILE_H___

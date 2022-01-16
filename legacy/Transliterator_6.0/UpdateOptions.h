#ifndef __UPDATEOPTIONS_H__
#define __UPDATEOPTIONS_H__

#include "language.h"

struct UpdateOptions
{
	bool m_bControls;
	bool m_bHotKey;
	bool m_bFont;
	bool m_bLanguage;
	bool m_abProfile[Language::nProfiles];

	void Reset()
	{
		m_bControls = false;
		m_bHotKey = true;
		m_bFont = true;
		m_bLanguage = false;
		memset(m_abProfile,0,sizeof(m_abProfile));
	}
};

#endif // __UPDATEOPTIONS_H__
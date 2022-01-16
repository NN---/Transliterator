#ifndef __PROFILESTRUCT_H__
#define __PROFILESTRUCT_H__

#include "langprofile.h"
#include "storage.h"

struct ProfileStruct
{
	LangProfile* m_pProfile;
	Storage* m_pStorage;
	unsigned m_nProfile;
};

#endif // __PROFILESTRUCT_H__
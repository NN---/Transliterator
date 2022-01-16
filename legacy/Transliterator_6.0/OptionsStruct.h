#ifndef __OPTIONSSTRUCT_H__
#define __OPTIONSSTRUCT_H__

#pragma once

#include "options.h"
#include "language.h"
#include "storage.h"

struct OptionsStruct
{
	LANGID		m_LangID;
	Options		m_Options;
	Language	m_Language;
	Storage		m_Storage;

	void Set(const Language& l,const Options& o,const Storage& s)
	{
		m_LangID = g_LangID;
		m_Language = l;
		m_Options = o;
		m_Storage = s;
	}
};

#endif // __OPTIONSSTRUCT_H__
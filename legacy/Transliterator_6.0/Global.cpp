#include "stdafx.h"

#include "global.h"

// Module
WTL::CAppModule _Module;
// Language ID
LANGID g_LangID;
const LANGID g_LangDefault = g_aLanguage[0];
const LANGID g_aLanguage[] = 
{
	MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US),
	MAKELANGID(LANG_RUSSIAN,SUBLANG_DEFAULT),
	MAKELANGID(LANG_BELARUSIAN,SUBLANG_DEFAULT),
	MAKELANGID(LANG_RUSSIAN,SUBLANG_DEFAULT+4)
};
const size_t g_nLanguage = NN::array_length(g_aLanguage);
// Language
Language g_Language;
// CP
const UINT g_CP = 1251;
// Storage
Storage g_Storage;
Storage g_OldStorage;
// Options
Options g_Options;
UpdateOptions g_UpdateOptions;
// Text
TextType g_Text[2];

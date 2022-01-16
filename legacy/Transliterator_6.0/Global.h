#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#pragma once

#include "types.h"
#include "language.h"
#include "options.h"
#include "storage.h"
#include "updateoptions.h"

// Module
extern WTL::CAppModule _Module;
// Language ID
extern LANGID g_LangID;
extern const LANGID g_LangDefault;
extern const LANGID g_aLanguage[];
extern const size_t g_nLanguage;
// Language
extern Language g_Language;
// CP
extern const UINT g_CP;
// Storage
extern Storage g_Storage;
extern Storage g_OldStorage;
// Options
extern Options g_Options;
extern UpdateOptions g_UpdateOptions;
// Text
extern TextType g_Text[2];

#endif // __GLOBAL_H__

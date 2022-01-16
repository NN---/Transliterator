#ifndef __STDAFX_H__
#define __STDAFX_H__

#pragma once

// Definitions
#define WINVER		0x0500
#define _WIN32_IE	0x0400
#define _RICHEDIT_VER	0x0300
#define _ATL_NO_COM
#define _ATL_NO_OLD_NAMES
#define _WTL_NO_WTYPES
#define _WTL_NO_CSTRING
#define _WTL_NEW_PAGE_NOTIFY_HANDLERS

//#define _ATL_ALL_WARNINGS

//#pragma warning(disable:4800) // 'int' : forcing value to bool 'true' or 'false' (performance warning)
#ifndef _DEBUG
#pragma warning(disable:4530)
#endif // !_DEBUG


// Language
#include <windows.h>
#define _LANG_R_
extern LANGID g_LangID;
#define _LANG_LangID_ g_LangID
#include <nn/lang.h>

// ATL / WTL
#include <atlbase.h>
#include <atlapp.h>
extern CAppModule _Module;
#include <atlwin.h>
#include <atlframe.h>
#include <atlctrls.h>
#include <atlctrlx.h>
#include <atldlgs.h>
#include <atlddx.h>
#include <atlfile.h>

// std
#include <string>
#include <list>
#include <vector>

// boost
#include <boost/tuple/tuple.hpp>

// NN
#define NN_USE_SHL_FOR_STRINGW
#include <nn/wnd_string.h>
#include <nn/auto.h>
#include <nn/currentdirectory.h>
#include <nn/mutex.h>
#include <nn/hotkey.h>
#include <nn/trayicon.h>
#include <nn/dialog.h>
#include <nn/dialoglang.h>
#include <nn/property.h>
#include <nn/propertylang.h>
#include <nn/optionsdialog.h>
#include <nn/mp3.h>
#include <nn/messagefilter.h>
#include <nn/toolwindow.h>

// Program
/*
#include "translate.h"
#include "types.h"
#include "langprofile.h"
#include "language.h"
#include "error.h"
*/

// Debug Information
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK,__FILE__,__LINE__)
#endif // _DEBUG

#endif // __STDAFX_H__
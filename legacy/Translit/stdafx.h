// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#ifndef __STDAFX_H__
#define __STDAFX_H__

// Change these values to use different versions
#define WINVER		0x0500
//#define _WIN32_WINNT	0x0400
#define _WIN32_IE	0x0400
#define _RICHEDIT_VER	0x0300
#define _WTL_NEW_PAGE_NOTIFY_HANDLERS
#define _ATL_NO_COM
#define _ATL_NO_OLD_NAMES
#define _WTL_NO_WTYPES
#define _WTL_NO_CSTRING
#pragma warning(disable:4800) // 'int' : forcing value to bool 'true' or 'false' (performance warning)
//#define _ATL_ALL_WARNINGS
#define NN_WINDOWS

#include <windows.h>
#define _T(x) TEXT(x) // avoid problems
#include <commctrl.h>
#include "Translate.h"
#include "Options.h"
extern Options _Options;
// Language
#define _LANG_R_
#define _LANG_LangID_ _Options.m_langID
#include <NN/Lang.h>
#undef _T // undefine to avoid redefine
#include <atlbase.h>
#include <atlapp.h>

extern CAppModule _Module;

#include <atlwin.h>
#include <atlframe.h>
#include <atlctrls.h>
#include <atldlgs.h>
#include <atlddx.h>
#include <atlfile.h>

#include <NN/TrayIcon.h>
#include <NN/Dialog.h>
#include <NN/DialogLang.h>
#include <NN/Property.h>
#include <NN/PropertyLang.h>
#include <NN/Tuple.h>
#include <NN/Array.h>
#include <NN/Auto.h>
#include <NN/Type.h>
#include <NN/CurrentDirectory.h>
using namespace NN;
#include "Translit.h"
#include "Global.h"

// Debug Information
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK,__FILE__,__LINE__)
#endif // _DEBUG

#endif // !__STDAFX_H__
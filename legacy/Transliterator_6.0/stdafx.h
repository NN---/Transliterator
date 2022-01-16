#ifndef __STDAFX_H__
#define __STDAFX_H__

#pragma once

// Definitions
#define WINVER		0x0500
#define _WIN32_IE	0x0400
#define _RICHEDIT_VER	0x0300

#define _ATL_NO_COM
#define _ATL_NO_HOSTING
#define _ATL_NO_OLD_NAMES
#define _ATL_CSTRING_NO_CRT
#define _WTL_NO_WTYPES
#define _WTL_NO_CSTRING
#define _WTL_NEW_PAGE_NOTIFY_HANDLERS

#define _ATL_NO_AUTOMATIC_NAMESPACE
#define _WTL_NO_AUTOMATIC_NAMESPACE

//#define _ATL_ALL_WARNINGS

#include <windows.h>

// Language
#define NN_LANG_STR
#define NN_LANG_R
#define NN_LANG_ID g_LangID
extern LANGID g_LangID;
#include <nn/lang.h>

// ATL / WTL
#include <atlbase.h>
#include <atlapp.h>
extern WTL::CAppModule _Module;
#include <atlwin.h>
#include <atlframe.h>
#include <atlctrls.h>
#include <atlctrlx.h>
#include <atldlgs.h>
#include <atlddx.h>
#include <atlfile.h>
#include <atlmisc.h>

// std
#pragma warning(push)
#pragma warning(disable:4702) // unreachable code
#include <algorithm>
#include <string>
#include <vector>
#pragma warning(pop)

// boost
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits.hpp>

// NN
#define NN_DDX_STRING
#define NN_USE_SHL_FOR_STRINGW

#include <nn/wnd_string.h>
#include <nn/string.h>
#include <nn/charaw.h>
#include <nn/auto.h>
#include <nn/directory.h>
#include <nn/mutex.h>
#include <nn/hotkey.h>
#include <nn/trayicon.h>
#include <nn/dialog.h>
#include <nn/dialoglang.h>
#include <nn/listcombomru.h>
#include <nn/optionsdialog.h>
#include <nn/ddx.h>
#include <nn/id3.h>
#include <nn/messagefilter.h>
#include <nn/toolwindow.h>
#include <nn/digits_number.h>
#include <nn/sg.h>
#include <nn/vector_string.h>
#include <nn/shorter.h>
#include <nn/algorithm.h>
#include <nn/array.h>

// Debug Information
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK,__FILE__,__LINE__)
#define new DEBUG_NEW
#endif // _DEBUG

#ifdef min
#undef min
using std::min;
#endif // min

#ifdef max
#undef max
using std::max;
#endif // max

#endif // __STDAFX_H__
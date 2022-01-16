#ifndef __STDAFX_H__
#define __STDAFX_H__

#pragma once

// Definitions
#define WINVER		0x0500
#define _WIN32_IE	0x0500
#define _RICHEDIT_VER	0x0300
#define _ATL_NO_COM
#define _ATL_NO_OLD_NAMES
#define _WTL_NO_WTYPES
#define _WTL_NO_CSTRING
#define _WTL_NEW_PAGE_NOTIFY_HANDLERS

//#define _ATL_ALL_WARNINGS
#define NN_WINDOWS

#pragma warning(disable:4800) // 'int' : forcing value to bool 'true' or 'false' (performance warning)

// Language
#include <windows.h>
#define NN_LANG_STR
#define NN_LANG_R
#define NN_LANG_ID g_LangID
extern LANGID g_LangID;
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

// NN
#include <nn/type.h>
#include <nn/array.h>
#include <nn/tuple.h>
#include <nn/auto.h>
#include <nn/directory.h>
#include <nn/commandline.h>
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
#include "msg.h"
#include "translate.h"
#include "change.h"
#include "splitstr.h"
#include "types.h"
#include "traits.h"
#include "langprofile.h"
#include "langstruct.h"
#include "ignore.h"

#include "error.h"
#include "language.h"
#include "options.h"
#include "global.h"
#include "controls.h"

// Debug Information
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK,__FILE__,__LINE__)
#endif // _DEBUG

#endif // __STDAFX_H__

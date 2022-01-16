#ifndef TRANSLITERATOR_STDAFX_H
#define TRANSLITERATOR_STDAFX_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif // _MSC_VER && (_MSC_VER >= 1200)

// Windows API Definitions
#define WINVER          0x0400
#define _WIN32_IE       0x0400
#define _RICHEDIT_VER   0x0300
#define NOMINMAX

// CRT Definitions
#define _CRT_SECURE_NO_DEPRECATE
#define _SCL_SECURE_NO_DEPRECATE

// ATL Definitions
#define _ATL_NO_AUTOMATIC_NAMESPACE
#define _ATL_NO_COM
#define _ATL_NO_HOSTING
#define _ATL_NO_OLD_NAMES

// WTL Definitions
#define _WTL_NO_CSTRING
#define _WTL_NO_WTYPES
#define _WTL_NO_AUTOMATIC_NAMESPACE
#define _WTL_NEW_PAGE_NOTIFY_HANDLERS

// STL Includes
#include <algorithm>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

// Using for WTL
using std::min;
using std::max;

// ATL Includes
#include <atlbase.h>
#include <atlfile.h>
#include <atltypes.h>
#include <atlwin.h>

// WTL Includes
#include <atlapp.h>
extern WTL::CAppModule _Module;
#include <atlctrls.h>
#include <atlctrlx.h>
#include <atlcrack.h>
#include <atldlgs.h>
#include <atlddx.h>
#include <atlframe.h>
#include <atlmisc.h>

// boost Includes
#pragma warning(push)
#pragma warning(disable:4510) // default constructor could not be generated
#pragma warning(disable:4610) // class can never be instantiated - user defined constructor required
#include <boost/array.hpp>
#pragma warning(pop)
#include <boost/tuple/tuple.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

// nn Includes
#include <nn/algorithm.hpp>
#include <nn/bimap.hpp>
#include <nn/convertion.hpp>
#include <nn/ddx.hpp>
#include <nn/dialog_icon.hpp>
#include <nn/dialog_impl.hpp>
#include <nn/dialog_lang.hpp>
#include <nn/digits_number.hpp>
#include <nn/foreach.hpp>
#include <nn/instance.hpp>
#include <nn/lang.hpp>
#include <nn/range.hpp>
#include <nn/resource.hpp>
#include <nn/tstring.hpp>
#include <nn/wnd_filter.hpp>
#include <nn/wnd_string.hpp>

// Debug Information
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _DEBUG

using namespace ATL;
using namespace WTL;
using namespace std;
using namespace boost;
using namespace nn;

#endif // TRANSLITERATOR_STDAFX_H

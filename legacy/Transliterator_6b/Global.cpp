#include "stdafx.h"
#include "language.h"

CAppModule _Module;
LANGID	g_LangID;
const LANGID g_LangIDDefault=MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US);
Language g_Language;
IgnoreArray g_Ignore;

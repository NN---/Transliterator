#include "stdafx.h"
#include "language.h"

// RusHeb
void Language::Reset5(LangProfile& rProfile)
{
	// Symbols
	static const LangType aSymbols[]=
	{
		LangType(L"а",L"א",Translate::trnsAll),
		LangType(L"б",L"ב",Translate::trnsAll),
		LangType(L"в",L"ג",Translate::trnsAll),
		LangType(L"г",L"ד",Translate::trnsAll),
		LangType(L"д",L"ה",Translate::trnsAll),
		LangType(L"е",L"ו",Translate::trnsAll),
		LangType(L"ж",L"ז",Translate::trnsAll),
		LangType(L"з",L"ח",Translate::trnsAll),
		LangType(L"и",L"ט",Translate::trnsAll),
		LangType(L"й",L"י",Translate::trnsAll),
		LangType(L"к",L"ך",Translate::trnsAll),
		LangType(L"л",L"כ",Translate::trnsAll),
		LangType(L"м",L"ל",Translate::trnsAll),
		LangType(L"н",L"ם",Translate::trnsAll),
		LangType(L"о",L"מ",Translate::trnsAll),
		LangType(L"п",L"ן",Translate::trnsAll),
		LangType(L"р",L"נ",Translate::trnsAll),
		LangType(L"с",L"ס",Translate::trnsAll),
		LangType(L"т",L"ע",Translate::trnsAll),
		LangType(L"у",L"ף",Translate::trnsAll),
		LangType(L"ф",L"פ",Translate::trnsAll),
		LangType(L"х",L"ץ",Translate::trnsAll),
		LangType(L"ц",L"צ",Translate::trnsAll),
		LangType(L"ч",L"ק",Translate::trnsAll),
		LangType(L"ш",L"ר",Translate::trnsAll),
		LangType(L"щ",L"ש",Translate::trnsAll),
		LangType(L"ъ",L"ת",Translate::trnsAll),
	};
	rProfile.m_aSymbols.assign(aSymbols,
		aSymbols+sizeof(aSymbols)/sizeof(aSymbols[0]));

	// Name
	static const wchar_t strName[]=L"RusHeb";
	rProfile.m_strName=strName;

	// Ignore
	rProfile.ResetIgnore();
}
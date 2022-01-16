#ifndef __MAKEDIRECTION_H__
#define __MAKEDIRECTION_H__

#include "global.h"

struct MakeDirection
{
	static const char* DirA() { return " -> "; }
	static const wchar_t* DirW() { return L" -> "; }
	static const TCHAR* DirT()
	{
#ifdef UNICODE
		return DirW();
#else
		return DirA();
#endif // UNICODE
	}

	static const char* DirBackA() { return " <- "; }
	static const wchar_t* DirBackW() { return L" <- "; }
	static const TCHAR* DirBackT()
	{
#ifdef UNICODE
		return DirBackW();
#else
		return DirBackA();
#endif // UNICODE
	}
	
	template<typename T>
	static void MakeW(T (&a)[2],const LangProfile* pProfile = 0)
	{
		if(!pProfile)
			pProfile = g_Language.GetCurProfile();

		NN::CharAWT<const WCHAR> astrLang[2];
		for(size_t i=0; i<2; ++i)
			astrLang[i].SetData(g_Language.GetCurProfile()->m_astrLang[i].c_str());

		for(size_t i=0; i<2; ++i)
		{
			a[i] = astrLang[i];
			a[i]+= DirW();
			a[i]+= astrLang[!i];
		}
	}

	template<typename T>
	static void MakeA(T (&a)[2],const LangProfile* pProfile = 0)
	{
		if(!pProfile)
			pProfile = g_Language.GetCurProfile();

		for(size_t i=0; i<2; ++i)
		{
			a[i] = pProfile->m_astrLang[i];
			a[i]+= DirA();
			a[i]+= pProfile->m_astrLang[!i];
		}
	}

	template<typename T>
	static void MakeT(T (&a)[2],const LangProfile* pProfile = 0)
	{
#ifdef UNICODE
			MakeW(a,pProfile);
#else
			MakeA(a,pProfile);
#endif // UNICODE
	}
};

#endif // __MAKEDIRECTION_H__
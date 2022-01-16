#include "stdafx.h"

#include "language.h"
#include "storage.h"
#include "makedirection.h"

#include "controls.h"

void InitCmbProfile(HWND hWnd,
	int nCurSel/* = 0*/,
	const Storage& storage/* = g_Storage*/)
{
	WTL::CComboBox cmb(hWnd);
	cmb.ResetContent();

	for(size_t i=0; i<Language::nProfiles; ++i)
		cmb.AddString(storage.m_astrProfile[i].c_str());

	cmb.SetCurSel(nCurSel);
}

void InitCmbDir(HWND hWnd,
	int nCurSel/* = 0*/,
	const LangProfile* pProfile/* = g_Language.GetCurProfile()*/)
{
	WTL::CComboBox cmb(hWnd);
	cmb.ResetContent();

	LangStringT astrDir[2];
	MakeDirection::MakeT(astrDir,pProfile);
	
	for(size_t i=0; i<2; ++i)
		cmb.AddString(astrDir[i].c_str());

	cmb.SetCurSel(nCurSel);
}
#include "stdafx.h"

#include "resource.h"
#include "global.h"
#include "makedirection.h"

#include "hotkeyspage.h"

void HotKeysPage::DialogLang_LanguageChanged()
{
	ProfileChanged();
}

void HotKeysPage::ProfileChanged()
{
	LangStringT strDir[2];
	MakeDirection::MakeT(strDir);

	WTL::CComboBox cmbAction = GetDlgItem(IDC_CMBACTION);
	int iSel = cmbAction.GetCurSel();
	for(size_t i=0; i<2; ++i)
		cmbAction.DeleteString(0);
	for(size_t i=0; i<2; ++i)
	{
		cmbAction.InsertString(i,strDir[i].c_str());
		SetDlgItemText(IDC_RADLANGTOPTOLANGBOTTOM+i,strDir[i].c_str());
	}
	cmbAction.SetCurSel(iSel);
}

void HotKeysPage::SaveHotKey()
{
	if(m_nCurSel != CB_ERR)
	{
		WTL::CHotKeyCtrl hotkey = GetDlgItem(IDC_HKACTION);
		NN::HotKey hk;
		hotkey.GetHotKey(hk.vk,hk.fsModifiers);
		hk.ConvertToWnd();
		if(GetOptions()->m_Options.m_HotKey[m_nCurSel] != hk)
		{
			g_UpdateOptions.m_bHotKey = true;
			GetOptions()->m_Options.m_HotKey[m_nCurSel] = hk;
		}
	}
}

void HotKeysPage::LoadHotKey()
{
	WTL::CHotKeyCtrl hotkey = GetDlgItem(IDC_HKACTION);
	m_nCurSel = SendDlgItemMessage(IDC_CMBACTION,CB_GETCURSEL,0,0);
	NN::HotKey& hk = GetOptions()->m_Options.m_HotKey[m_nCurSel];
	hk.ConvertToHotKey();
	hotkey.SetHotKey(hk.vk,hk.fsModifiers);
}

LRESULT HotKeysPage::OnCmbSelChangeAction(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	SaveHotKey();
	LoadHotKey();
	return 0;
}
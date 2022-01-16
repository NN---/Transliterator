#include "stdafx.h"

#include "resource.h"
#include "controls.h"

#include "generalpage.h"

void GeneralPage::DialogLang_LanguageChanged()
{
	for(size_t i=0; i<2; ++i)
		SetDlgItemText(IDC_EDTLANGTOP+i,
			GetOptions()->m_Storage.m_astrLang[i].c_str());
}

void GeneralPage::UpdateText()
{
	const BOOL bEnable = IsDlgButtonChecked(IDC_CHKSAVETEXTONEXIT);
	::EnableWindow(GetDlgItem(IDC_EDTLANGTOP),bEnable);
	::EnableWindow(GetDlgItem(IDC_EDTLANGBOTTOM),bEnable);
	::EnableWindow(GetDlgItem(IDC_RADTEXTREGISTRY),bEnable);
	::EnableWindow(GetDlgItem(IDC_RADTEXTFILE),bEnable);
}

LRESULT GeneralPage::OnSaveTextOnExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	UpdateText();
	return 0;
}
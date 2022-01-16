#include "stdafx.h"

#include "resource.h"
#include "storage.h"
#include "msg.h"

#include "profilename.h"

void ProfileName::DialogLang_LanguageChanged()
{
	LoadName();
}

void ProfileName::LoadName()
{
	SetDlgItemText(IDC_EDTPROFILENAME,
		GetOptions()->m_pStorage->m_astrProfile[GetOptions()->m_nProfile].c_str());

	for(size_t i=0; i<2; ++i)
		SetDlgItemText(IDC_EDTLANGTOP+i,GetOptions()->m_pProfile->m_astrLang[i].c_str());
}

void ProfileName::SaveName()
{
	NN::WndGetText(GetDlgItem(IDC_EDTPROFILENAME),
		GetOptions()->m_pStorage->m_astrProfile[GetOptions()->m_nProfile]);

	for(size_t i=0; i<2; ++i)
		NN::WndGetText(GetDlgItem(IDC_EDTLANGTOP+i),GetOptions()->m_pProfile->m_astrLang[i]);
}

LRESULT ProfileName::OnSet(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	SaveName();

	GetParent().SendMessage(UWM_PROFILENAME);
	GetParent().SendMessage(UWM_PROFILEUPDATE);

	InvalidateRect(NULL);

	return 0;
}
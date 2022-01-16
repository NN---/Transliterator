#include "stdafx.h"

#include "resource.h"
#include "controls.h"
#include "storage.h"
#include "msg.h"

#include "profilecopyprofile.h"

void ProfileCopyProfile::DialogLang_LanguageChanged()
{
	for(size_t i=0; i<2; ++i)
	{
		InitCmbProfile(
			GetDlgItem(IDC_CMBFROM+i),
			m_aFromTo[i],
			*GetOptions()->m_pStorage);
	}
}

LRESULT ProfileCopyProfile::OnSelChangeFromTo(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	m_aFromTo[wID-IDC_CMBFROM] = SendDlgItemMessage(wID,CB_GETCURSEL);

	return 0;
}

LRESULT ProfileCopyProfile::OnCopy(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(m_aFromTo[0] = m_aFromTo[1])
		return 0;

	GetParent().SendMessage(UWM_PROFILECOPYPROFILE,(WPARAM)m_aFromTo[0],(LPARAM)m_aFromTo[1]);

	InvalidateRect(NULL);
	
	return 0;
}
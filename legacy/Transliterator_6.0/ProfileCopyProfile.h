#ifndef __PROFILECOPYPROFILE_H__
#define __PROFILECOPYPROFILE_H__

#pragma once

#include "profilestruct.h"

class ProfileCopyProfile : public NN::OptionsPageImpl<ProfileCopyProfile,ProfileStruct>,
						public NN::DialogLang<ProfileCopyProfile>,
						public NN::MessageFilterDlg<ProfileCopyProfile>
{
public:
	enum { IDD = IDD_PROFILECOPYPROFILE };

	NN::auto_value<int> m_aFromTo[2];

	void DialogLang_LanguageChanged();

	BEGIN_DDX_MAP(ProfileCopyProfile)
	END_DDX_MAP()

	BEGIN_MSG_MAP(ProfileCopyProfile)
		COMMAND_HANDLER(IDC_CMBFROM,CBN_SELCHANGE,OnSelChangeFromTo)
		COMMAND_HANDLER(IDC_CMBTO,CBN_SELCHANGE,OnSelChangeFromTo)

		COMMAND_ID_HANDLER(IDC_BTNCOPY,OnCopy)
	END_MSG_MAP()

	LRESULT OnSelChangeFromTo(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnCopy(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
};

#endif // __PROFILECOPYPROFILE_H__
#ifndef __PROFILENAME_H__
#define __PROFILENAME_H__

#pragma once

#include "profilestruct.h"

class ProfileName : public NN::OptionsPageImpl<ProfileName,ProfileStruct>,
						public NN::DialogLang<ProfileName>,
						public NN::MessageFilterDlg<ProfileName>
{
public:
	enum { IDD = IDD_PROFILENAME };

	void DialogLang_LanguageChanged();

	void LoadName();
	void SaveName();

	BEGIN_DDX_MAP(ProfileName)
		if(!bSaveAndValidate)
			LoadName();
	END_DDX_MAP()

	BEGIN_MSG_MAP(ProfileName)
		COMMAND_ID_HANDLER(IDC_BTNSET,OnSet)
	END_MSG_MAP()

	LRESULT OnSet(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
};

#endif // __PROFILENAME__
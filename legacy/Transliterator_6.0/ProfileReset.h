#ifndef __PROFILERESET_H__
#define __PROFILERESET_H__

#pragma once

#include "profilestruct.h"

class ProfileReset : public NN::OptionsPageImpl<ProfileReset,ProfileStruct>,
						public NN::DialogLang<ProfileReset>,
						public NN::MessageFilterDlg<ProfileReset>
{
public:
	enum { IDD = IDD_PROFILERESET };

	enum Reset
	{
		resetTranslation = 1,
		resetIgnore		 = 2,
		resetIgnoreText	 = 4,
		resetName		 = 8
	};

	BEGIN_DDX_MAP(ProfileReset)
	END_DDX_MAP()

	BEGIN_MSG_MAP(ProfileReset)
		COMMAND_ID_HANDLER(IDC_BTNRESET,OnReset)
	END_MSG_MAP()

	LRESULT OnReset(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
};

#endif // __PROFILERESET_H__
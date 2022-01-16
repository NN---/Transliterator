#ifndef __HOTKEYSPAGE_H__
#define __HOTKEYSPAGE_H__

#pragma once

#include "optionsstruct.h"
#include "profilechanged.h"

class HotKeysPage : public NN::OptionsPageImpl<HotKeysPage,OptionsStruct>,
					public NN::DialogLang<HotKeysPage>,
					public NN::MessageFilterDlg<HotKeysPage>,
					public ProfileChanged
{
public:
	enum { IDD = IDD_PAGEHOTKEYS };

	NN::auto_value<int,CB_ERR> m_nCurSel;

	void DialogLang_LanguageChanged();
	void ProfileChanged();
	void SaveHotKey();
	void LoadHotKey();

	BEGIN_DDX_MAP(HotKeysPage)
		DDX_RADIO(IDC_RADLANGTOPTOLANGBOTTOM,(int&)GetOptions()->m_Options.m_nAutoTransliteration)
		if(bSaveAndValidate)
			SaveHotKey();
	END_DDX_MAP()

	BEGIN_MSG_MAP(HotKeysPage)
		NN_MSGFILTER_MESSAGE_ADD()
		NN_MSGFILTER_MESSAGE_REMOVE()
		COMMAND_HANDLER(IDC_CMBACTION,CBN_SELCHANGE,OnCmbSelChangeAction)
	END_MSG_MAP()
	
	LRESULT OnCmbSelChangeAction(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
};

#endif // __HOTKEYSPAGE_H__
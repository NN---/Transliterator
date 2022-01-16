#ifndef __OPTIONSDLG_H__
#define __OPTIONSDLG_H__

#pragma once

#include "optionsstruct.h"
#include "generalpage.h"
#include "viewpage.h"
#include "hotkeyspage.h"
#include "profilepage.h"

class OptionsDlg : public NN::OptionsDialogImpl<OptionsDlg,OptionsStruct>,
				public NN::DialogLang<OptionsDlg>,
				public NN::MessageFilterDlg<OptionsDlg>,
				public NN::ToolWindow<OptionsDlg>
{
public:
	enum { IDD = IDD_OPTIONS };

	typedef NN::OptionsDialogImpl<OptionsDlg,OptionsStruct> baseClass;

	WTL::CListBox m_ctrlOptions;

	GeneralPage	m_pageGeneral;
	ViewPage		m_pageView;
	HotKeysPage	m_pageHotKeys;
	ProfilePage	m_pageProfile;

	void DialogLang_LanguageChanged();
	void NotifyProfileChanged();

	void InitOptionsPage();
	void Apply();

	BEGIN_MSG_MAP(OptionsDlg)
		NN_MSGFILTER_MESSAGE_ADD()
		NN_MSGFILTER_MESSAGE_REMOVE()
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_SHOWWINDOW, OnShowWindow)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_ACTIVATE, OnActivate)

		COMMAND_ID_HANDLER(IDOK, OnOKApply)
		COMMAND_ID_HANDLER(IDC_BTNAPPLY, OnOKApply)
		
		COMMAND_HANDLER(IDC_LSTOPTIONS, LBN_SELCHANGE, OnSelChangeLstOptions)

		CHAIN_MSG_MAP(NN::ToolWindow<OptionsDlg>)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnShowWindow(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnOKApply(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnSelChangeLstOptions(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
};

#endif // __OPTIONSDLG_H__
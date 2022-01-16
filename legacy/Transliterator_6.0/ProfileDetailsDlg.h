#ifndef __PROFILEDETAILSDLG_H__
#define __PROFILEDETAILSDLG_H__

#pragma once

class ProfileDetailsDlg : public ATL::CDialogImpl<ProfileDetailsDlg>,
					public WTL::CDialogResize<ProfileDetailsDlg>,
					public NN::DialogLang<ProfileDetailsDlg>,
					public NN::MessageFilterDlg<ProfileDetailsDlg>,
					public NN::ToolWindow<ProfileDetailsDlg>
{
public:
	enum { IDD = IDD_PROFILEDETAILS };

	WTL::CRichEditCtrl m_reDetails;
	WTL::CComboBox m_cmbProfile;
	WTL::CComboBox m_cmbView;

	enum Profile
	{
		profileAll = Language::nProfiles
	};

	enum View
	{
		viewTranslation,
		viewIgnore,
		viewIgnoreText,
		viewAll
	};

	enum NumAll
	{
		nLang = 2,
		nView = 3,
		nDirection = 2
	};

	void UpdateDetails();
	void UpdateCmbProfile();
	void UpdateCmbView();

	void DialogLang_LanguageChanged();

	BEGIN_DLGRESIZE_MAP(CSymbolslg)
		BEGIN_DLGRESIZE_GROUP()
			DLGRESIZE_CONTROL(IDC_STATICSEPARATOR, DLSZ_SIZE_X)
			DLGRESIZE_CONTROL(IDC_REDETAILS, DLSZ_SIZE_X|DLSZ_SIZE_Y)
		END_DLGRESIZE_GROUP()
	END_DLGRESIZE_MAP()

	BEGIN_MSG_MAP(ProfileDetailsDlg)
		NN_MSGFILTER_MESSAGE_ADD()
		NN_MSGFILTER_MESSAGE_REMOVE()
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_SHOWWINDOW, OnShowWindow)
		
		COMMAND_HANDLER(IDC_CMBPROFILE,CBN_SELCHANGE,OnChange)
		COMMAND_HANDLER(IDC_CMBVIEW,CBN_SELCHANGE,OnChange)

		NOTIFY_HANDLER(IDC_REDETAILS, EN_MSGFILTER, OnEnMsgFilterDetails)

		CHAIN_MSG_MAP(WTL::CDialogResize<ProfileDetailsDlg>)
		CHAIN_MSG_MAP(NN::ToolWindow<ProfileDetailsDlg>)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnShowWindow(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	
	LRESULT OnChange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnEnMsgFilterDetails(int code, NMHDR* pnmhdr, BOOL& bHandled);
};

#endif // __PROFILEDETAILSDLG_H__
#ifndef __TRANSLATIONDLG_H__
#define __TRANSLATIONDLG_H__

class CTranslationDlg : public CDialogImpl<CTranslationDlg>,
					public NN::DialogLang<CTranslationDlg>,
					public CDialogResize<CTranslationDlg>,
					public NN::MessageFilterDlg<CTranslationDlg>,
					public NN::ToolWindow<CTranslationDlg>
{
public:
	enum { IDD = IDD_TRANSLATION };

	CRichEditCtrl m_reTranslation;
	int m_nCurProfile;

	void UpdateCmbProfile();
	void UpdateLanguage();
	void UpdateCurProfile();

	void UpdateTranslation();
	void MakeTranslation(LPTSTR strTranslation);
	size_t TranslationCount();

	BEGIN_DLGRESIZE_MAP(CTranslationDlg)
		BEGIN_DLGRESIZE_GROUP()
			DLGRESIZE_CONTROL(IDC_STATICSEPARATOR, DLSZ_SIZE_X)
			DLGRESIZE_CONTROL(IDC_TRANSLATION, DLSZ_SIZE_X|DLSZ_SIZE_Y)
		END_DLGRESIZE_GROUP()
	END_DLGRESIZE_MAP()

	BEGIN_MSG_MAP(CTranslationDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_SHOWWINDOW, OnShowWindow)
		NOTIFY_HANDLER(IDC_TRANSLATION, EN_MSGFILTER, OnEnMsgFilterTranslation)
		COMMAND_HANDLER(IDC_PROFILE,CBN_SELCHANGE,OnChangeProfile)
		CHAIN_MSG_MAP(CDialogResize<CTranslationDlg>)
		CHAIN_MSG_MAP(NN::ToolWindow<CTranslationDlg>)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnShowWindow(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnChangeProfile(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnEnMsgFilterTranslation(int code, NMHDR* pnmhdr, BOOL& bHandled);
};

#endif // __TRANSLATIONDLG_H__
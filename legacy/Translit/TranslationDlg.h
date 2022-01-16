#ifndef __TRANSLATIONDLG_H__
#define __TRANSLATIONDLG_H__

class CTranslationDlg : public CDialogImpl<CTranslationDlg>,
					public DialogLang<CTranslationDlg>
{
public:
	enum { IDD = IDD_TRANSLATION };

	CRichEditCtrl m_richeditTranslation;

	void UpdateTranslation();
	void MakeTranslation(LPTSTR szTranslation);

	BEGIN_MSG_MAP(CTranslationDlg)
		CHAIN_MSG_MAP(DialogLang<CTranslationDlg>)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_CLOSE, OnClose)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
		NOTIFY_HANDLER(IDC_TRANSLATION, EN_MSGFILTER, OnEnMsgFilterTranslation)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnEnMsgFilterTranslation(int code, NMHDR* pnmhdr, BOOL& bHandled);
};

#endif // __TRANSLATIONDLG_H__
#ifndef __ABOUTDLG_H__
#define __ABOUTDLG_H__

class CAboutDlg : public CDialogImpl<CAboutDlg>,
			public NN::DialogLang<CAboutDlg>
{
public:
	enum { IDD = IDD_ABOUT };

	BEGIN_MSG_MAP(CAboutDlg)
		MESSAGE_HANDLER(WM_INITDIALOG,OnInitDialog)
		COMMAND_ID_HANDLER(IDC_EMAIL, OnEmail)
		COMMAND_ID_HANDLER(IDC_SITE, OnSite)
		COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnEmail(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnSite(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnCloseCmd(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
};

#endif // __ABOUTDLG_H__
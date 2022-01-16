#ifndef __ABOUTDLG_H__
#define __ABOUTDLG_H__

class CAboutDlg : public CDialogImpl<CAboutDlg>,
				public NN::DialogLang<CAboutDlg>,
				public NN::ToolWindow<CAboutDlg>,
				public NN::MessageFilterDlg<CAboutDlg>
{
public:
	enum { IDD= IDD_ABOUT };
	typedef CAboutDlg thisClass;

	BEGIN_MSG_MAP(thisClass)
		COMMAND_ID_HANDLER(IDC_EMAIL, OnEmail)
		COMMAND_ID_HANDLER(IDC_SITE, OnSite)
		CHAIN_MSG_MAP(NN::ToolWindow<CAboutDlg>)
		CHAIN_MSG_MAP(NN::DialogLang<CAboutDlg>)
	END_MSG_MAP()

	LRESULT OnEmail(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		::ShellExecute(m_hWnd,_T("open"),_T("mailto:NN<nn-mail@bk.ru>"),NULL,NULL,SW_SHOW);
		return 0;
	}

	LRESULT OnSite(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		::ShellExecute(m_hWnd,_T("open"),_T("http://our-site.nm.ru"),NULL,NULL,SW_SHOW);
		return 0;
	}
};

#endif // __ABOUTDLG_H__
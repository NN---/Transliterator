#include "StdAfx.h"
#include "Resource.h"

#include "AboutDlg.h"

LRESULT CAboutDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	DialogLang_Init();
	CenterWindow(GetParent());
	return 0;
}

LRESULT CAboutDlg::OnEmail(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	ShellExecute(m_hWnd,_T("open"),_T("mailto:NN<nn-mail@bk.ru>"),NULL,NULL,SW_SHOW);
	return 0;
}

LRESULT CAboutDlg::OnSite(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	ShellExecute(m_hWnd,_T("open"),_T("http://our-site.nm.ru"),NULL,NULL,SW_SHOW);
	return 0;
}

LRESULT CAboutDlg::OnCloseCmd(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	EndDialog(0);
	return 0;
}
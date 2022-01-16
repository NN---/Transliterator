#include "stdafx.h"

#include "resource.h"

#include "aboutdlg.h"

LRESULT AboutDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	DialogLang_Init();

	m_hlEmail.SubclassWindow(GetDlgItem(IDC_BTNEMAIL));
	m_hlSite.SubclassWindow(GetDlgItem(IDC_BTNSITE));

	return 0;
}

LRESULT AboutDlg::OnEmail(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	::ShellExecute(m_hWnd, _T("open"),_T("mailto:NN<nn-mail@bk.ru>"),NULL,NULL,SW_SHOW);
	return 0;
}

LRESULT AboutDlg::OnSite(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	::ShellExecute(m_hWnd, _T("open"),_T("http://our-site.nm.ru"),NULL,NULL,SW_SHOW);
	return 0;
}
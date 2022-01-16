#ifndef __ABOUTDLG_H__
#define __ABOUTDLG_H__

#pragma once

class AboutDlg : public ATL::CDialogImpl<AboutDlg>,
				public NN::DialogLang<AboutDlg>,
				public NN::ToolWindow<AboutDlg>,
				public NN::MessageFilterDlg<AboutDlg>
{
public:
	enum { IDD = IDD_ABOUT };

	WTL::CHyperLink m_hlEmail;
	WTL::CHyperLink m_hlSite;
	
	BEGIN_MSG_MAP(AboutDlg)
		NN_MSGFILTER_MESSAGE_ADD()
		NN_MSGFILTER_MESSAGE_REMOVE()
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDC_BTNEMAIL, OnEmail)
		COMMAND_ID_HANDLER(IDC_BTNSITE, OnSite)
		CHAIN_MSG_MAP(NN::ToolWindow<AboutDlg>)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnEmail(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnSite(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
};

#endif // __ABOUTDLG_H__
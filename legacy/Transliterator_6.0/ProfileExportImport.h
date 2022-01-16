#ifndef __PROFILEEXPORTIMPORT_H__
#define __PROFILEEXPORTIMPORT_H__

#pragma once

#include "profilestruct.h"

class ProfileExportImport : public NN::OptionsPageImpl<ProfileExportImport,ProfileStruct>,
						public NN::DialogLang<ProfileExportImport>,
						public NN::MessageFilterDlg<ProfileExportImport>
{
public:
	enum { IDD = IDD_PROFILEEXPORTIMPORT };

	TCHAR m_szPath[MAX_PATH+1];

	void DialogLang_LanguageChanged();

	BEGIN_DDX_MAP(ProfileExportImport)
	END_DDX_MAP()

	BEGIN_MSG_MAP(ProfileExportImport)
		MESSAGE_HANDLER(WM_INITDIALOG,OnInitDialog)

		COMMAND_ID_HANDLER(IDC_BTNEXPORT,OnExport)
		COMMAND_ID_HANDLER(IDC_BTNIMPORT,OnImport)

		COMMAND_ID_HANDLER(IDC_BTNBROWSE,OnBrowse)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnExport(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnImport(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnBrowse(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
};

#endif // __PROFILEEXPORTIMPORT_H__
#ifndef __PROFILEIGNORE_H__
#define __PROFILEIGNORE_H__

#pragma once

#include "profilestruct.h"
#include "ddx.h"

class ProfileIgnore : public NN::OptionsPageImpl<ProfileIgnore,ProfileStruct>,
						public NN::DialogLang<ProfileIgnore>,
						public NN::MessageFilterDlg<ProfileIgnore>
{
public:
	enum { IDD = IDD_PROFILEIGNORE };

	WTL::CListViewCtrl m_lvIgnoreText;
	WTL::CRichEditCtrl m_reText;

	NN::auto_value<int,-1> m_nCurItem;

	NN::auto_value<bool,true> m_bChange;

	enum Column
	{
		clText,
		clLangToptoLangBottom,
		clLangBottomtoLangTop
	};
	
	static const Translate::Translation s_aTranslation[2];

	enum { eNextPage = 10 };

	void DialogLang_LanguageChanged();
	void UpdateLang();
	void UpdateIgnoreText();

	void LoadData();
	void SaveData();

	BEGIN_DDX_MAP(ProfileIgnore)
		for(unsigned i = 0;i<LangProfile::nIgnore; ++i)
			DDX_RE_EX(IDC_REBEGINTOP+i,GetOptions()->m_pProfile->m_astrIgnore[i])
		if(bSaveAndValidate)
		{
		}
		else
		{
			UpdateLang();
			UpdateIgnoreText();
		}
	END_DDX_MAP()

	BEGIN_MSG_MAP(ProfileIgnore)
		MESSAGE_HANDLER(WM_INITDIALOG,OnInitDialog)
		MESSAGE_HANDLER(WM_ACTIVATE, OnActivate)

		COMMAND_ID_HANDLER(IDC_BTNADD,OnAdd)
		COMMAND_ID_HANDLER(IDC_BTNDELETE,OnDelete)

		COMMAND_HANDLER(IDC_RETEXT, EN_CHANGE, OnEnChangeText)

		NOTIFY_HANDLER(IDC_LVIGNORETEXT,NM_CLICK,OnClickLVIgnoreText)
		NOTIFY_HANDLER(IDC_LVIGNORETEXT,NM_RCLICK,OnClickLVIgnoreText)
		NOTIFY_HANDLER(IDC_LVIGNORETEXT,LVN_KEYDOWN,OnKeyDownLVIgnoreText)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnAdd(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnDelete(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnEnChangeText(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnClickLVIgnoreText(int code, NMHDR* pnmhdr, BOOL& bHandled);
	LRESULT OnKeyDownLVIgnoreText(int code, NMHDR* pnmhdr, BOOL& bHandled);
};

#endif // __PROFILEIGNORE_H__
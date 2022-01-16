#ifndef __PROFILETRANSLATION_H__
#define __PROFILETRANSLATION_H__

#pragma once

#include "profilestruct.h"

class ProfileTranslation : public NN::OptionsPageImpl<ProfileTranslation,ProfileStruct>,
						public NN::DialogLang<ProfileTranslation>,
						public NN::MessageFilterDlg<ProfileTranslation>
{
public:
	enum { IDD = IDD_PROFILETRANSLATION };

	WTL::CRichEditCtrl m_reLang[2];
	WTL::CListViewCtrl m_lvTranslation;

	NN::auto_value<int,-1> m_nCurItem;

	NN::auto_value<bool,true> m_bChange;

	enum Column
	{
		clLangTop,
		clLangToptoLangBottom,
		clLangBottomtoLangTop,
		clLangBottom
	};

	static const Translate::Translation s_aTranslation[2];
	static const Column s_clLang[2];

	enum { eNextPage = 10 };

	void DialogLang_LanguageChanged();

	void UpdateLang();
	void UpdateHeaders();
	void UpdateTranslation();

	void LoadData();
	void SaveData();

	BEGIN_DDX_MAP(ProfileTranslation)
		if(bSaveAndValidate)
		{
		}
		else
		{
			UpdateLang();
			UpdateHeaders();
			UpdateTranslation();
		}
	END_DDX_MAP()

	BEGIN_MSG_MAP(ProfileTranslation)
		MESSAGE_HANDLER(WM_INITDIALOG,OnInitDialog)
		MESSAGE_HANDLER(WM_ACTIVATE, OnActivate)

		COMMAND_ID_HANDLER(IDC_BTNADD,OnAdd)
		COMMAND_ID_HANDLER(IDC_BTNDELETE,OnDelete)

		COMMAND_HANDLER(IDC_RELANGTOP, EN_CHANGE, OnEnChangeLang)
		COMMAND_HANDLER(IDC_RELANGBOTTOM, EN_CHANGE, OnEnChangeLang)

		NOTIFY_HANDLER(IDC_LVTRANSLATION,NM_CLICK,OnClickLVTranslation)
		NOTIFY_HANDLER(IDC_LVTRANSLATION,NM_RCLICK,OnClickLVTranslation)
		NOTIFY_HANDLER(IDC_LVTRANSLATION,LVN_KEYDOWN,OnKeyDownLVTranslation)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnAdd(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnDelete(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnEnChangeLang(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnClickLVTranslation(int code, NMHDR* pnmhdr, BOOL& bHandled);
	LRESULT OnKeyDownLVTranslation(int code, NMHDR* pnmhdr, BOOL& bHandled);
};

#endif // __PROFILETRANSLATION_H__
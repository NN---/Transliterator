#ifndef __GENERALPAGE_H__
#define __GENERALPAGE_H__

#pragma once

#include "optionsstruct.h"
#include "profilechanged.h"

class GeneralPage : public NN::OptionsPageImpl<GeneralPage,OptionsStruct>,
					public NN::DialogLang<GeneralPage>,
					public NN::MessageFilterDlg<GeneralPage>,
					public ProfileChanged
{
public:
	enum { IDD = IDD_PAGEGENERAL };

	NN::auto_value<int,CB_ERR> m_nCurSel;

	void DialogLang_LanguageChanged();
	void UpdateText();

	BEGIN_DDX_MAP(GeneralPage)
		DDX_RADIO(IDC_RADLOADNO,(int&)GetOptions()->m_Options.m_nLoadOnStartUp)
		DDX_CHECK(IDC_CHKSAVETEXTONEXIT,GetOptions()->m_Options.m_bSaveText)
		DDX_RADIO(IDC_RADTEXTREGISTRY,
			(int&)GetOptions()->m_Storage.m_stg[Storage::stgText])
		DDX_RADIO(IDC_RADPROFILESREGISTRY,
			(int&)GetOptions()->m_Storage.m_stg[Storage::stgProfiles])

		DDX_TEXT_STRING(IDC_EDTLANGTOP,GetOptions()->m_Storage.m_astrLang[0]);
		DDX_TEXT_STRING(IDC_EDTLANGBOTTOM,GetOptions()->m_Storage.m_astrLang[1]);

		// Language
		int nLangID = g_LangDefault;
		for(size_t i=0; i<g_nLanguage; ++i)
			if(GetOptions()->m_LangID == g_aLanguage[i])
			{
				nLangID = i;
				break;
			}
		DDX_RADIO(IDC_RADENGLISH,nLangID)
		if(bSaveAndValidate)
		{
			GetOptions()->m_LangID = g_aLanguage[nLangID];
			if(GetOptions()->m_LangID != g_LangID)
				g_UpdateOptions.m_bLanguage = true;
		}
		else
			UpdateText();
	END_DDX_MAP()

	BEGIN_MSG_MAP(GeneralPage)
		NN_MSGFILTER_MESSAGE_ADD()
		COMMAND_ID_HANDLER(IDC_CHKSAVETEXTONEXIT,OnSaveTextOnExit)
	END_MSG_MAP()

	LRESULT OnSaveTextOnExit(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
};

#endif // __GENERALPAGE_H__
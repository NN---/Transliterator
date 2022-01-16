#ifndef __VIEWPAGE_H__
#define __VIEWPAGE_H__

#pragma once

#include "optionsstruct.h"
#include "profilechanged.h"
#include "global.h"

class ViewPage : public NN::OptionsPageImpl<ViewPage,OptionsStruct>,
					public NN::DialogLang<ViewPage>,
					public NN::MessageFilterDlg<ViewPage>,
					public ProfileChanged
{
public:
	enum { IDD = IDD_PAGEVIEW };

	void DialogLang_LanguageChanged();
	void ProfileChanged();

	void FontDialog(LPLOGFONT pLF);
	void UpdateFont();

	BEGIN_DDX_MAP(ViewPage)
		DDX_CHECK(IDC_CHKCAPTIONPROFILE,GetOptions()->m_Options.m_bCaptionProfile)
		DDX_CHECK(IDC_CHKCAPTIONCOUNT,GetOptions()->m_Options.m_bCaptionCount)
		DDX_CHECK(IDC_CHKSTATUSBARCOUNT,GetOptions()->m_Options.m_bStatusBarCount)
		DDX_CHECK(IDC_CHKTRAYICONSHOW,GetOptions()->m_Options.m_bTrayIconShow)
		DDX_CHECK(IDC_CHKTASKBARSHOW,GetOptions()->m_Options.m_bTaskBarShow)
		DDX_RADIO(IDC_RADNORMAL,(int&)GetOptions()->m_Options.m_nPlacement)
		DDX_CHECK(IDC_CHKWRAPTEXT,GetOptions()->m_Options.m_bWrapText)
		DDX_CHECK(IDC_CHKSCROLLTEXT,GetOptions()->m_Options.m_bScrollText)
		if(GetOptions()->m_Options.m_bWrapText != g_Options.m_bWrapText||
			GetOptions()->m_Options.m_bScrollText != g_Options.m_bScrollText)
			g_UpdateOptions.m_bControls = true;
	END_DDX_MAP()

	BEGIN_MSG_MAP(ViewPage)
		NN_MSGFILTER_MESSAGE_ADD()
		NN_MSGFILTER_MESSAGE_REMOVE()

		COMMAND_ID_HANDLER(IDC_BTNFONTLANGTOP,OnFont)
		COMMAND_ID_HANDLER(IDC_BTNFONTLANGBOTTOM,OnFont)
		COMMAND_ID_HANDLER(IDC_BTNFONTPROFILEDETAILS,OnFont)
	END_MSG_MAP()

	LRESULT OnFont(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
};

#endif // __VIEWPAGE_H__
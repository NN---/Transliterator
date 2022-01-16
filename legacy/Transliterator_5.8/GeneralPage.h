#ifndef __GENERALPAGE_H__
#define __GENERALPAGE_H__

#include "trnsoptionspage.h"

class CGeneralPage : public TrnsOptionsPage<CGeneralPage>
{
public:
	enum { IDD=IDD_PAGEGENERAL };

	void FontDialog(LPLOGFONT pLF)
	{
		CFontDialog fontdlg(pLF);
		if(fontdlg.DoModal()==IDOK)
			*pLF=fontdlg.m_lf;
	}

	void UpdateFont()
	{
		char strFont[200];

		HDC hDC = ::GetDC(NULL);
		TEXTMETRIC tm;
		::GetTextMetrics(hDC,&tm);
		for(int i=0;i<Options::nFont;i++)
		{
			const LOGFONT& lf=GetOptions()->m_Options.m_lfFont[i];
			
			wsprintf(strFont,"%s - %d",
				lf.lfFaceName,
				(int)(0 - 
				(
					(double)
					MulDiv(lf.lfHeight, 72,
						GetDeviceCaps(hDC, LOGPIXELSY)) - 0.5)
				)
				);

			if(lf.lfWeight>=FW_BOLD)
				lstrcat(strFont," - Bold");
			if(lf.lfItalic)
				lstrcat(strFont," - Italic");
			if(lf.lfUnderline)
				lstrcat(strFont," - Underline");
			if(lf.lfStrikeOut)
				lstrcat(strFont," - StrikeOut");
			
			SetDlgItemText(IDC_FONTNAMETRNS+i,strFont);
		}
		::ReleaseDC(NULL,hDC);
	}

	BEGIN_DDX_MAP(CGeneralPage)
		DDX_CHECK(IDC_SHOWTRAYICON,GetOptions()->m_Options.m_bShowTrayIcon)
		DDX_CHECK(IDC_SHOWTASKBAR,GetOptions()->m_Options.m_bShowTaskBar)
		DDX_CHECK(IDC_TOPMOST,GetOptions()->m_Options.m_bTopMost)
		DDX_RADIO(IDC_LOADNO,(int&)GetOptions()->m_Options.m_nLoadOnStartUp)
		if(bSaveAndValidate==DDX_LOAD)
			UpdateFont();
	END_DDX_MAP()

	BEGIN_MSG_MAP(CGeneralPage)
		CHAIN_MSG_MAP(TrnsOptionsPage<CGeneralPage>)
		COMMAND_ID_HANDLER(IDC_FONTTRNS,OnFont)
		COMMAND_ID_HANDLER(IDC_FONTRUS,OnFont)
		COMMAND_ID_HANDLER(IDC_FONTTRANSLATION,OnFont)
	END_MSG_MAP()

	LRESULT OnFont(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		FontDialog(&GetOptions()->m_Options.m_lfFont[wID-IDC_FONTTRNS]);
		UpdateFont();
		return 0;
	}
};

#endif // __GENERALPAGE_H__
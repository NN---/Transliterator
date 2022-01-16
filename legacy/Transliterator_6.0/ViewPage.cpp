#include "stdafx.h"

#include "resource.h"

#include "viewpage.h"

void ViewPage::DialogLang_LanguageChanged()
{
	UpdateFont();
	ProfileChanged();
}

void ViewPage::ProfileChanged()
{
	for(size_t i=0; i<2; ++i)
		SetDlgItemText(IDC_BTNFONTLANGTOP+i,
		g_Language.GetCurProfile()->m_astrLang[i].c_str());
}

void ViewPage::FontDialog(LPLOGFONT pLF)
{
	const LOGFONT lfCurrent = *pLF;
	WTL::CFontDialog fontdlg(pLF);
	if(fontdlg.DoModal() == IDOK)
	{
		if(memcmp(pLF,&lfCurrent,sizeof(LOGFONT)))
			g_UpdateOptions.m_bFont = true;
		*pLF = fontdlg.m_lf;
	}
}

void ViewPage::UpdateFont()
{
	HDC hDC = ::GetDC(NULL);
	TEXTMETRIC tm;
	::GetTextMetrics(hDC,&tm);
	const int nLogPixelY = ::GetDeviceCaps(hDC, LOGPIXELSY);

	TCHAR szBold[255];
	ATL::AtlLoadString(IDS_BOLD, szBold, NN_ARRAY_LENGTH(szBold)-1);
	TCHAR szItalic[255];
	ATL::AtlLoadString(IDS_ITALIC, szItalic, NN_ARRAY_LENGTH(szItalic)-1);
	TCHAR szUnderline[255];
	ATL::AtlLoadString(IDS_UNDERLINE, szUnderline, NN_ARRAY_LENGTH(szUnderline)-1);
	TCHAR szStrikeOut[255];
	ATL::AtlLoadString(IDS_STRIKEOUT, szStrikeOut, NN_ARRAY_LENGTH(szStrikeOut)-1);

	static const TCHAR szDivider[] = _T(" - ");

	for(size_t i=0; i<Options::nFonts; ++i)
	{
		const LOGFONT& lf = GetOptions()->m_Options.m_alfFont[i];

		TCHAR szFont[200];
		int size = (int)(0 - (::MulDiv(lf.lfHeight, 72, nLogPixelY) - 0.5));
		wsprintf(szFont,_T("%s - %d"),lf.lfFaceName,size);

		TCHAR* pszFont = szFont;
		if(lf.lfWeight >= FW_BOLD)
		{
			pszFont = _tcscat(pszFont,szDivider);
			pszFont = _tcscat(pszFont,szBold);
		}
		if(lf.lfItalic)
		{
			pszFont = _tcscat(pszFont,szDivider);
			pszFont = _tcscat(pszFont,szItalic);
		}
		if(lf.lfUnderline)
		{
			pszFont = _tcscat(pszFont,szDivider);
			pszFont = _tcscat(pszFont,szUnderline);
		}
		if(lf.lfStrikeOut)
		{
			pszFont = _tcscat(pszFont,szDivider);
			pszFont = _tcscat(pszFont,szStrikeOut);
		}

		SetDlgItemText(IDC_REFONTLANGTOP+i,szFont);
	}

	::ReleaseDC(NULL,hDC);
}

LRESULT ViewPage::OnFont(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	FontDialog(&GetOptions()->m_Options.m_alfFont[wID-IDC_BTNFONTLANGTOP]);
	UpdateFont();

	return 0;
}
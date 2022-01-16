#include "stdafx.h"

#include "resource.h"
#include "global.h"
#include "msg.h"

#include "optionsdlg.h"

void OptionsDlg::DialogLang_LanguageChanged()
{
	m_pageGeneral.UpdateLanguage();
	m_pageView.UpdateLanguage();
	m_pageHotKeys.UpdateLanguage();
	m_pageProfile.UpdateLanguage();
	
	m_ctrlOptions.SetCurSel(GetCurrentPage());
}

void OptionsDlg::NotifyProfileChanged()
{
	m_pageGeneral.NotifyProfileChanged();
	m_pageView.NotifyProfileChanged();
	m_pageHotKeys.NotifyProfileChanged();
	m_pageProfile.NotifyProfileChanged();
}

void OptionsDlg::InitOptionsPage()
{
	GetOptions()->Set(g_Language,g_Options,g_Storage);
	SetOptionsPage();
	DoDataExchange(DDX_LOAD);
}

void OptionsDlg::Apply()
{
	DoDataExchange(DDX_SAVE);

	for(unsigned i = 0;i<Language::nProfiles; ++i)
		if(g_UpdateOptions.m_abProfile[i])
			*g_Language.GetProfile(i) = *GetOptions()->m_Language.GetProfile(i);

	if(g_UpdateOptions.m_bLanguage)
		g_LangID = GetOptions()->m_LangID;
	
	g_Options = GetOptions()->m_Options;
	g_Storage = GetOptions()->m_Storage;
	
	::PostMessage(GetParent(),UWM_APPLY,0,0);
}

LRESULT OptionsDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// Options Control
	m_ctrlOptions = GetDlgItem(IDC_LSTOPTIONS);

	// Create Pages
	m_pageGeneral.Create(m_hWnd);
	m_pageView.Create(m_hWnd);
	m_pageHotKeys.Create(m_hWnd);
	m_pageProfile.Create(m_hWnd);
	
	// Add Pages
	AddPage(&m_pageGeneral);
	AddPage(&m_pageView);
	AddPage(&m_pageHotKeys);
	AddPage(&m_pageProfile);

	// Move Pages
	RECT rect;
	::GetWindowRect(GetDlgItem(IDC_GRPOPTIONPLACE),&rect);
	ScreenToClient(&rect);
	for(int i=0; i<GetPageCount(); ++i)
		GetPage(i)->MoveWindow(&rect);

	// Init
	InitOptionsPage();
		
	// CurrentPage
	SetCurrentPage(0);

	return 0;
}

LRESULT OptionsDlg::OnShowWindow(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// Hide
	if(!wParam)
		InitOptionsPage();

	return 0;
}

LRESULT OptionsDlg::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	DestroyOptions();

	return 0;
}

LRESULT OptionsDlg::OnActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
{
	for(int i=0; i<GetPageCount(); ++i)
		GetPage(i)->SendMessage(uMsg,wParam,lParam);

	return 0;
}

LRESULT OptionsDlg::OnOKApply(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	Apply();
	if(wID == IDOK)
		CloseDialog();

	return 0;
}

LRESULT OptionsDlg::OnSelChangeLstOptions(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	SetCurrentPage(m_ctrlOptions.GetCurSel());
	return 0;
}
#include "stdafx.h"

#include "resource.h"
#include "optionsstruct.h"
#include "controls.h"

#include "profilepage.h"

void ProfilePage::DialogLang_LanguageChanged()
{
	InitCmbProfile(
		GetDlgItem(IDC_CMBPROFILE),
		m_nCurProfile,
		GetOptions()->m_Storage);

	m_profileTranslation.UpdateLanguage();
	m_profileIgnore.UpdateLanguage();
	m_profileExportImport.UpdateLanguage();
	m_profileCopyProfile.UpdateLanguage();
	m_profileName.UpdateLanguage();
	m_profileReset.UpdateLanguage();
}

void ProfilePage::ProfileChanged()
{
}

void ProfilePage::UpdateProfile()
{
	m_ps.m_nProfile = (unsigned)m_nCurProfile;
	m_ps.m_pProfile = GetOptions()->m_Language.GetProfile((unsigned)m_nCurProfile);
	m_ps.m_pStorage = &GetOptions()->m_Storage;
	
	for(int i=0; i<GetPageCount(); ++i)
		GetPage(i)->SetOptions(&m_ps);
}

LRESULT ProfilePage::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	m_profileTranslation.Create(m_hWnd);
	m_profileIgnore.Create(m_hWnd);
	m_profileExportImport.Create(m_hWnd);
	m_profileCopyProfile.Create(m_hWnd);
	m_profileName.Create(m_hWnd);
	m_profileReset.Create(m_hWnd);

	// Add Tabs
	AddPage(&m_profileTranslation);
	AddPage(&m_profileIgnore);
	AddPage(&m_profileExportImport);
	AddPage(&m_profileCopyProfile);
	AddPage(&m_profileName);
	AddPage(&m_profileReset);

	// Move Pages
	RECT rect;
	::GetWindowRect(GetDlgItem(IDC_GRPPROFILEACTION),&rect);
	ScreenToClient(&rect);
	for(int i=0; i<GetPageCount(); ++i)
		GetPage(i)->MoveWindow(&rect);

	// Init Tabs
	m_tabAction = GetDlgItem(IDC_TABPROFILEACTION);
	TCITEM tcitem = {};
	for(int i=0; i<GetPageCount(); ++i)
		m_tabAction.InsertItem(i, &tcitem);

	// CurrentPage
	SetCurrentPage(0);
	SendDlgItemMessage(IDC_CMBPROFILE, CB_SETCURSEL, 0, 0);

	return 0;
}

LRESULT ProfilePage::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	DestroyOptions();

	return 0;
}

LRESULT ProfilePage::OnActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
{
	for(int i=0; i<GetPageCount(); ++i)
		GetPage(i)->SendMessage(uMsg,wParam,lParam);

	return 0;
}

LRESULT ProfilePage::OnProfileName(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	UpdateLanguage();

	return 0;
}

LRESULT ProfilePage::OnProfileChange(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	DoDataExchange(DDX_LOAD);
	UpdateLanguage();
	g_UpdateOptions.m_abProfile[m_nCurProfile] = true;

	return 0;
}

LRESULT ProfilePage::OnProfileCopyProfile(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
{
	*GetOptions()->m_Language.GetProfile((unsigned)lParam) = 
		*GetOptions()->m_Language.GetProfile((unsigned)wParam);

	UpdateLanguage();
	DoDataExchange(DDX_LOAD);

	g_UpdateOptions.m_abProfile[lParam] = true;

	return 0;
}

LRESULT ProfilePage::OnProfileUpdate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	g_UpdateOptions.m_abProfile[m_nCurProfile] = true;

	return 0;
}

LRESULT ProfilePage::OnProfileReset(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	struct Reset_Func
	{
		ProfileReset::Reset reset;
		void (*pFReset)(unsigned,LangProfile&);
	};

	static const Reset_Func aReset_Func[] = 
	{
		{ProfileReset::resetTranslation,	Language::ResetTranslation	},
		{ProfileReset::resetIgnore,		Language::ResetIgnore		},
		{ProfileReset::resetIgnoreText,	Language::ResetIgnoreText	},
		{ProfileReset::resetName,			Language::ResetName			},
	};

	LangProfile* pProfile = GetOptions()->m_Language.GetProfile(m_nCurProfile);

	for(size_t i=0; i<NN_ARRAY_LENGTH(aReset_Func); ++i)
		if(wParam & aReset_Func[i].reset)
			(*aReset_Func[i].pFReset)(m_nCurProfile,*pProfile);

	if(wParam & ProfileReset::resetName)
		GetOptions()->m_Storage.m_astrProfile[m_nCurProfile] = 
		Storage::s_aszProfileName[m_nCurProfile];

	InitCmbProfile(GetDlgItem(IDC_CMBPROFILE), m_nCurProfile, GetOptions()->m_Storage);
	DoDataExchange(DDX_LOAD);

	g_UpdateOptions.m_abProfile[m_nCurProfile] = true;

	return 0;
}

LRESULT ProfilePage::OnCmbSelChangeProfileName(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	DoDataExchange(DDX_SAVE);
	SetCurrentPage(m_tabAction.GetCurSel());
	m_nCurProfile = SendDlgItemMessage(IDC_CMBPROFILE,CB_GETCURSEL);
	GetOptions()->m_Language.SetCurProfile(m_nCurProfile);
	DoDataExchange(DDX_LOAD);
	
	return 0;
}

LRESULT ProfilePage::OnTcnSelChangeProfileAction(int /*code*/, NMHDR* /*pnmhdr*/, BOOL& /*bHandled*/)
{
	SetCurrentPage(m_tabAction.GetCurSel());

	return 0;
}
#include "stdafx.h"

#include "resource.h"
#include "settings.h"
#include "error.h"
#include "msg.h"

#include "profileexportimport.h"

void ProfileExportImport::DialogLang_LanguageChanged()
{
	SetDlgItemText(IDC_EDTPATH,m_szPath);
}

LRESULT ProfileExportImport::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	m_szPath[0] = 0;
	SendDlgItemMessage(IDC_EDTPATH,EM_SETLIMITTEXT,(WPARAM)MAX_PATH,0);

	CheckDlgButton(IDC_CHKUNICODE,TRUE);

	return 0;
}

LRESULT ProfileExportImport::OnExport(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	const BOOL bUnicode = IsDlgButtonChecked(IDC_CHKUNICODE);

	GetDlgItemText(IDC_EDTPATH,m_szPath,MAX_PATH);
	
	ATL::CAtlFile file;
	file.Create(
		m_szPath,
		GENERIC_WRITE,
		NULL,
		CREATE_ALWAYS);

	if(!file)
		return 0;
	file.SetSize(0);

	try
	{
		LangString str;
		Settings::PrepareSaveProfileFile(GetOptions()->m_pProfile,str);

		if(bUnicode)
		{
			file.Write(
				&Settings::s_cUnicodeHeader,
				sizeof(Settings::s_cUnicodeHeader));
			file.Write(str.c_str(),str.length()*sizeof(WCHAR));
		}
		else
			file.Write(NN::CharAWT<const char>(str.c_str()),str.length()*sizeof(char));

		WTL::AtlMessageBox(m_hWnd, IDS_DONE,IDR_TRANSLITERATOR,MB_OK|MB_ICONINFORMATION);
	}
	catch(...)
	{
		ShowError(m_hWnd, IDS_EXPORT);
	}

	return 0;
}

LRESULT ProfileExportImport::OnImport(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	GetDlgItemText(IDC_EDTPATH,m_szPath,MAX_PATH);
	
	TCHAR* pszPathIni = m_szPath+_tcslen(m_szPath)-_tcslen(Settings::s_szIni);

	if(!_tcscmp(pszPathIni, Settings::s_szIni))
		*pszPathIni = 0;

	LangProfile profile;
	size_t reset = Settings::LoadProfileFile(m_szPath, &profile);
	if(reset != Settings::resetAll)
	{
		*GetOptions()->m_pProfile = profile;

		// Reset what wasn't imported
		if(reset & Settings::resetName)
			Language::ResetName(GetOptions()->m_nProfile, *GetOptions()->m_pProfile);
		if(reset & Settings::resetTranslation)
			Language::ResetTranslation(GetOptions()->m_nProfile, *GetOptions()->m_pProfile);
		if(reset & Settings::resetIgnore)
			Language::ResetIgnore(GetOptions()->m_nProfile, *GetOptions()->m_pProfile);
		if(reset & Settings::resetIgnoreText)
			Language::ResetIgnoreText(GetOptions()->m_nProfile, *GetOptions()->m_pProfile);
		
		GetParent().PostMessage(UWM_PROFILECHANGE);

		WTL::AtlMessageBox(m_hWnd, IDS_DONE, IDR_TRANSLITERATOR, MB_OK|MB_ICONINFORMATION);

		InvalidateRect(NULL);
	}
	else
		ShowError(m_hWnd, IDS_IMPORT);

	return 0;
}

LRESULT ProfileExportImport::OnBrowse(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	static const TCHAR szFilter[] = _T("Profile (*.ini*)\0*.ini\0All Files (*.*)\0*.*\0");

	WTL::CFileDialog fd(
		TRUE,
		Settings::s_szIni,
		NULL,
		OFN_HIDEREADONLY,
		szFilter);

	if(fd.DoModal() == IDOK)
	{
		_tcscpy(m_szPath,fd.m_szFileName);
		SetDlgItemText(IDC_EDTPATH,m_szPath);
	}

	return 0;
}
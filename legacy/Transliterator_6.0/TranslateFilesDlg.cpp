#include "stdafx.h"

#include "resource.h"
#include "language.h"
#include "global.h"
#include "controls.h"
#include "error.h"
#include "translatefiles.h"
#include "settings.h"

#include "translatefilesdlg.h"

void TranslateFilesDlg::UpdateCmbProfile()
{
	InitCmbProfile(GetDlgItem(IDC_CMBPROFILE));
}

void TranslateFilesDlg::UpdatePath()
{
	DoDataExchange(DDX_SAVE);
	if(!m_tf.m_szPath[0])
	{
		EnableAll(FALSE);
		return;
	}

	DWORD dwAttr = GetFileAttributes(m_tf.m_szPath);
	
	if(dwAttr == (DWORD)-1)
	{
		EnableAll(FALSE);
		return;
	}

	EnableExtra(TRUE);
	EnableIgnore(TRUE);
	EnableDirection(TRUE);
	EnableProfile(TRUE);
	
	if(dwAttr & FILE_ATTRIBUTE_DIRECTORY)
	{
		EnableFolder(TRUE);
		EnableFile(m_tf.m_bAllFiles);
	}
	else
	{
		EnableFolder(FALSE);
		EnableFile(TRUE);
	}
}

void TranslateFilesDlg::DialogLang_LanguageChanged()
{
	UpdateCmbProfile();
	
	WTL::CComboBox cmbDir = GetDlgItem(IDC_CMBDIRECTION);
	int nCurSel = cmbDir.GetCurSel();
	InitCmbDir(
		cmbDir,
		nCurSel = CB_ERR?0:nCurSel,
		g_Language.GetProfile(m_tf.m_nProfile));
	m_cmbPath.LoadEntries(Settings::s_hkProgKey,Settings::s_szProgPath,_T("Path"));
}

void TranslateFilesDlg::EnableFile(BOOL bEnable)
{
	::EnableWindow(GetDlgItem(IDC_CHKNAME),bEnable);
	::EnableWindow(GetDlgItem(IDC_CHKENTRY),bEnable);
	::EnableWindow(GetDlgItem(IDC_CHKMP3TAGV1),bEnable);
	::EnableWindow(GetDlgItem(IDC_CHKMP3TAGV2),bEnable);
}

void TranslateFilesDlg::EnableFolder(BOOL bEnable)
{
	::EnableWindow(GetDlgItem(IDC_CHKSELFOLDER),bEnable);
	::EnableWindow(GetDlgItem(IDC_CHKALLFILES),bEnable);
	::EnableWindow(GetDlgItem(IDC_CHKALLFOLDERS),bEnable);
	::EnableWindow(GetDlgItem(IDC_CHKALLSUBFOLDERS),bEnable);
}

void TranslateFilesDlg::EnableExtra(BOOL bEnable)
{
	::EnableWindow(GetDlgItem(IDC_EDTPREFIX),bEnable);
	::EnableWindow(GetDlgItem(IDC_EDTSUFFIX),bEnable);
}

void TranslateFilesDlg::EnableIgnore(BOOL bEnable)
{
	::EnableWindow(GetDlgItem(IDC_CHKUSEIGNORE),bEnable);
}

void TranslateFilesDlg::EnableDirection(BOOL bEnable)
{
	::EnableWindow(GetDlgItem(IDC_CMBDIRECTION),bEnable);
}

void TranslateFilesDlg::EnableProfile(BOOL bEnable)
{
	::EnableWindow(GetDlgItem(IDC_CMBPROFILE),bEnable);
}

void TranslateFilesDlg::EnableAll(BOOL bEnable)
{
	EnableFile(bEnable);
	EnableFolder(bEnable);
	EnableExtra(bEnable);
	EnableIgnore(bEnable);
	EnableDirection(bEnable);
	EnableProfile(bEnable);
}

LRESULT TranslateFilesDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	memset(&m_tf,0,sizeof(m_tf));
	m_cmbPath.SubclassWindow(GetDlgItem(IDC_CMBPATH));
	
	SendDlgItemMessage(IDC_CMBPATH,CB_LIMITTEXT,(WPARAM)TranslateFiles::nPath,0);
	SendDlgItemMessage(IDC_EDTPREFIX,EM_LIMITTEXT,(WPARAM)TranslateFiles::nPrefix,0);
	SendDlgItemMessage(IDC_EDTSUFFIX,EM_LIMITTEXT,(WPARAM)TranslateFiles::nSuffix,0);
	
	DoDataExchange(DDX_LOAD);

	EnableAll(FALSE);

	return 0;
}

LRESULT TranslateFilesDlg::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	m_cmbPath.SaveEntries(Settings::s_hkProgKey,Settings::s_szProgPath,_T("Path"));
	return 0;
}

LRESULT TranslateFilesDlg::OnTranslate(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	DoDataExchange(DDX_SAVE);
	if(m_tf.Translate())
	{
		m_cmbPath.AddEntry();
		WTL::AtlMessageBox(m_hWnd, IDS_DONE,IDR_TRANSLITERATOR,MB_OK|MB_ICONINFORMATION);
	}
	else
		ShowError(m_hWnd, IDS_TRANSLATEFILES);

	return 0;
}

LRESULT TranslateFilesDlg::OnBrowse(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	WTL::CFolderDialog fd(m_hWnd, 0,BIF_BROWSEINCLUDEFILES|BIF_VALIDATE);

	if(fd.DoModal() == IDOK)
	{
		SetDlgItemText(IDC_CMBPATH,fd.m_szFolderPath);
		UpdatePath();
	}
	return 0;
}

LRESULT TranslateFilesDlg::OnAllFiles(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	EnableFile(IsDlgButtonChecked(IDC_CHKALLFILES));
	return 0;
}

LRESULT TranslateFilesDlg::OnCbnSelChangeProfile(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	m_tf.m_nProfile = SendDlgItemMessage(IDC_CMBPROFILE,CB_GETCURSEL,0,0);

	WTL::CComboBox cmbDir = GetDlgItem(IDC_CMBDIRECTION);
	int nCurSel = cmbDir.GetCurSel();
	InitCmbDir(
		cmbDir,
		nCurSel = CB_ERR?0:nCurSel,
		g_Language.GetProfile(m_tf.m_nProfile));

	return 0;
}


LRESULT TranslateFilesDlg::OnCbnEditChangePath(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	UpdatePath();
	return 0;
}

LRESULT TranslateFilesDlg::OnCbnSelChangePath(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	m_cmbPath.GetLBText(m_cmbPath.GetCurSel(),m_tf.m_szPath);
	m_cmbPath.SetWindowText(m_tf.m_szPath);
	UpdatePath();
	return 0;
}
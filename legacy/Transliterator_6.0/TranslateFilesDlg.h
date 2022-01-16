#ifndef __TRANSLAGEFILESDLG_H__
#define __TRANSLAGEFILESDLG_H__

#pragma once

#include "translatefiles.h"

class TranslateFilesDlg : public ATL::CDialogImpl<TranslateFilesDlg>,
						public WTL::CWinDataExchange<TranslateFilesDlg>,
						public NN::DialogLang<TranslateFilesDlg>,
						public NN::MessageFilterDlg<TranslateFilesDlg>,
						public NN::ToolWindow<TranslateFilesDlg>
{
public:
	enum { IDD = IDD_TRANSLATEFILES };

	// Data
	TranslateFiles m_tf;

	// Controls
	NN::ComboBoxMRUCtrl m_cmbPath;

	// Update
	void UpdateCmbProfile();
	void UpdatePath();

	// Language
	void DialogLang_LanguageChanged();

	// Enable
	void EnableFile(BOOL bEnable);
	void EnableFolder(BOOL bEnable);
	void EnableExtra(BOOL bEnable);
	void EnableIgnore(BOOL bEnable);
	void EnableDirection(BOOL bEnable);
	void EnableProfile(BOOL bEnable);
	void EnableAll(BOOL bEnable);

	BEGIN_DDX_MAP(TranslateFilesDlg)
		DDX_CHECK(IDC_CHKUSEIGNORE,m_tf.m_bUseIgnore)
		DDX_CHECK(IDC_CHKSELFOLDER,m_tf.m_bSelFolder)
		DDX_CHECK(IDC_CHKALLFILES,m_tf.m_bAllFiles)
		DDX_CHECK(IDC_CHKALLFOLDERS,m_tf.m_bAllFolders)
		DDX_CHECK(IDC_CHKALLSUBFOLDERS,m_tf.m_bAllSubFolders)
		DDX_CHECK(IDC_CHKNAME,m_tf.m_bName)
		DDX_CHECK(IDC_CHKENTRY,m_tf.m_bEntry)
		DDX_CHECK(IDC_CHKMP3TAGV1,m_tf.m_bMP3TagV1)
		DDX_CHECK(IDC_CHKMP3TAGV2,m_tf.m_bMP3TagV2)
		DDX_COMBO_SEL(IDC_CMBPROFILE,(int&)m_tf.m_nProfile)
		DDX_COMBO_SEL(IDC_CMBDIRECTION,m_tf.m_nDirection)
		DDX_TEXT(IDC_EDTPREFIX,m_tf.m_szPrefix)
		DDX_TEXT(IDC_EDTSUFFIX,m_tf.m_szSuffix)
		DDX_TEXT(IDC_CMBPATH,m_tf.m_szPath)
	END_DDX_MAP()
	
	BEGIN_MSG_MAP(TranslateFilesDlg)
		NN_MSGFILTER_MESSAGE_ADD()
		NN_MSGFILTER_MESSAGE_REMOVE()
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		
		COMMAND_ID_HANDLER(IDOK, OnTranslate)
		COMMAND_ID_HANDLER(IDC_BTNTRANSLATE, OnTranslate)
		COMMAND_ID_HANDLER(IDC_BTNBROWSE, OnBrowse)
		COMMAND_ID_HANDLER(IDC_CHKALLFILES, OnAllFiles)
		COMMAND_HANDLER(IDC_CMBPROFILE, CBN_SELCHANGE, OnCbnSelChangeProfile)
		COMMAND_HANDLER(IDC_CMBPATH, CBN_EDITCHANGE, OnCbnEditChangePath)
		COMMAND_HANDLER(IDC_CMBPATH, CBN_SELCHANGE, OnCbnSelChangePath)
		
		CHAIN_MSG_MAP(NN::ToolWindow<TranslateFilesDlg>)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnTranslate(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnBrowse(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnAllFiles(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnCbnSelChangeProfile(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnCbnEditChangePath(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnCbnSelChangePath(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
};

#endif // __TRANSLAGEFILESDLG_H__
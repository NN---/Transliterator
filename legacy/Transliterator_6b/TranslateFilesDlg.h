#ifndef __TRANSLAGEFILESDLG_H__
#define __TRANSLAGEFILESDLG_H__

class CTranslateFilesDlg : public CDialogImpl<CTranslateFilesDlg>,
						public CWinDataExchange<CTranslateFilesDlg>,
						public NN::DialogLang<CTranslateFilesDlg>,
						public NN::MessageFilterDlg<CTranslateFilesDlg>,
						public NN::ToolWindow<CTranslateFilesDlg>
{
public:
	enum { IDD=IDD_TRANSLATEFILES } ;

	NN::AutoValue<BOOL,FALSE> m_bFiles;
	NN::AutoValue<BOOL,FALSE> m_bFolders;
	NN::AutoValue<BOOL,FALSE> m_bSubFolders;
	NN::AutoValue<BOOL,FALSE> m_bThisFolder;
	NN::AutoValue<BOOL,FALSE> m_bName;
	NN::AutoValue<BOOL,FALSE> m_bEntry;
	NN::AutoValue<BOOL,FALSE> m_bMP3Tags;
	NN::AutoValue<Translate::Direction,Translate::dirTrnstoRus> m_nDirection;
	TCHAR m_szPath[_MAX_PATH];
	LangProfile* m_pProfile;

	void UpdateCmbProfile();

	void TranslateFile(LPCSTR szPath,Translate::Direction dir);
	void TranslateEntryMP3Tags(LPCSTR szFile,Translate::Direction dir,bool bEntry);
	void Translate(LPCSTR szPath);
	void TranslateThisFolder();

	void TranslateTag(LPSTR szTag,Translate::Direction dir);

	void UpdateLanguage();

	void EnableDirs(BOOL bEnable);
	void EnableFiles(BOOL bEnable);

	BEGIN_DDX_MAP(CTranslateFilesDlg)
		DDX_RADIO(IDC_TRNSTORUS,(int&)m_nDirection)
		DDX_CHECK(IDC_FILES,m_bFiles)
		DDX_CHECK(IDC_FOLDERS,m_bFolders)
		DDX_CHECK(IDC_SUBFOLDERS,m_bSubFolders)
		DDX_CHECK(IDC_SELFOLDER,m_bThisFolder)
		DDX_CHECK(IDC_NAME,m_bName)
		DDX_CHECK(IDC_ENTRY,m_bEntry)
		DDX_CHECK(IDC_MP3TAGS,m_bMP3Tags)
		DDX_TEXT(IDC_PATH,m_szPath)
	END_DDX_MAP()
	
	BEGIN_MSG_MAP(CTranslateFilesDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDC_CLOSE, NN::ToolWindow<CTranslateFilesDlg>::OnCloseCmd)
		COMMAND_ID_HANDLER(IDOK, OnTranslate)
		COMMAND_ID_HANDLER(IDC_TRANSLATE, OnTranslate)
		COMMAND_ID_HANDLER(IDC_BROWSE, OnBrowse)
		COMMAND_ID_HANDLER(IDC_FILES, OnFiles)
		COMMAND_HANDLER(IDC_PROFILE, CBN_SELCHANGE, OnSelChangeProfile)
		COMMAND_HANDLER(IDC_PATH, EN_CHANGE, OnEnChangePath)
		CHAIN_MSG_MAP(NN::ToolWindow<CTranslateFilesDlg>)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnTranslate(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnBrowse(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnFiles(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnSelChangeProfile(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnEnChangePath(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
};

#endif // __TRANSLAGEFILESDLG_H__
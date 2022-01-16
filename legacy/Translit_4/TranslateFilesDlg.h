#ifndef __TRANSLAGEFILESDLG_H__
#define __TRANSLAGEFILESDLG_H__

class CTranslateFilesDlg : public CDialogImpl<CTranslateFilesDlg>,
						public CWinDataExchange<CTranslateFilesDlg>,
						public NN::DialogLang<CTranslateFilesDlg>
{
public:
	enum { IDD=IDD_TRANSLATEFILES } ;

	NN::AutoValue<BOOL,TRUE> m_bFiles;
	NN::AutoValue<BOOL,FALSE> m_bDirectories;
	NN::AutoValue<BOOL,FALSE> m_bSubDirectories;
	NN::AutoValue<BOOL,FALSE> m_bThisDirectory;
	NN::AutoValue<BOOL,TRUE> m_bName;
	NN::AutoValue<BOOL,FALSE> m_bEntry;
	NN::AutoValue<BOOL,FALSE> m_bMP3Tags;
	NN::AutoValue<Translate::Direction,Translate::dirEngtoRus> m_nDirection;
	TCHAR m_szPath[_MAX_PATH];

	static void TranslateFile(LPCSTR szPath,Translate::Direction dir);
	static void TranslateEntryMP3Tags(LPCSTR szFile,Translate::Direction dir,bool bEntry);
	void Translate(LPCSTR szPath);
	void TranslateThisDirectory();

	static void TranslateTag(LPSTR szTag,Translate::Direction dir);

	BEGIN_DDX_MAP(CChangeTranslationDlg)
		DDX_TEXT(IDC_PATH,m_szPath)
		DDX_CHECK(IDC_FILES,m_bFiles)
		DDX_CHECK(IDC_DIRECTORIES,m_bDirectories)
		DDX_CHECK(IDC_SUBDIRECTORIES,m_bSubDirectories)
		DDX_CHECK(IDC_THISDIRECTORY,m_bThisDirectory)
		DDX_CHECK(IDC_NAME,m_bName)
		DDX_CHECK(IDC_ENTRY,m_bEntry)
		DDX_CHECK(IDC_MP3TAGS,m_bMP3Tags)
		DDX_RADIO(IDC_ENGTORUS,(int&)m_nDirection)
	END_DDX_MAP()
	
	BEGIN_MSG_MAP(CChangeTranslationDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
		COMMAND_ID_HANDLER(IDC_CLOSE, OnCloseCmd)
		COMMAND_ID_HANDLER(IDOK, OnTranslate)
		COMMAND_ID_HANDLER(IDC_TRANSLATE, OnTranslate)
		COMMAND_ID_HANDLER(IDC_BROWSE, OnBrowse)
		COMMAND_ID_HANDLER(IDC_FILES, OnFiles)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCloseCmd(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnTranslate(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnBrowse(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnFiles(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
};

#endif // __TRANSLAGEFILESDLG_H__
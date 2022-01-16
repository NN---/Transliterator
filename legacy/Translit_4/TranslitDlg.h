#ifndef __TRANSLITDLG_H__
#define __TRANSLITDLG_H__

class CTranslitDlg : public CDialogImpl<CTranslitDlg>,
					public CUpdateUI<CTranslitDlg>,
					public CMessageFilter,
					public CIdleHandler,
					public CDialogResize<CTranslitDlg>,
					public NN::TrayIcon<CTranslitDlg>,
					public NN::DialogStatusBarMenu<CTranslitDlg>,
					public NN::DialogIcon<CTranslitDlg>,
					public NN::DialogLang<CTranslitDlg>
{
public:
	// Members
	enum { IDD=IDR_TRANSLIT } ;
	enum { Eng , Rus };

	enum { hkID = 1000 };

	HACCEL m_hAccel;
	bool m_bShown;
	bool m_bTrayIcon;
	bool m_bDlg;

	CRichEditCtrl m_reEngRus[2];

	CTranslitDlg();

	// Virtual Functions
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnIdle();

	// Functions
	void Translate(Translate::Direction dir);
	BOOL Show();
	void CloseDialog();

	void SetOptionsFont();
	void SetOptions();

	void SaveRegistry();
	void LoadRegistry();

	void UpdateTrayIcon();
	void SaveWindowPlacement();

	static HWND GetActiveWindowChild();
	void HotKeyTranslation(Translate::Direction dir);
	void HotKeyShowTranslit(bool bShow);

	Translate::Direction DefineDirection(Translate::Direction dir,LPCSTR szText);
	Translate::Direction DefineDirection(Translate::Direction dir,LPCWSTR szText);
	
	void InitControls();
	void InitMessageLoop();

	// Maps
	BEGIN_UPDATE_UI_MAP(CTranslitDlg)
		UPDATE_ELEMENT(ID_EDIT_UNDO,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_EDIT_REDO,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_EDIT_CUT,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_EDIT_COPY,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_EDIT_PASTE,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_EDIT_SELECT_ALL,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_EDIT_CLEAR,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_EDIT_CLEAR_ALL,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_EDIT_TRANSLATE,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_VIEW_LANGUAGE_ENGLISH,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_VIEW_LANGUAGE_RUSSIAN,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_VIEW_LAYOUT_WRAPTEXT,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_VIEW_LAYOUT_SCROLLTEXT,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_TOOLS_TRANSLATION,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_SHOW,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_HIDE,UPDUI_MENUPOPUP)
	END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP(CTranslitDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_SYSCOMMAND, OnSysCommand)
		MESSAGE_HANDLER(WM_HOTKEY, OnHotKey)
		COMMAND_ID_HANDLER(ID_APP_EXIT, OnAppExit)
		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
		COMMAND_RANGE_HANDLER(ID_EDIT_CLEAR,ID_EDIT_REDO,OnEditCommands)
		COMMAND_ID_HANDLER(ID_EDIT_TRANSLATE, OnEditTranslate)
		COMMAND_ID_HANDLER(ID_EDIT_NOTRANSLATE_INSERT, OnEditNoTranslate)
		COMMAND_ID_HANDLER(ID_EDIT_NOTRANSLATE_DELETE, OnEditNoTranslate)
		COMMAND_ID_HANDLER(ID_EDIT_COPY_ENGTORUS, OnEditCopyEngRus)
		COMMAND_ID_HANDLER(ID_EDIT_COPY_RUSTOENG, OnEditCopyEngRus)
		COMMAND_ID_HANDLER(ID_VIEW_LANGUAGE_ENGLISH, OnViewLanguage)
		COMMAND_ID_HANDLER(ID_VIEW_LANGUAGE_RUSSIAN, OnViewLanguage)
		COMMAND_ID_HANDLER(ID_VIEW_LAYOUT_WRAPTEXT, OnViewLayoutWrapScrollText)
		COMMAND_ID_HANDLER(ID_VIEW_LAYOUT_SCROLLTEXT, OnViewLayoutWrapScrollText)

		COMMAND_ID_HANDLER(ID_TOOLS_TRANSLATEFILES, OnToolsTranslateFiles)
		COMMAND_ID_HANDLER(ID_TOOLS_OPTIONS, OnToolsOptions)

		COMMAND_HANDLER(IDC_ENG, EN_CHANGE, OnEnChangeEngRus)
		COMMAND_HANDLER(IDC_RUS, EN_CHANGE, OnEnChangeEngRus)
		NOTIFY_HANDLER(IDC_ENG, EN_MSGFILTER, OnEnMsgFilterEngRus)
		NOTIFY_HANDLER(IDC_RUS, EN_MSGFILTER, OnEnMsgFilterEngRus)

		COMMAND_ID_HANDLER(ID_SHOW, OnShowHide)
		COMMAND_ID_HANDLER(ID_HIDE, OnShowHide)
		
		CHAIN_MSG_MAP(NN::DialogStatusBarMenu<CTranslitDlg>)
		CHAIN_MSG_MAP(NN::TrayIcon<CTranslitDlg>)
		CHAIN_MSG_MAP(CDialogResize<CTranslitDlg>)
		CHAIN_MSG_MAP(CUpdateUI<CTranslitDlg>)
	END_MSG_MAP()

	BEGIN_DLGRESIZE_MAP(CTranslitDlg)
		BEGIN_DLGRESIZE_GROUP()
			DLGRESIZE_CONTROL(IDC_SSEPARATOR, DLSZ_SIZE_X)
			DLGRESIZE_CONTROL(IDC_SENGTEXT, DLSZ_MOVE_Y)
			DLGRESIZE_CONTROL(IDC_SRUSTEXT, DLSZ_MOVE_Y)
			DLGRESIZE_CONTROL(IDC_ENG, DLSZ_SIZE_X|DLSZ_SIZE_Y)
			DLGRESIZE_CONTROL(IDC_RUS, DLSZ_SIZE_X|DLSZ_SIZE_Y)
		END_DLGRESIZE_GROUP()
	END_DLGRESIZE_MAP()

	// Map Functions
	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnHotKey(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnAppExit(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnAppAbout(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnEditCommands(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnEditTranslate(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnEditNoTranslate(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnEditCopyEngRus(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnViewLanguage(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnViewLayoutWrapScrollText(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnToolsTranslateFiles(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);	
	LRESULT OnToolsOptions(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);	
	
	LRESULT OnEnChangeEngRus(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnEnMsgFilterEngRus(int code, NMHDR* pnmhdr, BOOL& bHandled);

	LRESULT OnShowHide(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
};

#endif // __TRANSLITDLG_H__
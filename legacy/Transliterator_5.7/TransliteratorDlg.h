#ifndef __TRANSLITERATORDLG_H__
#define __TRANSLITERATORDLG_H__

#include "translatefilesdlg.h"
#include "translationdlg.h"
#include "optionsdlg.h"
#include "aboutdlg.h"

class CTransliteratorDlg : public CDialogImpl<CTransliteratorDlg>,
					public CUpdateUI<CTransliteratorDlg>,
					public CIdleHandler,
					public CDialogResize<CTransliteratorDlg>,
					public NN::TrayIcon<CTransliteratorDlg>,
					public NN::DialogStatusBarMenu<CTransliteratorDlg>,
					public NN::DialogIcon<CTransliteratorDlg>,
					public NN::DialogLang<CTransliteratorDlg>,
					public NN::MessageFilterDlgAccel<CTransliteratorDlg>
{
public:
	enum { IDD=IDR_TRANSLITERATOR } ;
	enum { Trns , Rus };
	enum
	{
		size_delta_left = 5,
		size_delta_right = 5,
		size_delta_top = 15,
		size_delta_bottom = 5
	};
	enum { CP = 1251 };
	enum { hkID = 1000 };

	// Static
	static const LANGID s_langEnglish;
	static const LANGID s_langRussian;
	static const LANGID s_langTranslit;

	// Text
	NN::AutoArray<wchar_t> m_aText[2];

	// Members
	NN::AutoValue<HACCEL> m_hAccel;
	POINT m_ptMinTrackSize;
	NN::AutoValue<bool,false> m_bTrayIcon;
	NN::AutoValue<bool,false> m_bShown;
	
	CMultiPaneStatusBarCtrl m_wndStatusBar;
	CRichEditCtrl m_reTrnsRus[2];

	enum { nTrnsRus = 30 };
	char m_strTrnsRus[2][nTrnsRus];

	// Dialogs
	CTranslationDlg m_dlgTranslation;
	CTranslateFilesDlg m_dlgTranslateFiles;
	COptionsDlg m_dlgOptions;
	CAboutDlg m_dlgAbout;

	// Virtual Functions
	virtual BOOL OnIdle();
	
	// Override
	void DlgResize_UpdateLayout(int cxWidth, int cyHeight);

	// Not Virtual
	void Translate(Translate::Direction dir);
	bool Show();
	void CloseDialog();
	void UpdateLayout();

	BOOL CTransliteratorDlg::LoadData(CRegKey& reg,const char* strData,void* data,unsigned size);
	BOOL CTransliteratorDlg::LoadDataSize(CRegKey& reg,const char* strData,void* data,unsigned size);
	void LoadSettings();
	void SaveSettings();
	
	void SetOptions(bool bFirst=false);
	void SetOptionsFont();

	void UpdateCount();
	void UpdateTrayIcon();
	void UpdateTaskBar();
	void UpdateStatusBar();
	void SaveWindowPlacement();

	void UpdateTrnsRusString();

	static HWND GetActiveWindowChild();
	void HotKeyText(Translate::Direction dir,HWND hWndTransliterator,void (*pDo)(char*,Translate::Direction,int,HWND));
	static void HotKeyTranslate(char* pText,Translate::Direction dir,int nChar,HWND);
	static void HotKeyCopy(char* pText,Translate::Direction dir,int nChar,HWND hWndTransliterator);
	void HotKeyShow(bool bShow);

	static Translate::Direction DefineDirection(Translate::Direction dir,LPCSTR strText);

	void UpdateTranslation();

	void InitControls();
	void InitDialog();
	void InitMessageLoop();

	// Maps
	BEGIN_UPDATE_UI_MAP(CTransliteratorDlg)
		UPDATE_ELEMENT(ID_EDIT_UNDO,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_EDIT_REDO,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_EDIT_CUT,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_EDIT_COPY,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_EDIT_PASTE,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_EDIT_CLEAR,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_EDIT_CLEAR_ALL,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_EDIT_SELECT_ALL,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_EDIT_IGNORE_INSERT,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_EDIT_IGNORE_REMOVE,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_VIEW_LANGUAGE_ENGLISH,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_VIEW_LANGUAGE_RUSSIAN,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_VIEW_LANGUAGE_TRANSLIT,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_VIEW_CONTROLS_WRAPTEXT,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_VIEW_CONTROLS_SCROLLTEXT,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_VIEW_CONTROLS_AUTOTRANSLITERATION,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_VIEW_CONTROLS_AUTOIGNORE,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_TOOLS_TRANSLATION,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_TOOLS_TRANSLATEFILES,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_TOOLS_OPTIONS,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_APP_ABOUT,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_SHOW,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_HIDE,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_PROFILE1,UPDUI_MENUPOPUP|UPDUI_TEXT)
		UPDATE_ELEMENT(ID_PROFILE2,UPDUI_MENUPOPUP|UPDUI_TEXT)
		UPDATE_ELEMENT(ID_PROFILE3,UPDUI_MENUPOPUP|UPDUI_TEXT)
		UPDATE_ELEMENT(ID_PROFILE4,UPDUI_MENUPOPUP|UPDUI_TEXT)
		UPDATE_ELEMENT(ID_PROFILE5,UPDUI_MENUPOPUP|UPDUI_TEXT)
		UPDATE_ELEMENT(ID_PROFILE6,UPDUI_MENUPOPUP|UPDUI_TEXT)
		UPDATE_ELEMENT(ID_PROFILE7,UPDUI_MENUPOPUP|UPDUI_TEXT)
		UPDATE_ELEMENT(ID_PROFILE8,UPDUI_MENUPOPUP|UPDUI_TEXT)
		UPDATE_ELEMENT(ID_PROFILE9,UPDUI_MENUPOPUP|UPDUI_TEXT)
	END_UPDATE_UI_MAP()

	BEGIN_DLGRESIZE_MAP(CTransliteratorDlg)
		BEGIN_DLGRESIZE_GROUP()
			DLGRESIZE_CONTROL(IDC_STATICSEPARATOR, DLSZ_SIZE_X)
			DLGRESIZE_CONTROL(IDC_STRNSTEXT, DLSZ_SIZE_X|DLSZ_SIZE_Y)
			DLGRESIZE_CONTROL(IDC_SRUSTEXT, DLSZ_SIZE_X|DLSZ_SIZE_Y)
		END_DLGRESIZE_GROUP()
	END_DLGRESIZE_MAP()
	
	BEGIN_MSG_MAP(CTranslieratortDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_SYSCOMMAND, OnSysCommand)
		MESSAGE_HANDLER(WM_HOTKEY, OnHotKey)
		MESSAGE_HANDLER(WM_QUERYENDSESSION, OnQueryEndSession)
		MESSAGE_HANDLER(WM_APPLY, OnApply)

		COMMAND_ID_HANDLER(ID_APP_EXIT, OnAppExit)
		COMMAND_RANGE_HANDLER(ID_EDIT_CLEAR,ID_EDIT_REDO,OnEditCommands)
		COMMAND_ID_HANDLER(ID_EDIT_IGNORE_INSERT, OnEditIgnore)
		COMMAND_ID_HANDLER(ID_EDIT_IGNORE_REMOVE, OnEditIgnore)
		COMMAND_ID_HANDLER(ID_EDIT_COPY_TRNSTORUS, OnEditCopy)
		COMMAND_ID_HANDLER(ID_EDIT_COPY_RUSTOTRNS, OnEditCopy)
		COMMAND_RANGE_HANDLER(ID_PROFILE1,ID_PROFILE9,OnProfile)
		COMMAND_ID_HANDLER(ID_VIEW_LANGUAGE_ENGLISH, OnViewLanguage)
		COMMAND_ID_HANDLER(ID_VIEW_LANGUAGE_RUSSIAN, OnViewLanguage)
		COMMAND_ID_HANDLER(ID_VIEW_LANGUAGE_TRANSLIT, OnViewLanguage)
		COMMAND_ID_HANDLER(ID_VIEW_CONTROLS_WRAPTEXT, OnViewControls)
		COMMAND_ID_HANDLER(ID_VIEW_CONTROLS_SCROLLTEXT, OnViewControls)
		COMMAND_ID_HANDLER(ID_VIEW_CONTROLS_AUTOTRANSLITERATION, OnViewControlsAutoTransliteration)
		COMMAND_ID_HANDLER(ID_VIEW_CONTROLS_AUTOIGNORE, OnViewControlsAutoIgnore)
		COMMAND_ID_HANDLER(ID_TOOLS_TRANSLATION, OnToolsTranslation)
		COMMAND_ID_HANDLER(ID_TOOLS_TRANSLATEFILES, OnToolsTranslateFiles)
		COMMAND_ID_HANDLER(ID_TOOLS_OPTIONS, OnToolsOptions)
		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)

		COMMAND_ID_HANDLER(ID_SHOW, OnShowHide)
		COMMAND_ID_HANDLER(ID_HIDE, OnShowHide)

		COMMAND_HANDLER(IDC_TRNS, EN_CHANGE, OnEnChangeTrnsRus)
		COMMAND_HANDLER(IDC_RUS, EN_CHANGE, OnEnChangeTrnsRus)
		NOTIFY_HANDLER(IDC_TRNS, EN_MSGFILTER, OnEnMsgFilterTrnsRus)
		NOTIFY_HANDLER(IDC_RUS, EN_MSGFILTER, OnEnMsgFilterTrnsRus)

		NOTIFY_HANDLER(ATL_IDW_STATUS_BAR, NM_RCLICK, OnClickStatusBar)
		NOTIFY_HANDLER(ATL_IDW_STATUS_BAR, NM_DBLCLK, OnClickStatusBar)

		CHAIN_MSG_MAP(NN::DialogStatusBarMenu<CTransliteratorDlg>)
		CHAIN_MSG_MAP(NN::TrayIcon<CTransliteratorDlg>)
		CHAIN_MSG_MAP(CDialogResize<CTransliteratorDlg>)
		CHAIN_MSG_MAP(CUpdateUI<CTransliteratorDlg>)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnHotKey(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnQueryEndSession(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnApply(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnAppExit(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnEditCommands(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnEditIgnore(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnEditCopy(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnProfile(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnViewLanguage(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnViewControls(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnViewControlsAutoTransliteration(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnViewControlsAutoIgnore(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnToolsTranslation(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnToolsTranslateFiles(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnToolsOptions(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnAppAbout(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnShowHide(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnEnChangeTrnsRus(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnEnMsgFilterTrnsRus(int code, NMHDR* pnmhdr, BOOL& bHandled);

	LRESULT OnClickStatusBar(int code, NMHDR* pnmhdr, BOOL& bHandled);
};

#endif // __TRANSLITERATORDLG_H__

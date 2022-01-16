#ifndef __TRANSLITDLG_H__
#define __TRANSLITDLG_H__

#include "TranslationDlg.h"

class CTranslitDlg : public CDialogImpl<CTranslitDlg>,
					public CDialogResize<CTranslitDlg>,
					public CUpdateUI<CTranslitDlg>,
					public CMessageFilter,
					public CIdleHandler,
					public TrayIcon<CTranslitDlg>,
					public DialogStatusBarMenu<CTranslitDlg>,
					public DialogIcon<CTranslitDlg>,
					public DialogLang<CTranslitDlg>
{
public:
	enum { IDD=IDR_TRANSLIT } ;

	enum hkID
	{
		hkIDTranslationEngtoRus = 1000,
		hkIDTranslationRustoEng,
		hkIDTranslationAuto,
		hkIDShowTranslit,
		hkIDHideTranslit
	};

	enum EngRus { Eng, Rus };
	CRichEditCtrl m_richeditEngRus[2];

	AutoValue<bool,false> m_bHelpDialog;
	AutoValue<HACCEL> m_hAccel;
	AutoValue<bool,false> m_bShown;
	AutoValue<bool,false> m_bTrayIcon;
	static RECT s_rectEngRus[2];
	CTranslationDlg m_dlgTranslation;
	POINT m_ptMinTrackSize;

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnIdle();

	void Translate(Translate::Direction dir);

	void SetOptions();
	void SaveRegistry();
	void LoadRegistry();

	BOOL Show();
	void CloseDialog();
	void UpdateTrayIcon();
	void SaveWindowPlacement();

	HWND GetActiveWindowChild();
	void HotKeyTranslation(Translate::Direction dir);
	void HotKeyShowTranslit(bool bShow);

	Translate::Direction DefineDirection(Translate::Direction dir,LPCSTR szText);
	Translate::Direction DefineDirection(Translate::Direction dir,LPCWSTR szText);

	void WrapText();

	void InitControls();
	void InitMessageLoop();
	void InitMinTrackSize();

	BEGIN_UPDATE_UI_MAP(CTranslitDlg)
		UPDATE_ELEMENT(ID_EDIT_ENG_UNDO,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_EDIT_ENG_REDO,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_EDIT_ENG_CUT,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_EDIT_ENG_COPY,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_EDIT_ENG_PASTE,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_EDIT_ENG_SELECTALL,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_EDIT_ENG_DELETE,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_EDIT_ENG_DELETEALL,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_EDIT_RUS_UNDO,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_EDIT_RUS_REDO,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_EDIT_RUS_CUT,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_EDIT_RUS_COPY,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_EDIT_RUS_PASTE,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_EDIT_RUS_SELECTALL,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_EDIT_RUS_DELETE,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_EDIT_RUS_DELETEALL,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_TOOLS_LANGUAGE_ENGLISH,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_TOOLS_LANGUAGE_RUSSIAN,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_TOOLS_TRANSLATION,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_SHOW,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_HIDE,UPDUI_MENUPOPUP)
	END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP(CTranslitDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_HOTKEY, OnHotKey)
		MESSAGE_HANDLER(WM_SYSCOMMAND, OnSysCommand)
		MESSAGE_HANDLER(WM_GETMINMAXINFO, OnGetMinMaxInfo)
		COMMAND_ID_HANDLER(ID_APP_EXIT, OnAppExit)
		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
		COMMAND_RANGE_HANDLER(ID_EDIT_ENG_UNDO,ID_EDIT_RUS_DELETEALL,OnEditEngRus)
		COMMAND_ID_HANDLER(ID_EDIT_NOTRANSLATE_SET,OnEditNoTranslate)
		COMMAND_ID_HANDLER(ID_EDIT_NOTRANSLATE_CLEAR,OnEditNoTranslate)
		COMMAND_ID_HANDLER(ID_TOOLS_LANGUAGE_ENGLISH, OnToolsLanguage)
		COMMAND_ID_HANDLER(ID_TOOLS_LANGUAGE_RUSSIAN, OnToolsLanguage)
		COMMAND_ID_HANDLER(ID_TOOLS_CHANGETRANSLATION, OnToolsOptions)
		COMMAND_ID_HANDLER(ID_TOOLS_TRANSLATION, OnToolsTranslation)
		COMMAND_ID_HANDLER(ID_TOOLS_OPTIONS, OnToolsOptions)
		COMMAND_ID_HANDLER(ID_TOOLS_TRANSLATEFILES,OnToolsTranslateFiles)
		COMMAND_ID_HANDLER(ID_SHOW, OnShowHide)
		COMMAND_ID_HANDLER(ID_HIDE, OnShowHide)
		COMMAND_HANDLER(IDC_ENG, EN_CHANGE, OnEnChangeEngRus)
		COMMAND_HANDLER(IDC_RUS, EN_CHANGE, OnEnChangeEngRus)
		NOTIFY_HANDLER(IDC_ENG, EN_MSGFILTER, OnEnMsgFilterEngRus)
		NOTIFY_HANDLER(IDC_RUS, EN_MSGFILTER, OnEnMsgFilterEngRus)
		CHAIN_MSG_MAP(DialogStatusBarMenu<CTranslitDlg>)
		CHAIN_MSG_MAP(TrayIcon<CTranslitDlg>)
		CHAIN_MSG_MAP(CUpdateUI<CTranslitDlg>)
		CHAIN_MSG_MAP(CDialogResize<CTranslitDlg>)
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

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnHotKey(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnAppExit(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnAppAbout(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnEnChangeEngRus(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnEditEngRus(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnEditNoTranslate(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnToolsLanguage(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnToolsTranslation(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnToolsTranslateFiles(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnToolsOptions(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnShowHide(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnEnMsgFilterEngRus(int code, NMHDR* pnmhdr, BOOL& bHandled);
};

#endif //!__TRANSLITDLG_H__
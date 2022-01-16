#ifndef __TRANSLITERATORDLG_H__
#define __TRANSLITERATORDLG_H__

#pragma once

#include "profiledetailsdlg.h"
#include "translatefilesdlg.h"
#include "aboutdlg.h"
#include "optionsdlg.h"
#include "msg.h"

class TransliteratorDlg : public ATL::CDialogImpl<TransliteratorDlg>,
					public WTL::CUpdateUI<TransliteratorDlg>,
					public WTL::CIdleHandler,
					public WTL::CDialogResize<TransliteratorDlg>,
					public NN::TrayIcon<TransliteratorDlg>,
					public NN::DialogStatusBarMenu<TransliteratorDlg>,
					public NN::DialogIcon<TransliteratorDlg>,
					public NN::DialogLang<TransliteratorDlg>,
					public NN::MessageFilterDlgAccel<TransliteratorDlg>
{
public:
	enum { IDD = IDR_TRANSLITERATOR } ;
	enum
	{
		size_delta_left = 5,
		size_delta_right = 5,
		size_delta_top = 15,
		size_delta_bottom = 5
	};
	enum { hkID = 1000 };

	// Text
	std::vector<wchar_t> m_aText[2];

	// Members
	NN::auto_value<HACCEL> m_hAccel;
	NN::auto_value<bool,false> m_bTrayIcon;
	NN::auto_value<bool,false> m_bShown;
	
	// Controls
	WTL::CMultiPaneStatusBarCtrl m_wndStatusBar;
	WTL::CRichEditCtrl m_areLang[2];
	//WTL::CRichEditCtrl m_areLang[2];

	// Dialogs
	ProfileDetailsDlg m_dlgProfileDetails;
	TranslateFilesDlg m_dlgTranslateFiles;
	AboutDlg m_dlgAbout;
	OptionsDlg m_dlgOptions;

	// Virtual Functions
	virtual BOOL OnIdle();
	
	// Override
	void DlgResize_UpdateLayout(int cxWidth, int cyHeight);
	int LoadStringForMenuItem(UINT uID, LPTSTR szBuff, int cchBuff);
	
	// Create and Destroy
	bool Show();
	void Close();

	// Options
	void SetOptions();
	void SetOptionsFont();

	// Placement
	void SaveWindowPlacement();
	// ShowHide
	void ShowHide(bool bShow);
	
	// Translate
	void Translate(Translate::Direction dir);
	// TranslateWindow
	void TranslateWindow(Translate::Direction dir);
	static void TranslateWindow_Edit(HWND hWndTranslation,Translate::Direction dir);
	static void TranslateWindow_IE(HWND hWndTranslation,Translate::Direction dir);
	static void TranslateWindow_Window(HWND hWndTranslation,Translate::Direction dir);

	static Translate::Direction DefineDirection(Translate::Direction dir, const LangChar* strText);
	static Translate::Direction DefineDirection(Translate::Direction dir, const LangCharA* strText);
	
	// Update
	// Layout
	void UpdateLayout();
	// StatusBar
	void UpdateStatusBar();
	// Caption
	void UpdateCaption();
	// Translation
	void UpdateTranslation();
	// Tray Icon
	void UpdateTrayIcon();
	// TaskBar
	void UpdateTaskBar();
	// Placement
	void UpdatePlacement();
	// Lang
	void UpdateLang();

	// Language
	void DialogLang_LanguageChanged();
	
	// Init
	void InitControls();
	void InitDialog();
	void InitStatusBar();

	// Maps
	BEGIN_UPDATE_UI_MAP(TransliteratorDlg)
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
		UPDATE_ELEMENT(ID_EDIT_COPY_LANGTOPTOLANGBOTTOM,UPDUI_MENUPOPUP|UPDUI_TEXT)
		UPDATE_ELEMENT(ID_EDIT_COPY_LANGBOTTOMTOLANGTOP,UPDUI_MENUPOPUP|UPDUI_TEXT)
		UPDATE_ELEMENT(ID_TOOLS_PROFILEDETAILS,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_TOOLS_TRANSLATEFILES,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_TOOLS_OPTIONS,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_TOOLS_ACTION_TRANSLITERATION,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_TOOLS_ACTION_IGNORE,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_TOOLS_ACTION_IGNORETEXT,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_TOOLS_ACTION_COPYIGNORE,UPDUI_MENUPOPUP)
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
		UPDATE_ELEMENT(ID_PROFILE10,UPDUI_MENUPOPUP|UPDUI_TEXT)
	END_UPDATE_UI_MAP()

	BEGIN_DLGRESIZE_MAP(TransliteratorDlg)
		BEGIN_DLGRESIZE_GROUP()
			DLGRESIZE_CONTROL(IDC_STATICSEPARATOR, DLSZ_SIZE_X)
			DLGRESIZE_CONTROL(IDC_GRPLANGTOP, DLSZ_SIZE_X|DLSZ_SIZE_Y)
			DLGRESIZE_CONTROL(IDC_GRPLANGBOTTOM, DLSZ_SIZE_X|DLSZ_SIZE_Y)
		END_DLGRESIZE_GROUP()
	END_DLGRESIZE_MAP()
	
	BEGIN_MSG_MAP(TransliteratortDlg)
		NN_MSGFILTER_MESSAGE_ADD()
		NN_MSGFILTER_IDLE_ADD()
		NN_MSGFILTER_MESSAGE_REMOVE()
		NN_MSGFILTER_IDLE_REMOVE()
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_SYSCOMMAND, OnSysCommand)
		MESSAGE_HANDLER(WM_HOTKEY, OnHotKey)
		MESSAGE_HANDLER(WM_QUERYENDSESSION, OnQueryEndSession)
		MESSAGE_HANDLER(UWM_APPLY, OnApply)

		COMMAND_ID_HANDLER(ID_APP_EXIT, OnAppExit)
		COMMAND_RANGE_HANDLER(ID_EDIT_CLEAR,ID_EDIT_REDO,OnEditCommands)
		COMMAND_ID_HANDLER(ID_EDIT_IGNORE_INSERT, OnEditIgnore)
		COMMAND_ID_HANDLER(ID_EDIT_IGNORE_REMOVE, OnEditIgnore)
		COMMAND_ID_HANDLER(ID_EDIT_COPY_LANGTOPTOLANGBOTTOM, OnEditCopy)
		COMMAND_ID_HANDLER(ID_EDIT_COPY_LANGBOTTOMTOLANGTOP, OnEditCopy)
		COMMAND_RANGE_HANDLER(ID_PROFILE1,ID_PROFILE10,OnProfile)
		NN_TOOLWINDOW(ID_TOOLS_PROFILEDETAILS, m_dlgProfileDetails)
		NN_TOOLWINDOW(ID_TOOLS_TRANSLATEFILES, m_dlgTranslateFiles)
		NN_TOOLWINDOW(ID_TOOLS_OPTIONS, m_dlgOptions)
		NN_TOOLWINDOW(ID_APP_ABOUT, m_dlgAbout)
		COMMAND_ID_HANDLER(ID_TOOLS_ACTION_TRANSLITERATION, OnToolsAction)
		COMMAND_ID_HANDLER(ID_TOOLS_ACTION_IGNORE, OnToolsAction)
		COMMAND_ID_HANDLER(ID_TOOLS_ACTION_IGNORETEXT, OnToolsAction)
		COMMAND_ID_HANDLER(ID_TOOLS_ACTION_COPYIGNORE, OnToolsAction)

		COMMAND_ID_HANDLER(ID_SHOW, OnShowHide)
		COMMAND_ID_HANDLER(ID_HIDE, OnShowHide)

		COMMAND_HANDLER(IDC_RELANGTOP, EN_CHANGE, OnEnChangeLang)
		COMMAND_HANDLER(IDC_RELANGBOTTOM, EN_CHANGE, OnEnChangeLang)
		
		NOTIFY_HANDLER(IDC_RELANGTOP, EN_MSGFILTER, OnEnMsgFilterLang)
		NOTIFY_HANDLER(IDC_RELANGBOTTOM, EN_MSGFILTER, OnEnMsgFilterLang)

		NOTIFY_HANDLER(ATL_IDW_STATUS_BAR, NM_RCLICK, OnClickStatusBar)
		NOTIFY_HANDLER(ATL_IDW_STATUS_BAR, NM_DBLCLK, OnClickStatusBar)
		
		CHAIN_MSG_MAP(NN::DialogStatusBarMenu<TransliteratorDlg>)
		CHAIN_MSG_MAP(NN::TrayIcon<TransliteratorDlg>)
		CHAIN_MSG_MAP(WTL::CDialogResize<TransliteratorDlg>)
		CHAIN_MSG_MAP(WTL::CUpdateUI<TransliteratorDlg>)
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
	LRESULT OnToolsAction(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnShowHide(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnEnChangeLang(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnEnMsgFilterLang(int code, NMHDR* pnmhdr, BOOL& bHandled);

	LRESULT OnClickStatusBar(int code, NMHDR* pnmhdr, BOOL& bHandled);
};

#endif // __TRANSLITERATORDLG_H__

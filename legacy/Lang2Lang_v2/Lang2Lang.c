// Warnings
#pragma warning(disable:4201) // nameless struct/union
#pragma warning(disable:4065) // default without no case
// Warnings
#define WINVER 0x400
#define _WIN32_IE 0x400
#define STRICT
#define _RICHEDIT_VER 0x200
#include <windows.h>
#if WINVER<0x500
#include <winable.h> // GetGUIThreadInfo
#endif // WINVER<0x500
#include <commctrl.h>
#include <richedit.h>
#include "resource.h"
#include "Lang2Lang.h"

// Dialog functions
LRESULT CALLBACK Lang2LangDlg(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK HelpDlg(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK AboutDlg(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK GeneralPageDlg(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK KeysPageDlg(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

void Translate(Lang2Lang *pLang2Lang,LPCTSTR szFrom,LPTSTR szTo);
void UpdateHelp(HWND hWndEdit,Lang2Lang *pLang2Lang,LPTSTR szHelp,unsigned nChar);
void MakeHelp(Lang2Lang *pLang2Lang,LPTSTR szHelp,unsigned nChar);
BOOL LoadOptions(HKEY hKey,Lang2LangOptions *pLang2LangOptions);
BOOL SaveOptions(HKEY hKey,Lang2LangOptions *pLang2LangOptions);
int DisplayOptions(HWND hWnd);
void CheckLang(HWND hWnd);
BOOL ShowLang2LangIcon(HWND hWnd);
BOOL HideLang2LangIcon(HWND hWnd);
void LoadWindowPos(HWND hWnd,WindowPos *pWindowPos);
void SaveWindowPos(HWND hWnd,WindowPos *pWindowPos);
void Lang2LangToTray(HWND hWnd);

// Initial Options
Lang2LangOptions Options=
{
	translationHotKey,
	{
		'L',
		MOD_ALT|MOD_CONTROL
	},
	minimizeToTray,
	closeExit,
	TRUE,
	{
		FALSE,
		FALSE,
		{
			0,
			0,
			0,
			0
		}
	},
	{
		// Eng2Rus
		{
			_T("Eng2Rus"),
			{
				{_T("à"),{_T("a")}},
				{_T("À"),{_T("A")}},
				{_T("á"),{_T("b")}},
				{_T("Á"),{_T("B")}},
				{_T("â"),{_T("v")}},
				{_T("Â"),{_T("V")}},
				{_T("ã"),{_T("g")}},
				{_T("Ã"),{_T("G")}},
				{_T("ä"),{_T("d")}},
				{_T("Ä"),{_T("D")}},
				{_T("å"),{_T("e")}},
				{_T("Å"),{_T("E")}},
				{_T("¸"),{_T("e'")}},
				{_T("¨"),{_T("E'")}},
				{_T("æ"),{_T("j")}},
				{_T("Æ"),{_T("J")}},
				{_T("ç"),{_T("z")}},
				{_T("Ç"),{_T("Z")}},
				{_T("è"),{_T("i")}},
				{_T("È"),{_T("I")}},
				{_T("é"),{_T("y")}},
				{_T("É"),{_T("Y")}},
				{_T("ê"),{_T("k")}},
				{_T("Ê"),{_T("K")}},
				{_T("ë"),{_T("l")}},
				{_T("Ë"),{_T("L")}},
				{_T("ì"),{_T("m")}},
				{_T("Ì"),{_T("M")}},
				{_T("í"),{_T("n")}},
				{_T("Í"),{_T("N")}},
				{_T("î"),{_T("o")}},
				{_T("Î"),{_T("O")}},
				{_T("ï"),{_T("p")}},
				{_T("Ï"),{_T("P")}},
				{_T("ð"),{_T("r")}},
				{_T("Ð"),{_T("R")}},
				{_T("ñ"),{_T("s")}},
				{_T("Ñ"),{_T("S")}},
				{_T("ò"),{_T("t")}},
				{_T("Ò"),{_T("T")}},
				{_T("ó"),{_T("u")}},
				{_T("Ó"),{_T("U")}},
				{_T("ô"),{_T("f")}},
				{_T("Ô"),{_T("F")}},
				{_T("õ"),{_T("x"),_T("h")}},
				{_T("Õ"),{_T("X"),_T("H")}},
				{_T("ö"),{_T("c")}},
				{_T("Ö"),{_T("C")}},
				{_T("÷"),{_T("ch")}},
				{_T("×"),{_T("ch")}},
				{_T("ø"),{_T("w"),_T("sh"),_T("sH")}},
				{_T("Ø"),{_T("W"),_T("SH"),_T("Sh")}},
				{_T("ù"),{_T("w'"),_T("sch"),_T("sCH"),_T("sCh"),_T("scH")}},
				{_T("Ù"),{_T("W'"),_T("SCH"),_T("Sch"),_T("SCh"),_T("ScH")}},
				{_T("ú"),{_T("`")}},
				{_T("Ú"),{_T("``")}},
				{_T("û"),{_T("y'")}},
				{_T("Û"),{_T("Y'")}},
				{_T("ü"),{_T("'")}},
				{_T("Ü"),{_T("''")}},
				{_T("ý"),{_T("e`")}},
				{_T("Ý"),{_T("E`")}},
				{_T("þ"),{_T("iu"),_T("iU"),_T("yu"),_T("yU")}},
				{_T("Þ"),{_T("IU"),_T("IU"),_T("YU"),_T("Yu")}},
				{_T("ÿ"),{_T("ia"),_T("iA"),_T("ya"),_T("yA")}},
				{_T("ß"),{_T("IA"),_T("Ia"),_T("YA"),_T("Ya")}}
			}
		},
		// Rus2Eng
		{
			_T("Rus2Eng"),
			{
				{_T("a"),{_T("à")}},
				{_T("A"),{_T("À")}},
				{_T("b"),{_T("á")}},
				{_T("B"),{_T("Á")}},
				{_T("c"),{_T("ö")}},
				{_T("C"),{_T("Ö")}},
				{_T("d"),{_T("ä")}},
				{_T("D"),{_T("Ä")}},
				{_T("e"),{_T("å")}},
				{_T("E"),{_T("Å")}},
				{_T("f"),{_T("ô")}},
				{_T("F"),{_T("Ô")}},
				{_T("g"),{_T("ã")}},
				{_T("G"),{_T("Ã")}},
				{_T("h"),{_T("õ")}},
				{_T("H"),{_T("Õ")}},
				{_T("i"),{_T("è")}},
				{_T("I"),{_T("È")}},
				{_T("j"),{_T("æ")}},
				{_T("J"),{_T("Æ")}},
				{_T("k"),{_T("ê")}},
				{_T("K"),{_T("Ê")}},
				{_T("l"),{_T("ë")}},
				{_T("L"),{_T("Ë")}},
				{_T("m"),{_T("ì")}},
				{_T("M"),{_T("Ì")}},
				{_T("n"),{_T("í")}},
				{_T("N"),{_T("Í")}},
				{_T("o"),{_T("î")}},
				{_T("O"),{_T("Î")}},
				{_T("p"),{_T("ï")}},
				{_T("P"),{_T("Ï")}},
				{_T("r"),{_T("ð")}},
				{_T("R"),{_T("Ð")}},
				{_T("s"),{_T("ñ")}},
				{_T("S"),{_T("Ñ")}},
				{_T("t"),{_T("ò")}},
				{_T("T"),{_T("Ò")}},
				{_T("u"),{_T("ó")}},
				{_T("U"),{_T("Ó")}},
				{_T("v"),{_T("â")}},
				{_T("V"),{_T("Â")}},
				{_T("w"),{_T("ø")}},
				{_T("W"),{_T("Ø")}},
				{_T("x"),{_T("õ")}},
				{_T("X"),{_T("Õ")}},
				{_T("y"),{_T("é")}},
				{_T("Y"),{_T("É")}},
				{_T("z"),{_T("ç")}},
				{_T("Z"),{_T("Ç")}},
			}
		},
		{0}
	}
};

#define ENG2RUS 0
#define RUS2ENG 1
#define DEF_LANG2LANG ENG2RUS
Lang2Lang *pLang2Lang = Options.aLang2Lang+DEF_LANG2LANG;

#define MAX_CHAR 65530
#define ENG 1
#define RUS 2

#define DEFFROM ENG
#define DEFTO RUS

#define MENU_EDITFROM 1
#define MENU_EDITTO 2

TCHAR szEditFrom[MAX_CHAR];
TCHAR szEditTo[MAX_CHAR];
int LangFrom = DEFFROM;
int LangTo = DEFTO;
HWND hDlgHelp = NULL;
BOOL bHelp = FALSE;

TCHAR szHelp[MAX_CHAR];

HINSTANCE g_hInstance;
HKEY g_hKey;
HICON g_hIcon;

// Main
void main()
{
	HMODULE hRichEdit;
	// Registry
	if(RegCreateKey(HKEY_CURRENT_USER,_T("Software\\NN\\Lang2Lang"),&g_hKey))
	{
		ShowErrorHT(IDE_REGKEY);
		ExitProcess(0);
		return;
	}
	RegSetValueEx(g_hKey,_T("Version"),0,REG_SZ,(CONST BYTE*)_T("2.0.0.0"),10*sizeof(TCHAR));
	//hInstance
	g_hInstance=GetModuleHandle(NULL);
	// LoadLibrary
	hRichEdit=LoadLibrary("riched20.dll");
	if(!hRichEdit)
	{
		ShowErrorHT(IDE_RICHED20);
		hRichEdit=LoadLibrary("riched32.dll");
		if(!hRichEdit)
		{
			ShowErrorHT(IDE_RICHED32);
			ExitProcess(0);
			return;
		}
	}
	// Init
	szEditFrom[0]=0;
	szEditTo[0]=0;
	g_hIcon=LoadIcon(g_hInstance,MAKEINTRESOURCE(IDR_LANG2LANG));
	// call dialog
	DialogBox(g_hInstance,MAKEINTRESOURCE(IDR_LANG2LANG),NULL,(DLGPROC)Lang2LangDlg);
	// FreeLibrary
	FreeLibrary(hRichEdit);
	// Registry
	RegCloseKey(g_hKey);
	//return
	ExitProcess(0);
}

// Dialog functions
LRESULT CALLBACK Lang2LangDlg(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// Avoid warning
	lParam;
	switch(uMsg)
	{
		case WM_INITDIALOG:
			{
				TCHAR szAbout[MAX_PATH];
				HMENU hSystemMenu;
				hSystemMenu=GetSystemMenu(hDlg,0);
				AppendMenu(hSystemMenu,MF_SEPARATOR,0,0);
				LoadString(g_hInstance,IDS_ABOUT,szAbout,MAX_PATH);
				AppendMenu(hSystemMenu,MF_STRING,IDM_ABOUT,szAbout);
				CheckLang(hDlg);
				SendDlgItemMessage(hDlg,IDC_EDITFROM,EM_SETEVENTMASK,0,
					ENM_CHANGE|ENM_KEYEVENTS|ENM_MOUSEEVENTS);
				SendDlgItemMessage(hDlg,IDC_EDITTO,EM_SETEVENTMASK,0,
					ENM_CHANGE|ENM_KEYEVENTS|ENM_MOUSEEVENTS);
				SendDlgItemMessage(hDlg,IDC_EDITFROM,EM_SETLIMITTEXT,MAX_CHAR,0);
				SendDlgItemMessage(hDlg,IDC_EDITTO,EM_SETLIMITTEXT,MAX_CHAR,0);
				LoadOptions(g_hKey,&Options);
				hDlgHelp = CreateDialog(g_hInstance,MAKEINTRESOURCE(IDD_HELP),hDlg,(DLGPROC)HelpDlg);
				RegisterHotKey(hDlg,HOTKEY_ID,Options.translationhotkey.fsModifiers,Options.translationhotkey.vk);
				SendMessage(hDlg,WM_SETICON,TRUE,(LPARAM)g_hIcon);
				SendMessage(hDlg,WM_SETICON,FALSE,(LPARAM)g_hIcon);
				if(Options.bShowTrayIcon)
					ShowLang2LangIcon(hDlg);
				LoadWindowPos(hDlg,&Options.windowpos);
			}
			break;
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case IDC_EDITFROM:
					switch(HIWORD(wParam))
					{
						case EN_CHANGE:
                            GetDlgItemText(hDlg,IDC_EDITFROM,szEditFrom,MAX_CHAR);
							Translate(pLang2Lang,szEditFrom,szEditTo);
							SetDlgItemText(hDlg,IDC_EDITTO,szEditTo);
							break;
					}
					break;
				case IDM_HELP:
				case IDC_HELPW:
				case IDM_OPTIONS:
					{
						BOOL bOptions=LOWORD(wParam)==IDM_OPTIONS;
						HMENU hMenu,hSubMenu;
						if(bOptions&&bHelp||
							!bOptions)
						{
							bHelp=!bHelp;
							CheckDlgButton(hDlg,IDC_HELPW,bHelp);
							ShowWindow(hDlgHelp,bHelp?SW_SHOW:SW_HIDE);
							hMenu=GetMenu(hDlg);
							hSubMenu=GetSubMenu(hMenu,3);
							CheckMenuItem(hSubMenu,IDM_HELP,MF_BYCOMMAND|(bHelp?MF_CHECKED:MF_UNCHECKED));
						}
						if(bOptions)
							if(DisplayOptions(hDlg)==IDOK)
							{
								UnregisterHotKey(hDlg,HOTKEY_ID);
								RegisterHotKey(hDlg,HOTKEY_ID,Options.translationhotkey.fsModifiers,Options.translationhotkey.vk);
								if(!Options.bShowTrayIcon)
									HideLang2LangIcon(hDlg);
								else
									ShowLang2LangIcon(hDlg);
							}
					}
					break;
				case IDM_ABOUT:
					DialogBox(g_hInstance,MAKEINTRESOURCE(IDD_ABOUT),hDlg,(DLGPROC)AboutDlg);
					break;
				case IDM_EXIT:
					PostMessage(hDlg,WM_CLOSE,0,0);
					break;
				case IDC_ENGFROM:
				case IDC_RUSFROM:
				case IDC_ENGTO:
				case IDC_RUSTO:
					switch(LOWORD(wParam))
					{
						case IDC_ENGFROM:
							LangFrom=ENG;
							break;
						case IDC_RUSFROM:
							LangFrom=RUS;
							break;
						case IDC_ENGTO:
							LangTo=ENG;
							break;
						case IDC_RUSTO:
							LangTo=RUS;
							break;
					}
					CheckLang(hDlg);
					Translate(pLang2Lang,szEditFrom,szEditTo);
					SetDlgItemText(hDlg,IDC_EDITTO,szEditTo);
					break;
				case IDM_UNDOFROM:
					SendDlgItemMessage(hDlg,IDC_EDITFROM,WM_UNDO,0,0);
					break;
				case IDM_REDOFROM:
					SendDlgItemMessage(hDlg,IDC_EDITFROM,EM_REDO,0,0);
					break;
				case IDM_CUTFROM:
					SendDlgItemMessage(hDlg,IDC_EDITFROM,WM_CUT,0,0);
					break;
				case IDM_COPYFROM:
					SendDlgItemMessage(hDlg,IDC_EDITFROM,WM_COPY,0,0);
					break;
				case IDM_PASTEFROM:
					SendDlgItemMessage(hDlg,IDC_EDITFROM,WM_PASTE,0,0);
					break;
				case IDM_SELECTALLFROM:
					SendDlgItemMessage(hDlg,IDC_EDITFROM,EM_SETSEL,0,(LPARAM)-1);
					break;
				case IDM_UNDOTO:
					SendDlgItemMessage(hDlg,IDC_EDITTO,WM_UNDO,0,0);
					break;
				case IDM_REDOTO:
					SendDlgItemMessage(hDlg,IDC_EDITTO,EM_REDO,0,0);
					break;
				case IDM_CUTTO:
					SendDlgItemMessage(hDlg,IDC_EDITTO,WM_CUT,0,0);
					break;
				case IDM_COPYTO:
					SendDlgItemMessage(hDlg,IDC_EDITTO,WM_COPY,0,0);
					break;
				case IDM_PASTETO:
					SendDlgItemMessage(hDlg,IDC_EDITTO,WM_PASTE,0,0);
					break;
				case IDM_SELECTALLTO:
					SendDlgItemMessage(hDlg,IDC_EDITTO,EM_SETSEL,0,(LPARAM)-1);
					break;
				case IDOK:
				case IDCANCEL:
					break;
				case IDM_SHOW:
					ShowWindow(hDlg,SW_SHOW);
					if(!Options.bShowTrayIcon)
						HideLang2LangIcon(hDlg);
					break;
				case IDM_HIDE:
					ShowWindow(hDlg,SW_HIDE);
					if(!Options.bShowTrayIcon)
						ShowLang2LangIcon(hDlg);
					break;
			}
			break;
		case WM_NOTIFY:
			if(((NMHDR *)lParam)->code==EN_MSGFILTER)
				if(LOWORD(wParam)==IDC_EDITFROM||LOWORD(wParam)==IDC_EDITTO)
				{
					MSGFILTER *pMsgFilter=(MSGFILTER *)lParam;
					if(pMsgFilter->msg==WM_RBUTTONDOWN)
					{
						HMENU hMenu,hSubMenu;
						POINT pt;
						GetCursorPos(&pt);
						hMenu=GetMenu(hDlg);
						hSubMenu=GetSubMenu(hMenu,LOWORD(wParam)==IDC_EDITFROM?MENU_EDITFROM:MENU_EDITTO);
						TrackPopupMenu(hSubMenu,TPM_LEFTALIGN|TPM_LEFTBUTTON|
							TPM_RIGHTBUTTON,pt.x,pt.y,0,hDlg,NULL);
					}
				}
			break;
		case WM_SYSCOMMAND:
			switch(LOWORD(wParam))
			{
				case IDM_ABOUT:
					DialogBox(g_hInstance,MAKEINTRESOURCE(IDD_ABOUT),hDlg,(DLGPROC)AboutDlg);
					break;
				case SC_CLOSE:
					if(Options.close==closeToTray)
					{
						Lang2LangToTray(hDlg);
						return TRUE;}
					break;
				case SC_MINIMIZE:
					if(Options.minimize==minimizeToTray)
					{
						Lang2LangToTray(hDlg);
						return TRUE;
					}
					break;
			}
			break;
		case WM_HOTKEY:
			{
				TCHAR szFrom[MAX_CHAR];
				TCHAR szTo[MAX_CHAR];
				TCHAR szClass[50];
				HWND hWndTranslate = GetForegroundWindow();
				DWORD dwThreadID = GetWindowThreadProcessId(hWndTranslate, NULL);
				GUITHREADINFO gui_thread_info;
				ZeroMem(&gui_thread_info, sizeof(GUITHREADINFO));
				gui_thread_info.cbSize = sizeof(GUITHREADINFO);
				GetGUIThreadInfo(dwThreadID, &gui_thread_info);
				hWndTranslate=gui_thread_info.hwndFocus;
				GetClassName(hWndTranslate,szClass,50-1);
#ifndef UNICODE
				if(!lstrcmpi(szClass,_T("EditW"))||
					!lstrcmpi(szClass,_T("RichEditW"))||
					!lstrcmpi(szClass,_T("RichEdit20W"))||
					!lstrcmpi(szClass,_T("RichEdit30W")))
				{
					WCHAR wszFrom[MAX_CHAR/2];
					WCHAR wszTo[MAX_CHAR/2];
					SendMessageW(hWndTranslate, WM_GETTEXT, (WPARAM)(MAX_CHAR/2-1),(LPARAM)wszFrom);
					WideCharToMultiByte(CP_ACP,0,wszFrom,-1,szFrom,sizeof(szFrom)/sizeof(TCHAR)-1,NULL,NULL);
					Translate(pLang2Lang,szFrom,szTo);
					MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,szTo,-1,wszTo,sizeof(wszTo)/sizeof(WCHAR)-1);
					SendMessageW(hWndTranslate, WM_SETTEXT, 0,(LPARAM)(LPCTSTR)wszTo);
				}
				else
				{
#endif // !UNICODE
					SendMessage(hWndTranslate, WM_GETTEXT, (WPARAM)(MAX_CHAR-1),(LPARAM)szFrom);
					Translate(pLang2Lang,szFrom,szTo);
					SendMessage(hWndTranslate, WM_SETTEXT, 0,(LPARAM)(LPCTSTR)szTo);
#ifndef UNICODE
				}
#endif // !UNICODE
			}
			break;
		case TRAYICON_MSG:
			switch (lParam)
			{
				case WM_LBUTTONDBLCLK:
					if(IsWindowVisible(hDlg))
						PostMessage(hDlg,WM_COMMAND,MAKEWPARAM(IDM_HIDE,BN_CLICKED),0);
					else
						PostMessage(hDlg,WM_COMMAND,MAKEWPARAM(IDM_SHOW,BN_CLICKED),0);
					break;
				case WM_RBUTTONDOWN:
					{
						HMENU hMenu,hSubMenu;
						POINT pt;
						hMenu=LoadMenu(g_hInstance,MAKEINTRESOURCE(IDR_POPUP));
						hSubMenu=GetSubMenu(hMenu,0);
						GetCursorPos(&pt);
						TrackPopupMenu(hSubMenu,TPM_RIGHTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON,pt.x,pt.y,0,hDlg,NULL);
						SetForegroundWindow(hDlg);
						DestroyMenu(hMenu);
					}
					break;
			}
			break;
		case WM_CLOSE:
			EndDialog(hDlg,0);
			break;
		case WM_DESTROY:
			SaveWindowPos(hDlg,&Options.windowpos);
			SaveOptions(g_hKey,&Options);
			UnregisterHotKey(hDlg,HOTKEY_ID);
			HideLang2LangIcon(hDlg);
			DestroyWindow(hDlgHelp);
			break;
	}
	return FALSE;
}

LRESULT CALLBACK HelpDlg(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	wParam;
	switch(uMsg)
	{
		case WM_INITDIALOG:
			//SetDlgItemText(hDlg,IDC_HELPC,szHelp);
			UpdateHelp(GetDlgItem(hDlg,IDC_HELPC),Options.aLang2Lang,szHelp,MAX_CHAR);
			SetFocus(GetDlgItem(hDlg,IDC_HELPC));
			break;
		case WM_SIZE:
			MoveWindow(GetDlgItem(hDlg,IDC_HELPC),0,0,LOWORD(lParam),HIWORD(lParam),TRUE);
			break;
		case WM_NOTIFY:
			if(((NMHDR *)lParam)->code==EN_MSGFILTER)
				if(LOWORD(wParam)==IDC_HELPC)
				{
					MSGFILTER *pMsgFilter=(MSGFILTER *)lParam;
					if(pMsgFilter->msg==WM_KEYDOWN)
						if(pMsgFilter->wParam==VK_ESCAPE)
							SendMessage(GetParent(hDlg),WM_COMMAND,HIWORD(BN_CLICKED)|LOWORD(IDC_HELPW),0);
				}
			break;
		case WM_CLOSE:
			SendMessage(GetParent(hDlg),WM_COMMAND,HIWORD(BN_CLICKED)|LOWORD(IDC_HELPW),0);
			break;
	}
	return FALSE;
}

LRESULT CALLBACK AboutDlg(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	lParam;
	switch(uMsg)
	{
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case IDC_EMAIL:
					ShellExecute(hDlg,"open","mailto:NN<nn-mail@yandex.ru>",NULL,NULL,SW_SHOW);
					break;
				case IDC_SITE:
					ShellExecute(hDlg,"open","http://nnsite.narod.ru",NULL,NULL,SW_SHOW);
					break;
				case IDOK:
					EndDialog(hDlg,0);
					break;
			}
			break;
		case WM_CLOSE:
			EndDialog(hDlg,0);
			break;
	}
	return FALSE;
}

LRESULT CALLBACK GeneralPageDlg(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	lParam;
	switch(uMsg)
	{
		case WM_INITDIALOG:
			{
				WORD fsModifiers=Options.translationhotkey.fsModifiers;
				Wnd2HotKey(&fsModifiers);
				SendDlgItemMessage(hDlg,IDC_HOTKEYTRANSLATE,HKM_SETHOTKEY,MAKEWORD(Options.translationhotkey.vk,fsModifiers),0);
				CheckRadioButton(hDlg,IDC_TRANSLATIONNO,IDC_TRANSLATIONHOTKEY,IDC_TRANSLATIONNO+Options.translation);
				//
				EnableWindow(GetDlgItem(hDlg,IDC_HOTKEYTRANSLATE),Options.translation==translationHotKey);
				//
				CheckRadioButton(hDlg,IDC_MINIMIZEMINIMIZE,IDC_MINIMIZETOTRAY,IDC_MINIMIZEMINIMIZE+Options.minimize);
				CheckRadioButton(hDlg,IDC_CLOSEEXIT,IDC_CLOSETOTRAY,IDC_CLOSEEXIT+Options.close);
				CheckDlgButton(hDlg,IDC_SHOWTRAYICON,Options.bShowTrayIcon);				
			}
			break;
		case WM_COMMAND:
			{
				UINT uID=LOWORD(wParam);
				switch(uID)
				{
					case IDC_TRANSLATIONNO:
					case IDC_TRANSLATIONHOTKEY:
						CheckRadioButton(hDlg,IDC_TRANSLATIONNO,IDC_TRANSLATIONHOTKEY,uID);
						EnableWindow(GetDlgItem(hDlg,IDC_HOTKEYTRANSLATE),uID==IDC_TRANSLATIONHOTKEY);
						break;
					case IDC_MINIMIZEMINIMIZE:
					case IDC_MINIMIZETOTRAY:
						CheckRadioButton(hDlg,IDC_MINIMIZEMINIMIZE,IDC_MINIMIZETOTRAY,uID);
						break;
					case IDC_CLOSEEXIT:
					case IDC_CLOSETOTRAY:
						CheckRadioButton(hDlg,IDC_CLOSEEXIT,IDC_CLOSETOTRAY,uID);
						break;
				}
			}
			break;
		case WM_NOTIFY:
			switch(((NMHDR *)lParam)->code)
			{
				case PSN_APPLY:
					{
						WORD wHotKey;
						if(IsDlgButtonChecked(hDlg,IDC_TRANSLATIONNO))
							Options.translation=translationNo;
						else
						if(IsDlgButtonChecked(hDlg,IDC_TRANSLATIONHOTKEY))
							Options.translation=translationHotKey;
						else
							Options.translation=translationTyping;
						if(IsDlgButtonChecked(hDlg,IDC_MINIMIZEMINIMIZE))
							Options.minimize=minimizeMinimize;
						else
							Options.minimize=minimizeToTray;
						if(IsDlgButtonChecked(hDlg,IDC_CLOSEEXIT))
							Options.close=closeExit;
						else
							Options.close=closeToTray;
						wHotKey=(WORD)SendDlgItemMessage(hDlg,IDC_HOTKEYTRANSLATE,HKM_GETHOTKEY,0,0);
						Options.translationhotkey.vk=LOBYTE(wHotKey);
						Options.translationhotkey.fsModifiers=HIBYTE(wHotKey);
						HotKey2Wnd(&Options.translationhotkey.fsModifiers);
						Options.bShowTrayIcon=IsDlgButtonChecked(hDlg,IDC_SHOWTRAYICON);
					}
					break;
			}
			break;
	}
	return FALSE;
}

LRESULT CALLBACK KeysPageDlg(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static Lang2Lang *pLang2Lang=NULL;
	static Lang2LangOptions KeysOptions;
	lParam;
	switch(uMsg)	
	{
		case WM_INITDIALOG:
		{
			unsigned uID;
			RECT rect;
			HWND hWndLang2Lang=GetDlgItem(hDlg,IDC_LANG2LANG);
			HWND hWndTo=GetDlgItem(hDlg,IDC_TO);
			for(uID=IDC_FROM1;uID<=IDC_FROM5;uID++)
				SendDlgItemMessage(hDlg,uID,EM_SETLIMITTEXT,LANG2LANGFROM_FROM-1,0);
			KeysOptions=Options;
			pLang2Lang=KeysOptions.aLang2Lang;
			while(*pLang2Lang->szName)
			{
				SendMessage(hWndLang2Lang,CB_ADDSTRING,0,(WPARAM)pLang2Lang->szName);
				pLang2Lang++;
			}
			pLang2Lang=NULL;
			GetWindowRect(hWndLang2Lang,&rect);
			ScreenToClient(hDlg,(LPPOINT)&rect);
			ScreenToClient(hDlg,(LPPOINT)&rect+1);
			rect.bottom+=150;
			MoveWindow(hWndLang2Lang,rect.left,rect.top,rect.right-rect.left,rect.bottom-rect.top,TRUE);
			GetWindowRect(hWndTo,&rect);
			ScreenToClient(hDlg,(LPPOINT)&rect);
			ScreenToClient(hDlg,(LPPOINT)&rect+1);
			rect.bottom+=60;
			MoveWindow(hWndTo,rect.left,rect.top,rect.right-rect.left,rect.bottom-rect.top,TRUE);
		}
		break;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
			case IDC_LANG2LANG:
				switch(HIWORD(wParam))
				{
					case CBN_SELCHANGE:
					{
						int iCurSel=(int)SendMessage((HWND)lParam,CB_GETCURSEL,0,0);
						if(pLang2Lang!=KeysOptions.aLang2Lang+iCurSel)
						{
							Lang2LangFromTo *pLang2LangFromTo;
							int i;
							pLang2Lang=KeysOptions.aLang2Lang+iCurSel;
							pLang2LangFromTo=pLang2Lang->FromTo;
							for(i=(int)LANG2LANG_FROMTO;i>=0;i--)
								SendDlgItemMessage(hDlg,IDC_TO,CB_DELETESTRING,(WPARAM)i,0);
							while(*pLang2LangFromTo->szTo)
							{
								SendDlgItemMessage(hDlg,IDC_TO,CB_ADDSTRING,0,(WPARAM)pLang2LangFromTo->szTo);
								pLang2LangFromTo++;
							}
							SendDlgItemMessage(hDlg,IDC_TO,CB_SETCURSEL,(WPARAM)CB_ERR,0);
							for(i=IDC_FROM1;i<=IDC_FROM5;i++)
								SetDlgItemText(hDlg,i,_T(""));
						}
					}
					break;
				}
				break;
			case IDC_TO:
				switch(HIWORD(wParam))
				{
					case CBN_SELCHANGE:
					{
						int iCurSel=(int)SendMessage((HWND)lParam,CB_GETCURSEL,0,0);
						unsigned uID;
						if(iCurSel!=CB_ERR)
						{
							Lang2LangFrom *pLang2LangFrom=pLang2Lang->FromTo[iCurSel].From;
							for(uID=IDC_FROM1;uID<=IDC_FROM5;uID++,pLang2LangFrom++)
								SetDlgItemText(hDlg,uID,pLang2LangFrom->szFrom);
						}
						else
						{
							for(uID=IDC_FROM1;uID<=IDC_FROM5;uID++)
								SetDlgItemText(hDlg,uID,_T(""));
						}
					}
					break;
				}
				break;
			case IDC_FROM1:
			case IDC_FROM2:
			case IDC_FROM3:
			case IDC_FROM4:
			case IDC_FROM5:
				{
					TCHAR szFrom[LANG2LANGFROM_FROM];
					unsigned uID,i;
					int iCurSel;
					iCurSel=(int)SendDlgItemMessage(hDlg,IDC_TO,CB_GETCURSEL,0,0);
					if(iCurSel!=CB_ERR)
					{
						for(uID=IDC_FROM1,i=0;uID<=IDC_FROM5;uID++)
						{
							GetDlgItemText(hDlg,uID,szFrom,LANG2LANGFROM_FROM-1);
							if(*szFrom)
							{
								lstrcpy(pLang2Lang->FromTo[iCurSel].From[i].szFrom,szFrom);
								i++;
							}
						}
						for(;i<LANG2LANGFROM_FROM;i++)
							pLang2Lang->FromTo[iCurSel].From[i].szFrom[0]=0;
					}
				}
			}
			break;
		case WM_NOTIFY:
			switch(((NMHDR *)lParam)->code)
			{
				case PSN_APPLY:
					Options=KeysOptions;
					break;
			}
			break;
	}
	return FALSE;
}

// Helper functions
void CheckLang(HWND hWnd)
{
	if(LangFrom == LangTo)
	switch(LangFrom)
	{
		case ENG:
			CheckRadioButton(hWnd,IDC_ENGTO,IDC_RUSTO,IDC_RUSTO);
			LangTo=RUS;
			break;
		case RUS:
			CheckRadioButton(hWnd,IDC_ENGTO,IDC_RUSTO,IDC_ENGTO);
			LangTo=ENG;
			break;
	}
	switch(LangFrom)
	{
		case ENG:
			pLang2Lang=Options.aLang2Lang+ENG2RUS;
			break;
		case RUS:
			switch(LangTo)
			{
				default: // case ENG:
					LangTo=ENG;
					pLang2Lang=Options.aLang2Lang+RUS2ENG;
					break;
			}
			break;
	}
	CheckDlgButton(hWnd, IDC_ENGFROM, LangFrom == ENG);
	CheckDlgButton(hWnd, IDC_RUSFROM, LangFrom == RUS);
	CheckDlgButton(hWnd, IDC_ENGTO, LangTo == ENG);
	CheckDlgButton(hWnd, IDC_RUSTO, LangTo == RUS);
	EnableWindow(GetDlgItem(hWnd, IDC_ENGTO), LangFrom != ENG);
	EnableWindow(GetDlgItem(hWnd, IDC_RUSTO), LangFrom == ENG);
}

void Translate(Lang2Lang *pLang2Lang,LPCTSTR szFrom,LPTSTR szTo)
{
	int len;
	Lang2LangFromTo *pOLang2LangFromTo=pLang2Lang->FromTo;
	Lang2LangFromTo *pLang2LangFromTo;
	Lang2LangFrom *pLang2LangFrom;
	// Init
	ZeroMem(szTo,MAX_CHAR);
	while(*szFrom)
	{
		len=LANG2LANGFROM_FROM;
		while(len)
		{
			pLang2LangFromTo=pOLang2LangFromTo;
			while(*(*pLang2LangFromTo->From).szFrom)
			{
				pLang2LangFrom=pLang2LangFromTo->From;
				while(*pLang2LangFrom->szFrom)
				{
					if(len==lstrlen(pLang2LangFrom->szFrom))
						if(CmpStrLen(szFrom,pLang2LangFrom->szFrom)>=0&&
						!CmpStr(szFrom,pLang2LangFrom->szFrom))
							goto lFound;
					pLang2LangFrom++;
				}
				pLang2LangFromTo++;
			}
			len--;
		}
		goto lNotFound;
lFound:
		lstrcat(szTo,pLang2LangFromTo->szTo);
		szTo+=lstrlen(pLang2LangFromTo->szTo);
		szFrom+=len;
		continue;
lNotFound:
		*szTo++=*szFrom++;
	}
}

void UpdateHelp(HWND hWndEdit,Lang2Lang *pLang2Lang,LPTSTR szHelp,unsigned nChar)
{
	MakeHelp(pLang2Lang,szHelp,nChar);
	SetWindowText(hWndEdit,szHelp);
}

void MakeHelp(Lang2Lang *pLang2Lang,LPTSTR szHelp,unsigned nChar)
{
	Lang2LangFrom *pLang2LangFrom;
	Lang2LangFromTo *pLang2LangFromTo;
	ZeroMem(szHelp,nChar);
	while(*pLang2Lang->szName)
	{
		lstrcat(szHelp,pLang2Lang->szName);
		lstrcat(szHelp,_T(" : \n"));
		pLang2LangFromTo=pLang2Lang->FromTo;
		while(*pLang2LangFromTo->szTo)
		{
			lstrcat(szHelp,pLang2LangFromTo->szTo);
			lstrcat(szHelp,_T(" - "));
			pLang2LangFrom=pLang2LangFromTo->From;
			while(*pLang2LangFrom->szFrom)
			{
				lstrcat(szHelp,pLang2LangFrom->szFrom);
				pLang2LangFrom++;
				if(*pLang2LangFrom->szFrom)
					lstrcat(szHelp,_T(" , "));
			}
			pLang2LangFromTo++;
			lstrcat(szHelp,_T("\n"));
		}
		lstrcat(szHelp,_T("\n"));
		pLang2Lang++;
	}
}

BOOL LoadOptions(HKEY hKey,Lang2LangOptions *pLang2LangOptions)
{
	DWORD dwType=REG_BINARY;
	DWORD dwSize=sizeof(Lang2LangOptions);
	LONG lRes;
	Lang2LangOptions options;
	lRes=RegQueryValueEx(hKey,_T("Options"),0,&dwType,(LPBYTE)&options,&dwSize);
	if(!lRes&&dwType==REG_BINARY&&dwSize==sizeof(Lang2LangOptions))
	{
		*pLang2LangOptions=options;
		return TRUE;
	}
	else
		return FALSE;
}

BOOL SaveOptions(HKEY hKey,Lang2LangOptions *pLang2LangOptions)
{
	return !RegSetValueEx(hKey,_T("Options"),0,REG_BINARY,(CONST BYTE *)pLang2LangOptions,sizeof(Lang2LangOptions));
}

int DisplayOptions(HWND hWnd)
{
	PROPSHEETPAGE psp[2];
	PROPSHEETHEADER psh;
	int res;

	psp[0].dwSize = sizeof(PROPSHEETPAGE);
	psp[0].dwFlags = 0;
	psp[0].hInstance = g_hInstance;
	psp[0].pszTemplate = MAKEINTRESOURCE(IDD_GENERALPAGE);
	psp[0].pfnDlgProc = (DLGPROC)GeneralPageDlg;

	psp[1].dwSize = sizeof(PROPSHEETPAGE);
	psp[1].dwFlags = 0;
	psp[1].hInstance = g_hInstance;
	psp[1].pszTemplate = MAKEINTRESOURCE(IDD_KEYSPAGE);
	psp[1].pfnDlgProc = (DLGPROC)KeysPageDlg;

	psh.dwSize = sizeof(PROPSHEETHEADER);
	psh.dwFlags = PSH_PROPSHEETPAGE | PSH_NOAPPLYNOW;
	psh.dwFlags&=~(PSH_HASHELP);
	psh.hwndParent = hWnd;
	psh.hInstance = g_hInstance;
	psh.pszCaption = MAKEINTRESOURCE(IDS_OPTIONS);
	psh.nPages = sizeof(psp) / sizeof(PROPSHEETPAGE);
	psh.ppsp = (LPCPROPSHEETPAGE) &psp;

	res=(int)PropertySheet(&psh);

	UpdateHelp(GetDlgItem(hDlgHelp,IDC_HELPC),Options.aLang2Lang,szHelp,MAX_CHAR);

	return res;
}

BOOL ShowLang2LangIcon(HWND hWnd)
{ return NotifyIconAddID(hWnd,TRAYICON_ID,TRAYICON_MSG,g_hIcon,IDS_LANG2LANG); }
BOOL HideLang2LangIcon(HWND hWnd)
{ return NotifyIconDelete(hWnd,TRAYICON_ID); }

void LoadWindowPos(HWND hWnd,WindowPos *pWindowPos)
{
	WINDOWPLACEMENT wndpl;

	if(!(pWindowPos->rcNormalPosition.left&&
		pWindowPos->rcNormalPosition.right&&
		pWindowPos->rcNormalPosition.top&&
		pWindowPos->rcNormalPosition.bottom))
		return;

	wndpl.flags=WPF_SETMINPOSITION;
	wndpl.length=sizeof(WINDOWPLACEMENT);
	wndpl.ptMinPosition.x=0;
	wndpl.ptMinPosition.y=0;
	wndpl.ptMaxPosition.x=-GetSystemMetrics(SM_CXBORDER);
	wndpl.ptMaxPosition.y=-GetSystemMetrics(SM_CYBORDER);
	wndpl.flags=WPF_SETMINPOSITION;
	wndpl.rcNormalPosition=pWindowPos->rcNormalPosition;

	if(pWindowPos->bMin)
	{
		wndpl.showCmd=SW_SHOWMINNOACTIVE;
		if(pWindowPos->bMax)
			wndpl.flags=WPF_RESTORETOMAXIMIZED;
	}
	else
	{
		if(pWindowPos->bMax)
		{
			wndpl.showCmd=SW_SHOWMAXIMIZED;
			wndpl.flags=WPF_RESTORETOMAXIMIZED;
		}
		else
			wndpl.showCmd=SW_RESTORE;
	}

	SetWindowPlacement(hWnd,&wndpl);
}

void SaveWindowPos(HWND hWnd,WindowPos *pWindowPos)
{
	WINDOWPLACEMENT wndpl;

	wndpl.length=sizeof(WINDOWPLACEMENT);
	
	GetWindowPlacement(hWnd,&wndpl);

	if(wndpl.showCmd==SW_SHOWMAXIMIZED)
	{
		pWindowPos->bMin=FALSE;
		pWindowPos->bMax=TRUE;
	}
	else
	if(wndpl.showCmd==SW_SHOWMINIMIZED)
	{
		pWindowPos->bMin=TRUE;
		pWindowPos->bMax=wndpl.flags?TRUE:FALSE;
	}
	else // if(wndpl.showCmd==SW_SHOWNORMAL)
	{
		pWindowPos->bMin=FALSE;
		pWindowPos->bMax=FALSE;
	}
	pWindowPos->rcNormalPosition=wndpl.rcNormalPosition;
}

void Lang2LangToTray(HWND hWnd)
{
	ShowWindow(hWnd,SW_HIDE);
	if(!Options.bShowTrayIcon)
		ShowLang2LangIcon(hWnd);
}
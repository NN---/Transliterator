#include "StdAfx.h"
#include "Resource.h"

#include "TranslitDlg.h"
#include "AboutDlg.h"
#include "ChangeTranslationDlg.h"
#include "TranslateFilesDlg.h"
#include "OptionsSheet.h"
#include "TranslitCommandLine.h"

BOOL CTranslitDlg::PreTranslateMessage(MSG* pMsg)
{
	if(TranslateAccelerator(m_hWnd,m_hAccel,pMsg))
			return TRUE;
	return IsDialogMessage(pMsg);
}

BOOL CTranslitDlg::OnIdle()
{
	BOOL bSelection,bText;
	// Eng
	bSelection=m_richeditEngRus[Eng].GetSelectionType()!=SEL_EMPTY;
	bText=m_richeditEngRus[Eng].GetTextLength()?TRUE:FALSE;
	UIEnable(ID_EDIT_ENG_UNDO,m_richeditEngRus[Eng].CanUndo());
	UIEnable(ID_EDIT_ENG_REDO,m_richeditEngRus[Eng].CanRedo());
	UIEnable(ID_EDIT_ENG_CUT,bSelection);
	UIEnable(ID_EDIT_ENG_COPY,bSelection);
	UIEnable(ID_EDIT_ENG_PASTE,m_richeditEngRus[Eng].CanPaste());
	UIEnable(ID_EDIT_ENG_SELECTALL,bText);
	UIEnable(ID_EDIT_ENG_DELETE,bSelection);
	UIEnable(ID_EDIT_ENG_DELETEALL,bText);
	// Rus
	bSelection=m_richeditEngRus[Rus].GetSelectionType()!=SEL_EMPTY;
	bText=m_richeditEngRus[Rus].GetTextLength()?TRUE:FALSE;
	UIEnable(ID_EDIT_RUS_UNDO,m_richeditEngRus[Rus].CanUndo());
	UIEnable(ID_EDIT_RUS_REDO,m_richeditEngRus[Rus].CanRedo());
	UIEnable(ID_EDIT_RUS_CUT,bSelection);
	UIEnable(ID_EDIT_RUS_COPY,bSelection);
	UIEnable(ID_EDIT_RUS_PASTE,m_richeditEngRus[Rus].CanPaste());
	UIEnable(ID_EDIT_RUS_SELECTALL,bText);
	UIEnable(ID_EDIT_RUS_DELETE,bSelection);
	UIEnable(ID_EDIT_RUS_DELETEALL,bText);
	// Menu
	BOOL bEnglish=_Options.m_langID==MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US);
	UISetCheck(ID_TOOLS_LANGUAGE_ENGLISH,bEnglish);
	UISetCheck(ID_TOOLS_LANGUAGE_RUSSIAN,!bEnglish);
	UISetCheck(ID_TOOLS_TRANSLATION,_Options.m_bTranslation);
	UISetCheck(ID_EDIT_WRAPTEXT,_Options.m_bWrapText);
	// Tray Menu
	BOOL bVisible=IsWindowVisible();
	UIEnable(ID_SHOW,!bVisible);
	UIEnable(ID_HIDE,bVisible);

	return FALSE;
}

void CTranslitDlg::Translate(Translate::Direction dir)
{
	bool b1= dir==Translate::dirEngtoRus;

	CRichEditCtrl& richeditFrom=m_richeditEngRus[!b1];
	CRichEditCtrl& richeditTo=m_richeditEngRus[b1];

	AutoArray<WCHAR> aEngRus(_MAX_CHAR);

	richeditFrom.GetTextEx((LPTSTR)aEngRus.GetData(),_MAX_CHAR-1,GT_DEFAULT,1200);
	_Translit.TranslateW(aEngRus.GetData(),dir,_MAX_CHAR-1);
	richeditTo.SetTextEx((LPTSTR)aEngRus.GetData(),ST_DEFAULT,1200);
}

void CTranslitDlg::SetOptions()
{
	// Fonts
	for(int i=0;i<2;i++)
	{
		HFONT hFont=::CreateFontIndirect(&_Options.m_lfEngRus[i]);
		m_richeditEngRus[i].SetFont(hFont);
		::DeleteObject(hFont);
	}

	// HotKeys
	UnregisterHotKey(m_hWnd,hkIDTranslationEngtoRus);
	_Options.m_hkTranslationEngtoRus.Register(m_hWnd,hkIDTranslationEngtoRus);
	UnregisterHotKey(m_hWnd,hkIDTranslationRustoEng);
	_Options.m_hkTranslationRustoEng.Register(m_hWnd,hkIDTranslationRustoEng);
	UnregisterHotKey(m_hWnd,hkIDTranslationAuto);
	_Options.m_hkTranslationAuto.Register(m_hWnd,hkIDTranslationAuto);
	UnregisterHotKey(m_hWnd,hkIDShowTranslit);
	_Options.m_hkShowTranslit.Register(m_hWnd,hkIDShowTranslit);
	UnregisterHotKey(m_hWnd,hkIDHideTranslit);
	_Options.m_hkHideTranslit.Register(m_hWnd,hkIDHideTranslit);

	// Icon
	UpdateTrayIcon();

	// Text
	WrapText();

	// Translation
	m_dlgTranslation.UpdateTranslation();
	
	if(_Options.m_bTranslation)
		m_dlgTranslation.ShowWindow(SW_SHOWNORMAL);
}

void CTranslitDlg::SaveRegistry()
{
	LONG lRes;

	CRegKey regTranslit;
	lRes=regTranslit.Create(HKEY_CURRENT_USER,_T("Software\\NN\\Translit"));
	if(lRes)
		return;

	WINDOWPLACEMENT wndpl;
	wndpl.length=sizeof(WINDOWPLACEMENT);
	GetWindowPlacement(&wndpl);
	_Options.m_wndState.nCmdShow=wndpl.showCmd;

	regTranslit.SetBinaryValue(_T("Options"),&_Options,sizeof(Options));
	regTranslit.SetBinaryValue(_T("Translit"),&_Translit,sizeof(Translit));

	regTranslit.Close();

	CRegKey regStart;
	regStart.Open(HKEY_CURRENT_USER,_T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"));
	if(_Options.m_bLoadOnStartUp)
	{
		TCHAR szPath[256];
		GetModuleFileName(NULL,szPath,256);
		lstrcat(szPath,_T(" -hide"));
		regStart.SetStringValue(_T("Translit"),szPath);
		
	}
	else
		regStart.DeleteValue(_T("Translit"));
	regStart.Close();
}

void CTranslitDlg::LoadRegistry()
{
	LONG lRes;

	CRegKey regTranslit;
	lRes=regTranslit.Open(HKEY_CURRENT_USER,_T("Software\\NN\\Translit"));

	if(!lRes)
	{
		ULONG nSize;
		nSize=sizeof(Options);
		lRes=regTranslit.QueryBinaryValue(_T("Options"),&_Options,&nSize);
		if(lRes||nSize!=sizeof(Options))
			_Options.Default();

		Translit tempTranslit;
		nSize=sizeof(Translit);
		lRes=regTranslit.QueryBinaryValue(_T("Translit"),&tempTranslit,&nSize);
		if(lRes||nSize!=sizeof(Translit))
			_Translit.Default();
		else
			_Translit.SetData(tempTranslit);
	}
	else
	{
		_Options.Default();
		_Translit.Default();
	}
}


BOOL CTranslitDlg::Show()
{
	// Avoid problems with tray icon
	BOOL bTrayIconShown=_Options.m_bTrayIconShown;
	_Options.m_bTrayIconShown=FALSE;
	BOOL bTrayIconHidden=_Options.m_bTrayIconHidden;
	_Options.m_bTrayIconHidden=FALSE;
	if(!Create(NULL))
		return FALSE;
	_Options.m_bTrayIconShown=bTrayIconShown;
	_Options.m_bTrayIconHidden=bTrayIconHidden;
	
	TranslitCommandLine cmdLine;

	if(cmdLine.GetCommandLineInfo()==TranslitCommandLineInfo::Default())
	{
		if(_Options.m_wndState.nCmdShow==SW_HIDE)
			HotKeyShowTranslit(false);
		ShowWindow(_Options.m_wndState.nCmdShow);
	}
	else
	{
		if(cmdLine.GetCommandLineInfo().nCmdShow==SW_HIDE)
			HotKeyShowTranslit(false);
		ShowWindow(cmdLine.GetCommandLineInfo().nCmdShow);
	}
	m_bShown=IsWindowVisible()?true:false;
	UpdateTrayIcon();

	return TRUE;
}

void CTranslitDlg::CloseDialog()
{
	SaveRegistry();
	DestroyWindow();
	::PostQuitMessage(0);
}

void CTranslitDlg::UpdateTrayIcon()
{
	if(m_bShown)
	{
		if(_Options.m_bTrayIconShown)
		{
			if(!m_bTrayIcon)
			{
				m_bTrayIcon=!m_bTrayIcon;
				ShowTrayIcon();
			}
		}
		else
		{
			if(m_bTrayIcon)
			{
				m_bTrayIcon=!m_bTrayIcon;
				HideTrayIcon();
			}
		}
	}
	else
	{
		if(_Options.m_bTrayIconHidden)
		{
			if(!m_bTrayIcon)
			{
				m_bTrayIcon=!m_bTrayIcon;
				ShowTrayIcon();
			}
		}
		else
		{
			if(m_bTrayIcon)
			{
				m_bTrayIcon=!m_bTrayIcon;
				HideTrayIcon();
			}
		}
	}
	SetDefaultItem(m_bShown?ID_HIDE:ID_SHOW);
}

void CTranslitDlg::SaveWindowPlacement()
{
	WINDOWPLACEMENT wndpl;
	wndpl.length=sizeof(WINDOWPLACEMENT);
	GetWindowPlacement(&wndpl);
	if(wndpl.showCmd==SW_SHOWMINIMIZED||wndpl.showCmd==SW_MINIMIZE)
		wndpl.showCmd=SW_RESTORE;
	_Options.m_wndState.nCmdShow=wndpl.showCmd;
}

HWND CTranslitDlg::GetActiveWindowChild()
{
	DWORD dwThreadID = ::GetWindowThreadProcessId(::GetForegroundWindow(), NULL);
	GUITHREADINFO gti;

	ZeroMemory(&gti, sizeof(GUITHREADINFO));
	gti.cbSize = sizeof(GUITHREADINFO);
	::GetGUIThreadInfo(dwThreadID, &gti);
	return gti.hwndFocus;
}

void CTranslitDlg::HotKeyTranslation(Translate::Direction dir)
{
	HWND hWndTranslation = GetActiveWindowChild();

	TCHAR szClass[50];
	GetClassName(hWndTranslation,szClass,50);

	// Edit , RichEdit
	if(!lstrcmpi(szClass,_T("Edit"))||
		!lstrcmp(szClass,_T("TMemo"))||
		!ArrayTraits<TCHAR>::CompareArrayLength(szClass,_T("RichEdit"),8)||
		!ArrayTraits<TCHAR>::CompareArrayLength(szClass,_T("RICHEDIT"),8))
	{
		AutoArray<TCHAR> aEngRus(_MAX_CHAR);
		CEdit wndTranslation=hWndTranslation;

		int nStart,nEnd;
		wndTranslation.GetSel(nStart,nEnd);

		if(nStart==nEnd||(!nStart&&nEnd==-1))
		{
			wndTranslation.SendMessage(WM_GETTEXT,_MAX_CHAR-1,(LPARAM)aEngRus.GetData());
			_Translit.Translate(aEngRus.GetData(),DefineDirection(dir,aEngRus.GetData()),_MAX_CHAR);
			wndTranslation.SendMessage(WM_SETTEXT,0,(LPARAM)aEngRus.GetData());
		}
		else
		{
			AutoArray<TCHAR> aText(_MAX_CHAR);

			wndTranslation.SendMessage(WM_GETTEXT,_MAX_CHAR-1,(LPARAM)aEngRus.GetData());
			for(int nItem=nStart;nItem<nEnd;nItem++)
				aText[nItem-nStart]=aEngRus[nItem];
			aText[nItem-nStart]=0;
			_Translit.Translate(aText.GetData(),DefineDirection(dir,aText.GetData()),_MAX_CHAR-(nEnd-nStart));
			wndTranslation.ReplaceSel(aText.GetData(),TRUE);	
		}
	}
	// IE
	else
	if(!lstrcmp(szClass,_T("Internet Explorer_Server")))
	{
		HINSTANCE hOleAccInstance=::LoadLibrary(_T("OLEACC.DLL"));
		if(!hOleAccInstance)
			return;
		
		CComPtr<IHTMLDocument2> spDoc;
		LRESULT lRes;
			
		UINT nMsg = ::RegisterWindowMessage(_T("WM_HTML_GETOBJECT"));
		::SendMessageTimeout(hWndTranslation, nMsg, 0L, 0L, SMTO_ABORTIFHUNG, 1000, (DWORD*)&lRes);

		if(LPFNOBJECTFROMLRESULT pfObjectFromLresult = (LPFNOBJECTFROMLRESULT)::GetProcAddress(hOleAccInstance, _T("ObjectFromLresult")))
		{
			if(SUCCEEDED((*pfObjectFromLresult)(lRes, IID_IHTMLDocument, 0, (void**)&spDoc)))
			{
				CComPtr<IDispatch> spDisp;
				CComQIPtr<IHTMLWindow2> spWin;
				spDoc->get_Script(&spDisp);
				spWin = spDisp;
				spWin->get_document(&spDoc.p);
				CComQIPtr<IHTMLElement> spElem;
				spDoc->get_activeElement(&spElem.p);
				
				CComQIPtr<IHTMLInputTextElement> spInput;
				CComQIPtr<IHTMLTextAreaElement> spTA;
				if(SUCCEEDED(spElem->QueryInterface(IID_IHTMLInputTextElement,(void**)&spInput))||
					SUCCEEDED(spElem->QueryInterface(IID_IHTMLTextAreaElement,(void**)&spTA)))
				{
					CComBSTR strText;
					CComVariant v;
					AutoArray<WCHAR> aText(_MAX_CHAR);
					
					if(spInput.p)
						spInput->get_value(&strText);
					else
						spTA->get_value(&strText);

					for(int i=0;strText[i];i++)
						aText[i]=strText[i];
					aText[i]=0;
					_Translit.TranslateW(aText.GetData(),DefineDirection(dir,aText.GetData()),_MAX_CHAR);
					v=aText.GetData();
					strText.Empty();
					v.CopyTo(&strText);

					if(spInput.p)
						spInput->put_value(strText);
					else
						spTA->put_value(strText);
				}
			}
		::FreeLibrary(hOleAccInstance);
		} // else Active Accessibility is not installed
	}
	// Window
	else
	{
		AutoArray<TCHAR> aEngRus(_MAX_CHAR);

		::SendMessage(hWndTranslation,WM_GETTEXT,(WPARAM)(_MAX_CHAR-1),(LPARAM)aEngRus.GetData());
		_Translit.Translate(aEngRus.GetData(),DefineDirection(dir,aEngRus.GetData()),_MAX_CHAR);
		::SendMessage(hWndTranslation,WM_SETTEXT,0,(LPARAM)aEngRus.GetData());
	}
}

void CTranslitDlg::HotKeyShowTranslit(bool bShow)
{
	if(bShow)
		ShowWindow(_Options.m_wndState.nCmdShow);
	else
	{
		SaveWindowPlacement();
		ShowWindow(SW_HIDE);
	}
	m_bShown=IsWindowVisible()?true:false;
	UpdateTrayIcon();
}

inline Translate::Direction CTranslitDlg::DefineDirection(Translate::Direction dir,LPCSTR szText)
{
	if(dir==Translate::dirAuto)
	{
		EngRusTuple tuple={{szText[0],0},{szText[0],0}};
		unsigned u=_Translit.Find(tuple,0,0);
		if(u!=(unsigned)-1)
			return Translate::dirEngtoRus;
		u=_Translit.Find(tuple,0,1);
		if(u!=(unsigned)-1)
			return Translate::dirRustoEng;
		return _Options.m_nDefaultTranslation;
	}
	else
		return dir;
}

inline Translate::Direction CTranslitDlg::DefineDirection(Translate::Direction dir,LPCWSTR szText)
{
	TCHAR szTextA[2];
	::WideCharToMultiByte(1251,0,szText,1,szTextA,1,NULL,NULL);
	szTextA[1]=0;
	return DefineDirection(dir,szTextA);
}

void CTranslitDlg::InitControls()
{
	// RichEdit
	for(int iRichEdit=0;iRichEdit<2;iRichEdit++)
	{
		m_richeditEngRus[iRichEdit]=GetDlgItem(IDC_ENG+iRichEdit);
		m_richeditEngRus[iRichEdit].SetEventMask(ENM_CHANGE|ENM_KEYEVENTS|ENM_MOUSEEVENTS);
		m_richeditEngRus[iRichEdit].SendMessage(EM_SETLIMITTEXT,(_MAX_CHAR-1)/EngRusArray::nCountInit,0);
	}
}

void CTranslitDlg::InitMessageLoop()
{
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->AddMessageFilter(this);
	pLoop->AddIdleHandler(this);

	UIAddChildWindowContainer(m_hWnd);
}

void CTranslitDlg::InitMinTrackSize()
{
	RECT r;
	GetWindowRect(&r);
	m_ptMinTrackSize.x=r.right-r.left-40;
	m_ptMinTrackSize.y=r.bottom-r.top-40;
}

LRESULT CTranslitDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	InitMinTrackSize();
	DlgResize_Init(false,false);
	DialogIcon_Init();
	DialogStatusBar_Init();
	DialogLang_Init();

	// center the dialog on the screen
	CenterWindow();

	// Init controls
	InitControls();

	// Icon
	HICON hIconTray=::LoadIcon(_Module.GetResourceInstance(),MAKEINTRESOURCE(IDR_TRANSLIT));
	InitTrayIcon(IDR_TRANSLIT,hIconTray,IDR_TRAY);

	// Translation Dialog
	m_dlgTranslation.Create(m_hWnd);

	// Options
	SetOptions();

	m_hAccel=::LoadAccelerators(_Module.GetResourceInstance(),MAKEINTRESOURCE(IDR_TRANSLIT));

	// register object for message filtering and idle updates
	InitMessageLoop();
	
	return TRUE;
}

LRESULT CTranslitDlg::OnHotKey(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	switch(wParam)
	{
		case hkIDTranslationEngtoRus:HotKeyTranslation(Translate::dirEngtoRus);break;
		case hkIDTranslationRustoEng:HotKeyTranslation(Translate::dirRustoEng);break;
		case hkIDTranslationAuto:HotKeyTranslation(Translate::dirAuto);break;
		case hkIDShowTranslit:HotKeyShowTranslit(true);break;
		case hkIDHideTranslit:HotKeyShowTranslit(false);break;
	}
	return 0;
}

LRESULT CTranslitDlg::OnSysCommand(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
{
	bHandled=FALSE;
	if(LOWORD(wParam)==SC_CLOSE&&_Options.m_nClose==Options::closeExit)
		CloseDialog();
	else
	if(LOWORD(wParam)==SC_CLOSE||LOWORD(wParam)==SC_MINIMIZE&&_Options.m_nMinimize==Options::minimizeToTray)
	{
		bHandled=TRUE;
		ShowWindow(SW_MINIMIZE);
		HotKeyShowTranslit(false);
	}
	else
	if(LOWORD(wParam)==SC_RESTORE||LOWORD(wParam)==SC_MAXIMIZE)
	{
		bHandled=TRUE;
		ShowWindow(LOWORD(wParam)==SC_RESTORE?SW_RESTORE:SW_SHOWMAXIMIZED);
		m_bShown=true;
		UpdateTrayIcon();
	}
	return 0;
}

LRESULT CTranslitDlg::OnGetMinMaxInfo(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
	((LPMINMAXINFO)lParam)->ptMinTrackSize=m_ptMinTrackSize;
	return 0;
}

LRESULT CTranslitDlg::OnAppExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CloseDialog();
	return 0;
}

LRESULT CTranslitDlg::OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(!m_bHelpDialog)
	{
		m_bHelpDialog=true;
		CAboutDlg().DoModal();
		m_bHelpDialog=false;
	}
	return 0;
}

LRESULT CTranslitDlg::OnEnChangeEngRus(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	static bool bTranslation;
	if(!bTranslation)
	{
		bTranslation=true;
		Translate(wID==IDC_ENG?Translate::dirEngtoRus:Translate::dirRustoEng);
		bTranslation=false;
	}
	return 0;
}

LRESULT CTranslitDlg::OnToolsOptions(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(!m_bHelpDialog)
	{
		m_bHelpDialog=true;
		_Options.m_bTranslation=FALSE;
		bool bSetOptions=false;
		if(wID==ID_TOOLS_OPTIONS)
		{
			if(COptionsSheet().DoModal(m_hWnd)==IDOK)
				bSetOptions=true;
		}
		else
			if(CChangeTranslationDlg().DoModal(m_hWnd)==IDOK)
				bSetOptions=true;
		if(bSetOptions)
			SetOptions();
		
		m_bHelpDialog=false;
	}
	return 0;
}

LRESULT CTranslitDlg::OnToolsTranslation(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	_Options.m_bTranslation=!_Options.m_bTranslation;
	m_dlgTranslation.ShowWindow(_Options.m_bTranslation?SW_SHOW:SW_HIDE);
	return 0;
}

LRESULT CTranslitDlg::OnToolsLanguage(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(m_bHelpDialog)
		return 0;

	if(wID==ID_TOOLS_LANGUAGE_ENGLISH)
	{
		if(_Options.m_langID==MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US))
			return 0;
	}
	else
	{
		if(_Options.m_langID==MAKELANGID(LANG_RUSSIAN,SUBLANG_DEFAULT))
			return 0;
	}

	_Options.m_langID=
		_Options.m_langID==MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US)?
			(LANGID)MAKELANGID(LANG_RUSSIAN,SUBLANG_DEFAULT):
			(LANGID)MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US);


	UpdateLanguage();
	m_dlgTranslation.UpdateLanguage();
	m_dlgTranslation.UpdateTranslation();
	return 0;
}

LRESULT CTranslitDlg::OnShowHide(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	HotKeyShowTranslit(wID==ID_SHOW);
	UpdateTrayIcon();
	return 0;
}

LRESULT CTranslitDlg::OnToolsTranslateFiles(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CTranslateFilesDlg().DoModal();
	return 0;
}

LRESULT CTranslitDlg::OnEditEngRus(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CRichEditCtrl &richedit=m_richeditEngRus[wID<ID_EDIT_RUS_UNDO?Eng:Rus];
	switch(wID)
	{
		case ID_EDIT_ENG_UNDO:
		case ID_EDIT_RUS_UNDO:
			richedit.Undo();
			break;
		case ID_EDIT_ENG_REDO:
		case ID_EDIT_RUS_REDO:
			richedit.Redo();
			break;
		case ID_EDIT_ENG_CUT:
		case ID_EDIT_RUS_CUT:
			richedit.Cut();
			break;
		case ID_EDIT_ENG_COPY:
		case ID_EDIT_RUS_COPY:
			richedit.Copy();
			break;
		case ID_EDIT_ENG_PASTE:
		case ID_EDIT_RUS_PASTE:
			richedit.Paste();
			break;
		case ID_EDIT_ENG_SELECTALL:
		case ID_EDIT_RUS_SELECTALL:
			richedit.SetSelAll();
			break;
		case ID_EDIT_ENG_DELETE:
		case ID_EDIT_RUS_DELETE:
			richedit.Clear();
			break;
		case ID_EDIT_ENG_DELETEALL:
		case ID_EDIT_RUS_DELETEALL:
			richedit.SetSel(0, -1);
			richedit.Clear();
			break;
	}
	return 0;
}

LRESULT CTranslitDlg::OnEnMsgFilterEngRus(int /*code*/, NMHDR *pnmhdr, BOOL& /*bHandled*/)
{
	MSGFILTER *pMsgFilter=(MSGFILTER *)pnmhdr;
	if(pMsgFilter->msg==WM_RBUTTONDOWN)
	{
		HMENU hMenu;
		POINT pt;
		::GetCursorPos(&pt);
		hMenu=GetMenu();
		hMenu=::GetSubMenu(hMenu,1);
		hMenu=::GetSubMenu(hMenu,pnmhdr->idFrom==IDC_ENG?0:1);
		::TrackPopupMenu(hMenu,TPM_LEFTALIGN|TPM_LEFTBUTTON|
			TPM_RIGHTBUTTON,pt.x,pt.y,0,m_hWnd,NULL);
	}
	return 0;
}

LRESULT CTranslitDlg::OnEditNoTranslate(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(wID==ID_EDIT_NOTRANSLATE_SET)
	{
	}
	else
	{
	}
	return 0;
}
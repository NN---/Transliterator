#include "StdAfx.h"
#include "Resource.h"

#include "TranslitDlg.h"
#include "TranslitCommandLine.h"
#include "AboutDlg.h"
#include "TranslateFilesDlg.h"
#include "OptionsSheet.h"

CTranslitDlg::CTranslitDlg() :
	m_hAccel(NULL),
	m_bShown(false),
	m_bTrayIcon(false),
	m_bDlg(false)
{
	m_ptMinTrackSize.x=m_ptMinTrackSize.y=180;
}

BOOL CTranslitDlg::PreTranslateMessage(MSG* pMsg)
{
	if(TranslateAccelerator(m_hWnd,m_hAccel,pMsg))
			return TRUE;
	return IsDialogMessage(pMsg);
}

BOOL CTranslitDlg::OnIdle()
{
	BOOL bSelection,bText;
	CRichEditCtrl re=GetFocus();
	if(re==m_reEngRus[Eng]||
		re==m_reEngRus[Rus])
	{
		bSelection=re.GetSelectionType()!=SEL_EMPTY;
		bText=re.GetTextLength()?TRUE:FALSE;
		UIEnable(ID_EDIT_UNDO,re.CanUndo());
		UIEnable(ID_EDIT_REDO,re.CanRedo());
		UIEnable(ID_EDIT_CUT,bSelection);
		UIEnable(ID_EDIT_COPY,bSelection);
		UIEnable(ID_EDIT_PASTE,re.CanPaste());
		UIEnable(ID_EDIT_SELECT_ALL,bText);
		UIEnable(ID_EDIT_CLEAR,bSelection);
		UIEnable(ID_EDIT_CLEAR_ALL,bText);
	}
	UISetCheck(ID_EDIT_TRANSLATE,_Options.m_bTranslate);
	
	BOOL bEnglish=_LangID==MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US);
	UISetCheck(ID_VIEW_LANGUAGE_ENGLISH,bEnglish);
	UISetCheck(ID_VIEW_LANGUAGE_RUSSIAN,!bEnglish);
	UISetCheck(ID_TOOLS_TRANSLATION,_Options.m_bTranslation);
	UISetCheck(ID_VIEW_LAYOUT_WRAPTEXT,_Options.m_bWrapText);
	UISetCheck(ID_VIEW_LAYOUT_SCROLLTEXT,_Options.m_bScrollText);
	// Tray Menu
	BOOL bVisible=IsWindowVisible();
	UIEnable(ID_SHOW,!bVisible);
	UIEnable(ID_HIDE,bVisible);

	return FALSE;
}

void CTranslitDlg::Translate(Translate::Direction dir)
{
	bool b1= dir==Translate::dirEngtoRus;

	CRichEditCtrl reFrom=m_reEngRus[!b1];
	CRichEditCtrl reTo=m_reEngRus[b1];

	NN::AutoArray<WCHAR> aEngRus(_MAX_CHAR);

	reFrom.GetTextEx((LPSTR)aEngRus.GetData(),(_MAX_CHAR-1)*sizeof(WCHAR),GT_DEFAULT,1200);
	_Translit.TranslateW(aEngRus.GetData(),dir,_MAX_CHAR-1);
	reTo.SetTextEx((LPCSTR)aEngRus.GetData(),ST_DEFAULT,1200);
}

BOOL CTranslitDlg::Show()
{
	// Avoid problems with tray icon
	{
		NN::AutoSGRef<BOOL> sgTrayIconShown(
				_Options.m_bTrayIconShown,
				FALSE,
				_Options.m_bTrayIconShown);
		NN::AutoSGRef<BOOL> sgTrayIconHidden(
				_Options.m_bTrayIconHidden,
				FALSE,
				_Options.m_bTrayIconHidden);

		if(!Create(NULL))
			return FALSE;
	}

	TranslitCommandLine cmdLine;

	int nCmdShow;

	if(cmdLine.GetCommandLineInfo().IsDefault())
		nCmdShow=_Options.m_wndState.nCmdShow;
	else // CmdLine
		nCmdShow=cmdLine.GetCommandLineInfo().nCmdShow;

	if(nCmdShow==SW_HIDE)
		HotKeyShowTranslit(false);
	else
		ShowWindow(nCmdShow);

	m_bShown=(bool)IsWindowVisible();
	UpdateTrayIcon();

	return TRUE;
}

void CTranslitDlg::CloseDialog()
{
	SaveRegistry();
	DestroyWindow();
	::PostQuitMessage(0);
}

void CTranslitDlg::SetOptionsFont()
{
	// Fonts
	for(int i=0;i<2;i++)
	{
		HFONT hFont=::CreateFontIndirect(&_Options.m_lfEngRus[i]);
		m_reEngRus[i].SetFont(hFont);
		::DeleteObject(hFont);
	}
}

void CTranslitDlg::SetOptions()
{
	SetOptionsFont();

	// HotKeys
	for(int i=0;i<Options::nHotKey;i++)
		UnregisterHotKey(m_hWnd,hkID+i);

	for(int i=0;i<Options::nHotKey;i++)
	{
		if(_Options.m_hkTranslit[i].GetHotKey())
			_Options.m_hkTranslit[i].Register(m_hWnd,hkID+i);
	}
	
	// Icon
	UpdateTrayIcon();

	// Translation
//	m_dlgTranslation.UpdateTranslation();
	
//	if(_Options.m_bTranslation)
//		m_dlgTranslation.ShowWindow(SW_SHOWNORMAL);
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
	regTranslit.SetBinaryValue(_T("Translit"),_Translit.GetData(),sizeof(Translit));
	regTranslit.SetBinaryValue(_T("LangID"),&_LangID,sizeof(LANGID));

	regTranslit.Close();

	CRegKey regStart;
	regStart.Open(HKEY_CURRENT_USER,_T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"));
	if(_Options.m_bLoadOnStartUp)
	{
		TCHAR szPath[_MAX_PATH];
		GetModuleFileName(NULL,szPath,_MAX_PATH);
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
			_Options.Reset();

		Translit tempTranslit;
		nSize=sizeof(Translit);
		lRes=regTranslit.QueryBinaryValue(_T("Translit"),&tempTranslit,&nSize);
		if(lRes||nSize!=sizeof(Translit))
			_Translit.Reset();
		else
			_Translit.SetData(tempTranslit);

		nSize=sizeof(LANGID);
		lRes=regTranslit.QueryBinaryValue(_T("LangID"),&_LangID,&nSize);
		if(lRes||nSize!=sizeof(LANGID))
			_LangID=_LangIDDefault;
	}
	else
	{
		_Options.Reset();
		_Translit.Reset();
		_LangID=_LangIDDefault;
	}
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
		!lstrcmp(szClass,_T("TTextEditor"))||
		!NN::ArrayTraits<TCHAR>::CompareArrayLength(szClass,_T("RichEdit"),8)||
		!NN::ArrayTraits<TCHAR>::CompareArrayLength(szClass,_T("RICHEDIT"),8))
	{
		NN::AutoArray<TCHAR> aEngRus(_MAX_CHAR);
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
			NN::AutoArray<TCHAR> aText(_MAX_CHAR);

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
					NN::AutoArray<WCHAR> aText(_MAX_CHAR);
					
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
		NN::AutoArray<TCHAR> aEngRus(_MAX_CHAR);

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
	m_bShown=(bool)IsWindowVisible();
	UpdateTrayIcon();
}

inline Translate::Direction CTranslitDlg::DefineDirection(Translate::Direction dir,LPCSTR szText)
{
	if(dir==Translate::dirAuto)
	{
		CHAR str[2]={szText[0]};
		EngRusType tuple(str,str);
		unsigned u=_Translit.Find(tuple,0,0);
		if(u!=(unsigned)-1)
			return Translate::dirEngtoRus;
		u=_Translit.Find(tuple,0,1);
		if(u!=(unsigned)-1)
			return Translate::dirRustoEng;
		return _Options.m_nAutoTranslation;
	}
	else
		return dir;
}

inline Translate::Direction CTranslitDlg::DefineDirection(Translate::Direction dir,LPCWSTR szText)
{
	CHAR szTextA[2];
	::WideCharToMultiByte(1251,0,szText,1,szTextA,1,NULL,NULL);
	szTextA[1]=0;
	return DefineDirection(dir,szTextA);
}

void CTranslitDlg::InitControls()
{
	RECT rectEngRus[2];
	bool bCreated=m_reEngRus[0].m_hWnd&&m_reEngRus[1].m_hWnd;
	NN::AutoSGRef<BOOL> sg(_Options.m_bTranslate,FALSE,_Options.m_bTranslate);

	// Save Position and Text
	NN::AutoArray<WCHAR> aEngRus[2];
	if(bCreated)
	{
		for(int i=0;i<2;i++)
		{
			// Position
			m_reEngRus[i].GetWindowRect(rectEngRus+i);
			ScreenToClient(&rectEngRus[i]);
			// Text
			aEngRus[i].Attach(new WCHAR[_MAX_CHAR]);
			m_reEngRus[i].GetTextEx((LPSTR)aEngRus[i].GetData(),(_MAX_CHAR-1)*sizeof(WCHAR),GT_DEFAULT,1200);
			// Destroy
			m_reEngRus[i].DestroyWindow();
		}
	}
	else
	{
		for(int i=0;i<2;i++)
		{
			::GetWindowRect(GetDlgItem(IDC_SENGPLACE+i),&rectEngRus[i]);
			ScreenToClient(&rectEngRus[i]);
		}		
	}

	// Create
	DWORD dwStyle=
		WS_TABSTOP|
		WS_BORDER|
		WS_CHILD|
		WS_VISIBLE|
		ES_WANTRETURN|
		ES_MULTILINE|
		WS_VSCROLL|
		ES_AUTOVSCROLL;
	
	if(!_Options.m_bWrapText)
		dwStyle|=WS_HSCROLL|ES_AUTOHSCROLL;
	DWORD dwExStyle=0;

	for(int i=0;i<2;i++)
	{
		m_reEngRus[i]=
		::CreateWindowEx(
			dwExStyle,
			_T("RichEdit20A"),
			_T(""),
			dwStyle,
			rectEngRus[i].left,
			rectEngRus[i].top,
			rectEngRus[i].right-rectEngRus[i].left,
			rectEngRus[i].bottom-rectEngRus[i].top,
			m_hWnd,
			(HMENU)(IDC_ENG+i),
			_Module.GetModuleInstance(),0
			);

		if(!m_reEngRus[i].m_hWnd)
		{
			ShowError(m_hWnd,_T("Cannot create text box"));
			return;
		}

		m_reEngRus[i].SendMessage(EM_SETLIMITTEXT,(_MAX_CHAR-1),0);
		m_reEngRus[i].SetEventMask(ENM_CHANGE|ENM_KEYEVENTS|ENM_MOUSEEVENTS);
		if(bCreated)
			m_reEngRus[i].SetTextEx((LPCSTR)aEngRus[i].GetData(),ST_DEFAULT,1200);
	}

	SetOptionsFont();
}

void CTranslitDlg::InitMessageLoop()
{
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->AddMessageFilter(this);
	pLoop->AddIdleHandler(this);

	UIAddChildWindowContainer(m_hWnd);
}

LRESULT CTranslitDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	InitControls();
	DialogIcon_Init();
	DialogStatusBar_Init();
	DialogLang_Init();
	DlgResize_Init(false,true);

	CenterWindow();

	m_hAccel=::LoadAccelerators(_Module.GetResourceInstance(),MAKEINTRESOURCE(IDR_TRANSLIT));

	InitTrayIcon(IDR_TRANSLIT,
		::LoadIcon(_Module.GetResourceInstance(),MAKEINTRESOURCE(IDR_TRANSLIT)),
		IDR_TRAYICON);

	SetOptions();

	InitMessageLoop();
	
	return TRUE;
}

LRESULT CTranslitDlg::OnSysCommand(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
{
	bHandled=FALSE;
	WORD wMsg=LOWORD(wParam);
	if(wMsg==SC_CLOSE&&_Options.m_nClose==Options::closeExit)
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
	bHandled=FALSE;
	return 0;
}

LRESULT CTranslitDlg::OnHotKey(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	switch(wParam-hkID)
	{
		case Options::hkCommandsMenu:
			{
				HMENU hMenu;
				POINT pt;
				::GetCursorPos(&pt);
				hMenu=::LoadMenu(_Module.GetModuleInstance(),
					MAKEINTRESOURCE(IDR_TRAYICON));
				hMenu=::GetSubMenu(hMenu,0);
				::TrackPopupMenu(hMenu,TPM_LEFTALIGN|TPM_LEFTBUTTON|
					TPM_RIGHTBUTTON,pt.x,pt.y,0,m_hWnd,NULL);
			}
			break;
		case Options::hkEngtoRus:
			HotKeyTranslation(Translate::dirEngtoRus);
			break;
		case Options::hkRustoEng:
			HotKeyTranslation(Translate::dirRustoEng);
			break;
		case Options::hkAuto:
			HotKeyTranslation(Translate::dirAuto);
			break;
		case Options::hkShow:
			HotKeyShowTranslit(true);
			break;
		case Options::hkHide:
			HotKeyShowTranslit(false);
			break;
		case Options::hkInsertNoTranslate:
			break;
		case Options::hkDeleteNoTranslate:
			break;
		case Options::hkCopyEng:
			break;
		case Options::hkCopyRus:
			break;
	}
	return 0;
}

LRESULT CTranslitDlg::OnAppExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CloseDialog();
	return 0;
}

LRESULT CTranslitDlg::OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	static bool bAbout;
	if(!bAbout)
	{
		NN::AutoSGRef<bool> sg(bAbout,true,false);
		CAboutDlg().DoModal();
	}
	return 0;
}

LRESULT CTranslitDlg::OnEditCommands(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CRichEditCtrl re=GetFocus();
	switch(wID)
	{
		case ID_EDIT_UNDO: re.Undo(); break;
		case ID_EDIT_REDO: re.Redo(); break;
		case ID_EDIT_CUT: re.Cut(); break;
		case ID_EDIT_COPY: re.Copy(); break;
		case ID_EDIT_PASTE: re.Paste(); break;
		case ID_EDIT_SELECT_ALL: re.SetSelAll(); break;
		case ID_EDIT_CLEAR_ALL: re.SetSel(0, -1);
		case ID_EDIT_CLEAR: re.Clear(); break;
	}
	return 0;
}

LRESULT CTranslitDlg::OnEditTranslate(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	_Options.m_bTranslate=!_Options.m_bTranslate;
	Translate(GetFocus()==m_reEngRus[Eng]?Translate::dirEngtoRus:Translate::dirRustoEng);
	return 0;
}

LRESULT CTranslitDlg::OnEditNoTranslate(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CRichEditCtrl re=GetFocus();

	int nLen=re.GetTextLength();
	if(!nLen)
		return 0;
	nLen++;
	
	// Get Text
	NN::AutoArray<WCHAR> aText(nLen*2);
	re.GetTextEx((LPSTR)aText.GetData(),nLen*sizeof(WCHAR),GT_DEFAULT,1200);
	if(!aText.GetData()||!aText[0])
		return 0;

	// Translate
	_Translit.NoTranslateW(aText.GetData(),nLen*2,re==m_reEngRus[Eng],wID==ID_EDIT_NOTRANSLATE_INSERT);
	
	// Set Text
	re.SetTextEx((LPCSTR)aText.GetData(),ST_DEFAULT,1200);

	return 0;
}


LRESULT CTranslitDlg::OnEditCopyEngRus(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	NN::AutoSGRef<BOOL> sg(_Options.m_bTranslate,FALSE);
	
	bool b1= wID==ID_EDIT_COPY_ENGTORUS;

	CRichEditCtrl& reFrom=m_reEngRus[!b1];
	CRichEditCtrl& reTo=m_reEngRus[b1];

	int nLen=reFrom.GetTextLength()+1;
	NN::AutoArray<WCHAR> aText(nLen);
	reFrom.GetTextEx((LPSTR)aText.GetData(),nLen,GT_DEFAULT,1251);
	reTo.SetTextEx((LPCSTR)aText.GetData(),ST_DEFAULT,1251);

	return 0;
}

LRESULT CTranslitDlg::OnViewLanguage(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	_LangID= wID==ID_VIEW_LANGUAGE_ENGLISH?
		MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US):
		MAKELANGID(LANG_RUSSIAN,SUBLANG_DEFAULT);
	
	UpdateLanguage();
	//m_dlgTranslation.UpdateLanguage();
	//m_dlgTranslation.UpdateTranslation();
	return 0;
}

LRESULT CTranslitDlg::OnViewLayoutWrapScrollText(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(wID==ID_VIEW_LAYOUT_WRAPTEXT)
		_Options.m_bWrapText=!_Options.m_bWrapText;
	else
		_Options.m_bScrollText=!_Options.m_bScrollText;

	InitControls();

	return 0;
}

LRESULT CTranslitDlg::OnToolsTranslateFiles(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	static bool bTF;
	if(!bTF)
	{
		NN::AutoSGRef<bool> sg(bTF,true,false);
		CTranslateFilesDlg().DoModal();
	}
	return 0;
}

LRESULT CTranslitDlg::OnToolsOptions(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	static bool bOptions;
	if(!bOptions)
	{
		NN::AutoSGRef<bool> sg(bOptions,true,false);
		COptionsSheet options;
		if(options.DoModal()==IDOK)
			SetOptions();
	}
	return 0;
}

LRESULT CTranslitDlg::OnEnChangeEngRus(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	static bool bTranslate=false;
	if(_Options.m_bTranslate&&!bTranslate)
	{
		NN::AutoSGRefT<bool,true,false> sg(bTranslate);
		Translate(wID==IDC_ENG?Translate::dirEngtoRus:Translate::dirRustoEng);
	}
	return 0;
}

LRESULT CTranslitDlg::OnEnMsgFilterEngRus(int /*code*/, NMHDR *pnmhdr, BOOL& /*bHandled*/)
{
	MSGFILTER *pMsgFilter=(MSGFILTER *)pnmhdr;
	if(pMsgFilter->msg==WM_RBUTTONDOWN)
	{
		::SetFocus(pnmhdr->hwndFrom);
		HMENU hMenu;
		POINT pt;
		::GetCursorPos(&pt);
		hMenu=GetMenu();
		hMenu=::GetSubMenu(hMenu,1);
		::TrackPopupMenu(hMenu,TPM_LEFTALIGN|TPM_LEFTBUTTON|
			TPM_RIGHTBUTTON,pt.x,pt.y,0,m_hWnd,NULL);
	}
	return 0;
}

LRESULT CTranslitDlg::OnShowHide(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	HotKeyShowTranslit(wID==ID_SHOW);
	UpdateTrayIcon();
	return 0;
}
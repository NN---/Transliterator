#include "stdafx.h"
#include "resource.h"

#include "transliteratordlg.h"
#include "progcommandline.h"

const LANGID CTransliteratorDlg::s_langEnglish=MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US);
const LANGID CTransliteratorDlg::s_langRussian=MAKELANGID(LANG_RUSSIAN,SUBLANG_DEFAULT);
const LANGID CTransliteratorDlg::s_langTranslit=MAKELANGID(LANG_RUSSIAN,SUBLANG_DEFAULT+4);

BOOL CTransliteratorDlg::OnIdle()
{
	BOOL bSelection,bText;
	CRichEditCtrl re=::GetFocus();

	if(re==m_reTrnsRus[Trns]||
		re==m_reTrnsRus[Rus])
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
		UIEnable(ID_EDIT_IGNORE_INSERT,TRUE);
		UIEnable(ID_EDIT_IGNORE_REMOVE,TRUE);
	}
	else
	{
		for(int i=ID_EDIT_CLEAR;i<ID_EDIT_REDO;i++)
			UIEnable(i,FALSE);
		UIEnable(ID_EDIT_IGNORE_INSERT,FALSE);
		UIEnable(ID_EDIT_IGNORE_REMOVE,FALSE);
	}

	UISetCheck(ID_VIEW_LANGUAGE_ENGLISH,g_LangID==s_langEnglish);
	UISetCheck(ID_VIEW_LANGUAGE_RUSSIAN,g_LangID==s_langRussian);
	UISetCheck(ID_VIEW_LANGUAGE_TRANSLIT,g_LangID==s_langTranslit);
	
	UISetCheck(ID_VIEW_CONTROLS_WRAPTEXT,g_Options.m_bWrapText);
	UISetCheck(ID_VIEW_CONTROLS_SCROLLTEXT,g_Options.m_bScrollText);
	UISetCheck(ID_VIEW_CONTROLS_AUTOTRANSLITERATION,g_Options.m_bTranslate);
	UISetCheck(ID_VIEW_CONTROLS_AUTOIGNORE,g_Options.m_bIgnore);
		
	UISetCheck(ID_TOOLS_TRANSLATION,m_dlgTranslation.IsWindowVisible());
	UISetCheck(ID_TOOLS_TRANSLATEFILES,m_dlgTranslateFiles.IsWindowVisible());
	UISetCheck(ID_TOOLS_OPTIONS,m_dlgOptions.IsWindowVisible());

	UISetCheck(ID_APP_ABOUT,m_dlgAbout.IsWindowVisible());

	// Tray Menu
	BOOL bVisible=IsWindowVisible();
	UIEnable(ID_SHOW,!bVisible);
	UIEnable(ID_HIDE,bVisible);

	// Profile
	char strText[100];
	char strKey[2]={0};
	for(unsigned i=0;i<Language::nProfiles;i++)
	{
		lstrcpy(strText,g_Language.GetProfile((Language::Profiles)i)->m_strName);
		lstrcat(strText,"\tCtrl+");
		strKey[0]=(char)i+'1';
		lstrcat(strText,strKey);

		UISetText(ID_PROFILE1+i,strText);

		UISetCheck(ID_PROFILE1+i,i==g_Options.m_nCurProfile?1:0);
	}
	
	return FALSE;
}

void CTransliteratorDlg::DlgResize_UpdateLayout(int cxWidth, int cyHeight)
{
	CDialogResize<CTransliteratorDlg>::DlgResize_UpdateLayout(cxWidth,cyHeight);
	UpdateLayout();
}

void CTransliteratorDlg::Translate(Translate::Direction dir)
{
	bool b1= dir==Translate::dirTrnstoRus;

	CRichEditCtrl reFrom=m_reTrnsRus[!b1];
	CRichEditCtrl reTo=m_reTrnsRus[b1];

	const unsigned nChar=((unsigned)reFrom.GetWindowTextLength()+1)*LangString::nCountInit;
	NN::auto_array<wchar_t> aText(nChar*2);
	if(!aText.data())
		return;
	
	{
		NN::auto_sg_ref<BOOL> sg(g_Options.m_bTranslate,FALSE,g_Options.m_bTranslate);

		reFrom.GetTextEx((LPSTR)aText.data(),nChar*sizeof(wchar_t),GT_DEFAULT,1200);
		g_Language.Translate(aText.data(),dir,nChar);
		reTo.SetTextEx((LPCSTR)aText.data(),ST_DEFAULT,1200);
	}
}

bool CTransliteratorDlg::Show()
{
	LoadSettings();

	if(!Create(::GetDesktopWindow()))
		return false;

	// Command Line
	ProgCommandLine cmdLine;
	int nCmdShow;
	if(cmdLine.GetCommandLineInfo().IsDefault())
		nCmdShow=g_Options.m_wndState.nCmdShow;
	else // CmdLine
		nCmdShow=cmdLine.GetCommandLineInfo().nCmdShow;

	ShowWindow(nCmdShow);
	
	m_bShown = (nCmdShow==SW_HIDE||
		((nCmdShow==SW_MINIMIZE||nCmdShow==SW_SHOWMINIMIZED)&&
			g_Options.m_bShowTrayIcon))?false:true;
	if(!m_bShown)
		ShowWindow(SW_HIDE);

	UpdateTrayIcon();
	UpdateTaskBar();
	
	return true;
}

void CTransliteratorDlg::CloseDialog()
{
	SaveSettings();
	m_dlgTranslation.DestroyWindow();
	m_dlgTranslateFiles.DestroyWindow();
	m_dlgOptions.DestroyWindow();
	m_dlgAbout.DestroyWindow();
	DestroyWindow();
	::PostQuitMessage(0);
}

void CTransliteratorDlg::UpdateLayout()
{
	for(int i=0;i<2;i++)
	{
		RECT rect;
		::GetWindowRect(GetDlgItem(IDC_STRNSTEXT+i),&rect);
		ScreenToClient(&rect);
		rect.left+=size_delta_left;
		rect.right-=size_delta_right;
		rect.top+=size_delta_top;
		rect.bottom-=size_delta_bottom;
		::MoveWindow(GetDlgItem(IDC_TRNS+i),rect.left,rect.top,rect.right-rect.left,rect.bottom-rect.top,TRUE);
	}
}

BOOL CTransliteratorDlg::LoadData(CRegKey& reg,const char* strData,void* data,unsigned size)
{
	ULONG nSize=size;
	LONG lRes=reg.QueryBinaryValue(strData,data,&nSize);
	return (lRes||nSize!=size);
}

BOOL CTransliteratorDlg::LoadDataSize(CRegKey& reg,const char* strData,void* data,unsigned size)
{
	ULONG nSize=size;
	LONG lRes=reg.QueryBinaryValue(strData,data,&nSize);
	return (lRes||!nSize||nSize>size);
}

void CTransliteratorDlg::LoadSettings()
{
	CRegKey regProg;

	if(!regProg.Open(HKEY_CURRENT_USER,"Software\\NN\\Transliterator"))
	{
		g_Language.ResetAll();

		char strUser[6]="User";
		LangProfile langprof;
		for(int i=Language::profUser1;i<Language::nProfiles;i++)
		{
			strUser[4]=(char)(i-Language::profUser1)+'1';
			if(!LoadData(regProg,strUser,&langprof,sizeof(LangProfile)))
				memcpy(g_Language.GetProfile((Language::Profiles)i),&langprof,sizeof(LangProfile));
		}
		
		if(LoadData(regProg,"Options",&g_Options,sizeof(Options)))
			g_Options.Reset();
		if(LoadData(regProg,"Ignore",&g_Ignore,sizeof(Ignore)))
			g_Ignore.Reset();
		if(LoadData(regProg,"LangID",&g_LangID,sizeof(LANGID)))
			g_LangID=g_LangIDDefault;

		const unsigned nChar=MAX_SYMBOL*LangString::nCountInit;

		static const char astrTrnsRusText[2][10]={"TrnsText","RusText"};

		for(int i=0;i<2;i++)
		{
			m_aText[i].alloc(nChar);
			if(m_aText[i].data())
				if(LoadDataSize(regProg,astrTrnsRusText[i],m_aText[i].data(),nChar))
					m_aText[i].free();
		}
	}
	else
	{
		g_Options.Reset();
		g_Language.ResetAll();
		g_Ignore.Reset();
		g_LangID=g_LangIDDefault;
	}
	g_Language.SetCurProfile((Language::Profiles)g_Options.m_nCurProfile);
}

void CTransliteratorDlg::SaveSettings()
{
	CRegKey regProg;
	if(regProg.Create(HKEY_CURRENT_USER,"Software\\NN\\Transliterator"))
		return;

	WINDOWPLACEMENT wndpl;
	wndpl.length=sizeof(WINDOWPLACEMENT);
	GetWindowPlacement(&wndpl);
	g_Options.m_wndState.nCmdShow=wndpl.showCmd;

	regProg.SetBinaryValue("Options",&g_Options,sizeof(Options));
	regProg.SetBinaryValue("Ignore",&g_Ignore,sizeof(Ignore));
	regProg.SetBinaryValue("LangID",&g_LangID,sizeof(LANGID));
	
	// Profiles
	char strUser[6]="User";
	for(int i=Language::profUser1;i<Language::nProfiles;i++)
	{
		strUser[4]=(char)(i-Language::profUser1)+'1';
	
		regProg.SetBinaryValue(strUser,g_Language.GetProfile((Language::Profiles)i),sizeof(LangProfile));
	}

	// Text
	unsigned anChar[2];
	for(int i=0;i<2;i++)
	{
		anChar[i]=(unsigned)m_reTrnsRus[i].GetWindowTextLength()+1;
		m_aText[i].alloc(anChar[i]);
		if(!m_aText[i].data())
			break;
	
		m_reTrnsRus[i].GetTextEx((LPSTR)m_aText[i].data(),anChar[i]*sizeof(wchar_t),GT_DEFAULT,1200);

		regProg.SetBinaryValue("TrnsText",m_aText[Trns].data(),anChar[i]*sizeof(wchar_t));
		regProg.SetBinaryValue("RusText",m_aText[Rus].data(),anChar[i]*sizeof(wchar_t));
		m_aText[i].free();
	}
	m_aText[Trns].free();
	m_aText[Rus].free();

	regProg.Close();

	CRegKey regStart;
	regStart.Open(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Run");
	if(g_Options.m_nLoadOnStartUp!=Options::loadNo)
	{
		TCHAR szPath[_MAX_PATH+30];
		::GetModuleFileName(NULL,szPath,_MAX_PATH);
		if(g_Options.m_nLoadOnStartUp==Options::loadHidden)
			lstrcat(szPath," -hide");
		regStart.SetStringValue("Transliterator",szPath);
		
	}
	else
		regStart.DeleteValue("Transliterator");
	regStart.Close();
}

void CTransliteratorDlg::SetOptions(bool bFirst/*=false*/)
{
	SetOptionsFont();

	// HotKeys
	if(!bFirst)
	{
		for(int i=0;i<Options::nHotKey;i++)
			UnregisterHotKey(m_hWnd,hkID+i);
	}

	for(int i=0;i<Options::nHotKey;i++)
	{
		if(g_Options.m_HotKey[i].GetHotKey())
			g_Options.m_HotKey[i].Register(m_hWnd,hkID+i);
	}
	
	// TopMost
	SetWindowPos(g_Options.m_bTopMost?HWND_TOPMOST:HWND_NOTOPMOST,
		0,0,0,0,SWP_NOSIZE|SWP_NOREPOSITION|SWP_NOMOVE);
	
	m_dlgTranslateFiles.UpdateCmbProfile();
	m_dlgTranslation.UpdateCmbProfile();
	if(!bFirst)
	{
		UpdateTrayIcon();
		UpdateTaskBar();
		m_dlgTranslation.UpdateTranslation();
	}
}

void CTransliteratorDlg::SetOptionsFont()
{
	// Fonts
	HFONT hFont;
	for(int i=0;i<2;i++)
	{
		hFont=::CreateFontIndirect(&g_Options.m_lfFont[i]);
		m_reTrnsRus[i].SetFont(hFont);
		::DeleteObject(hFont);
	}
	hFont=::CreateFontIndirect(&g_Options.m_lfFont[Options::fontTranslation]);
	m_dlgTranslation.m_reTranslation.SetFont(hFont);
	::DeleteObject(hFont);
}

void CTransliteratorDlg::UpdateCount()
{
	char str[2][30];
	SIZE size[2];

	HDC hDC=m_wndStatusBar.GetDC();
	
	for(int i=0;i<2;i++)
	{
		wsprintf(str[i],"%s - %d",m_strTrnsRus[i],m_reTrnsRus[i].GetWindowTextLength());
		::GetTextExtentPoint32(hDC,str[i],lstrlen(str[i]),&size[i]);
		m_wndStatusBar.SetPaneWidth(ID_COUNTTRNS+i,size[i].cx-10);
		m_wndStatusBar.SetPaneText(ID_COUNTTRNS+i,str[i]);
	}
	m_wndStatusBar.ReleaseDC(hDC);
}

void CTransliteratorDlg::UpdateTrayIcon()
{
	if(g_Options.m_bShowTrayIcon)
	{
		if(!m_bTrayIcon)
		{
			ShowTrayIcon();
			m_bTrayIcon=!m_bTrayIcon;
		}
	}
	else
	{
		if(m_bTrayIcon)
		{
			HideTrayIcon();
			m_bTrayIcon=!m_bTrayIcon;
		}
	}
	SetDefaultItem(IsWindowVisible()?ID_HIDE:ID_SHOW);
}

void CTransliteratorDlg::UpdateTaskBar()
{
    SetWindowLong(GWL_HWNDPARENT, (LONG)HWND_DESKTOP);
	if(!g_Options.m_bShowTaskBar)
		SetWindowLong(GWL_HWNDPARENT, (LONG)::GetDesktopWindow());
}

void CTransliteratorDlg::UpdateStatusBar()
{
	const char* pName = g_Language.GetCurProfile()->m_strName;
	HDC hDC=m_wndStatusBar.GetDC();
	SIZE size;
	::GetTextExtentPoint32(hDC,pName,lstrlen(pName),&size);
	m_wndStatusBar.ReleaseDC(hDC);
	m_wndStatusBar.SetPaneWidth(ID_PROFILE,size.cx);
	m_wndStatusBar.SetPaneText(ID_PROFILE,pName);
}

void CTransliteratorDlg::SaveWindowPlacement()
{
	WINDOWPLACEMENT wndpl;
	wndpl.length=sizeof(WINDOWPLACEMENT);
	GetWindowPlacement(&wndpl);
	if(wndpl.showCmd==SW_SHOWMINIMIZED||wndpl.showCmd==SW_MINIMIZE)
		wndpl.showCmd=SW_RESTORE;
	g_Options.m_wndState.nCmdShow=wndpl.showCmd;
}

void CTransliteratorDlg::UpdateTrnsRusString()
{
	for(int i=0;i<2;i++)
		::LoadString(_AtlBaseModule.GetResourceInstance(),
				IDS_TRANSLIT+i,m_strTrnsRus[i],nTrnsRus-1);
}

HWND CTransliteratorDlg::GetActiveWindowChild()
{
	DWORD dwThreadID = ::GetWindowThreadProcessId(::GetForegroundWindow(), NULL);
	GUITHREADINFO gti;

	ZeroMemory(&gti, sizeof(GUITHREADINFO));
	gti.cbSize = sizeof(GUITHREADINFO);
	::GetGUIThreadInfo(dwThreadID, &gti);
	return gti.hwndFocus;
}

void CTransliteratorDlg::HotKeyText(Translate::Direction dir,HWND hWndTransliterator,void (*pDo)(char*,Translate::Direction,int,HWND))
{
	HWND hWndTranslation = GetActiveWindowChild();
	if(!hWndTranslation)
		return;

	char szClass[64]={0};
	GetClassName(hWndTranslation,szClass,sizeof(szClass)/sizeof(char)-1);

	// Edit control
	// Prepare
	char szClassEdit[sizeof(szClass)/sizeof(char)]={0};
	lstrcpy(szClassEdit,szClass);
	::CharUpperBuff(szClassEdit, lstrlen(szClassEdit));
	// Check
	if((_tcsstr(szClassEdit, "EDIT")||
		_tcsstr(szClassEdit, "TEXT")))
	{
		CEdit wndTranslation=hWndTranslation;
		const unsigned nChar = (unsigned)(wndTranslation.GetWindowTextLength()+1)*LangString::nCountInit;

		NN::auto_array<char> aText(nChar);

		if(!aText.data())
			return;

		int nStart,nEnd;
		wndTranslation.GetSel(nStart,nEnd);

		if(nStart==nEnd||(!nStart&&nEnd==-1))
		{
			wndTranslation.SendMessage(WM_GETTEXT,nChar-1,(LPARAM)aText.data());
			
			(*pDo)(aText.data(),dir,nChar,hWndTransliterator);
						
			wndTranslation.SendMessage(WM_SETTEXT,0,(LPARAM)aText.data());
		}
		else
		{
			wndTranslation.SendMessage(WM_GETTEXT,nChar-1,(LPARAM)aText.data());
			for(int nItem=nStart;nItem<nEnd;nItem++)
				aText[nItem-nStart]=aText[nItem];
			aText[nItem-nStart]=0;
			
			(*pDo)(aText.data(),dir,nChar-(nEnd-nStart),hWndTransliterator);

			wndTranslation.ReplaceSel(aText.data(),TRUE);	
		}
	}
	// IE
	else
	if(!lstrcmp(szClass,"Internet Explorer_Server"))
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
				
				CComQIPtr<IHTMLInputTextElement> spInput=spElem;
				CComQIPtr<IHTMLTextAreaElement> spTA=spElem;
				
				CComBSTR strText;
				CComVariant v;
				
				if(spInput)
					spInput->get_value(&strText);
				else
				if(spTA)
					spTA->get_value(&strText);
				else
					spElem->get_innerText(&strText);

				if(strText)
				{
					const unsigned nChar=(strText.Length()+1)*LangString::nCountInit;
					
					{
						NN::auto_array<char> aTextA(nChar);
						if(!aTextA.data())
							return;
						::WideCharToMultiByte(CP,0,strText.m_str,nChar,aTextA.data(),nChar,0,0);
						(*pDo)(aTextA.data(),dir,nChar,hWndTransliterator);
						strText.Empty();
						strText.Append(aTextA.data());
					}

					if(spInput)
						spInput->put_value(strText);
					else
					if(spTA)
						spTA->put_value(strText);
					else
						spElem->put_innerText(strText);
				}
			}
		::FreeLibrary(hOleAccInstance);
		} // else Active Accessibility is not installed
	}
	// Window
	else
	{
		unsigned nChar = (unsigned)::SendMessage(hWndTranslation,WM_GETTEXTLENGTH,0,0)+1;
		nChar*=LangString::nCountInit;

		NN::auto_array<TCHAR> aText(nChar);
		if(!aText.data())
			return;

		::SendMessage(hWndTranslation,WM_GETTEXT,(WPARAM)(nChar-1),(LPARAM)aText.data());

		(*pDo)(aText.data(),dir,nChar,hWndTransliterator);

		::SendMessage(hWndTranslation,WM_SETTEXT,0,(LPARAM)aText.data());
	}
}

void CTransliteratorDlg::HotKeyTranslate(char* pText,Translate::Direction dir,int nChar,HWND)
{
	g_Language.Translate(pText,DefineDirection(dir,pText),nChar);
}

void CTransliteratorDlg::HotKeyCopy(char* pText,Translate::Direction dir,int /*nChar*/,HWND hWndTransliterator)
{
	::SendDlgItemMessage(hWndTransliterator,
		dir==Translate::dirTrnstoRus?IDC_TRNS:IDC_RUS,
		WM_SETTEXT,0,(LPARAM)pText);
}

void CTransliteratorDlg::HotKeyShow(bool bShow)
{
	if(bShow)
	{
		ShowWindow(g_Options.m_wndState.nCmdShow==SW_SHOWMINIMIZED||
			g_Options.m_wndState.nCmdShow==SW_MINIMIZE?
			SW_RESTORE:g_Options.m_wndState.nCmdShow);
	}
	else
	{
		SaveWindowPlacement();
		ShowWindow(SW_HIDE);
	}
	UpdateTrayIcon();
}

Translate::Direction CTransliteratorDlg::DefineDirection(Translate::Direction dir,LPCSTR strText)
{
	if(dir==Translate::dirAuto)
	{
		char str[2]={strText[0]};
		LangType t(str,str);
		unsigned u=g_Language.GetCurProfile()->m_map.Find(t,0,0);
		if(u!=(unsigned)-1)
			return Translate::dirTrnstoRus;
		u=g_Language.GetCurProfile()->m_map.Find(t,0,1);
		if(u!=(unsigned)-1)
			return Translate::dirRusToTrns;
		return g_Options.m_nAutoTranslation;
	}
	else
		return dir;
}

void CTransliteratorDlg::UpdateTranslation()
{
	Translate(::GetFocus()==m_reTrnsRus[Trns]?
			Translate::dirTrnstoRus:
			Translate::dirRusToTrns);
}

void CTransliteratorDlg::InitControls()
{
	NN::auto_sg_ref<BOOL> sg(g_Options.m_bTranslate,FALSE,g_Options.m_bTranslate);

	// Save Text
	NN::auto_array<wchar_t> aText[2];
	bool bCreated=m_reTrnsRus[0].m_hWnd&&m_reTrnsRus[1].m_hWnd;
	if(bCreated)
	{
		for(int i=0;i<2;i++)
		{
			// Text
			unsigned nChar=(unsigned)m_reTrnsRus[i].GetWindowTextLength()+1;
			aText[i].alloc(nChar);
			if(aText[i].data())
				m_reTrnsRus[i].GetTextEx((LPSTR)aText[i].data(),nChar*sizeof(wchar_t),GT_DEFAULT,1200);
			// Destroy
			m_reTrnsRus[i].DestroyWindow();
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
	
	if(!g_Options.m_bWrapText)
		dwStyle|=WS_HSCROLL|ES_AUTOHSCROLL;
	DWORD dwExStyle=0;

	RECT rect={0,0,1,1};
	for(int i=0;i<2;i++)
	{
		if(!m_reTrnsRus[i].Create(m_hWnd,rect,"",dwStyle,dwExStyle,IDC_TRNS+i))
		{
			ShowError(m_hWnd,_T("Cannot create text box"));
			return;
		}

		m_reTrnsRus[i].SendMessage(EM_SETLIMITTEXT,(WPARAM)MAX_SYMBOL,0);
		m_reTrnsRus[i].SetEventMask(ENM_CHANGE|ENM_KEYEVENTS|ENM_MOUSEEVENTS);
	}

	UpdateLayout();

	if(bCreated)
	{
		NN::auto_sg_ref<BOOL> sg(g_Options.m_bTranslate,FALSE,g_Options.m_bTranslate);
		for(int i=0;i<2;i++)
			if(aText[i].data())
				m_reTrnsRus[i].SetTextEx((LPCSTR)aText[i].data(),ST_DEFAULT,1200);
	}

	g_Language.SetCurProfile((Language::Profiles)g_Options.m_nCurProfile);
}

void CTransliteratorDlg::InitDialog()
{
	m_dlgTranslation.Create(m_hWnd);
	m_dlgTranslateFiles.Create(m_hWnd);
	m_dlgOptions.Create(m_hWnd);
	m_dlgAbout.Create(m_hWnd);
}

void CTransliteratorDlg::InitMessageLoop()
{
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->AddMessageFilter(this);
	pLoop->AddIdleHandler(this);
	
	pLoop->AddMessageFilter(&m_dlgOptions);
	pLoop->AddMessageFilter(&m_dlgTranslation);
	pLoop->AddMessageFilter(&m_dlgTranslateFiles);
	pLoop->AddMessageFilter(&m_dlgAbout);

	UIAddChildWindowContainer(m_hWnd);
}

LRESULT CTransliteratorDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// Icon
	DialogIcon_Init();
	// StatusBar
	m_wndStatusBar.Create(m_hWnd);
	m_hWndStatusBar = m_wndStatusBar;
	int panes[] = { ID_COUNTTRNS, ID_COUNTRUS, ID_DEFAULT_PANE, ID_PROFILE };
	m_wndStatusBar.SetPanes(panes, sizeof(panes)/sizeof(panes[0]), false);
	
	HDC hDC=m_wndStatusBar.GetDC();
	SetTextCharacterExtra(hDC,0);
	m_wndStatusBar.ReleaseDC(hDC);

	UpdateStatusBar();
	// Language
	DialogLang_Init();
	// Controls
	InitControls();
	// Resize
	DlgResize_Init(false,true);

	m_hAccel=::LoadAccelerators(ATL::_AtlBaseModule.GetResourceInstance(),MAKEINTRESOURCE(IDR_TRANSLITERATOR));

	InitDialog();

	InitTrayIcon(IDR_TRANSLITERATOR,
		::LoadIcon(ATL::_AtlBaseModule.GetResourceInstance(),MAKEINTRESOURCE(IDR_TRANSLITERATOR)),
		IDR_TRAYICON);

	{
		NN::auto_sg_ref<BOOL> sg(g_Options.m_bShowTrayIcon,FALSE,g_Options.m_bShowTrayIcon);
		SetOptions(true);
	}

	UpdateTrnsRusString();
	UpdateCount();
	m_dlgTranslation.UpdateCurProfile();

	// Set Text
	if(m_aText[Trns].data()||m_aText[Rus].data())
	{
		NN::auto_sg_ref<BOOL> sg(g_Options.m_bTranslate,FALSE,g_Options.m_bTranslate);
		for(int i=0;i<2;i++)
		{
			if(m_aText[i].data())
			{
				m_reTrnsRus[i].SetTextEx((LPCSTR)m_aText[i].data(),ST_DEFAULT,1200);
				m_aText[i].free();
			}
		}
	}

	InitMessageLoop();

	return TRUE;
}

LRESULT CTransliteratorDlg::OnSysCommand(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
{
	bHandled=FALSE;
	WORD wMsg=LOWORD(wParam);

	if(wMsg==SC_CLOSE)
		CloseDialog();
	else
	if(wMsg==SC_MINIMIZE&&g_Options.m_bShowTrayIcon)
	{
		bHandled=TRUE;
		ShowWindow(SW_MINIMIZE);
		HotKeyShow(false);
	}
	
	return 0;
}

LRESULT CTransliteratorDlg::OnHotKey(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	switch(wParam-hkID)
	{
		case Options::hkTrnstoRus:
			HotKeyText(Translate::dirTrnstoRus,NULL,HotKeyTranslate);
			break;
		case Options::hkRusToTrns:
			HotKeyText(Translate::dirRusToTrns,NULL,HotKeyTranslate);
			break;
		case Options::hkAuto:
			HotKeyText(Translate::dirAuto,m_hWnd,HotKeyTranslate);
			break;
		case Options::hkShowHide:
			HotKeyShow(IsWindowVisible()?false:true);
			break;
		case Options::hkCopyTrns:
			HotKeyText(Translate::dirTrnstoRus,m_hWnd,HotKeyCopy);
			break;
		case Options::hkCopyRus:
			HotKeyText(Translate::dirRusToTrns,m_hWnd,HotKeyCopy);
			break;
	}
	return 0;
}

LRESULT CTransliteratorDlg::OnQueryEndSession(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	SaveSettings();
	return TRUE;
}

LRESULT CTransliteratorDlg::OnApply(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
{
	if(lParam)
		SetOptions();
	if(wParam)
		UpdateTranslation();
	return 0;
}

LRESULT CTransliteratorDlg::OnAppExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CloseDialog();
	return 0;
}

LRESULT CTransliteratorDlg::OnEditCommands(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CRichEditCtrl re=::GetFocus();
	
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

LRESULT CTransliteratorDlg::OnEditIgnore(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CRichEditCtrl re=::GetFocus();

	bool bInsert=wID==ID_EDIT_IGNORE_INSERT;
	
	// Get Text
	unsigned nChar=re.GetWindowTextLength()*LangProfile::nIgnore*2+1;
	NN::auto_array<wchar_t> aText(nChar);
	long nStart,nEnd;
	re.GetSel(nStart,nEnd);

	re.GetTextEx((LPSTR)aText.data(),nChar*sizeof(wchar_t),GT_DEFAULT,1200);
	// Insert/Remove
	if(nStart==nEnd)
	{
		if(bInsert)
		{
			g_Language.SetIgnore(aText.data(),nChar-1,re==m_reTrnsRus[Trns],bInsert);
		
			re.SetTextEx((LPCSTR)aText.data(),ST_DEFAULT,1200);

			int nText=lstrlenW(aText.data());
			re.SetSel(nText,nText);
		}
		else
		{
			g_Language.SetIgnore(aText.data(),nChar-1,re==m_reTrnsRus[Trns],bInsert);
			re.SetTextEx((LPCSTR)aText.data(),ST_DEFAULT,1200);
			re.SetSel(nStart,nStart);
		}
	}
	// Ignore
	else
	{
		if(!nStart&&nEnd==-1||
			!nStart&&nEnd==lstrlenW(aText.data())) // All
		{
			g_Language.Ignore(aText.data(),nChar-1,re==m_reTrnsRus[Trns],bInsert);
			re.SetTextEx((LPCSTR)aText.data(),ST_DEFAULT,1200);
		}
		else // Selection
		{
			for(long nItem=nStart;nItem<nEnd;nItem++)
				aText[nItem-nStart]=aText[nItem];
			aText[nItem-nStart]=0;

			g_Language.Ignore(aText.data(),nChar-1,re==m_reTrnsRus[Trns],bInsert);
			NN::auto_array<char> aTextA(nChar);
			::WideCharToMultiByte(CP,0,aText.data(),nChar,aTextA.data(),nChar,0,0);
			re.ReplaceSel(aTextA.data());
		}
	}

	return 0;
}

LRESULT CTransliteratorDlg::OnEditCopy(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	NN::auto_sg_ref<BOOL> sg(g_Options.m_bTranslate,FALSE);
	
	bool b1= wID==ID_EDIT_COPY_TRNSTORUS;

	CRichEditCtrl& reFrom=m_reTrnsRus[!b1];
	CRichEditCtrl& reTo=m_reTrnsRus[b1];

	int nLen=reFrom.GetTextLength()+1;
	NN::auto_array<wchar_t> aText(nLen);
	reFrom.GetTextEx((LPSTR)aText.data(),nLen,GT_DEFAULT,CP);
	reTo.SetTextEx((LPCSTR)aText.data(),ST_DEFAULT,CP);

	return 0;
}

LRESULT CTransliteratorDlg::OnProfile(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	g_Options.m_nCurProfile=wID-ID_PROFILE1;
	g_Language.SetCurProfile((Language::Profiles)g_Options.m_nCurProfile);
	UpdateTranslation();
	UpdateStatusBar();
	m_dlgTranslation.UpdateCurProfile();

	return 0;
}

LRESULT CTransliteratorDlg::OnViewLanguage(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	switch(wID)
	{
		case ID_VIEW_LANGUAGE_ENGLISH:
			g_LangID=s_langEnglish;
			break;
		case ID_VIEW_LANGUAGE_RUSSIAN:
			g_LangID=s_langRussian;
			break;
		case ID_VIEW_LANGUAGE_TRANSLIT:
			g_LangID=s_langTranslit;
			break;
		default:
			return 0;
	}
	
	UpdateLanguage();

	m_dlgTranslation.UpdateLanguage();
	m_dlgTranslateFiles.UpdateLanguage();
	m_dlgOptions.UpdateLanguage();
	m_dlgAbout.UpdateLanguage();

	UpdateTrnsRusString();
	UpdateCount();

	return 0;
}

LRESULT CTransliteratorDlg::OnViewControls(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(wID==ID_VIEW_CONTROLS_WRAPTEXT)
		g_Options.m_bWrapText=!g_Options.m_bWrapText;
	else
		g_Options.m_bScrollText=!g_Options.m_bScrollText;

	InitControls();
	SetOptionsFont();
	
	return 0;
}

LRESULT CTransliteratorDlg::OnViewControlsAutoTransliteration(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	g_Options.m_bTranslate=!g_Options.m_bTranslate;
	return 0;
}

LRESULT CTransliteratorDlg::OnViewControlsAutoIgnore(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	g_Options.m_bIgnore=!g_Options.m_bIgnore;
	UpdateTranslation();
	return 0;
}

LRESULT CTransliteratorDlg::OnToolsTranslation(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	m_dlgTranslation.ShowHide();
	return 0;
}

LRESULT CTransliteratorDlg::OnToolsTranslateFiles(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	m_dlgTranslateFiles.ShowHide();
	return 0;
}

LRESULT CTransliteratorDlg::OnToolsOptions(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	m_dlgOptions.ShowHide();
	return 0;
}

LRESULT CTransliteratorDlg::OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	m_dlgAbout.ShowHide();
	return 0;
}

LRESULT CTransliteratorDlg::OnShowHide(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	HotKeyShow(wID==ID_SHOW);
	UpdateTrayIcon();
	if(wID==ID_SHOW)
		UpdateTaskBar();
	return 0;
}

LRESULT CTransliteratorDlg::OnEnChangeTrnsRus(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	static bool bTranslate=false;
	if(g_Options.m_bTranslate&&!bTranslate)
	{
		NN::auto_sg_ref_t<bool,true,false> sg(bTranslate);
		Translate(wID==IDC_TRNS?Translate::dirTrnstoRus:Translate::dirRusToTrns);
		
		bool b1= wID==IDC_TRNS;

		CRichEditCtrl reFrom=m_reTrnsRus[!b1];
		CRichEditCtrl reTo=m_reTrnsRus[b1];

		if(g_Options.m_bScrollText)
			reTo.LineScroll(reFrom.GetFirstVisibleLine());
	}
	UpdateCount();
	return 0;
}

LRESULT CTransliteratorDlg::OnEnMsgFilterTrnsRus(int /*code*/, NMHDR* pnmhdr, BOOL& /*bHandled*/)
{
	MSGFILTER *pMsgFilter=(MSGFILTER *)pnmhdr;
	if(pMsgFilter->msg==WM_RBUTTONDOWN)
	{
		::SetFocus(pMsgFilter->nmhdr.hwndFrom);
		OnIdle();
		POINT pt;
		::GetCursorPos(&pt);
		HMENU hMenu=::LoadMenu(_AtlBaseModule.GetResourceInstance(),
				MAKEINTRESOURCE(IDR_EDIT));
		hMenu=::GetSubMenu(hMenu,0);
		::TrackPopupMenu(hMenu,TPM_LEFTALIGN|TPM_LEFTBUTTON|
			TPM_RIGHTBUTTON,pt.x,pt.y,0,m_hWnd,NULL);
	}
	return 0;
}

LRESULT CTransliteratorDlg::OnClickStatusBar(int /*code*/, NMHDR* pnmhdr, BOOL& /*bHandled*/)
{
	if(pnmhdr->code==NM_RCLICK)
	{
		OnIdle();
		POINT pt;
		::GetCursorPos(&pt);

		HMENU hMenu=::LoadMenu(_AtlBaseModule.GetResourceInstance(),
			MAKEINTRESOURCE(IDR_PROFILE));
		hMenu=::GetSubMenu(hMenu,0);
		::SetMenuDefaultItem(hMenu,IsWindowVisible()?ID_HIDE:ID_SHOW,FALSE);
		::TrackPopupMenu(hMenu,TPM_LEFTALIGN|TPM_LEFTBUTTON|
			TPM_RIGHTBUTTON,pt.x,pt.y,0,m_hWnd,NULL);
	}
	else
	if(pnmhdr->code==NM_DBLCLK)
	{
		if(++g_Options.m_nCurProfile==Language::nProfiles)
			g_Options.m_nCurProfile=0;
		g_Language.SetCurProfile((Language::Profiles)g_Options.m_nCurProfile);
		UpdateTranslation();
		UpdateStatusBar();
	}

	return 0;
}
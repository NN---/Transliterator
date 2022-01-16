#include "stdafx.h"

#include "resource.h"
#include "error.h"
#include "global.h"
#include "msg.h"
#include "makedirection.h"
#include <mshtml.h>
#include "settings.h"

#include "transliteratordlg.h"

BOOL TransliteratorDlg::OnIdle()
{
	BOOL bSelection,bText;
	WTL::CRichEditCtrl re = ::GetFocus();

	if(re == m_areLang[0]||
		re == m_areLang[1])
	{
		bSelection = re.GetSelectionType() != SEL_EMPTY;
		bText = re.GetTextLength()?TRUE:FALSE;
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
		for(int i = ID_EDIT_CLEAR;i <= ID_EDIT_REDO; ++i)
			UIEnable(i,FALSE);
		UIEnable(ID_EDIT_IGNORE_INSERT,FALSE);
		UIEnable(ID_EDIT_IGNORE_REMOVE,FALSE);
	}

	{
		LangStringT astrDir[2];
		MakeDirection::MakeT(astrDir);
		for(size_t i=0; i<2; ++i)
			UISetText(ID_EDIT_COPY_LANGTOPTOLANGBOTTOM+i,astrDir[i].c_str());
	}

	UISetCheck(ID_TOOLS_PROFILEDETAILS,m_dlgProfileDetails.IsWindowVisible());
	UISetCheck(ID_TOOLS_TRANSLATEFILES,m_dlgTranslateFiles.IsWindowVisible());
	UISetCheck(ID_TOOLS_OPTIONS,m_dlgOptions.IsWindowVisible());
	
	UISetCheck(ID_TOOLS_ACTION_TRANSLITERATION,g_Options.m_bTranslate);
	UISetCheck(ID_TOOLS_ACTION_IGNORE,g_Options.m_bIgnore);
	UISetCheck(ID_TOOLS_ACTION_IGNORETEXT,g_Options.m_bIgnoreText);
	UISetCheck(ID_TOOLS_ACTION_COPYIGNORE,g_Options.m_bCopyIgnore);

	UISetCheck(ID_APP_ABOUT,m_dlgAbout.IsWindowVisible());

	// Tray Menu
	BOOL bVisible = IsWindowVisible();
	UIEnable(ID_SHOW,!bVisible);
	UIEnable(ID_HIDE,bVisible);

	// Profile
	static const TCHAR szCtrl[] = _T("\tCtrl+");
	LangStringT strText;
	strText.reserve(40);
	for(unsigned i = 0;i<Language::nProfiles; ++i)
	{
		strText = g_Storage.m_astrProfile[i];
		strText+= szCtrl;
		if(i == Language::nProfiles-1)
			strText+= _T('0');
		else
			strText+= (TCHAR)i+_T('1');

		UISetText(ID_PROFILE1+i,strText.c_str());
		UISetCheck(ID_PROFILE1+i,FALSE);
	}
	UISetCheck(ID_PROFILE1+g_Options.m_nCurProfile,TRUE);

	return FALSE;
}

void TransliteratorDlg::DlgResize_UpdateLayout(int cxWidth, int cyHeight)
{
	WTL::CDialogResize<TransliteratorDlg>::DlgResize_UpdateLayout(cxWidth,cyHeight);
	UpdateStatusBar();
	UpdateLayout();
}

int TransliteratorDlg::LoadStringForMenuItem(UINT uID, LPTSTR szBuff, int cchBuff)
{
	if(uID >= ID_PROFILE1&&uID <= ID_PROFILE10)
	{
		LangStringT& strProfile = g_Storage.m_astrProfile[uID-ID_PROFILE1];
		_tcsncpy(szBuff,strProfile.c_str(),(size_t)cchBuff);
		return std::min((int)strProfile.length(),cchBuff);
	}
	else
		return NN::DialogStatusBarMenu<TransliteratorDlg>::LoadStringForMenuItem(uID,szBuff,cchBuff);
}

bool TransliteratorDlg::Show()
{
	if(!Create(::GetDesktopWindow()))
		return false;
	
	// Command Line
	int nCmdShow = g_Options.m_wndpl.showCmd;
	if(__argc>1)
	{
		if(!_tcscmp(__targv[1],_T("-min")))
			nCmdShow = SW_MINIMIZE;
		else
		if(!_tcscmp(__targv[1],_T("-max")))
			nCmdShow = SW_MAXIMIZE;
		else
		if(!_tcscmp(__targv[1],_T("-hide")))
			nCmdShow = SW_HIDE;
	}

	static const RECT zeroRECT = {};
	if(!memcmp(&g_Options.m_wndpl.rcNormalPosition, &zeroRECT, sizeof(RECT)))
		CenterWindow();
	else
		MoveWindow(&g_Options.m_wndpl.rcNormalPosition);
	ShowWindow(nCmdShow);
	
	m_bShown = (nCmdShow == SW_HIDE||
		((nCmdShow == SW_MINIMIZE||nCmdShow == SW_SHOWMINIMIZED)&&
			g_Options.m_bTrayIconShow))?false:true;
	if(!m_bShown)
		ShowWindow(SW_HIDE);
	
	UpdateTaskBar();
	UpdateTrayIcon();

	return true;
}

void TransliteratorDlg::Close()
{
	if(g_Options.m_bSaveText)
	{
		try
		{
			for(size_t i=0; i<2; ++i)
			{
				size_t nLength = (size_t)m_areLang[i].GetTextLength()+1;
				g_Text[i].resize(nLength);
				m_areLang[i].GetTextEx((LPTSTR)&g_Text[i][0],
					nLength*sizeof(wchar_t),GT_DEFAULT,1200);
			}
		}
		catch(...)
		{
			for(size_t i=0; i<2; ++i)
				g_Text[i].clear();
		}
	}
	else
	{
		for(size_t i=0; i<2; ++i)
			g_Text[i].clear();
	}
	
	SaveWindowPlacement();
	
	m_dlgProfileDetails.DestroyWindow();
	m_dlgTranslateFiles.DestroyWindow();
	m_dlgAbout.DestroyWindow();
	m_dlgOptions.DestroyWindow();
	DestroyWindow();
	::PostQuitMessage(0);
}

void TransliteratorDlg::SetOptions()
{
	if(g_UpdateOptions.m_bControls)
	{
		InitControls();
		SetOptionsFont();
	}
	else
		if(g_UpdateOptions.m_bFont)
			SetOptionsFont();
		
	if(g_UpdateOptions.m_abProfile[g_Language.GetCurProfileNum()])
		UpdateTranslation();
		
	UpdateTaskBar();
	
	UpdateTrayIcon();

	UpdateStatusBar();
	
	UpdateCaption();

	// HotKeys
	if(g_UpdateOptions.m_bHotKey)
	{
		for(size_t i=0; i<Options::nHotKey; ++i)
			::UnregisterHotKey(m_hWnd, hkID+i);
	
		for(size_t i=0; i<Options::nHotKey; ++i)
		{
			if(g_Options.m_HotKey[i].GetHotKey())
				g_Options.m_HotKey[i].Register(m_hWnd, hkID+i);
		}
	}

	UpdatePlacement();

	if(g_UpdateOptions.m_bLanguage)
		UpdateLanguage();

	memset(&g_UpdateOptions, 0, sizeof(g_UpdateOptions));
}

void TransliteratorDlg::SetOptionsFont()
{
	// Fonts
	HFONT hFont;
	for(size_t i=0; i<2; ++i)
	{
		hFont = ::CreateFontIndirect(&g_Options.m_alfFont[i]);
		m_areLang[i].SetFont(hFont);
		::DeleteObject(hFont);
	}
	hFont = ::CreateFontIndirect(&g_Options.m_alfFont[Options::fontDetails]);
	m_dlgProfileDetails.m_reDetails.SetFont(hFont);
	::DeleteObject(hFont);
}

void TransliteratorDlg::SaveWindowPlacement()
{
	g_Options.m_wndpl.length = sizeof(WINDOWPLACEMENT);
	GetWindowPlacement(&g_Options.m_wndpl);
}

void TransliteratorDlg::ShowHide(bool bShow)
{
	if(bShow)
	{
		ShowWindow(
			g_Options.m_wndpl.showCmd == SW_SHOWMINIMIZED||
			g_Options.m_wndpl.showCmd == SW_MINIMIZE?
				SW_RESTORE:g_Options.m_wndpl.showCmd);
	}
	else
	{
		SaveWindowPlacement();
		ShowWindow(SW_HIDE);
	}
	UpdateTrayIcon();
}

void TransliteratorDlg::Translate(Translate::Direction dir)
{
	bool bfirst =  dir == Translate::dirToptoBottom;

	WTL::CRichEditCtrl reFrom = m_areLang[!bfirst];
	WTL::CRichEditCtrl reTo = m_areLang[bfirst];

	const size_t nCharIn = (size_t)reFrom.GetWindowTextLength()+1;
	const size_t nCharOut = 
		Language::CountOutTranslate(
			nCharIn,
			dir,
			g_Options.m_bIgnore,
			g_Language.GetCurProfile());

	try
	{
		std::vector<wchar_t> aTextIn(nCharIn);
		std::vector<wchar_t> aTextOut(nCharOut);
	
		reFrom.GetTextEx((LPTSTR)&aTextIn[0],
			nCharIn*sizeof(wchar_t), GT_DEFAULT, 1200);
		g_Language.Translate(&aTextIn[0], &aTextOut[0], dir, 0);
		
		{
			NN::sg<BOOL> sg(g_Options.m_bTranslate,FALSE,g_Options.m_bTranslate);
			reTo.SetTextEx((const TCHAR*)&aTextOut[0],ST_DEFAULT,1200);
		}
	}
	catch(...)
	{
	}
}

// TranslateWindow
void TransliteratorDlg::TranslateWindow(Translate::Direction dir)
{
	HWND hWndTranslation = NN::GetActiveWindowChild();
	if(!hWndTranslation)
		return;

	TCHAR szClass[64] = {};
	::GetClassName(hWndTranslation, szClass, NN_ARRAY_LENGTH(szClass)-1);

	TCHAR szClassEdit[NN_ARRAY_LENGTH(szClass)] = {};
	_tcscpy(szClassEdit,szClass);
	::CharUpperBuff(szClassEdit, _tcslen(szClassEdit));
	// Edit control
	if(_tcsstr(szClassEdit, _T("EDIT"))||
		_tcsstr(szClassEdit, _T("TEXT")))
		TranslateWindow_Edit(hWndTranslation,dir);
	// IE
	else
	if(!_tcscmp(szClass,_T("Internet Explorer_Server")))
		TranslateWindow_IE(hWndTranslation,dir);
	// Window
	else
		TranslateWindow_Window(hWndTranslation,dir);
}

void TransliteratorDlg::TranslateWindow_Edit(HWND hWndTranslation,Translate::Direction dir)
{
	const size_t nCharIn = (size_t)::SendMessage(hWndTranslation,WM_GETTEXTLENGTH,0,0)+1;
	try
	{
		std::vector<TCHAR> aTextIn(nCharIn);
	
		DWORD nStart,nEnd;
		::SendMessage(hWndTranslation,EM_GETSEL,(WPARAM)&nStart,(LPARAM)&nEnd);

		if(nStart == nEnd||(!nStart&&nEnd == (DWORD)-1))
		{
			::SendMessage(hWndTranslation,WM_GETTEXT,nCharIn,(LPARAM)&aTextIn[0]);
			
			dir = DefineDirection(dir,&aTextIn[0]);
			const size_t nCharOut = 
				Language::CountOutTranslate(
					nCharIn,
					dir,
					g_Options.m_bIgnore,
					g_Language.GetCurProfile());

			std::vector<wchar_t> aTextOut(nCharOut);
			g_Language.Translate(
				NN::CharAWT<const wchar_t>(&aTextIn[0]),
				&aTextOut[0],
				dir,0);
									
			::SendMessage(hWndTranslation,WM_SETTEXT,0,
				(LPARAM)(const TCHAR*)NN::CharAWT<const TCHAR>(&aTextOut[0]));
		}
		else
		{
			::SendMessage(hWndTranslation,WM_GETTEXT,nCharIn,(LPARAM)&aTextIn[0]);
			
			std::copy(&aTextIn[nStart],&aTextIn[nEnd+1],&aTextIn[0]);
			aTextIn[nEnd-nStart] = 0;
		
			const size_t nCharOut = 
				Language::CountOutTranslate(
					nCharIn,
					dir,
					g_Options.m_bIgnore,
					g_Language.GetCurProfile());

			std::vector<wchar_t> aTextOut(nCharOut);
			g_Language.Translate(
				NN::CharAWT<const wchar_t>(&aTextIn[0]),
				&aTextOut[0],
				dir,0);

			::SendMessage(hWndTranslation,EM_REPLACESEL,TRUE,
				(LPARAM)(const TCHAR*)NN::CharAWT<const TCHAR>(&aTextOut[0]));	
		}
	}
	catch(...)
	{
	}
}

void TransliteratorDlg::TranslateWindow_IE(HWND hWndTranslation,Translate::Direction dir)
{
	static bool binit = false;
	HINSTANCE hOleAccInstance;
	if(!binit)
		hOleAccInstance = ::LoadLibrary(_T("OLEACC.DLL"));
	else
		hOleAccInstance = ::GetModuleHandle(_T("OLEACC.DLL"));
	if(!hOleAccInstance)
		return;
	
	LRESULT lRes;
	
	UINT nMsg = ::RegisterWindowMessage(_T("WM_HTML_GETOBJECT"));
	::SendMessageTimeout(hWndTranslation, nMsg, 0L, 0L, SMTO_ABORTIFHUNG, 1000, (DWORD*)&lRes);

	LPFNOBJECTFROMLRESULT pfObjectFromLresult = (LPFNOBJECTFROMLRESULT)::GetProcAddress(hOleAccInstance, "ObjectFromLresult");
	if(!pfObjectFromLresult)
		return;

	ATL::CComPtr<IHTMLDocument2> spDoc;
	if(FAILED((*pfObjectFromLresult)(lRes, IID_IHTMLDocument, 0, (void**)&spDoc)))
		return;

	ATL::CComPtr<IDispatch> spDisp;
	ATL::CComQIPtr<IHTMLWindow2> spWin;
	spDoc->get_Script(&spDisp);
	spWin = spDisp;
	spWin->get_document(&spDoc.p);
	ATL::CComQIPtr<IHTMLElement> spElem;
	spDoc->get_activeElement(&spElem.p);
				
	ATL::CComQIPtr<IHTMLInputTextElement> spInput = spElem;
	ATL::CComQIPtr<IHTMLTextAreaElement> spTA = spElem;
	
	ATL::CComBSTR strText;
	ATL::CComVariant v;
				
	if(spInput)
		spInput->get_value(&strText);
	else
	if(spTA)
		spTA->get_value(&strText);
	else
		spElem->get_innerText(&strText);

	dir; // Unused variable
	if(strText)
	{
		dir = DefineDirection(dir,strText);
		try
		{
			const size_t nCharOut = 
				Language::CountOutTranslate(
					strText.Length(),
					dir,
					g_Options.m_bIgnore,
					g_Language.GetCurProfile());

			std::vector<wchar_t> aTextOut(nCharOut);
			g_Language.Translate(strText,&aTextOut[0],dir,0);
			strText = &aTextOut[0];
		}
		catch(...)
		{
			return;
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

void TransliteratorDlg::TranslateWindow_Window(HWND hWndTranslation,Translate::Direction dir)
{
	const size_t nCharIn = (size_t)::SendMessage(hWndTranslation,WM_GETTEXTLENGTH,0,0)+1;
		
	try
	{
		std::vector<TCHAR> aTextIn(nCharIn);
		::SendMessage(hWndTranslation,WM_GETTEXT,(WPARAM)(nCharIn),(LPARAM)&aTextIn[0]);
		
		dir = DefineDirection(dir,&aTextIn[0]);
		std::vector<LangChar> aTextOut(
			Language::CountOutTranslate(
				nCharIn,
				dir,
				g_Options.m_bIgnore,
				g_Language.GetCurProfile()));

		g_Language.Translate(NN::CharAWT<const wchar_t>(&aTextIn[0]),&aTextOut[0],dir,0);
		
		::SendMessage(
			hWndTranslation,
			WM_SETTEXT,
			0,
			(LPARAM)(const TCHAR*)NN::CharAWT<const TCHAR>(&aTextOut[0]));
	}
	catch(...)
	{
	}
}

Translate::Direction TransliteratorDlg::DefineDirection(Translate::Direction dir, const LangChar* strText)
{
	if(dir == Translate::dirAuto)
	{
		const LangChar str[2] = {strText[0]};
				
		// Find
		const LangArray& aTranslation = g_Language.GetCurProfile()->m_aTranslation;

		for(LangArray::const_iterator it = aTranslation.begin();
			it != aTranslation.end(); ++it)
			if(it->get<LangPos::Top>() == str)
				return Translate::dirToptoBottom;

		for(LangArray::const_iterator it = aTranslation.begin();
			it != aTranslation.end(); ++it)
			if(it->get<LangPos::Bottom>() == str)
				return Translate::dirBottomtoTop;
			
		return g_Options.m_nAutoTransliteration;
	}
	else
		return dir;
}

Translate::Direction TransliteratorDlg::DefineDirection(Translate::Direction dir, const LangCharA* strText)
{
	return DefineDirection(dir,NN::CharAWT<const LangChar>(strText));
}

void TransliteratorDlg::UpdateLayout()
{
	for(size_t i=0; i<2; ++i)
	{
		RECT rect;
		::GetWindowRect(GetDlgItem(IDC_GRPLANGTOP+i),&rect);
		ScreenToClient(&rect);
		rect.left+= size_delta_left;
		rect.right-= size_delta_right;
		rect.top+= size_delta_top;
		rect.bottom-= size_delta_bottom;
		::MoveWindow(
			GetDlgItem(IDC_RELANGTOP +i),
			rect.left,
			rect.top,
			rect.right-rect.left,
			rect.bottom-rect.top,
			TRUE);
	}
}

void TransliteratorDlg::UpdateStatusBar()
{
	HDC hDC = m_wndStatusBar.GetDC();
	::SetTextCharacterExtra(hDC,0);

	// Count	
	for(size_t i=0; i<2; ++i)
	{
		LangStringT str = g_Language.GetCurProfile()->m_astrLang[i];

		if(g_Options.m_bStatusBarCount)
		{
			str+= _T(" - ");
		
			TCHAR strLength[NN::digits_number<int>::value+1];
			_itot(m_areLang[i].GetWindowTextLength(),strLength,10);
			str+= strLength;
		}

		SIZE size;
		::GetTextExtentPoint32(hDC,str.c_str(),str.length(),&size);
		m_wndStatusBar.SetPaneWidth(ID_COUNTLANGTOP+i,size.cx);
		m_wndStatusBar.SetPaneText(ID_COUNTLANGTOP+i,str.c_str());
	}

	// Profile
	const LangStringT& strProfile = g_Storage.m_astrProfile[g_Language.GetCurProfileNum()];
	
	SIZE size;
	::GetTextExtentPoint32(hDC,strProfile.c_str(),strProfile.length(),&size);
	m_wndStatusBar.ReleaseDC(hDC);
	m_wndStatusBar.SetPaneWidth(ID_PROFILE,size.cx);
	m_wndStatusBar.SetPaneText(ID_PROFILE,strProfile.c_str());

	m_wndStatusBar.ReleaseDC(hDC);
}

void TransliteratorDlg::UpdateCaption()
{
	LangStringT strCaption;

	const LangStringT& strLang = g_Language.GetCurProfile()->m_astrLang[0];

	strCaption.reserve(
		g_Storage.m_astrProfile[g_Language.GetCurProfileNum()].length()+
		strLang.length()+
		strLang.length()+10);
	NN::WndLoadString(IDR_TRANSLITERATOR,strCaption);
	
	if(g_Options.m_bCaptionProfile)
	{
		strCaption+= _T(" - ");
		strCaption+= g_Storage.m_astrProfile[g_Language.GetCurProfileNum()];
	}
	
	if(g_Options.m_bCaptionCount)
	{
		strCaption+= _T(" - ");
		for(size_t i=0; i<2; ++i)
		{
			strCaption+= g_Language.GetCurProfile()->m_astrLang[i];
			strCaption+= _T(" - ");

			TCHAR strLength[10];
			_itot(m_areLang[i].GetWindowTextLength(),strLength,10);
			strCaption+= strLength;
			if(i<1)
				strCaption+= _T(" , ");
		}
	}
	
	SetWindowText(strCaption.c_str());
}

void TransliteratorDlg::UpdateTranslation()
{
	Translate(::GetFocus() == m_areLang[0]?
			Translate::dirToptoBottom:
			Translate::dirBottomtoTop);
}

void TransliteratorDlg::UpdateTrayIcon()
{
	if(g_Options.m_bTrayIconShow)
	{
		if(!m_bTrayIcon)
		{
			ShowTrayIcon();
			m_bTrayIcon = !m_bTrayIcon;
		}
	}
	else
	{
		if(m_bTrayIcon)
		{
			HideTrayIcon();
			m_bTrayIcon = !m_bTrayIcon;
		}
	}
	SetDefaultItem(IsWindowVisible()?ID_HIDE:ID_SHOW);
}

void TransliteratorDlg::UpdateTaskBar()
{
    SetWindowLong(GWL_HWNDPARENT, (LONG)HWND_DESKTOP);
	if(!g_Options.m_bTaskBarShow)
		SetWindowLong(GWL_HWNDPARENT, (LONG)::GetDesktopWindow());
}

void TransliteratorDlg::UpdatePlacement()
{
	SetWindowPos(
			g_Options.m_nPlacement == Options::placementOnTop?HWND_TOPMOST:
			g_Options.m_nPlacement == Options::placementOnBottom?HWND_BOTTOM:
			HWND_NOTOPMOST,
			0,0,0,0,SWP_NOSIZE|SWP_NOREPOSITION|SWP_NOMOVE);
}

void TransliteratorDlg::UpdateLang()
{
	for(size_t i=0; i<2; ++i)
		SetDlgItemText(IDC_GRPLANGTOP+i,
			g_Language.GetCurProfile()->m_astrLang[i].c_str());
}

void TransliteratorDlg::DialogLang_LanguageChanged()
{
	m_dlgProfileDetails.UpdateLanguage();
	m_dlgTranslateFiles.UpdateLanguage();
	m_dlgOptions.UpdateLanguage();
	m_dlgAbout.UpdateLanguage();

	UpdateCaption();
	UpdateStatusBar();
	UpdateLang();
}

void TransliteratorDlg::InitControls()
{
	NN::sg<BOOL> sg(g_Options.m_bTranslate,FALSE,g_Options.m_bTranslate);

	// Save Text
	std::vector<wchar_t> aText[2];
	bool bCreated = m_areLang[0]&&m_areLang[1];
	try
	{
		for(size_t i=0; i<2; ++i)
		{
			if(m_areLang[i])
			{
				// Text
				size_t nChar = (size_t)m_areLang[i].GetWindowTextLength()+1;
				aText[i].resize(nChar);
			
				m_areLang[i].GetTextEx((LPTSTR)&aText[i][0],
					nChar*sizeof(wchar_t),GT_DEFAULT,1200);
				
				// Destroy
				m_areLang[i].DestroyWindow();
			}
		}
	}
	catch(...)
	{
		for(size_t i=0; i<2; ++i)
			aText[i].clear();
	}
	
	// Create
	DWORD dwStyle = 
		WS_TABSTOP     |
		WS_BORDER      |
		WS_CHILD       |
		WS_VISIBLE     |
		WS_VSCROLL     |
		ES_WANTRETURN  |
		ES_MULTILINE   |
		ES_NOHIDESEL   |
		ES_AUTOVSCROLL;
	
	if(!g_Options.m_bWrapText)
		dwStyle|= WS_HSCROLL | ES_AUTOHSCROLL;
	DWORD dwExStyle = 0;

	static RECT rect = {0,0,1,1};
	for(size_t i=0; i<2; ++i)
	{
		if(!m_areLang[i].Create(m_hWnd, rect, _T(""), dwStyle, dwExStyle, IDC_RELANGTOP+i))
		{
			ShowError(m_hWnd, _T("Cannot create text box"));
			return;
		}

		m_areLang[i].SetEventMask(ENM_CHANGE|ENM_MOUSEEVENTS);
	}

	UpdateLayout();
	if(!bCreated)
	{
		if(g_Options.m_bScrollText)
			m_areLang[1].LineScroll(m_areLang[0].GetFirstVisibleLine());
	}

	for(size_t i=0; i<2; ++i)
	{
		const wchar_t* pszText;
		if(bCreated)
			pszText = static_cast<const wchar_t*>(&aText[i][0]);
		else
		{
			if(!g_Text[i].empty())
				pszText = static_cast<const wchar_t*>(&g_Text[i][0]);
			else
				pszText = 0;
		}
		m_areLang[i].SetTextEx((LPCTSTR)pszText,ST_DEFAULT,1200);
		g_Text[i].clear();
	}
}

void TransliteratorDlg::InitDialog()
{
	m_dlgProfileDetails.Create(m_hWnd);
	m_dlgTranslateFiles.Create(m_hWnd);
	m_dlgAbout.Create(m_hWnd);
	m_dlgOptions.Create(m_hWnd);
}

void TransliteratorDlg::InitStatusBar()
{
	m_wndStatusBar.Create(m_hWnd);
	m_hWndStatusBar = m_wndStatusBar;
	int panes[]  = 
	{
		ID_COUNTLANGTOP,
		ID_COUNTLANGBOTTOM,
		ID_DEFAULT_PANE,
		ID_PROFILE
	};
	m_wndStatusBar.SetPanes(panes, NN_ARRAY_LENGTH(panes) ,false);
	
	HDC hDC = m_wndStatusBar.GetDC();
	SetTextCharacterExtra(hDC,0);
	m_wndStatusBar.ReleaseDC(hDC);
}

LRESULT TransliteratorDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// Icon
	DialogIcon_Init();

	// StatusBar
	InitStatusBar();

	// InitControls
	InitControls();

	// Dialog
	InitDialog();

	// Language
	DialogLang_Init();

	// Resize
	DlgResize_Init(false,true);

	// TrayIcon
	InitTrayIcon(IDR_TRANSLITERATOR,
		WTL::AtlLoadIcon(IDR_TRANSLITERATOR),
		IDR_TRAYICON);

	m_hAccel = WTL::AtlLoadAccelerators(IDR_TRANSLITERATOR);

	// Options
	SetOptions();

	UIAddChildWindowContainer(m_hWnd);

	return TRUE;
}

LRESULT TransliteratorDlg::OnSysCommand(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
{
	bHandled = FALSE;
	WORD wMsg = LOWORD(wParam);

	if(wMsg == SC_CLOSE)
		Close();
	else
	if(wMsg == SC_MINIMIZE&&g_Options.m_bTrayIconShow)
	{
		bHandled = TRUE;
		ShowWindow(SW_MINIMIZE);
		ShowHide(false);
	}

	return 0;
}

LRESULT TransliteratorDlg::OnHotKey(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	switch(wParam-hkID)
	{
		case Options::hkLangToptoLangBottom:
			TranslateWindow(Translate::dirToptoBottom);
			break;
		case Options::hkLangBottomtoLangTop:
			TranslateWindow(Translate::dirBottomtoTop);
			break;
		case Options::hkAuto:
			TranslateWindow(Translate::dirAuto);
			break;
		case Options::hkShowHide:
			ShowHide(IsWindowVisible()?false:true);
			break;
		case Options::hkCopyIgnore:
			g_Options.m_bCopyIgnore = !g_Options.m_bCopyIgnore;
			UpdateTranslation();
			break;
	}
	return 0;
}

LRESULT TransliteratorDlg::OnQueryEndSession(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	Settings::Save();
	return TRUE;
}

LRESULT TransliteratorDlg::OnApply(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	SetOptions();
	m_dlgOptions.SetFocus();

	return 0;
}

LRESULT TransliteratorDlg::OnAppExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	Close();

	return 0;
}

LRESULT TransliteratorDlg::OnEditCommands(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	WTL::CRichEditCtrl re = ::GetFocus();
	
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

LRESULT TransliteratorDlg::OnEditIgnore(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	WTL::CRichEditCtrl re = ::GetFocus();

	const bool bInsert = wID == ID_EDIT_IGNORE_INSERT;
	const bool bfirst = re == m_areLang[0];
	
	const size_t nCharIn = (size_t)re.GetWindowTextLength()+1;
	const size_t maxlenI = g_Language.MaxLengthIgnore(g_Language.GetCurProfile());

	static const wchar_t strEmpty[] = {0};

	// Text
	try
	{
		std::vector<wchar_t> aTextIn(nCharIn);

		re.GetTextEx((LPTSTR)&aTextIn[0],nCharIn*sizeof(wchar_t),GT_DEFAULT,1200);

		std::vector<wchar_t> aTextIn1(strEmpty, NN_ARRAY_END(strEmpty));
		std::vector<wchar_t> aTextInT(strEmpty, NN_ARRAY_END(strEmpty));
		std::vector<wchar_t> aTextIn2(strEmpty, NN_ARRAY_END(strEmpty));
	
		std::vector<wchar_t> aTextOutT; // InT -> OutT
	
		// CharRange
		CHARRANGE cr;
		re.GetSel(cr);

		const bool bSetIgnore = cr.cpMin == cr.cpMax;

		// Insert/Remove
		if(bSetIgnore)
		{
			// In1
			// aTextIn1 = strEmpty;
	
			// InT
			aTextInT.resize(cr.cpMin+1);
		
			std::copy(&aTextIn[0],&aTextIn[cr.cpMin],&aTextInT[0]);
			aTextInT[cr.cpMin] = 0;

			// In2
			if((size_t)cr.cpMax != nCharIn-1)
			{
				aTextIn2.resize(nCharIn-cr.cpMax);
				wcscpy(&aTextIn2[0],&aTextIn[cr.cpMax]);
			}

			// OutT
			aTextOutT.resize(cr.cpMin + maxlenI +1);
		}
		// Ignore
		else
		{
			if(!cr.cpMin && (size_t)cr.cpMax == nCharIn-1) // All
			{
				aTextInT = aTextIn;
			}
			else // Selection
			{
				aTextIn1.resize(cr.cpMin+1);
				std::copy(&aTextIn[0],&aTextIn[cr.cpMin],&aTextIn1[0]);
				aTextIn1[cr.cpMin] = 0;
	
				aTextInT.resize(cr.cpMax-cr.cpMin+1);
				std::copy(&aTextIn[cr.cpMin],&aTextIn[cr.cpMax],&aTextInT[0]);
				aTextInT[cr.cpMax-cr.cpMin] = 0;

				if((size_t)cr.cpMax != nCharIn-1)
				{
					aTextIn2.resize(nCharIn-cr.cpMax);
					wcscpy(&aTextIn2[0],&aTextIn[cr.cpMax]);
				}
			}

			aTextOutT.resize(cr.cpMax - cr.cpMin + 2*maxlenI + 1);
		}

		aTextIn.clear();
		if(bSetIgnore)
		{
			g_Language.SetIgnore(&aTextInT[0],&aTextOutT[0],
					bfirst?Translate::dirToptoBottom:Translate::dirBottomtoTop,
 					bInsert,0);

			cr.cpMin = cr.cpMax = wcslen(&aTextOutT[0]);
		}
		else
		{
			g_Language.Ignore(&aTextInT[0],&aTextOutT[0],
					bInsert,bfirst,0);

			cr.cpMax = cr.cpMin+wcslen(&aTextOutT[0]);
		}

		std::vector<wchar_t> aTextOut(
			wcslen(&aTextIn1[0])+
			wcslen(&aTextOutT[0])+
			wcslen(&aTextIn2[0])+
			1);
		
		wcscpy(&aTextOut[0],&aTextIn1[0]);
		wcscat(&aTextOut[0],&aTextOutT[0]);
		wcscat(&aTextOut[0],&aTextIn2[0]);

		re.SetTextEx((const TCHAR*)&aTextOut[0],ST_DEFAULT,1200);
		re.SetSel(cr.cpMin,cr.cpMax);
	}
	catch(...)
	{
	}

	UpdateStatusBar();
	if(g_Options.m_bCaptionCount)
		UpdateCaption();

	return 0;
}

LRESULT TransliteratorDlg::OnEditCopy(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	NN::sg<BOOL> sg(g_Options.m_bTranslate,FALSE);
	
	bool b1 =  wID == ID_EDIT_COPY_LANGTOPTOLANGBOTTOM;

	WTL::CRichEditCtrl& reFrom = m_areLang[!b1];
	WTL::CRichEditCtrl& reTo = m_areLang[b1];

	int nLen = reFrom.GetTextLength()+1;
	std::vector<wchar_t> aText(nLen);
	reFrom.GetTextEx((LPTSTR)&aText[0],nLen*sizeof(wchar_t),GT_DEFAULT,1200);
	reTo.SetTextEx((const TCHAR*)&aText[0],ST_DEFAULT,1200);

	return 0;
}

LRESULT TransliteratorDlg::OnProfile(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	g_Options.m_nCurProfile = wID-ID_PROFILE1;
	g_Language.SetCurProfile(g_Options.m_nCurProfile);

	UpdateTranslation();
	UpdateStatusBar();
	UpdateCaption();
	UpdateLang();

	m_dlgOptions.NotifyProfileChanged();

	return 0;
}

LRESULT TransliteratorDlg::OnToolsAction(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	switch(wID)
	{
		case ID_TOOLS_ACTION_TRANSLITERATION:
			g_Options.m_bTranslate = !g_Options.m_bTranslate;
			break;
		case ID_TOOLS_ACTION_IGNORE:
			g_Options.m_bIgnore = !g_Options.m_bIgnore;
			break;
		case ID_TOOLS_ACTION_IGNORETEXT:
			g_Options.m_bIgnoreText = !g_Options.m_bIgnoreText;
			break;
		case ID_TOOLS_ACTION_COPYIGNORE:
			g_Options.m_bCopyIgnore = !g_Options.m_bCopyIgnore;
			break;
	}
	
	UpdateTranslation();

	return 0;
}

LRESULT TransliteratorDlg::OnShowHide(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	ShowHide(wID == ID_SHOW);
	UpdateTrayIcon();
	if(wID == ID_SHOW)
		UpdateTaskBar();
	return 0;
}

LRESULT TransliteratorDlg::OnEnChangeLang(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	static bool bTranslate = false;
	if(g_Options.m_bTranslate && !bTranslate)
	{
		NN::sg_t<bool,true,false> sg(bTranslate);
		Translate(wID == IDC_RELANGTOP?
			Translate::dirToptoBottom:
			Translate::dirBottomtoTop);
		
		bool bfirst =  wID == IDC_RELANGTOP;

		WTL::CRichEditCtrl reFrom = m_areLang[!bfirst];
		WTL::CRichEditCtrl reTo = m_areLang[bfirst];

		if(g_Options.m_bScrollText)
			reTo.LineScroll(reFrom.GetFirstVisibleLine());

		UpdateStatusBar();
		if(g_Options.m_bCaptionCount)
			UpdateCaption();
	}

	return 0;
}

LRESULT TransliteratorDlg::OnEnMsgFilterLang(int /*code*/, NMHDR* pnmhdr, BOOL& /*bHandled*/)
{
	MSGFILTER *pMsgFilter = (MSGFILTER *)pnmhdr;
	if(pMsgFilter->msg == WM_RBUTTONDOWN)
	{
		::SetFocus(pMsgFilter->nmhdr.hwndFrom);
		OnIdle();
		POINT pt;
		::GetCursorPos(&pt);
		HMENU hMenu = WTL::AtlLoadMenu(IDR_EDIT);
		hMenu = ::GetSubMenu(hMenu,0);
		::TrackPopupMenu(hMenu,TPM_LEFTALIGN|TPM_LEFTBUTTON|
			TPM_RIGHTBUTTON,pt.x,pt.y,0,m_hWnd,NULL);
		::DestroyMenu(hMenu);
	}
	return 0;
}

LRESULT TransliteratorDlg::OnClickStatusBar(int /*code*/, NMHDR* pnmhdr, BOOL& /*bHandled*/)
{
	if(pnmhdr->code == NM_RCLICK)
	{
		OnIdle();
		POINT pt;
		::GetCursorPos(&pt);

		HMENU hMenu = WTL::AtlLoadMenu(IDR_PROFILE);
		hMenu = ::GetSubMenu(hMenu,0);
		::SetMenuDefaultItem(hMenu,IsWindowVisible()?ID_HIDE:ID_SHOW,FALSE);
		::TrackPopupMenu(hMenu,TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON,
			pt.x,pt.y,0,m_hWnd,NULL);
		::DestroyMenu(hMenu);
	}
	else
	if(pnmhdr->code == NM_DBLCLK)
	{
		if(++g_Options.m_nCurProfile == Language::nProfiles)
			g_Options.m_nCurProfile = 0;
		g_Language.SetCurProfile(g_Options.m_nCurProfile);
		UpdateTranslation();
		UpdateStatusBar();
		UpdateCaption();
	}

	return 0;
}
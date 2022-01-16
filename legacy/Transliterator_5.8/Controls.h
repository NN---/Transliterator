#ifndef __CONTROLS_H__
#define __CONTROLS_H__

inline void InitCmbLanguage(HWND hWnd,int nCurSel=0,const Language& rL=g_Language)
{
	::SendMessage(hWnd,CB_RESETCONTENT,0,0);
	for(int i=0;i<Language::nProfiles;i++)
		::SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)(rL.GetProfile((Language::Profiles)i)->m_strName));
	::SendMessage(hWnd,CB_SETCURSEL,(WPARAM)nCurSel,0);
}

inline void InitCmbLanguageUser(HWND hWnd,int nCurSel=0,const Language& rL=g_Language)
{
	::SendMessage(hWnd,CB_RESETCONTENT,0,0);
	for(int i=Language::profUser1;i<Language::nProfiles;i++)
		::SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)(rL.GetProfile((Language::Profiles)i)->m_strName));
	::SendMessage(hWnd,CB_SETCURSEL,(WPARAM)nCurSel,0);
}

inline void InitCmbLanguageDefUser(HWND hWnd,int nCurSel,const Language& rL)
{
	::SendMessage(hWnd,CB_RESETCONTENT,0,0);
	for(int i=0;i<Language::profUser1;i++)
		::SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)(g_Language.GetProfile((Language::Profiles)i)->m_strName));
	for(int i=Language::profUser1;i<Language::nProfiles;i++)
		::SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)(rL.GetProfile((Language::Profiles)i)->m_strName));
	::SendMessage(hWnd,CB_SETCURSEL,(WPARAM)nCurSel,0);
}


#endif // __CONTROLS_H__
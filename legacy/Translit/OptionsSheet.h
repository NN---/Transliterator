#ifndef __OPTIONSSHEET_H__
#define __OPTIONSSHEET_H__

class CGeneralPage : public PropertyPageImplLang<CGeneralPage,IDD_GENERALPAGE>
{
public:
	typedef CGeneralPage thisClass;
	typedef PropertyPageImplLang<CGeneralPage,IDD_GENERALPAGE> baseClass;

	PROPERTYPAGEDDX_DECLARE(thisClass)

	BEGIN_DDX_MAP(thisClass)
		DDX_RADIO(IDC_CLOSEEXIT,(int&)_Options.m_nClose)
		DDX_RADIO(IDC_MINIMIZENORMAL,(int&)_Options.m_nMinimize)
		DDX_CHECK(IDC_LOADONSTARTUP,_Options.m_bLoadOnStartUp)
	END_DDX_MAP()

	BEGIN_MSG_MAP(thisClass)
		CHAIN_MSG_MAP_ALT(baseClass,1)
		CHAIN_MSG_MAP(baseClass)
	END_MSG_MAP()
};

class CLayoutPage : public PropertyPageImplLang<CLayoutPage,IDD_LAYOUTPAGE>
{
public:
	typedef CLayoutPage thisClass;
	typedef PropertyPageImplLang<CLayoutPage,IDD_LAYOUTPAGE> baseClass;

	void FontDialog(LPLOGFONT pLF)
	{
		CFontDialog fontdlg(pLF);
		if(fontdlg.DoModal()==IDOK)
			*pLF=fontdlg.m_lf;
	}

	PROPERTYPAGEDDX_DECLARE(thisClass)

	BEGIN_DDX_MAP(thisClass)
		DDX_CHECK(IDC_TRAYICONSHOWN,_Options.m_bTrayIconShown)
		DDX_CHECK(IDC_TRAYICONHIDDEN,_Options.m_bTrayIconHidden)
	END_DDX_MAP()

	BEGIN_MSG_MAP(thisClass)
		CHAIN_MSG_MAP_ALT(baseClass,1)
		COMMAND_ID_HANDLER(IDC_ENGFONT,OnEngRusFont)
		COMMAND_ID_HANDLER(IDC_RUSFONT,OnEngRusFont)
		CHAIN_MSG_MAP(baseClass)
	END_MSG_MAP()

	LRESULT OnEngRusFont(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		FontDialog(&_Options.m_lfEngRus[wID-IDC_ENGFONT]);
		return 0;
	}
};

#define DDX_HOTKEY(nID,vk,fsModifiers) \
	if(nCtlID == (UINT)-1 || nCtlID == nID) \
		DDX_HotKey(m_hWnd,nID,vk,fsModifiers,bSaveAndValidate);

#define DDX_HOTKEY_C(nID,rHotKey,bConvert) \
	if(nCtlID == (UINT)-1 || nCtlID == nID) \
		DDX_HotKey(m_hWnd,nID,rHotKey,bSaveAndValidate,bConvert);

#define DDX_HOTKEY_(nID,rHotKey) \
	if(nCtlID == (UINT)-1 || nCtlID == nID) \
		DDX_HotKey(m_hWnd,nID,rHotKey,bSaveAndValidate);

inline BOOL DDX_HotKey(HWND hWnd,UINT nID,WORD& vk,WORD& fsModifiers,BOOL bSave)
{
	if(bSave)
	{
		WORD wHotKey=(WORD)::SendDlgItemMessage(hWnd,nID,HKM_GETHOTKEY,0,0);
		vk=LOBYTE(wHotKey);
		fsModifiers=HIBYTE(wHotKey);
	}
	else
		::SendDlgItemMessage(hWnd,nID,HKM_SETHOTKEY,(WPARAM)MAKEWORD(vk,fsModifiers),0);
	return TRUE;
}

inline BOOL DDX_HotKey(HWND hWnd,UINT nID,HotKey& rHotKey,BOOL bSave,BOOL bConvert=TRUE)
{
	HotKey hk=rHotKey;
	if(bConvert)
		hk.ConvertToHotKey();
	if(bSave)
	{
		BOOL bRet=DDX_HotKey(hWnd,nID,hk.vk,hk.fsModifiers,bSave);
		if(bRet)
		{
			hk.ConvertToWnd();
			rHotKey=hk;
		}
		return bRet;
	}
	else
		return DDX_HotKey(hWnd,nID,hk.vk,hk.fsModifiers,bSave);
}

class CHotKeysPage : public PropertyPageImplLang<CHotKeysPage,IDD_HOTKEYSPAGE>
{
public:
	typedef CHotKeysPage thisClass;
	typedef PropertyPageImplLang<CHotKeysPage,IDD_HOTKEYSPAGE> baseClass;

	PROPERTYPAGEDDX_DECLARE(thisClass)

	BEGIN_DDX_MAP(thisClass)
		DDX_HOTKEY_(IDC_HOTKEYTRANSLATIONENGTORUS,_Options.m_hkTranslationEngtoRus)
		DDX_HOTKEY_(IDC_HOTKEYTRANSLATIONRUSTOENG,_Options.m_hkTranslationRustoEng)
		DDX_HOTKEY_(IDC_HOTKEYSHOWTRANSLIT,_Options.m_hkShowTranslit)
		DDX_HOTKEY_(IDC_HOTKEYHIDETRANSLIT,_Options.m_hkHideTranslit)
	END_DDX_MAP()

	BEGIN_MSG_MAP(CHotKeysPage)
		CHAIN_MSG_MAP_ALT(baseClass,1)
		CHAIN_MSG_MAP(baseClass)
	END_MSG_MAP()
};

class CAutoTranslationPage : public PropertyPageImplLang<CAutoTranslationPage,IDD_AUTOTRANSLATIONPAGE>
{
public:
	typedef CAutoTranslationPage thisClass;
	typedef PropertyPageImplLang<CAutoTranslationPage,IDD_AUTOTRANSLATIONPAGE> baseClass;

	PROPERTYPAGEDDX_DECLARE(thisClass)

	BEGIN_DDX_MAP(thisClass)
		DDX_RADIO(IDC_ENGTORUS,(int&)_Options.m_nDefaultTranslation)
		DDX_HOTKEY_(IDC_HOTKEYTRANSLATIONAUTO,_Options.m_hkTranslationAuto)
	END_DDX_MAP()

	BEGIN_MSG_MAP(CHotKeysPage)
		CHAIN_MSG_MAP_ALT(baseClass,1)
		CHAIN_MSG_MAP(baseClass)
	END_MSG_MAP()
};

class COptionsSheet : public CPropertySheetImpl<COptionsSheet>,
					public PropertyTitleLang<COptionsSheet>
{
public:
	typedef CPropertySheetImpl<COptionsSheet> baseClass;
	enum { IDD = IDS_OPTIONS };
	COptionsSheet(HWND hWndParent = NULL, UINT uStartPage = 0) :
		baseClass((LPCTSTR)0,uStartPage,hWndParent)
	{
		m_psh.dwFlags |= PSH_NOAPPLYNOW;
		m_psh.dwFlags &= ~(PSH_HASHELP);
		SetPropertyTitle(IDS_OPTIONS);
		AddPage(m_pageGeneral);
		AddPage(m_pageLayout);
		AddPage(m_pageHotKeys);
		AddPage(m_pageAutoTranslation);
	}

	CGeneralPage m_pageGeneral;
	CLayoutPage m_pageLayout;
	CHotKeysPage m_pageHotKeys;
	CAutoTranslationPage m_pageAutoTranslation;
};

#endif // __OPTIONSSHEET_H_
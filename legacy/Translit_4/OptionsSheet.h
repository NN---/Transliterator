#ifndef __OPTIONSSHEET_H__
#define __OPTIONSSHEET_H__

#define PAGEOPTIONS(name) \
	Options* m_pOptions; \
	name(Options* pOptions) : m_pOptions(pOptions) {}

class CGeneralPage : public NN::PropertyPageImplLang<CGeneralPage,IDD_GENERALPAGE>
{
public:
	typedef CGeneralPage thisClass;
	typedef NN::PropertyPageImplLang<CGeneralPage,IDD_GENERALPAGE> baseClass;

	PAGEOPTIONS(CGeneralPage)

	PROPERTYPAGEDDX_DECLARE(thisClass)

	BEGIN_DDX_MAP(thisClass)
		DDX_RADIO(IDC_CLOSEEXIT,(int&)m_pOptions->m_nClose)
		DDX_RADIO(IDC_MINIMIZENORMAL,(int&)m_pOptions->m_nMinimize)
		DDX_CHECK(IDC_LOADONSTARTUP,m_pOptions->m_bLoadOnStartUp)
	END_DDX_MAP()

	BEGIN_MSG_MAP(thisClass)
		CHAIN_MSG_MAP_ALT(baseClass,1)
		CHAIN_MSG_MAP(baseClass)
	END_MSG_MAP()
};

class CLayoutPage : public NN::PropertyPageImplLang<CLayoutPage,IDD_LAYOUTPAGE>
{
public:
	typedef CLayoutPage thisClass;
	typedef NN::PropertyPageImplLang<CLayoutPage,IDD_LAYOUTPAGE> baseClass;

	PAGEOPTIONS(CLayoutPage)

	void FontDialog(LPLOGFONT pLF)
	{
		CFontDialog fontdlg(pLF);
		if(fontdlg.DoModal()==IDOK)
			*pLF=fontdlg.m_lf;
	}

	PROPERTYPAGEDDX_DECLARE(thisClass)

	BEGIN_DDX_MAP(thisClass)
		DDX_CHECK(IDC_TRAYICONSHOWN,m_pOptions->m_bTrayIconShown)
		DDX_CHECK(IDC_TRAYICONHIDDEN,m_pOptions->m_bTrayIconHidden)
	END_DDX_MAP()

	BEGIN_MSG_MAP(thisClass)
		CHAIN_MSG_MAP_ALT(baseClass,1)
		COMMAND_ID_HANDLER(IDC_ENGFONT,OnEngRusFont)
		COMMAND_ID_HANDLER(IDC_RUSFONT,OnEngRusFont)
		CHAIN_MSG_MAP(baseClass)
	END_MSG_MAP()

	LRESULT OnEngRusFont(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		FontDialog(&m_pOptions->m_lfEngRus[wID-IDC_ENGFONT]);
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

inline BOOL DDX_HotKey(HWND hWnd,UINT nID,NN::HotKey& rHotKey,BOOL bSave,BOOL bConvert=TRUE)
{
	NN::HotKey hk=rHotKey;
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

class CHotKeysPage : public NN::PropertyPageImplLang<CHotKeysPage,IDD_HOTKEYSPAGE>
{
public:
	typedef CHotKeysPage thisClass;
	typedef NN::PropertyPageImplLang<CHotKeysPage,IDD_HOTKEYSPAGE> baseClass;

	PAGEOPTIONS(CHotKeysPage)

	PROPERTYPAGEDDX_DECLARE(thisClass)

	BEGIN_DDX_MAP(thisClass)
//		DDX_HOTKEY_(IDC_HOTKEYTRANSLATIONENGTORUS,m_pOptions->m_hkTranslationEngtoRus)
//		DDX_HOTKEY_(IDC_HOTKEYTRANSLATIONRUSTOENG,m_pOptions->m_hkTranslationRustoEng)
//		DDX_HOTKEY_(IDC_HOTKEYSHOWTRANSLIT,m_pOptions->m_hkShowTranslit)
//		DDX_HOTKEY_(IDC_HOTKEYHIDETRANSLIT,m_pOptions->m_hkHideTranslit)
		DDX_RADIO(IDC_ENGTORUS,(int&)m_pOptions->m_nAutoTranslation)
	END_DDX_MAP()

	BEGIN_MSG_MAP(CHotKeysPage)
		CHAIN_MSG_MAP_ALT(baseClass,1)
		MESSAGE_HANDLER(WM_DESTROY,OnDestroy)
		COMMAND_HANDLER(IDC_ACTION,CBN_SELCHANGE,OnCmbSelChangeAction)
		CHAIN_MSG_MAP(baseClass)
	END_MSG_MAP()

	NN::AutoValue<int,CB_ERR> m_nCurSel;

	void SaveHotKey()
	{
		CHotKeyCtrl hotkey=GetDlgItem(IDC_HOTKEYTRANSLIT);
		if(m_nCurSel!=CB_ERR)
		{
			hotkey.GetHotKey(m_pOptions->m_hkTranslit[m_nCurSel].vk,
				m_pOptions->m_hkTranslit[m_nCurSel].fsModifiers);
			m_pOptions->m_hkTranslit[m_nCurSel].ConvertToWnd();
		}
	}

	void LoadHotKey()
	{
		CHotKeyCtrl hotkey=GetDlgItem(IDC_HOTKEYTRANSLIT);
		m_nCurSel=CComboBox(GetDlgItem(IDC_ACTION)).GetCurSel();
		hotkey.SetHotKey(m_pOptions->m_hkTranslit[m_nCurSel].vk,
			m_pOptions->m_hkTranslit[m_nCurSel].fsModifiers);
	}
	
	LRESULT OnCmbSelChangeAction(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		SaveHotKey();
		m_nCurSel=::SendMessage(m_hWnd,CB_GETCURSEL,0,0);
		LoadHotKey();
		return 0;
	}

	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		SaveHotKey();
		return 0;
	}
};

class COptionsSheet : public CPropertySheetImpl<COptionsSheet>,
				public NN::PropertyTitleLang<COptionsSheet>
{
public:
	typedef CPropertySheetImpl<COptionsSheet> baseClass;
	enum { IDD = IDS_OPTIONS };
	COptionsSheet(HWND hWndParent = NULL, UINT uStartPage = 0) :
		baseClass((LPCTSTR)0,uStartPage,hWndParent),
			m_pageGeneral(&tempOptions),
			m_pageLayout(&tempOptions),
			m_pageHotKeys(&tempOptions)
	{
		m_psh.dwFlags |= PSH_NOAPPLYNOW;
		m_psh.dwFlags &= ~(PSH_HASHELP);
		SetPropertyTitle(IDS_OPTIONS);
		AddPage(m_pageGeneral);
		AddPage(m_pageLayout);
		AddPage(m_pageHotKeys);
	}

	INT_PTR DoModal(HWND hWndParent = ::GetActiveWindow())
	{
		tempOptions=_Options;
		INT_PTR nRet=baseClass::DoModal(hWndParent);
		if(nRet==IDOK)
			_Options=tempOptions;
		return nRet;
	}

	CGeneralPage m_pageGeneral;
	CLayoutPage m_pageLayout;
	CHotKeysPage m_pageHotKeys;

	Options tempOptions;
};

#endif // __OPTIONSSHEET_H_
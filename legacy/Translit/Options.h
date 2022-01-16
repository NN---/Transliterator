#ifndef __OPTIONS_H__
#define __OPTIONS_H__

#include <NN/Auto.h>
#include <NN/HotKey.h>
using namespace NN;

struct WindowState
{
	int nCmdShow;
	static const WindowState& Default()
	{
		static const WindowState state={SW_SHOWNORMAL};
		return state;
	}
	bool operator==(const WindowState& state) const
	{ return nCmdShow==state.nCmdShow; }
};

struct Options
{
public:
	AutoValue<BOOL,FALSE> m_bTranslation;
	WindowState m_wndState;
	AutoValue<LANGID,MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US)> m_langID;
	// Options Dialog
	AutoValue<BOOL,FALSE> m_bTrayIconShown;
	AutoValue<BOOL,TRUE> m_bTrayIconHidden;
	AutoValue<BOOL,FALSE> m_bLoadOnStartUp;
	enum Close { closeExit, closeToTray };
	AutoValue<Close,closeExit> m_nClose;
	enum Minimize { minimizeNormal, minimizeToTray };
	AutoValue<Minimize,minimizeToTray> m_nMinimize;
	LOGFONT m_lfEngRus[2];
	enum EngRus { Eng , Rus };
	HotKey m_hkTranslationEngtoRus;
	HotKey m_hkTranslationRustoEng;
	HotKey m_hkTranslationAuto;
	HotKey m_hkShowTranslit;
	HotKey m_hkHideTranslit;
	enum FromTo { FromEng=0, FromRus=1, ToEng=2, ToRus=3 };
	enum NotTranslate { nNotTranslate = 4 };
	TCHAR m_szNotTranslate[4][nNotTranslate];
	AutoValue<BOOL,FALSE> m_bCopyNotTranslate;
	AutoValue<Translate::Direction,Translate::dirEngtoRus> m_nDefaultTranslation;
	AutoValue<BOOL,FALSE> m_bWrapText;
	
	void Default()
	{
		m_bTranslation.Default();
		m_bTrayIconShown.Default();
		m_bTrayIconHidden.Default();
		m_wndState=WindowState::Default();
		m_langID.Default();
		// Options
		m_bLoadOnStartUp.Default();
		m_nClose.Default();
		m_nMinimize.Default();
		m_hkTranslationEngtoRus.SetHotKey(_T('E'),MOD_CONTROL|MOD_ALT);
		m_hkTranslationRustoEng.SetHotKey(_T('C'),MOD_CONTROL|MOD_ALT);
		m_hkTranslationAuto.SetHotKey(_T('T'),MOD_CONTROL|MOD_ALT);
		m_hkShowTranslit.SetHotKey(_T('S'),MOD_CONTROL|MOD_ALT);
		m_hkHideTranslit.SetHotKey(_T('H'),MOD_CONTROL|MOD_ALT);
		// Fonts
		LOGFONT lfCommon;
		::ZeroMemory(&lfCommon,sizeof(LOGFONT));
		lfCommon.lfCharSet=ANSI_CHARSET;
		lfCommon.lfHeight=-14;
		lfCommon.lfWeight=400;
		lstrcpy(lfCommon.lfFaceName,_T("Arial"));
		m_lfEngRus[Eng]=lfCommon;
		m_lfEngRus[Rus]=lfCommon;
		lstrcpy(m_szNotTranslate[FromEng],_T("["));
		lstrcpy(m_szNotTranslate[FromRus],_T("["));
		lstrcpy(m_szNotTranslate[ToEng],_T("]"));
		lstrcpy(m_szNotTranslate[ToRus],_T("]"));
		m_bCopyNotTranslate.Default();
		m_nDefaultTranslation.Default();
		m_bWrapText.Default();
	}
};

#endif // __OPTIONS_H__
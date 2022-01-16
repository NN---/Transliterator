#ifndef __OPTIONS_H__
#define __OPTIONS_H__

#include "windowstate.h"

struct Options
{
	enum { Trns , Rus };

	BOOL m_bTranslate;
	WindowState m_wndState;

	BOOL m_bShowTrayIcon;
	BOOL m_bShowTaskBar;
	BOOL m_bTopMost;
	enum LoadOnStartUp
	{
		loadNo,
		loadShown,
		loadHidden
	};
	LoadOnStartUp m_nLoadOnStartUp;

	enum Fonts
	{
		fontTrns,
		fontRus,
		fontTranslation,
		nFont
	};
	LOGFONT m_lfFont[nFont];
	
	enum HotKeys
	{
		hkTrnstoRus,
		hkRusToTrns,
		hkAuto,
		hkShowHide,
		hkCopyTrns,
		hkCopyRus,
		nHotKey
	};
	NN::HotKey m_HotKey[nHotKey];

	BOOL m_bCopyIgnore;
	Translate::Direction m_nAutoTranslation;
	
	BOOL m_bWrapText;
	BOOL m_bScrollText;

	UINT m_nCurProfile;

	BOOL m_bIgnore;

	void Reset()
	{
		m_bTranslate=TRUE;
		m_wndState.Reset();

		m_bShowTrayIcon=FALSE;
		m_bShowTaskBar=TRUE;
		m_bTopMost=FALSE;
		m_nLoadOnStartUp=loadNo;

		m_HotKey[hkTrnstoRus].SetHotKey('T',MOD_CONTROL|MOD_ALT|MOD_SHIFT);
		m_HotKey[hkRusToTrns].SetHotKey('R',MOD_CONTROL|MOD_ALT|MOD_SHIFT);
		m_HotKey[hkAuto].SetHotKey('A',MOD_CONTROL|MOD_ALT|MOD_SHIFT);
		m_HotKey[hkShowHide].SetHotKey('S',MOD_CONTROL|MOD_ALT|MOD_SHIFT);
		m_HotKey[hkCopyTrns].SetHotKey('C',MOD_CONTROL|MOD_ALT|MOD_SHIFT);
		m_HotKey[hkCopyRus].SetHotKey('O',MOD_CONTROL|MOD_ALT|MOD_SHIFT);

		// Fonts
		LOGFONT lfCommon;
		::ZeroMemory(&lfCommon,sizeof(LOGFONT));
		lfCommon.lfCharSet=ANSI_CHARSET;
		lfCommon.lfHeight=-14;
		lfCommon.lfWeight=FW_NORMAL;
		lstrcpy(lfCommon.lfFaceName,"Arial");
		m_lfFont[fontTrns]=lfCommon;
		m_lfFont[fontRus]=lfCommon;
		::ZeroMemory(&lfCommon,sizeof(LOGFONT));
		lfCommon.lfCharSet=ANSI_CHARSET;
		lfCommon.lfHeight=-10;
		lfCommon.lfWeight=FW_NORMAL;
		lstrcpy(lfCommon.lfFaceName,"Arial");
		m_lfFont[fontTranslation]=lfCommon;
		
		m_bCopyIgnore=FALSE;
		m_nAutoTranslation=Translate::dirTrnstoRus;

		m_bWrapText=TRUE;
		m_bScrollText=TRUE;

		m_nCurProfile=0;

		m_bIgnore=TRUE;
	}

	const Options& operator=(const Options& options)
	{
		memcpy(this,&options,sizeof(Options));
		return *this;
	}

	bool operator==(const Options& options) const
	{ return !operator!=(options); }
	bool operator!=(const Options& options) const
	{ return memcmp(this,&options,sizeof(Options)); }
};

#endif // __OPTIONS_H__
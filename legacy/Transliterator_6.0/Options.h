#ifndef __OPTIONS_H__
#define __OPTIONS_H__

#pragma once

#include "translate.h"

struct Options
{
	// Profile
	unsigned m_nCurProfile;
	
	// Show
	WINDOWPLACEMENT m_wndpl;
	
	// Action
	BOOL m_bTranslate;
	BOOL m_bIgnore;
	BOOL m_bIgnoreText;

	// Ignore
	BOOL m_bCopyIgnore;

	// AutoTransliteration
	Translate::Direction m_nAutoTransliteration;

	// Controls
	BOOL m_bWrapText;
	BOOL m_bScrollText;

	// Caption
	BOOL m_bCaptionProfile;
	BOOL m_bCaptionCount;

	// StatusBar
	BOOL m_bStatusBarCount;

	// Tray Icon
	BOOL m_bTrayIconShow;

	// TaskBar
	BOOL m_bTaskBarShow;
	
	// View
	enum Placement
	{
		placementNormal,
		placementOnTop,
		placementOnBottom
	};
	Placement m_nPlacement;
	
	// Font
	enum Font
	{
		fontLangTop,
		fontLangBottom,
		fontDetails,
		nFonts
	};
	LOGFONT m_alfFont[nFonts];

	// HotKeys
	enum HotKeys
	{
		hkLangToptoLangBottom,
		hkLangBottomtoLangTop,
		hkAuto,
		hkShowHide,
		hkCopyIgnore,
		nHotKey
	};
	NN::HotKey m_HotKey[nHotKey];

	// LoadOnStartUp
	enum LoadOnStartUp
	{
		loadNo,
		loadShown,
		loadHidden
	};
	LoadOnStartUp m_nLoadOnStartUp;

	// SaveText
	BOOL m_bSaveText;

	void Reset()
	{
		// CurProfile
		m_nCurProfile = 0;

		// Show
		::memset(&m_wndpl,0,sizeof(m_wndpl));
		m_wndpl.showCmd = SW_SHOWNORMAL;

		// Action
		m_bTranslate = TRUE;
		m_bIgnore = TRUE;
		m_bIgnoreText = TRUE;

		// CopyIgnore
		m_bCopyIgnore = FALSE;

		// AutoTransliteration
		 m_nAutoTransliteration = Translate::dirToptoBottom;

		// Controls
		m_bWrapText = TRUE;
		m_bScrollText = TRUE;

		// Caption
		m_bCaptionProfile = TRUE;
		m_bCaptionCount = FALSE;

		// StatusBar
		m_bStatusBarCount = TRUE;

		// Tray Icon
		m_bTrayIconShow = FALSE;

		// TaskBar
		m_bTaskBarShow = TRUE;

		// View
		m_nPlacement = placementNormal;

		// Font
		LOGFONT lfCommon = {};
		lfCommon.lfCharSet = ANSI_CHARSET;
		lfCommon.lfHeight = -14;
		lfCommon.lfWeight = FW_NORMAL;
		_tcscpy(lfCommon.lfFaceName,_T("Verdana"));
		m_alfFont[fontLangTop] = lfCommon;
		m_alfFont[fontLangBottom] = lfCommon;
		
		lfCommon.lfHeight = -10;
		m_alfFont[fontDetails] = lfCommon;

		// HotKey
		m_HotKey[hkLangToptoLangBottom].SetHotKey('X',MOD_CONTROL|MOD_SHIFT);
		m_HotKey[hkLangBottomtoLangTop].SetHotKey('C',MOD_CONTROL|MOD_SHIFT);
		m_HotKey[hkAuto].SetHotKey('Z',MOD_CONTROL|MOD_SHIFT);
		m_HotKey[hkShowHide].SetHotKey('S',MOD_CONTROL|MOD_SHIFT);
		m_HotKey[hkCopyIgnore].SetHotKey('D',MOD_CONTROL|MOD_SHIFT);

		// LoadOnStartUp
		m_nLoadOnStartUp = loadNo;
		
		// SaveText
		m_bSaveText = TRUE;
	}

	const Options& operator = (const Options& r)
	{
		memcpy(this,&r,sizeof(*this));
		return *this;
	}
};

#endif // __OPTIONS_H__
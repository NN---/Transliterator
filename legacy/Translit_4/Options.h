#ifndef __OPTIONS_H__
#define __OPTIONS_H__

#include "Translate.h"
#include "WindowState.h"

struct Options
{
public:
	enum { Eng , Rus };

	BOOL m_bTranslation;
	BOOL m_bTranslate;
	WindowState m_wndState;

	BOOL m_bTrayIconShown;
	BOOL m_bTrayIconHidden;
	BOOL m_bLoadOnStartUp;
	enum Close { closeExit, closeToTray };
	Close m_nClose;
	enum Minimize { minimizeNormal, minimizeToTray };
	Minimize  m_nMinimize;

	LOGFONT m_lfEngRus[2];

	enum
	{
		hkCommandsMenu,
		hkEngtoRus,
		hkRustoEng,
		hkAuto,
		hkShow,
		hkHide,
		hkInsertNoTranslate,
		hkDeleteNoTranslate,
		hkCopyEng,
		hkCopyRus,
		nHotKey
	};
	NN::HotKey m_hkTranslit[nHotKey];

	enum FromTo { FromEng=0, FromRus=1, ToEng=2, ToRus=3 , nFromTo};
	enum NotTranslate { nNotTranslate = 4 };
	TCHAR m_szNotTranslate[nFromTo][nNotTranslate];
	BOOL m_bCopyNotTranslate;
	Translate::Direction m_nAutoTranslation;
	
	BOOL m_bWrapText;
	BOOL m_bScrollText;

	void Reset()
	{
		m_bTranslation=FALSE;
		m_bTranslate=TRUE;
		m_wndState.Reset();

		m_bTrayIconShown=FALSE;
		m_bTrayIconHidden=TRUE;
		m_bLoadOnStartUp=FALSE;
		m_nClose=closeExit;
		m_nMinimize=minimizeToTray;

		m_hkTranslit[hkCommandsMenu].SetHotKey(_T('T'),MOD_CONTROL|MOD_ALT);
		for(int i=1;i<nHotKey;i++)
			m_hkTranslit[i].SetHotKey();

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
		m_bCopyNotTranslate=FALSE;
		m_nAutoTranslation=Translate::dirEngtoRus;

		m_bWrapText=FALSE;
		m_bScrollText=FALSE;
	}
};

#endif // __OPTIONS_H__
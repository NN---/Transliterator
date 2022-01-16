#ifndef __LANG2LANG_H__
#define __LANG2LANG_H__

#ifndef _T
#define _T(quote) TEXT(quote)
#endif // _T

#define HOTKEY_ID 1000
#define TRAYICON_ID 1001
#define TRAYICON_MSG (WM_USER+5)

// Lang2Lang
#define LANG2LANGFROM_FROM 4
typedef struct _Lang2LangFrom
{
	TCHAR szFrom[LANG2LANGFROM_FROM];
}Lang2LangFrom;
#define LANG2LANGFROMTO_FROM 6
#define LANG2LANGFROMTO_TO 3
typedef struct _Lang2LangFromTo
{
	TCHAR szTo[LANG2LANGFROMTO_TO];
	Lang2LangFrom From[LANG2LANGFROMTO_FROM];
}Lang2LangFromTo;
#define LANG2LANG_NAME 10
#define LANG2LANG_FROMTO 70
typedef struct _Lang2Lang
{
	TCHAR szName[LANG2LANG_NAME];
	Lang2LangFromTo FromTo[LANG2LANG_FROMTO];
}Lang2Lang;
enum Translation { translationNo, translationHotKey, translationTyping };
typedef struct _HotKey // Window Form
{
	WORD vk;
	WORD fsModifiers;
}HotKey;
enum Minimize { minimize, minimizeToTray };
enum Close { closeExit, closeToTray };
typedef struct _WindowPos
{
	BOOL bMin;
	BOOL bMax;
	BOOL bHide;
	RECT rcNormalPosition;
}WindowPos;
#define LANG2LANGOPTIONS_LANG2LANG 3
typedef struct _Lang2LangOptions
{
	enum Translation translation;
	HotKey translationhotkey;
	enum Close close;
	enum Minimize minimize;
	BOOL bShowTrayIcon;
	WindowPos wndPos;
	Lang2Lang aLang2Lang[LANG2LANGOPTIONS_LANG2LANG];
}Lang2LangOptions;

int CmpStr(LPCTSTR s1,LPCTSTR s2)
{
	while(*s1&&*s2)
	{
		if(*s1-*s2)
			return (int)(*s1-*s2);
		s1++;
		s2++;
	}
	return 0;
}
int CmpStrLen(LPCTSTR s1,LPCTSTR s2)
{
	while(*s1&&*s2)
	{
		s1++;
		s2++;
	}
	return *s1?1:*s2?-1:0;
}

void FillMem(void *p,size_t length,BYTE fill)
{
	size_t i;
	BYTE *pb=(BYTE *)p;
	for(i=0;i<length;i++)
		*pb++=fill;
}
#define ZeroMem(p,length) FillMem(p,length,0)
void HotKey2Wnd(WORD *pfsModifiers)
{
	WORD fs=0;
	if(*pfsModifiers&HOTKEYF_ALT)
		fs|=MOD_ALT;
	if(*pfsModifiers&HOTKEYF_CONTROL)
		fs|=MOD_CONTROL;
	if(*pfsModifiers&HOTKEYF_SHIFT)
		fs|=MOD_SHIFT;
	*pfsModifiers=fs;
}
void Wnd2HotKey(WORD *pfsModifiers)
{
	WORD fs=0;
	if(*pfsModifiers&MOD_ALT)
		fs|=HOTKEYF_ALT;
	if(*pfsModifiers&MOD_CONTROL)
		fs|=HOTKEYF_CONTROL;
	if(*pfsModifiers&MOD_SHIFT)
		fs|=HOTKEYF_SHIFT;
	*pfsModifiers=fs;
}

int ShowError(HWND hWnd,UINT uIDError,UINT uType)
{
	TCHAR szCaption[50];
	TCHAR szText[512];
	if(!LoadString(GetModuleHandle(NULL),IDS_ERROR,szCaption,50))
		return -1;
	if(!LoadString(GetModuleHandle(NULL),uIDError,szText,511))
		return -1;
	return MessageBox(hWnd,szText,szCaption,uType);
}
#define ShowErrorT(hWnd,uIDError) ShowError(hWnd,uIDError,MB_OK)
#define ShowErrorHT(uIDError) ShowErrorT(NULL,uIDError)

BOOL TrayMessage(HWND hWnd, UINT uID, DWORD dwMessage, UINT uCallbackMessage, HICON hIcon, PSTR szTip)
{
	BOOL res;
	NOTIFYICONDATA nid;

	nid.cbSize=sizeof(NOTIFYICONDATA);
	nid.hWnd=hWnd;
	nid.uID=uID;
	nid.uFlags=NIF_MESSAGE | NIF_TIP | NIF_ICON;
	nid.uCallbackMessage=uCallbackMessage;
	nid.hIcon=hIcon;

	if(szTip)
		lstrcpyn(nid.szTip, szTip, sizeof(nid.szTip));
	else
		nid.szTip[0] = '\0';

	res = Shell_NotifyIcon(dwMessage, &nid);

	if(hIcon)
		DestroyIcon(hIcon);

	return res;
}
BOOL TrayMessageID(HWND hWnd, UINT uID, DWORD dwMessage, UINT uCallbackMessage, HICON hIcon, UINT uIDTip)
{
	TCHAR szTip[256];
	LoadString(GetModuleHandle(NULL),uIDTip,szTip,256);
	return TrayMessage(hWnd,uID,dwMessage,uCallbackMessage,hIcon,szTip);
}

BOOL NotifyIconAdd(HWND hWnd, UINT uID, UINT uCallbackMessage, HICON hIcon, PSTR szTip)
{
	return TrayMessage(hWnd, uID, NIM_ADD, uCallbackMessage, hIcon, szTip);
}

BOOL NotifyIconAddID(HWND hWnd, UINT uID, UINT uCallbackMessage, HICON hIcon, UINT uIDTip)
{
	return TrayMessageID(hWnd, uID, NIM_ADD, uCallbackMessage, hIcon, uIDTip);
}

BOOL NotifyIconDelete(HWND hWnd, UINT uID)
{
	return TrayMessage(hWnd, uID, NIM_DELETE, 0, NULL, NULL);
}

BOOL NotifyIconModify(HWND hWnd, UINT uID, UINT uCallbackMessage, HICON hIcon, PSTR szTip)
{
	return TrayMessage(hWnd, uID, NIM_MODIFY, uCallbackMessage, hIcon, szTip);
}

BOOL NotifyIconModifyID(HWND hWnd, UINT uID, UINT uCallbackMessage, HICON hIcon, UINT uIDTip)
{
	return TrayMessageID(hWnd, uID, NIM_MODIFY, uCallbackMessage, hIcon, uIDTip);
}

#endif // __LANG2LANG_H__

#ifndef __DDXHOTKEY_H__
#define __DDXHOTKEY_H__

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

#endif // __DDXHOTKEY_H__
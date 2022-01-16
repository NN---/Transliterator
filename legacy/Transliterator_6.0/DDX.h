#ifndef __DDX_H__
#define __DDX_H__

#define DDX_RE_EX(nID,str) \
	if(nCtlID == (UINT)-1 || nCtlID == nID) \
		DDX_RE_Ex(m_hWnd, nID,str,bSaveAndValidate);

template<typename T,typename TTraits,typename TAlloc>
inline BOOL DDX_RE_Ex(
	HWND hWnd,
	UINT nID,
	std::basic_string<T,TTraits,TAlloc>& strText,
	BOOL bSave)
{
	BOOL bRet = TRUE;
	HWND hWndCtrl = ::GetDlgItem(hWnd,nID);
	
	if(bSave)
	{
		size_t nLen = (size_t)::GetWindowTextLength(hWndCtrl)+1;

		typedef typename std::basic_string<T,TTraits,TAlloc>::value_type value_type;
		value_type* pstr;
		pstr = (value_type*)malloc(nLen*sizeof(value_type));
		if(!pstr)
		{
			strText.clear();
			return FALSE;
		}

		GETTEXTEX gte = 
		{
			nLen*sizeof(value_type),
			GT_DEFAULT,
			1200
		};

		::SendMessage(hWndCtrl,EM_GETTEXTEX,(WPARAM)&gte,(LPARAM)pstr);

		try
		{
			strText = pstr;
		}
		catch(...)
		{
			bRet = FALSE;
		}
		free(pstr);
	}
	else
	{
		SETTEXTEX ste = 
		{
			ST_DEFAULT,
			1200
		};

		::SendMessage(hWndCtrl,EM_SETTEXTEX,(WPARAM)&ste,(LPARAM)strText.c_str());
	}
	return bRet;
}

#endif // __DDX_H__
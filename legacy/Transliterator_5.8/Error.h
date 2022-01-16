#ifndef __ERROR_H____
#define __ERROR_H____

#ifndef IDS_ERROR
#define IDS_ERROR 62000
#define IDS_ERROR_DEFINED
#endif // !IDS_ERROR

inline int ShowError(HWND hWnd, _U_STRINGorID Text,
	UINT uType = MB_OK|MB_ICONEXCLAMATION, _U_STRINGorID Caption = IDS_ERROR)
{ return AtlMessageBox(hWnd,Text,Caption,uType); }

inline int ShowError(_U_STRINGorID Text,
	UINT uType = MB_OK|MB_ICONEXCLAMATION, _U_STRINGorID Caption = IDS_ERROR)
{ return ShowError(NULL,Text,uType,Caption); }

#ifdef IDS_ERROR_DEFINED
#undef IDS_ERROR
#undef IDS_ERROR_DEFINED
#endif // IDS_ERROR_DEFINED

#endif // __ERROR_H____

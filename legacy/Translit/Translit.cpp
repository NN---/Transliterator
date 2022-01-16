#include "StdAfx.h"
#include "Resource.h"

#include "TranslitDlg.h"

int Run()
{
	CMessageLoop theLoop;
	_Module.AddMessageLoop(&theLoop);

	CTranslitDlg dlgTranslit;
	int nRet=0;

	// Registry
	dlgTranslit.LoadRegistry();
	
	if(!dlgTranslit.Show())
	{
		// Show Error
		return 0;
	}
	nRet = theLoop.Run();

	_Module.RemoveMessageLoop();
	return nRet;
}

HMODULE LoadRichEditLibrary()
{
	// LoadLibrary
	HMODULE hRichEdit=LoadLibrary("riched20.dll");
	if(!hRichEdit)
	{
//		ShowError(IDE_RICHED20);
		ATLTRACE("Error");
		hRichEdit=LoadLibrary("riched32.dll");
		if(!hRichEdit)
		{
//			ShowError(IDE_RICHED32);
			ATLTRACE("Error");
		}
	}
	return hRichEdit;
}

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR /*lpstrCmdLine*/, int /*nCmdShow*/)
{
	// Only one instance !
	HANDLE hMutex=NULL;
	BOOL bFound=FALSE;
	hMutex = ::CreateMutex(NULL, TRUE, _T("Plan"));
    if(GetLastError() == ERROR_ALREADY_EXISTS)
        bFound = TRUE;
    if(hMutex)
		::ReleaseMutex(hMutex);
	if(bFound)
		return FALSE;

	HRESULT hRes = ::CoInitialize(NULL);
	ATLASSERT(SUCCEEDED(hRes));

	// this resolves ATL window thunking problem when Microsoft Layer for Unicode (MSLU) is used
	::DefWindowProc(NULL, 0, 0, 0L);

	if(!LoadRichEditLibrary())
		ATLTRACE("Error");
	AtlInitCommonControls(0x4F);	// add flags to support other controls

	hRes = _Module.Init(NULL, hInstance);
	ATLASSERT(SUCCEEDED(hRes));

	int nRet = Run();
	_Module.Term();
	::CoUninitialize();

#ifdef _DEBUG
	_Translit.~Translit();
	_CrtDumpMemoryLeaks();
#endif // _DEBUG

	return nRet;
}

// Translit.cpp : main source file for Translit.exe
//

#include "StdAfx.h"
#include "Resource.h"

#include "TranslitDlg.h"

int Run(LPCSTR /*lpstrCmdLine*/, int /*nCmdShow*/)
{
	CMessageLoop theLoop;
	_Module.AddMessageLoop(&theLoop);

	CTranslitDlg dlgTranslit;
	int nRet=0;

	// Registry
	dlgTranslit.LoadRegistry();
	
	if(!dlgTranslit.Show())
	{
		ShowError(_T("Cannot create main window"));
		return 0;
	}
	nRet = theLoop.Run();

	_Module.RemoveMessageLoop();
	return nRet;
}

HMODULE LoadRichEditLibrary()
{
	HMODULE hRichEdit=LoadLibrary("riched20.dll");
	if(!hRichEdit)
		ShowError(_T("Cannot load \"riched20.dll\""));
	return hRichEdit;
}

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR lpstrCmdLine, int nCmdShow)
{
	// One Instance
	if(NN::SetOneInstance(_T("Translit")))
		return 0;

	// RichEdit Library
	if(!LoadRichEditLibrary())
		return 0;

	HRESULT hRes = ::CoInitialize(NULL);
	ATLASSERT(SUCCEEDED(hRes));

	::DefWindowProc(NULL, 0, 0, 0L);

	AtlInitCommonControls(0xFF);	// add flags to support other controls

	hRes = _Module.Init(NULL, hInstance);
	ATLASSERT(SUCCEEDED(hRes));

	int nRet = Run(lpstrCmdLine,nCmdShow);

	_Module.Term();
	::CoUninitialize();

#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif // _DEBUG

	return nRet;
}

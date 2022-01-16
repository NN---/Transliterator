#include "stdafx.h"
#include "resource.h"
//#include "transliteratordlg.h"

//
#include "translate.h"
#include "types.h"
#include "langprofile.h"
#include "language.h"
#include "error.h"
//

#include <stdio.h>

int Run()
{
	Language l;
	l.Reset();
	wchar_t x[1000]=L"**SCh'A**";
	wchar_t y[1000];

	l.Translate(x,y,Translate::dir1_2,l.GetProfile(0));
	/*	CMessageLoop theLoop;
	_Module.AddMessageLoop(&theLoop);

	CTransliteratorDlg dlgTransliterator;
	int nRet=0;

	if(!dlgTransliterator.Show())
	{
		ShowError(_T("Cannot create main window"));
		return 0;
	}
	nRet = theLoop.Run();

	_Module.RemoveMessageLoop();
	return nRet;*/
	return 0;
}

HMODULE LoadRichEditLibrary()
{
	HMODULE hRichEdit=LoadLibrary("riched20.dll");
	if(!hRichEdit)
		ShowError(_T("Cannot load \"riched20.dll\""));
	return hRichEdit;
}

//int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpstrCmdLine*/, int /*nCmdShow*/)
int main()
{
	//
	HMODULE hInstance = GetModuleHandle(NULL);
	//

	// One Instance
	if(NN::SetOneInstance(_T("Transliterator")))
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

	int nRet = Run();

	_Module.Term();
	::CoUninitialize();

#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif // _DEBUG

	return nRet;
}

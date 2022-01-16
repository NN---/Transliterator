#include "stdafx.h"

#include "resource.h"
#include "error.h"
#include "global.h"
#include "settings.h"

#include "transliteratordlg.h"

int Run()
{
	WTL::CMessageLoop theLoop;
	_Module.AddMessageLoop(&theLoop);

	TransliteratorDlg dlgTransliterator;
	int nRet = 0;

	if(!dlgTransliterator.Show())
	{
		ShowError(_T("Cannot create main window"));
		_Module.RemoveMessageLoop();
		return 0;
	}
	nRet = theLoop.Run();

	_Module.RemoveMessageLoop();

	return nRet;
}

HMODULE LoadRichEditLibrary()
{
	HMODULE hRichEdit = ::LoadLibrary(_T("riched20.dll"));
	if(!hRichEdit)
		ShowError(_T("Cannot load riched20.dll"));
	return hRichEdit;
}

int Main(HINSTANCE hInstance)
{
	// One Instance
	if(NN::SetOneInstance(_T("Transliterator 6.0")))
	{
		ShowError(IDS_TRANSLITERATOR_IS_RUNNING);
		return 0;
	}

	// RichEdit Library
	if(!LoadRichEditLibrary())
		return 0;

	if(!Settings::Load())
		return 0;
	
	HRESULT hRes = ::CoInitialize(NULL);
	ATLASSERT(SUCCEEDED(hRes));

	::DefWindowProc(NULL, 0, 0, 0L);

	WTL::AtlInitCommonControls(0xFF);	// add flags to support other controls

	hRes = _Module.Init(NULL, hInstance);
	ATLASSERT(SUCCEEDED(hRes));

	int nRet = Run();

	Settings::Save();
	
	_Module.Term();
	::CoUninitialize();

#ifdef _DEBUG
	g_Language.~Language();
	for(size_t i = 0;i<2; ++i)
		g_Text[i].clear();
	_CrtDumpMemoryLeaks();
#endif // _DEBUG

	return nRet;
}

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpstrCmdLine*/, int /*nCmdShow*/)
{
	try
	{
		return Main(hInstance);
	}
	catch(...)
	{
		return -1;
	}
}

// RusHeb.cpp : main source file for RusHeb.exe
//

#include "stdafx.h"

#include "resource.h"

CAppModule _Module;

#define MAX_SYMBOL 1000

class CRusHebDlg : public CDialogImpl<CRusHebDlg>,
				public CWinDataExchange<CRusHebDlg>
{
public:
	enum { IDD = IDD_RUSHEB };

	CRichEditCtrl m_reRusHeb[2];
	enum { Rus , Heb };

	BOOL bNew;

    BEGIN_DDX_MAP(CRusHebDlg)
		DDX_CHECK(IDC_NEW, bNew)
	END_DDX_MAP()

	BEGIN_MSG_MAP(CRusHebDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
		COMMAND_HANDLER(IDC_RUS, EN_CHANGE, OnEnChange)
		COMMAND_HANDLER(IDC_HEB, EN_CHANGE, OnEnChange)

		COMMAND_RANGE_HANDLER(ID_EDIT_CLEAR,ID_EDIT_REDO,OnEditCommands)

		NOTIFY_HANDLER(IDC_RUS, EN_MSGFILTER, OnEnMsgFilter)
		NOTIFY_HANDLER(IDC_HEB, EN_MSGFILTER, OnEnMsgFilter)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		// center the dialog on the screen
		CenterWindow();
		for(int i=0;i<2;i++)
		{
			m_reRusHeb[i]=GetDlgItem(IDC_RUS+i);
			m_reRusHeb[i].LimitText(MAX_SYMBOL-1);
			m_reRusHeb[i].SetEventMask(ENM_CHANGE|ENM_MOUSEEVENTS);
		}
		bNew=TRUE;
		DoDataExchange(DDX_LOAD);

		return TRUE;
	}

	LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		EndDialog(0);
		return 0;
	}

	LRESULT OnEnChange(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		static bool bT;
		if(!bT)
		{
			NN::AutoSGRef<bool> sg(bT,true,false);

			NN::AutoArray<wchar_t> textIn(MAX_SYMBOL);
			NN::AutoArray<wchar_t> textOut(MAX_SYMBOL);

			bool bRus=wID==IDC_RUS;

			CRichEditCtrl reFrom=m_reRusHeb[bRus?Rus:Heb];
			CRichEditCtrl reTo=m_reRusHeb[bRus?Heb:Rus];

			DoDataExchange(DDX_SAVE);

			reFrom.GetTextEx((LPTSTR)textIn.GetData(),MAX_SYMBOL-1,GT_DEFAULT,1200);
			Translate(textIn.GetData(),textOut.GetData(),bRus,bNew?true:false);
			reTo.SetTextEx((LPCTSTR)textOut.GetData(),ST_DEFAULT,1200);
		}
		
		return 0;
	}

	LRESULT OnEnMsgFilter(int /*code*/, NMHDR *pnmhdr, BOOL& /*bHandled*/)
	{
		MSGFILTER *pMsgFilter=(MSGFILTER *)pnmhdr;
		if(pMsgFilter->msg==WM_RBUTTONDOWN)
		{
			::SetFocus(pMsgFilter->nmhdr.hwndFrom);
			POINT pt;
			::GetCursorPos(&pt);
			HMENU hMenu=::LoadMenu(_AtlBaseModule.GetResourceInstance(),MAKEINTRESOURCE(IDR_POPUP));
			hMenu=::GetSubMenu(hMenu,0);
			::TrackPopupMenu(hMenu,TPM_LEFTALIGN|TPM_LEFTBUTTON|
				TPM_RIGHTBUTTON,pt.x,pt.y,0,m_hWnd,NULL);
		}
		return 0;
	}

	LRESULT OnEditCommands(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		CRichEditCtrl re=GetFocus();
		switch(wID)
		{
			case ID_EDIT_UNDO: re.Undo(); break;
			case ID_EDIT_REDO: re.Redo(); break;
			case ID_EDIT_CUT: re.Cut(); break;
			case ID_EDIT_COPY: re.Copy(); break;
			case ID_EDIT_PASTE: re.Paste(); break;
			case ID_EDIT_SELECT_ALL: re.SetSelAll(); break;
			case ID_EDIT_CLEAR_ALL: re.SetSel(0, -1);
			case ID_EDIT_CLEAR: re.Clear(); break;
		}
		return 0;
	}

	static void Translate(const wchar_t* pIn,wchar_t* pOut,bool bRustoHeb,bool bNew)
	{
		for(int in=0,out=0;in<lstrlenW(pIn);in++)
		{
			if(pIn[in]==L'\n'||
				pIn[in]==L'\r')
			{
				pOut[out]=pIn[in];
				out++;
				continue;
			}
			if(pIn[in]<32)
				continue;
			if(bRustoHeb)
			{
				if(bNew)
				{
					if(pIn[in]<0x430||pIn[in]>0x44F)
						pOut[out]=pIn[in];
					else
						pOut[out]=pIn[in]+(0x5D0-0x430); // 'alef' - 'A'
				}
				else
				{
					if(pIn[in]<0x420||pIn[in]>0x44F)
						pOut[out]=pIn[in];
					else
						pOut[out]=pIn[in]+(0x5D0-0x420); // 'alef' - 'P'
				}
			}
			else
			{
				if(bNew)
				{
					if(pIn[in]<0x5D0||pIn[in]>0x5EA)
						pOut[out]=pIn[in];
					else
						pOut[out]=pIn[in]-(0x5D0-0x430); // 'alef' - 'A'
				}
				else
				{
					if(pIn[in]<0x5D0||pIn[in]>0x5EA)
						pOut[out]=pIn[in];
					else
						pOut[out]=pIn[in]-(0x5D0-0x420); // 'alef' - 'P'
				}
			}
			out++;
		}
		pOut[out]=0;
	}
};

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR /*lpstrCmdLine*/, int /*nCmdShow*/)
{
	// RichEdit Library
	if(!LoadLibrary(_T("riched20.dll")))
		return 0;

	HRESULT hRes = ::CoInitialize(NULL);
// If you are running on NT 4.0 or higher you can use the following call instead to 
// make the EXE free threaded. This means that calls come in on a random RPC thread.
//	HRESULT hRes = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
	ATLASSERT(SUCCEEDED(hRes));

	// this resolves ATL window thunking problem when Microsoft Layer for Unicode (MSLU) is used
	::DefWindowProc(NULL, 0, 0, 0L);

	AtlInitCommonControls(0xff);	// add flags to support other controls

	hRes = _Module.Init(NULL, hInstance);
	ATLASSERT(SUCCEEDED(hRes));

	int nRet = 0;
	// BLOCK: Run application
	{
		CRusHebDlg dlgMain;
		nRet = dlgMain.DoModal();
	}

	_Module.Term();
	::CoUninitialize();

	return nRet;
}

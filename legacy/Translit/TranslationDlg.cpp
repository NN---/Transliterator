#include "StdAfx.h"
#include "Resource.h"

#include "TranslationDlg.h"

void CTranslationDlg::UpdateTranslation()
{
	AutoArray<TCHAR> szTranslation(_MAX_CHAR);
	MakeTranslation(szTranslation.GetData());

	AutoArray<WCHAR> szwTranslation(_MAX_CHAR);
	::MultiByteToWideChar(1251,0,szTranslation.GetData(),_MAX_CHAR,szwTranslation.GetData(),_MAX_CHAR);
	m_richeditTranslation.SetTextEx((LPTSTR)szwTranslation.GetData(),ST_DEFAULT,1200);
}

void CTranslationDlg::MakeTranslation(LPTSTR szTranslation)
{
	Translit tempTranslit;
	TCHAR szText[40];

	szTranslation[0]=0;
	
	for(int i=0;i<2;i++)
	{
		tempTranslit.SetData(_Translit);
		tempTranslit.Sort(true,(bool)i);
		
		AtlLoadString(IDS_ENGTORUS+i,szText,40);
		lstrcat(szTranslation,szText);
		lstrcat(szTranslation,_T("\n"));
		for(unsigned nItem=0;nItem<_Translit.GetLast()-1;nItem++)
		{
			lstrcat(szTranslation,
				((EngRusArray*)tempTranslit[nItem].Get((bool)i))->GetData());
			lstrcat(szTranslation,_T(" - "));
			lstrcat(szTranslation,
				((EngRusArray*)tempTranslit[nItem].Get((bool)!i))->GetData());
			lstrcat(szTranslation,_T("\n"));
		}
		if(!i)
			lstrcat(szTranslation,_T("\n"));
	}
}

LRESULT CTranslationDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	m_richeditTranslation=GetDlgItem(IDC_TRANSLATION);
	m_richeditTranslation.SendMessage(EM_SETLIMITTEXT,_MAX_CHAR-1,0);
	m_richeditTranslation.SetEventMask(ENM_KEYEVENTS);
	m_richeditTranslation.SetFocus();
	return 0;
}

LRESULT CTranslationDlg::OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	::SendMessage(GetParent(),WM_COMMAND,MAKEWPARAM(ID_TOOLS_TRANSLATION,BN_CLICKED),NULL);
	return 0;
}

LRESULT CTranslationDlg::OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
	::MoveWindow(GetDlgItem(IDC_TRANSLATION),0,0,GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam),TRUE);
	return 0;
}

LRESULT CTranslationDlg::OnOK(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	return 0;
}

LRESULT CTranslationDlg::OnCancel(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	::SendMessage(GetParent(),WM_COMMAND,MAKEWPARAM(ID_TOOLS_TRANSLATION,BN_CLICKED),NULL);
	return 0;
}

LRESULT CTranslationDlg::OnEnMsgFilterTranslation(int /*code*/, NMHDR* pnmhdr, BOOL& /*bHandled*/)
{
	MSGFILTER *pMsgFilter=(MSGFILTER *)pnmhdr;
	if(pMsgFilter->msg==WM_KEYDOWN&&pMsgFilter->wParam==VK_ESCAPE)
			::SendMessage(GetParent(),WM_COMMAND,MAKEWPARAM(ID_TOOLS_TRANSLATION,BN_CLICKED),NULL);
	return 0;
}
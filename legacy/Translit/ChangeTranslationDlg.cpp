#include "StdAfx.h"
#include "Resource.h"

#include "ChangeTranslationDlg.h"

void CChangeTranslationDlg::SetCmbEngRus(bool b1,LPCTSTR szText/*=NULL*/)
{
	Translit tempTranslit;
	int iCmb;
	
	if(szText)
	{
		EngRusTuple tuple;
		((EngRusArray*)tuple.Get(b1))->SetData(szText);
		unsigned nFind=0;
		for(unsigned nItem=0;nItem<m_Translit.GetLast();nItem++,nFind++)
		{
			nFind=m_Translit.Find(tuple,nFind,b1);
			if(nFind==(unsigned)-1)
				break;
			else
				tempTranslit.Add(m_Translit[nFind]);
		}
		iCmb=!b1;
	}
	else
	{
		for(unsigned nItem=0;nItem<m_Translit.GetLast();nItem++)
			if(tempTranslit.Find(m_Translit[nItem],0,b1)==(unsigned)-1)
				tempTranslit.Add(m_Translit[nItem]);
		iCmb=b1;
	}
	
	m_cmbEngRus[iCmb].ResetContent();
	if(!tempTranslit.GetLast())
		return;
	tempTranslit.Sort(true,b1);
	
	for(unsigned nItem=0;nItem<tempTranslit.GetLast();nItem++)
		m_cmbEngRus[iCmb].AddString(
			((EngRusArray*)tempTranslit[nItem].Get(iCmb))->GetData());
}

void CChangeTranslationDlg::InitCmbEngRus()
{
	SetCmbEngRus(false);
	SetCmbEngRus(true);
}

void CChangeTranslationDlg::UpdateEngRusCheck(const EngRusTuple* pTuple/*=NULL*/)
{
	BOOL bEnable=FALSE;
	BOOL bEngtoRus=FALSE;
	BOOL bRustoEng=FALSE;
	if(pTuple)
	{
		bEnable=pTuple->t0[0]&&pTuple->t1[0];
		if(bEnable)
		{
			Translate::EngRusTranslate translate=m_Translit[m_Translit.Find(*pTuple)].t2;
			bEngtoRus=translate&Translate::EngtoRus;
			bRustoEng=translate&Translate::RustoEng;
		}
	}
	::EnableWindow(GetDlgItem(IDC_ENGTORUS),bEnable);
	::EnableWindow(GetDlgItem(IDC_RUSTOENG),bEnable);
	CheckDlgButton(IDC_ENGTORUS,bEngtoRus);
	CheckDlgButton(IDC_RUSTOENG,bRustoEng);
}

LRESULT CChangeTranslationDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	DialogLang_Init();
	DoDataExchange(DDX_LOAD);
	for(int i=0;i<4;i++)
		SendDlgItemMessage(IDC_FROMENG+i,EM_SETLIMITTEXT,(WPARAM)(Options::nNotTranslate-1));
	for(int i=0;i<2;i++)
	{
		m_cmbEngRus[i]=GetDlgItem(IDC_ENG+i);
		m_cmbEngRus[i].LimitText(EngRusArray::nCountInit-1);
	}
	InitCmbEngRus();
	return 0;
}

LRESULT CChangeTranslationDlg::OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(wID==IDOK)
		DoDataExchange(DDX_SAVE);
	EndDialog(wID);
	return 0;
}

LRESULT CChangeTranslationDlg::OnAddRemove(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	EngRusTuple tuple;
	
	m_cmbEngRus[Eng].GetWindowText(tuple.Get<0>().GetData(),EngRusArray::nCountInit);
	m_cmbEngRus[Rus].GetWindowText(tuple.Get<1>().GetData(),EngRusArray::nCountInit);

	if(!tuple.Get<0>()[0]&&!tuple.Get<1>()[0])
		return 0;

	if(wID==IDC_ADD)
	{
		tuple.Get<2>()=Translate::None;
		if(IsDlgButtonChecked(IDC_ENGTORUS))
			(int&)tuple.Get<2>()|=Translate::EngtoRus;
		if(IsDlgButtonChecked(IDC_RUSTOENG))
			(int&)tuple.Get<2>()|=Translate::RustoEng;
		unsigned nFind=m_Translit.Find(tuple);
		if(nFind==(unsigned)-1)
			m_Translit.Add(tuple);
		else
			m_Translit[nFind].Get<2>()=tuple.Get<2>();
	}
	else
		m_Translit.Remove(tuple);

	InitCmbEngRus();
	UpdateEngRusCheck(NULL);

	return 0;
}

LRESULT CChangeTranslationDlg::OnClearReset(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(wID==IDC_RESET)
	{
		// Are you sure ?
		TCHAR szText[30];
		TCHAR szCaption[10];

		AtlLoadString(IDS_AREYOUSURE,szText,sizeof(szText)/sizeof(TCHAR));
		AtlLoadString(IDS_RESET,szCaption,sizeof(szCaption)/sizeof(TCHAR));

		if(MessageBox(szText,szCaption,MB_YESNO)==IDYES)
			m_Translit.Default();
	}
	m_cmbEngRus[Eng].Clear();
	m_cmbEngRus[Rus].Clear();
	UpdateEngRusCheck(NULL);
	return 0;
}

LRESULT CChangeTranslationDlg::OnEngRus(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	return 0;
}

LRESULT CChangeTranslationDlg::OnChangeEngRus(WORD wNotifyCode, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	int i1= wID!=IDC_ENG;
	EngRusTuple tuple;
	if(wNotifyCode==CBN_SELCHANGE)
	{
		m_cmbEngRus[i1].GetLBText(m_cmbEngRus[i1].GetCurSel(),((EngRusArray*)tuple.Get(i1))->GetData());
		m_cmbEngRus[!i1].GetWindowText(((EngRusArray*)tuple.Get(!i1))->GetData(),EngRusArray::nCountInit);
	}
	else
	{
		m_cmbEngRus[Eng].GetWindowText(tuple.Get<0>().GetData(),EngRusArray::nCountInit);
		m_cmbEngRus[Rus].GetWindowText(tuple.Get<1>().GetData(),EngRusArray::nCountInit);
	}
	
	if(!tuple.Get<0>()[0]&&!tuple.Get<1>()[0])
	{
		m_nUse=useNone;
		UpdateEngRusCheck(NULL);
		InitCmbEngRus();
		return 0;
	}

	Use useThis=!i1?useEng:useRus;
	if(m_nUse==useNone)
		m_nUse=useThis;

	if(m_nUse==useEng&&!tuple.t0[0]||
		m_nUse==useRus&&!tuple.t1[0])
	{
		m_nUse=m_nUse==useEng?useRus:useEng;
		bool b1=m_nUse==useRus;
		SetCmbEngRus(b1,
			((EngRusArray*)tuple.Get(b1))
			->GetData());
	}

	if(m_nUse==useThis)
	{
		SetCmbEngRus(i1,
			((EngRusArray*)tuple.Get(i1))
			->GetData());
	}
	
	UpdateEngRusCheck(&tuple);

	return 0;
}
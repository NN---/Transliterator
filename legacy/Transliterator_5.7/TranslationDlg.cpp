#include "stdafx.h"
#include "resource.h"

#include "translationdlg.h"

void CTranslationDlg::UpdateCmbProfile()
{
	CComboBox cmbProfile=GetDlgItem(IDC_PROFILE);
	InitCmbLanguage(cmbProfile);
	char strAll[50];
	::LoadString(_AtlBaseModule.GetResourceInstance(),IDS_ALL,strAll,sizeof(strAll)/sizeof(strAll[0]));
	cmbProfile.AddString(strAll);
	cmbProfile.SetCurSel(m_nCurProfile);
}

void CTranslationDlg::UpdateLanguage()
{
	NN::DialogLang<CTranslationDlg>::UpdateLanguage();
	UpdateTranslation();
	UpdateCmbProfile();
}

void CTranslationDlg::UpdateCurProfile()
{
	m_nCurProfile=g_Options.m_nCurProfile;
	UpdateTranslation();
	UpdateCmbProfile();
}

void CTranslationDlg::UpdateTranslation()
{
	const int nSize=TranslationCount()+1000;
	NN::AutoArray<char> aText(nSize);
	if(!aText.GetData())
		return;
	MakeTranslation(aText.GetData());

	NN::AutoArray<wchar_t> awText(nSize);
	if(!awText.GetData())
		return;
	::MultiByteToWideChar(1251,0,aText.GetData(),nSize,awText.GetData(),nSize);

	m_reTranslation.SetTextEx((LPTSTR)awText.GetData(),ST_DEFAULT,1200);
	m_reTranslation.HideSelection(true,TRUE);
	m_reTranslation.LineScroll(0);
}

void CTranslationDlg::MakeTranslation(LPTSTR strTranslation)
{
	strTranslation[0]=0;

	char strText[2][40];
	for(int i=0;i<2;i++)
		AtlLoadString(IDS_TRNSTORUS+i,strText[i],40);
	Translate::LangTranslate translate[2]={Translate::trnsTrnstoRus,Translate::trnsRustoTrns};

	LangMap map;

	for(int iProfile=0;iProfile<Language::nProfiles;iProfile++)
	{
		if(m_nCurProfile!=Language::nProfiles&&
			m_nCurProfile!=iProfile)
			continue;
			
		LangProfile* pProfile=g_Language.GetProfile((Language::Profiles)iProfile);
		map.SetData(pProfile->m_map);

		if(!map.GetLast())
		{
			lstrcat(strTranslation,pProfile->m_strName);
			lstrcat(strTranslation,":\r\n");
			continue;
		}

		for(int i=0;i<2;i++)
		{
			lstrcat(strTranslation,pProfile->m_strName);
			lstrcat(strTranslation,":\r\n");
			lstrcat(strTranslation,strText[i]);
			lstrcat(strTranslation,":\r\n");

			map.Sort(true,(bool)i);
			for(unsigned nItem=0;nItem<map.GetLast();nItem++)
			{
				if(!(map[nItem].Get<2>()&translate[i]))
					continue;
				lstrcat(strTranslation,
					((LangString*)map[nItem].Get((bool)i))->GetData());
				lstrcat(strTranslation," - ");
				lstrcat(strTranslation,
					((LangString*)map[nItem].Get((bool)!i))->GetData());
				lstrcat(strTranslation,"\r\n");
			}
			if(!i)
				lstrcat(strTranslation,"\r\n");
		}
		lstrcat(strTranslation,"\r\n");
	}
}

size_t CTranslationDlg::TranslationCount()
{
	size_t nCount=0;
	size_t nrn=lstrlen("\r\n");

	size_t nText[2];
	for(int i=0;i<2;i++)
		nText[i]=AtlLoadString(IDC_TRNSTORUS+i,0,0);
	Translate::LangTranslate translate[2]={Translate::trnsTrnstoRus,Translate::trnsRustoTrns};

	LangMap map;

	for(int iProfile=0;iProfile<Language::nProfiles;iProfile++)
	{
		LangProfile* pProfile=g_Language.GetProfile((Language::Profiles)iProfile);

		map.SetData(pProfile->m_map);

		if(!map.GetLast())
		{
			nCount+=lstrlen(pProfile->m_strName)+1;
			continue;
		}

		for(int i=0;i<2;i++)
		{
			nCount+=lstrlen(pProfile->m_strName)+nrn+1;
			nCount+=nText[i]+nrn;

			map.Sort(true,(bool)i);
			for(unsigned nItem=0;nItem<map.GetLast()-1;nItem++)
			{
				if(!(map[nItem].Get<2>()&translate[i]))
					continue;
				nCount+=lstrlen(((LangString*)map[nItem].Get((bool)i))->GetData());
				nCount+=lstrlen(" - ");
				nCount+=lstrlen(((LangString*)map[nItem].Get((bool)!i))->GetData());
				nCount+=nrn;
			}
			if(!i)
				nCount+=nrn;
		}
		nCount+=nrn;
	}
	return nCount;
}

LRESULT CTranslationDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	DialogLang_Init();
	DlgResize_Init();
	
	m_reTranslation=GetDlgItem(IDC_TRANSLATION);
	m_reTranslation.SetEventMask(ENM_KEYEVENTS);
	m_reTranslation.SetFocus();

	m_nCurProfile=Language::nProfiles;
	UpdateCmbProfile();

	return 0;
}

LRESULT CTranslationDlg::OnShowWindow(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	static bool bInit;
	if(wParam&&!bInit)
	{
		bInit=true;
		UpdateTranslation();
	}
	return 0;
}

LRESULT CTranslationDlg::OnChangeProfile(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	m_nCurProfile=SendDlgItemMessage(IDC_PROFILE,CB_GETCURSEL,0,0);
	UpdateTranslation();
	return 0;
}

LRESULT CTranslationDlg::OnEnMsgFilterTranslation(int /*code*/, NMHDR* pnmhdr, BOOL& /*bHandled*/)
{
	MSGFILTER *pMsgFilter=(MSGFILTER *)pnmhdr;
	if(pMsgFilter->msg==WM_KEYDOWN&&pMsgFilter->wParam==VK_ESCAPE)
		CloseDialog();
	return 0;
}
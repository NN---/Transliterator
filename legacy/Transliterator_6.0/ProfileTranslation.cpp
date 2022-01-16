#include "stdafx.h"
#include "resource.h"

#include "makedirection.h"
#include "compare.h"
#include "ddx.h"
#include "msg.h"

#include "profiletranslation.h"

const Translate::Translation ProfileTranslation::s_aTranslation[2] = 
{
	Translate::trnsToptoBottom,
	Translate::trnsBottomtoTop
};
const ProfileTranslation::Column ProfileTranslation::s_clLang[2] = 
{
	clLangTop,
	clLangBottom
};

void ProfileTranslation::DialogLang_LanguageChanged()
{
	UpdateLang();
	UpdateHeaders();
}

void ProfileTranslation::UpdateLang()
{
	LangStringT aDir[2];
	MakeDirection::MakeT(aDir,GetOptions()->m_pProfile);

	for(size_t i=0; i<2; ++i)
	{
		SetDlgItemText(IDC_LBLLANGTOP+i,
			GetOptions()->m_pProfile->m_astrLang[i].c_str());
		SetDlgItemText(IDC_CHKLANGTOPTOLANGBOTTOM+i,
			aDir[i].c_str());
	}
}

void ProfileTranslation::UpdateHeaders()
{
	for(size_t i=0; i<2; ++i)
	{
		LVCOLUMN lvcolumn = {};
		lvcolumn.mask = LVCF_TEXT;

		m_lvTranslation.GetColumn(s_clLang[i],&lvcolumn);
		
		const LangStringT& strLang = GetOptions()->m_pProfile->m_astrLang[i];
		lvcolumn.cchTextMax = (int)strLang.length();
		lvcolumn.pszText = (LPTSTR)strLang.c_str();

		m_lvTranslation.SetColumn(s_clLang[i],&lvcolumn);
	}
}

void ProfileTranslation::UpdateTranslation()
{
	m_lvTranslation.DeleteAllItems();

	const LangArray& aTranslation = GetOptions()->m_pProfile->m_aTranslation;
	if(aTranslation.empty())
	{
		m_nCurItem = -1;
		return;
	}

	int nItem = 0;
	for(LangArray::const_iterator it = aTranslation.begin();
		it != aTranslation.end();
		it++,nItem++)
	{
		m_lvTranslation.InsertItem(nItem,_T(""));

		m_lvTranslation.SetItem(
			nItem,
			clLangTop,
			LVIF_TEXT,
			NN::CharAWT<const TCHAR>(it->get<LangPos::Top>().c_str()),
			0,
			0,
			0,
			0);
		m_lvTranslation.SetItem(
			nItem,
			clLangBottom,
			LVIF_TEXT,
			NN::CharAWT<const TCHAR>(it->get<LangPos::Bottom>().c_str()),
			0,
			0,
			0,
			0);

		if(it->get<LangPos::Translation>() & (int)Translate::trnsToptoBottom)
			m_lvTranslation.SetItem(
				nItem,
				clLangToptoLangBottom,
				LVIF_TEXT,
				MakeDirection::DirT(),
				0,
				0,
				0,
				0);

		if(it->get<LangPos::Translation>() & (int)Translate::trnsBottomtoTop)
			m_lvTranslation.SetItem(
				nItem,
				clLangBottomtoLangTop,
				LVIF_TEXT,
				MakeDirection::DirBackT(),
				0,
				0,
				0,
				0);

	}

	if(m_nCurItem>(int)aTranslation.size())
		m_nCurItem = (int)aTranslation.size();
	
	LoadData();
}

void ProfileTranslation::LoadData()
{
	if(m_nCurItem == -1)
		return;

	const LangType& langitem = GetOptions()->m_pProfile->m_aTranslation[m_nCurItem];

	m_reLang[0].SetTextEx(
		(LPCTSTR)langitem.get<LangPos::Top>().c_str(),
		ST_DEFAULT,
		1200);
	m_reLang[1].SetTextEx(
		(LPCTSTR)langitem.get<LangPos::Bottom>().c_str(),
		ST_DEFAULT,
		1200);
	
	for(size_t i=0; i<2; ++i)
		CheckDlgButton(IDC_CHKLANGTOPTOLANGBOTTOM+i,
			langitem.get<LangPos::Translation>() & (int)s_aTranslation[i]);
}

void ProfileTranslation::SaveData()
{
	try
	{
		LangType item(L"",L"",Translate::trnsNone);

		for(size_t i=0; i<2; ++i)
			if(IsDlgButtonChecked(IDC_CHKLANGTOPTOLANGBOTTOM+i))
				(int&)item.get<LangPos::Translation>() |=  s_aTranslation[i];
		
		if(item.get<LangPos::Translation>() == Translate::trnsNone||
			(!m_reLang[0].GetTextLength()&&!m_reLang[1].GetTextLength()))
			return;
	
		DDX_RE_Ex(m_hWnd, IDC_RELANGTOP,item.get<LangPos::Top>(),TRUE);
		DDX_RE_Ex(m_hWnd, IDC_RELANGBOTTOM,item.get<LangPos::Bottom>(),TRUE);

		LangArray& aTranslation = GetOptions()->m_pProfile->m_aTranslation;

		LangArray::iterator it = aTranslation.begin();
		for(;it != aTranslation.end(); ++it)
			if(CompareLangType<true>(*it,item))
				break;
		if(it == aTranslation.end())
		{
			aTranslation.push_back(item);
			m_nCurItem = (int)aTranslation.size()-1;
		}
		else
		{
			it->get<LangPos::Translation>() = item.get<LangPos::Translation>();
			m_nCurItem = (int)std::distance(aTranslation.begin(),it);
		}
		
		UpdateTranslation();

		m_lvTranslation.SelectItem(m_nCurItem);
		m_lvTranslation.SetFocus();
	}
	catch(...)
	{
	}
}

LRESULT ProfileTranslation::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// InitLV
	m_lvTranslation = GetDlgItem(IDC_LVTRANSLATION);
	// Style
	m_lvTranslation.SetExtendedListViewStyle(LVS_EX_FULLROWSELECT| LVS_EX_GRIDLINES);
	// Columns
	m_lvTranslation.InsertColumn(clLangTop,_T(""),LVCFMT_LEFT,70,-1);
	m_lvTranslation.InsertColumn(clLangToptoLangBottom,MakeDirection::DirT(),LVCFMT_CENTER,40,-1);
	m_lvTranslation.InsertColumn(clLangBottomtoLangTop,MakeDirection::DirBackT(),LVCFMT_CENTER,40,-1);
	m_lvTranslation.InsertColumn(clLangBottom,_T(""),LVCFMT_LEFT,70,-1);

	// InitRE
	for(size_t i=0; i<2; ++i)
	{
		m_reLang[i] = GetDlgItem(IDC_RELANGTOP+i);
		m_reLang[i].SetEventMask(ENM_CHANGE);
	}

	return 0;
}

LRESULT ProfileTranslation::OnActivate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	InvalidateRect(NULL,FALSE);

	return 0;
}

LRESULT ProfileTranslation::OnAdd(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	SaveData();

	GetParent().SendMessage(UWM_PROFILEUPDATE);

	return 0;
}

LRESULT ProfileTranslation::OnDelete(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(m_nCurItem == -1)
		return 0;
	
	LangArray& aTranslation = GetOptions()->m_pProfile->m_aTranslation;
	
	LangArray::iterator it = aTranslation.begin();
	std::advance(it,m_nCurItem);
	aTranslation.erase(it);
	
	m_lvTranslation.DeleteItem(m_nCurItem);
	if(!m_lvTranslation.GetItemCount())
		m_nCurItem = -1;

	UpdateTranslation();
	m_lvTranslation.SelectItem(m_nCurItem);
	m_lvTranslation.SetFocus();

	GetParent().SendMessage(UWM_PROFILEUPDATE);

	return 0;
}

LRESULT ProfileTranslation::OnEnChangeLang(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(!m_bChange)
		return 0;

	LangType item(L"", L"", Translate::trnsNone);
	
	const bool l1 =  wID == IDC_RELANGTOP;
	LangString& itemstr = l1?item.get<LangPos::Top>():item.get<LangPos::Bottom>();

	DDX_RE_Ex(m_hWnd, wID,itemstr,TRUE);
	if(!itemstr.length())
		return 0;

	const LangArray& aTranslation = GetOptions()->m_pProfile->m_aTranslation;
	size_t len = itemstr.length();
	LangArray::const_iterator itfind;
	while(len)
	{
		itfind = 
			l1?
			std::find_if(
				aTranslation.begin(),
				aTranslation.end(),
				CompareSearchLangTop(item,len)):
			std::find_if(
				aTranslation.begin(),
				aTranslation.end(),
				CompareSearchLangBottom(item,len));
		if(itfind != aTranslation.end())
			break;
		--len;
	}
	if(!len)
		return 0;

	LangArray::const_iterator it = aTranslation.begin();
	int nItem = (int)std::distance(it,itfind);
	m_lvTranslation.SelectItem(nItem);
	m_nCurItem = nItem;

	return 0;
}

LRESULT ProfileTranslation::OnKeyDownLVTranslation(int /*code*/, NMHDR* pnmhdr, BOOL& /*bHandled*/)
{
	NMLVKEYDOWN* pnmkeydown = (NMLVKEYDOWN*)pnmhdr;

	const int nLastItem = m_lvTranslation.GetItemCount()-1;
	switch(pnmkeydown->wVKey)
	{
		case VK_UP:
			if(m_nCurItem)
				m_nCurItem--;
			break;
		case VK_DOWN:
			if(m_nCurItem != nLastItem)
				m_nCurItem++;
			break;
		case VK_NEXT:
			m_nCurItem+= eNextPage;
			if(m_nCurItem>nLastItem)
				m_nCurItem = nLastItem;
			break;
		case VK_PRIOR:
			m_nCurItem-= eNextPage;
			if(m_nCurItem<0)
				m_nCurItem = 0;
			break;
		case VK_HOME:
			m_nCurItem = 0;
			break;
		case VK_END:
			m_nCurItem = nLastItem;
			break;
		default:
			return 0;
	}

	m_lvTranslation.SetSelectionMark(m_nCurItem);
	
	m_bChange = false;
	LoadData();
	m_bChange = true;

	return 0;
}

LRESULT ProfileTranslation::OnClickLVTranslation(int /*code*/, NMHDR* pnmhdr, BOOL& /*bHandled*/)
{
	NMITEMACTIVATE* pnmitem = (NMITEMACTIVATE*)pnmhdr;
	if(pnmitem->iItem != -1)
	{
		m_nCurItem = pnmitem->iItem;
		
		m_bChange = false;
		LoadData();
		m_bChange = true;
	}

	return 0;
}
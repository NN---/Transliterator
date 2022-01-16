#include "stdafx.h"

#include "resource.h"
#include "makedirection.h"
#include "compare.h"
#include "ddx.h"
#include "msg.h"

#include "profileignore.h"

const Translate::Translation ProfileIgnore::s_aTranslation[2] = 
{
	Translate::trnsToptoBottom,
	Translate::trnsBottomtoTop
};

void ProfileIgnore::DialogLang_LanguageChanged()
{
	UpdateLang();

	LVCOLUMN lvcolumn = {};
	lvcolumn.mask = LVCF_TEXT;
    m_lvIgnoreText.GetColumn(clText,&lvcolumn);

	LangStringT strText;
	NN::WndGetText(GetDlgItem(IDC_LBLTEXT),strText);
	lvcolumn.cchTextMax = (int)strText.length();
	lvcolumn.pszText = (LPTSTR)strText.c_str();

	m_lvIgnoreText.SetColumn(clText,&lvcolumn);
}

void ProfileIgnore::UpdateLang()
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

void ProfileIgnore::UpdateIgnoreText()
{
	m_lvIgnoreText.DeleteAllItems();

	const IgnoreTextArray& aIgnoreText = GetOptions()->m_pProfile->m_aIgnoreText;
	if(aIgnoreText.empty())
	{
		m_nCurItem = -1;
		return;
	}

	int nItem = 0;
	for(IgnoreTextArray::const_iterator it = aIgnoreText.begin();
		it != aIgnoreText.end();
		it++,nItem++)
	{
		m_lvIgnoreText.InsertItem(nItem,NULL);

		m_lvIgnoreText.SetItem(
			nItem,
			clText,
			LVIF_TEXT,
			NN::CharAWT<const TCHAR>(it->get<IgnoreTextPos::String>().c_str()),
			0,
			0,
			0,
			0);

		if(it->get<IgnoreTextPos::Translation>() & (int)Translate::trnsToptoBottom)
			m_lvIgnoreText.SetItem(
				nItem,
				clLangToptoLangBottom,
				LVIF_TEXT,
				MakeDirection::DirT(),
				0,
				0,
				0,
				0);
		
		if(it->get<IgnoreTextPos::Translation>() & (int)Translate::trnsBottomtoTop)
			m_lvIgnoreText.SetItem(
				nItem,
				clLangBottomtoLangTop,
				LVIF_TEXT,
				MakeDirection::DirBackT(),
				0,
				0,
				0,
				0);
	}

	if(m_nCurItem>(int)aIgnoreText.size())
		m_nCurItem = (int)aIgnoreText.size();
	
	LoadData();
}

void ProfileIgnore::LoadData()
{
	if(m_nCurItem == -1)
		return;

	const IgnoreTextType& item = GetOptions()->m_pProfile->m_aIgnoreText[m_nCurItem];

	m_reText.SetTextEx(
		(LPCTSTR)item.get<IgnoreTextPos::String>().c_str(),
		ST_DEFAULT,
		1200);
	
	for(size_t i=0; i<2; ++i)
		CheckDlgButton(IDC_CHKLANGTOPTOLANGBOTTOM+i,
			item.get<IgnoreTextPos::Translation>() & (int)s_aTranslation[i]);
}

void ProfileIgnore::SaveData()
{
	try
	{
		IgnoreTextType item(L"",Translate::trnsNone);

		for(size_t i=0; i<2; ++i)
			if(IsDlgButtonChecked(IDC_CHKLANGTOPTOLANGBOTTOM+i))
				(int&)item.get<IgnoreTextPos::Translation>() |=  s_aTranslation[i];
		
		if(item.get<IgnoreTextPos::Translation>() == Translate::trnsNone||
			!m_reText.GetTextLength())
			return;
	
		DDX_RE_Ex(
			m_hWnd,
			IDC_RETEXT,
			item.get<IgnoreTextPos::String>(),
			TRUE);

		IgnoreTextArray& aIgnoreText = GetOptions()->m_pProfile->m_aIgnoreText;

		IgnoreTextArray::iterator it = aIgnoreText.begin();
		for(;it != aIgnoreText.end(); ++it)
			if(CompareIgnore(*it,item))
				break;
		if(it == aIgnoreText.end())
		{
			aIgnoreText.push_back(item);
			m_nCurItem = (int)aIgnoreText.size()-1;
		}
		else
		{
			it->get<IgnoreTextPos::Translation>()  = 
				item.get<IgnoreTextPos::Translation>();
			m_nCurItem = (int)std::distance(aIgnoreText.begin(),it);
		}
		
		UpdateIgnoreText();

		m_lvIgnoreText.SelectItem(m_nCurItem);
		m_lvIgnoreText.SetFocus();
	}
	catch(...)
	{
	}

}

LRESULT ProfileIgnore::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// InitLV
	m_lvIgnoreText = GetDlgItem(IDC_LVIGNORETEXT);
	// Style
	m_lvIgnoreText.SetExtendedListViewStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	// Columns
	m_lvIgnoreText.InsertColumn(
		clText,
		_T(""),
		LVCFMT_LEFT,
		70,
		-1);
	m_lvIgnoreText.InsertColumn(
		clLangToptoLangBottom,
		MakeDirection::DirT(),
		LVCFMT_CENTER,
		40,
		-1);
	m_lvIgnoreText.InsertColumn(
		clLangBottomtoLangTop,
		MakeDirection::DirBackT(),
		LVCFMT_CENTER,
		40,
		-1);

	// InitRE
	m_reText = GetDlgItem(IDC_RETEXT);
	m_reText.SetEventMask(ENM_CHANGE);

	return 0;
}

LRESULT ProfileIgnore::OnActivate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	InvalidateRect(NULL,FALSE);

	return 0;
}

LRESULT ProfileIgnore::OnAdd(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	SaveData();

	GetParent().SendMessage(UWM_PROFILEUPDATE);

	return 0;
}

LRESULT ProfileIgnore::OnDelete(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(m_nCurItem == -1)
		return 0;
	
	IgnoreTextArray& aIgnoreText = GetOptions()->m_pProfile->m_aIgnoreText;
	
	IgnoreTextArray::iterator it = aIgnoreText.begin();
	std::advance(it,m_nCurItem);
	aIgnoreText.erase(it);
	
	m_lvIgnoreText.DeleteItem(m_nCurItem);
	if(!m_lvIgnoreText.GetItemCount())
		m_nCurItem = -1;

	UpdateIgnoreText();
	m_lvIgnoreText.SelectItem(m_nCurItem);
	m_lvIgnoreText.SetFocus();

	GetParent().SendMessage(UWM_PROFILEUPDATE);

	return 0;
}

LRESULT ProfileIgnore::OnEnChangeText(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(!m_bChange)
		return 0;

	IgnoreTextType item(L"",Translate::trnsNone);
	IgnoreTextString& itemstr = item.get<IgnoreTextPos::String>();
	
	DDX_RE_Ex(m_hWnd, IDC_RETEXT,itemstr,TRUE);
	
	if(!itemstr.length())
		return 0;

	const IgnoreTextArray& aIgnoreText = GetOptions()->m_pProfile->m_aIgnoreText;
	IgnoreTextArray::const_iterator itfind;

	size_t lenI = 0;
	for(lenI = itemstr.length(); lenI; --lenI)
	{
		itfind = std::find_if
			(
				aIgnoreText.begin(),
				aIgnoreText.end(),
				CompareSearchIgnoreText(item,lenI)
			);
		
		if(itfind != aIgnoreText.end())
			break;
	}
	if(!lenI)
		return 0;

	int nItem = (int)std::distance(aIgnoreText.begin(),itfind);
	m_lvIgnoreText.SelectItem(nItem);
	m_nCurItem = nItem;
		
	return 0;
}

LRESULT ProfileIgnore::OnKeyDownLVIgnoreText(int /*code*/, NMHDR* pnmhdr, BOOL& /*bHandled*/)
{
	NMLVKEYDOWN* pnmkeydown = (NMLVKEYDOWN*)pnmhdr;

	const nLastItem = m_lvIgnoreText.GetItemCount()-1;
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

	m_lvIgnoreText.SetSelectionMark(m_nCurItem);

	m_bChange = false;
	LoadData();
	m_bChange = true;

	return 0;
}

LRESULT ProfileIgnore::OnClickLVIgnoreText(int /*code*/, NMHDR* pnmhdr, BOOL& /*bHandled*/)
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
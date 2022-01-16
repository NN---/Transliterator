#ifndef __IGNOREPAGE_H__
#define __IGNOREPAGE_H__

#include "trnsoptionspage.h"

class CIgnorePage : public TrnsOptionsPage<CIgnorePage>
{
public:
	enum { IDD=IDD_PAGEIGNORE };

	CRichEditCtrl m_reIgnore;
	CListBox m_lbIgnore;
	enum { Trns , Rus };
	enum { nTrnsRus = 50 };
	enum { CP = 1251 };
	char m_strTrnsRus[2][nTrnsRus];

	void UpdateLanguage()
	{
		TrnsOptionsPage<CIgnorePage>::UpdateLanguage();
		UpdateTrnsRusString();
		InitListIgnore();
	}

	void UpdateTrnsRusString()
	{
		for(int i=0;i<2;i++)
		::LoadString(_AtlBaseModule.GetResourceInstance(),
				IDS_TRANSLIT+i,m_strTrnsRus[i],nTrnsRus-1);
	}

	void InitListIgnore()
	{
		m_lbIgnore.ResetContent();
		char strText[IgnoreString::nCountInit+40];
		const Ignore& rIgnore=GetOptions()->m_Ignore;
		for(unsigned i=0;i<rIgnore.GetLast();i++)
		{
			lstrcpy(strText,rIgnore[i].Get<0>().GetData());
			if(rIgnore[i].Get<1>() != Translate::trnsNone)
			{
				lstrcat(strText," - ");
				if((int)rIgnore[i].Get<1>() & (int)Translate::trnsTrnstoRus)
					lstrcat(strText,m_strTrnsRus[Trns]);
				if((int)rIgnore[i].Get<1>() & (int)Translate::trnsRustoTrns)
				{
					lstrcat(strText,",");
					lstrcat(strText,m_strTrnsRus[Rus]);
				}
			}
			m_lbIgnore.AddString(strText);
		}
	}

	void Init()
	{
		InitListIgnore();
		m_reIgnore.SetWindowText("");
		CheckDlgButton(IDC_TRNSTORUS,FALSE);
		CheckDlgButton(IDC_RUSTOTRNS,FALSE);
	}

	unsigned FindIgnore(const char* str)
	{
		static const Translate::LangTranslate aMapLT[]=
		{
			Translate::trnsNone,
			Translate::trnsTrnstoRus,
			Translate::trnsRustoTrns,
			Translate::trnsAll,
		};
		
		IgnoreType type;
		type.Get<0>()=str;

		for(int i=0;i<sizeof(aMapLT)/sizeof(aMapLT[0]);i++)
		{
			type.Get<1>()=aMapLT[i];
			unsigned uFind=GetOptions()->m_Ignore.Find(type);
			if(uFind!=(unsigned)-1)
				return uFind;	
		}
		return (unsigned)-1;
	}

	BEGIN_DDX_MAP(CIgnorePage)
		if(!bSaveAndValidate)
		{
			Init();
		}
	END_DDX_MAP()

	BEGIN_MSG_MAP(CIgnorePage)
		CHAIN_MSG_MAP(TrnsOptionsPage<CIgnorePage>)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)

		COMMAND_HANDLER(IDC_LISTIGNORE,LBN_SELCHANGE, OnLbnSelChangeListIgnore)

		COMMAND_ID_HANDLER(IDC_ADD, OnAddRemoveClear)
		COMMAND_ID_HANDLER(IDC_REMOVE, OnAddRemoveClear)
		COMMAND_ID_HANDLER(IDC_CLEAR, OnAddRemoveClear)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		m_lbIgnore=GetDlgItem(IDC_LISTIGNORE);
		m_reIgnore=GetDlgItem(IDC_IGNORE);
		SendDlgItemMessage(IDC_IGNORE,EM_LIMITTEXT,(WPARAM)IgnoreString::nCountInit-1,0);
		UpdateTrnsRusString();

		return 0;
	}

	LRESULT OnLbnSelChangeListIgnore(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		char strText[IgnoreString::nCountInit];
		wchar_t strTextW[IgnoreString::nCountInit];

		IgnoreType& type=GetOptions()->m_Ignore[m_lbIgnore.GetCurSel()];
		lstrcpy(strText,type.Get<0>().GetData());

		::MultiByteToWideChar(CP,0,strText,IgnoreString::nCountInit-1,strTextW,IgnoreString::nCountInit-1);

		m_reIgnore.SetTextEx((LPCSTR)strTextW,ST_DEFAULT,1200);

		CheckDlgButton(IDC_TRNSTORUS,type.Get<1>()&Translate::trnsTrnstoRus);
		CheckDlgButton(IDC_RUSTOTRNS,type.Get<1>()&Translate::trnsRustoTrns);

		return 0;
	}

	LRESULT OnAddRemoveClear(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		Ignore& rIgnore=GetOptions()->m_Ignore;
		switch(wID)
		{
			case IDC_ADD:
				{
					IgnoreType type;

					wchar_t wstr[IgnoreString::nCountInit];
					m_reIgnore.GetTextEx((LPSTR)wstr,(IgnoreString::nCountInit-1)*sizeof(wchar_t),GT_DEFAULT,1200);
					if(!wstr[0])
						break;

					::WideCharToMultiByte(CP,0,wstr,IgnoreString::nCountInit-1,type.Get<0>().GetData(),
						IgnoreString::nCountInit-1,0,0);

					unsigned uFind=FindIgnore(type.Get<0>().GetData());
					if(uFind!=(unsigned)-1)
					{
						rIgnore[uFind].Get<0>()=type.Get<0>();
						Translate::LangTranslate& lt=rIgnore[uFind].Get<1>();
						lt=Translate::trnsNone;
						if(IsDlgButtonChecked(IDC_TRNSTORUS))
							(int&)lt|= (int)Translate::trnsTrnstoRus;
						if(IsDlgButtonChecked(IDC_RUSTOTRNS))
							(int&)lt|= (int)Translate::trnsRustoTrns;
					}
					else
					{
						type.Get<1>()=Translate::trnsNone;
						if(IsDlgButtonChecked(IDC_TRNSTORUS))
							(int&)type.Get<1>()|= (int)Translate::trnsTrnstoRus;
						if(IsDlgButtonChecked(IDC_RUSTOTRNS))
							(int&)type.Get<1>()|= (int)Translate::trnsRustoTrns;
						rIgnore.Add(type);
					}
				}
				break;
			case IDC_REMOVE:
				{
					unsigned cursel = (unsigned)m_lbIgnore.GetCurSel();
					if(cursel!=(unsigned)LB_ERR)
						rIgnore.RemoveAt(cursel);
				}
				break;
			case IDC_CLEAR:
				rIgnore.RemoveAll();
				break;
		}
		InitListIgnore();

		return 0;
	}
};

#endif // __IGNOREPAGE_H__
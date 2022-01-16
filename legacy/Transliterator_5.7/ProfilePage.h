#ifndef __PROFILEPAGE_H__
#define __PROFILEPAGE_H__

#include "trnsoptionspage.h"

class CProfilePage : public TrnsOptionsPage<CProfilePage>
{
public:
	enum { IDD=IDD_PAGEPROFILE };

	int m_nCurSel;
	CComboBox m_cmbTrnsRus[2];
	CComboBox m_cmbProfile;
	enum { Trns , Rus };

	enum Use { useNone, useEng, useRus };
	NN::AutoValue<Use,useNone> m_nUse;

	Language& GetLanguage()
	{ return GetOptions()->m_Language; }
	LangProfile* GetProfile(int nProfile)
	{
		return nProfile<Language::profUser1?
			g_Language.GetProfile((Language::Profiles)nProfile):
			GetLanguage().GetProfile(
				(Language::Profiles)(nProfile-Language::profUser1));
	}
	LangProfile* GetProfile()
	{ return GetLanguage().GetProfile((Language::Profiles)(m_nCurSel+Language::profUser1)); }

	void InitProfile()
	{
		InitCmbLanguageUser(GetDlgItem(IDC_PROFILE),0,GetLanguage());
		InitCmbLanguageDefUser(GetDlgItem(IDC_COPYFROM),0,GetLanguage());
	}

	void UpdateLanguage()
	{
		NN::DialogLang<CProfilePage>::UpdateLanguage();
		InitProfile();
	}
	
	typedef NN::StaticArray<LangString,LangMap::nCountInit> LangStringArray;

	void SetTrnsRus(bool b1,const char* strText=NULL)
	{
		LangStringArray aLangString;

		int iCmb;
		unsigned last=0;

		if(strText)
		{
			iCmb=b1;
			LangString lstr(strText);
			
			for(unsigned nItem=0;nItem<GetProfile()->m_map.GetLast();nItem++)
			{
				if(lstr==*(LangString*)GetProfile()->m_map[nItem].Get(b1))
					aLangString[last++]=*(LangString*)GetProfile()->m_map[nItem].Get(!b1);
			}
			iCmb=!b1;
		}
		else
		{
			for(unsigned i=0;i<GetProfile()->m_map.GetLast();i++)
			{
				LangString* plstr = (LangString*)GetProfile()->m_map[i].Get(b1);
				if(aLangString.Find(*plstr)==(unsigned)-1)
					aLangString[last++]=*plstr;
			}
			iCmb=b1;
		}

		if(last)
			aLangString.Sort(true,last-1);

		m_cmbTrnsRus[iCmb].ResetContent();
		
		for(unsigned i=0;i<last;i++)
			m_cmbTrnsRus[iCmb].AddString(aLangString[i].GetData());
	}

	void InitTrnsRus()
	{
		SetTrnsRus(true);
		SetTrnsRus(false);
	}

	void InitIgnore()
	{
		for(int i=0;i<LangProfile::nBeginEnd;i++)
			SendDlgItemMessage(IDC_BEGINTRNS+i,EM_LIMITTEXT,(WPARAM)LangProfile::nIgnore,0);
	}

	void LoadIgnore()
	{
		for(int i=0;i<LangProfile::nBeginEnd;i++)
			SetDlgItemText(IDC_BEGINTRNS+i,GetProfile()->m_strIgnore[i]);
	}

	void SaveIgnore()
	{
		for(int i=0;i<LangProfile::nBeginEnd;i++)
			GetDlgItemText(IDC_BEGINTRNS+i,GetProfile()->m_strIgnore[i],LangProfile::nIgnore-1);
	}

	void UpdateCheck(const LangType* pType)
	{
		BOOL bEnable=FALSE;
		BOOL bTrnstoRus=FALSE;
		BOOL bRustoTrns=FALSE;
		if(pType)
		{
			bEnable=pType->Get<0>()[0]&&pType->Get<1>()[0];
			if(bEnable)
			{
				unsigned nFind=GetProfile()->m_map.Find(*pType);
				if(nFind!=(unsigned)-1)
				{
					LangType& rType=GetProfile()->m_map[nFind];
					bTrnstoRus=(int)rType.Get<2>()&(int)Translate::trnsTrnstoRus;
					bRustoTrns=(int)rType.Get<2>()&(int)Translate::trnsRustoTrns;
				}
			}
		}
		::EnableWindow(GetDlgItem(IDC_TRNSTORUS),bEnable);
		::EnableWindow(GetDlgItem(IDC_RUSTOTRNS),bEnable);
		CheckDlgButton(IDC_TRNSTORUS,bTrnstoRus);
		CheckDlgButton(IDC_RUSTOTRNS,bRustoTrns);
	}

	void Clear()
	{
		for(int i=0;i<2;i++)
			m_cmbTrnsRus[i].SetCurSel(-1);
		UpdateCheck(NULL);
	}

	void InitAll(bool bProfile=true)
	{
		if(bProfile)
			InitProfile();
		InitTrnsRus();
		LoadIgnore();
		LoadProfileName();
		Clear();
	}

	void SaveProfileName()
	{
		GetDlgItemText(IDC_PROFILENAME,GetProfile()->m_strName,LangProfile::nName-1);
	}

	void LoadProfileName()
	{
		SetDlgItemText(IDC_PROFILENAME,GetProfile()->m_strName);
	}

	void SplitStr(const char* str,char* l,char* r)
	{
		splitstr(str,l,r,LangString::nCountInit-1,LangString::nCountInit-1,'=');
	}

	BEGIN_DDX_MAP(CProfilePage)
		if(bSaveAndValidate==DDX_LOAD)
		{
			InitAll();
		}
		else
		{
			SaveIgnore();
			SaveProfileName();
		}
		DDX_CHECK(IDC_COPYIGNORE,GetOptions()->m_Options.m_bCopyIgnore)
	END_DDX_MAP()

	BEGIN_MSG_MAP(CProfilePage)
		CHAIN_MSG_MAP(TrnsOptionsPage<CProfilePage>)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)

		COMMAND_HANDLER(IDC_PROFILE,CBN_SELCHANGE,OnCmbSelChangeProfile)
		COMMAND_HANDLER(IDC_PROFILENAME, EN_CHANGE, OnEnChangeProfileName)

		COMMAND_HANDLER(IDC_TRNS,CBN_SELCHANGE, OnChangeTrnsRus)
		COMMAND_HANDLER(IDC_RUS,CBN_SELCHANGE, OnChangeTrnsRus)
		COMMAND_HANDLER(IDC_TRNS, CBN_EDITCHANGE, OnChangeTrnsRus)
		COMMAND_HANDLER(IDC_RUS, CBN_EDITCHANGE, OnChangeTrnsRus)

		COMMAND_ID_HANDLER(IDC_ADD, OnAddRemove)
		COMMAND_ID_HANDLER(IDC_REMOVE, OnAddRemove)
		COMMAND_ID_HANDLER(IDC_CLEAR, OnClear)

		COMMAND_ID_HANDLER(IDC_COPY, OnCopy)
		
		COMMAND_ID_HANDLER(IDC_RESET, OnReset)
		COMMAND_ID_HANDLER(IDC_RESETALL, OnReset)

		COMMAND_ID_HANDLER(IDC_LOAD, OnLoadSave)
		COMMAND_ID_HANDLER(IDC_SAVE, OnLoadSave)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		m_nCurSel=0;
		for(int i=0;i<2;i++)
		{
			m_cmbTrnsRus[i]=GetDlgItem(IDC_TRNS+i);
			m_cmbTrnsRus[i].LimitText(LangString::nCountInit-1);
		}
		m_cmbProfile = GetDlgItem(IDC_PROFILE);
		SendDlgItemMessage(IDC_PROFILENAME,EM_LIMITTEXT,(WPARAM)LangProfile::nName-1,0);
		InitIgnore();
		return 0;
	}

	LRESULT OnCmbSelChangeProfile(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		m_nCurSel=m_cmbProfile.GetCurSel();
		InitTrnsRus();
		LoadProfileName();
		return 0;
	}

	LRESULT OnEnChangeProfileName(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		GetDlgItemText(IDC_PROFILENAME,GetProfile()->m_strName,LangProfile::nName-1);
		InitProfile();
		m_cmbProfile.SetCurSel(m_nCurSel);
		LoadIgnore();
		return 0;
	}

	LRESULT OnChangeTrnsRus(WORD wNotifyCode, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		int i1= wID!=IDC_TRNS;
	
		LangType type;

		if(wNotifyCode==CBN_SELCHANGE)
		{
			m_cmbTrnsRus[i1].GetLBText(m_cmbTrnsRus[i1].GetCurSel(),((LangString*)type.Get(i1))->GetData());
			m_cmbTrnsRus[!i1].GetWindowText(((LangString*)type.Get(!i1))->GetData(),LangString::nCountInit);
		}
		else
		{
			m_cmbTrnsRus[Trns].GetWindowText(type.Get<0>().GetData(),LangString::nCountInit);
			m_cmbTrnsRus[Rus].GetWindowText(type.Get<1>().GetData(),LangString::nCountInit);
		}

		if(!type.Get<0>()[0]&&!type.Get<1>()[0])
		{
			UpdateCheck(NULL);
			InitTrnsRus();
			return 0;
		}
		else
		{
			if(!*((LangString*)type.Get(!i1))->GetData())
				SetTrnsRus(i1,((LangString*)type.Get(i1))->GetData());
		}

		UpdateCheck(&type);

		return 0;
	}

	LRESULT OnAddRemove(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		LangType type;
	
		m_cmbTrnsRus[Trns].GetWindowText(type.Get<0>().GetData(),LangString::nCountInit);
		m_cmbTrnsRus[Rus].GetWindowText(type.Get<1>().GetData(),LangString::nCountInit);

		if(!type.Get<0>()[0]&&!type.Get<1>()[0])
			return 0;

		bool bAdd= wID==IDC_ADD;
		if(bAdd)
		{
			type.Get<2>()=Translate::trnsNone;
			if(IsDlgButtonChecked(IDC_TRNSTORUS))
				(int&)type.Get<2>()|=(int)Translate::trnsTrnstoRus;
			if(IsDlgButtonChecked(IDC_RUSTOTRNS))
				(int&)type.Get<2>()|=(int)Translate::trnsRustoTrns;
			unsigned nFind=GetProfile()->m_map.Find(type);
			if(nFind==(unsigned)-1)
				GetProfile()->m_map.Add(type);
			else
				GetProfile()->m_map[nFind].Get<2>()=type.Get<2>();
		}
		else
		{
			GetProfile()->m_map.Remove(type);
		}

		InitTrnsRus();
		if(bAdd)
		{
			GetProfile()->m_map.Find(type);
			UpdateCheck(&type);
		}
		else
			UpdateCheck(NULL);

		return 0;
	}

	LRESULT OnClear(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		Clear();
		return 0;
	}

	LRESULT OnCopy(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		int iFrom=SendDlgItemMessage(IDC_COPYFROM,CB_GETCURSEL);

		LangProfile* pFrom=GetProfile(iFrom);

		char strName[LangProfile::nName];
		lstrcpy(strName,GetProfile()->m_strName);
		memcpy(GetProfile(),pFrom,sizeof(LangProfile));
		lstrcpy(GetProfile()->m_strName,strName);

		InitAll();

		return 0;
	}

	LRESULT OnReset(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		if(wID==IDC_RESET)
			GetOptions()->m_Language.ResetProfile((Language::Profiles)m_nCurSel);
		else
			GetOptions()->m_Language.ResetUser();
		InitAll();
		return 0;
	}

	LRESULT OnLoadSave(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		BOOL bLoad=wID==IDC_LOAD;
		CFileDialog dlgFile(bLoad,"txt","",OFN_OVERWRITEPROMPT,"Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0",m_hWnd);
		if(dlgFile.DoModal()!=IDOK)
			return 0;
		
		// Test file
		CAtlFile file;
		if(file.Create(dlgFile.m_szFileName,bLoad?GENERIC_READ:GENERIC_WRITE,0,bLoad?OPEN_EXISTING:CREATE_ALWAYS))
		{
			ShowError(m_hWnd,"Error opening file");
			return 0;
		}
		if(!bLoad)
			file.SetSize(0);
		file.Close();

		static const unsigned size_string=LangString::nCountInit*2+1;
		static const unsigned size_section=(size_string)*LangMap::nCountInit;

		static const char strProfileName[]="Profile Name";
		static const char strName[]="Name";
		static const char astrIgnore[][30]=
		{
			"Translit Ignore Symbols",
			"Russian Ignore Symbols"
		};
		static const char astrBeginEnd[][10]=
		{
			"Begin",
			"End"
		};
		static const char astrTranslation[][20]=
		{
			"Translit to Russian",
			"Russian to Translit",
			"No Translate"
		};
		static const Translate::LangTranslate aTranslation[]=
		{
			Translate::trnsTrnstoRus,
			Translate::trnsRustoTrns,
			Translate::trnsNone
		};

		if(bLoad)
		{
			LangProfile profile;
			// Name
			GetPrivateProfileString(strProfileName,strName,"",
				profile.m_strName,LangProfile::nName-1,
				dlgFile.m_szFileName);
			// Ignore
			for(int i=0;i<LangProfile::nBeginEnd;i++)
				GetPrivateProfileString(
					astrIgnore[(i>>1)&1],
					astrBeginEnd[i&1],
					"",
					profile.m_strIgnore[i],
					LangProfile::nIgnore-1,
					dlgFile.m_szFileName);

			// Translation
			NN::AutoArray<char> section(size_section);
			for(int i=0;i<3;i++)
			{
				GetPrivateProfileSection(
					astrTranslation[i],
					section.GetData(),
					size_section,
					dlgFile.m_szFileName);

                if(!section[0])
					continue;

				const char* pstr;
				pstr=section.GetData();
				
				char left[LangString::nCountInit];
				char right[LangString::nCountInit];

				while(pstr[0]&&pstr[1])
				{
					SplitStr(pstr,left,right);
					if(left[0]&&right[0])
					{
						LangType type(
							i==1?right:left,
							i==1?left:right);
						unsigned nFind=profile.m_map.Find(type);
						if(nFind==(unsigned)-1)
						{
							((int&)type.Get<2>())=(int)aTranslation[i];
							profile.m_map.Add(type);
						}
						else
						{
							if(aTranslation[i]!=Translate::trnsNone)
								((int&)profile.m_map[nFind].Get<2>())|=(int)aTranslation[i];
							else
								profile.m_map[nFind].Get<2>()=Translate::trnsNone;
						}
					}
					pstr+=lstrlen(pstr)+1;
				}
			}
			
			// Load
			// Name
			if(profile.m_strName[0])
				lstrcpy(GetProfile()->m_strName,profile.m_strName);
			for(int i=0;i<LangProfile::nBeginEnd;i++)
				if(profile.m_strIgnore[i][0])
					lstrcpy(GetProfile()->m_strIgnore[i],profile.m_strIgnore[i]);
			if(profile.m_map.GetLast())
				GetProfile()->m_map.SetData(profile.m_map);
			
			// Update
			InitProfile();
			LoadIgnore();
			SetDlgItemText(IDC_PROFILENAME,GetProfile()->m_strName);
			InitTrnsRus();
		}
		else
		{
			// Name
			WritePrivateProfileString(
					strProfileName,
					strName,
					GetProfile()->m_strName,
					dlgFile.m_szFileName);
			
			// Ignore
			for(int i=0;i<LangProfile::nBeginEnd;i++)
				WritePrivateProfileString(
					astrIgnore[(i>>1)&1],
					astrBeginEnd[i&1],
					GetProfile()->m_strIgnore[i],
					dlgFile.m_szFileName);

			// Translation
			NN::AutoArray<char> section(size_section);
			for(int i=0;i<3;i++)
			{
				char* psection=section.GetData();
				LangMap map;
				map.SetData(GetProfile()->m_map);
				
				map.Sort(true,i==1);
				for(unsigned item=0;item<map.GetLast();item++)
				{
					if((int)map[item].Get<2>()&(int)aTranslation[i])
					{
						if(i==1)
							strcpy_change(&psection,map[item].Get<1>().GetData());
						else
							strcpy_change(&psection,map[item].Get<0>().GetData());
						strcpy_change(&psection,"=");
						if(i==1)
							strcpy_change(&psection,map[item].Get<0>().GetData());
						else
							strcpy_change(&psection,map[item].Get<1>().GetData());
						*psection++=0;
					}
				}
				*psection=0;
				WritePrivateProfileSection(astrTranslation[i],
									section.GetData(),
									dlgFile.m_szFileName);
			}
		}
		return 0;
	}
};

#endif // __PROFILEPAGE_H__
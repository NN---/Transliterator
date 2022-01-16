#include "stdafx.h"

#include "resource.h"
#include "error.h"
#include "global.h"
#include "controls.h"
#include "compare.h"
#include "makedirection.h"

#include "profiledetailsdlg.h"

void ProfileDetailsDlg::DialogLang_LanguageChanged()
{
	UpdateCmbView();
	static bool bfirst = true;
	if(!bfirst)
	{
		UpdateDetails();
		bfirst = false;
	}
	UpdateCmbProfile();
}

void ProfileDetailsDlg::UpdateDetails()
{
	int nCurProfile = m_cmbProfile.GetCurSel();
	int nCurView = m_cmbView.GetCurSel();

	LangString strDetails;
	const size_t nsize  = 
		nCurProfile == profileAll ? 2000 : 500 +
		nCurView == viewAll ? 1000 : 500;
	strDetails.reserve(nsize);
	
	LangString astrView[nView];
	for(size_t i=0; i<NN::array_length(astrView); ++i)
		NN::WndLoadStringW(IDS_TRANSLATION+i,astrView[i]);

	LangString astrIgnore[2];
	for(size_t i=0; i<NN::array_length(astrIgnore); ++i)
		NN::WndLoadStringW(IDS_BEGIN+i,astrIgnore[i]);

	static const LangChar strNL[] = L"\r\n";
	static const LangChar strC[] = L":";
	static const LangChar strNLC[] = L":\r\n";

	typedef bool (*pfCompare)(const LangType&, const LangType&);
	static const pfCompare apfCompare[] = 
	{
		&CompareLangType<true>,
		&CompareLangType<false>
	};

	static const Translate::Translation translation[] = 
	{
		Translate::trnsToptoBottom,
		Translate::trnsBottomtoTop
	};
	
	for(int nProfile = 0;nProfile<Language::nProfiles;nProfile++)
	{
		// Profile
		if(nProfile != nCurProfile&&
			nCurProfile != profileAll)
			continue;
		
		const LangProfile* pProfile = g_Language.GetProfile((unsigned)nProfile);

		LangString astrDirection[nDirection];
		MakeDirection::MakeW(astrDirection,pProfile);
		
		strDetails+= NN::CharAWT<const WCHAR>(
			g_Storage.m_astrProfile[nProfile].c_str());
		strDetails+= strNLC;

		if(pProfile->m_aTranslation.empty())
			continue;

		// Translation
		if(nCurView == viewTranslation||
			nCurView == viewAll)
		{
			strDetails+= astrView[viewTranslation];
			strDetails+= strNL;

			// Direction
			for(int trns = 0;trns<2;trns++)
			{
				strDetails+= astrDirection[trns];
				strDetails+= strNLC;

				LangArray aTranslation = pProfile->m_aTranslation;
				
				std::sort(aTranslation.begin(),aTranslation.end(),apfCompare[trns]);

				for(LangArray::const_iterator it = aTranslation.begin();
					it != aTranslation.end(); ++it)
				{
					if((int)it->get<LangPos::Translation>() & translation[trns])
					{
						strDetails+= 
							translation[trns] & (int)Translate::trnsToptoBottom?
								it->get<LangPos::Top>() : it->get<LangPos::Bottom>();
						strDetails+= L" - ";
						strDetails+= 
							translation[trns] & (int)Translate::trnsToptoBottom?
								it->get<LangPos::Bottom>() : it->get<LangPos::Top>();
						strDetails+= strNL;
					}
				}
			}
		}

		// Ignore
		if(nCurView == viewIgnore||
			nCurView == viewAll)
		{
			strDetails+= astrView[viewIgnore];
			strDetails+= strNLC;

			for(size_t i=0; i<2; ++i)
			{
				strDetails+= NN::CharAWT<const WCHAR>(pProfile->m_astrLang[i].c_str());
				strDetails+= strNL;
				for(int j = 0;j<2;j++)
				{
					strDetails+= astrIgnore[j];
					strDetails+= strC;
					strDetails+= pProfile->m_astrIgnore[i+j];
					strDetails+= strNL;
				}
			}
		}

		// Ignore Text
		if(nCurView == viewIgnoreText||
			nCurView == viewAll)
		{
			if(!pProfile->m_aIgnoreText.empty()&&
				(nCurView == viewIgnoreText||
					nCurView == viewAll))
			{
				strDetails+= astrView[viewIgnoreText];
				strDetails+= strNLC;
			
				for(size_t i=0; i<2; ++i)
				{
					IgnoreTextArray aIgnoreText = pProfile->m_aIgnoreText;
					
					std::sort(aIgnoreText.begin(),aIgnoreText.end(),CompareIgnore);

					strDetails+= astrDirection[i];
					strDetails+= strNLC;

					for(IgnoreTextArray::const_iterator it = aIgnoreText.begin();
						it != aIgnoreText.end(); ++it)
						if((int)it->get<IgnoreTextPos::Translation>() & i)
							strDetails+= it->get<IgnoreTextPos::String>();
				}
			}
		}
	}

	m_reDetails.SetWindowText(_T(""));
	m_reDetails.SetTextEx((LPTSTR)strDetails.c_str(),ST_DEFAULT,1200);
	m_reDetails.HideSelection(true,TRUE);
}

void ProfileDetailsDlg::UpdateCmbProfile()
{
	InitCmbProfile(m_cmbProfile);
	LangStringT str;
	NN::WndLoadString(IDS_ALL,str);
	m_cmbProfile.AddString(str.c_str());
}

void ProfileDetailsDlg::UpdateCmbView()
{
	m_cmbView.SetCurSel(0);
}

LRESULT ProfileDetailsDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	m_reDetails = GetDlgItem(IDC_REDETAILS);
	m_reDetails.SetEventMask(ENM_KEYEVENTS);
	m_reDetails.SetFocus();

	m_cmbProfile = GetDlgItem(IDC_CMBPROFILE);
	m_cmbView = GetDlgItem(IDC_CMBVIEW);

	DlgResize_Init(false,false);
	
	return 0;
}

LRESULT ProfileDetailsDlg::OnShowWindow(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	static bool bfirst = false;
	if(wParam&&!bfirst)
	{
		bfirst = true;
		UpdateDetails();
	}
	return 0;
}

LRESULT ProfileDetailsDlg::OnChange(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	UpdateDetails();
	return 0;
}

LRESULT ProfileDetailsDlg::OnEnMsgFilterDetails(int /*code*/, NMHDR* pnmhdr, BOOL& /*bHandled*/)
{
	MSGFILTER *pMsgFilter = (MSGFILTER *)pnmhdr;
	if(pMsgFilter->msg == WM_KEYDOWN&&pMsgFilter->wParam == VK_ESCAPE)
		CloseDialog();
	return 0;
}
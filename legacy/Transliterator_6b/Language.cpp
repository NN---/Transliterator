#include "stdafx.h"
#include "language.h"
#include "global.h"
#include <nn/string.h>

void Language::ResetProfile(unsigned nProfile)
{
	typedef void (*ResetFunc)(LangProfile&);
	
	static const ResetFunc m_aResetFunc[nProfiles]=
	{
		&Language::Reset1,
		&Language::Reset2,
		&Language::Reset3,
		&Language::Reset4,
		&Language::Reset5,
		&Language::Reset6,
		&Language::Reset7,
		&Language::Reset8,
		&Language::Reset9,
	};

	(*m_aResetFunc[nProfile])(*GetProfile(nProfile));
}

void Language::Reset()
{
	for(unsigned i=0;i<nProfiles;i++)
		ResetProfile(i);
}

void Language::Translate(const wchar_t* strIn,wchar_t* strOut,
					Translate::Direction dir,LangProfile* pProfile)
{
	if(!pProfile)
		pProfile=m_pCurProfile;

	if(!strIn||!*strIn)
	{
		*strOut=0;
		return;
	}

	const int i1= dir==Translate::dir2_1;

	const wchar_t* pIn=strIn;
	wchar_t* pOut=strOut;

	// Max length
	size_t maxlenT=0;
	for(LangArray::iterator it=pProfile->m_aSymbols.begin();
		it!=pProfile->m_aSymbols.end();it++)
	{
		const LangString& rString = i1?it->get<1>():it->get<0>();
				
		if(maxlenT<rString.length())
			maxlenT=rString.length();
	}

	// Max length
	size_t maxlenI=0;
	for(IgnoreArray::iterator it=g_Ignore.begin();it!=g_Ignore.end();it++)
	{
		if(maxlenI<it->get<0>().length())
			maxlenI=it->get<0>().length();
	}
	
	while(*pIn)
	{
		if(Translate_Ignore(&pIn,&pOut,dir,pProfile))
			continue;
		if(Translate_IgnoreText(&pIn,&pOut,dir,maxlenI))
			continue;
		if(Translate_Translate(&pIn,&pOut,dir,pProfile,maxlenT))
			continue;
		if(*pIn)
			*pOut++=*pIn++;
	}
	// End
	*pOut=0;
}

bool Language::Translate_Translate(const wchar_t** ppIn,wchar_t** ppOut,
		Translate::Direction dir,LangProfile* pProfile,size_t maxlenT)
{
	// Check
	if(!**ppIn)
		return true;

	// Init
	const int i1= dir==Translate::dir2_1;

	// Translate
	for(size_t len=maxlenT;len;len--)
	{
		for(LangArray::iterator it=pProfile->m_aSymbols.begin();
			it!=pProfile->m_aSymbols.end();it++)
		{
			// Translate::LangTranslate
			const Translate::Translation& trnsItem=it->get<2>();
			if(dir==Translate::dir1_2)
			{
				if(!(trnsItem&Translate::trns1_2))
					continue;
			}
			else
			{
				if(!(trnsItem&Translate::trns2_1))
					continue;
			}
			
			const LangString& rStringIn = i1?it->get<1>():it->get<0>();
			if(rStringIn.length() == len &&
				!LangStringTraits::compare(*ppIn,rStringIn.c_str(),len))
			{
				const LangString& rStringOut = i1?it->get<0>():it->get<1>();
				NN::wstrcpy_change(ppOut,rStringOut.c_str());
				(*ppIn)+=len;
				return true;
			}
		}
	}
	return false;
}

bool Language::Translate_Ignore(const wchar_t** ppIn,wchar_t** ppOut,
		Translate::Direction dir,LangProfile* pProfile)
{
	// Check
	if(!**ppIn)
		return true;

	// Init
	const int i1= dir==Translate::dir2_1;

	const LangString& strBeginIn=
		pProfile->m_astrIgnore[i1?LangProfile::Begin2:LangProfile::Begin1];
	const LangString& strEndIn=
		pProfile->m_astrIgnore[i1?LangProfile::End2:LangProfile::End1];
	const LangString& strBeginOut=
		pProfile->m_astrIgnore[i1?LangProfile::Begin1:LangProfile::Begin2];
	const LangString& strEndOut=
		pProfile->m_astrIgnore[i1?LangProfile::End1:LangProfile::End2];	

	// Ignore
	if(!LangStringTraits::compare(*ppIn,strBeginIn.c_str(),strBeginIn.length()))
	{
		// Continue
		(*ppIn)+=strBeginIn.length();

		// Copy Ignore
		//if(g_Options.m_bCopyIgnore)
			//NN::wstrcpy_change(&pOut,strBeginOut)
		strBeginOut;

		// Copy
		while(**ppIn&&
			LangStringTraits::compare(*ppIn,strEndIn.c_str(),strEndIn.length()))
			*(*ppOut)++=*(*ppIn)++;

		if(!**ppIn)
			return true;
			
		(*ppIn)+=strEndIn.length();
		
		// Copy Ignore
		//if(g_Options.m_bCopyIgnore)
			//NN::wstrcpy_change(&pOut,strEndOut);
		strEndOut;
			
		if(!**ppIn)
			return true;
	}
	return false;
}

bool Language::Translate_IgnoreText(const wchar_t** ppIn,wchar_t** ppOut,
		Translate::Direction dir,size_t maxlenI)
{
	// Check
	if(!**ppIn)
		return true;

	// Ignore text
	for(size_t lenI=maxlenI;lenI;lenI--)
	{
		for(IgnoreArray::iterator it=g_Ignore.begin();it!=g_Ignore.end();it++)
		{
			// Check translation direction
			const Translate::Translation& trnsItem=it->get<1>();
			if(dir==Translate::dir1_2)
			{
				if(!(trnsItem&Translate::trns1_2))
					continue;
			}
			else
			{
				if(!(trnsItem&Translate::trns2_1))
					continue;
			}

			const IgnoreString& ignorestr=it->get<0>();
			if(ignorestr.length()==lenI&&
				!LangStringTraits::compare(*ppIn,ignorestr.c_str(),lenI))
			{
				NN::wstrcpy_change(ppOut,ignorestr.c_str());
				(*ppIn)+=ignorestr.length();
				return true;
			}
		}
	}
	return false;
}

		/*

void Language::Ignore(const LangStruct& ls)
{
	// Profile
	if(!ls.GetProfile())
		ls.SetProfile(m_pCurProfile);
	// Empty
	if(ls.Empty())
	{
		ls.Clear();
		return;
	}
	if(!ls.GetProfile()->m_map.GetLast())
	{
		lstrcpy(ls.GetOut(),ls.GetIn());
		return;
	}

	const char* pIn=ls.GetIn();
	char* pOut=ls.GetOut();

	const char* pFromIn = ls.GetProfile()->m_strIgnore[ls.GetDirection()==Translate::dirTrnstoRus?LangProfile::BeginTrns:LangProfile::BeginRus];
	const char* pToIn = ls.GetProfile()->m_strIgnore[ls.GetDirection()==Translate::dirTrnstoRus?LangProfile::EndTrns:LangProfile::EndRus];
	const char* pFromOut = ls.GetProfile()->m_strIgnore[ls.GetDirection()==Translate::dirTrnstoRus?LangProfile::BeginTrns:LangProfile::BeginRus];
	const char* pToOut = ls.GetProfile()->m_strIgnore[ls.GetDirection()==Translate::dirTrnstoRus?LangProfile::EndTrns:LangProfile::EndRus];

	const int nFromIn = lstrlen(pFromIn);
	const int nToIn = lstrlen(pToIn);

	NN::Tuple<char,char> aCheck[LangMap::nCountInit];
	UpdateCheck(ls.GetProfile(),aCheck);

	if(ls.GetInsert())
	{
		bool bInsert=false;
		for(size_t iChar=0;*pIn&&iChar<ls.GetCharCount();iChar++)
		{
			// Ignore
			if(!LangStringTraits::CompareArrayLength(
					pIn,pFromIn,LangProfile::nIgnore))
			{
				bInsert=true;

				pIn+=nFromIn;

				iChar+=strcpy_change(&pOut,pFromOut);
				
				while(*pIn&&LangStringTraits::CompareArrayLength(
						pIn,pToIn,LangProfile::nIgnore)&&
						iChar<ls.GetCharCount())
					*pOut++=*pIn++;
				
				if(!*pIn||iChar>=ls.GetCharCount())
					break;
				
				pIn+=nToIn;

				if(!*pIn||iChar>=ls.GetCharCount())
					break;
				
				iChar+=strcpy_change(&pOut,pToOut);

				bInsert=false;
			}
			// Text
			if(IsTrnsRus(*pIn,ls.IsTrns(),aCheck))
			{
				bInsert=true;
				
				strcpy_change(&pOut,pFromOut);

				while(*pIn&&				
					(IsTrnsRus(*pIn,ls.IsTrns(),aCheck)||
					(!IsTrns(*pIn,aCheck)&&!IsRus(*pIn,aCheck)))&&
					iChar<ls.GetCharCount())
				{
					*pOut++=*pIn++;
					iChar++;
				}

				if(!*pIn||iChar>=ls.GetCharCount())
					break;

				iChar+=strcpy_change(&pOut,pToOut);

				bInsert=false;
			}
			*pOut++=*pIn++;
		}
		if(bInsert)
			strcpy_change(&pOut,pToOut);
	}
	else
	{
		for(size_t iChar=0;*pIn&&iChar<ls.GetCharCount();iChar++)
		{
			// Ignore
			if(!LangStringTraits::CompareArrayLength(
				pIn,pFromIn,LangProfile::nIgnore))
			{
				pIn+=nFromIn;
				iChar+=nFromIn;

				while(*pIn&&
					LangStringTraits::CompareArrayLength(
						pIn,pFromIn,LangProfile::nIgnore)&&
						iChar<ls.GetCharCount())
					*pOut++=*pIn++;
					
				if(!*pIn||iChar>=ls.GetCharCount())
					break;
	
				if(!LangStringTraits::CompareArrayLength(
					pIn,pToIn,LangProfile::nIgnore))
						pIn+=nToIn;
				
				if(!*pIn||iChar>=ls.GetCharCount())
					break;
			}
			*pOut++=*pIn++;
		}
	}
	*pOut=0;
}

void Language::SetIgnore(const LangStruct& ls)
{
	// Profile
	if(!ls.GetProfile())
		ls.SetProfile(m_pCurProfile);
	if(!ls.GetProfile()->m_map.GetLast())
	{
		lstrcpy(ls.GetOut(),ls.GetIn());
		return;
	}

	const char* pIn=ls.GetIn();
	char* pOut=ls.GetOut();

	const char* pFromIn = ls.GetProfile()->m_strIgnore[ls.GetDirection()==Translate::dirTrnstoRus?LangProfile::BeginTrns:LangProfile::BeginRus];
	const char* pToIn = ls.GetProfile()->m_strIgnore[ls.GetDirection()==Translate::dirTrnstoRus?LangProfile::EndTrns:LangProfile::EndRus];

	const int nFromIn = lstrlen(pFromIn);
	const int nToIn = lstrlen(pToIn);

	if(ls.GetInsert())
	{
		bool bFrom=true;
		lstrcpy(pOut,pIn);

		for(size_t iChar=0;*pIn&&iChar<ls.GetCharCount();iChar++)
		{
			if(!LangStringTraits::CompareArrayLength(
				pIn,pFromIn,LangProfile::nIgnore)&&bFrom)
			{
				pIn+=nFromIn;
				iChar+=nFromIn;
				bFrom=!bFrom;
			}
			if(!LangStringTraits::CompareArrayLength(
				pIn,pToIn,LangProfile::nIgnore)&&!bFrom)
			{
				pIn+=nToIn;
				iChar+=nToIn;
				bFrom=!bFrom;
			}
			if(*pIn&&pIn[1])
				pIn++;
		}
		lstrcat(pOut,bFrom?pFromIn:pToIn);
	}
	else
	{
		if(ls.Empty())
		{
			ls.Clear();
			return;
		}

		bool bFrom=false;
		bool bT=false;
		int nIn=lstrlen(ls.GetIn());
		pIn=ls.GetIn()+nIn-1;
		for(int iChar=nIn;iChar;iChar--)
		{
			if(!LangStringTraits::CompareArrayLength(pIn,pToIn,LangProfile::nIgnore))
			{
				bT=true;
				bFrom=false;
			}
			else
			if(!LangStringTraits::CompareArrayLength(pIn,pFromIn,LangProfile::nIgnore))
			{
				bT=true;
				bFrom=true;
			}
			if(bT)
			{
				memcpy(pOut,ls.GetIn(),(pIn-ls.GetIn())*sizeof(char));
				pOut[pIn-ls.GetIn()]=0;
				pIn+=bFrom?nFromIn:nToIn;
				lstrcat(pOut,pIn);
				break;
			}
			pIn--;
		}
		if(!bT)
			lstrcpy(ls.GetOut(),ls.GetIn());
	}
}
*/
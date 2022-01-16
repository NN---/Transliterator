#include "stdafx.h"

#include "language.h"
#include "options.h"
#include "storage.h"
#include "global.h"
#include "functor.h"

template<int N, typename T>
typename T::size_type Language::MaxLengthArray(const T& c)
{
	if(!c.size())
		return (typename T::size_type)0;
	else
		return std::max_element
			(
				c.begin(),
				c.end(),
				TupleShorter<N, typename T::value_type>()
			)->get<N>().size();
}

size_t Language::MaxLengthTranslate(const LangProfile* pProfile, bool bfirst)
{
	return bfirst ?
			MaxLengthArray<0,LangArray>(pProfile->m_aTranslation) :
			MaxLengthArray<1,LangArray>(pProfile->m_aTranslation);
}

size_t Language::MaxLengthIgnore(const LangProfile* pProfile)
{
	return std::max_element(
		pProfile->m_astrIgnore,
		pProfile->m_astrIgnore+LangProfile::nIgnore,
		NN::shorter<LangString>())->size();
}

size_t Language::MaxLengthIgnoreText(const LangProfile* pProfile)
{
	return MaxLengthArray<0>(pProfile->m_aIgnoreText);
}

size_t Language::CountOutTranslate(size_t nCharIn,
	Translate::Direction dir,BOOL bIgnore,const LangProfile* pProfile)
{
	if(!pProfile)
		return 0;
	return nCharIn*
		(1+
			std::max(
				MaxLengthTranslate(pProfile,dir == Translate::dirBottomtoTop),
				(bIgnore?MaxLengthIgnore(pProfile):1)
				)
		)+1;
}

void Language::Translate(const wchar_t* strIn,wchar_t* strOut,
	Translate::Direction dir,const LangProfile* pProfile)
{
	if(!InitTI(strIn,strOut,&pProfile))
		return;

	const wchar_t* pIn = strIn;
	wchar_t* pOut = strOut;
	
	// Max length
	const size_t maxlenT = MaxLengthTranslate(pProfile, IsFirst(dir));
	const size_t maxlenI = MaxLengthIgnoreText(pProfile);
		
	while(*pIn)
	{
		if(g_Options.m_bIgnore)
		{
			if(Translate_Ignore(&pIn,&pOut,dir,pProfile))
				continue;
		}
		if(g_Options.m_bIgnoreText)
		{
			if(Translate_IgnoreText(&pIn,&pOut,dir,pProfile,maxlenI))
				continue;
		}
		if(g_Options.m_bTranslate)
		{
			if(Translate_Translate(&pIn,&pOut,dir,pProfile,maxlenT))
				continue;
		}
		if(*pIn)
			*pOut++= *pIn++;
	}
	// End
	*pOut = 0;
}

bool Language::Translate_Translate(const wchar_t** ppIn,wchar_t** ppOut,
	Translate::Direction dir,const LangProfile* pProfile,size_t maxlenT)
{
	// Check
	if(!**ppIn)
		return true;

	// Init
	const bool bfirst =  dir == Translate::dirToptoBottom;

	// Translate
	for(size_t len = maxlenT;len;len--)
	{
		for(LangArray::const_iterator it = pProfile->m_aTranslation.begin();
			it != pProfile->m_aTranslation.end(); ++it)
		{
			// Translate::LangTranslate
			const Translate::Translation& TrnsItem = it->get<LangPos::Translation>();
			if(dir == Translate::dirToptoBottom)
			{
				if(!(TrnsItem & Translate::trnsToptoBottom))
					continue;
			}
			else
			{
				if(!(TrnsItem & Translate::trnsBottomtoTop))
					continue;
			}
			
			const LangString& rStringIn  = 
				bfirst ?
				it->get<LangPos::Top>() :
				it->get<LangPos::Bottom>();

			const LangString& rStringOut  = 
				bfirst ?
				it->get<LangPos::Bottom>() :
				it->get<LangPos::Top>();

			if(rStringIn.length() == len &&
				!LangStringTraits::compare(*ppIn,rStringIn.c_str(),len))
			{
				NN::wcscpy_change(ppOut,rStringOut.c_str());
				(*ppIn)+= len;

				return true;
			}
		}
	}
	return false;
}

bool Language::Translate_Ignore(const wchar_t** ppIn,wchar_t** ppOut,
	Translate::Direction dir,const LangProfile* pProfile)
{
	// Check
	if(!**ppIn)
		return true;

	// Init
	const bool bfirst =  dir == Translate::dirToptoBottom;
		
	const LangString& strBeginIn  = 
		pProfile->m_astrIgnore[bfirst?LangProfile::BeginTop:LangProfile::BeginBottom];
	const LangString& strEndIn = 
		pProfile->m_astrIgnore[bfirst?LangProfile::EndTop:LangProfile::EndBottom];
	const LangString& strBeginOut = 
		pProfile->m_astrIgnore[bfirst?LangProfile::BeginBottom:LangProfile::BeginTop];
	const LangString& strEndOut = 
		pProfile->m_astrIgnore[bfirst?LangProfile::EndBottom:LangProfile::EndTop];

	// Ignore
	if(!LangStringTraits::compare(*ppIn,strBeginIn.c_str(),strBeginIn.length()))
	{
		// Continue
		(*ppIn)+= strBeginIn.length();

		// Copy Ignore
		if(g_Options.m_bCopyIgnore)
			NN::wcscpy_change(ppOut,strBeginOut.c_str());

		// Copy
		while(**ppIn&&
			LangStringTraits::compare(*ppIn,strEndIn.c_str(),strEndIn.length()))
			*(*ppOut)++= *(*ppIn)++;

		if(!**ppIn)
			return true;
			
		(*ppIn)+= strEndIn.length();
		
		// Copy Ignore
		if(g_Options.m_bCopyIgnore)
			NN::wcscpy_change(ppOut,strEndOut.c_str());
			
		if(!**ppIn)
			return true;
	}
	return false;
}

bool Language::Translate_IgnoreText(const wchar_t** ppIn,wchar_t** ppOut,
	Translate::Direction dir,const LangProfile* pProfile,size_t maxlenI)
{
	// Check
	if(!**ppIn)
		return true;

	// Ignore text
	for(size_t lenI = maxlenI;lenI;lenI--)
	{
		for(IgnoreTextArray::const_iterator it = pProfile->m_aIgnoreText.begin();
			it != pProfile->m_aIgnoreText.end(); ++it)
		{
			// Check translation direction
			const Translate::Translation& TrnsItem = it->get<IgnoreTextPos::Translation>();
			if(dir == Translate::dirToptoBottom)
			{
				if(!(TrnsItem&Translate::trnsToptoBottom))
					continue;
			}
			else
			{
				if(!(TrnsItem&Translate::trnsBottomtoTop))
					continue;
			}

			const IgnoreTextString& ignorestr = it->get<IgnoreTextPos::String>();
			if(ignorestr.length() == lenI&&
				!LangStringTraits::compare(*ppIn,ignorestr.c_str(),lenI))
			{
				NN::wcscpy_change(ppOut,ignorestr.c_str());
				(*ppIn)+= ignorestr.length();
				return true;
			}
		}
	}
	return false;
}

void Language::Ignore(const wchar_t* strIn,wchar_t* strOut,
	bool bInsert,bool bfirst,const LangProfile* pProfile)
{
	if(!InitTI(strIn,strOut,&pProfile))
	{
		if(bInsert)
			wcscpy(strOut,pProfile->m_astrIgnore[
				bfirst?LangProfile::BeginBottom:LangProfile::BeginTop].c_str());
		return;
	}
	
	const wchar_t* pIn = strIn;
	wchar_t* pOut = strOut;

	if(bInsert)
		Ignore_Insert(pIn,pOut,bfirst,pProfile);
	else
		Ignore_Remove(pIn,pOut,bfirst,pProfile);
}

void Language::Ignore_Insert(const wchar_t* pIn,wchar_t* pOut,
		bool bfirst,const LangProfile* pProfile)
{
	// Init
	const LangString& strBeginIn = 
		pProfile->m_astrIgnore[bfirst?LangProfile::BeginTop:LangProfile::BeginBottom];
	const LangString& strEndIn = 
		pProfile->m_astrIgnore[bfirst?LangProfile::EndTop:LangProfile::EndBottom];
	const LangString& strBeginOut = 
		pProfile->m_astrIgnore[bfirst?LangProfile::BeginBottom:LangProfile::BeginTop];
	const LangString& strEndOut = 
		pProfile->m_astrIgnore[bfirst?LangProfile::EndBottom:LangProfile::EndTop];

	// List Details
	int Language_Ignore_Insert; // Not Used

	typedef std::vector<wchar_t> ListWChar;
	ListWChar aCheck[] = 
	{
		ListWChar(pProfile->m_aTranslation.size()),
		ListWChar(pProfile->m_aTranslation.size())
	};

	{
		ListWChar::iterator aitCheck[] = 
		{
			aCheck[0].begin(),
			aCheck[1].begin()
		};

		for(LangArray::const_iterator itProfile = pProfile->m_aTranslation.begin();
			itProfile != pProfile->m_aTranslation.end();
			++itProfile, ++aitCheck[0], ++aitCheck[1])
		{
			*aitCheck[LangPos::Top] = itProfile->get<LangPos::Top>()[0];
			*aitCheck[LangPos::Bottom] = itProfile->get<LangPos::Bottom>()[0];
		}
	}
	const ListWChar& lCheck = aCheck[!bfirst];
	
	bool bDoInsert = false;
	while(*pIn)
	{
		// Ignore
		if(!LangStringTraits::compare(
			pIn,strBeginIn.c_str(),strBeginIn.length()))
		{
			bDoInsert = true;

			pIn+= strBeginIn.length();

			NN::wcscpy_change(&pOut,strBeginOut.c_str());

			while(*pIn&&
				LangStringTraits::compare(
				pIn,strEndIn.c_str(),strEndIn.length()))
				*pOut++= *pIn++;

			if(!*pIn)
				break;

			pIn+= strEndIn.length();

			if(!*pIn)
				break;

			NN::wcscpy_change(&pOut,strEndOut.c_str());

			bDoInsert = false;
		}
		// Text
		if(std::find(lCheck.begin(),lCheck.end(),*pIn) != lCheck.end())
		{
			bDoInsert = true;

			NN::wcscpy_change(&pOut,strBeginOut.c_str());

			while(*pIn&&
				(
					std::find(lCheck.begin(),lCheck.end(),*pIn) != lCheck.end()) ||
						(
						std::find(aCheck[0].begin(),aCheck[0].end(),*pIn) == aCheck[0].end() &&
						std::find(aCheck[1].begin(),aCheck[1].end(),*pIn) == aCheck[1].end()
						)
				)
				*pOut++= *pIn++;

			if(!*pIn)
				break;

			NN::wcscpy_change(&pOut,strEndOut.c_str());

			bDoInsert = false;
		}
		*pOut++= *pIn++;
	}
	if(bDoInsert)
		NN::wcscpy_change(&pOut,strEndOut.c_str());
	*pOut = 0;
}

void Language::Ignore_Remove(const wchar_t* pIn,wchar_t* pOut,
		bool bfirst,const LangProfile* pProfile)
{
	// Init
	const LangString& strBeginIn = 
		pProfile->m_astrIgnore[bfirst?LangProfile::BeginTop:LangProfile::BeginBottom];
	const LangString& strEndIn = 
		pProfile->m_astrIgnore[bfirst?LangProfile::EndTop:LangProfile::EndBottom];
	
	while(*pIn)
	{
		// Ignore
		if(!LangStringTraits::compare(pIn,strBeginIn.c_str(),strBeginIn.length()))
		{
			pIn+= strBeginIn.length();
			
			while(*pIn&&
				LangStringTraits::compare(
				pIn,strEndIn.c_str(),strEndIn.length()))
				*pOut++= *pIn++;

			if(!*pIn)
				break;

			pIn+= strEndIn.length();

			continue;
		}
		*pOut++= *pIn++;
	}
	*pOut = 0;
}

void Language::SetIgnore(const wchar_t* strIn,wchar_t* strOut,
	Translate::Direction dir,bool bInsert,const LangProfile* pProfile)
{
	if(!InitTI(strIn,strOut,&pProfile)&&*strIn&&bInsert)
		return;

	const wchar_t* pIn = strIn;
	wchar_t* pOut = strOut;

	if(bInsert)
		SetIgnore_Insert(pIn,pOut,dir,pProfile);
	else
		SetIgnore_Remove(pIn,pOut,dir,pProfile);
}

void Language::SetIgnore_Insert(const wchar_t* pIn,wchar_t* pOut,
	Translate::Direction dir,const LangProfile* pProfile)
{
	// Init
	const bool bfirst =  dir == Translate::dirToptoBottom;

	const LangString& strBeginIn = 
		pProfile->m_astrIgnore[bfirst?LangProfile::BeginTop:LangProfile::BeginBottom];
	const LangString& strEndIn = 
		pProfile->m_astrIgnore[bfirst?LangProfile::EndTop:LangProfile::EndBottom];
	const LangString& strBeginOut = 
		pProfile->m_astrIgnore[bfirst?LangProfile::BeginBottom:LangProfile::BeginTop];
	const LangString& strEndOut = 
		pProfile->m_astrIgnore[bfirst?LangProfile::EndBottom:LangProfile::EndTop];

	wcscpy(pOut,pIn);
	bool bBegin = true;
	
	pIn--;
	while(*++pIn)
	{
		// Begin
		if(!LangStringTraits::compare(
			pIn,strBeginIn.c_str(),strBeginIn.length())&&bBegin)
		{
			pIn+= strBeginIn.length();
			bBegin = !bBegin;
		}

		// End
		if(!LangStringTraits::compare(
			pIn,strEndIn.c_str(),strEndIn.length())&&!bBegin)
		{
			pIn+= strEndIn.length();
			bBegin = !bBegin;
		}
	}
	
	wcscat(pOut,bBegin?strBeginOut.c_str():strEndOut.c_str());
}

void Language::SetIgnore_Remove(const wchar_t* pIn,wchar_t* pOut,
	Translate::Direction dir,const LangProfile* pProfile)
{
	// Init
	const bool bfirst =  dir == Translate::dirToptoBottom;

	const LangString& strBeginIn = 
		pProfile->m_astrIgnore[bfirst?LangProfile::BeginTop:LangProfile::BeginBottom];
	const LangString& strEndIn = 
		pProfile->m_astrIgnore[bfirst?LangProfile::EndTop:LangProfile::EndBottom];

	const wchar_t* pIn_o = pIn;
	*pOut = 0;

	bool bBegin = false;
	bool bT = false;
	const size_t nIn = wcslen(pIn);

	pIn = pIn+nIn;

	while(*--pIn)
	{
		if(!LangStringTraits::compare(
			pIn,strEndIn.c_str(),strEndIn.length()))
		{
			bT = true;
			bBegin = false;
		}
		else
		if(!LangStringTraits::compare(
			pIn,strBeginIn.c_str(),strBeginIn.length()))
		{
			bT = true;
			bBegin = true;
		}
		
		if(bT)
		{
			wmemcpy(pOut,pIn_o,pIn-pIn_o);
			pOut[pIn-pIn_o] = 0;
			pIn+= bBegin?strBeginIn.length():strEndIn.length();
			wcscat(pOut,pIn);
			break;
		}
	}
	if(!bT)
		wcscpy(pOut,pIn_o);
}

bool Language::InitTI(const wchar_t* strIn,wchar_t* strOut,const LangProfile** ppProfile)
{
	if(!*ppProfile)
		*ppProfile = GetCurProfile();
	if(!*strIn||!strIn)
	{
		*strOut = 0;
		return false;
	}
	if((*ppProfile)->m_aTranslation.empty())
	{
		wcscpy(strOut,strIn);
		return false;
	}
	return true;
}

const Language& Language::operator = (const Language& r)
{
	for(unsigned i = 0;i<nProfiles; ++i)
		m_aProfile[i] = r.m_aProfile[i];

	return *this;
}
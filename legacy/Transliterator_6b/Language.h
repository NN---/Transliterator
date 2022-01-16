#ifndef __LANGUAGE_H__
#define __LANGUAGE_H__

#include "langprofile.h"

class Language
{
public:
	enum { nProfiles = 9 };
private:
	LangProfile* m_pCurProfile;
	LangProfile m_aProfile[nProfiles];
public:
	Language() : m_pCurProfile(&m_aProfile[0]) {}
	
	// Profiles
	LangProfile* GetProfile(unsigned nProfile)
	{ return &m_aProfile[nProfile]; }
	const LangProfile* GetProfile(unsigned nProfile) const
	{ return &m_aProfile[nProfile]; }
	void SetCurProfile(LangProfile* pProfile)
	{ m_pCurProfile=pProfile; }
	void SetCurProfile(unsigned nProfile)
	{ m_pCurProfile=&m_aProfile[nProfile]; }

	// Reset
	// Standard
	static void Reset1(LangProfile& rProfile);
	// Symbols
	static void Reset2(LangProfile& rProfile);
	// GOST
	static void Reset3(LangProfile& rProfile);
	// QWER
	static void Reset4(LangProfile& rProfile);
	// RusHeb
	static void Reset5(LangProfile& rProfile);
	// User1
	static void Reset6(LangProfile& rProfile);
	// User2
	static void Reset7(LangProfile& rProfile);
	// User3
	static void Reset8(LangProfile& rProfile);
	// User4
	static void Reset9(LangProfile& rProfile);

	void ResetProfile(unsigned nProfile);
	void Reset();

	// Translate
	void Translate(const wchar_t* strIn,wchar_t* strOut,
		Translate::Direction dir,LangProfile* pProfile);
	bool Translate_Translate(const wchar_t** ppIn,wchar_t** ppOut,
		Translate::Direction dir,LangProfile* pProfile,size_t maxlenT);
	bool Translate_Ignore(const wchar_t** ppIn,wchar_t** ppOut,
		Translate::Direction dir,LangProfile* pProfile);
	bool Translate_IgnoreText(const wchar_t** ppIn,wchar_t** ppOut,
		Translate::Direction dir,size_t maxlenI);
};


/*
struct Language
{
	// Translate
	void Translate(const LangStruct& ls);
	inline void Translate(const char* strIn,char* strOut,Translate::Direction dir,size_t nChar,const LangProfile* pProfile=0)
	{ Translate(LangStruct(strIn,strOut,dir,nChar,pProfile)); }
	inline void Translate(char* strIn,Translate::Direction dir,size_t nChar,const LangProfile* pProfile=0)
	{ Translate(LangStruct(strIn,dir,nChar,pProfile)); }
	inline void Translate(wchar_t* strIn,Translate::Direction dir,size_t nChar,const LangProfile* pProfile=0)
	{ Translate(LangStruct(strIn,dir,nChar,pProfile)); }

	// Ignore
	void Ignore(const LangStruct& ls);
	inline void Ignore(const char* strIn,char* strOut,size_t nChar,bool bTrns,bool bInsert,const LangProfile* pProfile=0)
	{ Ignore(LangStruct(strIn,strOut,nChar,bTrns,bInsert,pProfile)); }
	inline void Ignore(char* strIn,size_t nChar,bool bTrns,bool bInsert,const LangProfile* pProfile=0)
	{ Ignore(LangStruct(strIn,nChar,bTrns,bInsert,pProfile)); }
	inline void Ignore(wchar_t* strIn,size_t nChar,bool bTrns,bool bInsert,const LangProfile* pProfile=0)
	{ Ignore(LangStruct(strIn,nChar,bTrns,bInsert,pProfile)); }

	// SetIgnore
	void SetIgnore(const LangStruct& ls);
	inline void SetIgnore(const char* strIn,char* strOut,size_t nChar,bool bTrns,bool bInsert,const LangProfile* pProfile=0)
	{ SetIgnore(LangStruct(strIn,strOut,nChar,bTrns,bInsert,pProfile)); }
	inline void SetIgnore(char* strIn,size_t nChar,bool bTrns,bool bInsert,const LangProfile* pProfile=0)
	{ SetIgnore(LangStruct(strIn,nChar,bTrns,bInsert,pProfile)); }
	inline void SetIgnore(wchar_t* strIn,size_t nChar,bool bTrns,bool bInsert,const LangProfile* pProfile=0)
	{ SetIgnore(LangStruct(strIn,nChar,bTrns,bInsert,pProfile)); }
private:
	// Check Trns or Rus
	typedef NN::Tuple<char,char> TupleCharChar;
	template<int i1>
	bool FindCheck_(char c,TupleCharChar* paCheck)
	{
		while(paCheck->Get<i1>())
			if((paCheck++)->Get<i1>()==c)
				return true;
		return false;
	}

	inline bool FindCheck(char c,bool bTrns,TupleCharChar* paCheck)
	{ return bTrns?FindCheck_<0>(c,paCheck):FindCheck_<1>(c,paCheck); }

	void UpdateCheck(const LangProfile* pProfile,TupleCharChar* paCheck)
	{
		for(size_t i=0;i<pProfile->m_map.GetCount();i++)
		{
			paCheck[i].Get<0>()=pProfile->m_map[i].Get<0>().GetAt(0);
			paCheck[i].Get<1>()=pProfile->m_map[i].Get<1>().GetAt(0);
		}
	}

	bool IsTrnsRus(CHAR c,bool bTrns,TupleCharChar* paCheck)
	{ return FindCheck(c,bTrns,paCheck); }

	bool IsTrns(CHAR c,TupleCharChar* paCheck)
	{ return IsTrnsRus(c,true,paCheck); }

	bool IsRus(CHAR c,TupleCharChar* paCheck)
	{ return IsTrnsRus(c,false,paCheck); }
public:
	const Language& operator=(const Language& src)
	{
		// Language
		for(int i=profUser1;i<nProfiles;i++)
		{
			const LangProfile* pProfileR=&src.m_LangProfile[i];
			LangProfile* pProfile=&m_LangProfile[i];

			// Name
			lstrcpy(pProfile->m_strName,pProfileR->m_strName);

			// Ignore
			for(int j=0;j<LangProfile::nBeginEnd;j++)
				lstrcpy(pProfile->m_strIgnore[j],pProfileR->m_strIgnore[j]);

			// Map
			pProfile->m_map.SetData(pProfileR->m_map);
		}
		return *this;
	}

	bool operator!=(const Language& language) const
	{
		// Language
		for(int i=profUser1;i<nProfiles;i++)
		{
			const LangProfile* pProfileR=&language.m_LangProfile[i];
			const LangProfile* pProfile=&m_LangProfile[i];

			// Name
			if(lstrcmp(pProfile->m_strName,pProfileR->m_strName))
				return true;

			// Ignore
			for(int j=0;j<LangProfile::nBeginEnd;j++)
				if(lstrcmp(pProfile->m_strIgnore[j],pProfileR->m_strIgnore[j]))
					return true;

			// Map
			if(pProfile->m_map.Compare(pProfileR->m_map))
				return true;
		}
		return false;
	}
	bool operator==(const Language& language) const
	{ return !operator!=(language); }

	typedef void (*ResetFunc)(LangProfile&);
	static ResetFunc m_aResetFunc[nProfiles];
};
*/


#endif // __LANGUAGE_H__

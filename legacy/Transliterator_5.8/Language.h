#ifndef __LANGUAGE_H__
#define __LANGUAGE_H__

#include "langprofile.h"
#include "langstruct.h"

struct Language
{
	Language() { m_pCurProfile=&m_LangProfile[profStandard]; }
	// Profiles
	enum Profiles
	{
		profStandard,
		profSymbols,
		profGOST,
		profQWER,
		profFonetic,
		profUser1,
		profUser2,
		profUser3,
		profUser4,
		nProfiles
	};
private:
	LangProfile m_LangProfile[nProfiles];
	LangProfile* m_pCurProfile;
public:
	LangProfile* GetProfile(Profiles nProfile) { return &m_LangProfile[nProfile]; }
	const LangProfile* GetProfile(Profiles nProfile) const { return &m_LangProfile[nProfile]; }
	LangProfile* GetCurProfile() { return m_pCurProfile; }
	void SetCurProfile(LangProfile* pProfile) { m_pCurProfile=pProfile; }
	void SetCurProfile(Profiles nProfile) { m_pCurProfile=&m_LangProfile[nProfile]; }
	
	// Reset
	static void ResetStandard(LangProfile& profile);
	static void ResetSymbols(LangProfile& profile);
	static void ResetGOST(LangProfile& profile);
	static void ResetQWER(LangProfile& profile);
	static void ResetFonetic(LangProfile& profile);
	static void ResetUser1(LangProfile& profile);
	static void ResetUser2(LangProfile& profile);
	static void ResetUser3(LangProfile& profile);
	static void ResetUser4(LangProfile& profile);
	static void ResetEmpty(LangProfile& profile,const char* strName);
	void ResetProfile(Profiles profile);
	void ResetAll();
	void ResetUser();

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

#endif // __LANGUAGE_H__

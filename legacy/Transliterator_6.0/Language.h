#ifndef __LANGUAGE_H__
#define __LANGUAGE_H__

#pragma once

#include "langprofile.h"

class Language
{
public:
	enum { nProfiles = 10 };
private:
	LangProfile* m_pCurProfile;
	LangProfile m_aProfile[nProfiles];
public:
	Language() : m_pCurProfile(&m_aProfile[0]) {}

	// Max Length
	template<int N, typename T>
	static typename T::size_type MaxLengthArray(const T& c);

	static size_t MaxLengthTranslate(const LangProfile* pProfile,bool bfirst);
	static size_t MaxLengthIgnore(const LangProfile* pProfile);
	static size_t MaxLengthIgnoreText(const LangProfile* pProfile);

	bool IsFirst(Translate::Direction dir)
	{ return dir == Translate::dirToptoBottom; }

	// Output Length
	static size_t Language::CountOutTranslate(size_t nCharIn,
		Translate::Direction dir,BOOL bIgnore,const LangProfile* pProfile);
	
	// Profiles
	LangProfile* GetProfile(unsigned nProfile)
	{ return &m_aProfile[nProfile]; }
	const LangProfile* GetProfile(unsigned nProfile) const
	{ return &m_aProfile[nProfile]; }
	LangProfile* GetCurProfile()
	{ return m_pCurProfile; }
	const LangProfile* GetCurProfile() const
	{ return m_pCurProfile; }
	unsigned GetCurProfileNum()
	{ return m_pCurProfile-&m_aProfile[0]; }
	void SetCurProfile(LangProfile* pProfile)
	{ m_pCurProfile = pProfile; }
	void SetCurProfile(unsigned nProfile)
	{ m_pCurProfile = &m_aProfile[nProfile]; }

	// Reset
	
	// Standard
	static void Reset1(LangProfile& rProfile);
	static void ResetTranslation1(LangProfile& rProfile);
	static void ResetIgnore1(LangProfile& rProfile);
	static void ResetIgnoreText1(LangProfile& rProfile);
	static void ResetName1(LangProfile& rProfile);
	// Fonetic
	static void Reset2(LangProfile& rProfile);
	static void ResetTranslation2(LangProfile& rProfile);
	static void ResetIgnore2(LangProfile& rProfile);
	static void ResetIgnoreText2(LangProfile& rProfile);
	static void ResetName2(LangProfile& rProfile);
	// GOST
	static void Reset3(LangProfile& rProfile);
	static void ResetTranslation3(LangProfile& rProfile);
	static void ResetIgnore3(LangProfile& rProfile);
	static void ResetIgnoreText3(LangProfile& rProfile);
	static void ResetName3(LangProfile& rProfile);
	// Symbols
	static void Reset4(LangProfile& rProfile);
	static void ResetTranslation4(LangProfile& rProfile);
	static void ResetIgnore4(LangProfile& rProfile);
	static void ResetIgnoreText4(LangProfile& rProfile);
	static void ResetName4(LangProfile& rProfile);
	// QWER
	static void Reset5(LangProfile& rProfile);
	static void ResetTranslation5(LangProfile& rProfile);
	static void ResetIgnore5(LangProfile& rProfile);
	static void ResetIgnoreText5(LangProfile& rProfile);
	static void ResetName5(LangProfile& rProfile);
	// DOS-Win
	static void Reset6(LangProfile& rProfile);
	static void ResetTranslation6(LangProfile& rProfile);
	static void ResetIgnore6(LangProfile& rProfile);
	static void ResetIgnoreText6(LangProfile& rProfile);
	static void ResetName6(LangProfile& rProfile);
	// KOI8-R-Win
	static void Reset7(LangProfile& rProfile);
	static void ResetTranslation7(LangProfile& rProfile);
	static void ResetIgnore7(LangProfile& rProfile);
	static void ResetIgnoreText7(LangProfile& rProfile);
	static void ResetName7(LangProfile& rProfile);
	// HebRus
	static void Reset8(LangProfile& rProfile);
	static void ResetTranslation8(LangProfile& rProfile);
	static void ResetIgnore8(LangProfile& rProfile);
	static void ResetIgnoreText8(LangProfile& rProfile);
	static void ResetName8(LangProfile& rProfile);
	// User
	static void Reset9(LangProfile& rProfile);
	static void ResetTranslation9(LangProfile& rProfile);
	static void ResetIgnore9(LangProfile& rProfile);
	static void ResetIgnoreText9(LangProfile& rProfile);
	static void ResetName9(LangProfile& rProfile);
	// User2
	static void Reset10(LangProfile& rProfile);
	static void ResetTranslation10(LangProfile& rProfile);
	static void ResetIgnore10(LangProfile& rProfile);
	static void ResetIgnoreText10(LangProfile& rProfile);
	static void ResetName10(LangProfile& rProfile);

	static void ResetProfile(unsigned nProfile,LangProfile& rProfile);
	static void ResetTranslation(unsigned nProfile,LangProfile& rProfile);
	static void ResetIgnore(unsigned nProfile,LangProfile& rProfile);
	static void ResetIgnoreText(unsigned nProfile,LangProfile& rProfile);
	static void ResetName(unsigned nProfile,LangProfile& rProfile);

	void Reset();

	// Translate
	void Translate(const wchar_t* strIn,wchar_t* strOut,
		Translate::Direction dir,const LangProfile* pProfile);
private:
	bool Translate_Translate(const wchar_t** ppIn,wchar_t** ppOut,
		Translate::Direction dir,const LangProfile* pProfile,size_t maxlenT);
	bool Translate_Ignore(const wchar_t** ppIn,wchar_t** ppOut,
		Translate::Direction dir,const LangProfile* pProfile);
	bool Translate_IgnoreText(const wchar_t** ppIn,wchar_t** ppOut,
		Translate::Direction dir,const LangProfile* pProfile,size_t maxlenI);
public:

	// Ignore
	void Ignore(const wchar_t* strIn,wchar_t* strOut,
		bool bInsert,bool bfirst,const LangProfile* pProfile);
private:
	void Ignore_Insert(const wchar_t* pIn,wchar_t* pOut,
		bool bfirst,const LangProfile* pProfile);
	void Ignore_Remove(const wchar_t* pIn,wchar_t* pOut,
		bool bfirst,const LangProfile* pProfile);
public:

	// SetIgnore
	void SetIgnore(const wchar_t* strIn,wchar_t* strOut,
		Translate::Direction dir,bool bInsert,const LangProfile* pProfile);
private:
	void SetIgnore_Insert(const wchar_t* pIn,wchar_t* pOut,
		Translate::Direction dir,const LangProfile* pProfile);
	void SetIgnore_Remove(const wchar_t* pIn,wchar_t* pOut,
		Translate::Direction dir,const LangProfile* pProfile);
private:
	bool InitTI(const wchar_t* strIn,wchar_t* strOut,const LangProfile** ppProfile);
	
public:
	// operator
	const Language& operator = (const Language& r);
};

#endif // __LANGUAGE_H__

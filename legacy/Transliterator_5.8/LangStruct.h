#ifndef __LANGSTRUCT_H___
#define __LANGSTRUCT_H___

#include "types.h"
#include "langprofile.h"

struct LangStruct
{
	enum { CP = 1251 };
private:
	// In
	char* m_strIn;
	wchar_t* m_strInW;
	// Out
	char* m_strOut;

	// Translate
	Translate::Direction m_dir;
	// Ignore
	bool m_bInsert;
	bool m_bTrns;

	size_t m_nChar;

	const LangProfile* m_pProfile;

	// Helper
	bool m_bOut;
	bool m_bWide;
public:
	LangStruct(const char* strIn,char* strOut,Translate::Direction dir,size_t nChar,const LangProfile* pProfile=0) :
		m_strIn(const_cast<char*>(strIn)),
		m_strOut(strOut),
		m_dir(dir),
		m_nChar(nChar),
		m_pProfile(pProfile),
		m_bWide(false)
	{ Init(); }

	LangStruct(char* strIn,Translate::Direction dir,size_t nChar,const LangProfile* pProfile=0) :
		m_strIn(strIn),
		m_strOut(0),
		m_dir(dir),
		m_nChar(nChar),
		m_pProfile(pProfile),
		m_bWide(false)
	{ Init(); }

	LangStruct(wchar_t* strInW,Translate::Direction dir,size_t nChar,const LangProfile* pProfile=0) :
		m_strInW(strInW),
		m_strOut(0),
		m_dir(dir),
		m_nChar(nChar),
		m_pProfile(pProfile),
		m_bWide(true)
	{ Init(); }

	LangStruct(const char* strIn,char* strOut,size_t nChar,bool bTrns,bool bInsert,const LangProfile* pProfile=0) :
		m_strIn(const_cast<char*>(strIn)),
		m_strOut(strOut),
		m_nChar(nChar),
		m_bTrns(bTrns),
		m_bInsert(bInsert),
		m_pProfile(pProfile),
		m_bWide(false)
	{ Init(); }

	LangStruct(char* strIn,size_t nChar,bool bTrns,bool bInsert,const LangProfile* pProfile=0) :
		m_strIn(strIn),
		m_strOut(0),
		m_nChar(nChar),
		m_bTrns(bTrns),
		m_bInsert(bInsert),
		m_pProfile(pProfile),
		m_bWide(false)
	{ Init(); }

	LangStruct(wchar_t* strInW,size_t nChar,bool bTrns,bool bInsert,const LangProfile* pProfile=0) :
		m_strInW(strInW),
		m_strOut(0),
		m_nChar(nChar),
		m_bTrns(bTrns),
		m_bInsert(bInsert),
		m_pProfile(pProfile),
		m_bWide(true)
	{ Init(); }

	~LangStruct()
	{ Destroy(); }

	void Init()
	{
		// nChar
		if(!m_nChar)
			m_nChar=m_bWide?(size_t)lstrlenW(m_strInW):(size_t)lstrlenA(m_strIn);
		// Wide
		if(m_bWide)
		{
			m_strIn=new char[m_nChar+1];
			::WideCharToMultiByte(CP,0,m_strInW,m_nChar+1,m_strIn,m_nChar+1,0,0);
		}
		// Out
		m_bOut= !m_strOut;
		if(m_bOut)
			m_strOut=new char[m_nChar*LangString::nCountInit+1];
	}

	void Destroy()
	{
		if(m_bOut)
		{
			lstrcpyn(m_strIn,m_strOut,m_nChar);
			delete[] m_strOut;
		}
		if(m_bWide)
		{
			::MultiByteToWideChar(CP,0,m_strIn,m_nChar+1,m_strInW,m_nChar+1);
			delete[] m_strIn;
		}
	}

	inline const char* GetIn() const { return m_strIn; }
	inline char* GetOut() const { return m_strOut; }
	inline Translate::Direction GetDirection() const { return m_dir; }
	inline size_t GetCharCount() const { return m_nChar; }
	inline const LangProfile* GetProfile() const { return m_pProfile; }
	inline void SetProfile(const LangProfile* pProfile) const
	{ (const_cast<LangStruct*>(this))->m_pProfile=pProfile; }
	inline bool IsTrns() const { return m_bTrns; }
	inline bool GetInsert() const { return m_bInsert; }

	inline bool Empty() const { return !m_pProfile->m_map.GetLast()||!*m_strIn||!m_nChar; }
	inline void Clear() const { GetOut()[0]=0; }
};

#endif // __LANGSTRUCT_H___

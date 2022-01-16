#ifndef __TRANSLIT_H__
#define __TRANSLIT_H__

#define ENGRUS_COUNT 6
typedef NN::StaticArray<CHAR,ENGRUS_COUNT> EngRusArray;
typedef NN::StaticArray<WCHAR,ENGRUS_COUNT> EngRusArrayW;
typedef NN::Tuple<EngRusArray,EngRusArray,Translate::EngRusTranslate> EngRusType;
typedef NN::Tuple<EngRusArrayW,EngRusArrayW,Translate::EngRusTranslate> EngRusTypeW;
#define TRANSLIT_COUNT 150
typedef NN::StaticArrayMap<EngRusType,TRANSLIT_COUNT> EngRusMap;

// ArrayTraits
// We must not compare Item.Get<2>() (Translate::EngRusTranslate)
template<>
class NN::StaticArrayMapTraitsLastArrayItem<EngRusType>
{
public:
	inline static bool LastArrayItem(const EngRusType& Item)
	{
		return !(Item.Get<0>()[0]&&Item.Get<1>()[0]);
	}
};

template<>
class NN::ArrayTraitsCompare<EngRusType>
{
public:
	static int Compare(const EngRusType& value1,const EngRusType& value2)
	{
		if(value1.Get<0>()==value2.Get<0>()&&
			value1.Get<1>()==value2.Get<1>())
			return 0;
		else
		if(value1.Get<0>()>value2.Get<0>()&&
			value1.Get<1>()>value2.Get<1>())
			return 1;
		else
			return -1;
	}

	static int CompareLength(const EngRusType* /*pArray1*/,const EngRusType* /*pArray2*/)
	{
		return 0;
	}

	static int CompareArray(const EngRusType* pArray1,const EngRusType* pArray2,unsigned nItems)
	{
		int iCmp;
		for(unsigned nItem=0;nItem<nItems;nItem++)
		{
			iCmp=Compare(pArray1[nItem],pArray2[nItem]);
			if(iCmp)
				return iCmp;
		}
		return 0;
	}

	static int CompareArrayLength(const EngRusType* pArray1,const EngRusType* pArray2,unsigned nItems)
	{
		return CompareArray(pArray1,pArray2,nItems);
	}
};

// Translit
class Translit : public EngRusMap
{
public:
	void Reset()
	{
		static const Type defArray[nCountInit]=
		{
			Type(_T("a"),_T("�"),Translate::EngRus),
			Type(_T("A"),_T("�"),Translate::EngRus),
			Type(_T("b"),_T("�"),Translate::EngRus),
			Type(_T("B"),_T("�"),Translate::EngRus),
			Type(_T("c"),_T("�"),Translate::EngRus),
			Type(_T("C"),_T("�"),Translate::EngRus),
			Type(_T("ch"),_T("�"),Translate::EngRus),
			Type(_T("cH"),_T("�"),Translate::EngtoRus),
			Type(_T("CH"),_T("�"),Translate::EngRus),
			Type(_T("Ch"),_T("�"),Translate::EngtoRus),
			Type(_T("d"),_T("�"),Translate::EngRus),
			Type(_T("D"),_T("�"),Translate::EngRus),
			Type(_T("e"),_T("�"),Translate::EngRus),
			Type(_T("E"),_T("�"),Translate::EngRus),
			Type(_T("e'"),_T("�"),Translate::EngRus),
			Type(_T("E'"),_T("�"),Translate::EngRus),
			Type(_T("e`"),_T("�"),Translate::EngRus),
			Type(_T("E`"),_T("�"),Translate::EngRus),
			Type(_T("e''"),_T("�"),Translate::EngRus),
			Type(_T("E''"),_T("�"),Translate::EngRus),
			Type(_T("f"),_T("�"),Translate::EngRus),
			Type(_T("F"),_T("�"),Translate::EngRus),
			Type(_T("g"),_T("�"),Translate::EngRus),
			Type(_T("G"),_T("�"),Translate::EngRus),
			Type(_T("g'`"),_T("�"),Translate::EngRus),
			Type(_T("g`'"),_T("�"),Translate::EngtoRus),
			Type(_T("G'`"),_T("�"),Translate::EngRus),
			Type(_T("G`'"),_T("�"),Translate::EngtoRus),
			Type(_T("h"),_T("�"),Translate::EngRus),
			Type(_T("H"),_T("�"),Translate::EngRus),
			Type(_T("i"),_T("�"),Translate::EngRus),
			Type(_T("I"),_T("�"),Translate::EngRus),
			Type(_T("i'"),_T("�"),Translate::EngRus),
			Type(_T("I'"),_T("�"),Translate::EngRus),
			Type(_T("i`"),_T("�"),Translate::EngRus),
			Type(_T("I`"),_T("�"),Translate::EngRus),
			Type(_T("j"),_T("�"),Translate::EngRus),
			Type(_T("J"),_T("�"),Translate::EngRus),
			Type(_T("k"),_T("�"),Translate::EngRus),
			Type(_T("K"),_T("�"),Translate::EngRus),
			Type(_T("l"),_T("�"),Translate::EngRus),
			Type(_T("L"),_T("�"),Translate::EngRus),
			Type(_T("m"),_T("�"),Translate::EngRus),
			Type(_T("M"),_T("�"),Translate::EngRus),
			Type(_T("n"),_T("�"),Translate::EngRus),
			Type(_T("N"),_T("�"),Translate::EngRus),
			Type(_T("o"),_T("�"),Translate::EngRus),
			Type(_T("O"),_T("�"),Translate::EngRus),
			Type(_T("p"),_T("�"),Translate::EngRus),
			Type(_T("P"),_T("�"),Translate::EngRus),
			Type(_T("q"),_T("�"),Translate::EngtoRus),
			Type(_T("Q"),_T("�"),Translate::EngtoRus),
			Type(_T("r"),_T("�"),Translate::EngRus),
			Type(_T("R"),_T("�"),Translate::EngRus),
			Type(_T("s"),_T("�"),Translate::EngRus),
			Type(_T("S"),_T("�"),Translate::EngRus),
			Type(_T("sh"),_T("�"),Translate::EngRus),
			Type(_T("sH"),_T("�"),Translate::EngtoRus),
			Type(_T("SH"),_T("�"),Translate::EngRus),
			Type(_T("Sh"),_T("�"),Translate::EngtoRus),
			Type(_T("sh''"),_T("�"),Translate::EngtoRus),
			Type(_T("sH''"),_T("�"),Translate::EngtoRus),
			Type(_T("Sh''"),_T("�"),Translate::EngtoRus),
			Type(_T("SH''"),_T("�"),Translate::EngtoRus),
			Type(_T("sch'"),_T("�"),Translate::EngRus),
			Type(_T("sCh'"),_T("�"),Translate::EngtoRus),
			Type(_T("scH'"),_T("�"),Translate::EngtoRus),
			Type(_T("sCH'"),_T("�"),Translate::EngtoRus),
			Type(_T("Sch'"),_T("�"),Translate::EngtoRus),
			Type(_T("SCh'"),_T("�"),Translate::EngtoRus),
			Type(_T("ScH'"),_T("�"),Translate::EngtoRus),
			Type(_T("SCH'"),_T("�"),Translate::EngRus),
			Type(_T("t"),_T("�"),Translate::EngRus),
			Type(_T("T"),_T("�"),Translate::EngRus),
			Type(_T("tc'"),_T("�"),Translate::EngtoRus),
			Type(_T("tC'"),_T("�"),Translate::EngtoRus),
			Type(_T("Tc'"),_T("�"),Translate::EngtoRus),
			Type(_T("TC'"),_T("�"),Translate::EngtoRus),
			Type(_T("u"),_T("�"),Translate::EngRus),
			Type(_T("U"),_T("�"),Translate::EngRus),
			Type(_T("u'"),_T("�"),Translate::EngRus),
			Type(_T("U'"),_T("�"),Translate::EngRus),
			Type(_T("v"),_T("�"),Translate::EngRus),
			Type(_T("V"),_T("�"),Translate::EngRus),
			Type(_T("w"),_T("�"),Translate::EngtoRus),
			Type(_T("W"),_T("�"),Translate::EngtoRus),
			Type(_T("w''"),_T("�"),Translate::EngtoRus),
			Type(_T("W''"),_T("�"),Translate::EngtoRus),
			Type(_T("x"),_T("�"),Translate::EngtoRus),
			Type(_T("X"),_T("�"),Translate::EngtoRus),
			Type(_T("y"),_T("�"),Translate::EngRus),
			Type(_T("Y"),_T("�"),Translate::EngRus),
			Type(_T("ya"),_T("�"),Translate::EngRus),
			Type(_T("yA"),_T("�"),Translate::EngtoRus),
			Type(_T("YA"),_T("�"),Translate::EngRus),
			Type(_T("Ya"),_T("�"),Translate::EngtoRus),
			Type(_T("yu"),_T("�"),Translate::EngRus),
			Type(_T("yU"),_T("�"),Translate::EngtoRus),
			Type(_T("YU"),_T("�"),Translate::EngRus),
			Type(_T("Yu"),_T("�"),Translate::EngtoRus),
			Type(_T("y'"),_T("�"),Translate::EngRus),
			Type(_T("Y'"),_T("�"),Translate::EngRus),
			Type(_T("z"),_T("�"),Translate::EngRus),
			Type(_T("Z"),_T("�"),Translate::EngRus),
			Type(_T("'"),_T("�"),Translate::EngRus),
			Type(_T("''"),_T("�"),Translate::EngRus),
			Type(_T("`"),_T("�"),Translate::EngRus),
			Type(_T("``"),_T("�"),Translate::EngRus),
		};
		SetData(defArray);
	}

	void Translate(LPCSTR szIn,LPSTR szOut,Translate::Direction dir,size_t nChar)
	{
		if(!GetLast()||!szIn||!nChar)
		{
			if(szOut)
				*szOut=0;
			return;
		}

		// Init loop
		LPCSTR pszIn=szIn;
		LPSTR pszOut=szOut;

		ZeroMemory(pszOut,nChar);

		int i1= dir==Translate::dirRustoEng;

		// The loop
		for(size_t iChar=0;*pszIn&&iChar<nChar;iChar++)
		{
			// Not Translate
			if(!EngRusArray::Traits::CompareArrayLength(pszIn,_Options.m_szNotTranslate[dir==Translate::dirEngtoRus?Options::FromEng:Options::FromRus],Options::nNotTranslate))
			{
				pszIn+=lstrlen(_Options.m_szNotTranslate[dir==Translate::dirEngtoRus?Options::FromEng:Options::FromRus]);
				if(_Options.m_bCopyNotTranslate)
				{
					lstrcat(pszOut,_Options.m_szNotTranslate[dir==Translate::dirEngtoRus?Options::FromRus:Options::FromEng]);
					pszOut+=lstrlen(_Options.m_szNotTranslate[dir==Translate::dirEngtoRus?Options::FromRus:Options::FromEng]);
				}
				if(!*pszIn)
					break;
				while(*pszIn&&
							EngRusArray::Traits::CompareArrayLength(
								pszIn,_Options.m_szNotTranslate[
								dir==Translate::dirEngtoRus?
								Options::ToEng:Options::ToRus],
								Options::nNotTranslate))
					*pszOut++=*pszIn++;
				if(!*pszIn)
					break;
				pszIn+=lstrlen(_Options.m_szNotTranslate[dir==Translate::dirEngtoRus?Options::ToEng:Options::ToRus]);
				if(_Options.m_bCopyNotTranslate)
				{
					lstrcat(pszOut,_Options.m_szNotTranslate[dir==Translate::dirEngtoRus?Options::ToRus:Options::ToEng]);
					pszOut+=lstrlen(_Options.m_szNotTranslate[dir==Translate::dirEngtoRus?Options::ToRus:Options::ToEng]);
				}
				if(!*pszIn)
					break;
			}
			// Translate
			for(size_t len=EngRusArray::nCountInit;len;len--)
			{
				for(size_t nItem=0;nItem<GetLast();nItem++)
				{
					// Translate Translate::Direction
					if(dir==Translate::dirEngtoRus)
					{
						if(!(GetAt(nItem).Get<2>()&Translate::EngtoRus))
							continue;
					}
					else
					{
						if(!(GetAt(nItem).Get<2>()&Translate::RustoEng))
							continue;
					}
					EngRusArray* pArray=(EngRusArray*)GetAt(nItem).Get(i1);
					if(pArray->GetLength(len)&&
						!EngRusArray::Traits::CompareArrayLength(pszIn,pArray->GetData(),len))
					{
						pArray=(EngRusArray*)GetAt(nItem).Get(!i1);
						lstrcat(pszOut,pArray->GetData());
						pszOut+=pArray->GetLength();
						pszIn+=len;
						goto lNext;
					}
				}
			}
			*pszOut++=*pszIn++;
			lNext:
				continue;
		}
	}

	void Translate(LPSTR szEngRus,Translate::Direction dir,size_t nChar)
	{
		NN::AutoArray<CHAR> aOut(nChar);
		if(!aOut.GetData())
		{
			*szEngRus=0;
			return;
		}

		Translate(szEngRus,aOut.GetData(),dir,nChar);

		memcpy(szEngRus,aOut.GetData(),lstrlen(aOut.GetData())+1);
	}

	void TranslateW(LPWSTR szEngRusW,Translate::Direction dir,size_t nChar)
	{
		NN::AutoArray<CHAR> aEngRus(nChar);
		if(!aEngRus.GetData())
		{
			*szEngRusW=0;
			return;
		}
		
		::WideCharToMultiByte(1251,0,szEngRusW,nChar,aEngRus.GetData(),nChar,NULL,NULL);
		
		Translate(aEngRus.GetData(),dir,nChar);

		::MultiByteToWideChar(1251,0,aEngRus.GetData(),nChar,szEngRusW,nChar);
	}
private:
	NN::Tuple<CHAR,CHAR> aCheck[nCountInit];

	template<int i1>
	bool FindEngRusCheck_(CHAR c)
	{
		NN::Tuple<CHAR,CHAR>* pT=aCheck;
		while(pT->Get<i1>())
			if((pT++)->Get<i1>()==c)
				return true;
		return false;
	}

	inline bool FindEngRusCheck(CHAR c,bool bEng)
	{ return bEng?FindEngRusCheck_<0>(c):FindEngRusCheck_<1>(c); }

	void UpdateEngRusCheck()
	{
		for(int i=0;i<nCountInit;i++)
		{
			aCheck[i].Get<0>()=GetAt(i).Get<0>().GetAt(0);
			aCheck[i].Get<1>()=GetAt(i).Get<1>().GetAt(0);
		}
	}

	inline bool IsEngRus(CHAR c,bool bEng)
	{ return FindEngRusCheck(c,bEng); }

	inline bool IsEng(CHAR c)
	{ return IsEngRus(c,true); }

	inline bool IsRus(CHAR c)
	{ return IsEngRus(c,false); }
public:
	// No Translate
	void NoTranslate(LPCSTR szIn,LPSTR szOut,size_t nChar,bool bEng,bool bInsert)
	{
		LPCSTR pszIn=szIn;
		LPSTR pszOut=szOut;
	
		ZeroMemory(pszOut,nChar);
	
		UpdateEngRusCheck();
		
		Options::FromTo from=bEng?Options::FromEng:Options::FromRus;
		Options::FromTo to=bEng?Options::ToEng:Options::ToRus;
		
		if(bInsert)
		{
			bool bSet=false;
			while(*pszIn)
			{
				// No Translate
				if(!EngRusArray::Traits::CompareArrayLength(
					pszIn,_Options.m_szNotTranslate[from],Options::nNotTranslate))
				{
					bSet=true;
					int len=lstrlen(_Options.m_szNotTranslate[from]);
					for(int i=0;i<len;i++)
						*pszOut++=*pszIn++;
					while(*pszIn&&EngRusArray::Traits::CompareArrayLength(
						pszIn,_Options.m_szNotTranslate[to],Options::nNotTranslate))
						*pszOut++=*pszIn++;
					if(!*pszIn)
						break;
					bSet=false;
				}
				// Text
				if(IsEngRus(*pszIn,bEng))
				{
					bSet=true;
					lstrcat(pszOut,_Options.m_szNotTranslate[from]);
					pszOut+=lstrlen(_Options.m_szNotTranslate[from]);
					while(*pszIn&&IsEngRus(*pszIn,bEng))
						*pszOut++=*pszIn++;
					if(!*pszIn)
						break;
					lstrcat(pszOut,_Options.m_szNotTranslate[to]);
					pszOut+=lstrlen(_Options.m_szNotTranslate[to]);
					bSet=false;
				}
				*pszOut++=*pszIn++;
			}
			if(bSet)
				lstrcat(pszOut,_Options.m_szNotTranslate[to]);
		}
		else
		{
			while(*pszIn)
			{
				// No Translate
				if(!EngRusArray::Traits::CompareArrayLength(
					pszIn,_Options.m_szNotTranslate[from],Options::nNotTranslate))
				{
					pszIn+=lstrlen(_Options.m_szNotTranslate[from]);
					while(*pszIn&&EngRusArray::Traits::CompareArrayLength(
						pszIn,_Options.m_szNotTranslate[to],Options::nNotTranslate))
						*pszOut++=*pszIn++;
					if(!*pszIn)
						break;
					if(!EngRusArray::Traits::CompareArrayLength(
						pszIn,_Options.m_szNotTranslate[to],Options::nNotTranslate))
						pszIn+=lstrlen(_Options.m_szNotTranslate[to]);
					if(!*pszIn)
						break;
				}
				*pszOut++=*pszIn++;
			}
		}
	}

	void NoTranslate(LPSTR szEngRus,size_t nChar,bool bEng,bool bInsert)
	{
		NN::AutoArray<CHAR> aOut(nChar);
		if(!aOut.GetData())
		{
			*szEngRus=0;
			return;
		}

		NoTranslate(szEngRus,aOut.GetData(),nChar,bEng,bInsert);

		memcpy(szEngRus,aOut.GetData(),lstrlen(aOut.GetData())+1);
	}

	void NoTranslateW(LPWSTR szEngRusW,size_t nChar,bool bEng,bool bInsert)
	{
		NN::AutoArray<CHAR> aEngRus(nChar);
		if(!aEngRus.GetData())
		{
			*szEngRusW=0;
			return;
		}
		
		::WideCharToMultiByte(1251,0,szEngRusW,nChar,aEngRus.GetData(),nChar,NULL,NULL);
		
		NoTranslate(aEngRus.GetData(),nChar,bEng,bInsert);

		::MultiByteToWideChar(1251,0,aEngRus.GetData(),nChar,szEngRusW,nChar);
	}
};

#endif // !__TRANSLIT_H__
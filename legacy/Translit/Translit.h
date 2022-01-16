#ifndef __TRANSLIT_H__
#define __TRANSLIT_H__

#define ENGRUS_COUNT 6
typedef CHAR EngRusType;
typedef WCHAR EngRusTypeW;
typedef StaticArrayNC<EngRusType,ENGRUS_COUNT> EngRusArray;
typedef StaticArrayNC<EngRusTypeW,ENGRUS_COUNT> EngRusArrayW;
typedef TupleNC<EngRusArray,EngRusArray,Translate::EngRusTranslate> EngRusTuple;
typedef TupleNC<EngRusArrayW,EngRusArrayW,Translate::EngRusTranslate> EngRusTupleW;
#define TRANSLIT_COUNT 150
typedef StaticArrayMap<EngRusTuple,TRANSLIT_COUNT> EngRusMap;

template<>
class NN::StaticArrayMapTraitsLastArrayItem<EngRusTuple>
{
public:
	static bool LastArrayItem(const EngRusTuple& Item)
	{
		return !(Item.Get<0>()[0]&&Item.Get<1>()[0]);
	}
};

template<>
class NN::ArrayTraitsCompare<EngRusTuple>
{
public:
	static int Compare(const EngRusTuple& value1,const EngRusTuple& value2)
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

	static int CompareLength(const EngRusTuple* /*pArray1*/,const EngRusTuple* /*pArray2*/)
	{
		return 0;
	}

	static int CompareArray(const EngRusTuple* pArray1,const EngRusTuple* pArray2,unsigned nItems)
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

	static int CompareArrayLength(const EngRusTuple* pArray1,const EngRusTuple* pArray2,unsigned nItems)
	{
		return CompareArray(pArray1,pArray2,nItems);
	}
};

class Translit : public EngRusMap
{
public:
	void Default()
	{
		static const Type defArray[nCountInit]=
		{
			{_T("a"),_T("�"),Translate::EngRus},
			{_T("A"),_T("�"),Translate::EngRus},
			{_T("b"),_T("�"),Translate::EngRus},
			{_T("B"),_T("�"),Translate::EngRus},
			{_T("c"),_T("�"),Translate::EngRus},
			{_T("C"),_T("�"),Translate::EngRus},
			{_T("ch"),_T("�"),Translate::EngRus},
			{_T("cH"),_T("�"),Translate::EngtoRus},
			{_T("CH"),_T("�"),Translate::EngRus},
			{_T("Ch"),_T("�"),Translate::EngtoRus},
			{_T("d"),_T("�"),Translate::EngRus},
			{_T("D"),_T("�"),Translate::EngRus},
			{_T("e"),_T("�"),Translate::EngRus},
			{_T("E"),_T("�"),Translate::EngRus},
			{_T("e'"),_T("�"),Translate::EngRus},
			{_T("E'"),_T("�"),Translate::EngRus},
			{_T("e`"),_T("�"),Translate::EngRus},
			{_T("E`"),_T("�"),Translate::EngRus},
			{_T("e''"),_T("�"),Translate::EngRus},
			{_T("E''"),_T("�"),Translate::EngRus},
			{_T("f"),_T("�"),Translate::EngRus},
			{_T("F"),_T("�"),Translate::EngRus},
			{_T("g"),_T("�"),Translate::EngRus},
			{_T("G"),_T("�"),Translate::EngRus},
			{_T("g'`"),_T("�"),Translate::EngRus},
			{_T("g`'"),_T("�"),Translate::EngtoRus},
			{_T("G'`"),_T("�"),Translate::EngRus},
			{_T("G`'"),_T("�"),Translate::EngtoRus},
			{_T("h"),_T("�"),Translate::EngRus},
			{_T("H"),_T("�"),Translate::EngRus},
			{_T("i"),_T("�"),Translate::EngRus},
			{_T("I"),_T("�"),Translate::EngRus},
			{_T("i'"),_T("�"),Translate::EngRus},
			{_T("I'"),_T("�"),Translate::EngRus},
			{_T("i`"),_T("�"),Translate::EngRus},
			{_T("I`"),_T("�"),Translate::EngRus},
			{_T("j"),_T("�"),Translate::EngRus},
			{_T("J"),_T("�"),Translate::EngRus},
			{_T("k"),_T("�"),Translate::EngRus},
			{_T("K"),_T("�"),Translate::EngRus},
			{_T("l"),_T("�"),Translate::EngRus},
			{_T("L"),_T("�"),Translate::EngRus},
			{_T("m"),_T("�"),Translate::EngRus},
			{_T("M"),_T("�"),Translate::EngRus},
			{_T("n"),_T("�"),Translate::EngRus},
			{_T("N"),_T("�"),Translate::EngRus},
			{_T("o"),_T("�"),Translate::EngRus},
			{_T("O"),_T("�"),Translate::EngRus},
			{_T("p"),_T("�"),Translate::EngRus},
			{_T("P"),_T("�"),Translate::EngRus},
			{_T("q"),_T("�"),Translate::EngtoRus},
			{_T("Q"),_T("�"),Translate::EngtoRus},
			{_T("r"),_T("�"),Translate::EngRus},
			{_T("R"),_T("�"),Translate::EngRus},
			{_T("s"),_T("�"),Translate::EngRus},
			{_T("S"),_T("�"),Translate::EngRus},
			{_T("sh"),_T("�"),Translate::EngRus},
			{_T("sH"),_T("�"),Translate::EngtoRus},
			{_T("SH"),_T("�"),Translate::EngRus},
			{_T("Sh"),_T("�"),Translate::EngtoRus},
			{_T("sh''"),_T("�"),Translate::EngtoRus},
			{_T("sH''"),_T("�"),Translate::EngtoRus},
			{_T("Sh''"),_T("�"),Translate::EngtoRus},
			{_T("SH''"),_T("�"),Translate::EngtoRus},
			{_T("sch'"),_T("�"),Translate::EngRus},
			{_T("sCh'"),_T("�"),Translate::EngtoRus},
			{_T("scH'"),_T("�"),Translate::EngtoRus},
			{_T("sCH'"),_T("�"),Translate::EngtoRus},
			{_T("Sch'"),_T("�"),Translate::EngtoRus},
			{_T("SCh'"),_T("�"),Translate::EngtoRus},
			{_T("ScH'"),_T("�"),Translate::EngtoRus},
			{_T("SCH'"),_T("�"),Translate::EngRus},
			{_T("t"),_T("�"),Translate::EngRus},
			{_T("T"),_T("�"),Translate::EngRus},
			{_T("tc'"),_T("�"),Translate::EngtoRus},
			{_T("tC'"),_T("�"),Translate::EngtoRus},
			{_T("Tc'"),_T("�"),Translate::EngtoRus},
			{_T("TC'"),_T("�"),Translate::EngtoRus},
			{_T("u"),_T("�"),Translate::EngRus},
			{_T("U"),_T("�"),Translate::EngRus},
			{_T("u'"),_T("�"),Translate::EngRus},
			{_T("U'"),_T("�"),Translate::EngRus},
			{_T("v"),_T("�"),Translate::EngRus},
			{_T("V"),_T("�"),Translate::EngRus},
			{_T("w"),_T("�"),Translate::EngtoRus},
			{_T("W"),_T("�"),Translate::EngtoRus},
			{_T("w''"),_T("�"),Translate::EngtoRus},
			{_T("W''"),_T("�"),Translate::EngtoRus},
			{_T("x"),_T("�"),Translate::EngtoRus},
			{_T("X"),_T("�"),Translate::EngtoRus},
			{_T("y"),_T("�"),Translate::EngRus},
			{_T("Y"),_T("�"),Translate::EngRus},
			{_T("ya"),_T("�"),Translate::EngRus},
			{_T("yA"),_T("�"),Translate::EngtoRus},
			{_T("YA"),_T("�"),Translate::EngRus},
			{_T("Ya"),_T("�"),Translate::EngtoRus},
			{_T("yu"),_T("�"),Translate::EngRus},
			{_T("yU"),_T("�"),Translate::EngtoRus},
			{_T("YU"),_T("�"),Translate::EngRus},
			{_T("Yu"),_T("�"),Translate::EngtoRus},
			{_T("y'"),_T("�"),Translate::EngRus},
			{_T("Y'"),_T("�"),Translate::EngRus},
			{_T("z"),_T("�"),Translate::EngRus},
			{_T("Z"),_T("�"),Translate::EngRus},
			{_T("'"),_T("�"),Translate::EngRus},
			{_T("''"),_T("�"),Translate::EngRus},
			{_T("`"),_T("�"),Translate::EngRus},
			{_T("``"),_T("�"),Translate::EngRus},
		};
		SetData(defArray);
	}

	void Translate(EngRusType* szIn,EngRusType* szOut,Translate::Direction dir,size_t nChar)
	{
		// Check
		if(!GetLast()||!*szIn||!nChar)
		{
			szOut[0]=0;
			return;
		}

		// Init loop
		EngRusType* pszIn=szIn;
		EngRusType* pszOut=szOut;

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

	void Translate(EngRusType* szEngRus,Translate::Direction dir,size_t nChar)
	{
		AutoArray<EngRusType> aOut(nChar);
		if(!aOut.GetData())
			return;

		Translate(szEngRus,aOut.GetData(),dir,nChar);

		memcpy(szEngRus,aOut.GetData(),sizeof(EngRusType)*nChar);
	}

	void TranslateW(EngRusTypeW* szEngRusW,Translate::Direction dir,size_t nChar)
	{
		AutoArray<EngRusType> aEngRus(nChar);
		
		::WideCharToMultiByte(1251,0,szEngRusW,nChar,aEngRus.GetData(),nChar,NULL,NULL);
		
		Translate(aEngRus.GetData(),dir,nChar);

		::MultiByteToWideChar(1251,0,aEngRus.GetData(),nChar,szEngRusW,nChar);
	}
};

#endif // !__TRANSLIT_H__
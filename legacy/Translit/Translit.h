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
			{_T("a"),_T("à"),Translate::EngRus},
			{_T("A"),_T("À"),Translate::EngRus},
			{_T("b"),_T("á"),Translate::EngRus},
			{_T("B"),_T("Á"),Translate::EngRus},
			{_T("c"),_T("ö"),Translate::EngRus},
			{_T("C"),_T("Ö"),Translate::EngRus},
			{_T("ch"),_T("÷"),Translate::EngRus},
			{_T("cH"),_T("÷"),Translate::EngtoRus},
			{_T("CH"),_T("×"),Translate::EngRus},
			{_T("Ch"),_T("×"),Translate::EngtoRus},
			{_T("d"),_T("ä"),Translate::EngRus},
			{_T("D"),_T("Ä"),Translate::EngRus},
			{_T("e"),_T("å"),Translate::EngRus},
			{_T("E"),_T("Å"),Translate::EngRus},
			{_T("e'"),_T("¸"),Translate::EngRus},
			{_T("E'"),_T("¨"),Translate::EngRus},
			{_T("e`"),_T("ý"),Translate::EngRus},
			{_T("E`"),_T("Ý"),Translate::EngRus},
			{_T("e''"),_T("º"),Translate::EngRus},
			{_T("E''"),_T("ª"),Translate::EngRus},
			{_T("f"),_T("ô"),Translate::EngRus},
			{_T("F"),_T("Ô"),Translate::EngRus},
			{_T("g"),_T("ã"),Translate::EngRus},
			{_T("G"),_T("Ã"),Translate::EngRus},
			{_T("g'`"),_T("´"),Translate::EngRus},
			{_T("g`'"),_T("´"),Translate::EngtoRus},
			{_T("G'`"),_T("¥"),Translate::EngRus},
			{_T("G`'"),_T("¥"),Translate::EngtoRus},
			{_T("h"),_T("õ"),Translate::EngRus},
			{_T("H"),_T("Õ"),Translate::EngRus},
			{_T("i"),_T("è"),Translate::EngRus},
			{_T("I"),_T("È"),Translate::EngRus},
			{_T("i'"),_T("³"),Translate::EngRus},
			{_T("I'"),_T("²"),Translate::EngRus},
			{_T("i`"),_T("¿"),Translate::EngRus},
			{_T("I`"),_T("¯"),Translate::EngRus},
			{_T("j"),_T("æ"),Translate::EngRus},
			{_T("J"),_T("Æ"),Translate::EngRus},
			{_T("k"),_T("ê"),Translate::EngRus},
			{_T("K"),_T("Ê"),Translate::EngRus},
			{_T("l"),_T("ë"),Translate::EngRus},
			{_T("L"),_T("Ë"),Translate::EngRus},
			{_T("m"),_T("ì"),Translate::EngRus},
			{_T("M"),_T("Ì"),Translate::EngRus},
			{_T("n"),_T("í"),Translate::EngRus},
			{_T("N"),_T("Í"),Translate::EngRus},
			{_T("o"),_T("î"),Translate::EngRus},
			{_T("O"),_T("Î"),Translate::EngRus},
			{_T("p"),_T("ï"),Translate::EngRus},
			{_T("P"),_T("Ï"),Translate::EngRus},
			{_T("q"),_T("û"),Translate::EngtoRus},
			{_T("Q"),_T("Û"),Translate::EngtoRus},
			{_T("r"),_T("ð"),Translate::EngRus},
			{_T("R"),_T("Ð"),Translate::EngRus},
			{_T("s"),_T("ñ"),Translate::EngRus},
			{_T("S"),_T("Ñ"),Translate::EngRus},
			{_T("sh"),_T("ø"),Translate::EngRus},
			{_T("sH"),_T("ø"),Translate::EngtoRus},
			{_T("SH"),_T("Ø"),Translate::EngRus},
			{_T("Sh"),_T("Ø"),Translate::EngtoRus},
			{_T("sh''"),_T("ù"),Translate::EngtoRus},
			{_T("sH''"),_T("ù"),Translate::EngtoRus},
			{_T("Sh''"),_T("Ù"),Translate::EngtoRus},
			{_T("SH''"),_T("Ù"),Translate::EngtoRus},
			{_T("sch'"),_T("ù"),Translate::EngRus},
			{_T("sCh'"),_T("ù"),Translate::EngtoRus},
			{_T("scH'"),_T("ù"),Translate::EngtoRus},
			{_T("sCH'"),_T("ù"),Translate::EngtoRus},
			{_T("Sch'"),_T("Ù"),Translate::EngtoRus},
			{_T("SCh'"),_T("Ù"),Translate::EngtoRus},
			{_T("ScH'"),_T("Ù"),Translate::EngtoRus},
			{_T("SCH'"),_T("Ù"),Translate::EngRus},
			{_T("t"),_T("ò"),Translate::EngRus},
			{_T("T"),_T("Ò"),Translate::EngRus},
			{_T("tc'"),_T("ö"),Translate::EngtoRus},
			{_T("tC'"),_T("ö"),Translate::EngtoRus},
			{_T("Tc'"),_T("Ö"),Translate::EngtoRus},
			{_T("TC'"),_T("Ö"),Translate::EngtoRus},
			{_T("u"),_T("ó"),Translate::EngRus},
			{_T("U"),_T("Ó"),Translate::EngRus},
			{_T("u'"),_T("¢"),Translate::EngRus},
			{_T("U'"),_T("¡"),Translate::EngRus},
			{_T("v"),_T("â"),Translate::EngRus},
			{_T("V"),_T("Â"),Translate::EngRus},
			{_T("w"),_T("ø"),Translate::EngtoRus},
			{_T("W"),_T("Ø"),Translate::EngtoRus},
			{_T("w''"),_T("ù"),Translate::EngtoRus},
			{_T("W''"),_T("Ù"),Translate::EngtoRus},
			{_T("x"),_T("õ"),Translate::EngtoRus},
			{_T("X"),_T("Õ"),Translate::EngtoRus},
			{_T("y"),_T("é"),Translate::EngRus},
			{_T("Y"),_T("É"),Translate::EngRus},
			{_T("ya"),_T("ÿ"),Translate::EngRus},
			{_T("yA"),_T("ÿ"),Translate::EngtoRus},
			{_T("YA"),_T("ß"),Translate::EngRus},
			{_T("Ya"),_T("ß"),Translate::EngtoRus},
			{_T("yu"),_T("þ"),Translate::EngRus},
			{_T("yU"),_T("þ"),Translate::EngtoRus},
			{_T("YU"),_T("Þ"),Translate::EngRus},
			{_T("Yu"),_T("Þ"),Translate::EngtoRus},
			{_T("y'"),_T("û"),Translate::EngRus},
			{_T("Y'"),_T("Û"),Translate::EngRus},
			{_T("z"),_T("ç"),Translate::EngRus},
			{_T("Z"),_T("Ç"),Translate::EngRus},
			{_T("'"),_T("ü"),Translate::EngRus},
			{_T("''"),_T("Ü"),Translate::EngRus},
			{_T("`"),_T("ú"),Translate::EngRus},
			{_T("``"),_T("Ú"),Translate::EngRus},
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
#include "stdafx.h"
#include "language.h"

void Language::ResetStandard(LangProfile& profile)
{
	// Map
	static const LangType defMap[]=
	{
		LangType("a","�",Translate::trnsAll),
		LangType("A","�",Translate::trnsAll),
		LangType("b","�",Translate::trnsAll),
		LangType("B","�",Translate::trnsAll),
		LangType("c","�",Translate::trnsAll),
		LangType("C","�",Translate::trnsAll),
		LangType("ch","�",Translate::trnsAll),
		LangType("cH","�",Translate::trnsTrnstoRus),
		LangType("CH","�",Translate::trnsAll),
		LangType("Ch","�",Translate::trnsTrnstoRus),
		LangType("d","�",Translate::trnsAll),
		LangType("D","�",Translate::trnsAll),
		LangType("e","�",Translate::trnsAll),
		LangType("E","�",Translate::trnsAll),
		LangType("e'","�",Translate::trnsAll),
		LangType("E'","�",Translate::trnsAll),
		LangType("e`","�",Translate::trnsAll),
		LangType("E`","�",Translate::trnsAll),
		LangType("e''","�",Translate::trnsAll),
		LangType("E''","�",Translate::trnsAll),
		LangType("f","�",Translate::trnsAll),
		LangType("F","�",Translate::trnsAll),
		LangType("g","�",Translate::trnsAll),
		LangType("G","�",Translate::trnsAll),
		LangType("g'`","�",Translate::trnsAll),
		LangType("g`'","�",Translate::trnsTrnstoRus),
		LangType("G'`","�",Translate::trnsAll),
		LangType("G`'","�",Translate::trnsTrnstoRus),
		LangType("h","�",Translate::trnsAll),
		LangType("H","�",Translate::trnsAll),
		LangType("i","�",Translate::trnsAll),
		LangType("I","�",Translate::trnsAll),
		LangType("i'","�",Translate::trnsAll),
		LangType("I'","�",Translate::trnsAll),
		LangType("i`","�",Translate::trnsAll),
		LangType("I`","�",Translate::trnsAll),
		LangType("j","�",Translate::trnsAll),
		LangType("J","�",Translate::trnsAll),
		LangType("k","�",Translate::trnsAll),
		LangType("K","�",Translate::trnsAll),
		LangType("l","�",Translate::trnsAll),
		LangType("L","�",Translate::trnsAll),
		LangType("m","�",Translate::trnsAll),
		LangType("M","�",Translate::trnsAll),
		LangType("n","�",Translate::trnsAll),
		LangType("N","�",Translate::trnsAll),
		LangType("o","�",Translate::trnsAll),
		LangType("O","�",Translate::trnsAll),
		LangType("p","�",Translate::trnsAll),
		LangType("P","�",Translate::trnsAll),
		LangType("q","�",Translate::trnsTrnstoRus),
		LangType("Q","�",Translate::trnsTrnstoRus),
		LangType("r","�",Translate::trnsAll),
		LangType("R","�",Translate::trnsAll),
		LangType("s","�",Translate::trnsAll),
		LangType("S","�",Translate::trnsAll),
		LangType("sh","�",Translate::trnsAll),
		LangType("sH","�",Translate::trnsTrnstoRus),
		LangType("SH","�",Translate::trnsAll),
		LangType("Sh","�",Translate::trnsTrnstoRus),
		LangType("sh''","�",Translate::trnsTrnstoRus),
		LangType("sH''","�",Translate::trnsTrnstoRus),
		LangType("Sh''","�",Translate::trnsTrnstoRus),
		LangType("SH''","�",Translate::trnsTrnstoRus),
		LangType("sch'","�",Translate::trnsAll),
		LangType("sCh'","�",Translate::trnsTrnstoRus),
		LangType("scH'","�",Translate::trnsTrnstoRus),
		LangType("sCH'","�",Translate::trnsTrnstoRus),
		LangType("Sch'","�",Translate::trnsTrnstoRus),
		LangType("SCh'","�",Translate::trnsTrnstoRus),
		LangType("ScH'","�",Translate::trnsTrnstoRus),
		LangType("SCH'","�",Translate::trnsAll),
		LangType("t","�",Translate::trnsAll),
		LangType("T","�",Translate::trnsAll),
		LangType("tc'","�",Translate::trnsTrnstoRus),
		LangType("tC'","�",Translate::trnsTrnstoRus),
		LangType("Tc'","�",Translate::trnsTrnstoRus),
		LangType("TC'","�",Translate::trnsTrnstoRus),
		LangType("u","�",Translate::trnsAll),
		LangType("U","�",Translate::trnsAll),
		LangType("u'","�",Translate::trnsAll),
		LangType("U'","�",Translate::trnsAll),
		LangType("v","�",Translate::trnsAll),
		LangType("V","�",Translate::trnsAll),
		LangType("w","�",Translate::trnsTrnstoRus),
		LangType("W","�",Translate::trnsTrnstoRus),
		LangType("w''","�",Translate::trnsTrnstoRus),
		LangType("W''","�",Translate::trnsTrnstoRus),
		LangType("x","�",Translate::trnsTrnstoRus),
		LangType("X","�",Translate::trnsTrnstoRus),
		LangType("y","�",Translate::trnsAll),
		LangType("Y","�",Translate::trnsAll),
		LangType("ya","�",Translate::trnsAll),
		LangType("yA","�",Translate::trnsTrnstoRus),
		LangType("YA","�",Translate::trnsAll),
		LangType("Ya","�",Translate::trnsTrnstoRus),
		LangType("yu","�",Translate::trnsAll),
		LangType("yU","�",Translate::trnsTrnstoRus),
		LangType("YU","�",Translate::trnsAll),
		LangType("Yu","�",Translate::trnsTrnstoRus),
		LangType("y'","�",Translate::trnsAll),
		LangType("Y'","�",Translate::trnsAll),
		LangType("z","�",Translate::trnsAll),
		LangType("Z","�",Translate::trnsAll),
		LangType("'","�",Translate::trnsAll),
		LangType("''","�",Translate::trnsAll),
		LangType("`","�",Translate::trnsAll),
		LangType("``","�",Translate::trnsAll),
	};
	profile.m_map.SetData(defMap);
	// Name
	static const char strName[]="Standard";
	lstrcpy(profile.m_strName,strName);
	// Ignore
	static const char strIgnore[LangProfile::nBeginEnd][LangProfile::nIgnore]=
	{
		"**",
		"**",
		"**",
		"**"
	};
	for(int i=0;i<LangProfile::nIgnore;i++)
		lstrcpy(profile.m_strIgnore[i],strIgnore[i]);
}

void Language::ResetSymbols(LangProfile& profile)
{
	// Profile
	static const LangType defMap[]=
	{
		LangType("a","�",Translate::trnsAll),
		LangType("A","�",Translate::trnsAll),
		LangType("6","�",Translate::trnsAll),
		LangType("6","�",Translate::trnsRustoTrns),
		LangType("B","�",Translate::trnsAll),
		LangType("�","�",Translate::trnsRustoTrns),
		LangType("r","�",Translate::trnsAll),
		LangType("r","�",Translate::trnsRustoTrns),
		LangType("D","�",Translate::trnsAll),
		LangType("D","�",Translate::trnsRustoTrns),
		LangType("e","�",Translate::trnsAll),
		LangType("E","�",Translate::trnsAll),
		LangType("e","�",Translate::trnsRustoTrns),
		LangType("E","�",Translate::trnsRustoTrns),
		LangType(">|<","�",Translate::trnsAll),
		LangType("}|{","�",Translate::trnsAll),
		LangType(">-|-<","�",Translate::trnsRustoTrns),
		LangType("}-|-{","�",Translate::trnsTrnstoRus),
		LangType("3","�",Translate::trnsAll),
		LangType("3","�",Translate::trnsRustoTrns),
		LangType("u","�",Translate::trnsAll),
		LangType("U","�",Translate::trnsAll),
		LangType("u'","�",Translate::trnsAll),
		LangType("U'","�",Translate::trnsAll),
		LangType("u`","�",Translate::trnsTrnstoRus),
		LangType("U`","�",Translate::trnsTrnstoRus),
		LangType("k","�",Translate::trnsAll),
		LangType("K","�",Translate::trnsAll),
		LangType("/\\","�",Translate::trnsAll),
		LangType("JI","�",Translate::trnsAll),
		LangType("m","�",Translate::trnsAll),
		LangType("M","�",Translate::trnsAll),
		LangType("H","�",Translate::trnsAll),
		LangType("H","�",Translate::trnsRustoTrns),
		LangType("o","�",Translate::trnsAll),
		LangType("O","�",Translate::trnsAll),
		LangType("n","�",Translate::trnsAll),
		LangType("n","�",Translate::trnsRustoTrns),
		LangType("p","�",Translate::trnsAll),
		LangType("P","�",Translate::trnsAll),
		LangType("c","�",Translate::trnsAll),
		LangType("C","�",Translate::trnsAll),
		LangType("T","�",Translate::trnsAll),
		LangType("T","�",Translate::trnsRustoTrns),
		LangType("y","�",Translate::trnsAll),
		LangType("Y","�",Translate::trnsAll),
		LangType("f","�",Translate::trnsAll),
		LangType("F","�",Translate::trnsAll),
		LangType("<|>","�",Translate::trnsAll),
		LangType("<I>","�",Translate::trnsAll),
		LangType("x","�",Translate::trnsAll),
		LangType("X","�",Translate::trnsAll),
		LangType("L|","�",Translate::trnsAll),
		LangType("L|","�",Translate::trnsRustoTrns),
		LangType("4","�",Translate::trnsAll),
		LangType("4","�",Translate::trnsRustoTrns),
		LangType("LLI","�",Translate::trnsAll),
		LangType("w","�",Translate::trnsAll),
		LangType("LL|","�",Translate::trnsAll),
		LangType("LL|","�",Translate::trnsRustoTrns),
		LangType("\\","�",Translate::trnsAll),
		LangType("\\\\","�",Translate::trnsRustoTrns),
		LangType("bI","�",Translate::trnsAll),
		LangType("bI","�",Translate::trnsRustoTrns),
		LangType("b","�",Translate::trnsAll),
		LangType("b","�",Translate::trnsRustoTrns),
		LangType("e","�",Translate::trnsRustoTrns),
		LangType("E","�",Translate::trnsRustoTrns),
		LangType("IO","�",Translate::trnsAll),
		LangType("IO","�",Translate::trnsRustoTrns),
		LangType("I-O","�",Translate::trnsTrnstoRus),
		LangType("I-O","�",Translate::trnsRustoTrns),
		LangType("9I","�",Translate::trnsAll),
		LangType("9I","�",Translate::trnsRustoTrns),
	};
	profile.m_map.SetData(defMap);
	// Name
	static const char strName[]="Symbols";
	lstrcpy(profile.m_strName,strName);
	// Ignore
	static const char strIgnore[LangProfile::nBeginEnd][LangProfile::nIgnore]=
	{
		"**",
		"**",
		"**",
		"**"
	};
	for(int i=0;i<LangProfile::nIgnore;i++)
		lstrcpy(profile.m_strIgnore[i],strIgnore[i]);
}

void Language::ResetGOST(LangProfile& profile)
{
	// Map
	static const LangType defMap[]=
	{
		LangType("a","�",Translate::trnsAll),
		LangType("A","�",Translate::trnsAll),
		LangType("b","�",Translate::trnsAll),
		LangType("B","�",Translate::trnsAll),
		LangType("v","�",Translate::trnsAll),
		LangType("V","�",Translate::trnsAll),
		LangType("g","�",Translate::trnsAll),
		LangType("G","�",Translate::trnsAll),
		LangType("d","�",Translate::trnsAll),
		LangType("D","�",Translate::trnsAll),
		LangType("e","�",Translate::trnsAll),
		LangType("E","�",Translate::trnsAll),
		LangType("jo","�",Translate::trnsAll),
		LangType("jO","�",Translate::trnsTrnstoRus),
		LangType("JO","�",Translate::trnsAll),
		LangType("Jo","�",Translate::trnsTrnstoRus),
		LangType("zh","�",Translate::trnsAll),
		LangType("zH","�",Translate::trnsTrnstoRus),
		LangType("ZH","�",Translate::trnsAll),
		LangType("Zh","�",Translate::trnsTrnstoRus),
		LangType("z","�",Translate::trnsAll),
		LangType("Z","�",Translate::trnsAll),
		LangType("i","�",Translate::trnsAll),
		LangType("I","�",Translate::trnsAll),
		LangType("jj","�",Translate::trnsAll),
		LangType("jJ","�",Translate::trnsTrnstoRus),
		LangType("JJ","�",Translate::trnsAll),
		LangType("Jj","�",Translate::trnsTrnstoRus),
		LangType("k","�",Translate::trnsAll),
		LangType("K","�",Translate::trnsAll),
		LangType("l","�",Translate::trnsAll),
		LangType("L","�",Translate::trnsAll),
		LangType("m","�",Translate::trnsAll),
		LangType("M","�",Translate::trnsAll),
		LangType("n","�",Translate::trnsAll),
		LangType("N","�",Translate::trnsAll),
		LangType("o","�",Translate::trnsAll),
		LangType("O","�",Translate::trnsAll),
		LangType("p","�",Translate::trnsAll),
		LangType("P","�",Translate::trnsAll),
		LangType("r","�",Translate::trnsAll),
		LangType("R","�",Translate::trnsAll),
		LangType("s","�",Translate::trnsAll),
		LangType("S","�",Translate::trnsAll),
		LangType("t","�",Translate::trnsAll),
		LangType("T","�",Translate::trnsAll),
		LangType("u","�",Translate::trnsAll),
		LangType("U","�",Translate::trnsAll),
		LangType("f","�",Translate::trnsAll),
		LangType("F","�",Translate::trnsAll),
		LangType("kh","�",Translate::trnsAll),
		LangType("kH","�",Translate::trnsTrnstoRus),
		LangType("KH","�",Translate::trnsAll),
		LangType("Kh","�",Translate::trnsTrnstoRus),
		LangType("c","�",Translate::trnsAll),
		LangType("C","�",Translate::trnsAll),
		LangType("ch","�",Translate::trnsAll),
		LangType("cH","�",Translate::trnsTrnstoRus),
		LangType("CH","�",Translate::trnsAll),
		LangType("Ch","�",Translate::trnsTrnstoRus),
		LangType("sh","�",Translate::trnsAll),
		LangType("sH","�",Translate::trnsTrnstoRus),
		LangType("SH","�",Translate::trnsAll),
		LangType("Sh","�",Translate::trnsTrnstoRus),
		LangType("shh","�",Translate::trnsAll),
		LangType("shH","�",Translate::trnsTrnstoRus),
		LangType("sHh","�",Translate::trnsTrnstoRus),
		LangType("sHH","�",Translate::trnsTrnstoRus),
		LangType("SHH","�",Translate::trnsAll),
		LangType("SHh","�",Translate::trnsTrnstoRus),
		LangType("ShH","�",Translate::trnsTrnstoRus),
		LangType("Shh","�",Translate::trnsTrnstoRus),
		LangType("\"","�",Translate::trnsAll),
		LangType("\"\"","�",Translate::trnsAll),
		LangType("y","�",Translate::trnsAll),
		LangType("Y","�",Translate::trnsAll),
		LangType("'","�",Translate::trnsAll),
		LangType("''","�",Translate::trnsAll),
		LangType("eh","�",Translate::trnsAll),
		LangType("eH","�",Translate::trnsTrnstoRus),
		LangType("EH","�",Translate::trnsAll),
		LangType("Eh","�",Translate::trnsTrnstoRus),
		LangType("ju","�",Translate::trnsAll),
		LangType("jU","�",Translate::trnsTrnstoRus),
		LangType("JU","�",Translate::trnsAll),
		LangType("Ju","�",Translate::trnsTrnstoRus),
		LangType("ja","�",Translate::trnsAll),
		LangType("jA","�",Translate::trnsTrnstoRus),
		LangType("JA","�",Translate::trnsAll),
		LangType("Ja","�",Translate::trnsTrnstoRus),
	};
	profile.m_map.SetData(defMap);
	// Name
	static const char strName[]="GOST";
	lstrcpy(profile.m_strName,strName);
	// Ignore
	static const char strIgnore[LangProfile::nBeginEnd][LangProfile::nIgnore]=
	{
		"**",
		"**",
		"**",
		"**"
	};
	for(int i=0;i<LangProfile::nIgnore;i++)
		lstrcpy(profile.m_strIgnore[i],strIgnore[i]);
}

void Language::ResetQWER(LangProfile& profile)
{
	// Map
	static const LangType defMap[]=
	{
		LangType("`","�",Translate::trnsAll),
		LangType("~","�",Translate::trnsAll),
		LangType("@","\"",Translate::trnsAll),
		LangType("#","�",Translate::trnsAll),
		LangType("$",";",Translate::trnsAll),
		LangType("^",":",Translate::trnsAll),
		LangType("&","?",Translate::trnsAll),
		LangType("|","/",Translate::trnsAll),
		LangType("q","�",Translate::trnsAll),
		LangType("w","�",Translate::trnsAll),
		LangType("e","�",Translate::trnsAll),
		LangType("r","�",Translate::trnsAll),
		LangType("t","�",Translate::trnsAll),
		LangType("y","�",Translate::trnsAll),
		LangType("u","�",Translate::trnsAll),
		LangType("i","�",Translate::trnsAll),
		LangType("o","�",Translate::trnsAll),
		LangType("p","�",Translate::trnsAll),
		LangType("[","�",Translate::trnsAll),
		LangType("{","�",Translate::trnsAll),
		LangType("]","�",Translate::trnsAll),
		LangType("}","�",Translate::trnsAll),
		LangType("a","�",Translate::trnsAll),
		LangType("s","�",Translate::trnsAll),
		LangType("d","�",Translate::trnsAll),
		LangType("f","�",Translate::trnsAll),
		LangType("g","�",Translate::trnsAll),
		LangType("h","�",Translate::trnsAll),
		LangType("j","�",Translate::trnsAll),
		LangType("k","�",Translate::trnsAll),
		LangType("l","�",Translate::trnsAll),
		LangType(";","�",Translate::trnsAll),
		LangType(":","�",Translate::trnsAll),
		LangType("'","�",Translate::trnsAll),
		LangType("\"","�",Translate::trnsAll),
		LangType("z","�",Translate::trnsAll),
		LangType("x","�",Translate::trnsAll),
		LangType("c","�",Translate::trnsAll),
		LangType("v","�",Translate::trnsAll),
		LangType("b","�",Translate::trnsAll),
		LangType("n","�",Translate::trnsAll),
		LangType("m","�",Translate::trnsAll),
		LangType(",","�",Translate::trnsAll),
		LangType("<","�",Translate::trnsAll),
		LangType(".","�",Translate::trnsAll),
		LangType(">","�",Translate::trnsAll),
		LangType("/",".",Translate::trnsAll),
		LangType("?",",",Translate::trnsAll),
		LangType("Q","�",Translate::trnsAll),
		LangType("W","�",Translate::trnsAll),
		LangType("E","�",Translate::trnsAll),
		LangType("R","�",Translate::trnsAll),
		LangType("T","�",Translate::trnsAll),
		LangType("Y","�",Translate::trnsAll),
		LangType("U","�",Translate::trnsAll),
		LangType("I","�",Translate::trnsAll),
		LangType("O","�",Translate::trnsAll),
		LangType("P","�",Translate::trnsAll),
		LangType("A","�",Translate::trnsAll),
		LangType("S","�",Translate::trnsAll),
		LangType("D","�",Translate::trnsAll),
		LangType("F","�",Translate::trnsAll),
		LangType("G","�",Translate::trnsAll),
		LangType("H","�",Translate::trnsAll),
		LangType("J","�",Translate::trnsAll),
		LangType("K","�",Translate::trnsAll),
		LangType("L","�",Translate::trnsAll),
		LangType("Z","�",Translate::trnsAll),
		LangType("X","�",Translate::trnsAll),
		LangType("C","�",Translate::trnsAll),
		LangType("V","�",Translate::trnsAll),
		LangType("B","�",Translate::trnsAll),
		LangType("N","�",Translate::trnsAll),
		LangType("M","�",Translate::trnsAll),
	};
	profile.m_map.SetData(defMap);
	// Name
	static const char strName[]="QWER-����";
	lstrcpy(profile.m_strName,strName);
	// Ignore
	static const char strIgnore[LangProfile::nBeginEnd][LangProfile::nIgnore]=
	{
		"**",
		"**",
		"**",
		"**"
	};
	for(int i=0;i<LangProfile::nIgnore;i++)
		lstrcpy(profile.m_strIgnore[i],strIgnore[i]);
}

void Language::ResetUser1(LangProfile& profile)
{
	ResetEmpty(profile,"User1");
}

void Language::ResetUser2(LangProfile& profile)
{
	ResetEmpty(profile,"User2");
}

void Language::ResetUser3(LangProfile& profile)
{
	ResetEmpty(profile,"User3");
}

void Language::ResetUser4(LangProfile& profile)
{
	ResetEmpty(profile,"User4");
}

void Language::ResetUser5(LangProfile& profile)
{
	ResetEmpty(profile,"User5");
}

void Language::ResetEmpty(LangProfile& profile,const char* strName)
{
	// Map
	static const LangType defMap[]=
	{
		LangType()
	};
	profile.m_map.SetData(defMap);
	// Name
	lstrcpy(profile.m_strName,strName);
	// Ignore
	static const char strIgnore[LangProfile::nBeginEnd][LangProfile::nIgnore]=
	{
		"**",
		"**",
		"**",
		"**"
	};
	for(int i=0;i<LangProfile::nIgnore;i++)
		lstrcpy(profile.m_strIgnore[i],strIgnore[i]);
}

void Language::ResetProfile(Profiles profile)
{
	static const ResetFunc m_aResetFunc[nProfiles]=
	{
		&Language::ResetStandard,
		&Language::ResetSymbols,
		&Language::ResetGOST,
		&Language::ResetQWER,
		&Language::ResetUser1,
		&Language::ResetUser2,
		&Language::ResetUser3,
		&Language::ResetUser4,
		&Language::ResetUser5,
	};

	(*m_aResetFunc[(int)profile])(*GetProfile(profile));
}

void Language::ResetAll()
{
	for(size_t i=0;i<nProfiles;i++)
		ResetProfile((Language::Profiles)i);
}

void Language::ResetUser()
{
	for(size_t i=Language::profUser1;i<nProfiles;i++)
		ResetProfile((Language::Profiles)i);
}

void Language::Translate(const LangStruct& ls)
{
	// Profile
	if(!ls.GetProfile())
		ls.SetProfile(m_pCurProfile);
	// Empty
	if(ls.Empty())
	{
		lstrcpy(ls.GetOut(),ls.GetIn());
		return;
	}

	NN::AutoArray<char> aInIgnore;
	
	const int i1= ls.GetDirection()==Translate::dirRusToTrns;

	const char* pIn=ls.GetIn();
	char* pOut=ls.GetOut();

	const char* pFromIn = ls.GetProfile()->m_strIgnore[ls.GetDirection()==Translate::dirTrnstoRus?LangProfile::BeginTrns:LangProfile::BeginRus];
	const char* pToIn = ls.GetProfile()->m_strIgnore[ls.GetDirection()==Translate::dirTrnstoRus?LangProfile::EndTrns:LangProfile::EndRus];
	const char* pFromOut = ls.GetProfile()->m_strIgnore[ls.GetDirection()==Translate::dirTrnstoRus?LangProfile::BeginTrns:LangProfile::BeginRus];
	const char* pToOut = ls.GetProfile()->m_strIgnore[ls.GetDirection()==Translate::dirTrnstoRus?LangProfile::EndTrns:LangProfile::EndRus];

	const int nFromIn = lstrlen(pFromIn);
	const int nToIn = lstrlen(pToIn);

	// Lenth array
	size_t aLen[LangMap::nCountInit];
	size_t maxlen=0;
	for(size_t i=0;i<ls.GetProfile()->m_map.GetLast();i++)
	{
		aLen[i]=((LangString*)ls.GetProfile()->m_map[i].Get(i1))->GetLength();
		
		if(maxlen<aLen[i])
			maxlen=aLen[i];
	}

	// Lenth ignore array
	size_t aLenI[LangMap::nCountInit];
	size_t maxlenI=0;
	for(size_t i=0;i<g_Ignore.GetLast();i++)
	{
		aLenI[i]=g_Ignore[i].Get<0>().GetLength();
		
		if(maxlenI<aLenI[i])
			maxlenI=aLenI[i];
	}

	for(size_t iChar=0;*pIn&&iChar<ls.GetCharCount();iChar++)
	{
		// Ignore
		if(!LangStringTraits::CompareArrayLength(pIn,
				pFromIn,LangProfile::nIgnore))
		{
			// Continue
			pIn+=nFromIn;
			// Copy Ignore
			if(g_Options.m_bCopyIgnore)
				iChar+=strcpy_change(&pOut,pFromOut);

			// Copy
			while(*pIn&&
				LangStringTraits::CompareArrayLength(
					pIn,pToIn,LangProfile::nIgnore)&&
					iChar<ls.GetCharCount())
			{
				*pOut++=*pIn++;
				iChar++;
			}
			
			if(!*pIn||iChar>=ls.GetCharCount())
				break;
			pIn+=nToIn;
			
			// Copy Ignore
			if(g_Options.m_bCopyIgnore)
				iChar+=strcpy_change(&pOut,pToOut);
			
			if(!*pIn||iChar>=ls.GetCharCount())
				break;
		}
		// Ignore
		for(size_t lenI=maxlenI;lenI;lenI--)
		{
			for(size_t nItem=0;nItem<g_Ignore.GetLast();nItem++)
			{
				const Translate::LangTranslate& trnsItem=g_Ignore[nItem].Get<1>();
				if(ls.GetDirection()==Translate::dirTrnstoRus)
				{
					if(!(trnsItem&Translate::trnsTrnstoRus))
						continue;
				}
				else
				{
					if(!(trnsItem&Translate::trnsRustoTrns))
						continue;
				}
				
				if(aLenI[nItem] == lenI&&
					!LangStringTraits::CompareArrayLength(pIn,
						g_Ignore[nItem].Get<0>().GetData(),lenI))
				{
					strcpy_change(&pOut,g_Ignore[nItem].Get<0>().GetData());
					pIn+=lenI;
					iChar+=lenI;
					goto lNext;
				}
			}
		}
		// Translate
		for(size_t len=maxlen;len;len--)
		{
			for(size_t nItem=0;nItem<ls.GetProfile()->m_map.GetLast();nItem++)
			{
				// Translate::LangTranslate
				const Translate::LangTranslate& trnsItem=ls.GetProfile()->m_map[nItem].Get<2>();
				if(ls.GetDirection()==Translate::dirTrnstoRus)
				{
					if(!(trnsItem&Translate::trnsTrnstoRus))
						continue;
				}
				else
				{
					if(!(trnsItem&Translate::trnsRustoTrns))
						continue;
				}
				if(aLen[nItem] == len &&
					!LangStringTraits::CompareArrayLength(pIn,
						((LangString*)ls.GetProfile()->m_map[nItem].Get(i1))->GetData(),len))
				{
					LangString* pString=(LangString*)ls.GetProfile()->m_map[nItem].Get(!i1);
					strcpy_change(&pOut,pString->GetData());
					pIn+=len;
					iChar+=len;
					goto lNext;
				}
			}
		}
		*pOut++=*pIn++;
		lNext:;
	}
	// End
	*pOut=0;
}

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
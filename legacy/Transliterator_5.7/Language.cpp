#include "stdafx.h"
#include "language.h"

void Language::ResetStandard(LangProfile& profile)
{
	// Map
	static const LangType defMap[]=
	{
		LangType("a","à",Translate::trnsAll),
		LangType("A","À",Translate::trnsAll),
		LangType("b","á",Translate::trnsAll),
		LangType("B","Á",Translate::trnsAll),
		LangType("c","ö",Translate::trnsAll),
		LangType("C","Ö",Translate::trnsAll),
		LangType("ch","÷",Translate::trnsAll),
		LangType("cH","÷",Translate::trnsTrnstoRus),
		LangType("CH","×",Translate::trnsAll),
		LangType("Ch","×",Translate::trnsTrnstoRus),
		LangType("d","ä",Translate::trnsAll),
		LangType("D","Ä",Translate::trnsAll),
		LangType("e","å",Translate::trnsAll),
		LangType("E","Å",Translate::trnsAll),
		LangType("e'","¸",Translate::trnsAll),
		LangType("E'","¨",Translate::trnsAll),
		LangType("e`","ý",Translate::trnsAll),
		LangType("E`","Ý",Translate::trnsAll),
		LangType("e''","º",Translate::trnsAll),
		LangType("E''","ª",Translate::trnsAll),
		LangType("f","ô",Translate::trnsAll),
		LangType("F","Ô",Translate::trnsAll),
		LangType("g","ã",Translate::trnsAll),
		LangType("G","Ã",Translate::trnsAll),
		LangType("g'`","´",Translate::trnsAll),
		LangType("g`'","´",Translate::trnsTrnstoRus),
		LangType("G'`","¥",Translate::trnsAll),
		LangType("G`'","¥",Translate::trnsTrnstoRus),
		LangType("h","õ",Translate::trnsAll),
		LangType("H","Õ",Translate::trnsAll),
		LangType("i","è",Translate::trnsAll),
		LangType("I","È",Translate::trnsAll),
		LangType("i'","³",Translate::trnsAll),
		LangType("I'","²",Translate::trnsAll),
		LangType("i`","¿",Translate::trnsAll),
		LangType("I`","¯",Translate::trnsAll),
		LangType("j","æ",Translate::trnsAll),
		LangType("J","Æ",Translate::trnsAll),
		LangType("k","ê",Translate::trnsAll),
		LangType("K","Ê",Translate::trnsAll),
		LangType("l","ë",Translate::trnsAll),
		LangType("L","Ë",Translate::trnsAll),
		LangType("m","ì",Translate::trnsAll),
		LangType("M","Ì",Translate::trnsAll),
		LangType("n","í",Translate::trnsAll),
		LangType("N","Í",Translate::trnsAll),
		LangType("o","î",Translate::trnsAll),
		LangType("O","Î",Translate::trnsAll),
		LangType("p","ï",Translate::trnsAll),
		LangType("P","Ï",Translate::trnsAll),
		LangType("q","û",Translate::trnsTrnstoRus),
		LangType("Q","Û",Translate::trnsTrnstoRus),
		LangType("r","ð",Translate::trnsAll),
		LangType("R","Ð",Translate::trnsAll),
		LangType("s","ñ",Translate::trnsAll),
		LangType("S","Ñ",Translate::trnsAll),
		LangType("sh","ø",Translate::trnsAll),
		LangType("sH","ø",Translate::trnsTrnstoRus),
		LangType("SH","Ø",Translate::trnsAll),
		LangType("Sh","Ø",Translate::trnsTrnstoRus),
		LangType("sh''","ù",Translate::trnsTrnstoRus),
		LangType("sH''","ù",Translate::trnsTrnstoRus),
		LangType("Sh''","Ù",Translate::trnsTrnstoRus),
		LangType("SH''","Ù",Translate::trnsTrnstoRus),
		LangType("sch'","ù",Translate::trnsAll),
		LangType("sCh'","ù",Translate::trnsTrnstoRus),
		LangType("scH'","ù",Translate::trnsTrnstoRus),
		LangType("sCH'","ù",Translate::trnsTrnstoRus),
		LangType("Sch'","Ù",Translate::trnsTrnstoRus),
		LangType("SCh'","Ù",Translate::trnsTrnstoRus),
		LangType("ScH'","Ù",Translate::trnsTrnstoRus),
		LangType("SCH'","Ù",Translate::trnsAll),
		LangType("t","ò",Translate::trnsAll),
		LangType("T","Ò",Translate::trnsAll),
		LangType("tc'","ö",Translate::trnsTrnstoRus),
		LangType("tC'","ö",Translate::trnsTrnstoRus),
		LangType("Tc'","Ö",Translate::trnsTrnstoRus),
		LangType("TC'","Ö",Translate::trnsTrnstoRus),
		LangType("u","ó",Translate::trnsAll),
		LangType("U","Ó",Translate::trnsAll),
		LangType("u'","¢",Translate::trnsAll),
		LangType("U'","¡",Translate::trnsAll),
		LangType("v","â",Translate::trnsAll),
		LangType("V","Â",Translate::trnsAll),
		LangType("w","ø",Translate::trnsTrnstoRus),
		LangType("W","Ø",Translate::trnsTrnstoRus),
		LangType("w''","ù",Translate::trnsTrnstoRus),
		LangType("W''","Ù",Translate::trnsTrnstoRus),
		LangType("x","õ",Translate::trnsTrnstoRus),
		LangType("X","Õ",Translate::trnsTrnstoRus),
		LangType("y","é",Translate::trnsAll),
		LangType("Y","É",Translate::trnsAll),
		LangType("ya","ÿ",Translate::trnsAll),
		LangType("yA","ÿ",Translate::trnsTrnstoRus),
		LangType("YA","ß",Translate::trnsAll),
		LangType("Ya","ß",Translate::trnsTrnstoRus),
		LangType("yu","þ",Translate::trnsAll),
		LangType("yU","þ",Translate::trnsTrnstoRus),
		LangType("YU","Þ",Translate::trnsAll),
		LangType("Yu","Þ",Translate::trnsTrnstoRus),
		LangType("y'","û",Translate::trnsAll),
		LangType("Y'","Û",Translate::trnsAll),
		LangType("z","ç",Translate::trnsAll),
		LangType("Z","Ç",Translate::trnsAll),
		LangType("'","ü",Translate::trnsAll),
		LangType("''","Ü",Translate::trnsAll),
		LangType("`","ú",Translate::trnsAll),
		LangType("``","Ú",Translate::trnsAll),
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
		LangType("a","à",Translate::trnsAll),
		LangType("A","À",Translate::trnsAll),
		LangType("6","á",Translate::trnsAll),
		LangType("6","Á",Translate::trnsRustoTrns),
		LangType("B","Â",Translate::trnsAll),
		LangType("Â","â",Translate::trnsRustoTrns),
		LangType("r","ã",Translate::trnsAll),
		LangType("r","Ã",Translate::trnsRustoTrns),
		LangType("D","ä",Translate::trnsAll),
		LangType("D","Ä",Translate::trnsRustoTrns),
		LangType("e","å",Translate::trnsAll),
		LangType("E","Å",Translate::trnsAll),
		LangType("e","¸",Translate::trnsRustoTrns),
		LangType("E","¨",Translate::trnsRustoTrns),
		LangType(">|<","æ",Translate::trnsAll),
		LangType("}|{","Æ",Translate::trnsAll),
		LangType(">-|-<","æ",Translate::trnsRustoTrns),
		LangType("}-|-{","Æ",Translate::trnsTrnstoRus),
		LangType("3","ç",Translate::trnsAll),
		LangType("3","Ç",Translate::trnsRustoTrns),
		LangType("u","è",Translate::trnsAll),
		LangType("U","È",Translate::trnsAll),
		LangType("u'","é",Translate::trnsAll),
		LangType("U'","É",Translate::trnsAll),
		LangType("u`","é",Translate::trnsTrnstoRus),
		LangType("U`","É",Translate::trnsTrnstoRus),
		LangType("k","ê",Translate::trnsAll),
		LangType("K","Ê",Translate::trnsAll),
		LangType("/\\","ë",Translate::trnsAll),
		LangType("JI","Ë",Translate::trnsAll),
		LangType("m","ì",Translate::trnsAll),
		LangType("M","Ì",Translate::trnsAll),
		LangType("H","í",Translate::trnsAll),
		LangType("H","Í",Translate::trnsRustoTrns),
		LangType("o","î",Translate::trnsAll),
		LangType("O","Î",Translate::trnsAll),
		LangType("n","ï",Translate::trnsAll),
		LangType("n","Ï",Translate::trnsRustoTrns),
		LangType("p","ð",Translate::trnsAll),
		LangType("P","Ð",Translate::trnsAll),
		LangType("c","ñ",Translate::trnsAll),
		LangType("C","Ñ",Translate::trnsAll),
		LangType("T","ò",Translate::trnsAll),
		LangType("T","Ò",Translate::trnsRustoTrns),
		LangType("y","ó",Translate::trnsAll),
		LangType("Y","Ó",Translate::trnsAll),
		LangType("f","ô",Translate::trnsAll),
		LangType("F","Ô",Translate::trnsAll),
		LangType("<|>","ô",Translate::trnsAll),
		LangType("<I>","Ô",Translate::trnsAll),
		LangType("x","õ",Translate::trnsAll),
		LangType("X","Õ",Translate::trnsAll),
		LangType("L|","ö",Translate::trnsAll),
		LangType("L|","Ö",Translate::trnsRustoTrns),
		LangType("4","÷",Translate::trnsAll),
		LangType("4","×",Translate::trnsRustoTrns),
		LangType("LLI","Ø",Translate::trnsAll),
		LangType("w","ø",Translate::trnsAll),
		LangType("LL|","ù",Translate::trnsAll),
		LangType("LL|","Ù",Translate::trnsRustoTrns),
		LangType("\\","ú",Translate::trnsAll),
		LangType("\\\\","Ú",Translate::trnsRustoTrns),
		LangType("bI","û",Translate::trnsAll),
		LangType("bI","Û",Translate::trnsRustoTrns),
		LangType("b","ü",Translate::trnsAll),
		LangType("b","Ü",Translate::trnsRustoTrns),
		LangType("e","ý",Translate::trnsRustoTrns),
		LangType("E","Ý",Translate::trnsRustoTrns),
		LangType("IO","þ",Translate::trnsAll),
		LangType("IO","Þ",Translate::trnsRustoTrns),
		LangType("I-O","þ",Translate::trnsTrnstoRus),
		LangType("I-O","Þ",Translate::trnsRustoTrns),
		LangType("9I","ÿ",Translate::trnsAll),
		LangType("9I","ß",Translate::trnsRustoTrns),
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
		LangType("a","à",Translate::trnsAll),
		LangType("A","À",Translate::trnsAll),
		LangType("b","á",Translate::trnsAll),
		LangType("B","Á",Translate::trnsAll),
		LangType("v","â",Translate::trnsAll),
		LangType("V","Â",Translate::trnsAll),
		LangType("g","ã",Translate::trnsAll),
		LangType("G","Ã",Translate::trnsAll),
		LangType("d","ä",Translate::trnsAll),
		LangType("D","Ä",Translate::trnsAll),
		LangType("e","å",Translate::trnsAll),
		LangType("E","Å",Translate::trnsAll),
		LangType("jo","¸",Translate::trnsAll),
		LangType("jO","¸",Translate::trnsTrnstoRus),
		LangType("JO","¨",Translate::trnsAll),
		LangType("Jo","¸",Translate::trnsTrnstoRus),
		LangType("zh","æ",Translate::trnsAll),
		LangType("zH","æ",Translate::trnsTrnstoRus),
		LangType("ZH","Æ",Translate::trnsAll),
		LangType("Zh","Æ",Translate::trnsTrnstoRus),
		LangType("z","ç",Translate::trnsAll),
		LangType("Z","Ç",Translate::trnsAll),
		LangType("i","è",Translate::trnsAll),
		LangType("I","È",Translate::trnsAll),
		LangType("jj","é",Translate::trnsAll),
		LangType("jJ","é",Translate::trnsTrnstoRus),
		LangType("JJ","É",Translate::trnsAll),
		LangType("Jj","É",Translate::trnsTrnstoRus),
		LangType("k","ê",Translate::trnsAll),
		LangType("K","Ê",Translate::trnsAll),
		LangType("l","ë",Translate::trnsAll),
		LangType("L","Ë",Translate::trnsAll),
		LangType("m","ì",Translate::trnsAll),
		LangType("M","Ì",Translate::trnsAll),
		LangType("n","í",Translate::trnsAll),
		LangType("N","Í",Translate::trnsAll),
		LangType("o","î",Translate::trnsAll),
		LangType("O","Î",Translate::trnsAll),
		LangType("p","ï",Translate::trnsAll),
		LangType("P","Ï",Translate::trnsAll),
		LangType("r","ð",Translate::trnsAll),
		LangType("R","Ð",Translate::trnsAll),
		LangType("s","ñ",Translate::trnsAll),
		LangType("S","Ñ",Translate::trnsAll),
		LangType("t","ò",Translate::trnsAll),
		LangType("T","Ò",Translate::trnsAll),
		LangType("u","ó",Translate::trnsAll),
		LangType("U","Ó",Translate::trnsAll),
		LangType("f","ô",Translate::trnsAll),
		LangType("F","Ô",Translate::trnsAll),
		LangType("kh","õ",Translate::trnsAll),
		LangType("kH","õ",Translate::trnsTrnstoRus),
		LangType("KH","Õ",Translate::trnsAll),
		LangType("Kh","Õ",Translate::trnsTrnstoRus),
		LangType("c","ö",Translate::trnsAll),
		LangType("C","Ö",Translate::trnsAll),
		LangType("ch","÷",Translate::trnsAll),
		LangType("cH","÷",Translate::trnsTrnstoRus),
		LangType("CH","×",Translate::trnsAll),
		LangType("Ch","×",Translate::trnsTrnstoRus),
		LangType("sh","ø",Translate::trnsAll),
		LangType("sH","ø",Translate::trnsTrnstoRus),
		LangType("SH","Ø",Translate::trnsAll),
		LangType("Sh","Ø",Translate::trnsTrnstoRus),
		LangType("shh","ù",Translate::trnsAll),
		LangType("shH","ù",Translate::trnsTrnstoRus),
		LangType("sHh","ù",Translate::trnsTrnstoRus),
		LangType("sHH","ù",Translate::trnsTrnstoRus),
		LangType("SHH","Ù",Translate::trnsAll),
		LangType("SHh","Ù",Translate::trnsTrnstoRus),
		LangType("ShH","Ù",Translate::trnsTrnstoRus),
		LangType("Shh","Ù",Translate::trnsTrnstoRus),
		LangType("\"","ú",Translate::trnsAll),
		LangType("\"\"","Ú",Translate::trnsAll),
		LangType("y","û",Translate::trnsAll),
		LangType("Y","Û",Translate::trnsAll),
		LangType("'","ü",Translate::trnsAll),
		LangType("''","Ü",Translate::trnsAll),
		LangType("eh","ý",Translate::trnsAll),
		LangType("eH","ý",Translate::trnsTrnstoRus),
		LangType("EH","Ý",Translate::trnsAll),
		LangType("Eh","Ý",Translate::trnsTrnstoRus),
		LangType("ju","þ",Translate::trnsAll),
		LangType("jU","þ",Translate::trnsTrnstoRus),
		LangType("JU","Þ",Translate::trnsAll),
		LangType("Ju","Þ",Translate::trnsTrnstoRus),
		LangType("ja","ÿ",Translate::trnsAll),
		LangType("jA","ÿ",Translate::trnsTrnstoRus),
		LangType("JA","ß",Translate::trnsAll),
		LangType("Ja","ß",Translate::trnsTrnstoRus),
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
		LangType("`","¸",Translate::trnsAll),
		LangType("~","¨",Translate::trnsAll),
		LangType("@","\"",Translate::trnsAll),
		LangType("#","¹",Translate::trnsAll),
		LangType("$",";",Translate::trnsAll),
		LangType("^",":",Translate::trnsAll),
		LangType("&","?",Translate::trnsAll),
		LangType("|","/",Translate::trnsAll),
		LangType("q","é",Translate::trnsAll),
		LangType("w","ö",Translate::trnsAll),
		LangType("e","ó",Translate::trnsAll),
		LangType("r","ê",Translate::trnsAll),
		LangType("t","å",Translate::trnsAll),
		LangType("y","í",Translate::trnsAll),
		LangType("u","ã",Translate::trnsAll),
		LangType("i","ø",Translate::trnsAll),
		LangType("o","ù",Translate::trnsAll),
		LangType("p","ç",Translate::trnsAll),
		LangType("[","õ",Translate::trnsAll),
		LangType("{","Õ",Translate::trnsAll),
		LangType("]","ú",Translate::trnsAll),
		LangType("}","Ú",Translate::trnsAll),
		LangType("a","ô",Translate::trnsAll),
		LangType("s","û",Translate::trnsAll),
		LangType("d","â",Translate::trnsAll),
		LangType("f","à",Translate::trnsAll),
		LangType("g","ï",Translate::trnsAll),
		LangType("h","ð",Translate::trnsAll),
		LangType("j","î",Translate::trnsAll),
		LangType("k","ë",Translate::trnsAll),
		LangType("l","ä",Translate::trnsAll),
		LangType(";","æ",Translate::trnsAll),
		LangType(":","Æ",Translate::trnsAll),
		LangType("'","ý",Translate::trnsAll),
		LangType("\"","Ý",Translate::trnsAll),
		LangType("z","ÿ",Translate::trnsAll),
		LangType("x","÷",Translate::trnsAll),
		LangType("c","ñ",Translate::trnsAll),
		LangType("v","ì",Translate::trnsAll),
		LangType("b","è",Translate::trnsAll),
		LangType("n","ò",Translate::trnsAll),
		LangType("m","ü",Translate::trnsAll),
		LangType(",","á",Translate::trnsAll),
		LangType("<","Á",Translate::trnsAll),
		LangType(".","þ",Translate::trnsAll),
		LangType(">","Þ",Translate::trnsAll),
		LangType("/",".",Translate::trnsAll),
		LangType("?",",",Translate::trnsAll),
		LangType("Q","É",Translate::trnsAll),
		LangType("W","Ö",Translate::trnsAll),
		LangType("E","Ó",Translate::trnsAll),
		LangType("R","Ê",Translate::trnsAll),
		LangType("T","Å",Translate::trnsAll),
		LangType("Y","Í",Translate::trnsAll),
		LangType("U","Ã",Translate::trnsAll),
		LangType("I","Ø",Translate::trnsAll),
		LangType("O","Ù",Translate::trnsAll),
		LangType("P","Ç",Translate::trnsAll),
		LangType("A","Ô",Translate::trnsAll),
		LangType("S","Û",Translate::trnsAll),
		LangType("D","Â",Translate::trnsAll),
		LangType("F","À",Translate::trnsAll),
		LangType("G","Ï",Translate::trnsAll),
		LangType("H","Ð",Translate::trnsAll),
		LangType("J","Î",Translate::trnsAll),
		LangType("K","Ë",Translate::trnsAll),
		LangType("L","Ä",Translate::trnsAll),
		LangType("Z","ß",Translate::trnsAll),
		LangType("X","×",Translate::trnsAll),
		LangType("C","Ñ",Translate::trnsAll),
		LangType("V","Ì",Translate::trnsAll),
		LangType("B","È",Translate::trnsAll),
		LangType("N","Ò",Translate::trnsAll),
		LangType("M","Ü",Translate::trnsAll),
	};
	profile.m_map.SetData(defMap);
	// Name
	static const char strName[]="QWER-ÉÖÓÊ";
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
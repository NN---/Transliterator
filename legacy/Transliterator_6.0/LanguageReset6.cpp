#include "stdafx.h"

#include "language.h"

// DOS-Win
void Language::Reset6(LangProfile& rProfile)
{
	ResetTranslation6(rProfile);
	ResetIgnore6(rProfile);
	ResetIgnoreText6(rProfile);
	ResetName6(rProfile);
}

void Language::ResetTranslation6(LangProfile& rProfile)
{
	static const LangTypeNS aTranslation[] = 
	{
		LangTypeNS(L"‡",L"†",Translate::trnsAll),
		LangTypeNS(L"°",L"·",Translate::trnsAll),
		LangTypeNS(L"¢",L"‚",Translate::trnsAll),
		LangTypeNS(L"£",L"„",Translate::trnsAll),
		LangTypeNS(L"§",L"‰",Translate::trnsAll),
		LangTypeNS(L"•",L"Â",Translate::trnsAll),
		LangTypeNS(L"¶",L"Ê",Translate::trnsAll),
		LangTypeNS(L"ß",L"Á",Translate::trnsAll),
		LangTypeNS(L"®",L"Ë",Translate::trnsAll),
		LangTypeNS(L"©",L"È",Translate::trnsAll),
		LangTypeNS(L"™",L"Í",Translate::trnsAll),
		LangTypeNS(L"´",L"Î",Translate::trnsAll),
		LangTypeNS(L"¨",L"Ï",Translate::trnsAll),
		LangTypeNS(L"≠",L"Ì",Translate::trnsAll),
		LangTypeNS(L"Æ",L"Ó",Translate::trnsAll),
		LangTypeNS(L"Ø",L"Ô",Translate::trnsAll),
		LangTypeNS(L"‡",L"",Translate::trnsAll),
		LangTypeNS(L"·",L"Ò",Translate::trnsAll),
		LangTypeNS(L"‚",L"Ú",Translate::trnsAll),
		LangTypeNS(L"„",L"Û",Translate::trnsAll),
		LangTypeNS(L"‰",L"Ù",Translate::trnsAll),
		LangTypeNS(L"Â",L"ı",Translate::trnsAll),
		LangTypeNS(L"Ê",L"ˆ",Translate::trnsAll),
		LangTypeNS(L"Á",L"˜",Translate::trnsAll),
		LangTypeNS(L"Ë",L"¯",Translate::trnsAll),
		LangTypeNS(L"È",L"˘",Translate::trnsAll),
		LangTypeNS(L"Í",L"˙",Translate::trnsAll),
		LangTypeNS(L"Î",L"˚",Translate::trnsAll),
		LangTypeNS(L"Ï",L"¸",Translate::trnsAll),
		LangTypeNS(L"Ì",L"˝",Translate::trnsAll),
		LangTypeNS(L"Ó",L"˛",Translate::trnsAll),
		LangTypeNS(L"Ô",L"ˇ",Translate::trnsAll),
		LangTypeNS(L"Ä",L"¿",Translate::trnsAll),
		LangTypeNS(L"Å",L"¡",Translate::trnsAll),
		LangTypeNS(L"Ç",L"¬",Translate::trnsAll),
		LangTypeNS(L"É",L"√",Translate::trnsAll),
		LangTypeNS(L"Ñ",L"ƒ",Translate::trnsAll),
		LangTypeNS(L"Ö",L"≈",Translate::trnsAll),
		LangTypeNS(L"Ü",L"∆",Translate::trnsAll),
		LangTypeNS(L"á",L"«",Translate::trnsAll),
		LangTypeNS(L"à",L"»",Translate::trnsAll),
		LangTypeNS(L"â",L"…",Translate::trnsAll),
		LangTypeNS(L"ä",L" ",Translate::trnsAll),
		LangTypeNS(L"ã",L"À",Translate::trnsAll),
		LangTypeNS(L"å",L"Ã",Translate::trnsAll),
		LangTypeNS(L"ç",L"Õ",Translate::trnsAll),
		LangTypeNS(L"é",L"Œ",Translate::trnsAll),
		LangTypeNS(L"è",L"œ",Translate::trnsAll),
		LangTypeNS(L"ê",L"–",Translate::trnsAll),
		LangTypeNS(L"ë",L"—",Translate::trnsAll),
		LangTypeNS(L"í",L"“",Translate::trnsAll),
		LangTypeNS(L"ì",L"”",Translate::trnsAll),
		LangTypeNS(L"î",L"‘",Translate::trnsAll),
		LangTypeNS(L"ï",L"’",Translate::trnsAll),
		LangTypeNS(L"ñ",L"÷",Translate::trnsAll),
		LangTypeNS(L"ó",L"◊",Translate::trnsAll),
		LangTypeNS(L"ò",L"ÿ",Translate::trnsAll),
		LangTypeNS(L"ô",L"Ÿ",Translate::trnsAll),
		LangTypeNS(L"ö",L"⁄",Translate::trnsAll),
		LangTypeNS(L"õ",L"€",Translate::trnsAll),
		LangTypeNS(L"ú",L"‹",Translate::trnsAll),
		LangTypeNS(L"ù",L"›",Translate::trnsAll),
		LangTypeNS(L"û",L"ﬁ",Translate::trnsAll),
		LangTypeNS(L"ü",L"ﬂ",Translate::trnsAll),
		LangTypeNS(L"Ò",L"∏",Translate::trnsAll),
		LangTypeNS(L"",L"®",Translate::trnsAll),
		LangTypeNS(L"Û",L"∫",Translate::trnsAll),
		LangTypeNS(L"Ú",L"™",Translate::trnsAll),
		LangTypeNS(L"ı",L"ø",Translate::trnsAll),
		LangTypeNS(L"Ù",L"Ø",Translate::trnsAll),
		LangTypeNS(L"˜",L"¢",Translate::trnsAll),
		LangTypeNS(L"ˆ",L"°",Translate::trnsAll),
		LangTypeNS(L"¶",L"π",Translate::trnsAll),
	};
	try
	{
		rProfile.m_aTranslation.assign(aTranslation, NN_ARRAY_END(aTranslation));
	}
	catch(...)
	{
		rProfile.ResetTranslation();
	}
}

void Language::ResetIgnore6(LangProfile& rProfile)
{
	rProfile.ResetIgnore();
}

void Language::ResetIgnoreText6(LangProfile& rProfile)
{
	rProfile.ResetIgnoreText();
}

void Language::ResetName6(LangProfile& rProfile)
{
	rProfile.m_astrLang[0] = "Cyrillic(DOS)";
	rProfile.m_astrLang[1] = "Cyrillic(Win)";
}
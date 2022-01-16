#ifndef __SETTINGS_H__
#define __SETTINGS_H__

#include "langprofile.h"

struct Settings
{
	static const HKEY s_hkProgKey;
	static const TCHAR s_szProgPath[];
	static const TCHAR s_szNNPath[];
	static const TCHAR s_szTransliterator[];
	static const TCHAR s_szRunPath[];

	static const TCHAR* const s_aszLang[];
	static const WCHAR* const s_aszLangF[];
	
	static const TCHAR s_szStorageName[];
	static const TCHAR s_szLangIDName[];
	static const TCHAR s_szIgnoreName[];
	static const TCHAR s_szIgnoreTextName[];
	static const TCHAR s_szLangName[];

	static const TCHAR s_szTxt[];
	static const TCHAR s_szIni[];

	// Storage
	static const TCHAR* const s_aszStorageStg[];
	static const TCHAR s_szOptions[];
	static const TCHAR* const s_aszProfiles[];

	// Profiles
	static const TCHAR s_szTranslationName[];
	static const TCHAR* const s_aszIgnoreName[];
	static const WCHAR* const s_aszIgnoreNameF[];

	// File
	static const WCHAR s_szLangF[];
	static const WCHAR s_szTranslationF[];
	static const WCHAR s_szIgnoreF[];
	static const WCHAR s_szIgnoreTextF[];

	static const WCHAR s_cUnicodeHeader;
	static const WCHAR s_szDivider[];
	static const WCHAR s_szEQ[];
	static const WCHAR s_szNL[];

	static const WCHAR* const s_aszDirDiv[];

	static const TCHAR s_szVersionName[];
	static const TCHAR s_szVersion[];

	static ATL::CRegKey s_regProg;

	static HKEY OpenKeyLoad(HKEY hKey,LPCTSTR szSubKey);
	static HKEY OpenKeySave(HKEY hKey,LPCTSTR szSubKey);

	static HANDLE OpenFileLoad(LPCTSTR szFile);
	static HANDLE OpenFileSave(LPCTSTR  szFile);

	static bool Load();
	static void Save();

	static bool LoadVersion();
	static void LoadStorage();
	static void LoadOptions();
	static void LoadLanguage();
	static void LoadText();
	static void LoadLangID();

	enum ResetFlag
	{
		resetNone		 = 0,
		resetName		 = 1,
		resetTranslation = 2,
		resetIgnore		 = 4,
		resetIgnoreText	 = 8,
		resetAll		 = resetIgnoreText*2 - 1
	};

	static size_t LoadProfileFile(const TCHAR* szProfileName, LangProfile* pProfile);
	static size_t LoadProfileFileData(const WCHAR* pData, LangProfile* pProfile);

	static bool LoadProfileFileName(const WCHAR* pBegin, const WCHAR* pEnd, LangProfile* pProfile);
	static bool LoadProfileFileTranslation(const WCHAR* pBegin, const WCHAR* pEnd, LangProfile* pProfile);
	static bool LoadProfileFileIgnore(const WCHAR* pBegin, const WCHAR* pEnd, LangProfile* pProfile);
	static bool LoadProfileFileIgnoreText(const WCHAR* pBegin, const WCHAR* pEnd, LangProfile* pProfile);

	static bool FindProfileFileSection(const WCHAR* pData, const WCHAR* szSection, const WCHAR** ppBegin, const WCHAR** ppEnd);

    static size_t LoadProfileReg(const TCHAR* szProfileName, LangProfile* pProfile);
	static bool LoadProfileRegTranslation(HKEY hkProfile, LangProfile* pProfile);
	static bool LoadProfileRegIgnore(HKEY hkProfile, LangProfile* pProfile);
	static bool LoadProfileRegIgnoreText(HKEY hkProfile, LangProfile* pProfile);
	static bool LoadProfileRegName(HKEY hkProfile, LangProfile* pProfile);

	static bool ParseLoadTranslation(const WCHAR* pBegin, const WCHAR* pEnd, LangType& item);
	static bool ParseLoadIgnoreText(const WCHAR* pBegin, const WCHAR* pEnd, IgnoreTextType& item);

	static void SaveVersion();
	static void SaveStorage();
	static void SaveOptions();
	static void SaveLanguage();
	static void SaveText();
	static void SaveLangID();

	static void SaveProfileFile(const TCHAR* szProfileName,const LangProfile* pProfile);
	static void PrepareSaveProfileFile(const LangProfile* pProfile,LangString& str);

	static void SaveProfileReg(const TCHAR* szProfileName,const LangProfile* pProfile);
	static void SaveProfileTranslation(HKEY hkProfile, const LangProfile* pProfile);
	static void SaveProfileIgnore(HKEY hkProfile, const LangProfile* pProfile);
	static void SaveProfileIgnoreText(HKEY hkProfile, const LangProfile* pProfile);
	static void SaveProfileLangName(HKEY hkProfile, const LangProfile* pProfile);

	static void ParseSaveTranslation(const LangType& item, LangString &str);
	static void ParseSaveIgnoreText(const IgnoreTextType& item, IgnoreTextString& str);
};

#endif // __SETTINGS_H__
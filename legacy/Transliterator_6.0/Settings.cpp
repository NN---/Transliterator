#include "stdafx.h"

#include "resource.h"
#include "global.h"
#include "makedirection.h"

#include "settings.h"

/*
Registry Format :
HKEY_CURRENT_USER\Software\NN\Transliterator\
	Storage\
		Lang
		Profiles
		Profile[n]
	Path\
		n - Path
	[Profiles]\
		Translation\
			n - LangTop [->] [<-] LangBottom
		Ignore\
			BeginTop
			EndTop
			BeginBottom
			EndBottom
		IgnoreText\
			n - IgnoreText [->] [<-]
		Lang\
			LangTop
			LangBottom

File Format:
[Lang]
LangTop = 
LangBottom = 
[Translation]
LangTop [->] [<-] LangBottom
[Ignore]
BeginTop = 
EndTop = 
BeginBottom = 
EndBottom = 
[IgnoreText]
IgnoreText [->] [<-]
*/

const HKEY Settings::s_hkProgKey = HKEY_CURRENT_USER;
const TCHAR Settings::s_szProgPath[] = _T("Software\\NN\\Transliterator");
const TCHAR Settings::s_szNNPath[] = _T("Software\\NN");
const TCHAR Settings::s_szTransliterator[] = _T("Transliterator");
const TCHAR Settings::s_szRunPath[] = _T("Software\\Microsoft\\Windows\\CurrentVersion\\Run");

const TCHAR* const Settings::s_aszLang[] = 
{
	_T("LangTop"),
	_T("LangBottom")
};

const WCHAR* const Settings::s_aszLangF[] = 
{
	L"LangTop",
	L"LangBottom"
};

const TCHAR Settings::s_szStorageName[] = _T("Storage");
const TCHAR Settings::s_szLangIDName[] = _T("LangID");
const TCHAR Settings::s_szIgnoreName[] = _T("Ignore");
const TCHAR Settings::s_szIgnoreTextName[] = _T("IgnoreText");
const TCHAR Settings::s_szLangName[] = _T("Lang");

const TCHAR Settings::s_szTxt[] = _T(".txt");
const TCHAR Settings::s_szIni[] = _T(".ini");

// Storage
const TCHAR* const Settings::s_aszStorageStg[] = 
{
	_T("TextStorage"),
	_T("ProfilesStorage")
};
const TCHAR Settings::s_szOptions[] = _T("Options");
const TCHAR* const Settings::s_aszProfiles[] = 
{
	_T("Profile1"),
	_T("Profile2"),
	_T("Profile3"),
	_T("Profile4"),
	_T("Profile5"),
	_T("Profile6"),
	_T("Profile7"),
	_T("Profile8"),
	_T("Profile9"),
	_T("Profile10")
};

// Profiles
const TCHAR Settings::s_szTranslationName[] = _T("Translation");

const TCHAR* const Settings::s_aszIgnoreName[] = 
{
	_T("BeginTop"),
	_T("EndTop"),
	_T("BeginBottom"),
	_T("EndBottom")
};

const WCHAR* const Settings::s_aszIgnoreNameF[] = 
{
	L"BeginTop",
	L"EndTop",
	L"BeginBottom",
	L"EndBottom"
};

const WCHAR Settings::s_szLangF[] = L"[Lang]";
const WCHAR Settings::s_szTranslationF[] = L"[Translation]";
const WCHAR Settings::s_szIgnoreF[] = L"[Ignore]";
const WCHAR Settings::s_szIgnoreTextF[] = L"[IgnoreText]";

const WCHAR Settings::s_cUnicodeHeader = L'\xFEFF';
const WCHAR Settings::s_szDivider[] = L" ";
const WCHAR Settings::s_szEQ[] = L"=";
const WCHAR Settings::s_szNL[] = L"\r\n";

const WCHAR* const Settings::s_aszDirDiv[] = 
{
	L"",		// None
	L" -> ",	// Top to Bottom
	L" <- ",	// Bottom to Top
	L" -> <- "	// Two way
};

const TCHAR Settings::s_szVersionName[] = _T("Version");
const TCHAR Settings::s_szVersion[] = _T("6.00");

ATL::CRegKey Settings::s_regProg;

HKEY Settings::OpenKeyLoad(HKEY hKey , LPCTSTR szSubKey)
{
	HKEY hKeyResult;
	::RegOpenKeyEx(
		hKey,
		szSubKey,
		REG_OPTION_NON_VOLATILE,
		KEY_READ,
		&hKeyResult);
	return hKeyResult;
}

HKEY Settings::OpenKeySave(HKEY hKey , LPCTSTR szSubKey)
{
	HKEY hKeyResult;
	
	::RegDeleteKey(hKey , szSubKey);

	::RegCreateKeyEx(
		hKey,
		szSubKey,
		NULL,
		NULL,
		REG_OPTION_NON_VOLATILE,
		KEY_WRITE,
		NULL,
		&hKeyResult,
		NULL);
	return hKeyResult;
}

HANDLE Settings::OpenFileLoad(LPCTSTR szFile)
{
	return ::CreateFile(
		szFile,
		GENERIC_READ,
		0,
		0,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		0);
}

HANDLE Settings::OpenFileSave(LPCTSTR szFile)
{
	HANDLE hFile = 
		::CreateFile(
			szFile,
			GENERIC_WRITE,
			0,
			0,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			0);

	if(hFile != INVALID_HANDLE_VALUE)
	{
		::SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
		::SetEndOfFile(hFile);
	}

	return hFile;
}

bool Settings::Load()
{
	s_regProg.Attach(OpenKeyLoad(s_hkProgKey, s_szProgPath));

	if(!LoadVersion())
		return false;

	LoadStorage();
	LoadOptions();
	LoadLanguage();
	LoadText();
	LoadLangID();

	g_Language.SetCurProfile(g_Options.m_nCurProfile);
	g_UpdateOptions.Reset();
	g_OldStorage = g_Storage;

	s_regProg.Close();

	return true;
}

void Settings::Save()
{
	s_regProg.Attach(OpenKeySave(s_hkProgKey,s_szProgPath));

	SaveVersion();
	SaveStorage();
	SaveOptions();
	SaveLanguage();
	SaveText();	
	SaveLangID();

	s_regProg.Close();
}

bool Settings::LoadVersion()
{
	do
	{
		if(!s_regProg)
			break;

		DWORD size;
		if(s_regProg.QueryStringValue(s_szVersionName,NULL,&size))
			break;
		
		const DWORD sizeVersion = sizeof(s_szVersion)/sizeof(s_szVersion[0]);
		if(size != sizeVersion)
			break;
	
		TCHAR szVersion[sizeVersion];
		if(s_regProg.QueryStringValue(s_szVersionName,szVersion,&size))
			break;

		if(_tcscmp(szVersion,s_szVersion))
		{
			LangStringT strCaption;
			NN::WndLoadString(IDR_TRANSLITERATOR,strCaption);

			LangStringT strText;
			NN::WndLoadString(IDS_NEWVERSION,strText);

			if(::MessageBox(
				NULL,
				strText.c_str(),
				strCaption.c_str(),
				MB_YESNO|MB_ICONINFORMATION) == IDYES)
				break;
			else
				return false;
		}
		return true;
	}while(false);

	s_regProg.Close();

	ATL::CRegKey regNN;
	if(!regNN.Open(s_hkProgKey,s_szNNPath,KEY_WRITE))
		regNN.RecurseDeleteKey(s_szTransliterator);

	return true;
}

void Settings::LoadStorage()
{
	do
	{
		if(!s_regProg)
			break;

		ATL::CRegKey regStorage(OpenKeyLoad(s_regProg,s_szStorageName));
		if(!regStorage)
			break;

		// Storage
		for(size_t i=0; i<Storage::nStg; ++i)
			if(regStorage.QueryDWORDValue(s_aszStorageStg[i],(DWORD&)g_Storage.m_stg[i]))
				g_Storage.ResetStg(i);

		// Language
		for(size_t i=0; i<2; ++i)
		{
			ULONG size;
			regStorage.QueryStringValue(s_aszLang[i],NULL,&size);

			try
			{
				std::vector<TCHAR> aLang(size);

				if(regStorage.QueryStringValue(s_aszLang[i],&aLang[0],&size))
					throw 0;

				NN::vector_to_string(aLang,g_Storage.m_astrLang[i]);
			}
			catch(...)
			{
				g_Storage.ResetLang(i);
			}
		}

		// Profiles
		for(size_t i=0; i<Language::nProfiles; ++i)
		{
			ULONG size;
			regStorage.QueryStringValue(s_aszProfiles[i],NULL,&size);
			
			try
			{
				std::vector<TCHAR> aProfile(size);

				if(regStorage.QueryStringValue(
					s_aszProfiles[i],
					&aProfile[0],
					&size))
					throw 0;

				NN::vector_to_string(aProfile,g_Storage.m_astrProfile[i]);
			}
			catch(...)
			{
				g_Storage.ResetProfile(i);
			}
		}

		return;
	}
	while(false);

	g_Storage.Reset();
}

void Settings::LoadOptions()
{
	do{
		if(!s_regProg)
			break;

		DWORD size = sizeof(g_Options);
		LONG lRes = s_regProg.QueryBinaryValue(s_szOptions,&g_Options,&size);
		if(lRes||size != sizeof(g_Options))
			break;

		return;
	}while(false);
		
	g_Options.Reset();
}

void Settings::LoadLanguage()
{
	size_t (*pFuncLoad)(const TCHAR*, LangProfile*) = 
			g_Storage.m_stg[Storage::stgProfiles] == Storage::stgRegistry?
			LoadProfileReg:
			LoadProfileFile;

	for(size_t i=0 ;i<Language::nProfiles; ++i)
	{
		LangProfile* pProfile = g_Language.GetProfile(i);
		
		size_t reset = (*pFuncLoad)(g_Storage.m_astrProfile[i].c_str(),pProfile);
		
		if(reset & resetName)
			Language::ResetName(i, *pProfile);
		if(reset & resetTranslation)
			Language::ResetTranslation(i, *pProfile);
		if(reset & resetIgnore)
			Language::ResetIgnore(i, *pProfile);
		if(reset & resetIgnoreText)
			Language::ResetIgnoreText(i, *pProfile);
	}
}

void Settings::LoadText()
{
	if(!g_Options.m_bSaveText)
		return;

	if(g_Storage.m_stg[Storage::stgText] == Storage::stgRegistry)
	{
		if(!s_regProg)
			return;
		
		try
		{
			for(size_t i=0; i<2; ++i)
			{
				DWORD size;
				if(s_regProg.QueryBinaryValue(
					g_Storage.m_astrLang[i].c_str(),
					NULL,
					&size))
					continue;
				g_Text[i].resize(size/sizeof(wchar_t)+1);
				
				if(s_regProg.QueryBinaryValue(
					g_Storage.m_astrLang[i].c_str(),
					&g_Text[i][0],
					&size))
				{
					g_Text[i].clear();
					continue;
				}
				g_Text[i][g_Text[i].size()-1] = 0;
			}
		}
		catch(...)
		{
		}
	}
	else
	{
		for(size_t i=0; i<2; ++i)
		{
			ATL::CAtlFile file(OpenFileLoad(g_Storage.m_astrLang[i].c_str()));
			if(file == INVALID_HANDLE_VALUE)
				continue;
			if(::GetFileSize(file,NULL)<2)
				continue;

			file.Seek(2,FILE_BEGIN);
			DWORD dwSize = ::GetFileSize(file,NULL)-2;
			try
			{
				g_Text[i].resize(dwSize/sizeof(wchar_t)+1);
				if(file.Read(&g_Text[i][0],dwSize*sizeof(wchar_t),NULL))
					continue;
				g_Text[i][g_Text[i].size()-1] = 0;
			}
			catch(...)
			{
			}
		}
	}
}

void Settings::LoadLangID()
{
	do
	{
		if(!s_regProg)
			break;
	
		DWORD size = sizeof(g_LangID);
		LONG lRes = s_regProg.QueryBinaryValue(s_szLangIDName,&g_LangID,&size);
		if(lRes||size != sizeof(g_LangID))
			break;

		return;
	}while(false);

	g_LangID = g_LangDefault;
}

size_t Settings::LoadProfileFile(const TCHAR* szProfileName, LangProfile* pProfile)
{
	size_t reset = resetAll;

	// Prepare
	LangStringT strProfileName = szProfileName;
	strProfileName+= s_szIni;

	// Open
	ATL::CAtlFile fileProfile(OpenFileLoad(strProfileName.c_str()));
	if(fileProfile == INVALID_HANDLE_VALUE)
		return reset;

	// Map
	ATL::CAtlFileMapping<> fmProfile;
	if(fmProfile.MapFile(fileProfile) != S_OK)
		return reset;
	
	const bool bUnicode  = 
		memcmp(fmProfile,&s_cUnicodeHeader,sizeof(s_cUnicodeHeader))?false:true;

	// Copy to memory
	NN::CharAWT<WCHAR> caw;

	if(!bUnicode)
		caw.SetData(
			reinterpret_cast<const CHAR*>(fmProfile.GetData()),
			fmProfile.GetMappingSize());
	else
		caw.SetData(
			reinterpret_cast<const WCHAR*>(fmProfile.GetData())+
				sizeof(s_cUnicodeHeader)/sizeof(WCHAR),
			fmProfile.GetMappingSize());
	
	// Closing file
	fmProfile.Unmap();
	fileProfile.Close();

	// Parsing
	reset = LoadProfileFileData(caw.GetData(), pProfile);
	
	return reset;
}

size_t Settings::LoadProfileFileData(const WCHAR* pData, LangProfile* pProfile)
{
	size_t reset = resetAll;
	
	const WCHAR* pBegin = NULL;
	const WCHAR* pEnd   = NULL;

	// Lang
	if(FindProfileFileSection(pData, s_szLangF, &pBegin, &pEnd))
		if(LoadProfileFileName(pBegin + NN_ARRAY_LENGTH_1(s_szNL), pEnd, pProfile))
			reset&= ~resetName;

	// Translation
	if(FindProfileFileSection(pData, s_szTranslationF, &pBegin, &pEnd))
		if(LoadProfileFileTranslation(pBegin + NN_ARRAY_LENGTH_1(s_szNL), pEnd, pProfile))
			reset&= ~resetTranslation;

	// Ignore
	if(FindProfileFileSection(pData, s_szIgnoreF, &pBegin, &pEnd))
		if(LoadProfileFileIgnore(pBegin + NN_ARRAY_LENGTH_1(s_szNL), pEnd, pProfile))
			reset&= ~resetIgnore;

	// IgnoreText
	if(FindProfileFileSection(pData, s_szIgnoreTextF, &pBegin, &pEnd))
		if(LoadProfileFileIgnoreText(pBegin + NN_ARRAY_LENGTH_1(s_szNL), pEnd, pProfile))
			reset&= ~resetIgnoreText;

	return reset;
}

bool Settings::LoadProfileFileName(const WCHAR* pBegin, const WCHAR* pEnd, LangProfile* pProfile)
{
	if(NN::count(pBegin, pEnd, s_szNL, NN_ARRAY_END_1(s_szNL)) != 
		NN_ARRAY_LENGTH(pProfile->m_astrLang))
		return false;

	try
	{
		const WCHAR* pFind = pBegin;
		
		pFind = std::search(pBegin, pEnd, s_szNL, NN_ARRAY_END_1(s_szNL));

	}
	catch(...)
	{
		for(size_t i=0; i<NN_ARRAY_LENGTH(pProfile->m_astrLang); ++i)
			pProfile->m_astrLang[i].clear();
	}
	
	return false;
}

bool Settings::LoadProfileFileTranslation(const WCHAR* pBegin, const WCHAR* pEnd, LangProfile* pProfile)
{
	const size_t nItems = NN::count(pBegin, pEnd, s_szNL, NN_ARRAY_END_1(s_szNL));
	if(!nItems)
		return false;

	pProfile->m_aTranslation.reserve(nItems);
	
	const WCHAR* pItem = pBegin;
	while(pItem != pEnd)
	{
		const WCHAR* pItemEnd = wcsstr(pItem, s_szNL);
		if(pItemEnd)
		{	
			LangType item(L"", L"", Translate::trnsNone);
		
			if(ParseLoadTranslation(pItem, pItemEnd, item))
				pProfile->m_aTranslation.push_back(item);
		
			pItem = pItemEnd + NN_ARRAY_LENGTH_1(s_szNL);
		}
	}
			
	return pProfile->m_aTranslation.size() != 0;
}

bool Settings::LoadProfileFileIgnore(const WCHAR* pBegin, const WCHAR* pEnd, LangProfile* pProfile)
{
	bool b = false;
/*	for(size_t i=0; i<LangProfile::nIgnore; ++i)
	{
		GetStringValue(pBegin, pEnd, s_aszIgnoreNameF[i], pProfile->m_astrIgnore[i]);
		
		if(pProfile->m_astrIgnore[i].size())
			true;
	}
*/
	return b;
}

bool Settings::LoadProfileFileIgnoreText(const WCHAR* pBegin, const WCHAR* pEnd, LangProfile* pProfile)
{
	const size_t nItems = NN::count(pBegin, pEnd, s_szNL, NN_ARRAY_END_1(s_szNL));
	if(!nItems)
		return false;

	pProfile->m_aTranslation.reserve(nItems);
	
	const WCHAR* pItem = pBegin;
	while(pItem != pEnd)
	{
		const WCHAR* pItemEnd = wcsstr(pItem, s_szNL);
		if(pItemEnd)
		{	
			IgnoreTextType item(L"", Translate::trnsNone);
		
			if(ParseLoadIgnoreText(pItem, pItemEnd+1, item))
				pProfile->m_aIgnoreText.push_back(item);
		
			pItem = pItemEnd + NN_ARRAY_LENGTH_1(s_szNL);
		}
	}
			
	return pProfile->m_aTranslation.size() != 0;
}

bool Settings::FindProfileFileSection(const WCHAR* pData, const WCHAR* szSection, const WCHAR** ppBegin, const WCHAR** ppEnd)
{
	// Begin
	const WCHAR* pBegin = wcsstr(pData, szSection);
	if(!pBegin)
	{
		*ppBegin = *ppEnd = NULL;
		return false;
	}
	*ppBegin = pBegin + wcslen(szSection); 

	// End
	pData = *ppBegin;
	while(*pData)
	{
		// Read line
		const WCHAR* pLineEnd = wcsstr(pData, s_szNL);
		if(!pLineEnd)
			pLineEnd = &pData[wcslen(pData)];

		// Check
		if(pData[0] == '[' && wcschr(pData, ']') < pLineEnd)
		{
			*ppEnd = pData;
			return true;
		}

		// Next line
		pData = pLineEnd + NN_ARRAY_LENGTH_1(s_szNL);
	}
	// Reached end
	*ppEnd = &pData[wcslen(pData)];
	
	return *ppBegin != *ppEnd;
}

size_t Settings::LoadProfileReg(const TCHAR* szProfileName, LangProfile* pProfile)
{
	size_t reset = resetAll;
	
	if(!s_regProg)
		return reset;
		
	ATL::CRegKey regProfile(OpenKeyLoad(s_regProg,szProfileName));
	if(!regProfile)
		return reset;

	if(LoadProfileRegName(regProfile, pProfile))
		reset&= ~resetName;
	if(LoadProfileRegTranslation(regProfile, pProfile))
		reset&= ~resetTranslation;
	if(LoadProfileRegIgnore(regProfile, pProfile))
		reset&= ~resetIgnore;
	if(LoadProfileRegIgnoreText(regProfile, pProfile))
		reset&= ~resetIgnoreText;
	
	return reset;
}

bool Settings::LoadProfileRegTranslation(HKEY hkProfile, LangProfile* pProfile)
{
	ATL::CRegKey regTranslation;
	regTranslation.Open(hkProfile,s_szTranslationName);
	if(!regTranslation)
		return false;

	DWORD nValues;
	::RegQueryInfoKey(
		regTranslation,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		&nValues,
		NULL,
		NULL,
		NULL,
		NULL);
	if(!nValues)
		return false;

	TCHAR szName[NN::digits_number<int>::value+1];

	for(DWORD i=0; i<nValues; ++i)
	{
		try
		{
			_itot((int)i, szName, 10);

			DWORD size;
			if(regTranslation.QueryBinaryValue(szName, NULL, &size))
				continue;

			std::vector<WCHAR> aTranslation(size/2);
			if(regTranslation.QueryBinaryValue(szName, &aTranslation[0], &size))
				continue;

			LangType item(L"", L"", Translate::trnsNone);
			if(ParseLoadTranslation(&aTranslation[0],
									&*aTranslation.end(),
									item))
				pProfile->m_aTranslation.push_back(item);
		}
		catch(...)
		{
			continue;
		}
	}

	return true;
}

bool Settings::LoadProfileRegIgnore(HKEY hkProfile, LangProfile* pProfile)
{
	ATL::CRegKey regIgnore;
	regIgnore.Open(hkProfile,s_szIgnoreName);
	if(!regIgnore)
		return false;
	
	for(size_t i=0; i<LangProfile::nIgnore; ++i)
	{
		try
		{
			std::vector<WCHAR> aIgnore;

			DWORD size;
			if(regIgnore.QueryBinaryValue(s_aszIgnoreName[i],NULL,&size))
				return false;
			aIgnore.resize(size);
			if(regIgnore.QueryBinaryValue(s_aszIgnoreName[i],&aIgnore[0],&size))
				return false;

			NN::vector_to_string(aIgnore,pProfile->m_astrIgnore[i]);
		}
		catch(...)
		{
			continue;
		}
	}

	return true;
}

bool Settings::LoadProfileRegIgnoreText(HKEY hkProfile, LangProfile* pProfile)
{
	ATL::CRegKey regIgnoreText;
	regIgnoreText.Open(hkProfile,s_szIgnoreTextName);
	if(!regIgnoreText)
		return false;

	DWORD nValues;
	::RegQueryInfoKey(
		regIgnoreText,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		&nValues,
		NULL,
		NULL,
		NULL,
		NULL);
	if(!nValues)
		return false;

	TCHAR szName[NN::digits_number<DWORD>::value+1];

	for(size_t i=0; i<nValues; ++i)
	{
		ltoa((long)i,szName,10);

		std::vector<WCHAR> aIgnoreText;

		DWORD size;
		if(regIgnoreText.QueryBinaryValue(szName,NULL,&size))
			continue;
		aIgnoreText.resize(size);
		if(regIgnoreText.QueryBinaryValue(szName,&aIgnoreText[0],&size))
			continue;

		IgnoreTextType item(L"",Translate::trnsNone);
		if(ParseLoadIgnoreText(&aIgnoreText[0],
							   &aIgnoreText[aIgnoreText.size()-1],
							   item))
			pProfile->m_aIgnoreText.push_back(item);
	}

	return true;
}

bool Settings::LoadProfileRegName(HKEY hkProfile, LangProfile* pProfile)
{
	ATL::CRegKey regLang;
	regLang.Open(hkProfile,s_szLangName);
	if(!regLang)
		return false;

	try
	{
		for(size_t i=0; i<2; ++i)
		{
			std::vector<TCHAR> aLang;

			DWORD size;
			if(regLang.QueryStringValue(s_aszLang[i],NULL,&size))
				continue;
			aLang.resize(size);
			if(regLang.QueryStringValue(s_aszLang[i],&aLang[0],&size))
				return false;

			NN::vector_to_string(aLang,pProfile->m_astrLang[i]);
		}
	}
	catch(...)
	{
		return false;
	}

	return true;
}

bool Settings::ParseLoadTranslation(const WCHAR* pBegin, const WCHAR* pEnd, LangType& item)
{
	// str - [t] [->] [<-] [b]
	for(size_t i=NN_ARRAY_LENGTH(s_aszDirDiv)-1; i; --i)
	{
		const WCHAR* pFind = std::search(pBegin,
										 pEnd,
										 s_aszDirDiv[i],
										 s_aszDirDiv[i] + wcslen(s_aszDirDiv[i]));

		if(pFind != pEnd)
		{
			item.get<LangPos::Top>().assign(pBegin, pFind);
			item.get<LangPos::Bottom>().assign(pFind + wcslen(s_aszDirDiv[i]), pEnd);
			
			item.get<LangPos::Translation>() = (Translate::Translation)i;

			return true;
		}
	}

	
	return false;
}

bool Settings::ParseLoadIgnoreText(const WCHAR* pBegin, const WCHAR* pEnd, IgnoreTextType& item)
{
	// str - [t] [->] [<-]
	for(size_t i=NN_ARRAY_LENGTH(s_aszDirDiv)-1; i != 0 ; --i)
	{
		const WCHAR* pFind = std::search(pBegin,
										 pEnd,
										 s_aszDirDiv[i],
										 s_aszDirDiv[i] + wcslen(s_aszDirDiv[i]));

		if(pFind)
		{
			item.get<IgnoreTextPos::String>().assign(pBegin, pFind);
			item.get<IgnoreTextPos::Translation>() = (Translate::Translation)i;

			return true;
		}
	}

	return false;
}

void Settings::SaveVersion()
{
	if(!s_regProg)
		return;

	s_regProg.SetStringValue(s_szVersionName,s_szVersion);
}

void Settings::SaveStorage()
{
	if(!s_regProg)
		return;

	// Deleting Old
	s_regProg.DeleteSubKey(s_szStorageName);
	for(size_t i=0; i<2; ++i)
		::DeleteFile(g_OldStorage.m_astrLang[i].c_str());
	
	for(size_t i=0; i<Language::nProfiles; ++i)
	{
		LangStringT strProfile = g_OldStorage.m_astrProfile[i];
		strProfile+= s_szIni;

		::DeleteFile(strProfile.c_str());

		s_regProg.RecurseDeleteKey(g_OldStorage.m_astrProfile[i].c_str());
	}

	// Creating New
	ATL::CRegKey regStorage(OpenKeySave(s_regProg,s_szStorageName));
	if(!regStorage)
		return;

	// Saving
	for(size_t i=0; i<Storage::nStg; ++i)
		regStorage.SetDWORDValue(s_aszStorageStg[i],g_Storage.m_stg[i]);

	for(size_t i=0; i<2; ++i)
		regStorage.SetStringValue(s_aszLang[i],g_Storage.m_astrLang[i].c_str());

	for(size_t i=0; i<Language::nProfiles; ++i)
		regStorage.SetStringValue(s_aszProfiles[i],g_Storage.m_astrProfile[i].c_str());
}

void Settings::SaveOptions()
{
	if(s_regProg)
		s_regProg.SetBinaryValue(s_szOptions,&g_Options,sizeof(g_Options));
	
	ATL::CRegKey regRun(OpenKeySave(s_hkProgKey,s_szRunPath));
	if(regRun)
	{
		if(g_Options.m_nLoadOnStartUp == Options::loadNo)
			regRun.DeleteValue(s_szTransliterator);
		else
		{
			try
			{
				LangStringT strPath = __targv[0];
				if(g_Options.m_nLoadOnStartUp == Options::loadHidden)
					strPath+= _T(" -hide");
				regRun.SetStringValue(s_szTransliterator,strPath.c_str());
			}
			catch(...)
			{
			}
		}
	}
}

void Settings::SaveLanguage()
{
	void (*pFuncSave)(const TCHAR*,const LangProfile*) = 
		g_Storage.m_stg[Storage::stgProfiles] == Storage::stgRegistry ?
		SaveProfileReg:
		SaveProfileFile;

	for(unsigned i = 0;i<Language::nProfiles; ++i)
		(*pFuncSave)(g_Storage.m_astrProfile[i].c_str(),g_Language.GetProfile(i));
}

void Settings::SaveText()
{
	if(s_regProg)
	{
		for(size_t i=0; i<2; ++i)
			if(g_Storage.m_stg[Storage::stgText] == Storage::stgRegistry)
				s_regProg.SetBinaryValue(g_Storage.m_astrLang[i].c_str(),&g_Text[i][0],
					g_Text[i].size()*sizeof(wchar_t));
			else
				s_regProg.DeleteValue(g_Storage.m_astrLang[i].c_str());
	}

	for(size_t i=0; i<2; ++i)
	{
		if(g_Storage.m_stg[Storage::stgText] == Storage::stgRegistry)
			::DeleteFile(g_Storage.m_astrLang[i].c_str());
		else
		{
			if(g_Options.m_bSaveText)
			{
				ATL::CAtlFile file(OpenFileSave(g_Storage.m_astrLang[i].c_str()));
				if(file == INVALID_HANDLE_VALUE)
					continue;

				file.Write(&s_cUnicodeHeader,sizeof(s_cUnicodeHeader));
				file.Write(&g_Text[i][0],g_Text[i].size()*sizeof(wchar_t));
			}
		}
	}
}

void Settings::SaveLangID()
{
	if(!s_regProg)
		return;
	s_regProg.SetBinaryValue(s_szLangIDName,&g_LangID,sizeof(g_LangID));
}

void Settings::SaveProfileFile(const TCHAR* szProfileName,const LangProfile* pProfile)
{
	LangStringT strFileName(szProfileName);
	strFileName+= s_szIni;
	ATL::CAtlFile fileProfile(OpenFileSave(strFileName.c_str()));
	if(!fileProfile)
		return;

	LangString str;
	PrepareSaveProfileFile(pProfile, str);
	fileProfile.Write(&s_cUnicodeHeader, sizeof(s_cUnicodeHeader));
	fileProfile.Write(str.c_str(), str.length()*sizeof(LangChar));
}

void Settings::PrepareSaveProfileFile(const LangProfile* pProfile,LangString& str)
{
	// Lang
	str.reserve(
		pProfile->m_aTranslation.size()*
			(Language::MaxLengthTranslate(pProfile,true)+
			Language::MaxLengthTranslate(pProfile,true))+
		LangProfile::nIgnore*
			(Language::MaxLengthIgnore(pProfile))+
		pProfile->m_aIgnoreText.size()*
			(Language::MaxLengthIgnoreText(pProfile)));

	str+= Settings::s_szLangF;
	str+= s_szNL;
    for(size_t i=0; i<2; ++i)
	{
		str+= s_aszLangF[i];
		str+= s_szEQ;
		str+= NN::CharAWT<const LangString::value_type>(pProfile->m_astrLang[i].c_str());
		str+= s_szNL;
	}

	// Translation
	str+= Settings::s_szTranslationF;
	str+= s_szNL;
	for(LangArray::const_iterator it = pProfile->m_aTranslation.begin();
		it != pProfile->m_aTranslation.end();
		++it)
	{
		LangString strTranslation;
		ParseSaveTranslation(*it, strTranslation);
		str+= strTranslation;
		str+= s_szNL;
	}
	
	// Ignore
	str+= Settings::s_szIgnoreF;
	str+= s_szNL;
	for(size_t i=0; i<LangProfile::nIgnore; ++i)
	{
		str+= s_aszIgnoreNameF[i];
		str+= s_szEQ;
		str+= pProfile->m_astrIgnore[i];
		str+= s_szNL;
	}

	// IgnoreText
	str+= Settings::s_szIgnoreTextF;
	str+= s_szNL;
	for(IgnoreTextArray::const_iterator it = pProfile->m_aIgnoreText.begin();
		it != pProfile->m_aIgnoreText.end();
		++it)
	{
		LangString strIgnoreText;
		ParseSaveIgnoreText(*it,strIgnoreText);
		str+= strIgnoreText;
		str+= s_szNL;
	}
}

void Settings::SaveProfileReg(const TCHAR* szProfileName,const LangProfile* pProfile)
{
	ATL::CRegKey regProfile(OpenKeySave(s_regProg,szProfileName));
	if(!regProfile)
		return;

	SaveProfileTranslation(regProfile,pProfile);
	SaveProfileIgnore(regProfile,pProfile);
	SaveProfileIgnoreText(regProfile,pProfile);
	SaveProfileLangName(regProfile,pProfile);
}

void Settings::SaveProfileTranslation(HKEY hkProfile, const LangProfile* pProfile)
{
	ATL::CRegKey regTranslation(OpenKeySave(hkProfile,s_szTranslationName));
	if(!regTranslation)
		return;

	TCHAR szName[NN::digits_number<int>::value+1];

	int iTranslation = 0;
	for(LangArray::const_iterator it = pProfile->m_aTranslation.begin();
		it != pProfile->m_aTranslation.end();
		++it, ++iTranslation)
	{
		_itot(iTranslation,szName,10);

		LangString strTranslation;

		ParseSaveTranslation(*it,strTranslation);

		regTranslation.SetBinaryValue(
			szName,
			strTranslation.c_str(),
			strTranslation.length()*sizeof(LangChar));
	}
}

void Settings::SaveProfileIgnore(HKEY hkProfile, const LangProfile* pProfile)
{
	ATL::CRegKey regIgnore(OpenKeySave(hkProfile,s_szIgnoreName));
	if(!regIgnore)
		return;

	for(size_t i=0; i<LangProfile::nIgnore; ++i)
		regIgnore.SetBinaryValue(
			s_aszIgnoreName[i],
			pProfile->m_astrIgnore[i].c_str(),
			(pProfile->m_astrIgnore[i].length()+1)*sizeof(wchar_t));
}

void Settings::SaveProfileIgnoreText(HKEY hkProfile, const LangProfile* pProfile)
{
	ATL::CRegKey regIgnoreText(OpenKeySave(hkProfile,s_szIgnoreTextName));
	if(!regIgnoreText)
			return;

	TCHAR szName[NN::digits_number<int>::value+1];

	int iIgnoreText = 0;
	for(IgnoreTextArray::const_iterator it = pProfile->m_aIgnoreText.begin();
		it != pProfile->m_aIgnoreText.end();
		it++,iIgnoreText++)
	{
		_itot(iIgnoreText,szName,10);

		LangString strIgnoreText;

		ParseSaveIgnoreText(*it,strIgnoreText);

		regIgnoreText.SetBinaryValue(
			szName,
			strIgnoreText.c_str(),
			strIgnoreText.length()*sizeof(LangChar));
	}
}

void Settings::SaveProfileLangName(HKEY hkProfile, const LangProfile* pProfile)
{
	ATL::CRegKey regLang(OpenKeySave(hkProfile,s_szLangName));

	for(size_t i=0; i<2; ++i)
		regLang.SetStringValue(s_aszLang[i],pProfile->m_astrLang[i].c_str());
}

void Settings::ParseSaveTranslation(const LangType& item, LangString &str)
{
	str+= item.get<LangPos::Top>();
	str+= s_aszDirDiv[item.get<LangPos::Translation>()];
	str+= item.get<LangPos::Bottom>();
}

void Settings::ParseSaveIgnoreText(const IgnoreTextType& item, IgnoreTextString& str)
{
	str+= item.get<IgnoreTextPos::String>();
	str+= s_aszDirDiv[item.get<IgnoreTextPos::Translation>()];
}

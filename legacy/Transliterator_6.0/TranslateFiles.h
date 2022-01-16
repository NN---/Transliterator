#ifndef __TRANSLATEFILES_H__
#define __TRANSLATEFILES_H__

#pragma once

struct TranslateFiles
{
	// Members

	// Path
	enum
	{
		nPath = _MAX_PATH
	};
	TCHAR m_szPath[nPath+1];

	// Profile
	size_t m_nProfile;

	// UseIgnore
	BOOL m_bUseIgnore;

	// Folder
	BOOL m_bSelFolder;
	BOOL m_bAllFiles;
	BOOL m_bAllFolders;
	BOOL m_bAllSubFolders;

	// File
	BOOL m_bName;
	BOOL m_bEntry;
	BOOL m_bMP3TagV1;
	BOOL m_bMP3TagV2;

	// Direction
	int m_nDirection;

	// Extra
	enum
	{	
		nPrefix = 30,
		nSuffix = 30
	};
	
	TCHAR m_szPrefix[nPrefix+1];
	TCHAR m_szSuffix[nSuffix+1];

	// Functions
	bool Translate();
	void TranslateName(const TCHAR* szPath);
	void TranslateEntryMP3Tag(const TCHAR* szPath);
	void TranslateFile(const TCHAR* szPath);
	void TranslateTag(const char* szTagIn, char* szTagOut);
	void TranslateFolder(const TCHAR*);
	
	void TranslateSelFolder();
	void TranslatePathName(const TCHAR* szPath);
};

#endif // __TRANSLATEFILES_H__
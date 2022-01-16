#include "stdafx.h"

#include "language.h"
#include "global.h"

#include "translatefiles.h"

bool TranslateFiles::Translate()
{
	if(!m_szPath[0])
		return false;

	if(!(GetFileAttributes(m_szPath)&FILE_ATTRIBUTE_DIRECTORY))
	{
		if(!m_bName&&!m_bEntry&&!m_bMP3TagV1&&!m_bMP3TagV2)
			return true;

		TCHAR* pszPath = m_szPath+_tcslen(m_szPath);
		while(*--pszPath != _T('\\'));
		const TCHAR c = *pszPath;
		*pszPath = 0;

		NN::CurrentDirectory curdir(m_szPath);
		TranslateFile(pszPath+1);

		*pszPath = c;

		return true;
	}

	bool bRet = false;
	if(m_bAllFiles&&
		(!m_bName&&!m_bEntry&&!m_bMP3TagV1&&!m_bMP3TagV2))
		m_bAllFiles = FALSE;

	if(!m_bAllFiles&&!m_bAllFolders&&!m_bAllSubFolders&&
		!m_bSelFolder)
		return bRet;

	bRet = true;
	TranslateFolder(m_szPath);

	if(m_bSelFolder)
		TranslateSelFolder();

	return bRet;
}

void TranslateFiles::TranslateName(const TCHAR* szPath)
{
	const size_t nPath = _tcslen(szPath);

	int nDotPos = nPath;
	while(szPath[nDotPos] != _T('.')&&nDotPos)
		nDotPos--;

	TCHAR szExt[MAX_PATH+1];
	TCHAR szName[MAX_PATH+1];	
	if(nDotPos)
	{	
		_tcscpy(szExt,szPath+nDotPos);
		_tcsncpy(szName,szPath,nDotPos);
		szName[nDotPos] = 0;
	}
	else
	{
		szExt[0] = 0;
		_tcscpy(szName,szPath);
	}

	const LangProfile* pProfile = g_Language.GetProfile(m_nProfile);
	const size_t nNameOut = 
		Language::CountOutTranslate(
			MAX_PATH,
			(Translate::Direction)m_nDirection,
			m_bUseIgnore,
			g_Language.GetProfile(m_nProfile));

	try
	{
		std::vector<TCHAR> aNameOut(
				nNameOut+
				_tcslen(m_szPrefix)+
				_tcslen(m_szSuffix));
		
		_tcscpy(&aNameOut[0],m_szPrefix);
		{
			NN::sg<BOOL> sg(
				g_Options.m_bIgnore,
				m_bUseIgnore,
				g_Options.m_bIgnore);

			g_Language.Translate(
				NN::CharAWT<const wchar_t>(szName,0,CP_ACP),
				NN::CharAWT<wchar_t>(&aNameOut[_tcslen(m_szPrefix)],nNameOut,CP_ACP),
				(Translate::Direction)m_nDirection,
				pProfile);
		}
		TCHAR* pNameOut = _tcscat(&aNameOut[0],m_szSuffix);

		_tcscat(pNameOut,szExt);

		std::vector<TCHAR> aNameOutPS;
		
		::MoveFile(szPath,&aNameOut[0]);
	}
	catch(...)
	{
	}
}

void TranslateFiles::TranslateEntryMP3Tag(const TCHAR* szPath)
{
	ATL::CAtlFile file;
	if(file.Create(szPath,GENERIC_READ|GENERIC_WRITE,NULL,OPEN_EXISTING) != S_OK)
		return;

	const LangProfile* pProfile = g_Language.GetProfile(m_nProfile);
	size_t lFileSize = (size_t)::GetFileSize(file,NULL);
	const size_t maxTI  = 
		std::max(
			Language::MaxLengthTranslate(pProfile,!m_nDirection),
			(m_bUseIgnore?Language::MaxLengthIgnore(pProfile):1)
		);
	size_t lFileSizeTranslate = Language::CountOutTranslate(lFileSize,
		(Translate::Direction)m_nDirection,m_bUseIgnore,pProfile);

	ATL::CAtlFileMapping<CHAR> filemap;
	if(filemap.MapFile(file,lFileSize+1,0,PAGE_READWRITE,FILE_MAP_WRITE) != S_OK)
		return;

	if(m_bEntry&&(m_bMP3TagV1||m_bMP3TagV2)&&
		_tcsicmp(szPath+_tcslen(szPath)-4,_T(".mp3")))
		m_bEntry = FALSE;

	if(m_bEntry)
	{
		const bool bUnicode = 
			(unsigned char)static_cast<const char*>(filemap)[0] == 0xFF &&
			(unsigned char)static_cast<const char*>(filemap)[1] == 0xFE;

		filemap[lFileSize] = 0;
		if(bUnicode)
			filemap[lFileSize+1] = 0;

		try
		{
			std::vector<wchar_t> aOutW(lFileSizeTranslate+1);

			{
				NN::sg<BOOL> sg(
					g_Options.m_bIgnore,
					m_bUseIgnore,
					g_Options.m_bIgnore);

				g_Language.Translate(
					bUnicode?
						reinterpret_cast<const wchar_t*>(
							static_cast<const char*>(filemap)+2):
						NN::CharAWT<const wchar_t>(
							static_cast<const char*>(filemap)),
					&aOutW[0],
					(Translate::Direction)m_nDirection,
					pProfile);
			}

			size_t len = wcslen(&aOutW[0]);
			if(!bUnicode)
			{
				::WideCharToMultiByte(CP_ACP,0,&aOutW[0],len,filemap,len,0,0);
				lFileSize = len;
			}
			else
			{
				memcpy(static_cast<char*>(filemap)+2,&aOutW[0],len*sizeof(wchar_t));
				lFileSize = (len+2)*sizeof(wchar_t);
			}
		}
		catch(...)
		{
			return;
		}
	}
	else
	{
		char* pCur;
	
		// Mp3 Tag V1
		if(m_bMP3TagV1)
		{
			pCur = filemap+lFileSize-(sizeof(NN::ID3Tag));
			NN::ID3Tag mp3tagIn;
			NN::ID3Tag mp3tagOut;
			memcpy(&mp3tagIn,pCur,sizeof(NN::ID3Tag));
			mp3tagOut = mp3tagIn;

			static const char szTag[3] = {'T','A','G'};
			
			static size_t nOut = NN::ID3Tag::nCount*maxTI+1;
			
			if(!LangStringTraitsA::compare(mp3tagIn.szTag,
										   szTag,
										   NN_ARRAY_LENGTH(szTag)))
			{
				TranslateTag(mp3tagIn.szAlbom,mp3tagOut.szAlbom);
				TranslateTag(mp3tagIn.szArtist,mp3tagOut.szArtist);
				TranslateTag(mp3tagIn.szTitle,mp3tagOut.szTitle);
				TranslateTag(mp3tagIn.szComment,mp3tagOut.szComment);
				
				memcpy(pCur,&mp3tagOut,sizeof(NN::ID3Tag));
			}
		}
	}

	filemap.Unmap();
	file.SetSize(lFileSize);
}

void TranslateFiles::TranslateTag(const char* szTagIn, char* szTagOut)
{
	g_Language.Translate(
					NN::CharAWT<const wchar_t>(szTagIn),
					NN::CharAWT<wchar_t>(szTagOut,NN::ID3Tag::nCount),
					(Translate::Direction)m_nDirection,
					g_Language.GetProfile(m_nProfile));
}

void TranslateFiles::TranslateFile(const TCHAR* szPath)
{
	if(m_bEntry||
		m_bMP3TagV1||
		m_bMP3TagV2)
		TranslateEntryMP3Tag(szPath);

	if(m_bName)
		TranslateName(szPath);
}

void TranslateFiles::TranslateFolder(const TCHAR* szPath)
{
	NN::CurrentDirectory curdir(szPath);
	
	WTL::CFindFile ff;

	if(!ff.FindFile())
		return;
	
	do{
		if(!_tcscmp(ff.m_fd.cFileName,_T("."))||
			!_tcscmp(ff.m_fd.cFileName,_T("..")))
			continue;
				
		if(ff.IsDirectory())
		{
			if(m_bAllSubFolders&&
				_tcslen(szPath)+
				_tcslen(_T("\\"))+
				_tcslen(ff.m_fd.cFileName) <= MAX_PATH)
			{
				TCHAR szNextPath[MAX_PATH];
				TCHAR* pszNextPath = _tcscpy(szNextPath,szPath);
				_tcscat(pszNextPath,_T("\\"));
				_tcscat(pszNextPath,ff.m_fd.cFileName);
				TranslateFolder(szNextPath);
			}
			if(m_bAllFolders)
				TranslateName(ff.m_fd.cFileName);
		}
		else
		{
			TranslateFile(ff.m_fd.cFileName);
		}
	}while(ff.FindNextFile());

	ff.Close();
}

void TranslateFiles::TranslateSelFolder()
{
	TranslatePathName(m_szPath);
}

void TranslateFiles::TranslatePathName(const TCHAR* szPath)
{
	NN::CurrentDirectory curdir(szPath);
	
	const size_t nPath = _tcslen(szPath);
	try
	{
		std::vector<TCHAR> aszPath(szPath,&szPath[nPath+1]);
		
		TCHAR* pszPath = &aszPath[nPath];
		while(*pszPath != _T('\\')&&*pszPath != _T('/'))
			pszPath--;

		const TCHAR c =  *++pszPath;
		*pszPath = 0;
		::SetCurrentDirectory(&aszPath[0]);
		*pszPath = c;

		TranslateName(pszPath);
	}
	catch(...)
	{
	}
}
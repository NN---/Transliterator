#include "stdafx.h"
#include "resource.h"

#include "translatefilesdlg.h"

void CTranslateFilesDlg::UpdateCmbProfile()
{
	InitCmbLanguage(GetDlgItem(IDC_PROFILE));
}

void CTranslateFilesDlg::TranslateFile(LPCSTR szPath,Translate::Direction dir)
{
	char szFileExt[_MAX_PATH*LangString::nCountInit];
	char szFileName[_MAX_PATH*LangString::nCountInit];	

	const int nFileName=lstrlen(szPath);

	int i=nFileName;
	while(i&&szPath[i]!='.') i--;

	if(i)
	{	
		memcpy(szFileExt,szPath+i,(nFileName-i)*sizeof(char));
		szFileExt[nFileName-i]=0;
		memcpy(szFileName,szPath,i*sizeof(char));
		szFileName[i]=0;
	}
	else
	{
		szFileExt[0]=0;
		lstrcpy(szFileName,szPath);
	}

	g_Language.Translate(szFileName,dir,sizeof(szFileName)/sizeof(szFileName[0]),m_pProfile);
	
	lstrcat(szFileName,szFileExt);

	::MoveFile(szPath,szFileName);
}

void CTranslateFilesDlg::TranslateEntryMP3Tags(LPCSTR szFile,Translate::Direction dir,bool bEntry)
{
	CAtlFile file;
	if(file.Create(szFile,GENERIC_READ|GENERIC_WRITE,NULL,OPEN_EXISTING)!=S_OK)
		return;

	long lFileSize=::GetFileSize(file,NULL);
	if(bEntry)
		lFileSize*=LangString::nCountInit;
	CAtlFileMapping<CHAR> filemap;
	if(filemap.MapFile(file,lFileSize,0,PAGE_READWRITE,FILE_MAP_WRITE)!=S_OK)
		return;

	LPSTR pFileView=(LPSTR)filemap.GetData();

	if(bEntry)
	{
		g_Language.Translate(pFileView,dir,lFileSize,m_pProfile);
		lFileSize=lstrlen(pFileView);
	}
	else
	{
		LPSTR pCur;
	
		// Mp3 Tag V1
		pCur=pFileView+lFileSize-(sizeof(NN::MP3Tag));
		NN::MP3Tag mp3tag;
		memcpy(&mp3tag,pCur,sizeof(NN::MP3Tag));

		if(!LangStringTraits::CompareArrayLength(mp3tag.szTag,"TAG",3))
		{
			TranslateTag(mp3tag.szAlbom,dir);
			TranslateTag(mp3tag.szArtist,dir);
			TranslateTag(mp3tag.szTitle,dir);
			TranslateTag(mp3tag.szComment,dir);
			memcpy(pCur,&mp3tag,sizeof(NN::MP3Tag));
		}
	}

	filemap.Unmap();
	file.SetSize(lFileSize);
}

void CTranslateFilesDlg::Translate(LPCSTR szPath)
{
	NN::CurrentDirectory curdir(szPath);
	
	HANDLE hFindFile;
	WIN32_FIND_DATA ffd;
	
	hFindFile = ::FindFirstFile("*.*",&ffd);
	if(hFindFile==INVALID_HANDLE_VALUE)
		return;
	
	do{
		if(!LangStringTraits::CompareArrayLength(ffd.cFileName,".",1)||
			!LangStringTraits::CompareArrayLength(ffd.cFileName,"..",2))
			continue;

		if(ffd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
		{
			if(m_bSubFolders)
			{
				char szNextPath[_MAX_PATH];
				lstrcpy(szNextPath,szPath);
				lstrcat(szNextPath,"\\");
				lstrcat(szNextPath,ffd.cFileName);
				Translate(szNextPath);
			}
			if(m_bFolders)
				TranslateFile(ffd.cFileName,m_nDirection);
		}
		else
		{
			bool bNotMP3=LangStringTraits::CompareArray(ffd.cFileName+lstrlen(ffd.cFileName)-4,".mp3",4);
			if(bNotMP3&&m_bEntry||
				!bNotMP3&&m_bMP3Tags)
				TranslateEntryMP3Tags(ffd.cFileName,m_nDirection,bNotMP3);
			if(m_bName)
				TranslateFile(ffd.cFileName,m_nDirection);
		}
	}while(::FindNextFile(hFindFile,&ffd));

	::FindClose(hFindFile);
}

void CTranslateFilesDlg::TranslateThisFolder()
{
	NN::CurrentDirectory curdir(m_szPath);
	char *pszPath=m_szPath+lstrlen(m_szPath);
	pszPath--;
	while(*pszPath!='\\'&&*pszPath!='/')
		pszPath--;
	pszPath++;
	char c=*pszPath;
	*pszPath=0;
	::SetCurrentDirectory(m_szPath);
	*pszPath=c;
		
	TranslateFile(pszPath,m_nDirection);
}

void CTranslateFilesDlg::TranslateTag(LPSTR szTag,Translate::Direction dir)
{
	g_Language.Translate(szTag,dir,NN::MP3Tag::nCount,m_pProfile);
}

void CTranslateFilesDlg::UpdateLanguage()
{
	NN::DialogLang<CTranslateFilesDlg>::UpdateLanguage();
	UpdateCmbProfile();
}

void CTranslateFilesDlg::EnableDirs(BOOL bEnable)
{
	::EnableWindow(GetDlgItem(IDC_FILES),bEnable);
	::EnableWindow(GetDlgItem(IDC_FOLDERS),bEnable);
	::EnableWindow(GetDlgItem(IDC_SUBFOLDERS),bEnable);
	::EnableWindow(GetDlgItem(IDC_SELFOLDER),bEnable);
}

void CTranslateFilesDlg::EnableFiles(BOOL bEnable)
{
	::EnableWindow(GetDlgItem(IDC_NAME),bEnable);
	::EnableWindow(GetDlgItem(IDC_ENTRY),bEnable);
	::EnableWindow(GetDlgItem(IDC_MP3TAGS),bEnable);
}

LRESULT CTranslateFilesDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	DialogLang_Init();
	SendDlgItemMessage(IDC_PATH,EM_LIMITTEXT,(WPARAM)(_MAX_PATH-1));
	m_szPath[0]=0;
	DoDataExchange(DDX_LOAD);
	InitCmbLanguage(GetDlgItem(IDC_PROFILE));
	m_pProfile=g_Language.GetProfile((Language::Profiles)0);

	return 0;
}

LRESULT CTranslateFilesDlg::OnTranslate(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	DoDataExchange(DDX_SAVE);

	NN_AUTOSG_F4(sg_tMB,AtlMessageBox,0,IDS_DONE,IDR_TRANSLITERATOR,MB_OK|MB_ICONINFORMATION)sg;

	if(!m_szPath[0])
		return 0;

	if(m_bFiles&&
		(!m_bName&&!m_bEntry&&!m_bMP3Tags))
		m_bFiles=FALSE;

	if(m_bFiles&&!(GetFileAttributes(m_szPath)&FILE_ATTRIBUTE_DIRECTORY))
	{
		char* pszPath;
		pszPath=m_szPath+lstrlen(m_szPath);
		while(*pszPath!='\\')
			pszPath--;
		*pszPath=0;
		NN::CurrentDirectory curdir(m_szPath);
		if(m_bMP3Tags||m_bEntry)
			TranslateEntryMP3Tags(pszPath+1,m_nDirection,m_bEntry);
		if(m_bName)
			TranslateFile(pszPath+1,m_nDirection);
		return 0;
	}

	if(!m_bFiles&&!m_bFolders&&!m_bSubFolders&&
		!m_bThisFolder)
		return 0;

	char *pszPath=m_szPath+lstrlen(m_szPath)-1;
	if(*pszPath=='\\')
		*pszPath=0;

	Translate(m_szPath);

	if(m_bThisFolder)
		TranslateThisFolder();

	return 0;
}

LRESULT CTranslateFilesDlg::OnBrowse(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CFolderDialog fd(m_hWnd,0,BIF_BROWSEINCLUDEFILES|BIF_VALIDATE);

	if(fd.DoModal()==IDOK)
		SetDlgItemText(IDC_PATH,fd.m_szFolderPath);
	return 0;
}

LRESULT CTranslateFilesDlg::OnFiles(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	EnableFiles(IsDlgButtonChecked(IDC_FILES));

	return 0;
}

LRESULT CTranslateFilesDlg::OnSelChangeProfile(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	m_pProfile=g_Language.GetProfile((Language::Profiles)SendDlgItemMessage(IDC_PROFILE,CB_GETCURSEL));
	return 0;
}

LRESULT CTranslateFilesDlg::OnEnChangePath(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	DoDataExchange(DDX_SAVE);
	DWORD dwAttr = GetFileAttributes(m_szPath);

	if(!*m_szPath)
	{
		EnableFiles(FALSE);
		EnableDirs(FALSE);
	}
	else
	{
		if(dwAttr & FILE_ATTRIBUTE_DIRECTORY)
		{
			EnableDirs(TRUE);
			EnableFiles(IsDlgButtonChecked(IDC_FILES));
		}
		else
		{
			EnableDirs(FALSE);
			EnableFiles(TRUE);
		}
	}
	
	return 0;
}

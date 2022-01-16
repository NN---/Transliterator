#include "StdAfx.h"
#include "Resource.h"

#include "TranslateFilesDlg.h"
#include <NN/MP3.h>

void CTranslateFilesDlg::TranslateFile(LPCSTR szPath,Translate::Direction dir)
{
	TCHAR szFileExt[_MAX_PATH];
	TCHAR szFileName[_MAX_PATH];	

	const int nFileName=lstrlen(szPath);

	int i=nFileName;
	while(i&&szPath[i]!=_T('.')) i--;

	if(i)
	{	
		memcpy(szFileExt,szPath+i,(nFileName-i)*sizeof(TCHAR));
		szFileExt[nFileName-i]=0;
		memcpy(szFileName,szPath,i*sizeof(TCHAR));
		szFileName[i]=0;
	}
	else
	{
		szFileExt[0]=0;
		lstrcpy(szFileName,szPath);
	}

	_Translit.Translate(szFileName,dir,_MAX_PATH);
	
	lstrcat(szFileName,szFileExt);

	::MoveFile(szPath,szFileName);
}

void CTranslateFilesDlg::TranslateEntryMP3Tags(LPCSTR szFile,Translate::Direction dir,bool bEntry)
{
	CAtlFile file;
	if(file.Create(szFile,GENERIC_READ|GENERIC_WRITE,NULL,OPEN_EXISTING)!=S_OK)
		return;

	long lFileSizeOrig=::GetFileSize(file,NULL);
	long lFileSize=lFileSizeOrig*EngRusArray::nCountInit;
	CAtlFileMapping<CHAR> filemap;
	if(filemap.MapFile(file,lFileSize,0,PAGE_READWRITE,FILE_MAP_WRITE)!=S_OK)
		return;

	LPSTR pFileView=(LPSTR)filemap.GetData();

	if(bEntry)
	{
		_Translit.Translate(pFileView,dir,lFileSize);
		lFileSize=lstrlen(pFileView);
		filemap.Unmap();
		file.SetSize(lFileSize);
	}
	else
	{
		LPSTR pCur;
	
		// Mp3 Tag V1
		pCur=pFileView+lFileSizeOrig-(sizeof(NN::MP3Tag));
		NN::MP3Tag mp3tag;
		memcpy(&mp3tag,pCur,sizeof(NN::MP3Tag));

		if(!EngRusArray::Traits::CompareArrayLength(mp3tag.szTag,"TAG",3))
		{
			TranslateTag(mp3tag.szAlbom,dir);
			TranslateTag(mp3tag.szTitle,dir);
			TranslateTag(mp3tag.szComment,dir);
			memcpy(pCur,&mp3tag,sizeof(NN::MP3Tag));
		}

		filemap.Unmap();
		file.SetSize(lFileSizeOrig);
	}
}

void CTranslateFilesDlg::Translate(LPCSTR szPath)
{
	NN::CurrentDirectory curdir(szPath);
	
	HANDLE hFindFile;
	WIN32_FIND_DATA ffd;
	
	hFindFile = ::FindFirstFile(_T("*.*"),&ffd);
	if(hFindFile==INVALID_HANDLE_VALUE)
		return;
	
	do{
		if(!EngRusArray::Traits::CompareArrayLength(ffd.cFileName,_T("."),1)||
			!EngRusArray::Traits::CompareArrayLength(ffd.cFileName,_T(".."),2))
			continue;

		if(ffd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
		{
			if(m_bSubDirectories)
			{
				TCHAR szNextPath[_MAX_PATH];
				lstrcpy(szNextPath,szPath);
				lstrcat(szNextPath,_T("\\"));
				lstrcat(szNextPath,ffd.cFileName);
				Translate(szNextPath);
			}
			if(m_bDirectories)
				TranslateFile(ffd.cFileName,m_nDirection);
		}
		else
		{
			bool bNotMP3=EngRusArray::Traits::CompareArray(ffd.cFileName+lstrlen(ffd.cFileName)-4,_T(".mp3"),4);
			if(bNotMP3&&m_bEntry||
				!bNotMP3&&m_bMP3Tags)
				TranslateEntryMP3Tags(ffd.cFileName,m_nDirection,bNotMP3);
			if(m_bName)
				TranslateFile(ffd.cFileName,m_nDirection);
		}
	}while(::FindNextFile(hFindFile,&ffd));

	::FindClose(hFindFile);
}

void CTranslateFilesDlg::TranslateThisDirectory()
{
	NN::CurrentDirectory curdir(m_szPath);
	TCHAR *pszPath=m_szPath+lstrlen(m_szPath);
	pszPath--;
	while(*pszPath!=_T('\\')&&*pszPath!=_T('/'))
		pszPath--;
	pszPath++;
	TCHAR c=*pszPath;
	*pszPath=0;
	::SetCurrentDirectory(m_szPath);
	*pszPath=c;
		
	TranslateFile(pszPath,m_nDirection);
}

void CTranslateFilesDlg::TranslateTag(LPSTR szTag,Translate::Direction dir)
{
	NN::AutoArray<CHAR> aTranslate(NN::MP3Tag::nCount*EngRusArray::nCountInit);
	_Translit.Translate(szTag,aTranslate.GetData(),dir,NN::MP3Tag::nCount);
	memcpy(szTag,aTranslate.GetData(),NN::MP3Tag::nCount);
}

LRESULT CTranslateFilesDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	DialogLang_Init();
	SendDlgItemMessage(IDC_PATH,EM_LIMITTEXT,(WPARAM)(_MAX_PATH-1));
	m_szPath[0]=0;
	DoDataExchange(DDX_LOAD);
	return 0;
}

LRESULT CTranslateFilesDlg::OnCloseCmd(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	EndDialog(0);
	return 0;
}

LRESULT CTranslateFilesDlg::OnTranslate(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	DoDataExchange(DDX_SAVE);

	if(!m_szPath[0])
		return 0;

	if(m_bFiles&&
		(!m_bName&&!m_bEntry&&!m_bMP3Tags))
		m_bFiles=FALSE;

	if(!m_bFiles&&!m_bDirectories&&!m_bSubDirectories&&
		!m_bThisDirectory)
		return 0;

	TCHAR *pszPath=m_szPath+lstrlen(m_szPath)-1;
	if(*pszPath==_T('\\'))
		*pszPath=0;

	Translate(m_szPath);

	if(m_bThisDirectory)
		TranslateThisDirectory();

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
	::EnableWindow(GetDlgItem(IDC_NAME),IsDlgButtonChecked(IDC_FILES));
	::EnableWindow(GetDlgItem(IDC_ENTRY),IsDlgButtonChecked(IDC_FILES));
	::EnableWindow(GetDlgItem(IDC_MP3TAGS),IsDlgButtonChecked(IDC_FILES));
	return 0;
}
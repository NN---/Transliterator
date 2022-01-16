#ifndef __OPTIONSDLG_H__
#define __OPTIONSDLG_H__

#include "generalpage.h"
#include "hotkeyspage.h"
#include "profilepage.h"
#include "ignorepage.h"

class COptionsDlg : public NN::OptionsDialogImpl<COptionsDlg,OptionsStruct>,
				public NN::DialogLang<COptionsDlg>,
				public NN::MessageFilterDlg<COptionsDlg>,
				public NN::ToolWindow<COptionsDlg>
{
public:
	enum { IDD=IDD_OPTIONS };

	NN::AutoValue<int> m_nCurPage;
	CListBox m_ctrlOptions;

	CGeneralPage m_pageGeneral;
	CHotKeysPage m_pageHotKeys;
	CProfilePage m_pageProfile;
	CIgnorePage m_pageIgnore;

	void UpdateLanguage()
	{
		NN::DialogLang<COptionsDlg>::UpdateLanguage();
	
		m_pageGeneral.UpdateLanguage();
		m_pageHotKeys.UpdateLanguage();
		m_pageProfile.UpdateLanguage();
		m_pageIgnore.UpdateLanguage();
	
		InitListOptions();
	}

	void InitListOptions()
	{
		for(int i=0;i<GetPageCount();i++)
		{
			char strOptions[40];
			AtlLoadString(IDS_GENERAL+i,strOptions,sizeof(strOptions)/sizeof(char)-1);
			m_ctrlOptions.AddString(strOptions);
		}
	}

	template<typename T>
	void UpdateChange(T& t,const T& tc,BOOL& bChange)
	{
		if(t!=tc)
		{
			t=tc;
			bChange=TRUE;
		}
	}

	void Apply()
	{
		DoDataExchange(DDX_SAVE);

		BOOL bChangeTranslation=FALSE;
		BOOL bChangeOptions=FALSE;
		
		UpdateChange(g_Language,GetOptions()->m_Language,bChangeTranslation);
		UpdateChange(g_Ignore,GetOptions()->m_Ignore,bChangeTranslation);
		UpdateChange(g_Options,GetOptions()->m_Options,bChangeOptions);
		
		::SendMessage(GetParent(),WM_APPLY,(WPARAM)bChangeTranslation,(LPARAM)bChangeOptions);
	}

	void InitOptionsPage()
	{
		GetOptions()->Set(g_Language,g_Options,g_Ignore);
		SetOptionsPage();
		DoDataExchange(DDX_LOAD);
	}

	BEGIN_MSG_MAP(COptionsDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_SHOWWINDOW, OnShowWindow)

		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDC_CLOSE, NN::ToolWindow<COptionsDlg>::OnCloseCmd)
		COMMAND_ID_HANDLER(IDC_APPLY, OnApply)
		COMMAND_ID_HANDLER(IDC_RESET, OnReset)

		COMMAND_HANDLER(IDC_LISTOPTIONS, LBN_SELCHANGE, OnSelChangeListOptions)
		CHAIN_MSG_MAP(NN::ToolWindow<COptionsDlg>)
	END_MSG_MAP()


	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		DialogLang_Init();
		m_ctrlOptions=GetDlgItem(IDC_LISTOPTIONS);

		// Create
		m_pageGeneral.Create(m_hWnd);
		m_pageHotKeys.Create(m_hWnd);
		m_pageProfile.Create(m_hWnd);
		m_pageIgnore.Create(m_hWnd);

		AddPage(&m_pageGeneral);
		AddPage(&m_pageHotKeys);
		AddPage(&m_pageProfile);
		AddPage(&m_pageIgnore);

		// Prepare Move Window
		RECT rect;
		::GetWindowRect(GetDlgItem(IDC_SDLGPLACE),&rect);
		ScreenToClient(&rect);
		// Move Window
		for(int i=0;i<GetPageCount();i++)
			GetPage(i)->MoveWindow(&rect);
		
		InitListOptions();
		InitOptionsPage();
		
		SetCurrentPage(0);

		return 0;
	}

	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		DestroyOptions();
		return 0;
	}

	LRESULT OnShowWindow(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		if(!wParam)
			InitOptionsPage();

		return 0;
	}

	LRESULT OnOK(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		Apply();
		CloseDialog();
		return 0;
	}

	LRESULT OnApply(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		Apply();
		return 0;
	}

	LRESULT OnReset(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		GetOptions()->Reset();
		DoDataExchange(DDX_LOAD);
		return 0;
	}

	LRESULT OnSelChangeListOptions(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		SetCurrentPage(m_ctrlOptions.GetCurSel());
		return 0;
	}
};

#endif // __OPTIONSDLG_H__
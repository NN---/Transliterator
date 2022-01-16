#ifndef __CHANGETRANSLATIONDLG_H__
#define __CHANGETRANSLATIONDLG_H__

class CChangeTranslationDlg : public CDialogImpl<CChangeTranslationDlg>,
					public CWinDataExchange<CChangeTranslationDlg>,
					public DialogLang<CChangeTranslationDlg>
{
public:
	enum { IDD=IDD_CHANGETRANSLATION } ;

	CComboBox m_cmbEngRus[2];
	Translit m_Translit;

	enum EngRus { Eng,Rus };
	enum Use { useNone, useEng, useRus };
	AutoValue<Use,useNone> m_nUse;

	void SetCmbEngRus(bool b1,LPCTSTR szText=NULL);
	void InitCmbEngRus();
	void UpdateEngRusCheck(const EngRusTuple* pTuple=NULL);
	
	BEGIN_DDX_MAP(CChangeTranslationDlg)
		if(bSaveAndValidate)
			_Translit.SetData(m_Translit);
		else
			m_Translit.SetData(_Translit);
		DDX_TEXT(IDC_FROMENG,_Options.m_szNotTranslate[Options::FromEng])
		DDX_TEXT(IDC_TOENG,_Options.m_szNotTranslate[Options::ToEng])
		DDX_TEXT(IDC_FROMRUS,_Options.m_szNotTranslate[Options::FromRus])
		DDX_TEXT(IDC_TORUS,_Options.m_szNotTranslate[Options::ToRus])
		DDX_CHECK(IDC_COPYNOTTRANSLATE,_Options.m_bCopyNotTranslate)
	END_DDX_MAP()

	BEGIN_MSG_MAP(CChangeTranslationDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
		COMMAND_ID_HANDLER(IDC_ADD, OnAddRemove)
		COMMAND_ID_HANDLER(IDC_REMOVE, OnAddRemove)
		COMMAND_ID_HANDLER(IDC_CLEAR, OnClearReset)
		COMMAND_ID_HANDLER(IDC_RESET, OnClearReset)
		COMMAND_ID_HANDLER(IDC_ENGTORUS, OnEngRus)
		COMMAND_ID_HANDLER(IDC_RUSTOENG, OnEngRus)
		COMMAND_HANDLER(IDC_ENG, CBN_EDITCHANGE, OnChangeEngRus)
		COMMAND_HANDLER(IDC_RUS, CBN_EDITCHANGE, OnChangeEngRus)
		COMMAND_HANDLER(IDC_ENG, CBN_SELCHANGE, OnChangeEngRus)
		COMMAND_HANDLER(IDC_RUS, CBN_SELCHANGE, OnChangeEngRus)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCloseCmd(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnAddRemove(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnClearReset(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnEngRus(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnChangeEngRus(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
};

#endif // __CHANGETRANSLATIONDLG_H__
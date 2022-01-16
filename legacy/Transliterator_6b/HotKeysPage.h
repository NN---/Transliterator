#ifndef __HOTKEYSPAGE_H__
#define __HOTKEYSPAGE_H__

#include "trnsoptionspage.h"
#include "ddxhotkey.h"

class CHotKeysPage : public TrnsOptionsPage<CHotKeysPage>
{
public:
	enum { IDD=IDD_PAGEHOTKEYS };

	NN::AutoValue<int,CB_ERR> m_nCurSel;

	BEGIN_DDX_MAP(CHotKeysPage)
		DDX_RADIO(IDC_TRNSTORUS,(int&)GetOptions()->m_Options.m_nAutoTranslation)
		if(bSaveAndValidate)
			SaveHotKey();
	END_DDX_MAP()

	BEGIN_MSG_MAP(CHotKeysPage)
		CHAIN_MSG_MAP(TrnsOptionsPage<CHotKeysPage>)
		COMMAND_HANDLER(IDC_ACTION,CBN_SELCHANGE,OnCmbSelChangeAction)
	END_MSG_MAP()

	void SaveHotKey()
	{
		if(m_nCurSel!=CB_ERR)
		{
			CHotKeyCtrl hotkey=GetDlgItem(IDC_HOTKEYACTION);
			NN::HotKey& hk=GetOptions()->m_Options.m_HotKey[m_nCurSel];
			hotkey.GetHotKey(hk.vk,hk.fsModifiers);
			hk.ConvertToWnd();
		}
	}

	void LoadHotKey()
	{
		CHotKeyCtrl hotkey=GetDlgItem(IDC_HOTKEYACTION);
		m_nCurSel=SendDlgItemMessage(IDC_ACTION,CB_GETCURSEL,0,0);
		NN::HotKey& hk=GetOptions()->m_Options.m_HotKey[m_nCurSel];
		hk.ConvertToHotKey();
		hotkey.SetHotKey(hk.vk,hk.fsModifiers);
	}
	
	LRESULT OnCmbSelChangeAction(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		SaveHotKey();
		LoadHotKey();
		return 0;
	}
};

#endif // __HOTKEYSPAGE_H__
#ifndef __PROFILEPAGE_H__
#define __PROFILEPAGE_H__

#pragma once

#include "optionsstruct.h"
#include "profilestruct.h"
#include "profilechanged.h"
#include "ddx.h"
#include "msg.h"

#include "profiletranslation.h"
#include "profileignore.h"
#include "profileexportimport.h"
#include "profilecopyprofile.h"
#include "profilename.h"
#include "profilereset.h"

class ProfilePage : public NN::OptionsPageImpl<ProfilePage,OptionsStruct>,
					public NN::OptionsDialogPagesT<ProfileStruct>,
					public NN::DialogLang<ProfilePage>,
					public NN::MessageFilterDlg<ProfilePage>,
					public ProfileChanged
{
public:
	enum { IDD = IDD_PAGEPROFILE };

	typedef NN::OptionsDialogPagesT<ProfileStruct> DDXPagesClass;

	ProfileStruct m_ps;

	NN::auto_value<int> m_nCurProfile;
	WTL::CTabCtrl m_tabAction;

	ProfileTranslation		m_profileTranslation;
	ProfileIgnore			m_profileIgnore;
	ProfileExportImport	m_profileExportImport;
	ProfileCopyProfile		m_profileCopyProfile;
	ProfileName			m_profileName;
	ProfileReset			m_profileReset;

	void DialogLang_LanguageChanged();
	void ProfileChanged();
	void UpdateProfile();

	BEGIN_DDX_MAP(ProfilePage)
		UpdateProfile();
		DDXPagesClass::DoDataExchange(bSaveAndValidate);
	END_DDX_MAP()

	BEGIN_MSG_MAP(ProfilePage)
		NN_MSGFILTER_MESSAGE_ADD()
		NN_MSGFILTER_MESSAGE_REMOVE()
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_ACTIVATE, OnActivate)
		MESSAGE_HANDLER(UWM_PROFILENAME,OnProfileName)
		MESSAGE_HANDLER(UWM_PROFILECHANGE, OnProfileChange)
		MESSAGE_HANDLER(UWM_PROFILEUPDATE, OnProfileUpdate)
		MESSAGE_HANDLER(UWM_PROFILECOPYPROFILE, OnProfileCopyProfile)
		MESSAGE_HANDLER(UWM_PROFILERESET, OnProfileReset)
		
		COMMAND_HANDLER(IDC_CMBPROFILE,CBN_SELCHANGE,OnCmbSelChangeProfileName)
		NOTIFY_HANDLER(IDC_TABPROFILEACTION,TCN_SELCHANGE,OnTcnSelChangeProfileAction)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnProfileName(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnProfileChange(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnProfileUpdate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnProfileCopyProfile(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnProfileReset(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnCmbSelChangeProfileName(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnTcnSelChangeProfileAction(int code, NMHDR* pnmhdr, BOOL& bHandled);
};

#endif // __PROFILEPAGE_H__
#include "stdafx.h"

#include "resource.h"
#include "msg.h"

#include "profilereset.h"

LRESULT ProfileReset::OnReset(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	struct ID_Reset
	{
		unsigned ID;
		Reset reset;
	};
	
	static const ID_Reset aIDReset[] = 
	{
		{IDC_CHKRESETTRANSLATION, resetTranslation},
		{IDC_CHKRESETIGNORE, resetIgnore},
		{IDC_CHKRESETIGNORETEXT, resetIgnoreText},
		{IDC_CHKRESETNAME, resetName}
	};
	
	unsigned nReset = 0;

	for(size_t i=0; i<NN_ARRAY_LENGTH(aIDReset); ++i)
	if(IsDlgButtonChecked(aIDReset[i].ID))
		nReset|= aIDReset[i].reset;

	if(!nReset)
		return 0;
	
	GetParent().SendMessage(UWM_PROFILERESET, (WPARAM)nReset);

	InvalidateRect(NULL);

	return 0;
}
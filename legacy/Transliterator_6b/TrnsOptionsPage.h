#ifndef __TRNSOPTIONSPAGE_H__
#define __TRNSOPTIONSPAGE_H__

#include "optionsstruct.h"

template<typename T>
class TrnsOptionsPage : public NN::OptionsPageImpl<T,OptionsStruct>,
				public NN::DialogLang<T>
{
public:
	typedef NN::OptionsPageImpl<T,OptionsStruct> baseClass;
	
	BEGIN_MSG_MAP(TrnsOptionsPage)
		CHAIN_MSG_MAP(NN::DialogLang<T>)
	END_MSG_MAP()
};

#endif // __TRNSOPTIONSPAGE_H__
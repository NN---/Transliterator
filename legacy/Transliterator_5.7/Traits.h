#ifndef __TRAITS_H___
#define __TRAITS_H___

template<>
class NN::StaticArrayMapTraitsLastArrayItem<LangType>
{
public:
	inline static bool LastArrayItem(const LangType& Item)
	{
		return !(Item.Get<0>()[0]&&Item.Get<1>()[0]);
	}
};

#endif // __TRAITS_H___

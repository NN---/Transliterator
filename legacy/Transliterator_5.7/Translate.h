#ifndef __TRANSLATE_H__
#define __TRANSLATE_H__

struct Translate
{
public:
	enum LangTranslate
	{
		trnsNone,
		trnsTrnstoRus,
		trnsRustoTrns,
		trnsAll=trnsTrnstoRus|trnsRustoTrns,
	};

	enum Direction
	{
		dirTrnstoRus,
		dirRusToTrns,
		dirAuto,
	};
};

#endif // __TRANSLATE_H__

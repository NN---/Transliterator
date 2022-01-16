#ifndef __TRANSLATE_H__
#define __TRANSLATE_H__

struct Translate
{
public:
	enum EngRusTranslate
	{
		None=0,
		EngtoRus=1,
		RustoEng=2,
		EngRus=EngtoRus|RustoEng,
		RusEng=EngRus,
	};

	enum Direction
	{
		dirEngtoRus=0,
		dirRustoEng=1,
		dirAuto=2
	};
};

#endif // __TRANSLATE_H__
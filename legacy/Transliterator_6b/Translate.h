#ifndef __TRANSLATE_H__
#define __TRANSLATE_H__

struct Translate
{
public:
	enum Translation
	{
		trnsNone,
		trns1_2,
		trns2_1,
		trnsAll=trns1_2|trns2_1
	};

	enum Direction
	{
		dir1_2,
		dir2_1,
		dirAuto,
	};
};

#endif // __TRANSLATE_H__

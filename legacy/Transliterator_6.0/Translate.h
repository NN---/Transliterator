#ifndef __TRANSLATE_H__
#define __TRANSLATE_H__

#pragma once

struct Translate
{
public:
	enum Translation
	{
		trnsNone,
		trnsToptoBottom,
		trnsBottomtoTop,
		trnsAll = trnsToptoBottom|trnsBottomtoTop
	};

	enum Direction
	{
		dirToptoBottom,
		dirBottomtoTop,
		dirAuto,
	};
};

#endif // __TRANSLATE_H__

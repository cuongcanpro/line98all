#pragma once
#include "Game/Logic/PointGame.h"
#ifndef WayPikachu_h__
#define WayPikachu_h__

class WayPikachu
{
public:
	WayPikachu();
	~WayPikachu();

	int pointSameRow;
    int pointSameColumn;
	bool specialBrick;
	PointGame* previousPointRow;
	PointGame* previousPointColumn;
	bool sameRow;
	bool sameColumn;
	int countBreak;

	void reset();
};
#endif // WayPikachu_h__


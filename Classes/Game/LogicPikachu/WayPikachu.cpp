#include "WayPikachu.h"


WayPikachu::WayPikachu()
{
	pointSameRow = -1;
    pointSameColumn = -1;
	previousPointRow = new PointGame();
	previousPointColumn = new PointGame();
}


WayPikachu::~WayPikachu()
{
}

void WayPikachu::reset()
{
	pointSameRow = -1;
    pointSameColumn = -1;
	specialBrick = false;
	sameRow = false;
	sameColumn = false;
	countBreak = -1;
}

#include "Logic.h"
#include <math.h>
#include "../Data/GlobalData.h"
#include "cocos2d.h"
using namespace cocos2d;
Logic::Logic(void)
{
}


Logic::~Logic(void)
{
}

float Logic::getDistance( float x0, float y0, float x1, float y1, float x2, float y2 )
{
	float b = x1 - x2;
	float a =  y2 - y1;

	float numerator = fabs(x0 * a + y0 * b + y1 * x2 - y2 * x1);
	float denomirator = sqrt((x1 - x2) * (x1 - x2) + (y2 - y1) * (y2 - y1));
	return numerator / denomirator;
}

bool Logic::inDistance( float x0, float x1, float x2 , float d)
{
	float medium = (x1 + x2) / 2;
	float mediumDis = fabs(x2 - x1) / 2;
	if(fabs(medium - x0) < (d + mediumDis))
		return true;
	else return false;
}

bool Logic::detectHit( float x0, float y0, float d0, float x1, float y1, float x2, float y2, float d1 )
{
	float distance = getDistance(x0, y0, x1, y1, x2, y2);
	if(distance < d0 / 2 + d1 / 2)
	{
		if(inDistance(x0, x1, x2, d0/2))
		{
			if(inDistance(y0, y1, y2, d0/2))
				return true;
		}
		else
		{
			return false;
		}
// 		if(inDistance(x0 - d0/ 2, x1, x2))
// 		{
// 			if(inDistance(y0 - d0 / 2, y1, y2))
// 				return true;
// 			else if(inDistance(y0 + d0 / 2, y1, y2))
// 				return true;
// 			else if(inDistance(y0, y1, y2))
// 				return true;
// 			return false;
// 		}
// 		else if(inDistance(x0, x1, x2))
// 		{
// 			if(inDistance(y0 - d0 / 2, y1, y2))
// 				return true;
// 			else if(inDistance(y0 + d0 / 2, y1, y2))
// 				return true;
// 			else if(inDistance(y0, y1, y2))
// 				return true;
// 			return false;
// 		}
// 		else if(inDistance(x0 + d0/ 2, x1, x2))
// 		{
// 			if(inDistance(y0 - d0 / 2, y1, y2))
// 				return true;
// 			else if(inDistance(y0 + d0 / 2, y1, y2))
// 				return true;
// 			else if(inDistance(y0, y1, y2))
// 				return true;
// 			return false;
// 		}
// 		return false;
	}
	else
	{
		return false;
	}
}

float Logic::getDistance2Point( float x1, float y1, float x2, float y2 )
{
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

bool Logic::detectHitCircle( float x0, float y0, float d0, float x1, float y1, float d1 )
{
	float dis = getDistance2Point(x0, y0, x1, y1);
	if(dis < d1 / 2 && dis > d1 / 2 * RATE)
		return true;

	if(dis + d0 / 2 < d1 / 2 && dis + d0 / 2 > d1 / 2 * RATE )
		return true;

	if(dis - d0 / 2 < d1 / 2 && dis - d0 / 2 > d1 / 2 * RATE )
		return true;

	return false;
}

bool Logic::validCoordinate(int row, int column)
{
	return row >= 0 && row < NUM_ROW_MERGE && column >= 0 && column < NUM_COLUMN_MERGE;
}

cocos2d::ccColor3B Logic::getColorColumn(int column)
{
	if (column % 2 == 0) {
		return ccColor3B(0, 0, 0);
	}
	return ccColor3B(255, 255, 255);
}

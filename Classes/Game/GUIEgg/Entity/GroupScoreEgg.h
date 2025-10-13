#ifndef _GroupScoreEgg_h__
#define _GroupScoreEgg_h__
#include <cocos2d.h>

using namespace cocos2d;
class GroupScoreEgg : public CCNodeRGBA
{
public:

	GroupScoreEgg(void);
	~GroupScoreEgg(void);
	void createNormalScore(int numBall, int numDrop, int mul);
	void createBonusScore(int bonus);
	void createNormalBonusScore(int numBall, int numDrop, int mul, int bonus);
	static int getNormalBonusScore(int numBall, int numDrop, int mul, int bonus);
	
};
#endif

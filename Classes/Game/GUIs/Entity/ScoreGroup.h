#ifndef _ScoreGroup_h__
#define _ScoreGroup_h__
#include <cocos2d.h>

using namespace cocos2d;
class ScoreGroup : public CCNode
{
public:
	int max;
	ScoreGroup(void);
	ScoreGroup(long money, int max = 8);
	~ScoreGroup(void);
	void setMoney(double money);
};
#endif

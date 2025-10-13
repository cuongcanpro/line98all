#ifndef _LAYER_H_
#define _LAYER_H_
#include "cocos2d.h"
class GameLayer :
	public cocos2d::CCLayer
{
public:
	unsigned short	idLayer;
	GameLayer(void);
	~GameLayer(void);
	GameLayer(int);
};

#endif

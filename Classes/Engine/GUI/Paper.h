#pragma once
#include "cocos2d.h"
#include <vector>

USING_NS_CC;
using namespace std;
class Paper : public CCNode {
public:
	Paper(float width, float height, int directionX = 1, int directionY = 1);
	vector<CCSprite*> arrayStar;
	float width, height;
	int directionX, directionY;
	float countGen;
	float lifeTime;
	void startEffect();
	void effectStar(CCSprite* sprite);
	void updateEffect(float dt);
	CCSprite* getStar();
	void callbackEffectStar(CCNode* sender);
};


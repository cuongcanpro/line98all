#pragma once
#include "cocos2d.h"
#include <vector>

USING_NS_CC;
using namespace std;
class StarFly : public CCNode {
public:
	StarFly(float width, float height);
	vector<CCSprite*> arrayStar;
	float width, height;
	float countGen;
	float lifeTime;
	void startEffect();
	void effectStar(CCSprite* sprite);
	void updateEffect(float dt);
	CCSprite* getStar();
};


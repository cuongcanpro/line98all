#pragma once
#ifndef Number_h__
#define Number_h__
#include <cocos2d.h>
#include "Engine/GUI/GameImage.h"
#include "Engine/GUI/LabelBM.h"

#include "dragonbones/DragonBones.h"
#include "dragonbones/renderer/DBCCFactory.h"

using namespace dragonBones;
using namespace cocos2d;
class Number : public Ref
{
public:
	Number(void);
	~Number(void);

	GameImage* ball;

	LabelBM* label;
	int id;
	bool isFall;
	DBCCArmatureNode* eff;
	float width, height;
	float x, y;
	bool visible;

	bool isVisible();
	void setVisible(bool visible);
	void addToParent(CCNode* parent);
	void setX(float x);
	void setY(float y);
	void setPosition(float x, float y);
	float getWidth();
	float getHeight();
	float getX();
	float getY();
	void setNumber(int number);
	void effectNewGame();
	void effectEndGame();
	void effectEat();
	void doEffectEat();
	int countEffect;
	void stopAllActions();
	void updateSize();
	void remove();
};
#endif // Number_h__


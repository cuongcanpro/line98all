#ifndef _ObjectNumberPop_h__
#define _ObjectNumberPop_h__
#include <cocos2d.h>
#include "Engine/GUI/GameImage.h"
#include "Engine/GUI/LabelBM.h"
#include "ui/UIText.h"
#include "dragonbones/DragonBones.h"
#include "dragonbones/renderer/DBCCFactory.h"
using namespace dragonBones;
using namespace cocos2d;
using namespace cocos2d::ui;
class ObjectNumberPop : public CCNode
{
public:

	ObjectNumberPop(void);
	~ObjectNumberPop(void);
	Sprite* ball;
	Sprite* border;
	Sprite* bomb;
	Text* label;
	DBCCArmatureNode* eff;
	DBCCArmatureNode* eff1;
	
	int number;
	float rootX;
	float rootY;
	bool isEffect();
	void playEffect();
	bool getAvailable() const { return available; }
	void setAvailable(bool val) { available = val; }
	void setRootPosition();
	void resetPosition();
	void setNumber(int number);
	int getNumber() { return number; };
	void increaseNumber(int num);
	void callback1();
	void callback2();
	bool checkSame(int _number);
	void moveDown(float time);
	void callbackMoveDown();
	void moveToEat(float time, Vec2 pos);
	void callbackMoveEat();
	void effectNewGame();
	void effectEndGame();
	void showBomb(bool show);
	void setNewNumber();
	
private:
	bool available;
};
#endif

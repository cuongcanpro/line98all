#ifndef _GroupNewNumberPop_h__
#define _GroupNewNumberPop_h__
#include <cocos2d.h>
#include "Engine/GUI/GameImage.h"
#include "Engine/GUI/LabelBM.h"
#include "ui/UIText.h"
#include "dragonbones/DragonBones.h"
#include "dragonbones/renderer/DBCCFactory.h"
#include "ObjectNumberPop.h"
#include "Engine/GUI/Paper.h"
#include "ui/UIButton.h"
#include "Engine/GUI/StarFly.h"
using namespace dragonBones;
using namespace cocos2d;
using namespace cocos2d::ui;
class GroupNewNumberPop : public CCNode
{
public:

	GroupNewNumberPop(void);
	~GroupNewNumberPop(void);
	cocos2d::LayerColor* layerColor;
	DBCCArmatureNode* eff;
	DBCCArmatureNode* eff1;
	ObjectNumberPop* newNumber;
	Paper* paperRight;
	Paper* paperLeft;
	StarFly* starFly;
	Button* btnOk;
	Sprite* imgCongrat;
	Text* lbCongrat;
	void showNewNumber(int number, Vec2 pos, float scale);
	void callbackShowNew();
};
#endif

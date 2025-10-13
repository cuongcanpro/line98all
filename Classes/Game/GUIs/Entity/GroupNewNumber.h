#ifndef _GroupNewNumber_h__
#define _GroupNewNumber_h__
#include <cocos2d.h>
#include "Engine/GUI/GameImage.h"
#include "Engine/GUI/LabelBM.h"
#include "ui/UIText.h"
#include "dragonbones/DragonBones.h"
#include "dragonbones/renderer/DBCCFactory.h"
#include "ObjectNumber.h"
#include "Engine/GUI/Paper.h"
#include "ui/UIButton.h"
#include "Engine/GUI/StarFly.h"
using namespace dragonBones;
using namespace cocos2d;
using namespace cocos2d::ui;
class GroupNewNumber : public CCNode
{
public:

	GroupNewNumber(void);
	~GroupNewNumber(void);
	cocos2d::LayerColor* layerColor;
	DBCCArmatureNode* eff;
	DBCCArmatureNode* eff1;
	ObjectNumber* newNumber;
	Paper* paperRight;
	Paper* paperLeft;
	StarFly* starFly;
	Button* btnOk;

	void showNewNumber(int number, Vec2 pos, float scale);
	void callbackShowNew();
};
#endif

#include "GroupNewNumber.h"
#include <cmath>  
#include <string>
#include "../../Utility/GameUtility.h"
#include "Game/Utility/JNIUtils.h"
#include "Game/Utility/GameSound.h"
#include "Game/GUIManager.h"


GroupNewNumber::GroupNewNumber(void)
{
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();
	layerColor = CCLayerColor::create(ccc4(0, 0, 0, 200), size.width, size.height);
	addChild(layerColor);
	layerColor->setContentSize(size);
	layerColor->setVisible(true);
	layerColor->setOpacity(0);

	starFly = new StarFly(size.width, size.height * 0.6);
	addChild(starFly);
	starFly->setPosition(0, size.height * 0.3);

	paperLeft = new Paper(size.width * 0.5, 300, 1, 1);
	addChild(paperLeft);
	paperLeft->setPosition(0, size.height * 0.45);
	//paperLeft->startEffect();
	paperLeft->setLocalZOrder(4);

	paperRight = new Paper(size.width * 0.5, 300, -1, 1);
	addChild(paperRight);
	paperRight->setPosition(size.width, size.height * 0.45);
	//paperRight->startEffect();
	paperRight->setLocalZOrder(4);

	Vec2 pos = ccp(size.width * 0.5, size.height * 0.65);
	eff = DBCCFactory::getInstance()->buildArmatureNode("tile_light");
	if (eff) {
		this->addChild(eff);
		eff->setPosition(pos);
	}

	eff1 = DBCCFactory::getInstance()->buildArmatureNode("cast_skill_vua_le_hoi");
	if (eff1) {
		this->addChild(eff1);
		eff1->setPosition(pos.x, pos.y + 50);
	}

	newNumber = new ObjectNumber();
	addChild(newNumber);
	newNumber->setVisible(true);

	btnOk = Button::create("btnOk.png", "btnOk.png", "btnOk.png", Widget::TextureResType::PLIST);
	addChild(btnOk);
	btnOk->setPosition(ccp(size.width * 0.5, size.height * 0.35));
	btnOk->addClickEventListener([this](Ref* sender)
	{
		btnOk->runAction(CCScaleTo::create(0.5, 0));
		newNumber->runAction(CCSpawn::create(
			CCEaseBackIn::create(CCScaleTo::create(0.4, 0)),
			CCFadeOut::create(0.5),
			NULL
		));

		layerColor->runAction(
			CCFadeOut::create(0.5)
		);

		this->runAction(
			CCSequence::create(
				CCDelayTime::create(0.5),
				CCHide::create(),
				NULL
			)
		);
		GUIManager::getInstance().guiMerge.resumeGame();
	});

	setCascadeColorEnabled(true);
	setCascadeOpacityEnabled(true);
}

GroupNewNumber::~GroupNewNumber(void)
{

}

void GroupNewNumber::showNewNumber(int number, Vec2 pos, float scale)
{
	if (isVisible())
		return;
	setOpacity(255);
	setVisible(true);
	GameSound::playLevelUp();
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();
	layerColor->setVisible(true);
	layerColor->setOpacity(0);
	layerColor->stopAllActions();
	layerColor->runAction(CCSequence::create(
		CCEaseIn::create(CCFadeTo::create(0.5, 200), 2),
		CCDelayTime::create(1.8),
		NULL
	));

	if (eff) {
		eff->setVisible(true);
		eff->gotoAndPlay("run", 0.5, -1, 1);
		eff->setCompleteListener([](dragonBones::DBCCArmatureNode* armature) {
			armature->setVisible(false);
		});
	}

	if (eff1) {
		eff1->setVisible(true);
		eff1->gotoAndPlay("run", 0.5, -1, 1);
		eff1->setCompleteListener([](dragonBones::DBCCArmatureNode* armature) {
			armature->setVisible(false);
		});
	}

	newNumber->setVisible(true);
	newNumber->setNumber(number);
	newNumber->setPosition(pos);
	newNumber->setScale(scale);
	newNumber->setOpacity(255);
	newNumber->runAction(
		CCSequence::create(
			CCSpawn::create(
				CCEaseOut::create(CCScaleTo::create(0.4, 2), 2),
				CCEaseOut::create(CCMoveTo::create(0.4, ccp(size.width * 0.5, size.height * 0.65)), 2),
				NULL
			),
			CCSpawn::create(CCRotateTo::create(0.4, Vec3(0, -20, 0)), CCMoveBy::create(0.4, ccp(-5, 0)), NULL),
			CCSpawn::create(CCRotateTo::create(0.4, Vec3(10, 20, 0)), CCMoveBy::create(0.4, ccp(10, 0)), NULL),
			CCSpawn::create(CCRotateTo::create(0.4, Vec3(0, 0, 0)), CCMoveBy::create(0.4, ccp(-5, 0)), NULL),
			NULL
		)
	);
	paperRight->startEffect();
	paperLeft->startEffect();

	btnOk->setVisible(true);
	btnOk->setScale(1);
	btnOk->setOpacity(0);
	btnOk->runAction(
		CCSequence::create(
			CCDelayTime::create(3.5),
			CCCallFunc::create(this, callfunc_selector(GroupNewNumber::callbackShowNew)),
			CCFadeIn::create(0.5),
			NULL
		)
	);

	starFly->setVisible(true);
	starFly->startEffect();
}

void GroupNewNumber::callbackShowNew()
{
	if (newNumber->getNumber() % 2 == 0)
		game->showAdsFull();
}

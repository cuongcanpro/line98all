#include "GroupNewNumberPop.h"
#include <cmath>  
#include <string>
#include "../../Utility/GameUtility.h"
#include "Game/Utility/JNIUtils.h"
#include "Game/Utility/GameSound.h"
#include "Game/GUIManager.h"


GroupNewNumberPop::GroupNewNumberPop(void)
{
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();
	layerColor = CCLayerColor::create(ccc4(0, 0, 0, 200), size.width, size.height);
	addChild(layerColor);
	layerColor->setContentSize(size);
	layerColor->setVisible(true);
	layerColor->setOpacity(0);

	imgCongrat = Sprite::create("480_800/imgCongrat.png");
	addChild(imgCongrat);
	imgCongrat->setPosition(0, size.height * 0.8);

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

	newNumber = new ObjectNumberPop();
	addChild(newNumber);
	newNumber->setVisible(true);
	newNumber->setNewNumber();

	lbCongrat = Text::create("You have just unlocked number 10", "fonts/tahomabd.ttf", 23);
	lbCongrat->enableOutline(ccc4(50, 10, 0, 255), 2);
	addChild(lbCongrat, 10);
	lbCongrat->setPosition(ccp(size.width * 0.5, size.height * 0.3));

	btnOk = Button::create("480_800/btnOk.png", "480_800/btnOk.png", "480_800/btnOk.png");
	addChild(btnOk);
	btnOk->setPosition(ccp(size.width * 0.5, lbCongrat->getPositionY() - btnOk->getContentSize().height * 1.2));
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
		lbCongrat->runAction(CCFadeOut::create(0.5));
		imgCongrat->runAction(FadeOut::create(0.5));
		GUIManager::getInstance().guiPop.updatePosCenter();
	});

	setCascadeColorEnabled(true);
	setCascadeOpacityEnabled(true);
}

GroupNewNumberPop::~GroupNewNumberPop(void)
{

}

void GroupNewNumberPop::showNewNumber(int number, Vec2 pos, float scale)
{
	if (isVisible())
		return;
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();
	float centerY = size.height * 0.6;
	lbCongrat->setString("You have just unlocked number " + GameUtility::toString(number));
	lbCongrat->setOpacity(0);
	lbCongrat->setPosition(ccp(size.width * 0.5, centerY - newNumber->getContentSize().height * 0.5 * 2 - lbCongrat->getContentSize().height * 2));
	lbCongrat->runAction(
		Sequence::create(
			DelayTime::create(2.0),
			FadeIn::create(0.5),
			NULL
		)
	);
	setOpacity(255);
	setVisible(true);
	GameSound::playLevelUp();
	
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

	imgCongrat->setOpacity(0);
	imgCongrat->setPosition(size.width * 0.5, size.height + 200);
	imgCongrat->runAction(
		Sequence::create(
			DelayTime::create(2.0),
			CCSpawn::create(
				EaseBackOut::create(MoveTo::create(0.5, ccp(size.width * 0.5, size.height * 0.6 + newNumber->getContentSize().height * 0.5 * 2 + imgCongrat->getContentSize().height * 0.7))),
				FadeIn::create(0.5),
				NULL
			),
			NULL
		)
	);

	newNumber->setVisible(true);
	newNumber->setNumber(number);
	newNumber->setPosition(pos);
	newNumber->setScale(scale);
	newNumber->setOpacity(255);
	newNumber->runAction(
		CCSequence::create(
			CCSpawn::create(
				CCEaseOut::create(CCScaleTo::create(0.4, 2), 2),
				CCEaseOut::create(CCMoveTo::create(0.4, ccp(size.width * 0.5, size.height * 0.6)), 2),
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
	btnOk->setPositionY(lbCongrat->getPositionY() - btnOk->getContentSize().height * 1.5);
	btnOk->setScale(1);
	btnOk->setOpacity(0);
	btnOk->runAction(
		CCSequence::create(
			CCDelayTime::create(3.5),
			CCCallFunc::create(this, callfunc_selector(GroupNewNumberPop::callbackShowNew)),
			CCFadeIn::create(0.5),
			NULL
		)
	);

	starFly->setVisible(true);
	starFly->startEffect();
}

void GroupNewNumberPop::callbackShowNew()
{
	if (newNumber->getNumber() % 2 == 0)
		game->showAdsFull();
}

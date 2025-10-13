#include "ObjectNumberPop.h"
#include <cmath>  
#include <string>
#include "../../Utility/GameUtility.h"
#include "Game/Utility/JNIUtils.h"


ObjectNumberPop::ObjectNumberPop(void)
{
	ball = Sprite::create("480_800/bgNumber2.png");
	addChild(ball);
	setContentSize(ball->getContentSize());

	label = Text::create("SCORE", "fonts/tahomabd.ttf", 40);
	addChild(label);
	label->enableOutline(Color4B(115, 37, 31, 255), 2);

	bomb = Sprite::create("480_800/iconBomb.png");
	addChild(bomb);
	bomb->setOpacity(50);
	bomb->setScale(1.3);
	//bomb->setAnchorPoint(ccp(0, 0));
	//bomb->setPosition(-ball->getContentSize().width * 0.5, -ball->getContentSize().height * 0.5);
	bomb->setVisible(false);
	setNumber(0);
	setCascadeColorEnabled(true);
	setCascadeOpacityEnabled(true);
}


void ObjectNumberPop::setRootPosition()
{
	rootX = getPositionX();
	rootY = getPositionY();
}

void ObjectNumberPop::resetPosition()
{
	setPositionX(rootX);
	setPositionY(rootY);
}

void ObjectNumberPop::setNumber(int number)
{
	setVisible(true);
	setAvailable(true);
	if (number == this->number)
		return;
	this->number = number;
	label->setText(GameUtility::toString(number).c_str());
	string s = "480_800/" + GameUtility::toString(number % 16) + ".png";
	s = "480_800/bgNumber2.png";
	ball->setTexture(s.c_str());
	ball->setColor(GameUtility::getColorPop(number));

	if (number >= 100) {
		ball->setVisible(false);
		s = "480_800/level" + GameUtility::toString(number % 10 + 1) + ".png";
		border->setTexture(s);
		//label->enableOutline(Color4B(115, 37, 31, 255), 1);
		
	}
	else {
		//label->disableEffect();
		ball->setVisible(true);
	}
}

void ObjectNumberPop::increaseNumber(int num)
{
	number = number + num;
	setNumber(number);
	playEffect();
	//JNIUtils::vibrate();
}

bool ObjectNumberPop::isEffect()
{
	return eff->isVisible();
}

void ObjectNumberPop::playEffect()
{
	eff->setVisible(true);
	eff->setOpacity(0);
	eff->runAction(
		CCSequence::create(
			CCDelayTime::create(0.1),
			CCFadeIn::create(0.1),
			NULL
		)
	);

	//eff->gotoAndPlay("1", 0.1, -1, 1);
	eff->gotoAndPlay("vienkhung", 0.1, 0.7, 1);
	eff->setCompleteListener([](dragonBones::DBCCArmatureNode* armature) {
		armature->setVisible(false);
	});

	eff1->setVisible(true);
	eff1->setOpacity(0);
	eff1->runAction(
		CCSequence::create(
			CCDelayTime::create(0.1),
			CCFadeIn::create(0.1),
			NULL
		)
	);
	eff1->gotoAndPlay("1", 0.1, -1, 1);
	eff1->setCompleteListener([](dragonBones::DBCCArmatureNode* armature) {
		armature->setVisible(false);
	});
}

void ObjectNumberPop::callback1()
{
	label->runAction(
		CCSequence::create(
			CCEaseBackIn::create(CCScaleTo::create(0.4, 0)),
			CCCallFunc::create(this, callfunc_selector(ObjectNumberPop::callback2)),
			NULL
		)
	);
}

void ObjectNumberPop::callback2()
{
	setNumber(number);
	label->runAction(
		CCSequence::create(
			CCEaseBounceOut::create(CCScaleTo::create(0.5, 1)),
			//CCCallFunc::create(this, callfunc_selector(Number::effectEndGame)),
			NULL
		)
	);
}

bool ObjectNumberPop::checkSame(int _number)
{
	return number == _number;
}

void ObjectNumberPop::moveDown(float time)
{
	stopAllActions();
	runAction(CCSequence::create(
		CCMoveTo::create(time, ccp(rootX, rootY)),
		CCCallFunc::create(this, callfunc_selector(ObjectNumberPop::callbackMoveDown)),
		NULL
	));
	runAction(
		CCSequence::create(
			CCDelayTime::create(time),
			CCScaleTo::create(time * 0.4, 1.05, 0.9),
			CCEaseBounceOut::create(CCScaleTo::create(time * 0.6, 1, 1)),
			NULL
		)
	);
}

void ObjectNumberPop::callbackMoveDown()
{
	//setIsIdle(true);
}

void ObjectNumberPop::moveToEat(float time, Vec2 pos)
{
	stopAllActions();
	runAction(CCSequence::create(
		CCMoveTo::create(time, pos),
		CCCallFunc::create(this, callfunc_selector(ObjectNumberPop::callbackMoveEat)),
		NULL
	));
	setAvailable(false);
}

void ObjectNumberPop::callbackMoveEat()
{
	setVisible(false);
}

ObjectNumberPop::~ObjectNumberPop(void)
{
}

void ObjectNumberPop::effectNewGame()
{
	float sX = ball->getScaleX();
	float sY = ball->getScaleY();
	setScale(0);
	float delay = GameUtility::getRandom() * 0.3;
	runAction(
		CCSequence::create(
			CCDelayTime::create(delay),
			CCEaseExponentialOut::create(CCScaleTo::create(0.5, 1, 1)),
			NULL
		)
	);
}

void ObjectNumberPop::effectEndGame()
{
	float pX = 5 * (0.5 - GameUtility::getRandom()) + rootX;
	float pY = 5 * (0.5 - GameUtility::getRandom()) + rootY;
	runAction(CCSequence::create(
		CCMoveTo::create(0.02 + GameUtility::getRandom() * 0.08, Vec2(pX, pY)),
		CCCallFunc::create(this, callfunc_selector(ObjectNumberPop::effectEndGame)),
		NULL
	));

}

void ObjectNumberPop::showBomb(bool show)
{
	bomb->setVisible(show);
	if (show) {
		bomb->setOpacity(0);
		bomb->runAction(FadeTo::create(0.5, 50));
	}
}

void ObjectNumberPop::setNewNumber()
{
	label->setFontSize(80);
	label->setScale(0.5);

	Sprite* border = Sprite::create("480_800/border.png");
	addChild(border);
	border->setScale(0.75);
}

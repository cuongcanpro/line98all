#include "Paper.h"
#include "Game/Utility/GameUtility.h"

Paper::Paper(float width, float height, int directionX, int directionY): CCNode()
{
	this->width = width;
	this->height = height;
	countGen = 0.2;
	this->directionX = directionX;
	this->directionY = directionY;
}

void Paper::startEffect()
{
	setVisible(true);
	schedule(schedule_selector(Paper::updateEffect), 0.02);
	/*for (int i = 0; i < 10; i++) {
		CCSprite* sprite = getStar();
		effectStar(sprite);
	}*/
	countGen = 0.0;
	lifeTime = 2;
}

void Paper::effectStar(CCSprite* sprite)
{
	float delayTime = 0;
	//sprite->setBlendFunc(BlendFunc{ GL_DST_COLOR, GL_ONE });
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	
	Vec2 p1 = ccp(0, (0.5 - GameUtility::getRandom()) * 1);
	Vec2 p2 = ccp(
		width * 0.75 * (0.25 + GameUtility::getRandom()) * directionX,
		height * GameUtility::getRandom() * directionY
	);
	Vec2 p3 = ccp(
		(p1.x + p2.x) / 2 + (0.5 - GameUtility::getRandom()) * 300,
		(p1.y + p2.y) / 2 + (0.5 - GameUtility::getRandom()) * 150
	);

	p3 = ccp(
		(p1.x + p2.x) / 2 + (0.5 - GameUtility::getRandom()) * 50,
		(p1.y + p2.y) / 2 + (0.5 - GameUtility::getRandom()) * 50
	);
	float rTime = (1.5 + GameUtility::getRandom() * 1.2) * (width / size.width);

	sprite->runAction(CCSequence::create(
		CCDelayTime::create(delayTime + rTime / 5),
		CallFuncN::create(CC_CALLBACK_1(Paper::callbackEffectStar, this)),
		NULL
	));

	ccBezierConfig bezier;
	bezier.controlPoint_1 = p1;
	bezier.controlPoint_2 = p3;
	bezier.endPosition = p2;
	sprite->setPosition(0, 0);
	sprite->setOpacity(0);
	sprite->runAction(CCSequence::create(
		CCDelayTime::create(delayTime),
		CCFadeIn::create(0),
		CCEaseExponentialOut::create(CCBezierTo::create(rTime, bezier)),
		NULL
	));
	
	float delayRemove = delayTime + rTime - 0.1 > 0 ? delayTime + rTime - 0.1 : 0;
	sprite->runAction(CCSequence::create(
		CCDelayTime::create(delayRemove),
		CCFadeOut::create(0.1),
		CCHide::create(),
		NULL
	));

}

void Paper::updateEffect(float dt) {
	if (lifeTime > 0) {
		countGen = countGen - dt;
		if (countGen <= 0) {
			for (int i = 0; i < 3; i++) {
				CCSprite* sprite = getStar();
				sprite->setTexture("particles/p" + GameUtility::toString(GameUtility::getRandom() * 5) + ".png");
				effectStar(sprite);
			}
			countGen = 0.05;
		}
		lifeTime = lifeTime - dt;
		if (lifeTime <= 0) {
			runAction(
				CCSequence::create(
					CCDelayTime::create(2.0),
					CCHide::create(),
					NULL
				)
			);
		};
	}
}

cocos2d::CCSprite* Paper::getStar()
{
	CCSprite* image = NULL;
	for (int i = 0; i < arrayStar.size(); i++) {
		if (!arrayStar.at(i)->isVisible()) {
			image = arrayStar.at(i);
			break;
		}
	}
	if (image == NULL) {
		image = CCSprite::create("480_800/stars.png");
		this->addChild(image);
		arrayStar.push_back(image);
	}
	image->setVisible(true);
	image->setOpacity(255);
	image->stopAllActions();
	image->setScale(1);
	return image;
}

void Paper::callbackEffectStar(CCNode* sender)
{
	float rSpin = GameUtility::getRandom() * 0.25 + 0.25;
	float osX = sender->getScaleX();
	float osY = sender->getScaleY();
	float r1 = round(GameUtility::getRandom());
	float r2 = round(GameUtility::getRandom());
	if (r1 == r2 && r1 == 0) {
		r1 = 1;
	}
	if (r1 == r2 && r1 == 1) {
		r1 = 0;
	}
	sender->runAction(
		CCRepeatForever::create(
			CCSequence::create(
				CCScaleTo::create(rSpin, r1 * osX, r2 * osY),
				CCScaleTo::create(rSpin, osX, osY),
				NULL
			)
		)
	);
}

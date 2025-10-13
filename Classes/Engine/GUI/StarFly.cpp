#include "StarFly.h"
#include "Game/Utility/GameUtility.h"

StarFly::StarFly(float width, float height): CCNode()
{
	this->width = width;
	this->height = height;
	countGen = 0.2;
}

void StarFly::startEffect()
{
	setVisible(true);
	schedule(schedule_selector(StarFly::updateEffect), 0.02);
	for (int i = 0; i < 10; i++) {
		CCSprite* sprite = getStar();
		effectStar(sprite);
	}
	countGen = 0.1;
	lifeTime = 100;
}

void StarFly::effectStar(CCSprite* sprite)
{
	//sprite->setBlendFunc(BlendFunc{ GL_DST_COLOR, GL_ONE });
	
	sprite->setPosition(width * GameUtility::getRandom(), height * (GameUtility::getRandom() * 0.2));
	float randomTime = GameUtility::getRandom() * 2 + 4;
	float rAction1 = GameUtility::getRandom();
	float rAction2 = GameUtility::getRandom();
	float rScale = GameUtility::getRandom() * 0.6 + 0.6;
	float rOpacity = GameUtility::getRandom() * 100 + 155;

	float rTimeOpacity = GameUtility::getRandom();
	float rTimeBlink = GameUtility::getRandom() + 0.1;
	Vec2 pos = sprite->getPosition();
	sprite->setScale(rScale);
	//sprite->setOpacity(rOpacity);
	sprite->setOpacity(255);
	sprite->setPosition(pos);
	Vec2 p1 = pos;
	Vec2 p2 = ccp(GameUtility::getRandom() * width, (GameUtility::getRandom() * 0.2 + 0.8) * height);
	Vec2 p3 = ccp(p1.x / 2 + p2.x / 2 + (GameUtility::getRandom() - 0.5) * width, p1.y / 2 + p2.y / 2 + (GameUtility::getRandom() - 0.5) * height);
	Vec2 p4 = ccp(p1.x / 2 + p2.x / 2 + (GameUtility::getRandom() - 0.5) * width, p1.y / 2 + p2.y / 2 + (GameUtility::getRandom() - 0.5) * height);
	ccBezierConfig bezier;
	bezier.controlPoint_1 = p2;
	bezier.controlPoint_2 = p3;
	bezier.endPosition = p4;
	sprite->runAction(
		CCSequence::create(
			CCSpawn::create(
				CCBezierTo::create(randomTime, bezier),
				CCSequence::create(
					CCFadeOut::create(randomTime),
					NULL
				),
				NULL
			),
			CCHide::create(),
			NULL
		)
	);
	sprite->runAction(
		CCRepeatForever::create(
			CCSequence::create(
				CCSpawn::create(
					CCSequence::create(
						CCFadeIn::create(rTimeBlink),
						CCFadeOut::create(rTimeBlink),
						NULL
					),
					NULL
				),
				NULL
			)
		)
	);
}

void StarFly::updateEffect(float dt) {
	if (lifeTime > 0) {
		countGen = countGen - dt;
		if (countGen <= 0) {
			for (int i = 0; i < 3; i++) {
				CCSprite* sprite = getStar();
				effectStar(sprite);
			}
			
			countGen = 0.2;
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

cocos2d::CCSprite* StarFly::getStar()
{
	CCSprite* image = NULL;
	for (int i = 0; i < arrayStar.size(); i++) {
		if (!arrayStar.at(i)->isVisible()) {
			image = arrayStar.at(i);
			break;
		}
	}
	if (image == NULL) {
		image = CCSprite::create("particles/spark.png");
		this->addChild(image);
		arrayStar.push_back(image);
	}
	image->setVisible(true);
	return image;
}

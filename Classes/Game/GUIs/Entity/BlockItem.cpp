#include "BlockItem.h"
#include "Game/Data/GlobalData.h"
#include "Game/Utility/GameUtility.h"
#include "Engine/GlobalVar.h"


BlockItem::BlockItem(void)
{
	ball = new GameImage("title.png", true);
	ball->setWidth(WIDTH_BALL * 1.2f);
	ball->setHeight(HEIGH_BALL * 1.2f);
	//ball->getImg()->setAnchorPoint(ccp(0, 0));

	image = new GameImage("icon_3_1.png", true);
	float newHeight = WIDTH_BALL * 0.9f / image->getWidth() * image->getHeight();
	image->setWidth(WIDTH_BALL * 0.7f);
	image->setHeight(HEIGH_BALL * 0.7f);
	image->setPositionX(ball->getRealWidth() * 0.45f);
	image->setPositionY(ball->getRealHeight() * 0.57f);

	width = WIDTH_BALL;
	height = HEIGH_BALL;
	x = 0;
	y = 0;
	visible = false;
}


BlockItem::~BlockItem(void)
{
	
}


bool BlockItem::isVisible()
{
	return visible;
}

void BlockItem::setVisible(bool visible)
{
	this->visible = visible;
	ball->setVisible(visible);
	image->setVisible(visible);
}
void BlockItem::addToParent(CCNode* layer)
{
	layer->addChild(ball);
	layer->addChild(image);
}

void BlockItem::setX(float x)
{
	float dx = x - this->x;
	this->x = x;
	ball->setPositionX(this->x + ball->getRealWidth() * 0.5);
	image->setPositionX(ball->getPositionX() - ball->getRealWidth() * 0.1);
}

void BlockItem::setY(float y)
{
	float dy = y - this->y;
	this->y = y;
	ball->setPositionY(this->y + ball->getRealHeight() * 0.5);
	image->setPositionY(ball->getPositionY() + ball->getRealHeight() * 0.1);
}

void BlockItem::setPosition(float x, float y)
{
	setX(x);
	setY(y);
}
float BlockItem::getWidth()
{
	return WIDTH_BALL;
}
float BlockItem::getHeight()
{
	return height;
}
float BlockItem::getX()
{
	return x;
}
float BlockItem::getY()
{
	return y;
}
void BlockItem::setNumber(int _id) {
	id = _id;
	//game->typeTheme = 3;
	//if (game->typeTheme < 0)
		//game->typeTheme = 0;
    
	int typeTheme = 1;
  
	image->setImage(("icon_" + to_string(typeTheme) + "_" + GameUtility::toString(_id + 1) + ".png").c_str(), true);
	float rate = image->getHeight() / image->getWidth();
	if (rate > 1)
	{
		image->setHeight(0.7f * HEIGH_BALL);
		image->setWidth(0.7f * HEIGH_BALL / rate);
		
	}
	else {
		image->setHeight(0.65f * HEIGH_BALL);
		image->setWidth(0.65f * HEIGH_BALL);
	}
	/*else
	{
		image->setWidth(0.7f * WIDTH_BALL);
		image->setHeight(0.7f * WIDTH_BALL * rate);
	}*/

	//image.setPosition(x + Constant.WIDTH_BALL * 0.5f - image.getRealWidth() * 0.5f, y + Constant.HEIGH_BALL * 0.5f - image.getRealHeight() * 0.5f);
}

void BlockItem::runAction( float x, float y )
{
	//setPosition(this->x + x, this->y + y);
	this->ball->setPosition(this->ball->getPositionX() - x, this->ball->getPositionY() - y);
	this->ball->runAction(CCEaseSineOut::create(CCMoveBy::create(0.15, ccp(x, y))));

	this->image->setPosition(this->image->getPositionX() - x, this->image->getPositionY() - y);
	this->image->runAction(CCEaseSineOut::create(CCMoveBy::create(0.15, ccp(x, y))));
}

void BlockItem::effectNewGame(float delayTime)
{
	float scaleX = ball->getScaleX();
	float scaleY = ball->getScaleY();
	ball->setScale(0);
	ball->runAction(CCSequence::create(
		CCDelayTime::create(delayTime),
		CCEaseBackOut::create(CCScaleTo::create(0.2, scaleX, scaleY)),
		NULL
	));

	scaleX = image->getScaleX();
	scaleY = image->getScaleY();
	image->setScale(0);
	image->runAction(
		CCSequence::create(
			CCDelayTime::create(delayTime),
			CCEaseBackOut::create(CCScaleTo::create(0.2, scaleX, scaleY)),
			NULL
		));
	//image->setVisible(false);
}


void BlockItem::effectEndGame(float delayTime)
{
	ball->getImg()->runAction(CCSequence::create(
		CCDelayTime::create(delayTime),
		CCTintTo::create(0.5, ccc3(100, 100, 100)),
		NULL
	));

	image->getImg()->runAction(CCSequence::create(
		CCDelayTime::create(delayTime),
		CCTintTo::create(0.5, ccc3(100, 100, 100)),
		NULL
	));

}

void BlockItem::setSelect(bool isSelect)
{
	if(isSelect)
		ball->setImage("titleSelect.png", true);
	else
	{
		ball->setImage("title.png", true);
	}
	ball->setWidth(WIDTH_BALL * 1.2f);
	ball->setHeight(HEIGH_BALL * 1.2f);
	//ball->getImg()->setAnchorPoint(ccp(0, 0));
	if (isSelect) {
		float scaleX = ball->getScaleX();
		float scaleY = ball->getScaleY();
		ball->runAction(CCSequence::create(
			CCScaleTo::create(0.1, scaleX * 1.1, scaleY * 1.1),
			CCScaleTo::create(0.1, scaleX, scaleY),
			NULL
		));

		scaleX = image->getScaleX();
		scaleY = image->getScaleY();
		image->runAction(
			CCSequence::create(
			CCScaleTo::create(0.2, scaleX * 1.1, scaleY * 1.1),
			CCScaleTo::create(0.2, scaleX, scaleY),
			NULL
		));
	}
	
}

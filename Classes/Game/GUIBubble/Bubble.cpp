#include "Bubble.h"
#include "../Utility/GameUtility.h"
#include "../../Engine/GlobalVar.h"
#include "Game/GUIManager.h"


Bubble::Bubble(void):CCNode()
{
}

Bubble::Bubble( const char *nameImg, bool frame ):CCNode()
{
	countTime = 0;
	frameTime = 0.1f;
	currentFrame = 0;

	bg = new GameImage(GameUtility::getTextureColor(1).c_str());
	this->addChild(bg);

	label = LabelBM::create("0", FONT_BOLD_TYPE);
	label->setAnchorPoint(ccp(0.55f, 0.65f));
	this->addChild(label);
}


Bubble::~Bubble(void)
{
}

void Bubble::update()
{

}

void Bubble::setState( BubbleState _state )
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	float dy = size.height * 0.007f;
	state = _state;
	currentFrame = 0;
	setScaleX(1);
	setScaleY(1);
	setPos(rootX, rootY);
	switch (state)
	{
	case JUMP_BUBBLE:
		cleanup();
		runAction(CCRepeatForever::create(CCSequence::create(CCScaleTo::create(0.5f, rootScaleX * 0.8f), 
			CCScaleTo::create(0.5f, rootScaleX), NULL)));
		break;
	case NORMAL_BUBBLE:
		cleanup();
		
		setVisible(true);
		break;
	case DISAPPEAR_BUBBLE:
		cleanup();
		setVisible(false);
		break;
	case SMALL_BUBBLE:
		cleanup();
		setPos(rootX, rootY);
		setScaleX(0.4f * 1);
		setScaleY(1 * 0.4f);
		break;
	case BIGGER_BUBBLE:
	{
		cleanup();
		//setScale(rootScaleX * 0.4f);
		setVisible(true);

		ccColor3B temp = bg->getImg()->getColor();
		//bg->setColor(ccc3(255, 255, 255));
		bg->getImg()->runAction(CCTintTo::create(0.1f, temp.r, temp.g, temp.b));
		//runAction(CCScaleTo::create(0.035f, rootScaleX, rootScaleY));
	}
		break;
	case AUTO_SCORE_BUBBLE:
	{
		currentScore = id;
		nextScore = id * 4;
		deltaScore = (nextScore - currentScore) / 10;
		updateNumber();
	}
		break;
	default:
		break;
	}
}

void Bubble::setImage( const char* nameImg )
{
// 	if(strcmp(nameImg, nameImage.c_str()) == 0)
// 	{
// 
// 	}
// 	else
// 	{
// 		string s(nameImg);
// 		nameImage = s;
// 		Image::setImage((s + ".png").c_str());
		
//	}
	
}

void Bubble::setPos( float x, float y )
{
	CCNode::setPosition(x, y);
	rootX = x;
	rootY = y;
}

void Bubble::setNumber(int _id) {
	//_id = 1024;
	id = _id;
	int color = 1;
	//int color = sqrt(id);
	
	//bg->setColor(GameUtility::getColor(_id));
    bg->setImage(GameUtility::getTextureColor(_id).c_str());
	
	float sizeReal = label->getWidth();
	float sizeWish;
	if(_id < 10)
	{
		label->setText("0");
		sizeWish = getContentSize().width * 0.3f;
	}
	else if(_id < 100)
	{
		label->setText("00");
		sizeWish = getContentSize().width * 0.6f;
	}
	else if(_id < 1000)
	{
		label->setText("000");
		sizeWish = getContentSize().width * 0.7f;
	}
	else
	{
		label->setText("0000");
		sizeWish = getContentSize().width * 0.8f;
	}
	sizeReal = label->getWidth();
	float scale = sizeWish / sizeReal;
	label->setScale(scale);
	label->setText(GameUtility::toString(id).c_str());
// 	switch (color % 20) {
// 	case 1:
// 
// 		setColor(GameUtility::getColor(_id));
// 		label->setColor(ccc3(0.4f * 255, 0.4f * 255, 0.4f * 255));
// 		break;
// 	case 2:
// 		setColor(GameUtility::getColor(_id));
// 		label->setColor(ccc3(1.0f * 255, 1.0f * 255, 1.0f * 255));
// 		break;
// 	case 3:
// 		setColor(GameUtility::getColor(_id));
// 		label->setColor(ccc3(1.0f * 255, 1.0f * 255, 1.0f * 255));
// 		break;
// 	case 4:
// 		setColor(GameUtility::getColor(_id));
// 		label->setColor(ccc3(0.3f * 255, 0.3f * 255, 0.3f * 255));
// 		break;
// 	case 5:
// 		setColor(GameUtility::getColor(_id));
// 		label->setColor(ccc3(1.0f * 255, 1.0f * 255, 1.0f * 255));
// 		break;
// 	case 6:
// 		setColor(GameUtility::getColor(_id));
// 		label->setColor(ccc3(1.0f * 255, 1.0f * 255, 1.0f * 255));
// 		break;
// 	case 7:
// 		setColor(GameUtility::getColor(_id));
// 		label->setColor(ccc3(1.0f * 255, 1.0f * 255, 1.0f * 255));
// 		break;
// 	case 8:
// 		setColor(GameUtility::getColor(_id));
// 		label->setColor(ccc3(0.3f * 255, 0.3f * 255, 0.3f * 255));
// 		break;
// 	case 9:
// 		setColor(GameUtility::getColor(_id));
// 		label->setColor(ccc3(1.0f * 255, 1.0f * 255, 1.0f * 255));
// 		break;
// 	case 10:
// 		setColor(GameUtility::getColor(_id));
// 		label->setColor(ccc3(1.0f * 255, 1.0f * 255, 1.0f * 255));
// 		break;
// 	case 11:
// 		setColor(GameUtility::getColor(_id));
// 		label->setColor(ccc3(1.0f * 255, 1.0f * 255, 1.0f * 255));
// 		break;
// 	case 12:
// 		setColor(GameUtility::getColor(_id));
// 		label->setColor(ccc3(0.2f * 255, 0.2f * 255, 0.2f * 255));
// 		break;
// 	case 13:
// 		setColor(GameUtility::getColor(_id));
// 		label->setColor(ccc3(0.9f * 255, 0.9f * 255, 0.9f * 255));
// 		break;
// 	case 14:
// 		setColor(GameUtility::getColor(_id));
// 		label->setColor(ccc3(0.2f * 255, 0.2f * 255, 0.2f * 255));
// 		break;
// 	case 15:
// 		setColor(GameUtility::getColor(_id));
// 		label->setColor(ccc3(0.2f * 255, 0.2f * 255, 0.2f * 255));
// 		break;
// 	case 16:
// 		setColor(GameUtility::getColor(_id));
// 		label->setColor(ccc3(0.2f * 255, 0.2f * 255, 0.2f * 255));
// 		break;
// 	case 17:
// 		setColor(GameUtility::getColor(_id));
// 		label->setColor(ccc3(0.99f * 255, 0.99f * 255, 0.99f * 255));
// 		break;
// 	case 18:
// 		setColor(GameUtility::getColor(_id));
// 		label->setColor(ccc3(0.99f * 255, 0.99f * 255, 0.99f * 255));
// 		break;
// 	case 19:
// 		setColor(GameUtility::getColor(_id));
// 		label->setColor(ccc3(0.99f * 255, 0.99f * 255, 0.99f * 255));
// 		break;
// 	case 0:
// 		setColor(GameUtility::getColor(_id));
// 		label->setColor(ccc3(0.99f * 255, 0.99f * 255, 0.99f * 255));
// 		break;
// 	}
	//label->setColor(ccc3(20, 20, 20));
	//label->setPosition(getWidth() * 0.5f, getHeight() * 0.5f);
// 	label->setPosition(getWidth() * 0.5f - label->getWidth() * 0.5f + getPositionX(),
// 		getHeight() * 0.5f - label->getHeight() * 0.5f + getPositionY());
}

void Bubble::setHeight( float height )
{
	setContentSize(CCSizeMake(getContentSize().width, height));
	rootScaleX = getScaleX();
	bg->setHeight(height);
}

void Bubble::setWidth( float width )
{
	setContentSize(CCSizeMake(width, getContentSize().height));
	rootScaleX = getScaleX();
	bg->setWidth(width);
	float sizeReal = label->getHeight() * rootScaleX;
	float sizeWish = width * 0.6f;
	float scale = sizeWish / sizeReal;
	//label->setScale(scale);
	//label->set
}

float Bubble::getRealHeight()
{
	return getContentSize().height;
}

float Bubble::getRealWidth()
{
	return getContentSize().width;
}

void Bubble::updateNumber()
{
	currentScore = currentScore + deltaScore;
	if (abs(nextScore - currentScore) < 2 * deltaScore)
	{
		setNumber(nextScore);
	}
	else
	{
		label->setText(GameUtility::toString(currentScore).c_str());
		label->runAction(CCSequence::create(CCDelayTime::create(0.05f), CCCallFunc::create(this, callfunc_selector(Bubble::updateNumber)), NULL));
	}
}



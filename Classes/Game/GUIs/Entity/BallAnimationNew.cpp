#include "BallAnimationNew.h"
#include "../../Utility/GameUtility.h"
#include "Engine/GlobalVar.h"
#include "Game/GUIManager.h"


BallAnimationNew::BallAnimationNew(void):GameImage()
{
}

BallAnimationNew::BallAnimationNew( const char *nameImg, bool frame ): GameImage(nameImg, frame)
{
	string s(nameImg);
	nameImage = s;
	countTime = 0;
	frameTime = 0.1f;
	currentFrame = 0;
}


BallAnimationNew::~BallAnimationNew(void)
{
}

void BallAnimationNew::update()
{
	if(true)
		return;
}

void BallAnimationNew::setState( BallState _state )
{
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();
	float dy = getWidth() * rootScaleX * 0.16;
	BallState save = state;
	state = _state;
	currentFrame = 0;
	//stopAllActions();
	switch (state)
	{
	case BallState::JUMP:
		cleanup();
		/*runAction(CCRepeatForever::create(CCSequence::create(
			CCSpawn::create(CCMoveTo::create(0.3f, ccp(rootX, rootY + +dy)), CCSequence::create(CCScaleTo::create(0.15f, rootScaleX * 1.1f, rootScaleY * 0.9f), CCScaleTo::create(0.3f, rootScaleX * 1.0f, rootScaleY * 1.0f), NULL), NULL),
			CCMoveTo::create(0.3f, ccp(rootX, rootY - dy)), NULL)));*/
		runAction(
			Sequence::create(
				Spawn::create(
					ScaleTo::create(0.2, 1.2 * rootScaleX, 0.8 * rootScaleY),
					EaseSineOut::create(MoveTo::create(0.2, ccp(rootX, rootY + dy))),
					NULL
				),
				//EaseSineInOut::create(MoveTo::create(0.2, ccp(rootX, rootY + dy))),
				Repeat::create(
					Sequence::create(
						Spawn::create(
							ScaleTo::create(0.4, rootScaleX, rootScaleY),
							EaseSineIn::create(MoveTo::create(0.4, ccp(rootX, rootY - dy))),
							NULL
						),
						Spawn::create(
							ScaleTo::create(0.1, 1.2 * rootScaleX, 0.8 * rootScaleY),
							EaseSineIn::create(MoveTo::create(0.1, ccp(rootX, rootY - dy * 0.6))),
							NULL
						),
						Spawn::create(
							ScaleTo::create(0.3, rootScaleX * 1.1, rootScaleY * 0.9),
							EaseSineOut::create(MoveTo::create(0.3, ccp(rootX, rootY + dy))),
							NULL
						),
						NULL
					), -1
				),
				NULL
			)
		);

		/*runAction(
			Sequence::create(
				EaseSineInOut::create(MoveTo::create(0.2, ccp(rootX, rootY + dy))),
				Repeat::create(
					Sequence::create(
						EaseSineIn::create(MoveTo::create(0.4, ccp(rootX, rootY - dy))),
						Spawn::create(
							ScaleTo::create(0.1, 1.2 * rootScaleX, 0.8 * rootScaleY),
							EaseSineIn::create(MoveTo::create(0.1, ccp(rootX, rootY - dy * 0.6))),
							NULL
						),
						Spawn::create(
							ScaleTo::create(0.3, rootScaleX, rootScaleY),
							EaseSineOut::create(MoveTo::create(0.3, ccp(rootX, rootY + dy))),
							NULL
						),
						NULL
					), -1
				),
				NULL
			)
		);*/
		break;
	case BallState::NORMAL:
		if (save != BallState::BIGGER) {
			cleanup();
			setScaleX(rootScaleX);
			setScaleY(rootScaleY);
		}
		setPos(rootX, rootY);
		break;
	case BallState::DISAPPEAR:
		setVisible(false);
		break;
	case BallState::SMALL:
		cleanup();
		setPos(rootX, rootY);
		setScale(0);
		runAction(CCScaleTo::create(0.3, rootScaleX * 0.4, rootScaleY * 0.4));
		break;
	case BallState::BIGGER:
		cleanup();
		runAction(CCSequence::create(CCDelayTime::create(GameUtility::getRandom() * 0.3), CCEaseBackOut::create(CCScaleTo::create(0.5f, rootScaleX, rootScaleY)), NULL));
		//runAction(CCEaseBackOut::create(CCScaleTo::create(0.15f, rootScaleX, rootScaleY)));
		break;
	default:
		break;
	}
}

void BallAnimationNew::setImage( const char* nameImg )
{
	string s(nameImg);
	nameImage = s;
	GameImage::setImage(nameImg, false);
	int value = 255 * game->brightBall;
	getImg()->setColor(ccc3(value, value, value));
}

void BallAnimationNew::setIdBall(int idBall)
{
	this->idBall = idBall;
	
	if (idBall > 0 && idBall < 15) {
		int id = (idBall - 1) % 7;
		string s = GameUtility::getResourceBall(id + 1);
		setImage(s.c_str());
		setVisible(true);
		if (idBall > 7) {
			setState(BallState::SMALL);
		}
		else {
			setState(BallState::NORMAL);
		}
	}
	
	else {
		setVisible(false);
	}
}

void BallAnimationNew::setPos( float x, float y )
{
	GameImage::setPos(x, y);
	rootX = x;
	rootY = y;
}


void BallAnimationNew::setNumber(int _id) {
	setColor(GameUtility::getColorLine(_id));
}

void BallAnimationNew::animationNewGame()
{
	stopAllActions();
	float saveScale = getScaleX();
	setScale(0);
	float targetX = rootScaleX;
	float targetY = rootScaleY;
	if (state == BallState::SMALL) {
		targetX = targetX * 0.4;
		targetY = targetY * 0.4;
	}
	if (this->idBall < 100)
		runAction(CCSequence::create(CCDelayTime::create(GameUtility::getRandom() * 0.5), CCEaseBackOut::create(CCScaleTo::create(0.5, targetX, targetY)), NULL));
	else
		runAction(CCSequence::create(CCDelayTime::create(GameUtility::getRandom() * 0.5), CCEaseBackOut::create(CCScaleTo::create(0.5, saveScale, saveScale)), NULL));
}

void BallAnimationNew::effectEndGame(float delay)
{
	runAction(CCSequence::create(
		CCDelayTime::create(delay),
		CCMoveBy::create(0.2, Vec2(0, 20)),
		CCEaseBounceOut::create(CCMoveBy::create(0.5, Vec2(0, -20))),
		NULL
	));
}

void BallAnimationNew::doBreak()
{
	stopAllActions();
	float scale = getScaleX();
	runAction(CCSequence::create(
		CCDelayTime::create(0.3),
		CCRepeat::create(CCSequence::create(CCScaleTo::create(0.06, scale * 1.1), CCScaleTo::create(0.06, scale), NULL), 4),
		CCHide::create(), 
		NULL));
}



void BallAnimationNew::effectVibrate()
{
	if (state == BallState::JUMP)
		return;
	if (state == BallState::BIGGER || state == BallState::NORMAL) {
		stopAllActions();
		setScale(rootScaleX);
	}
	numVibrate = 0;
	doVibrate();
}

void BallAnimationNew::doVibrate()
{
	if (numVibrate > 3) {
		stopAllActions();
		setPosition(rootX, rootY);
		return;
	}
	numVibrate++;
	float pX = rootX + 5 * (0.5 - GameUtility::getRandom());
	float pY = rootY + 5 * (0.5 - GameUtility::getRandom());
	runAction(CCSequence::create(
		CCMoveTo::create(0.01 + GameUtility::getRandom() * 0.004, Vec2(pX, pY)),
		CCCallFunc::create(this, callfunc_selector(BallAnimationNew::doVibrate)),
		NULL
	));
}

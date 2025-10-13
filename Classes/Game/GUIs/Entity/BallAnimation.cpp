#include "BallAnimation.h"
#include "../../Utility/GameUtility.h"
#include "Engine/GlobalVar.h"
#include "Game/GUIManager.h"


BallAnimation::BallAnimation(void):GameImage()
{
}

BallAnimation::BallAnimation( const char *nameImg, bool frame ):GameImage(nameImg, frame)
{
	string s(nameImg);
	nameImage = s;

	countTime = 0;
	frameTime = 0.1f;
	currentFrame = 0;
}


BallAnimation::~BallAnimation(void)
{
}

void BallAnimation::update()
{
	if(!getVisible())
		return;
	if(state == NORMAL || state == SMALL)
		return;
	countTime = countTime + game->deltaTime;
	if(countTime > frameTime)
	{
		countTime = 0;
		currentFrame = currentFrame + 1;
	
		int frame = 0;
		switch (state)
		{
		case JUMP:
			{
				if(currentFrame >= 7)
					currentFrame = 0;
				frame = currentFrame + 1;
			}
		
			break;
		case NORMAL:
			break;
		case DISAPPEAR:
			{
				if(currentFrame >= 10)
				{
					currentFrame = 0;
					setState(NORMAL);
					setVisible(false);

					if(isAct)
					{
						//GUIManager::getInstance().guiLineOld.onFinish();
					}
					return;
				}
				frame = 8 + currentFrame;
			}
			
			break;
		case SMALL:
			break;
		case BIGGER:
			{
				if(currentFrame == 5)
				{
					setState(NORMAL);
					return;
				}
				frame = 22 - currentFrame;
			}
			
			break;
		default:
			return;
			break;
		}
		string s = nameImage  + GameUtility::toString(frame) +".png";
		GameImage::setImage(s.c_str(), true);
	}
}

void BallAnimation::setState( BallState _state )
{
	state = _state;
	currentFrame = 0;
	switch (state)
	{
	case JUMP:
		GameImage::setImage((nameImage + "1.png").c_str(), true);
		frameTime = 0.08f;
		break;
	case NORMAL:
		GameImage::setImage((nameImage + "1.png").c_str(), true);
		break;
	case DISAPPEAR:
		GameImage::setImage((nameImage + "8.png").c_str(), true);
		frameTime = 0.07f;
		break;
	case SMALL:
		GameImage::setImage((nameImage + "21.png").c_str(), true);
		
		break;

	case BIGGER:
		GameImage::setImage((nameImage + "22.png").c_str(), true);
		frameTime = 0.03f;
		break;
	default:
		break;
	}
}

void BallAnimation::setImage( const char* nameImg )
{
// 	if(strcmp(nameImg, nameImage.c_str()) == 0)
// 	{
// 
// 	}
// 	else
// 	{
		string s(nameImg);
		nameImage = s;
		GameImage::setImage((s + "1.png").c_str(), true);
		
//	}
	
}


void BallAnimation::effectEndGame(float delay)
{
	runAction(CCSequence::create(
		CCDelayTime::create(delay),
		CCCallFunc::create(this, callfunc_selector(BallAnimation::callbackEnd)),
		NULL
	));
}

void BallAnimation::callbackEnd()
{
	setState(DISAPPEAR);
}

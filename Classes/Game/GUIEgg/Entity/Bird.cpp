#include "Bird.h"
#include "Game/Data/GlobalData.h"
#include "math.h"
#include "Game/Utility/GameUtility.h"
#include "Game/GUIManager.h"
#include "Game/Data/GlobalData.h"


Bird::Bird(void)
{
	GameImage("egg/fly_1.png");
	countTime = 0;
	frameTime = 0.04f;
	currentFrame = 0;
	setImage("egg/fly_1.png");
	//act(0);
}


Bird::~Bird(void)
{
}

void Bird::setDegree( double degree )
{
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();
	if (degree > 0) {
		setScaleX(1);
	} else {
		setScaleX(-1);
	}
	this->degree = degree;

	double radian = degree / 180 * 3.14;

	if (countAppear == 0) {
		SPEED_BIRD = size.width * 0.0073f;
	} else if (countAppear == 1) {
		SPEED_BIRD = size.width * 0.0096f;
	} else if (countAppear == 2) {
		SPEED_BIRD = size.width * 0.0119f;
	} else if (countAppear == 3) {
		SPEED_BIRD = size.width * 0.0132f;
	}
	else{
		SPEED_BIRD = size.width * 0.0132f + size.width * 0.002 * (countAppear - 3);
	}


	vx = (float) (SPEED_BIRD * sin(radian));
	vy = (float) (SPEED_BIRD * cos(radian));
}

void Bird::updatePosition(float delta) {
	countTime = countTime + delta;
	if (countTime >= frameTime)
	{
		countTime = 0;
		currentFrame++;
		if (currentFrame > 15)
		{
			currentFrame = 0;
		}
	}
	if (currentFrame < 0)
		currentFrame = 0;
	setImage(("egg/fly_" + GameUtility::toString(currentFrame + 1) + ".png").c_str());

	setPositionX(getPositionX() + vx);
	setPositionY(getPositionY() + vy);

}

void Bird::checkVisible() {
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();
	if (getPositionY() > size.height) {
		setVisible(false);
		if (GUIManager::getInstance().guiEgg.genBall->isVisible()) {
			// them bong moi
			countAppear = 0;
			GUIManager::getInstance().guiEgg.addNewBall();
		}
	}
	else {
		if (getPositionX() <= START_X
			|| getPositionX() >= size.width - START_X - fabs(getRealWidth()) * 0.5f) {
			// dao chieu bay cua chim
			setDegree(-degree);
		}
	}
}

void Bird::act( float delta )
{
	if(isVisible())
	{
		this->updatePosition(delta);
		this->checkVisible();
	}
}

void Bird::newGame()
{
	setVisible(false);
	countAppear = 0;
}



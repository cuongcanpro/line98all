#include "Ball.h"
#include "Game/Utility/GameUtility.h"
#include "Game/Data/GlobalData.h"
#include "Game/GUIManager.h"


Ball::Ball(void)
{
	idRow = 0;
	bonusImage = NULL;

	setId(1);
	setWidth(WIDTH_BALL_EGG);
	setHeight(WIDTH_BALL_EGG);
	rScaleX = getScaleX();
	rScaleY = getScaleY();

	
	
}

Ball::Ball( int _idBall, int _idRow, int _idColumn, int _typeRow ) : GameImage()
{
	bonusImage = NULL;
	setId(_idBall);
	setWidth(WIDTH_BALL_EGG);
	setHeight(WIDTH_BALL_EGG);
	idBall = _idBall;
	idRow = _idRow;
	idColumn = _idColumn;
	typeRow = _typeRow;
	isVibrate = false;
	getImg()->setAnchorPoint(ccp(0, 0));
	if (_typeRow == EIGHT_ROW)
		setPosition(WIDTH_BALL_EGG * (0.5f + idColumn), idRow * HEIGH_BALL_EGG);
	else
		setPosition(WIDTH_BALL_EGG * idColumn, idRow * HEIGH_BALL_EGG);

	rootX = getPositionX();
	rootY = getPositionY();
	rScaleX = getScaleX();
	rScaleY = getScaleY();

}


Ball::~Ball(void)
{
}

void Ball::removeBall()
{
	setVisible(false);
	cleanup();
	int idRow, idColumn;

	idRow = this->idRow;
	idColumn = this->idColumn - 1;
	checkRemoveNearBall(idRow, idColumn);

	idRow = this->idRow;
	idColumn = this->idColumn + 1;
	checkRemoveNearBall(idRow, idColumn);

	idRow = this->idRow - 1;
	idColumn = this->idColumn;
	checkRemoveNearBall(idRow, idColumn);

	idRow = this->idRow + 1;
	idColumn = this->idColumn;
	checkRemoveNearBall(idRow, idColumn);

	if (typeRow == EIGHT_ROW) {
		Ball ballAdd;
		// se co 6 bong tiem can voi bong nay, o hang 8 thi la

		idRow = this->idRow - 1;
		idColumn = this->idColumn + 1;
		checkRemoveNearBall(idRow, idColumn);

		idRow = this->idRow + 1;
		idColumn = this->idColumn + 1;
		checkRemoveNearBall(idRow, idColumn);
	} else {
		// se co 6 bong tiem can voi bong nay, o hang 8 thi la
		idRow = this->idRow - 1;
		idColumn = this->idColumn - 1;
		checkRemoveNearBall(idRow, idColumn);

		idRow = this->idRow + 1;
		idColumn = this->idColumn - 1;
		checkRemoveNearBall(idRow, idColumn);
	}
}

bool Ball::isConnect()
{
	
		if (idRow == GUIManager::getInstance().guiEgg.arrayRow.size() - 1)
			return true;
	

	isCheckConnect = true;
	int idRow, idColumn;

	idRow = this->idRow - 1;
	idColumn = this->idColumn;
	if (checkIsConnectNearBall(idRow, idColumn))
		return true;

	if (typeRow == EIGHT_ROW) {
		// se co 6 bong tiem can voi bong nay, o hang 8 thi la

		idRow = this->idRow - 1;
		idColumn = this->idColumn + 1;
		if (checkIsConnectNearBall(idRow, idColumn))
			return true;

		idRow = this->idRow + 1;
		idColumn = this->idColumn + 1;
		if (checkIsConnectNearBall(idRow, idColumn))
			return true;
	} else {
		// se co 6 bong tiem can voi bong nay, o hang 8 thi la
		idRow = this->idRow - 1;
		idColumn = this->idColumn - 1;
		if (checkIsConnectNearBall(idRow, idColumn))
			return true;

		idRow = this->idRow + 1;
		idColumn = this->idColumn - 1;
		if (checkIsConnectNearBall(idRow, idColumn))
			return true;
	}

	idRow = this->idRow;
	idColumn = this->idColumn - 1;
	if (checkIsConnectNearBall(idRow, idColumn))
		return true;

	idRow = this->idRow;
	idColumn = this->idColumn + 1;
	if (checkIsConnectNearBall(idRow, idColumn))
		return true;



	idRow = this->idRow + 1;
	idColumn = this->idColumn;
	if (checkIsConnectNearBall(idRow, idColumn))
		return true;


	return false;
}

void Ball::copy( Ball* ball )
{
	typeRow = ball->typeRow;
	idBall = ball->idBall;
	idColumn = ball->idColumn;
	// ball->idRow = idRow;
	setVisible(ball->isVisible());
	setPositionX(ball->rootX);
	//	setPositionY(ball->rootY);
	// setPositionY(ball->getPositionY());
	setId(ball->idBall);
	if(ball->isBonus())
	{
		setIdBonus(ball->idBonus);
		bonusImage->setVisible(true);
	}
	rootX = getPositionX();
	setPositionY(rootY);
	ball->cleanup();
	ball->countVibrate = 0;

	isVibrate = ball->isVibrate;
	countVibrate = ball->countVibrate;
	if(isVibrate)
	{
		runActionVibrate();
	}
}

void Ball::renew( int _typeRow )
{
	idBall = (int) (GameUtility::getRandom() * NUM_BALL);
	setId(idBall);
	
	setVisible(true);
	typeRow = _typeRow;

	if (typeRow == EIGHT_ROW) {
		setPositionX(WIDTH_BALL_EGG * (0.5f + idColumn));
	} else
		setPositionX(WIDTH_BALL_EGG * idColumn);
	rootX = getPositionX();
	rootY = getPositionY();
	isVibrate = false;
	countVibrate = 0;
	cleanup();
}

void Ball::checkRemoveNearBall( int idRow, int idColumn )
{
	
		
		Ball* ballAdd = GUIManager::getInstance().guiEgg.getBall(idRow, idColumn);
		if (ballAdd != NULL && ballAdd->isVisible()) {
			if (ballAdd->idBall == idBall) {
				ballAdd->removeBall();
			} else {
				GUIManager::getInstance().guiEgg.resetCheckConnect();
				if (!ballAdd->isConnect()) {
					ballAdd->removeBall();
				}
			}
		}
	
}

bool Ball::checkIsConnectNearBall( int idRow, int idColumn )
{

		
		Ball* ballAdd = GUIManager::getInstance().guiEgg.getBall(idRow, idColumn);
		if (ballAdd != NULL && ballAdd->isVisible()) {
			if (ballAdd->isCheckConnect)
				return false;
			else
				return ballAdd->isConnect();
		}
		return false;
	
}

void Ball::newRow( int typeRow2 )
{
	setVisible(false);
	typeRow = typeRow2;

	if (typeRow == EIGHT_ROW)
		setPosition(WIDTH_BALL_EGG * (0.5f + idColumn), idRow
		* HEIGH_BALL_EGG);
	else
		setPosition(WIDTH_BALL_EGG * idColumn, idRow
		* HEIGH_BALL_EGG);
	rootX = getPositionX();
	rootY = getPositionY();
}

bool Ball::checkEatBall()
{
	
		GUIManager::getInstance().guiEgg.resetCheckConnect();
		GUIManager::getInstance().guiEgg.arrayEatBall.clear();
	
	int count = countNearBall();
	if (count >= 3)
		return true;
	else
		return false;
}

int Ball::countNearBall()
{
	if (isCheckConnect)
		return 0;
	
		GUIManager::getInstance().guiEgg.arrayEatBall.push_back(this);
	

	isCheckConnect = true;
	int count = 0;
	int idRow, idColumn;
	idRow = this->idRow;
	idColumn = this->idColumn - 1;
	count = count + getCountNearBall(idRow, idColumn);

	idRow = this->idRow;
	idColumn = this->idColumn + 1;
	count = count + getCountNearBall(idRow, idColumn);

	idRow = this->idRow - 1;
	idColumn = this->idColumn;
	count = count + getCountNearBall(idRow, idColumn);

	idRow = this->idRow + 1;
	idColumn = this->idColumn;
	count = count + getCountNearBall(idRow, idColumn);

	if (typeRow == EIGHT_ROW) {
		// se co 6 bong tiem can voi bong nay, o hang 8 thi la

		idRow = this->idRow - 1;
		idColumn = this->idColumn + 1;
		count = count + getCountNearBall(idRow, idColumn);

		idRow = this->idRow + 1;
		idColumn = this->idColumn + 1;
		count = count + getCountNearBall(idRow, idColumn);
	} else {
		// se co 6 bong tiem can voi bong nay, o hang 8 thi la
		idRow = this->idRow - 1;
		idColumn = this->idColumn - 1;
		count = count + getCountNearBall(idRow, idColumn);

		idRow = this->idRow + 1;
		idColumn = this->idColumn - 1;
		count = count + getCountNearBall(idRow, idColumn);
	}

	return 1 + count;
}

int Ball::getCountNearBall( int idRow, int idColumn )
{
	
		Ball* ballAdd = GUIManager::getInstance().guiEgg.getBall(idRow, idColumn);
		if (ballAdd != NULL && ballAdd->isVisible() && ballAdd->idBall == idBall) {
			return ballAdd->countNearBall();
		}
		return 0;
	
}

void Ball::runActionVibrate()
{
	if(countVibrate > 70)
	{
		isVibrate = false;
		countVibrate = 0;
		setPositionX(rootX);
		setPositionY(rootY);
		cleanup();
		return;
	}
	countVibrate++;
	int signal = (GameUtility::getRandom() > 0.5f ? 1 : -1);
	float goalX = (float) (GameUtility::getRandom() * WIDTH_BALL_EGG * 0.1f * signal) + rootX;
	signal = (GameUtility::getRandom() > 0.5f ? 1 : -1);
	float goalY = (float) (GameUtility::getRandom() * WIDTH_BALL_EGG * 0.1f * signal) + rootY;
	isVibrate = true;
	
	
	runAction(CCSequence::create(CCMoveTo::create(0.05f, ccp(goalX, goalY)), CCCallFunc::create(this, callfunc_selector(Ball::runActionVibrate)), NULL));
}

void Ball::setId( int i )
{
	idBall = i;
	setImage(("egg/bubble_" + GameUtility::toString(idBall + 1) + ".png").c_str());
}

void Ball::setImage( const char* url )
{
	GameImage::setImage(url);
	getImg()->setAnchorPoint(ccp(0, 0));

	if(bonusImage != NULL)
		addChild(bonusImage);
}

void Ball::setIdBonus( int id )
{
	if(id >= 0)
	{
		idBonus = id;
		if(bonusImage == NULL)
		{
			bonusImage = new GameImage(("egg/x_" + GameUtility::toString(id + 2) + ".png").c_str());
			bonusImage->setWidth(WIDTH_BALL_EGG * 0.75f);
			bonusImage->setHeight(WIDTH_BALL_EGG * 0.75f);
			addChild(bonusImage);
			bonusImage->setPos(getWidth() * 0.5f, getWidth() * 0.5f);
		}
		else
			bonusImage->setImage(("egg/x_" + GameUtility::toString(id + 2) + ".png").c_str());
		bonusImage->setVisible(true);
	}
	else
	{
		if(bonusImage != NULL)
		{
			bonusImage->setVisible(false);
		}
	}
}

void Ball::moveUp(int countUp)
{
	stopAllActions();
	setIdRow(idRow + countUp);
	//setPositionY(getPositionY() + HEIGH_BALL_EGG * countUp);
}

void Ball::setIdRow(int idRow)
{
	this->idRow = idRow;
	setPositionY(idRow * HEIGH_BALL_EGG);
	rootY = getPositionY();
}

bool Ball::isBonus()
{
	if(bonusImage == NULL)
		return false;
	return bonusImage->isVisible();
}



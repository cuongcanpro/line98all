#include "../../Engine/Utility/ScreenUtils.h"
#include "../../Engine/GlobalVar.h"
#include "../../Engine/Utility/LocalizedString.h"
#include "../GUIManager.h"
#include "../Utility/JNIUtils.h"
#include "../Data/GlobalData.h"
#include "../Utility/GameUtility.h"
#include "Game/Data/GlobalData.h"
#include "Engine/Utility/CStringUtils.h"
#include "../Utility/GameSound.h"
#include "Entity/GroupScoreEgg.h"
#include "Engine/GUI/ParticleEffect.h"

#define BTN_BACK_ID 1
#define BTN_SOUND_ID 2
#define BTN_UNDO_ID 3


GUIEgg::GUIEgg(void) : BaseGUI()
{
	BaseGUI();

	setKeypadEnabled(true);
}


GUIEgg::~GUIEgg(void)
{
}

void endGameLoading()
{
	GameClient::endGame();
}


void GUIEgg::initGUI(){

	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();
	//runAction(CCSequence::create(CCDelayTime::create(0.1f), CCCallFunc::create(this, callfunc_selector(GUIEgg::callBackSplash)), NULL));
	callBackSplash();
}

void GUIEgg::onBackKey(){
	JNIUtils::showAdsBanner(1);
	if (GUIManager::getInstance().isCallBackPress == false && GUIManager::getInstance().getLastGui() == this)
	{
		GUIManager::getInstance().removeAllGui();
	
			GUIManager::getInstance().showGui(&GUIManager::getInstance().guiMinigames);
		GUIManager::getInstance().isCallBackPress = true;
	}
}



void GUIEgg::update()
{
	
}
void okEndGame()
{
	game->endGame();
}

void GUIEgg::onButtonRelease(int buttonID, CCTouch* touch)
{
	switch (buttonID)
	{
            GameSound::playClick();
	case BTN_BACK_ID:
		{
			onBackKey();
		}
		
		break;
	case BTN_SOUND_ID:
		{
	//	this->groupBall->setScale(0.3);
			game->music = !game->music;
			if(game->music)
			{
				btnSound->normalImage->setImage("btnSoundOn.png");
			}
			else
			{
				btnSound->normalImage->setImage("btnSoundOff.png");
			}

			CCUserDefault::sharedUserDefault()->setBoolForKey("music", game->music);
			CCUserDefault::sharedUserDefault()->flush();
		
		}
		break;
	case BTN_UNDO_ID:
		{
			
		}
		break;
	default:
		break;
	}
}

void makeNewGame()
{
	//GUIManager::getInstance().guiWaiting.showAds(false);
    game->showAdsFull();
	GUIManager::getInstance().guiEgg.newGame();
}

void makeBack()
{
	game->showAdsForOldUser();
	GUIManager::getInstance().guiEgg.onBackKey();
}
void GUIEgg::callBackSplash()
{
	BaseGUI::initGUI();
	isUpdate = true;
	
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();

	GameImage* background = addImage("egg/jungleback.jpg");
	background->setAnchorPoint(ccp(0, 0));
	background->setWidth(size.width);
	background->setHeight(size.height);
	background->setPos(size.width / 2, size.height / 2);

	GameImage* black = addImage("egg/blackLayer.png");
	black->getImg()->setAnchorPoint(ccp(0, 0));
	black->setWidth(size.width);
	black->setHeight(size.height * 0.11);
	// black->setPosition(size.width * 0.5f, size.height);
	black->setVisible(true);
	black->setZOrder(2);

	WIDTH_BALL_EGG = size.width * 0.8f / NINE_ROW;
	START_X_EGG = size.width * 0.1f;
	START_Y_EGG = size.height * 0.5f;
	HEIGH_BALL_EGG = WIDTH_BALL_EGG * 0.85f;
	WIDTH_GATE = WIDTH_BALL_EGG * 0.9f;
	LIMIT_X = START_X_EGG + WIDTH_BALL_EGG * NINE_ROW;

	arrow = new Arrow();
	arrow->setPos(200, 100);
	arrow->setHeightArrow(200);
	arrow->setRotateArrow(30);

	bar = addImage("egg/ceiling.png");
	bar->getImg()->setAnchorPoint(ccp(0, 0));
	bar->setWidth(size.width);
	bar->setPosition(size.width * 0.5f, size.height);
	bar->setVisible(true);

	int NUM_ROW = (int) (size.height * 0.73f / HEIGH_BALL_EGG);

	groupBall = new CCNode();
	addChild(groupBall);
	groupBall->setAnchorPoint(ccp(0, 0));
	groupBall->setPosition(START_X_EGG, START_Y_EGG);

	cannon1 = addImage("egg/cannon1.png");
	cannon1->getImg()->setAnchorPoint(ccp(0, 0));
	cannon1->setHeight(WIDTH_BALL_EGG * 2.3f / cannon1->getRealWidth() * cannon1->getRealHeight());
	cannon1->setWidth(WIDTH_BALL_EGG * 2.3f);
	if (size.width / size.height < 320.0f / 480.0f) {
		cannon1->setPositionY(size.height * 0.12);
		black->setVisible(true);
		JNIUtils::showAdsBanner(1);
	}
	else {
		black->setVisible(false);
		JNIUtils::showAdsBanner(0);
	}

	GameImage* cannon2 = addImage("egg/cannon2.png");
	cannon2->getImg()->setAnchorPoint(ccp(0, 0));
	cannon2->setHeight(WIDTH_BALL_EGG * 2.3f / cannon2->getRealWidth() * cannon2->getRealHeight());
	cannon2->setWidth(WIDTH_BALL_EGG * 2.3f);
	cannon2->setPosition(size.width * 0.5f - cannon2->getRealWidth() * 0.5f, 0);
	if (size.width / size.height < 320.0f / 480.0f) {
		cannon2->setPositionY(size.height * 0.12);
		black->setVisible(true);
	}
	else {
		black->setVisible(false);
	}

	arrow->setPos(size.width * 0.5f, cannon2->getPositionY() + cannon2->getRealHeight() * 0.85f);
	arrow->setHeightArrow(size.height * 0.3f);
	arrow->setRotateArrow(0);
	START_BALL_X = size.width * 0.5f - WIDTH_BALL_EGG * 0.5f;
	START_BALL_Y = arrow->y - WIDTH_BALL_EGG * 0.5f;

	speed = WIDTH_BALL_EGG * 0.9f;
	speedY = -1;

	rope = addImage("egg/rop.png");
	rope->setWidth(size.width);
	rope->setAnchorPoint(ccp(0, 0));
	rope->setPosition(size.width * 0.5f, START_BALL_Y + WIDTH_BALL_EGG * 1.5f);

	arrow->addToParent(this);

	moveBall = new Ball();
	addChild(moveBall);
	moveBall->setPosition(START_BALL_X, START_BALL_Y);

	nextBall = new Ball();
	addChild(nextBall);
	nextBall->setPosition(cannon1->getPositionX() + cannon1->getRealWidth() * 0.8f,
		cannon1->getPositionY() + cannon1->getRealHeight() * 0.8f);

	leftWall = addImage("egg/leftwall.png");
	leftWall->getImg()->setAnchorPoint(ccp(0,0));
	leftWall->setHeight(size.height);
	leftWall->setPositionX(START_X_EGG - leftWall->getRealWidth() * 0.7f);

	rightWall = addImage("egg/rightwall.png");
	rightWall->getImg()->setAnchorPoint(ccp(0,0));
	rightWall->setHeight(size.height);
	rightWall->setPosition(LIMIT_X - rightWall->getRealWidth() * 0.3f, 0);

	upWall = addImage("egg/upwall.png");
	upWall->getImg()->setAnchorPoint(ccp(0,0));
	upWall->setWidth(size.width);
	upWall->setPosition(0, size.height - upWall->getRealHeight());
	// arrayRow.at(0]->arrayBall[0].runAction();

	ani = new Bird();
	addChild(ani);
	ani->setVisible(false);

	genBall = new Ball();
	genBall->setWidth(WIDTH_BALL_EGG);
	genBall->setHeight(WIDTH_BALL_EGG);
	addChild(genBall);
	genBall->setVisible(false);

	labelScore = LabelBM::create("Score: 0", FONT_BOLD_TYPE);
    labelScore->setScale(0.9f);
	labelScore->setAnchorPoint(ccp(0, 0));
	addChild(labelScore);
	labelScore->setPosition(size.width * 0.02f, upWall->getPositionY() + upWall->getRealHeight() * 0.1f);

	labelHighscore = LabelBM::create("Highscore: 0", FONT_BOLD_TYPE);
    labelHighscore->setScale(0.9f);
	labelHighscore->setAnchorPoint(ccp(0, 0));
	addChild(labelHighscore);
	labelHighscore->setPosition(size.width * 0.3f, labelScore->getPositionY());

	GameImage* progress1 = new GameImage("egg/progress.png");
	bgProgress = addImage("egg/bgProgress.png");
	bgProgress->setAnchorPoint(ccp(0, 1));
	bgProgress->addChild(progress1);
	progress1->setPositionX(bgProgress->getWidth() * 0.01f);
	bgProgress->setPos(size.width * 0.93f, size.height * 0.3f);
	progress = CCProgressTimer::create(CCSprite::create("480_800/egg/bgProgress.png"));
	progress->setType(kCCProgressTimerTypeBar);
	progress->setMidpoint(ccp(0,1));
	progress->setBarChangeRate(ccp(0, 1));
	bgProgress->addChild(progress);

	bonusEffect = new BonusEffect();
	addChild(bonusEffect);
	bonusEffect->maxTime = 4;
	bonusEffect->radius = size.width * 0.12f;
	bonusEffect->rootX = LIMIT_X;
	bonusEffect->rootY = size.height * 0.2f;
	//bonusEffect->setVisible(false);

	bgRow = addImage("egg/bgDark.png");
	bgRow->setAnchorPoint(ccp(0, 0));
	bgRow->setHeight(upWall->getRealHeight() * 0.4f);
	bgRow->setWidth(size.width * 0.2f);
	bgRow->setPosition(size.width * 0.15f, upWall->getPositionY() + upWall->getRealHeight() * 0.5f);

	labelRow = LabelBM::create("10 ROWS", FONT_BOLD_TYPE);
	labelRow->setAnchorPoint(ccp(0, 0.5f));
	addChild(labelRow);
	labelRow->setPosition(bgRow->getPositionX() - bgRow->getRealWidth() * 0.45f, bgRow->getPositionY());

	btnBack = addButton(1, "egg/btnBack.png");
	btnBack->setPosition(size.width - btnBack->getWidth() * 0.7f, upWall->getPositionY() + upWall->getRealHeight() * 0.1f + btnBack->getHeight() * 0.5f);

	btnSound = addButton(2, "egg/btnSoundOff.png");
	btnSound->setPosition(btnBack->getPositionX() - btnSound->getWidth() * 1.2f, btnBack->getPositionY());

	if(game->music)
	{
		btnSound->normalImage->setImage("egg/btnSoundOn.png");
	}
	else
	{
		btnSound->normalImage->setImage("egg/btnSoundOff.png");
	}
	initDragonbone();


	//btnPause = addButton(3, "btnPause.png");
	//btnPause->setPosition(btnSound->getPositionX() - btnPause->getWidth() * 1.2f, btnBack->getPositionY());
}



Ball* GUIEgg::getBall(int idRow, int idColumn) {
	if (idRow < 0 || idColumn < 0)
		return NULL;
	if (idRow >= arrayRow.size())
		return NULL;
	RowBall* row = arrayRow.at(idRow);
	if (idColumn > row->typeRow - 1)
		return NULL;
	Ball* ball = arrayRow.at(idRow)->getBall(idColumn);
	return ball;
}

void GUIEgg::act(float delta) {
	// TODO Auto-generated method stub
	float rateSpeed = delta * 60 * 2.0;
	float speed = 42;
	if (isUpdate != true)
		return;
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();
	if (state == GameStateEgg::PLAY_EGG) {
		START_Y_EGG = groupBall->getPositionY();
		if (gameType == ENDLESS) {
			// di chuyen chim cong qua bong moi
			genBall->setPosition(ani->getPositionX(), ani->getPositionY() - ani->getRealHeight() * 0.75f);
			ani->act(delta);

			// random ra qua bong rung
			countTimeVibrate = countTimeVibrate + delta;
			Ball* b;
			if (countTimeVibrate > 25) {
				countTimeVibrate = 0;
				int r, c;
				do {
					r = (int)(GameUtility::getRandom() * 8);
					c = (int)(GameUtility::getRandom() * 8);
					b = arrayRow.at(r)->arrayBall[c];
				} while (!b->isVisible() || b->isBonus());
				b->countVibrate = 0;
				b->runActionVibrate();
			}

			// di chuyen group ball xuong
			if (groupBall->getContentSize().height > 0.9f * size.height) {
				groupBall->setPositionY(0.9f * size.height);
				START_Y_EGG = 0.9f * size.height;
			}
			if (bonusEffect->isVisible() && bonusEffect->idBonus == 4) {
				groupBall->setPositionY(groupBall->getPositionY() + speed * 0.03f * rateSpeed);
				START_Y_EGG = START_Y_EGG + speed * 0.03f * rateSpeed;
			}
			else if (increaseSpeed) {
				float dY = ((groupBall->getPositionY() - START_BALL_Y) - size.height * 0.3) * 0.025;
				groupBall->setPositionY(groupBall->getPositionY() - dY * rateSpeed);
				START_Y_EGG = START_Y_EGG - dY * rateSpeed;
				if (dY <= 2) {
					increaseSpeed = false;
				}
			}
			else {
				float rate = 0.0033f;
				rate = rate - 0.0015f * (NUM_BALL - 3) / 5.0f;

				groupBall->setPositionY(groupBall->getPositionY() - speed * rate * rateSpeed);
				START_Y_EGG = START_Y_EGG - speed * rate * rateSpeed;
			}

			// check xem co trung qua bong duoc chim cong
			if (speedY > 0 && genBall->isVisible()) {
				// tinh khoang cach bong bay den qua bong duoc gen
				double distance = (genBall->getPositionX() - moveBall->getPositionX())
					* (genBall->getPositionX() - moveBall->getPositionX());
				distance = distance + (genBall->getPositionY() - moveBall->getPositionY())
					* (genBall->getPositionY() - moveBall->getPositionY());
				distance = sqrt(distance);

				if (distance <= WIDTH_BALL_EGG) {
					// vo bong
					genBall->setVisible(false);
					GameSound::playWhirleyHit();
					showParticle(genBall->getPositionX(), genBall->getPositionY(), NUM_BALL);
					moveBall->setVisible(false);
					speedY = -1;
					score = score + 50;
					updateScore();

                    GroupScoreEgg *group = getGroupScore();
					group->setVisible(true);
					group->createBonusScore(50);
					group->setPosition(moveBall->getPositionX() + moveBall->getRealWidth() * 0.5f, moveBall->getPositionY() + moveBall->getRealHeight() * 0.5f);
					group->runAction(Sequence::create(EaseBackOut::create(MoveTo::create(0.7f, Vec2(group->getPositionX(), group->getPositionY() + size.height * 0.1f)))
						, FadeOut::create(0.5), Hide::create(), NULL));

					// Todo: Effect Later
					/*effectBreakBall->stopAllActions();
					effectBreakBall->setVisible(true);
					effectBreakBall->getAnimation()->gotoAndPlay("run", -1, -1, -1);
					effectBreakBall->setPosition(genBall->getPosition());*/
					effectBreakBall->stop();
					effectBreakBall->setVisible(true);
					effectBreakBall->play(0);
					effectBreakBall->setPosition(genBall->getPosition());
					JNIUtils::vibrate(50);
				}

			}

			if (groupBall->getPositionY() - START_BALL_Y > size.height * 0.5f) {
				increaseSpeed = true;
			}

			if (bonusEffect->isVisible())
			{
				bonusEffect->act(delta);
			}
		}
		else if (gameType == TIME) {
			if (arrayRow.size() > 0) {
				bar->setPosition(0, groupBall->getPositionY() + arrayRow.at(arrayRow.size() - 1)->arrayBall[0]->rootY
					+ arrayRow.at(arrayRow.size() - 1)->arrayBall[0]->getRealHeight());
				countTime = countTime + delta;
				updateTime();
			}

			float d = fabs(((double)(rope->getPositionY() + rope->getRealHeight() - groupBall->getPositionY())));
			if (d > HEIGH_BALL_EGG * 0.1f) {
				if (groupBall->getPositionY() > rope->getPositionY() + rope->getRealHeight())
					groupBall->setPositionY(groupBall->getPositionY() - speed * 0.05f * rateSpeed);
				else
					groupBall->setPositionY(groupBall->getPositionY() + speed * 0.05f * rateSpeed);
				START_Y_EGG = groupBall->getPositionY();
			}
		}
		else {
			if (arrayRow.size() > 0) {
				bar->setPosition(0, groupBall->getPositionY() + arrayRow.at(arrayRow.size() - 1)->arrayBall[0]->rootY
					+ arrayRow.at(arrayRow.size() - 1)->arrayBall[0]->getRealHeight());
			}
			if (distanceY != 0) {
				countDistance = countDistance + speed * 0.05f * rateSpeed;
				if (countDistance >= distanceY) {
					distanceY = 0;
				}
				else {
					groupBall->setPositionY(groupBall->getPositionY() - speed * 0.05f * rateSpeed);
					START_Y_EGG = groupBall->getPositionY();
				}
			}
		}

		if (speedY > 0) {
			oldX = moveBall->getPositionX() + moveBall->getRealWidth() * 0.5f;
			oldY = moveBall->getPositionY() + moveBall->getRealWidth() * 0.5f;
			if (moveBall->getPositionY() >= START_Y_EGG)
				oldRow = (int)((moveBall->getPositionY() + moveBall->getRealWidth() * 0.5f - START_Y_EGG) / HEIGH_BALL_EGG);
			else
				oldRow = (int)(floor((moveBall->getPositionY() + moveBall->getRealWidth() * 0.5f - START_Y_EGG) / HEIGH_BALL_EGG));
			int size1 = arrayRow.size();
			if (oldRow >= size1)
				oldRow = arrayRow.size() - 1;
			if (oldRow < -1) {
				oldColumn = (int)((moveBall->getPositionX() + moveBall->getRealWidth()
					* 0.5f - START_X_EGG) / WIDTH_BALL_EGG);
				if (arrayRow.at(0)->typeRow == EIGHT_ROW) {
					if (oldColumn >= NINE_ROW)
						oldColumn = NINE_ROW - 1;
				}
				else {
					if (oldColumn >= NINE_ROW - 1)
						oldColumn = NINE_ROW - 2;
				}
			}
			else if (oldRow != -1) {
				if (arrayRow.at(oldRow)->typeRow == EIGHT_ROW) {
					oldColumn = (int)((moveBall->getPositionX() + moveBall->getRealWidth() * 0.5f - WIDTH_BALL_EGG * 0.5f - START_X_EGG) / WIDTH_BALL_EGG);
					if (oldColumn == NINE_ROW - 1)
						oldColumn = NINE_ROW - 2;
				}
				else {
					oldColumn = (int)((moveBall->getPositionX() + moveBall->getRealWidth() * 0.5f - START_X_EGG) / WIDTH_BALL_EGG);
					if (oldColumn == NINE_ROW)
						oldColumn = NINE_ROW - 1;
				}
			}
			else {
				if (arrayRow.at(0)->typeRow == EIGHT_ROW) {
					oldColumn = (int)((moveBall->getPositionX() + moveBall->getRealWidth() * 0.5f - START_X_EGG) / WIDTH_BALL_EGG);
					if (oldColumn >= NINE_ROW)
						oldColumn = NINE_ROW - 1;
				}
				else {
					oldColumn = (int)((moveBall->getPositionX() + moveBall->getRealWidth() * 0.5f - WIDTH_BALL_EGG * 0.5f - START_X_EGG) / WIDTH_BALL_EGG);
					if (oldColumn >= NINE_ROW - 1)
						oldColumn = NINE_ROW - 2;
				}
			}
			moveBall->setPositionX(moveBall->getPositionX() + speedX);
			moveBall->setPositionY(moveBall->getPositionY() + speedY);

			if (moveBall->getPositionY() > size.height * 1.2f) {
				moveBall->setVisible(false);
				speedY = -1;
				if (delay)
					delayReturn();
				delay = false;
				return;
			}

			getNearBall(moveBall->getPositionX() + moveBall->getRealWidth() * 0.5f, moveBall->getPositionY() + moveBall->getRealHeight() * 0.5f);
			if (speedX > 0) {
				if ((LIMIT_X - moveBall->getPositionX()) <= WIDTH_BALL_EGG) {
					speedX = -speedX;
				}
			}
			else {
				if ((moveBall->getPositionX() - START_X_EGG) <= 0) {
					speedX = -speedX;
				}
			}
		}

		if (checkEndGame()) {
			if (countVisible == 0) {
				countVisible = 1;
				GameSound::playWarn();
			}
			countTimeVisible = countTimeVisible + delta;
			if (countTimeVisible > 0.2f) {
				countTimeVisible = 0;
				for (int i = 0; i < NINE_ROW; i++) {
					if (arrayRow.at(0)->arrayBall[i]->getImg()->getOpacity() >= 255)
						arrayRow.at(0)->arrayBall[i]->setOpacity(0);
					else
						arrayRow.at(0)->arrayBall[i]->setOpacity(255);
				}
				countVisible++;
				if (countVisible >= 8) {
					endGame();
				}
			}
		}
		else {
			countVisible = 0;
			if (arrayRow.size() == 0)
				return;
			for (int i = 0; i < NINE_ROW; i++) {
				arrayRow.at(0)->arrayBall[i]->setOpacity(255);
			}
		}

	}
	else {

	}
	for (int i = 0; i < arrayImageEffect.size(); i++) {
		if (arrayImageEffect.at(i)->isVisible()) {
			arrayImageEffect.at(i)->updateCoin(game->deltaTime);
		}
	}
	manager->update(delta);
}

bool GUIEgg::onTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();
	if(pTouch->getLocation().y < size.height * 0.68f)
	{
		if (state == GameStateEgg::WAIT_PLAY_EGG || state == GameStateEgg::PAUSE_EGG) {
			state = GameStateEgg::PLAY_EGG;
			//btnPause->setChecked(false);
		}
		if (state == GameStateEgg::PLAY_EGG)
			moveArrow(pTouch->getLocation().x, pTouch->getLocation().y);
	}
	else
	{
		if (BaseGUI::onTouchBegan(pTouch, pEvent))
			return true;
	}
	return BaseGUI::onTouchBegan(pTouch, pEvent);
}

void GUIEgg::onTouchMoved(CCTouch*touch, CCEvent* event)
{
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();
	if(touch->getLocation().y < size.height * 0.8f)
	{
		
		if (state == GameStateEgg::PLAY_EGG)
			moveArrow(touch->getLocation().x, touch->getLocation().y);
	}
	else
	{
		BaseGUI::onTouchMoved(touch, event);
	}
}

void GUIEgg::moveArrow(int screenX, int screenY) {

	float tag = getTag(screenX, screenY);
	arrow->setRotateArrow(tag);
}

float GUIEgg::getTag(int screenX, int screenY) {
	//int convertY = (int) (getRealHeight() - screenY);
	int convertY = screenY;
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();
	float distance = (float) (sqrt((convertY - arrow->y) * (convertY - arrow->y)
		+ (screenX - arrow->x - arrow->getWidth() * 0.5f) * (screenX - arrow->x - arrow->getWidth() * 0.5f)));
	distance = distance - arrow->getArrowHeight();
	arrow->setHeightArrow(distance + size.height * 0.2f);

	float tagValue = (screenX - arrow->x - arrow->getWidth() * 0.5f) / (convertY - arrow->y);
	float tag = (float) (atan(tagValue) / 3.14f * 180);
	return tag;
}

void GUIEgg::onTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();
	if (pTouch->getLocation().y < size.height * 0.8f)
	{
		if (isMoving)
		{
			BaseGUI::onTouchEnded(pTouch, pEvent);
			return;
		}
		moveArrow(pTouch->getLocation().x, pTouch->getLocation().y);
		speedX = (float)(speed * sin(arrow->getRadian()));
		speedY = (float)(speed * cos(arrow->getRadian()));
		nextBall->setVisible(true);
		isMoving = true;
		ccBezierConfig c;
		c.controlPoint_1 = ccp(nextBall->getPositionX(), nextBall->getPositionY());
		c.controlPoint_2 = ccp(nextBall->getPositionX() + 40 - GameUtility::getRandom() * 20, nextBall->getPositionY() + 60 - GameUtility::getRandom() * 20);
		c.endPosition = ccp(START_BALL_X, START_BALL_Y);

		nextBall->runAction(CCSequence::create(CCEaseExponentialOut::create(CCBezierTo::create(0.5f, c))
			, CCCallFunc::create(this, callfunc_selector(GUIEgg::callbackNextBall)), NULL));
		effectShootBall->stopAllActions();
		effectShootBall->getAnimation()->gotoAndPlay("vaoban", 0.3, -1, 1);
		effectShootBall->runAction(CCSequence::create(CCDelayTime::create(0.4), CCShow::create(),
			CCDelayTime::create(1.0), CCHide::create(), NULL));
		effectShoot->stopAllActions();
		effectShoot->setVisible(true);
		effectShoot->getAnimation()->gotoAndPlay("1", -1, -1, 1);
		effectShoot->runAction(CCSequence::create(CCDelayTime::create(0.8), CCHide::create(), NULL));
	}
	else
	{
		BaseGUI::onTouchEnded(pTouch, pEvent);
	}
}

void GUIEgg::delayReturn() {
	moveBall->setVisible(true);
	moveBall->setPosition(START_BALL_X, START_BALL_Y);
	moveBall->setId(nextBall->idBall);
	if (nextBall->isBonus())
	{
		moveBall->setIdBonus(nextBall->idBonus);
	}
	nextBall->setIdBonus(-1);
	int idNextBall = 0;
	if (gameType == ENDLESS) {
		idNextBall = (int)(GameUtility::getRandom() * NUM_BALL);
	}
	else {
		vector<int> arrayId;
		for (int i = 0; i < arrayRow.size(); i++) {
			vector<int> arrayIdBall = arrayRow.at(i)->getArrayId();
			for (int j = 0; j < arrayIdBall.size(); j++) {
				if (std::count(arrayId.begin(), arrayId.end(), arrayIdBall[j]) >= 0) {
					arrayId.push_back(arrayIdBall[j]);
				}
				else {
				}
			}
		}
		if (arrayId.size() == 0)
			idNextBall = 0;
		else {
			idNextBall = (int)(GameUtility::getRandom() * arrayId.size());
			idNextBall = arrayId.at(idNextBall);
		}
	}
	
	nextBall->setId(idNextBall);
	nextBall->setPosition(cannon1->getPositionX() + cannon1->getRealWidth() * 0.8f,
		cannon1->getPositionY() + cannon1->getRealHeight() * 0.8f);
	nextBall->stopAllActions();
	float scale = nextBall->rScaleX;
	nextBall->setScale(0);
	nextBall->runAction(CCEaseBounceOut::create(CCScaleTo::create(0.5, scale)));
	if (nextBonus) {
		makeBonus();
	}
	isMoving = false;
}

// Update lai mang ball sau khi remove bong, day cac hang tren xuong neu
// hang duoi cung khong con bong
void GUIEgg::updateArrayBall() {
	int i;
	for (i = arrayRow.size() - 1; i >= 0; i--) {
		int j;
		for (j = 0; j < arrayRow.at(i)->arrayBall.size(); j++) {
			if (arrayRow.at(i)->arrayBall[j]->isVisible()) {
				break;
			}
		}
		if (j >= arrayRow.at(i)->arrayBall.size())
			break;
	}
	if (i >= 0) {
		if (gameType == ENDLESS) {
			// update lai mang ball

			vector<RowBall*> arrayNew;
			for(int k = 0; k < i + 1; k++)
			{
				RowBall* rowBall = arrayRow.at(0);
				arrayRow.erase(arrayRow.begin());
				arrayNew.push_back(rowBall);
			}
			
			for(int k = 0; k < arrayRow.size(); k++)
				arrayRow.at(k)->moveUp(-i - 1);
			int sizeArray = arrayNew.size();
			while (sizeArray > 0)
			{
				RowBall* rowBall = arrayNew.at(arrayNew.size() - 1);
				arrayNew.pop_back();
				sizeArray = arrayNew.size();
				rowBall->setIdRow(arrayRow.at(arrayRow.size() - 1)->idRow + 1,  NINE_ROW + EIGHT_ROW - arrayRow.at(arrayRow.size() - 1)->typeRow);
				rowBall->setVisibleAll();
                rowBall->renew(rowBall->typeRow);
				arrayRow.push_back(rowBall);
			}
			START_Y_EGG = START_Y_EGG + (i + 1) * HEIGH_BALL_EGG;
			groupBall->setPositionY(START_Y_EGG);
			
// 			for (int k = 0; k + i + 1 < arrayRow.size(); k++) {
// 				arrayRow.at(k)->copy(arrayRow.at(k + i + 1));
// 			}
// 
// 			START_Y_EGG = START_Y_EGG + (i + 1) * HEIGH_BALL_EGG;
// 			groupBall->setPositionY(START_Y_EGG);
// 			int saveTypeRow, typeRow;
// 
// 			// re
// 			int rowAdd = arrayRow.size() - i - 2;
// 			saveTypeRow = typeRow = arrayRow.at(rowAdd)->typeRow;
// 			for (int k = rowAdd + 1; k < arrayRow.size(); k++) {
// 				typeRow = EIGHT_ROW + NINE_ROW - typeRow;
// 				arrayRow.at(k)->renew(typeRow);
// 			}
		} else {
			// update lai mang ball
			for (int k = 0; k + i + 1 < arrayRow.size(); k++) {
				arrayRow.at(k)->copy(arrayRow.at(k + i + 1));
			}

			START_Y_EGG = START_Y_EGG + (i + 1) * HEIGH_BALL_EGG;
			groupBall->setPositionY(START_Y_EGG);
			int saveTypeRow, typeRow;

			// remove het bon dang sau
			for (int k = 0; k < i + 1; k++) {
				for (int j = 0; j < NINE_ROW; j++) {
					arrayRow.at(arrayRow.size() - 1 - k)->arrayBall[j]->removeFromParent();
				}
			}

			for (int k = 0; k < i + 1; k++) {
					arrayRow.pop_back();
			}
		}
	}
}

PointGame* GUIEgg::getPoint(float x, float y) {
	int row = (int) ((y - START_Y_EGG) / HEIGH_BALL_EGG);
	int column;
	if (row < 0)
		return new PointGame(-1, -1);

	RowBall* rowBall = arrayRow.at(row);
	if (rowBall->typeRow == EIGHT_ROW) {
		column = (int) ((x - START_X_EGG - WIDTH_BALL_EGG * 0.5f) / WIDTH_BALL_EGG);
	} else {
		column = (int) ((x - START_X_EGG) / WIDTH_BALL_EGG);
	}
	return new PointGame(column, row);
}

void GUIEgg::resetCheckConnect() {
	for (int i = 0; i < arrayRow.size(); i++) {
		arrayRow.at(i)->resetCheckConnect();
	}
}

// lay nhung bong co the bi gan bong bay vao
void GUIEgg::getNearBall(float x, float y) {
	int row;
	if (y >= START_Y_EGG)
		row = (int) ((y - START_Y_EGG) / HEIGH_BALL_EGG);
	else
		row = (int) (floor((y - START_Y_EGG) / HEIGH_BALL_EGG));
	int column;
	if (row < -1)
		return;
	int size = arrayRow.size();
	if (row >= size)
	{
		int n = arrayRow.size();
		row = arrayRow.size() - 1;
	}
	int idRow;
	int idColumn;
	Ball ballAdd;
	if (row > -1) {

		if (arrayRow.at(row)->typeRow == EIGHT_ROW) {
			column = (int) ((x - WIDTH_BALL_EGG * 0.5f - START_X_EGG) / WIDTH_BALL_EGG);
			if (column >= NINE_ROW - 1)
				column = NINE_ROW - 2;
			if (arrayRow.at(row)->arrayBall[column]->isVisible()) {
				float medX = (oldX + arrayRow.at(row)->arrayBall[column]->getPositionX() + WIDTH_BALL_EGG * 0.5f + START_X_EGG) / 2;
				float medY = (oldY + arrayRow.at(row)->arrayBall[column]->getPositionY() + WIDTH_BALL_EGG * 0.5f + START_Y_EGG) / 2;
				int medRow = (int) ((medY - START_Y_EGG) / HEIGH_BALL_EGG);
				int medColumn;
				if (medRow < 0)
					medRow = 0;
				if (arrayRow.at(medRow)->typeRow == EIGHT_ROW) {
					medColumn = (int) ((medX - START_X_EGG - WIDTH_BALL_EGG * 0.5f) / WIDTH_BALL_EGG);
					if (medColumn == NINE_ROW - 1)
						medColumn = NINE_ROW - 2;
				} else {
					medColumn = (int) ((medX - START_X_EGG) / WIDTH_BALL_EGG);
				}
				CCLOG("MeRow %i OldRow %i ", medRow, oldRow);
				if (arrayRow.at(medRow)->arrayBall[medColumn]->isVisible()) {
					CCLOG("Voa day ** ");
					addMoveBall(oldRow, oldColumn);
				} else {
					CCLOG("Voa day ** 2");
					addMoveBall(medRow, medColumn);
				}

			} else {
				if (row < arrayRow.size() - 1) {
					// xet 6 vi tri quanh diem nay, neu co bong thi dung lai
					// ngay
					if (checkNearBall(x, y, row, column, 0, -1))
						return;
					if (checkNearBall(x, y, row, column, 0, 1))
						return;
					if (checkNearBall(x, y, row, column, -1, 0))
						return;
					if (checkNearBall(x, y, row, column, -1, 1))
						return;
					if (checkNearBall(x, y, row, column, 1, 0))
						return;
					if (checkNearBall(x, y, row, column, 1, 1))
						return;
				} else {
					CCLOG("vao day co 5");
					addMoveBall(row, column);
				}
			}

		} else {
			column = (int) ((x - START_X_EGG) / WIDTH_BALL_EGG);
			if (column >= NINE_ROW)
				column = NINE_ROW - 1;
			if (arrayRow.at(row)->arrayBall[column]->isVisible()) {
				float medX = (oldX + arrayRow.at(row)->arrayBall[column]->getPositionX() + WIDTH_BALL_EGG * 0.5f + START_X_EGG) / 2;
				float medY = (oldY + arrayRow.at(row)->arrayBall[column]->getPositionY() + WIDTH_BALL_EGG * 0.5f + START_Y_EGG) / 2;
				int medRow = (int) ((medY - START_Y_EGG) / HEIGH_BALL_EGG);
				int medColumn;
				if (medRow < 0)
					medRow = 0;
				if (arrayRow.at(medRow)->typeRow == EIGHT_ROW) {
					medColumn = (int) ((medX - START_X_EGG - WIDTH_BALL_EGG * 0.5f) / WIDTH_BALL_EGG);
					if (medColumn == NINE_ROW - 1)
						medColumn = NINE_ROW - 2;
				} else {
					medColumn = (int) ((medX - START_X_EGG) / WIDTH_BALL_EGG);
				}
				CCLOG("MeRow %i OldRow %i ", medRow, oldRow);
				if (arrayRow.at(medRow)->arrayBall[medColumn]->isVisible()) {
					CCLOG("Voa day ** 3");
					addMoveBall(oldRow, oldColumn);
				} else {
					CCLOG("Voa day ** 4");
					addMoveBall(medRow, medColumn);
				}
			} else {
				if (row < arrayRow.size() - 1) {
					if (checkNearBall(x, y, row, column, 0, -1))
						return;
					if (checkNearBall(x, y, row, column, 0, 1))
						return;
					if (checkNearBall(x, y, row, column, -1, 0))
						return;
					if (checkNearBall(x, y, row, column, -1, -1))
						return;
					if (checkNearBall(x, y, row, column, 1, 0))
						return;
					if (checkNearBall(x, y, row, column, 1, -1))
						return;
				} else {
					CCLOG("vao day co 6");
					addMoveBall(row, column);
				}
			}
		}

	} else {
		if (arrayRow.at(0)->typeRow == EIGHT_ROW) {
			column = (int) ((x - START_X_EGG) / WIDTH_BALL_EGG);
			if (column >= NINE_ROW)
				column = NINE_ROW - 1;
			if (checkNearBall(x, y, row, column, 1, 0))
				return;
			if (checkNearBall(x, y, row, column, 1, -1))
				return;
			if (checkNearBall(x, y, row, column, 1, 1))
				return;
		} else {
			column = (int) ((x - WIDTH_BALL_EGG * 0.5f - START_X_EGG) / WIDTH_BALL_EGG);
			if (column >= NINE_ROW - 1)
				column = NINE_ROW - 2;
			if (checkNearBall(x, y, row, column, 1, 0))
				return;
			if (checkNearBall(x, y, row, column, 1, 1))
				return;
			if (checkNearBall(x, y, row, column, 1, -1))
				return;
		}
	}

}

// kiem tra khoang cach bong bay voi bong co san tren hang
bool GUIEgg::checkNearBall(float x, float y, int row, int column,int dRow, int dColumn) 
{
	int idRow = row + dRow;
	int idColumn = column + dColumn;
	Ball* ballAdd = getBall(idRow, idColumn);
	if (ballAdd != NULL) {
		if (getDistance(ballAdd, x, y) < WIDTH_GATE) {
			// tao them bong o day
			addMoveBall(row, column);
			return true;
		}
	}
	return false;
}

void GUIEgg::addMoveBall(int row, int column) {
	Ball* ball;
	speedY = -1;
	CCLOG("Row %i column %i ", row, column);
	
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();
	if (row <= -1) {
		if (gameType == ENDLESS) {
			// day het cac hang len tren, them hang moi

			START_Y_EGG = START_Y_EGG - HEIGH_BALL_EGG;
			groupBall->setPositionY(START_Y_EGG);
	
			RowBall* rowBall = arrayRow.at(arrayRow.size() - 1);
			arrayRow.pop_back();

			for(int i1 = 0; i1 < arrayRow.size(); i1++)
			{
				arrayRow.at(i1)->moveUp(1);
			}
			arrayRow.insert(arrayRow.begin(), rowBall);
			rowBall->setIdRow(0, NINE_ROW + EIGHT_ROW - arrayRow.at(1)->typeRow);


			ball = arrayRow.at(0)->arrayBall[column];
			row = 0;
		}
		else {
			// day het cac hang len tren, them hang moi
			START_Y_EGG = START_Y_EGG - HEIGH_BALL_EGG;
			groupBall->setPositionY(START_Y_EGG);

			RowBall* rowBall =  new RowBall(0);
			for(int i = 0; i < rowBall->arrayBall.size(); i++)
			{
				groupBall->addChild(rowBall->arrayBall.at(i));
			}

			for(int i1 = 0; i1 < arrayRow.size(); i1++)
			{
				arrayRow.at(i1)->moveUp(1);
			}
			arrayRow.insert(arrayRow.begin(), rowBall);
			rowBall->setIdRow(0, NINE_ROW + EIGHT_ROW - arrayRow.at(1)->typeRow);

			ball = arrayRow.at(0)->arrayBall[column];
			row = 0;
		}
	} else {
		// dinh qua bong nay vao
		ball = arrayRow.at(row)->arrayBall[column];

	}
	
	ball->setVisible(true);
	ball->setId(moveBall->idBall);
	ball->setIdRow(row);
	ball->idColumn = column;
	ball->typeRow = arrayRow.at(row)->arrayBall[column]->typeRow;
	if (moveBall->isBonus()) {
		ball->setIdBonus(moveBall->idBonus);
	}
	
	/*if (true)
		return;*/
	moveBall->setVisible(false);
	moveBall->setIdBonus(-1);
	
	if (ball->checkEatBall()) {
		// remove qua bong nay cung nhung thang co lien quan
		
		int bonusScore = 0;
		GameSound::playBreakEgg();
		CCLOG("EAT BALL %i ", arrayEatBall.size());
		for (int i = 0; i < arrayEatBall.size(); i++) {
			showParticle(arrayEatBall.at(i)->getPositionX() + groupBall->getPositionX(),
				arrayEatBall.at(i)->getPositionY() + groupBall->getPositionY(), ball->idBall);
			if (arrayEatBall.at(i)->isVibrate) {
				nextBonus = true;
				bonusScore = bonusScore + 50;
				JNIUtils::vibrate(50);
				GameSound::playMama();

				GameImage* dinosaur = addImage("egg/dinosaur.png");
				dinosaur->setPosition(arrayEatBall.at(i)->rootX + groupBall->getPositionX(), arrayEatBall.at(i)->rootY + groupBall->getPositionY());
				dinosaur->runAction(CCSequence::create(CCDelayTime::create(0.5), CCMoveBy::create(1, ccp(0, -size.height)), CCCallFuncN::create(this, callfuncN_selector(GUIEgg::callbackRemove)), NULL));

				//effectBreakBall->stopAllActions();
				//effectBreakBall->setVisible(true);
				//effectBreakBall->getAnimation()->gotoAndPlay("run", -1, -1, -1);
				////   effectBreakBall->runAction(CCSequence::create(CCDelayTime::create(1.0), CCHide::create()));
				//effectBreakBall->setPosition(dinosaur->getPosition());

				effectBreakBall->stop();
				effectBreakBall->setVisible(true);
				effectBreakBall->play(0);
				effectBreakBall->setPosition(dinosaur->getPosition());
			}
			if (arrayEatBall.at(i)->isBonus()) {
					arrayEatBall.at(i)->bonusImage->setVisible(false);
					bonusEffect->setIdBonus(arrayEatBall.at(i)->idBonus);
			}
		}
	
		
		// int size = arrayRow.size();
		vector<vector<bool>> save;
		for (int i = 0; i < arrayRow.size(); i++) {
			vector<bool> save1;
			for (int j = 0; j < NINE_ROW; j++) {
				save1.push_back(arrayRow.at(i)->arrayBall[j]->isVisible());
			}
			save.push_back(save1);
		}
		ball->removeBall();
		int countEat = 0;

		int i;
		for (i = arrayRow.size() - 1; i >= 0; i--) {
			int j;
			for (j = 0; j < arrayRow.at(i)->arrayBall.size(); j++) {
				if (arrayRow.at(i)->arrayBall[j]->isVisible()) {
					break;
				}
			}
			if (j >= arrayRow.at(i)->arrayBall.size())
				break;
		}
		int rowRemove = i;

		for (int i = 0; i < arrayRow.size(); i++) {
			for (int j = 0; j < NINE_ROW; j++) {
				Ball* ball = arrayRow.at(i)->arrayBall[j];
				if (save[i][j] != arrayRow.at(i)->arrayBall[j]->isVisible()) {
					int i1;
					countEat++;
					for (i1 = 0; i1 < arrayEatBall.size(); i1++) {
						if (arrayEatBall.at(i1)->idColumn == j && arrayEatBall.at(i1)->idRow == i)
							break;
					}
					if (i1 == arrayEatBall.size()) {
						// hien effect bong roi
						CCLOG("Bong roi ");
						this->dropBall(ball->idBall, ball->getPositionX() + START_X_EGG, ball->getPositionY() + START_Y_EGG);
					}
				}
			}
		}
		if (gameType == ENDLESS || gameType == STOMP) {
			int addScore = GroupScoreEgg::getNormalBonusScore(arrayEatBall.size(), countEat - arrayEatBall.size(), bonusEffect->getMul(), bonusScore);
			if (arrayEatBall.size() > 6) {
				int vibrate = addScore / 5;
				vibrate = vibrate > 200 ? 200 : vibrate;
				JNIUtils::vibrate(vibrate);	
			}
			
			score = score + addScore;
			
			updateScore();
			GroupScoreEgg* group = getGroupScore();
			group->setVisible(true);
			group->createNormalBonusScore(arrayEatBall.size(), countEat - arrayEatBall.size(),
				bonusEffect->getMul(), bonusScore);
			group->setPosition(ball->rootX + groupBall->getPositionX() - group->getContentSize().width * 0.5f, ball->rootY + groupBall->getPositionY());
			group->runAction(CCSequence::create(CCEaseBackOut::create(CCMoveBy::create(0.7f, ccp(0, size.height * 0.1f))), CCFadeOut::create(0.5), CCHide::create(), NULL));
		}

		updateArrayBall();

		if (gameType == STOMP) {

			if (arrayRow.size() == 0) {
				// hoan thanh stomp nay
				state = GameStateEgg::END_GAME_EGG;
				if (level >= game->level) {
					game->level = level + 1;
					CCUserDefault::sharedUserDefault()->setIntegerForKey("level", game->level);
					CCUserDefault::sharedUserDefault()->flush();
					//MyCaro.game.caroScreen.getLeveLayer().updateLobby();
					//PreferenceHandler.saveLevel();
				}
				// mo lobby stomp

				numRowScore = (int) ((bar->getPositionY() - rope->getPositionY() - rope->getRealHeight()) / HEIGH_BALL_EGG + 1);
				countRowScore = 1;
				makeEffectScore();
			}
		} else if (gameType == TIME) {

			if (arrayRow.size() == 0) {
				state = GameStateEgg::END_GAME_EGG;
				// Hoan thanh game
				string s;
				if (game->scoreTime == 0
					|| game->scoreTime > countTime) {
						game->scoreTime = (int) countTime;
						labelHighscore->setText(("Highscore: " + convertTime(countTime)).c_str());
						CCUserDefault::sharedUserDefault()->setIntegerForKey("scoreTime", game->scoreTime);
						CCUserDefault::sharedUserDefault()->flush();
						s = "New Best Time: " + convertTime(countTime);
				} else {
					s = "Finish. Your Time: " + convertTime(countTime);
				}
				GUIManager::getInstance().guiDialog.showGUI(s.c_str(), &makeNewGame, false, &makeBack);
				// update highscore
				
			}

		}

	} else {
		GameSound::playEggLands();
	}
	labelRow->setText((GameUtility::toString(arrayRow.size()) + " ROWS").c_str());
	if (gameType == TIME) {
		if (arrayRow.size() != 0)
			distanceY = rope->getPositionY() + rope->getRealHeight() - groupBall->getPositionY();
	}

	if (delay)
		delayReturn();
	delay = false;

}

double GUIEgg::getDistance(Ball* ball, float x, float y) {
	double result;
	result = (groupBall->getPositionX() + ball->getPositionX() + ball->getRealWidth() * 0.5f - x)
		* (groupBall->getPositionX() + ball->getPositionX() + ball->getRealWidth() * 0.5f - x)
		+ (groupBall->getPositionY() + ball->getPositionY() + ball->getRealHeight() * 0.5f - y)
		* (groupBall->getPositionY() + ball->getPositionY() + ball->getRealHeight() * 0.5f - y);
	result = (float) (sqrt(result));
	return result;
}

bool GUIEgg::checkEndGame() {
	if (gameType == TIME)
		return false;
	if (START_Y_EGG < rope->getPositionY() + rope->getRealHeight()) {
		return true;
	}
	return false;

}

void GUIEgg::endGame() {
	state = GameStateEgg::END_GAME_EGG;
	genBall->setVisible(false);
	int count = 0;
	for (int i = 0; i < arrayRow.size(); i++) {
		for (int j = 0; j < NINE_ROW; j++) {
			if (arrayRow.at(i)->arrayBall[j]->isVisible()) {
				arrayRow.at(i)->arrayBall[j]->runAction(Sequence::create(DelayTime::create(count * 0.015), Hide::create(), NULL));
				if (GameUtility::getRandom() < 0.3f)
				{
					showBomb(arrayRow.at(i)->arrayBall[j]->getPositionX() + groupBall->getPositionX(),
						arrayRow.at(i)->arrayBall[j]->getPositionY() + groupBall->getPositionY(), count * 0.015);
				}
				count++;
			}
		}

	}
	progress->cleanup();
    GameSound::playGameOver();

	runAction(CCSequence::create(CCDelayTime::create(1),  CCCallFunc::create(this, callfunc_selector(GUIEgg::callbackEndGame)), NULL));
	
	// hien hop hoi thoai end game
}

void GUIEgg::makeGenBall() {
	// TODO Auto-generated method stub
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();
	if (state != GameStateEgg::PLAY_EGG)
		return;
	if (gameType == ENDLESS) {
		if (NUM_BALL == 8)
			return;
		ani->setVisible(true);
		genBall->setVisible(true);

		double rand = GameUtility::getRandom() * 45;
		rand = rand;
	//	rand = rand * (GameUtility::getRandom() > 0.5f ? 1 : -1);
		
		ani->setDegree(rand);
        ani->countAppear++;
		ani->setPosition(size.width * 0.5f, -ani->getRealHeight());
		genBall->setId(NUM_BALL);
		GameSound::playWhirley();
	} else if (gameType == STOMP) {
		// Tween.to(groupBall, ActorAccessor.POS_XY,
		// 500).target(groupBall->getPositionX(), groupBall->getPositionY() -
		// HEIGH_BALL_EGG)
		// .start(MyCaro.game.tweenManger);
		distanceY = HEIGH_BALL_EGG;
		countDistance = 0;
	}

}

void GUIEgg::showParticle(float px, float py, int id) {
	Layer *layer = layerMgr->getLayerByIndex(LAYER_EFFECT_GAME);
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	string s = "particles/egg" + GameUtility::toString(id + 1) + ".plist";
//	s = "particles/vip.plist";
	ParticleEffect *effect = new ParticleEffect();
	effect->create(s.c_str(), layer);
	effect->particle->setPosition(px, py);
	effect->particle->setBlendAdditive(false);
	effect->particle->setAutoRemoveOnFinish(true);
	//CCSize size = CCDirector::sharedDirector()->getWinSize();
	float scale = (size.width / DEFAULT_SCREEN_WIDTH) > (size.height / DEFAULT_SCREEN_HEIGHT) ? (size.width / DEFAULT_SCREEN_WIDTH) : (size.height / DEFAULT_SCREEN_HEIGHT);
	effect->particle->setScale(scale);

// 	effect =  effectMgr->addParticleEffect("particles/egg.plist", ccp (px, py), layer);
// 	effect->particle->setBlendAdditive(false);
// 
	ParticleEffect *effect1 = new ParticleEffect();
	effect1->create("particles/ball.plist", layer);
	effect1->particle->setPosition(px, py);
	effect1->particle->setBlendAdditive(false);
	effect1->particle->setAutoRemoveOnFinish(true);

	if (bonusEffect->isVisible() && bonusEffect->getMul() > 1) {
		effect1 = new ParticleEffect();
		effect1->create("particles/bigbet.plist", layer);
		effect1->particle->setPosition(px, py);
		effect1->particle->setBlendAdditive(false);
		effect1->particle->setAutoRemoveOnFinish(true);
	}
}


void GUIEgg::showBomb(float px, float py, float delayTime) {
	BombEffect* group = NULL;
	for (int i = 0; i < arrayBomb.size(); i++)
	{
		if (!arrayBomb.at(i)->isVisible())
		{
			arrayBomb.at(i)->setOpacity(255);
			group = arrayBomb.at(i);
			break;
		}
	}
	if (group == NULL)
	{
		group = new BombEffect();
		addChild(group);
	}
	group->setLocalZOrder(100);
	arrayBomb.push_back(group);
	group->setPosition(px, py);
	group->showBomb(delayTime);
}

void GUIEgg::makeBonus() {
	for(int i = 0; i < arrayRow.size(); i++)
	{
		for(int j = 0; j < arrayRow.at(i)->arrayBall.size(); j++)
		{
			if(arrayRow.at(i)->arrayBall.at(j)->isVisible() && arrayRow.at(i)->arrayBall.at(j)->isBonus())
				return;
		}

	}
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();
	double rand = GameUtility::getRandom();
	int id;
	if (rand < 0.4f) {
		if (groupBall->getPositionY() < size.height * 0.35f) {
			if (GameUtility::getRandom() > 0.7f)
				nextBall->setIdBonus(4);
			else
				nextBall->setIdBonus(0);
		} else
			nextBall->setIdBonus(0);
	} else if (rand < 0.65f) {
		nextBall->setIdBonus(1);
	} else if (rand < 0.85f) {
		nextBall->setIdBonus(2);
	} else {
		nextBall->setIdBonus(3);
	}
	
	nextBonus = false;

}

void GUIEgg::updateScore() {

	labelScore->setText(("Score: " + GameUtility::toString(score)).c_str());

	if (gameType == ENDLESS) {
		if (score > game->scoreEndless) {
			labelHighscore->setText(("Highscore: " + GameUtility::toString(score)).c_str());
			game->scoreEndless = score;
			CCUserDefault::sharedUserDefault()->setIntegerForKey("scoreEndless", score);
			CCUserDefault::sharedUserDefault()->flush();
			isNewhigh = true;
		}
	} else {
		if (score > game->scoreStomp[level]) {
			labelHighscore->setText(("Highscore: " + GameUtility::toString(score)).c_str());
			game->scoreStomp[level] = score;
			CCUserDefault::sharedUserDefault()->setIntegerForKey(("scoreStomp" + GameUtility::toString(level)).c_str(), score);
			CCUserDefault::sharedUserDefault()->flush();
			isNewhigh = true;
		}
	}
}

void GUIEgg::newGame() {
	for (int i = 0; i < arrayGroupScore.size(); i++) {
		arrayGroupScore.at(i)->setVisible(false);
	}
	for (int i = 0; i < arrayBomb.size(); i++) {
		arrayBomb.at(i)->setVisible(false);
	}
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();
	//gameType = STOMP;
	//level = 4;
	initGame();
	arrayEatBall.clear();
	isNewhigh = false;
	int idBall = (int) (GameUtility::getRandom() * NUM_BALL);
	moveBall->setId(idBall);
	moveBall->setPosition(START_BALL_X, START_BALL_Y);

	int idNextBall = (int) (GameUtility::getRandom() * NUM_BALL);
	nextBall->setId(idNextBall);
	nextBall->setPosition(cannon1->getPositionX() + cannon1->getRealWidth() * 0.8f, cannon1->getPositionY() + cannon1->getRealHeight() * 0.8f);
	distanceY = 0;
	speedY = -1;
	if (gameType == ENDLESS) {
		START_Y_EGG = size.height * 0.5f;
		NUM_BALL = 3;
		rope->setPosition(size.width * 0.5f, START_BALL_Y + WIDTH_BALL_EGG * 1.5f);
		progress->setVisible(true);
		bgProgress->setVisible(true);
	} else if (gameType == TIME) {
		rope->setPosition(size.width * 0.5f, size.height * 0.4f);
		START_Y_EGG = rope->getPositionY() + rope->getRealHeight();
		progress->setVisible(false);
		bgProgress->setVisible(false);
		bar->setPosition(0, START_Y_EGG + arrayRow.at(arrayRow.size() - 1)->arrayBall[0]->rootY + arrayRow.at(arrayRow.size() - 1)->arrayBall[0]->getRealHeight());
	} else if (gameType == STOMP){
		rope->setPosition(size.width * 0.5f , START_BALL_Y + WIDTH_BALL_EGG * 1.5f);
		if(level == 11 || level ==16 || level == 17 || level == 18)
			START_Y_EGG = rope->getPositionY() + 3.9f * HEIGH_BALL_EGG;
		else if(level == 17)
			START_Y_EGG = rope->getPositionY() + 3.9f * HEIGH_BALL_EGG;
		else
			START_Y_EGG = rope->getPositionY() + 2.9f * HEIGH_BALL_EGG;
		progress->setVisible(true);
		bgProgress->setVisible(true);
		bar->setPosition(0,START_Y_EGG + arrayRow.at(arrayRow.size() - 1)->arrayBall[0]->rootY + arrayRow.at(arrayRow.size() - 1)->arrayBall[0]->getRealHeight());
	}
	groupBall->setPosition(START_X_EGG, START_Y_EGG);

	countTime = 0;
	countTimeVisible = 0;
	countVisible = -1;
	delay = false;
	arrayEatBall.clear();

	state = GameStateEgg::WAIT_PLAY_EGG;
	ani->newGame();

	genBall->setVisible(false);

	increaseSpeed = false;

	countTimeVibrate = 0;

	nextBonus = false;

    ani->setVisible(false);
	score = 0;
	if(gameType != TIME)
		updateScore();
	bonusEffect->setVisible(false);
	isMoving = false;

	for (int i = 0; i < arrayEffectBall.size(); i++) {
		arrayEffectBall.at(i)->setVisible(false);
	}

	// for (int i = 0; i < arrayRow.size(); i++) {
	// arrayRow.at(i)->renew(arrayRow.at(i)->typeRow);
	// }
}

void GUIEgg::initGame() {
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();
	groupBall->removeAllChildren();
	arrayRow.clear();
	int NUM_ROW = 0;
	// START_X_EGG = 0;
	// WIDTH_BALL_EGG = WIDTH_BALL_EGG * 0.8f;
	// HEIGH_BALL_EGG = WIDTH_BALL_EGG * 0.9f;
	switch (gameType) {
	case ENDLESS:
		{
			labelHighscore->setText(("Highscore: " + GameUtility::toString(game->scoreEndless)).c_str());

			NUM_ROW = (int) (size.height * 0.73f / HEIGH_BALL_EGG);
			NINE_ROW = 9;
			EIGHT_ROW = NINE_ROW - 1;
			START_X_EGG = size.width * 0.1f;
			NUM_BALL = 3;
			for (int i = 0; i < NUM_ROW; i++) {
				RowBall* rowBall;
				rowBall = new RowBall(i);
				arrayRow.push_back(rowBall);
			}

			for (int i = 0; i < NUM_ROW; i++) {
				for (int j = 0; j < arrayRow.at(NUM_ROW - 1 - i)->arrayBall.size(); j++) {
					groupBall->addChild(arrayRow.at(i)->arrayBall[j]);
				}
				arrayRow[i]->effectNewGame(0.04 * i);
			}
			
			bar->setPositionY(size.height);

			labelRow->setVisible(false);
			bgRow->setVisible(false);

			bgProgress->setVisible(true);
			progress->cleanup();
			CCProgressTo *to1 = CCProgressTo::create(20, 100);
			//    Setup for a bar starting from the bottom since the midpoint is 0 for the y
			progress->setMidpoint(ccp(0,1));
			//    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
			progress->setBarChangeRate(ccp(0, 1));
			progress->setPercentage(0);
			progress->runAction(CCRepeatForever::create(CCSequence::create(to1, CCCallFunc::create(this, callfunc_selector(GUIEgg::callbackProgress)), NULL)));
			break;
		}
		
	case STOMP:
		{
			labelHighscore->setText(("Highscore: " + GameUtility::toString(game->scoreStomp[level])).c_str());
			game->readDataLevel(level);
			NUM_ROW = game->dataLevel[level].size();
			NINE_ROW = game->dataLevel[level][0].size();
			EIGHT_ROW = NINE_ROW - 1;
			NUM_BALL = game->numBall[level];
			START_X_EGG = (size.width - NINE_ROW * WIDTH_BALL_EGG) / 2;

			int typeRow = game->typeRow[level];
			for (int i = 0; i < NUM_ROW; i++) {
				RowBall* rowBall;
				rowBall = new RowBall(i, typeRow);
				typeRow = NINE_ROW + EIGHT_ROW - typeRow;
				arrayRow.push_back(rowBall);
			}

			for (int i = 0; i < NUM_ROW; i++) {
				for (int j = 0; j < arrayRow.at(NUM_ROW - 1 - i)->arrayBall.size(); j++) {
					groupBall->addChild(arrayRow.at(i)->arrayBall[j]);
					if (game->dataLevel[level][i][j] == -1) {
						arrayRow.at(i)->arrayBall[j]->setVisible(false);
					} else {
						arrayRow.at(i)->arrayBall[j]->setVisible(true);
						arrayRow.at(i)->arrayBall[j]->setId(game->dataLevel[level][i][j]);
					}
				}
			}
			
			bar->setVisible(true);

			labelRow->setVisible(false);
			bgRow->setVisible(false);
			labelRow->setText(NUM_ROW + " ROWS");

			bgProgress->setVisible(true);
			progress->cleanup();
			CCProgressTo *to1 = CCProgressTo::create(10, 100);
			//    Setup for a bar starting from the bottom since the midpoint is 0 for the y
			progress->setMidpoint(ccp(0,1));
			//    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
			progress->setBarChangeRate(ccp(0, 1));
			progress->setPercentage(0);
			progress->runAction(CCRepeatForever::create(CCSequence::create(to1, CCCallFunc::create(this, callfunc_selector(GUIEgg::callbackProgress)), NULL)));
			break;
		}
		
	case TIME:
		{
			labelScore->setText("Time: 00:00");
			if (game->scoreTime == 0) {
				labelHighscore->setText("Best Time: --:-- ");
			} else {
				labelHighscore->setText(("Best Time: " + convertTime(game->scoreTime)).c_str());
			}
			NUM_ROW = 10;
			NINE_ROW = 9;
			EIGHT_ROW = NINE_ROW - 1;
			START_X_EGG = size.width * 0.1f;
			NUM_BALL = 7;

			for (int i = 0; i < NUM_ROW; i++) {
				RowBall* rowBall;
				rowBall = new RowBall(i);
				arrayRow.push_back(rowBall);
			}

			for (int i = 0; i < NUM_ROW; i++) {
				for (int j = 0; j < arrayRow.at(NUM_ROW - 1 - i)->arrayBall.size(); j++) {
					groupBall->addChild(arrayRow.at(i)->arrayBall[j]);
				}
			}

			bar->setVisible(true);
			bar->setPosition(0, groupBall->getPositionY() + arrayRow.at(arrayRow.size() - 1)->arrayBall[0]->rootY);
			labelRow->setVisible(true);
			bgRow->setVisible(true);
			break;
		}
		
	default:
		break;
	}

	LIMIT_X = START_X_EGG + WIDTH_BALL_EGG * NINE_ROW;
	leftWall->setPositionX(START_X_EGG - leftWall->getRealWidth() * 0.7f);
	rightWall->setPositionX(LIMIT_X - rightWall->getRealWidth() * 0.3f);

}

void GUIEgg::updateTime() {

	labelScore->setText(GameUtility::convertTime(countTime).c_str());

}

string GUIEgg::convertTime(float countTime) {
	int minute = (int) (countTime / 60);
	int second = (int) (countTime - minute * 60);

	string minuteS, secondS;
	if (minute < 10) {
		minuteS = "0" + GameUtility::toString(minute);
	} else {
		minuteS = "" + GameUtility::toString(minute);
	}

	if (second < 10) {
		secondS = "0" + GameUtility::toString(second);
	} else {
		secondS = "" + GameUtility::toString(second);
	}
	return minuteS + ":" + secondS;
}

void GUIEgg::onPause() {
	
}

GroupScoreEgg * GUIEgg::getGroupScore()
{
	GroupScoreEgg *group;
	for (int i = 0; i < arrayGroupScore.size(); i++) {
		if (!arrayGroupScore.at(i)->isVisible()) {
			arrayGroupScore.at(i)->setOpacity(255);
			return arrayGroupScore.at(i);
		}
	}
	group = new GroupScoreEgg();
	addChild(group);
	group->setLocalZOrder(100);

	arrayGroupScore.push_back(group);
	return group;
}


void GUIEgg::callbackNextBall()
{
	moveBall->setVisible(true);
	if (speedY > 0) {
		delay = true;
	} else {
		// delay viec quay lai cua move ball
		delayReturn();
	}
}

void GUIEgg::callbackRemove(CCNode* pSender)
{
	pSender->removeAllChildrenWithCleanup(true);
}

void GUIEgg::callbackProgress()
{
	progress->setPercentage(0);
	makeGenBall();
	
}


void GUIEgg::callbackEndGame()
{
	string s = "";

	if (gameType == ENDLESS || gameType == STOMP) {

		if (gameType == STOMP)
			GUIManager::getInstance().guiResult.showGUI(score, game->scoreStomp[level]);
		else
			GUIManager::getInstance().guiResult.showGUI(score, game->scoreEndless);
	} else {
		s = "Game Over";
		GUIManager::getInstance().guiDialog.showGUI(s.c_str(), &makeNewGame, false, &makeBack);
	}
	
}

void GUIEgg::makeEffectScore()
{
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();
	int add;
	if (countRowScore == numRowScore)
	{
		add = 1000;
		endGame();
	}
	else
	{
		add = countRowScore * 100;
		countRowScore++;
		runAction(CCSequence::create(CCDelayTime::create(0.2f), CCCallFunc::create(this, callfunc_selector(GUIEgg::makeEffectScore)), NULL));
	}

	score = score + add;
	updateScore();
	GroupScoreEgg* group = getGroupScore();
	group->setVisible(true);
	group->createBonusScore(add);
	group->setPosition(size.width * 0.5f - group->getContentSize().width * 0.5f, rope->getPositionY() + countRowScore * HEIGH_BALL_EGG);
	group->runAction(CCSequence::create(CCSpawn::create(CCFadeOut::create(0.5f), 
		CCEaseBackOut::create(CCMoveBy::create(0.7f, ccp(0, size.height * 0.1f))), NULL), CCFadeOut::create(0.5), CCHide::create(), NULL));
}

void GUIEgg::showGui( GameType gameType )
{
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();
	if (size.width / size.height < 320.0f / 480.0f) {
		JNIUtils::showAdsBanner(1);
	}
	else {
		JNIUtils::showAdsBanner(0);
	}
	this->gameType = gameType;
	if(isInitted() && isVisible())
		return;
	BaseGUI::showGUI();
	GUIManager::getInstance().addToListGui(this);
	newGame();
}

void GUIEgg::showGui( int level )
{
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();
	if (size.width / size.height < 320.0f / 480.0f) {
		JNIUtils::showAdsBanner(1);
	}
	else {
		JNIUtils::showAdsBanner(0);
	}
	this->gameType = STOMP;
	this->level = level;
	if(isInitted() && isVisible())
		return;
	BaseGUI::showGUI();
	GUIManager::getInstance().addToListGui(this);
	newGame();
}


void GUIEgg::initDragonbone()
{
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();
	//if (effectLight != NULL) {
	//	effectLight->removeFromParent();
	//	effectShootBall->removeFromParent();
	//	effectBreakBall->removeFromParent();
	//	effectShoot->removeFromParent();
	//	effectWin->removeFromParent();
	//	//effectLight->removeFromParent();
	//}
	DBCCFactory::getInstance()->loadDragonBonesData("effect/LightBg/skeleton.xml", "LightBg");
	DBCCFactory::getInstance()->loadTextureAtlas("effect/LightBg/texture.plist", "LightBg");
	effectLight = DBCCFactory::getInstance()->buildArmatureNode("LightBg");
	effectLight->getAnimation()->gotoAndPlay("1");
	this->addChild(effectLight);
	effectLight->setPosition(size.width * 0.5, size.height * 0.7);
	effectLight->setScale(2.5);
	effectLight->setOpacity(170);

	DBCCFactory::getInstance()->loadDragonBonesData("effect/Vaoban/skeleton.xml", "Vaoban");
	DBCCFactory::getInstance()->loadTextureAtlas("effect/Vaoban/texture.plist", "Vaoban");
	effectShootBall = DBCCFactory::getInstance()->buildArmatureNode("Vaoban");
	effectShootBall->getAnimation()->gotoAndPlay("vaoban");
	this->addChild(effectShootBall);
	effectShootBall->setPosition(cannon1->getPositionX() + cannon1->getRealWidth() * 0.99f,
		cannon1->getPositionY() + cannon1->getRealHeight() * 0.99f);
	effectShootBall->setScale(0.5);
	effectShootBall->retain();

	DBCCFactory::getInstance()->loadDragonBonesData("effect/bom_change/skeleton.xml", "bom_change");
	DBCCFactory::getInstance()->loadTextureAtlas("effect/bom_change/texture.plist", "bom_change");
	

	DBCCFactory::getInstance()->loadDragonBonesData("effect/SaoBay/skeleton.xml", "SaobayCard");
	DBCCFactory::getInstance()->loadTextureAtlas("effect/SaoBay/texture.plist", "SaobayCard");
	effectShoot = DBCCFactory::getInstance()->buildArmatureNode("SaobayCard");
	effectShoot->getAnimation()->gotoAndPlay("1");
	this->addChild(effectShoot);
	effectShoot->setPosition(START_BALL_X + 10, START_BALL_Y);
	effectShoot->setScale(0.8);
	effectShoot->setVisible(false);

	DBCCFactory::getInstance()->loadDragonBonesData("effect/Chest/skeleton.xml", "Chest");
	DBCCFactory::getInstance()->loadTextureAtlas("effect/Chest/texture.plist", "Chest");
	effectWin = DBCCFactory::getInstance()->buildArmatureNode("Chest");
	effectWin->getAnimation()->gotoAndPlay("1");
	this->addChild(effectWin);
	effectWin->setPosition(size.width * 0.5, size.height * 0.6);

	effectWin->setVisible(false);

	manager = EffectManager::create(Size(size.width, size.height));
	auto effect = efk::Effect::create("fire.efk", 40.0f);
	if (effect != nullptr)
	{
		effectBreakBall = efk::EffectEmitter::create(manager);
		effectBreakBall->setEffect(effect);
		effectBreakBall->setPlayOnEnter(false);
		effectBreakBall->setRemoveOnStop(false);
		effectBreakBall->setSpeed(0.5);
		effectBreakBall->setPosition(200, 300);
        effectBreakBall->setScale(2);
	  //  effectBreakBall->setPosition(clock->getPosition());
		this->addChild(effectBreakBall, 10);
	}
}

void GUIEgg::dropBall(int id, float posX, float posY)
{
	CCLOG("DRO NE***");
	Ball* ball = getEffectBall();
	ball->setId(id);
	ball->setPosition(posX, posY);

	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();
	posY = posY - size.height * 1.1f;

	ball->runAction(CCSequence::create(CCEaseSineIn::create(CCMoveTo::create(1.2f, ccp(posX, posY))), CCHide::create(), NULL));
}

Ball* GUIEgg::getEffectBall()
{
	Ball* ball = NULL;
	for (int i = 0; i < arrayEffectBall.size(); i++) {
		if (!arrayEffectBall.at(i)->isVisible()) {
			ball = arrayEffectBall.at(i);
			break;
		}
	}
	if (ball == NULL) {
		ball = new Ball();
		this->addChild(ball);
		arrayEffectBall.push_back(ball);
	}
	ball->setVisible(true);
	ball->stopAllActions();
	return ball;
}


void GUIEgg::effectImage(int id)
{
	for (int j = 0; j < 10; j++) {
		ImageEffect* image = NULL;
		for (int i = 0; i < arrayImageEffect.size(); i++) {
			if (!arrayImageEffect.at(i)->isVisible()) {
				image = arrayImageEffect.at(i);
				break;
			}
		}
		if (image == NULL) {
			image = ImageEffect::create();
			this->addChild(image);
			arrayImageEffect.push_back(image);
		}
		image->setVisible(true);
		image->setOpacity(255);
		image->setScale(arrayRow.at(0)->arrayBall[0]->getScaleX());
		image->setTexture("480_800/egg/bubble_" + StringUtils::toString(id) + ".png");
		CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();
		image->initCoin(ImageEffect::TYPE_FLOW, 0, size.width * GameUtility::getRandom(), size.height * 1);
	}
}

void GUIEgg::addNewBall()
{
	NUM_BALL++;
	genBall->setVisible(false);
	effectImage(NUM_BALL);
}

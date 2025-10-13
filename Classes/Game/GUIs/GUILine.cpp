#include "GUILine.h"
#include "../../Engine/Utility/ScreenUtils.h"
#include "../../Engine/GlobalVar.h"
#include "../../Engine/Utility/LocalizedString.h"
#include "../GUIManager.h"
#include "../Utility/JNIUtils.h"
#include "../Utility/GameUtility.h"
#include "Engine/Utility/CStringUtils.h"
#include "../Utility/GameSound.h"
#include "Engine/GUI/ParticleEffect.h"
#include "Game/Data/GlobalData.h"
#include "Game/Utility/Toast.h"

#define BACKGROUND_RES "loading/bgPortalCenterZP.jpg"
#define PROGRESS_RES "loading/bgProgress.png"
#define ICON_GAME "loading/iconGame.png"
#define BG_PROGRESS "loading/black.png"

#define BTN_BACK_ID 1
#define BTN_SOUND_ID 2
#define BTN_UNDO_ID 3
#define BTN_BALL 4
#define BTN_HELP_ID 5
#define BTN_TROPHY 6
#define BTN_SAVE_ID 7
#define BTN_RESIZE_ID 8
#define BTN_NEW_GAME_ID 9

GUILine::GUILine(void) : BaseGUI()
{
	BaseGUI();

	setKeypadEnabled(true);
}


GUILine::~GUILine(void)
{
}


void GUILine::initGUI(){

	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();
// 	CCTextureCache::sharedTextureCache()->addImage(ScreenUtils::fileFull(BACKGROUND_RES).c_str());
// 	CCTextureCache::sharedTextureCache()->addImage(ScreenUtils::fileFull(PROGRESS_RES).c_str());
// 	CCTextureCache::sharedTextureCache()->addImage(ScreenUtils::fileFull("loading/LG2.png").c_str());
// 	CCTextureCache::sharedTextureCache()->addImage(ScreenUtils::fileFull("loading/LG2.png").c_str());
	//Image *bg1 = addImage("loading/LG2.png");
	//bg1->setWidth(size.width);
	//bg1->setHeight(size.height);
	//bg1->getImg()->runAction(CCSequence::create(CCFadeIn::create(0.8f), CCDelayTime::create(.8f), CCFadeOut::create(0.8f), CCCallFunc::create(this, callfunc_selector(GUILine::callBackSplash)), NULL));
	//runAction(CCSequence::create(CCDelayTime::create(0.1f), CCCallFunc::create(this, callfunc_selector(GUILine::callBackSplash)), NULL));
	//bg1->setPos(size.width / 2, size.height / 2);
	callBackSplash();
	
}

void GUILine::onBackKey(){
	if (typeMode == 0)
		game->showHelp = false;
	if (GUIManager::getInstance().isCallBackPress == false && GUIManager::getInstance().getLastGui() == this)
	{
		GUIManager::getInstance().isCallBackPress = true;
		savePreference();
		GUIManager::getInstance().removeAllGui();
		GUIManager::getInstance().showGui(&GUIManager::getInstance().guiMinigames);
		//GUIManager::getInstance().guiTop.showTop(-1);

	
		CCUserDefault::sharedUserDefault()->setFloatForKey("scaleBall", game->scaleBall);
		CCUserDefault::sharedUserDefault()->setFloatForKey("brightBall", game->brightBall);
		CCUserDefault::sharedUserDefault()->setIntegerForKey("timePlay", game->timePlay);
		CCUserDefault::sharedUserDefault()->flush();
	}
}


void GUILine::update(float dt)
{
	labelUndo->setString((GameUtility::toString(game->numUndo) + " Undo").c_str());
	game->timePlay = game->timePlay + dt;
	if (slider->isVisible()) {
		if (game->scaleBall != slider->getValue()) {
			game->scaleBall = slider->getValue();
			float scaleX;
			float scaleY;
			for (int i = 0; i < 9; i++)
				for (int j = 0; j < 9; j++)
				{
					if (board->arrayBall[i][j] >= 1 && board->arrayBall[i][j] <= 7) {
						arrayBall[i][j]->setWidth(sizeCell * game->scaleBall);
						arrayBall[i][j]->setHeight(sizeCell * game->scaleBall);
						scaleX = arrayBall[i][j]->getScaleX();
						scaleY = arrayBall[i][j]->getScaleY();
					}
				}
			for (int i = 0; i < 9; i++)
				for (int j = 0; j < 9; j++)
				{
					arrayBall[i][j]->rootScaleX = scaleX;
					arrayBall[i][j]->rootScaleY = scaleY;
				}
		}
		if (game->brightBall != sliderBright->getValue()) {
			game->brightBall = sliderBright->getValue();
			for (int i = 0; i < 9; i++)
				for (int j = 0; j < 9; j++)
				{

					int value = 255 * game->brightBall;
					arrayBall[i][j]->getImg()->setColor(ccc3(value, value, value));
				}
		}
	}
}
void okEndGame1()
{
    game->endGame();
}

void okUndo () {
	JNIUtils::showRewardedAds();
}

void cancelUndo () {

}


void cancelNewGame()
{
    
}

void okNewGame()
{
	game->showHelp = false;
	if (GUIManager::getInstance().guiLine.score > 100) {
		game->showAdsFull();
		GUIManager::getInstance().guiLine.loadAdsFull();
	}
    if(GUIManager::getInstance().guiLine.typeMode == 0)
    {
        game->isPlaying = false;
        CCUserDefault::sharedUserDefault()->setBoolForKey("isPlaying", false);
		CCUserDefault::sharedUserDefault()->setBoolForKey("isPlayingNormal", false);
    }
    else
    {
        game->isPlayingTime = false;
        CCUserDefault::sharedUserDefault()->setBoolForKey("isPlayingTime", false);
    }
    CCUserDefault::sharedUserDefault()->flush();
    GUIManager::getInstance().guiLine.newGame();
}


void GUILine::onButtonRelease(int buttonID, CCTouch* touch)
{
	switch (buttonID)
	{
	case BTN_BACK_ID:
		{
			onBackKey();
		}
		break;
	case BTN_SOUND_ID:
		{
			game->music = !game->music;
			if(game->music)
			{
				btnSound->normalImage->setImage("btnSoundOn.png", true);
			}
			else
			{
				btnSound->normalImage->setImage("btnSoundOff.png", true);
			}

			CCUserDefault::sharedUserDefault()->setBoolForKey("music", game->music);
			CCUserDefault::sharedUserDefault()->flush();
		}
		break;
	case BTN_UNDO_ID:
		{
			if(canUndo && (game->showHelp == false || typeMode == 1))
			{
				//if (game->numUndo > 0) {
					undo();
					canUndo = false;
					btnUndo->setEnable(canUndo);
					numUndo--;
					if (numUndo < 0) {
						//game->showAdsForOldUser();
						numUndo = 2;
					}
				/*}
				else {
					GUIManager::getInstance().guiDialog.showGUI("You must view Video Ads to get more Undo Action?", &okUndo, false, &cancelUndo);
				}*/
			}
		}
		break;
            
        case BTN_BALL:
        {
			game->typeBall = game->typeBall + 1;
			int numBall = 5;
			if (game->isIOS())
				numBall = 5;
			if (game->typeBall > numBall)
				game->typeBall = 0;
			int id = game->typeBall + 1;
			if (id > numBall)
				id = 0;
			CCLOG("TYPE BALL NE %i ", id);
			btnBall->normalImage->setImage(("btnBall_" + GameUtility::toString(id) + ".png").c_str(), true);
			//typeBall = 1 - typeBall;
			
			if (game->typeBall == 6) {
				for (int i = 0; i < 9; i++)
					for (int j = 0; j < 9; j++)
					{
						int index = i * 9 + j;
						game->data[index] = board->arrayBall[i][j];
					}

				GUIManager::getInstance().removeAllGui();
			//	GUIManager::getInstance().guiLineOld.showGui();
			}
			else {
				// load next ball

				updateNextBall();
				for (int i = 0; i < 9; i++)
					for (int j = 0; j < 9; j++) {
						if (board->arrayBall[i][j] > 0) {
							genBall(i, j);
						}
					}

			}

		
       //     game->oldVersion = true;
			
            CCUserDefault::sharedUserDefault()->setIntegerForKey("typeBallNew", game->typeBall);
            CCUserDefault::sharedUserDefault()->flush();
        }
            break;
		case BTN_HELP_ID:
		{
			
			GUIManager::getInstance().showGui(&GUIManager::getInstance().guiHelp);
		}
		break;
		case BTN_TROPHY:
		{
			/*if (typeMode == 0)
				JNIUtils::submitScore(game->highscore, typeMode);
			else
				JNIUtils::submitScore(game->highscoreTime, typeMode);*/
			//GUIManager::getInstance().showGui(&GUIManager::getInstance().guiChangeName);
			break;
		}
		case BTN_SAVE_ID:
		{
			game->loadSave();
			savePreference();
			GUIManager::getInstance().guiSave.showGUI(true);
		//	game->showAdsForOldUser();
			break;
		}
		case BTN_RESIZE_ID:
		{
			slider->setVisible(!slider->isVisible());
			sliderBright->setVisible(!sliderBright->isVisible());
			btnNewGame->setVisible(!slider->isVisible());
			btnTrophy->setVisible(!slider->isVisible() && !game->isIOS());
			break;
		}
		case BTN_NEW_GAME_ID:
		{
			GUIManager::getInstance().guiDialog.showGUI(CCLocalizedString("START_NEW_GAME").c_str(), &okNewGame, false, &cancelNewGame,
				NULL, NULL);
			break;
		}
        default:
		break;
	}
}

void GUILine::callBackSplash()
{
	BaseGUI::initGUI();
	isUpdate = true;
//	typeBall = game->typeBall;
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();

	GameImage* background = addImage("lobby_background.png");
	background->setWidth(size.width);
	background->setHeight(size.height);
	background->setPos(size.width / 2, size.height / 2);

	btnBack = addButton(BTN_BACK_ID, "btnBack.png", new BubbleBehavior(), NULL, true);
	btnBack->setPosition(size.width - btnBack->getWidth() * 0.6f, size.height - btnBack->getHeight() * 0.7f);
	if (game->isIOS() && size.width / size.height < 11.0 / 20.0) {
		btnBack->setPosition(size.width - btnBack->getWidth() * 0.7f, size.height - btnBack->getHeight() * 1.5f);
	}
	else {
		btnBack->setPosition(size.width - btnBack->getWidth() * 0.7f, size.height - btnBack->getHeight() * 0.7f);
	}

	btnSound = addButton(BTN_SOUND_ID, "btnSoundOn.png", new BubbleBehavior(), NULL, true);
	btnSound->setPosition(btnBack->getPositionX() - btnBack->getWidth() * 1.1f, btnBack->getPositionY());
	if(game->music)
	{
		btnSound->normalImage->setImage("btnSoundOn.png", true);
	}
	else
	{
		btnSound->normalImage->setImage("btnSoundOff.png", true);
	}

	btnHelp = addButton(BTN_HELP_ID, "btnHelp.png", new BubbleBehavior(), NULL, true);
	btnHelp->setPosition(btnSound->getPositionX() - btnSound->getWidth() * 1.1f, btnBack->getPositionY());
	//btnHelp->setVisible(false);

	btnSave = addButton(BTN_SAVE_ID, "btnSave.png", new BubbleBehavior(), NULL, true);
	btnSave->setPosition(btnHelp->getPositionX() - btnHelp->getWidth() * 1.1f, btnBack->getPositionY());

	btnUndo = addButton(BTN_UNDO_ID, "btnUndo.png", new BubbleBehavior(), NULL, true);
	btnUndo->setPosition(btnSave->getPositionX() - btnSave->getWidth() * 1.1f, btnBack->getPositionY());

	btnResize = addButton(BTN_RESIZE_ID, "btnResize.png", new BubbleBehavior(), NULL, false);
	btnResize->setPosition(btnResize->getWidth() * 0.7f, btnBack->getPositionY());

	int id =  game->typeBall + 1;
	int numBall = 5;
	if (game->isIOS())
		numBall = 6;
	if (id > numBall)
		id = 0;
	btnBall = addButton(BTN_BALL, ("btnBall_" + GameUtility::toString(id) + ".png").c_str(), new BubbleBehavior(), NULL, true);
	btnBall->setPosition(btnResize->getPositionX() + btnResize->getWidth() * 1.2f, btnBack->getPositionY());

	btnTrophy = addButton(BTN_TROPHY, "iconTrophy.png", new BubbleBehavior(), NULL, true);
	btnTrophy->setPosition(btnTrophy->getWidth() * 0.6, btnBack->getPositionY() - btnBack->getHeight() * 1.0);
	btnTrophy->setVisible(!game->isIOS());

	btnNewGame = addButton(BTN_NEW_GAME_ID, "btnNewGame.png", new BubbleBehavior(), NULL, true);
	btnNewGame->setPosition(size.width * 0.5, btnBack->getPositionY() - btnBack->getHeight() * 1.1);

	btnSkip = addButton(BTN_NEW_GAME_ID, "btnSkip.png", new BubbleBehavior(), NULL, false);
	btnSkip->setPosition(btnNewGame->getPositionX(), btnNewGame->getPositionY());

	lbKnowRule = Text::create("I known game's rule", "fonts/tahomabd.ttf", 22);
	addChild(lbKnowRule);
	lbKnowRule->setColor(ccColor3B(172, 232, 251));
	lbKnowRule->enableOutline(Color4B(115, 37, 31, 255), 2);
	lbKnowRule->setPosition(Vec2(btnSkip->getPositionX() + 70, btnSkip->getPositionY()));
	lbKnowRule->setAnchorPoint(ccp(0, 0.5));

	slider = extension::ControlSlider::create("bgProgressEvent.png", "progressEvent.png", "dot.png");
	float sliderScale = size.width * 0.4 / slider->getContentSize().width;
	slider->setScale(sliderScale);
	addChild(slider);
	slider->setPosition(slider->getContentSize().width * 0.6 * sliderScale, btnNewGame->getPositionY());
	slider->setMinimumValue(0.6);
	slider->setMaximumValue(0.9);
	slider->setValue(game->scaleBall);
	slider->setVisible(false);

	sliderBright = extension::ControlSlider::create("bgProgressEvent.png", "progressEvent.png", "dot.png");
	sliderBright->setScale(sliderScale);
	addChild(sliderBright);
	sliderBright->setPosition(size.width * 1.0 - sliderBright->getContentSize().width * 0.6 * sliderScale, btnNewGame->getPositionY());
	sliderBright->setMinimumValue(0.7);
	sliderBright->setMaximumValue(0.9);
	sliderBright->setValue(game->brightBall);
	sliderBright->setVisible(false);
    
	bg = addImage("bkg.png", 0, 0, 0,true);
    float widthBoard;
	if (size.width / size.height >= 3.0f / 4.0f)
		widthBoard = size.width * 0.8f;
	else if (size.width / size.height > 481.0f / 800.0f)
		widthBoard = size.width * (0.9 - 0.1 * ((1.0/4.0 - (3.0/4.0 - size.width/size.height)) / (1.0/4.0)));
    else if (size.width / size.height > 475.0f / 800.0f)
        widthBoard = size.width * 0.92;
	else
		widthBoard = size.width * 0.98;
	float scale = widthBoard / bg->getWidth();
	bg->setWidth(widthBoard);
	bg->setHeight(bg->getHeight() * scale);
    bg->setPos(size.width / 2, btnNewGame->getPositionY() - btnNewGame->getHeight() * 0.6f - bg->getRealHeight() * 0.5f);
    
    scoreGroup = new ScoreGroup(0);
	addChild(scoreGroup);
	scoreGroup->setPositionX(bg->getPositionX() - bg->getRealWidth() * 0.49f);
	scoreGroup->setPositionY(bg->getPositionY() + bg->getRealHeight() * 0.39f + bg->getRealHeight() * 0.1f * 0.5f - scoreGroup->getContentSize().height * 0.5f);// - scoreGroup->getContentSize().height * 1.3f);

	highscoreGroup = new ScoreGroup(0);
	addChild(highscoreGroup);
	highscoreGroup->setPositionX(bg->getPositionX() + bg->getRealWidth() * 0.49f - highscoreGroup->getContentSize().width);
	highscoreGroup->setPositionY(scoreGroup->getPositionY());
	highscoreGroup->setMoney(game->highscore);

	ballMove = addImage("lineBall_0_0.png", 0, 0, 0, false);
	ballMove->setVisible(false);
	ballMove->setZOrder(2);

	_streak = MotionStreak::create(0.15f, 5.0f, 30, Color3B(255, 255, 255), "480_800/lineBall_0_0.png");
	Texture2D *texture = _director->getTextureCache()->addImage("480_800/lineBall_2_6.png");
	_streak->setTexture(texture);
	addChild(_streak);
	_streak->setPosition(100, 100);
	//_streak->setLocalZOrder(2);
	_streak->setVisible(false);
	//_streak->runAction(CCMoveBy::create(0.5, ccp(100, 600)));
	

	for (int i = 3; i >= 0; i--) {
		arrayMoveBall[i] = addImage("lineBall_0_0.png", 0, 0, 0, false);
		arrayMoveBall[i]->setVisible(false);
		
		arrayMoveBall[i]->setLocalZOrder(1);
	}

	for(int i = 0; i < 3; i++)
	{
		arrayNext[i] = addImage("lineBall_0_0.png", 0, 0, 0, false);
		arrayNext[i]->setVisible(false);
		arrayNext[i]->setWidth(bg->getRealWidth() * 0.085f);
		arrayNext[i]->setHeight(arrayNext[i]->getRealWidth());
		if(i == 0)
		{
			arrayNext[i]->setPos(size.width / 2 - arrayNext[i]->getRealWidth() * 1.1f, bg->getPositionY() + bg->getRealHeight() * 0.5f - arrayNext[i]->getRealHeight() * 0.75f);
		}
		else
		{
			arrayNext[i]->setPos(arrayNext[i - 1]->getPositionX() + arrayNext[i - 1]->getRealWidth() * 1.1f, arrayNext[0]->getPositionY());
		}
		
	}
    
    bgProgress = addImage("progress_bg.png", 0, 0, 0, true);
    bgProgress->setAnchorPointImage(ccp(0, 0.5f));
    bgProgress->setWidth(arrayNext[0]->getRealWidth() * 3);
    bgProgress->setHeight(arrayNext[0]->getRealHeight() * 0.2f);
    bgProgress->setPos(arrayNext[1]->getPositionX() - bgProgress->getRealWidth() * 0.5f, arrayNext[1]->getPositionY() - arrayNext[1]->getRealHeight() * 0.4f);
   // bgProgress->setColor(ccc3(50, 50, 50));
    
    progress = addImage("progress.png", 0, 0, 0, true);
    progress->setAnchorPointImage(ccp(0, 0.5f));
    progress->setWidth(bgProgress->getRealWidth());
    progress->setHeight(bgProgress->getRealHeight());
    progress->setPos(bgProgress->getPositionX(), bgProgress->getPositionY());
    

	float pad = size.width * 0.0117f;

	startX = bg->getPositionX() - bg->getRealWidth() * 0.495f;
	startY = bg->getPositionY() - bg->getRealHeight() * 0.495f;
	sizeCell = bg->getRealWidth() * 0.99f * (1/9.0f);

	ballMove->setWidth(sizeCell * 0.5f);
	ballMove->setHeight(sizeCell * 0.5f);
	for(int i = 0; i < 9; i++)
		for(int j = 0; j < 9; j++)
		{
			arrayBall[i][j] = new BallAnimationNew("lineBall_0_0.png", false);
			arrayBall[i][j]->nameImage = "lineBall_0_0";
			addImage(arrayBall[i][j]);
			arrayBall[i][j]->setWidth(sizeCell * game->scaleBall);
			arrayBall[i][j]->setHeight(sizeCell * game->scaleBall);
			arrayBall[i][j]->rootScaleX = arrayBall[i][j]->getScaleX();
			arrayBall[i][j]->rootScaleY = arrayBall[i][j]->getScaleY();
			arrayBall[i][j]->setPos(sizeCell * (j + 0.5f) + startX, startY + sizeCell * (i + 0.5f));
		}

	labelScore = Text::create("20", "fonts/tahomabd.ttf", 40);
	addChild(labelScore);
	labelScore->setColor(ccColor3B(172, 232, 251));
	labelScore->enableOutline(Color4B(115, 37, 31, 255), 2);
	labelScore->setPosition(Vec2(scoreGroup->getPositionX() + scoreGroup->getContentSize().width * 0.5, scoreGroup->getPositionX() + scoreGroup->getContentSize().height * 0.5));

	labelUndo = LabelBM::create("20", FONT_GAME_TYPE);
	labelUndo->setAnchorPoint(ccp(1, 0.75));
	labelUndo->setAlignment(TextHAlignment::RIGHT);
	addChild(labelUndo);
	labelUndo->setScale(0.8);
	labelUndo->setColor(ccColor3B(43, 202, 240));
	labelUndo->setLocalZOrder(10);
	labelUndo->setPosition(btnUndo->getPositionX() - btnUndo->getWidth() * 0.7, btnUndo->getPositionY());
	labelUndo->setVisible(false);

	effect = new GameImage("effect_1.png", true);
	this->addChild(effect);
	effect->setLocalZOrder(10);

	DBCCFactory::getInstance()->loadDragonBonesData("Chest/skeleton.xml", "Chest");
	DBCCFactory::getInstance()->loadTextureAtlas("Chest/texture.plist", "Chest");

	effIcon = DBCCFactory::getInstance()->buildArmatureNode("Chest");
	if (effIcon)
	{
		addChild(effIcon);
		effIcon->setPosition(size.width * 0.5, bg->getPositionY());
		effIcon->setVisible(false);
	}

	board = new BoardData();

	iconHand = addImage("iconHand.png", 0, 0, 0, false);
	iconHand->setVisible(false);

	layerColor = CCLayerColor::create(ccc4(0, 0, 0, 100), size.width, size.height);
	addChild(layerColor);
	layerColor->setLocalZOrder(1);
	layerColor->setContentSize(size);

	imgNewBest = Sprite::create("480_800/iconNewBest.png");
	addChild(imgNewBest);
	imgNewBest->setLocalZOrder(3);
}

void okFunction1()
{
	
}

void cancelFunction1()
{
	if(GUIManager::getInstance().guiLine.typeMode == 0)
	{
		game->isPlaying = false;
		CCUserDefault::sharedUserDefault()->setBoolForKey("isPlaying", false);
		CCUserDefault::sharedUserDefault()->setBoolForKey("isPlayingNormal", false);
	}
	else
	{
		game->isPlayingTime = false;
		CCUserDefault::sharedUserDefault()->setBoolForKey("isPlayingTime", false);
	}
	CCUserDefault::sharedUserDefault()->flush();
	GUIManager::getInstance().guiLine.newGame();
}


void GUILine::newGame()
{
	numUndo = 2;
	layerColor->setVisible(false);
	JNIUtils::crashlyticSetString("GUILine", "New Game");
	imgNewBest->setVisible(false);
	imgNewBest->stopAllActions();
	iconHand->setVisible(false);
	effect->setVisible(false);
	effIcon->setVisible(false);
	labelUndo->setString((GameUtility::toString(game->numUndo) + " Undo").c_str());
	labelScore->setVisible(false);
	for (int i = 0; i < arrayEffectBall.size(); i++) {
		arrayEffectBall.at(i)->setVisible(false);
	}
	labelScore->setVisible(false);
	//game->isPlaying = false;
	if(typeMode == 0)
	{
		if (game->isPlaying)
		{
			board->loadGame();
			updateScore(game->saveScore);
			//Toast::makeToast(2.0, "Loaded old game");
			//GUIManager::getInstance().guiDialog.showGUI("Do you want to continue the last game?", &okFunction1, false, &cancelFunction1,
				//NULL, "btnNewGame.png");
			btnSkip->setVisible(false);
			lbKnowRule->setVisible(false);
			btnNewGame->setVisible(false);
		}
		else
		{
			if (game->showHelp) {
				game->countHelp = 0;
				board->newGameTutorial();
				waitNextStep();
				
				CCUserDefault::sharedUserDefault()->setBoolForKey("showHelp", false);
				CCUserDefault::sharedUserDefault()->flush();
				btnNewGame->setVisible(false);
				btnSkip->setVisible(true);
				lbKnowRule->setVisible(true);
				btnSkip->normalImage->stopAllActions();
				btnSkip->normalImage->runAction(
					CCRepeatForever::create(
						CCSequence::create(
							CCScaleTo::create(0.2, 1.1),
							CCScaleTo::create(0.2, 1.0),
							NULL
						)
					)
				);
			}
			else {
				board->newGame();
				btnNewGame->setVisible(true);
				btnSkip->setVisible(false);
				lbKnowRule->setVisible(false);
			}
			
			updateScore(0);
		}
		progress->setVisible(false);
		bgProgress->setVisible(false);
		highscoreGroup->setMoney(game->highscore);
		if (score < game->highscore) {
			isNewBest = false;
		}
	}
	else
	{
		if (game->isPlayingTime)
		{
			board->loadGameTime();
			updateScore(game->saveScoreTime);

			//Toast::makeToast(2.0, "Loaded old game");
		}
		else
		{
			board->newGame();
			updateScore(0);
		}
		highscoreGroup->setMoney(game->highscoreTime);
		progress->setVisible(true);
		bgProgress->setVisible(true);
		btnNewGame->setVisible(true);
		btnSkip->setVisible(false);
		lbKnowRule->setVisible(false);
		newTimer();
		if (score < game->highscoreTime) {
			isNewBest = false;
		}
	}
	
	
	
	updateNextBall();
	updateViewBall();
	gameState = GameState::PLAY;
	canUndo = false;
	btnUndo->setEnable(canUndo);
	for (int i = 0; i < 9; i++)
	{
		string s = "";
		for (int j = 0; j < 9; j++) {
			arrayOldBall[i][j] = -1;
			saveBall[i][j] = board->arrayBall[i][j];
			//s = s + " " + GameUtility::toString(board->arrayBall[i][j]);

			arrayBall[i][j]->animationNewGame();
		}
	}
}

void GUILine::newTimer()
{
	if(typeMode == 0)
		return;
    progress->setVisible(true);
   
    progress->cleanup();
    progress->setScaleX(bgProgress->getScaleX());
	float time = 3 + board->getNumBall() * 0.08;
	CCLOG("Time %f ", time);
    progress->runAction(CCSequence::create(CCScaleTo::create(time, 0, progress->getScaleY()), CCCallFunc::create(this, callfunc_selector(GUILine::autoBiggerBall)), NULL));
}

void GUILine::callbackTimer()
{
    makeBiggerBall();
    checkEatPoint();
    newTimer();
}

void GUILine::showGui()
{
    BaseGUI::showGUI();
    setVisible(true);
    GUIManager::getInstance().addToListGui(this);

	int id = game->typeBall + 1;
	if (id > 5)
		id = 0;
	btnBall->normalImage->setImage(("btnBall_" + GameUtility::toString(id) + ".png").c_str(), true);
    
    board->loadGame();
    updateScore(game->saveScore);
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++) {
            arrayOldBall[i][j] = -1;
            saveBall[i][j] = board->arrayBall[i][j];
        }
    updateNextBall();
    updateViewBall();
    game->isPlaying = true;
    
    
    gameState = GameState::PLAY;
    canUndo = false;
    btnUndo->setEnable(canUndo);
}

void GUILine::showGuiWithMode(int typeMode)
{
	this->typeMode = typeMode;
    BaseGUI::showGUI();
	int id = game->typeBall + 1;
	int numBall = 5;
	if (game->isIOS())
		numBall = 6;
	if (id > numBall)
		id = 0;
	btnBall->normalImage->setImage(("btnBall_" + GameUtility::toString(id) + ".png").c_str(), true);
    setVisible(true);
    GUIManager::getInstance().addToListGui(this);
	if (typeMode == 0) {
		btnUndo->setPosition(btnSave->getPositionX() - btnSave->getWidth() * 1.1, btnUndo->getPositionY());
		btnSave->setVisible(true);
		btnBall->setVisible(true);
	}
	else {
		btnUndo->setPosition(btnSave->getPositionX() , btnUndo->getPositionY());
		btnSave->setVisible(false);
		btnBall->setVisible(false);
	}
	btnBall->setVisible(false);
	newGame();
	slider->setVisible(false);
	sliderBright->setVisible(false);
	btnNewGame->setVisible(true);
	btnTrophy->setVisible(true && !game->isIOS());
	btnTrophy->setVisible(false);

	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();
	float sY = size.height - btnBack->getHeight() * 0.7;
	float sX = size.width * 0.5;
	moveVertical(btnBack->normalImage->_img, 0, 400, 0);
	moveVertical(btnSound->normalImage->_img, 0, 400, 0.05);
	moveVertical(btnSave->normalImage->_img, 0, 400, 0.1);
	moveVertical(btnHelp->normalImage->_img, 0, 400, 0.13);
	moveVertical(btnUndo->normalImage->_img, 0, 400, 0.15);
	moveVertical(btnNewGame->normalImage->_img, 0, 400, 0.2);
	moveVertical(btnBall->normalImage->_img, 0, 400, 0.3);
	moveVertical(btnResize->normalImage->_img, 0, 400, 0.35);
	moveVertical(btnTrophy->normalImage->_img, 0, 400, 0.4);
	bg->_img->setOpacity(0);
	bg->_img->runAction(CCFadeIn::create(0.5));
}

void GUILine::showGuiWithData(int data[81], int score)
{
	effect->setVisible(false);
	effIcon->setVisible(false);
	labelUndo->setString((GameUtility::toString(game->numUndo) + " Undo").c_str());
	labelScore->setVisible(false);
	for (int i = 0; i < arrayEffectBall.size(); i++) {
		arrayEffectBall.at(i)->setVisible(false);
	}
	labelScore->setVisible(false);
	//game->isPlaying = false;
			board->loadGameData(data);
			game->saveScore = score;
			updateScore(game->saveScore);
		
		progress->setVisible(false);
		bgProgress->setVisible(false);
		highscoreGroup->setMoney(game->highscore);

	for (int i = 0; i < 9; i++)
	{
		string s = "";
		for (int j = 0; j < 9; j++) {
			arrayOldBall[i][j] = -1;
			saveBall[i][j] = board->arrayBall[i][j];
			s = s + " " + GameUtility::toString(board->arrayBall[i][j]);
		}
	}

	updateNextBall();
	updateViewBall();
	gameState = GameState::PLAY;
	canUndo = false;
	btnUndo->setEnable(canUndo);
}

void GUILine::updateScore( int score )
{
	this->score = score;
	scoreGroup->setMoney(this->score);

    if(typeMode == 0)
    {
        if(this->score > game->highscore)
        {
            
            game->highscore = this->score;
            CCUserDefault::sharedUserDefault()->setIntegerForKey("highscore", game->highscore);
            CCUserDefault::sharedUserDefault()->flush();
            highscoreGroup->setMoney(game->highscore);
        }
        
    }
    else
    {
        if(this->score > game->highscoreTime)
        {
            game->highscoreTime = this->score;
            CCUserDefault::sharedUserDefault()->setIntegerForKey("highscoreTime", game->highscoreTime);
            CCUserDefault::sharedUserDefault()->flush();
            highscoreGroup->setMoney(game->highscoreTime);
        }
        
    }
}

void GUILine::showFinishTutorial() {
	btnSkip->setVisible(false);
	btnNewGame->setVisible(true);
	GUIManager::getInstance().guiDialog.showGUI(CCLocalizedString("FINISH_TUTORIAL").c_str(), NULL, true);
}

bool GUILine::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint point = pTouch->getLocation();

	if (point.y < startY)
		return BaseGUI::onTouchBegan(pTouch, pEvent);
	int row = (int)((point.y - startY) / sizeCell);
	int column = (int)((point.x - startX) / sizeCell);
	if (row < 0 || column < 0 || row >= 9 || column >= 9 || (gameState != GameState::NORMAL_GAME && gameState != GameState::PLAY && gameState != GameState::TOUCH))
		return BaseGUI::onTouchBegan(pTouch, pEvent);

	if (game->showHelp && typeMode == 0) {
		if (game->countHelp < 0 || game->countHelp > 10) {
			game->showHelp = false;
			CCUserDefault::sharedUserDefault()->setBoolForKey("showHelp", false);
			CCUserDefault::sharedUserDefault()->flush();
			return false;
		}
		if (row != game->arrayTutorial[game->countHelp]->row || column != game->arrayTutorial[game->countHelp]->column)
			return BaseGUI::onTouchBegan(pTouch, pEvent);
		game->countHelp++;
		if (game->countHelp < 6) {
			waitNextStep();
		}
		else {
			iconHand->setVisible(false);
			runAction(CCSequence::create(CCDelayTime::create(1.0), CCCallFunc::create(this, callfunc_selector(GUILine::showFinishTutorial)), NULL));
			
			game->showHelp = false;
			game->countHelp = -1;
		}
	}
	if (board->arrayBall[row][column] >= 1 && board->arrayBall[row][column] <= 7) {
		if (arrayBall[row][column]->state == BallState::JUMP) {
			arrayBall[row][column]->setState(BallState::NORMAL);
			gameState = GameState::PLAY;
			currentRow = -1;
			
		} else {
			if (currentRow >= 0)
				arrayBall[currentRow][currentColumn]->setState(BallState::NORMAL);
			arrayBall[row][column]->setState(BallState::JUMP);
			board->updatePoint(column, row);
            gameState = GameState::TOUCH;
			currentRow = row;
			currentColumn = column;
			CCLOG("XONG XUOI ");
		}
		GameSound::playChooseBall();
	} else {
		if (gameState == GameState::TOUCH) {

			board->setWay(row, column);
			if (board->arrayPoint.size() > 0) {
				gameState = GameState::MOVE;
				SPEED = 100 / board->arrayPoint.size();
				ballMove->setVisible(true);
				int id = board->arrayBall[currentRow][currentColumn] - 1;
				if (id < 0 || id > 6) {
					if (currentRow >= 0 && currentRow <= 8 && currentColumn >= 0 && currentColumn <= 8)
						arrayBall[currentRow][currentColumn]->setState(BallState::NORMAL);
					gameState = GameState::PLAY;
					currentRow = -1;
					return BaseGUI::onTouchBegan(pTouch, pEvent);
				}
				string s = GameUtility::getResourceBall(board->arrayBall[currentRow][currentColumn]);
				ballMove->setImage(s.c_str(), false);
				ballMove->setWidth(sizeCell * game->scaleBall);
				ballMove->setHeight(sizeCell * game->scaleBall);
				ballMove->setPositionX(arrayBall[currentRow][currentColumn]->getPositionX());
				ballMove->setPositionY(arrayBall[currentRow][currentColumn]->getPositionY());
				//ballMove->setVisible(false);

				_streak->reset();
				Texture2D *texture = _director->getTextureCache()->addImage("480_800/" + s);
				_streak->setTexture(texture);
				_streak->setVisible(true);
				_streak->setPosition(ballMove->getPosition());
				GameSound::playMove();

				/*for (int i = 0; i < 4; i++) {
					arrayMoveBall[i]->setImage(s.c_str(), false);
					arrayMoveBall[i]->setVisible(false);
					arrayMoveBall[i]->runAction(CCSequence::create(
						CCDelayTime::create(0.02 * i),
						CCShow::create(),
						NULL
					));
					arrayMoveBall[i]->setPosition(ballMove->getPosition());
					arrayMoveBall[i]->setWidth(sizeCell * game->scaleBall);
					arrayMoveBall[i]->setHeight(sizeCell * game->scaleBall);
					arrayMoveBall[i]->getImg()->setOpacity(100 + 40 * (3 - i));
				}*/

				// luu lai mang gia tri
				for (int i = 0; i < 9; i++)
					for (int j = 0; j < 9; j++) {
						saveBall[i][j] = board->arrayBall[i][j];
					}
					SPEED = 0.1f / board->arrayPoint.size();
					doMoveBall();
					if(typeMode == 0)
						game->isPlaying = true;
					else
					{
						game->isPlayingTime = true;
					}
					arrayBall[currentRow][currentColumn]->setVisible(false);

					int saveValue = board->arrayBall[currentRow][currentColumn];
					saveValue2 = board->arrayBall[row][column];
					board->updateValue(currentRow, currentColumn, -1);

					board->updateValue(row, column, saveValue);

					arrayOldBall[currentRow][currentColumn] = -1;
					arrayOldBall[row][column] = board->arrayBall[currentRow][currentColumn];
					currentRow = -1;

					nextRow = row;
					nextColumn = column;
					
			} else {
				GameSound::playFail();
				//this->stopAllActions();
				//this->runAction(CCSequence::create(CCRotateTo::create(0.1, 1), CCRotateTo::create(0.1, 0), NULL));
				for (int i = 0; i < 9; i++)
					for (int j = 0; j < 9; j++) {
						if (board->arrayBall[i][j] >= 0 && board->arrayBall[i][j] < 8) {
							arrayBall[i][j]->effectVibrate();
						}
					}
			}
		}
	}
	return BaseGUI::onTouchBegan(pTouch, pEvent);
}

void GUILine::genBall(int i, int j) {
	if (i < 0 || i > 8 || j < 0 || j > 8)
		return;
	int id = ((board->arrayBall[i][j] - 1) % 7);

	if (id < 0 || id >= 7)
		return;
	
	string s = GameUtility::getResourceBall(id + 1);
	arrayBall[i][j]->setImage(s.c_str());
	arrayBall[i][j]->setVisible(true);
	if(board->arrayBall[i][j] > 7)
	{
		arrayBall[i][j]->setState(BallState::SMALL);
	}
	else
	{
		arrayBall[i][j]->setState(BallState::NORMAL);
	}
}

void GUILine::updateViewBall() {
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++) {
			if (board->arrayBall[i][j] > 0 && board->arrayBall[i][j] != arrayOldBall[i][j]) {
				genBall(i, j);
				arrayOldBall[i][j] = board->arrayBall[i][j];
			} else if (board->arrayBall[i][j] <= 0)
				arrayBall[i][j]->setVisible(false);
		}

}

void GUILine::updateNextBall() {
	int count = 0;
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++) {
			if (board->arrayBall[i][j] >= 8) {
				string s = "count " + GameUtility::toString(count) + " id " + GameUtility::toString(board->arrayBall[i][j] - 7) + " resource " + GameUtility::getResourceBall(board->arrayBall[i][j] - 7);
				cocos2d::log("data %s ", s.c_str());
				arrayNext[count]->setImage(GameUtility::getResourceBall(board->arrayBall[i][j] - 7).c_str(), false);
				arrayNext[count]->setWidth(sizeCell * 0.75f);
				arrayNext[count]->setHeight(sizeCell * 0.75f);
				arrayNext[count]->setVisible(true);
				count++;
			}
		}

		for (int i = count; i < 3; i++) {
			arrayNext[i]->setVisible(false);
		}
}

void GUILine::checkGenNextBall() {
	board->result.clear();
	for (int i = 0; i < arrayChange.size(); i++) {
		board->getListBall(arrayChange.at(i)->y, arrayChange.at(i)->x);
	}

	if (board->result.size() < 5)
		genNext = true;
	else
		genNext = false;
}

void okEndFunction1()
{
	GUIManager::getInstance().guiLine.newGame();
}

void cancelEndFunction1()
{
	if (GUIManager::getInstance().guiLine.typeMode == 0)
		JNIUtils::submitScore(game->highscore, GUIManager::getInstance().guiLine.typeMode);
	else
		JNIUtils::submitScore(game->highscoreTime, GUIManager::getInstance().guiLine.typeMode);
	GUIManager::getInstance().guiLine.newGame();
}

void GUILine::onFinish() {
	// TODO Auto-generated method stub
	if (GUIManager::getInstance().guiLine.valueSaveBall >= 8) {
		int row = GUIManager::getInstance().guiLine.positionSaveBall / 9;
		int column = GUIManager::getInstance().guiLine.positionSaveBall % 9;
		GUIManager::getInstance().guiLine.board->updateValue(row, column, GUIManager::getInstance().guiLine.valueSaveBall);
		GUIManager::getInstance().guiLine.updateNextBall();
		GUIManager::getInstance().guiLine.updateViewBall();
	}
}

void GUILine::doMoveBall() {
	
	if (board->arrayPoint.size() > 0) {
		int nextRow = board->arrayPoint.at(board->arrayPoint.size() - 1)->y;
		int nextColumn = board->arrayPoint.at(board->arrayPoint.size() - 1)->x;
		board->arrayPoint.erase(board->arrayPoint.begin() + board->arrayPoint.size() - 1);

		ballMove->cleanup();
		Vec2 p = arrayBall[nextRow][nextColumn]->getPosition();
		_streak->runAction(CCSequence::create(CCMoveTo::create(SPEED, p), NULL));
		ballMove->runAction(CCSequence::create(CCMoveTo::create(SPEED, p)
			, CCCallFunc::create(this, callfunc_selector(GUILine::doMoveBall)), NULL));

		//for (int i = 0; i < 4; i++) {
		//	//arrayMoveBall[i]->setVisible(false);
		//	arrayMoveBall[i]->runAction(CCSequence::create(
		//		CCDelayTime::create(0.02 * i),
		//		CCShow::create(),
		//		CCMoveTo::create(SPEED, p),
		//		NULL
		//	));
		//}
	} else {
		ballMove->setVisible(false);
		genBall(nextRow, nextColumn);
		checkAfterMove();
		/*for (int i = 0; i < 4; i++) {
			arrayMoveBall[i]->setVisible(false);
		}*/
	}
}

void GUILine::checkAfterMove() {
	// check xem co kha nang an quan ko, neu co thi ko lam bong
	// lon len
	arrayChange.clear();
	arrayChange.push_back(new PointGame(nextColumn, nextRow));
	checkGenNextBall();
	if (saveValue2 >= 8) {
		// thay the vi tri bong nho sang cho khac
		if (genNext) {
			board->randomReplace(saveValue2);
			updateViewBall();
			valueSaveBall = 0;
		}
		else {
			valueSaveBall = saveValue2;
			positionSaveBall = nextRow * 9 + nextColumn;
		}
	}
	else {
		valueSaveBall = 0;
	}
	if (genNext) {
		makeBiggerBall();
		this->runAction(CCSequence::create(CCDelayTime::create(0.16f), CCCallFunc::create(this, callfunc_selector(GUILine::checkAfterMove2)), NULL));
	}
	else
	{
		newTimer();
		checkAfterMove2();
	}
	canUndo = true;
	btnUndo->setEnable(canUndo);
}

void GUILine::checkAfterMove2() {
	CCLOG("After move 2");
	if (genNext)
		board->randomNext();
	updateNextBall();
	updateViewBall();
	if (gameState == GameState::TOUCH) {
		if (currentRow >= 0 && currentColumn >= 0 && board->arrayBall[currentRow][currentColumn] >= 0) {

		}
		else {
			gameState = GameState::PLAY;
		}
	}
	else {
		gameState = GameState::PLAY;
	}
	
	checkEatPoint();
	checkEndGame();
}


void GUILine::makeBiggerBall() {
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++) {
			if (board->arrayBall[i][j] >= 8) {
				arrayBall[i][j]->setState(BallState::BIGGER);
				board->updateValue(i, j, board->arrayBall[i][j] - 7);
				arrayChange.push_back(new PointGame(j, i));
			}
		}

}

void GUILine::autoBiggerBall()
{
	arrayChange.clear();
	makeBiggerBall();
	this->runAction(CCSequence::create(CCDelayTime::create(0.16f), CCCallFunc::create(this, callfunc_selector(GUILine::checkAfterMove2)), NULL));
	genNext = true;
	//	board->randomNext();
	//	updateNextBall();
	//	updateViewBall();
	////	gameState = GameState::PLAY;
	//	checkEatPoint();
		canUndo = false;
		btnUndo->setEnable(false);
	//	GameSound::playMove();
}

void GUILine::checkEndGame() {
	if (board->checkEndGame())
	{
		if (typeMode == 0)
		{
			game->isPlaying = false;
			CCUserDefault::sharedUserDefault()->setBoolForKey("isPlaying", false);
			CCUserDefault::sharedUserDefault()->setBoolForKey("isPlayingNormal", false);
		}
		else
		{
			game->isPlayingTime = false;
			CCUserDefault::sharedUserDefault()->setBoolForKey("isPlayingTime", false);
		}
		CCUserDefault::sharedUserDefault()->flush();
		gameState = GAME_OVER;
		progress->cleanup();
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				//arrayBall[i][j]->effectEndGame(0.03 * i + 0.02 * j);
				arrayBall[i][j]->effectEndGame(0.01 * i * 7 + 0.01 * j);
			}
		}
		runAction(CCSequence::create(
			CCDelayTime::create(1.2),
			CCCallFunc::create(this, callfunc_selector(GUILine::callbackEffectEndGame)),
			NULL
		));
		canUndo = false;
		btnUndo->setEnable(canUndo);
	}
	else
	{
		newTimer();
	}
}

void GUILine::callbackEffectEndGame()
{
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++) {
			arrayBall[i][j]->setVisible(false);
			if (GameUtility::getRandom() > 0.5) {
				showParticle(arrayBall[i][j]->getPositionX(), arrayBall[i][j]->getPositionY(), board->arrayBall[i][j], 0);
			}
		}
	runAction(CCSequence::create(
		CCDelayTime::create(1.0),
		CCCallFunc::create(this, callfunc_selector(GUILine::callbackEffectEndGame1)),
		NULL
	));
}

void GUILine::callbackEffectEndGame1()
{
	if (typeMode == 0)
		GUIManager::getInstance().guiResult.showGUI(score, game->highscore);
	else
		GUIManager::getInstance().guiResult.showGUI(score, game->highscoreTime);
}

int GUILine::convertIdBall(int id)
{
	return game->arrayBall[id];
}

void GUILine::checkEatPoint() {
	oldScore = score;
	board->result.clear();
	for (int i = 0; i < arrayChange.size(); i++) {
		board->getListBall(arrayChange.at(i)->y, arrayChange.at(i)->x);
	}

	CCPoint posScore;
	int count = 0;
	for (int i = 0; i < board->result.size(); i++) {
		arrayBall[board->result.at(i)->y][board->result.at(i)->x]->setState(BallState::DISAPPEAR);
		showParticle(arrayBall[board->result.at(i)->y][board->result.at(i)->x]->rootX, arrayBall[board->result.at(i)->y][board->result.at(i)->x]->rootY, arrayOldBall[board->result.at(i)->y][board->result.at(i)->x], count * 0.1);
		count++;
		if (i == 2) {
			posScore.x = arrayBall[board->result.at(i)->y][board->result.at(i)->x]->rootX;
			posScore.y = arrayBall[board->result.at(i)->y][board->result.at(i)->x]->rootY;
		}
		board->updateValue(board->result.at(i)->y, board->result.at(i)->x, -1);
		arrayOldBall[board->result.at(i)->y][board->result.at(i)->x] = -1;
		if(i == 0)
		{
			arrayBall[board->result.at(i)->y][board->result.at(i)->x]->isAct = true;
		}
		else
		{
			arrayBall[board->result.at(i)->y][board->result.at(i)->x]->isAct = false;
		}
		
	}
	int addScore = 0;
	int typeEffect = 0;
    onFinish();
	if (board->result.size() >= 5) {
		switch (board->result.size()) {
		case 5:
			{
				GameSound::playScore1();
				addScore = 5;
			}
			
			break;
		case 6:
			{
				GameSound::playScore2();
				addScore = 12;
				typeEffect = 1;
			}
			
			break;
		case 7:
			{
				GameSound::playScore3();
				addScore = 21;
				typeEffect = 2;
			}
			
			break;
		case 8:
			{
				GameSound::playScore4();
				addScore = 32;
				typeEffect = 3;
			}
			
			break;
		case 9:
			{
				GameSound::playScore5();
				addScore = 45; typeEffect = 3;
			}
			
			break;
		case 10:
			{
				GameSound::playScore6();
				addScore = 60; typeEffect = 3;
			}
			
			break;
		case 11:
			{
				GameSound::playScore6();
				addScore = 77; typeEffect = 3;
			}
			
			break;
		case 12:
			{
				GameSound::playScore6();
				addScore = 96; typeEffect = 3;
			}
			
			break;
		case 13:
			{
				GameSound::playScore6();
				addScore = 117; typeEffect = 3;
			}
			
			break;
		case 14:
			{
				GameSound::playScore6();
				addScore = 140; typeEffect = 3;
			}
			
			break;
		default:
			GameSound::playScore6();
			addScore = 200; typeEffect = 3;
			break;
		}
		if (addScore > 0) {
			checkIsNewBest(addScore);
			updateScore(score + addScore);
			labelScore->setVisible(true);
			labelScore->stopAllActions();
			labelScore->setOpacity(0);
			labelScore->setString(("+" + GameUtility::toString(addScore)).c_str());
			labelScore->setPosition(Vec2(scoreGroup->getPositionX() + scoreGroup->getContentSize().width * 0.5, scoreGroup->getPositionY() + scoreGroup->getContentSize().height * 0.5));
			//labelScore->runAction(CCSpawn::create(CCFadeOut::create(0.6), CCSequence::create(CCEaseBackOut::create(CCMoveBy::create(0.6, ccp(0, 50))), CCHide::create(), NULL), NULL));
			labelScore->runAction(CCSequence::create(CCDelayTime::create(0.8), CCFadeIn::create(0.5), CCEaseBackOut::create(CCMoveBy::create(0.5, ccp(0, 50))), CCFadeOut::create(0.5), CCHide::create(), NULL));

			if (typeEffect > 0 && game->showAnimation) {
				effect->setVisible(true);
				effect->setImage(("effect_" + GameUtility::toString(typeEffect) + ".png").c_str(), true);
				effect->stopAllActions();
				effect->setOpacity(255);
				effect->setPosition(bg->getPosition().x, bg->getPositionY() - 50);
				effect->runAction(CCSequence::create(CCEaseBackOut::create(CCMoveBy::create(0.5, ccp(0, 50))), CCDelayTime::create(1.0), CCFadeOut::create(0.5), NULL));
				effect->runAction(CCFadeIn::create(0.4));
				effect->runAction(CCSequence::create(CCScaleTo::create(0.5, 1.1), CCScaleTo::create(0.3, 1.0), NULL));

				Layer *layer = layerMgr->getLayerByIndex(LAYER_EFFECT_GAME);
				ParticleEffect *effect1 = new ParticleEffect();
				effect1->create("particles/particle_texture.plist", layer);
				effect1->particle->setPosition(bg->getPosition().x, bg->getPositionY() - bg->getRealHeight() * 0.55);
				CCSize size = CCDirector::sharedDirector()->getWinSize();
				effect1->particle->setPosition(size.width * 0.5, bg->getPositionY() - bg->getRealHeight() * 0.5);
				effect1->particle->setAutoRemoveOnFinish(true);
				effect1->particle->setBlendAdditive(false);

				effIcon->setVisible(true);
				effIcon->gotoAndPlay("1", -1, -1, 1);
				effIcon->runAction(CCSequence::create(CCDelayTime::create(2.5), CCHide::create(), NULL));
			}
		}
	}
	savePreference();
}


void GUILine::updateHighScore() {
	
}

void GUILine::undo() {
	board->loadGame(saveBall);
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++) {
			arrayOldBall[i][j] = -1;
		}
		updateNextBall();
		updateViewBall();
		updateScore(oldScore);
}

void GUILine::showParticle( float posX, float posY , int id, float time)
{
	if (id < 1 || id > 7)
		return;

	if (game->showAnimation) {
		string s = GameUtility::getResourceBall(id);
		CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();
		GameImage* ball = getEffectBall();
		ball->setImage(s.c_str(), false);
		ball->setOpacity(255);
		ball->setWidth(sizeCell * 0.8);
		ball->setHeight(sizeCell * 0.8);
		ball->setPosition(posX, posY);
		CCPoint center = Vec2(size.width * (GameUtility::getRandom() * 0.8 + 0.2), size.height * (GameUtility::getRandom() * 0.8 + 0.2));
		CCPoint end = Vec2(scoreGroup->getPosition().x + scoreGroup->getContentSize().width * 0.5, scoreGroup->getPosition().y + scoreGroup->getContentSize().height * 0.5);

		ccBezierConfig bezier;
		bezier.controlPoint_1 = Vec2(posX, posY);
		bezier.controlPoint_2 = center;
		bezier.endPosition = end;
		ball->runAction(CCSequence::create(
			CCDelayTime::create(time),
			CCEaseSineInOut::create(CCBezierTo::create(0.5, bezier)),
			CCScaleTo::create(0.2, ball->getScaleX() * 1.2),
			CCScaleTo::create(0.2, 0),
			CCHide::create(),
			NULL
		));
	}
	else {
		Layer *layer = layerMgr->getLayerByIndex(LAYER_EFFECT_GAME);
		ParticleEffect *effect = new ParticleEffect();
		effect->create(("particles/egg" + GameUtility::toString(id) + ".plist").c_str(), layer);
		string s = "480_800/" + GameUtility::getResourceBall(id);
		effect->particle->setTexture(TextureCache::sharedTextureCache()->addImage(s.c_str()));
		effect->particle->setPosition(posX, posY);
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		float scale = (size.width / DEFAULT_SCREEN_WIDTH) > (size.height / DEFAULT_SCREEN_HEIGHT) ? (size.width / DEFAULT_SCREEN_WIDTH) : (size.height / DEFAULT_SCREEN_HEIGHT);
		effect->particle->setScale(scale);
		effect->particle->setAutoRemoveOnFinish(true);
		effect->particle->setBlendAdditive(false);
	}
}

GameImage* GUILine::getEffectBall() {
	int i;
	GameImage* ball;
	for (i = 0; i < arrayEffectBall.size(); i++) {
		if (!arrayEffectBall.at(i)->isVisible()) {
			ball = arrayEffectBall.at(i);
			break;
		}
	}
	if (i == arrayEffectBall.size()) {
		ball = new GameImage(GameUtility::getResourceBall(1).c_str(), false);
		this->addChild(ball);
		ball->setWidth(sizeCell * 0.8);
		ball->setHeight(sizeCell * 0.8);
		arrayEffectBall.push_back(ball);
	}
	ball->setVisible(true);
	return ball;
}

void GUILine::act()
{
	
}


string GUILine::getResourceBall() {
	return "lineBall_" + GameUtility::toString(game->typeBall) + "_";
}

void GUILine::savePreference()
{
	CCLOG("SAVE PRE 1");
	if (game->isPlaying || game->isPlayingTime)
	{
		string s = "";
		int index = 0;
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
			{
				if (i == 0 && j == 0)
				{
					s = s + GameUtility::toString(board->arrayBall[i][j]);
				}
				else
				{
					s = s + "," + GameUtility::toString(board->arrayBall[i][j]);
				}
				if (typeMode == 0)
					game->data[i * 9 + j] = board->arrayBall[i][j];
				else
					game->dataTime[i * 9 + j] = board->arrayBall[i][j];
			}
		if (typeMode == 0)
		{
			CCLOG("VAO DAY NAO ");
			CCUserDefault::sharedUserDefault()->setBoolForKey("isPlaying", true);
			CCUserDefault::sharedUserDefault()->setBoolForKey("isPlayingNormal", true);
			CCUserDefault::sharedUserDefault()->setIntegerForKey("score", score);
			CCUserDefault::sharedUserDefault()->setStringForKey("data", s);
			CCUserDefault::sharedUserDefault()->setStringForKey("dataNormal", s);
			CCLOG("PUT DATAA %s ", s.c_str());
			game->saveScore = score;
		}
		else
		{
			CCUserDefault::sharedUserDefault()->setBoolForKey("isPlayingTime", true);
			CCUserDefault::sharedUserDefault()->setIntegerForKey("scoreTime", score);
			CCUserDefault::sharedUserDefault()->setStringForKey("dataTime", s);
			game->saveScoreTime = score;
		}

	}
	else
	{
		if (typeMode == 0) {
			CCUserDefault::sharedUserDefault()->setBoolForKey("isPlaying", false);
			CCUserDefault::sharedUserDefault()->setBoolForKey("isPlayingNormal", false);
		}
		else
			CCUserDefault::sharedUserDefault()->setBoolForKey("isPlayingTime", false);
	}

	CCUserDefault::sharedUserDefault()->flush();
}

void GUILine::showHand(CCPoint pos) {
	iconHand->getImg()->stopAllActions();
	iconHand->setPosition(pos);
	iconHand->setVisible(true);
	iconHand->getImg()->setOpacity(0);
	iconHand->getImg()->runAction(CCFadeIn::create(0.5));
	iconHand->stopAllActions();
	iconHand->runAction(CCRepeatForever::create(CCSequence::create(CCScaleTo::create(0.2, 1.2), CCScaleTo::create(0.2, 1.0), NULL)));
}
	 
void GUILine::doTutorial() {
	if (game->countHelp >= 6 || game->countHelp < 0)
	{
		game->showHelp = false;
		return;
	}
	TutorialData* data = game->arrayTutorial[game->countHelp];
	if (data->row >= 0) {
		int posX = (data->column + 0.5) * (sizeCell)+startX + iconHand->getWidth() * 0.1;
		int posY = data->row * sizeCell + startY - iconHand->getHeight() * 0.3;
		showHand(ccp(posX, posY));
		showToast1(data->content.c_str());
	}
	else {
		iconHand->setVisible(false);
		showToast2(data->content.c_str());
		game->countHelp++;
		waitNextStep();

	}
}

void GUILine::showToast1(const char* content) {
	Toast::makeToast(5, content);
}

void GUILine::showToast2(const char* content) {
	Toast::makeToast(2, content);
}

void GUILine::waitNextStep() {
	iconHand->stopAllActions();
	iconHand->getImg()->runAction(CCFadeOut::create(0.3));
	iconHand->runAction(CCSequence::create(CCDelayTime::create(game->arrayTutorial[game->countHelp]->timeDelay), CCCallFunc::create(this, callfunc_selector(GUILine::doTutorial)), NULL));
}

void GUILine::checkIsNewBest(int add)
{
	if (isNewBest)
		return;
	if (typeMode == 0) {
		if (!isNewBest && this->score <= game->highscore && game->highscore > 0 && this->score + add > game->highscore) {
			// show Effect Best Score
			isNewBest = true;
			showEffectLabel("480_800/iconNewBest.png");
			GameSound::playWin();
		}
	}
	else {
		if (!isNewBest && this->score <= game->highscoreTime && game->highscoreTime > 0 && this->score + add > game->highscoreTime) {
			// show Effect Best Score
			isNewBest = true;
			showEffectLabel("480_800/iconNewBest.png");
			GameSound::playWin();
		}
	}
}


void GUILine::showEffectLabel(string s)
{
	layerColor->setVisible(true);
	layerColor->setOpacity(0);
	layerColor->runAction(
		CCSequence::create(
			CCFadeTo::create(0.5, 100),
			CCDelayTime::create(2.5),
			CCFadeOut::create(0.5),
			CCHide::create(),
			NULL
		)
	);

	auto eff = DBCCFactory::getInstance()->buildArmatureNode("tile_light");
	if (eff) {
		this->addChild(eff);
		eff->setLocalZOrder(2);
		eff->setPosition(bg->getPosition());
		eff->gotoAndPlay("run", 0.5, -1, 1);
		eff->setCompleteListener([](dragonBones::DBCCArmatureNode* armature) {
			armature->removeFromParent();
		});
	}
	imgNewBest->setVisible(true);
	imgNewBest->setPosition(bg->getPosition());
	imgNewBest->setOpacity(0);
	imgNewBest->setScale(6);
	imgNewBest->runAction(Sequence::create(
		EaseBounceOut::create(ScaleTo::create(0.6, 1.5)),
		DelayTime::create(2.0),
		FadeOut::create(0.5),
		Hide::create(),
		NULL
	));
	imgNewBest->runAction(FadeIn::create(0.5));
}

void GUILine::loadAdsFull()
{
	runAction(CCSequence::create(
		CCDelayTime::create(1.0),
		CCCallFunc::create(this, callfunc_selector(GUILine::callbackLoadAdsFull)),
		NULL
	));
}
void GUILine::callbackLoadAdsFull()
{
//	JNIUtils::loadAdsFull();
}

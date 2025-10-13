#include "GUIBubble.h"
#include "Engine/Utility/ScreenUtils.h"
#include "Engine/GlobalVar.h"
#include "Engine/Utility/LocalizedString.h"
#include "../GUIManager.h"
#include "../Utility/JNIUtils.h"
#include "../Data/GlobalData.h"
#include "../Utility/GameUtility.h"
#include "Game/Data/GlobalData.h"
#include "Engine/Utility/CStringUtils.h"
#include "../Utility/GameSound.h"
#include "Engine/GUI/ParticleEffect.h"
#include "../Utility/Toast.h"
#define BACKGROUND_RES "loading/bgPortalCenterZP.jpg"
#define PROGRESS_RES "loading/bgProgress.png"
#define ICON_GAME "loading/iconGame.png"
#define BG_PROGRESS "loading/black.png"

#define BTN_BACK_ID 1
#define BTN_SOUND_ID 2
#define BTN_UNDO_ID 3
#define BTN_ACHIEVEMENT_ID 4

#define BTN_DOWNLOAD 5

GUIBubble::GUIBubble(void) : BaseGUI()
{
	BaseGUI();

}


GUIBubble::~GUIBubble(void)
{
}


void GUIBubble::initGUI(){

	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();
// 	CCTextureCache::sharedTextureCache()->addImage(ScreenUtils::fileFull(BACKGROUND_RES).c_str());
// 	CCTextureCache::sharedTextureCache()->addImage(ScreenUtils::fileFull(PROGRESS_RES).c_str());
// 	CCTextureCache::sharedTextureCache()->addImage(ScreenUtils::fileFull("loading/LG2.png").c_str());
// 	CCTextureCache::sharedTextureCache()->addImage(ScreenUtils::fileFull("loading/LG2.png").c_str());
	//Image *bg1 = addImage("loading/LG2.png");
	//bg1->setWidth(size.width);
	//bg1->setHeight(size.height);
	//bg1->getImg()->runAction(CCSequence::create(CCFadeIn::create(0.8f), CCDelayTime::create(.8f), CCFadeOut::create(0.8f), CCCallFunc::create(this, callfunc_selector(GUIBubble::callBackSplash)), NULL));
	//runAction(CCSequence::create(CCDelayTime::create(0.1f), CCCallFunc::create(this, callfunc_selector(GUIBubble::callBackSplash)), NULL));
	//bg1->setPos(size.width / 2, size.height / 2);
	callBackSplash();
	
}

void GUIBubble::onBackKey(){
	game->showHelpBubble = false;
	if (GUIManager::getInstance().isCallBackPress == false && GUIManager::getInstance().getLastGui() == this)
	{
		//        if (supportGame == 1) {
		//            game->endGame();
		//        }
		//        else {
		if (game->isPlayingBubble || game->isPlayingTime)
		{
			string s = "";
			int index = 0;
			for (int i = 0; i < NUM_ROW_GAME; i++)
				for (int j = 0; j < NUM_COLUMN_GAME; j++)
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
						game->dataBubble[i * NUM_COLUMN_GAME + j] = board->arrayBall[i][j];
					else
						game->dataTime[i * NUM_COLUMN_GAME + j] = board->arrayBall[i][j];
				}
			string sRand = "";
			for (int i = 0; i < MAX_NEXT; i++)
			{
				if (i < board->numRand)
				{
					sRand = sRand + GameUtility::toString(board->arrayNext[i]);
				}
				else sRand = sRand + "0";
			}
			if (typeMode == 0)
			{
				CCUserDefault::sharedUserDefault()->setBoolForKey("isPlayingBubble", true);
				CCUserDefault::sharedUserDefault()->setIntegerForKey("scoreBubble", score);
				CCUserDefault::sharedUserDefault()->setStringForKey("dataBubble", s);
				CCUserDefault::sharedUserDefault()->setStringForKey("saveRandBubble", sRand);
				game->saveScoreBubble = score;
			}
			else
			{
				/*CCUserDefault::sharedUserDefault()->setBoolForKey("isPlayingTime", true);
				CCUserDefault::sharedUserDefault()->setIntegerForKey("scoreTime", score);
				CCUserDefault::sharedUserDefault()->setStringForKey("dataTime", s);
				CCUserDefault::sharedUserDefault()->setStringForKey("saveRandTime", sRand);
				game->saveScoreTime = score;*/
			}

		}
		else
		{
			if (typeMode == 0)
				CCUserDefault::sharedUserDefault()->setBoolForKey("isPlayingBubble", false);
			else
				CCUserDefault::sharedUserDefault()->setBoolForKey("isPlayingTime", false);
		}

		CCUserDefault::sharedUserDefault()->flush();

		GUIManager::getInstance().removeAllGui();
		GUIManager::getInstance().showGui(&GUIManager::getInstance().guiMinigames);
		GUIManager::getInstance().isCallBackPress = true;
	}
}



void GUIBubble::update()
{
// 	if(isUpdate)
// 	{
// 		for(int i = 0; i < 9; i++)
// 			for(int j = 0; j < 9; j++)
// 			{
// 				arrayBall[i][j]->update();
// 			}
// 	}
}
void okEndGame1Bubble()
{
    game->endGame();
}

void GUIBubble::onButtonRelease(int buttonID, CCTouch* touch)
{
	switch (buttonID)
	{
	case BTN_BACK_ID:
		{
			onBackKey();
		}
		
		break;
	case BTN_DOWNLOAD:
	{
		if (game->isIOS())
			JNIUtils::openApp("https://apps.apple.com/app/id6448207771");
		else
			JNIUtils::openApp("com.bcsofts.bubbleConnect");
	}
	break;
	case BTN_SOUND_ID:
		{
			game->music = !game->music;
			if(game->music)
			{
				btnSound->normalImage->setImage("gameBubble/btnSoundOn.png");
			}
			else
			{
				btnSound->normalImage->setImage("gameBubble/btnSoundOff.png");
			}

			CCUserDefault::sharedUserDefault()->setBoolForKey("music", game->music);
			CCUserDefault::sharedUserDefault()->flush();

			
		}
		break;
	case BTN_UNDO_ID:
		{
			if(board->level < 2)
			{
				if(canUndo)
				{
					undo();
					canUndo = false;
					btnUndo->setEnable(canUndo);
					
				}
			}
		}
		break;
       
		case BTN_ACHIEVEMENT_ID:
			if(board->level < 2)
				//JNIUtils::openLeaderboard(board->level, (board->level == 0) ? game->highscore : game->highscoreTime);
			break;
        default:
		break;
	}
}

void GUIBubble::callBackSplash()
{
	BaseGUI::initGUI();
	isUpdate = true;
	
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();

	GameImage* background = addImage("background.jpg");
	background->setWidth(size.width);
	background->setHeight(size.height);
	background->setPos(size.width / 2, size.height / 2);
	//background->setColor(ccc3(30, 30, 30));
    //background->setVisible(false);

	btnBack = addButton(BTN_BACK_ID, "btnBack.png");
	btnBack->setPosition(size.width - btnBack->getWidth() * 0.6f, size.height - btnBack->getHeight() * 0.6f);
    
    if (game->isIOS() && size.width / size.height < 11.0 / 20.0)
        btnBack->setPosition(size.width - btnBack->getWidth() * 0.6f, size.height - btnBack->getHeight() * 1.7f);
    else
        btnBack->setPosition(size.width - btnBack->getWidth() * 0.6f, size.height - btnBack->getHeight() * 0.8f);

	btnSound = addButton(BTN_SOUND_ID, "btnSoundOn.png");
	btnSound->setPosition(btnBack->getPositionX() - btnBack->getWidth() * 1.1f, btnBack->getPositionY());
	if(game->music)
	{
		btnSound->normalImage->setImage("btnSoundOn.png");
	}
	else
	{
		btnSound->normalImage->setImage("btnSoundOff.png");
	}

	BaseButton* btnDownload = addButton(BTN_DOWNLOAD, "btnDownload.png");
	btnDownload->setPosition(btnBack->getPositionX() - btnDownload->getWidth() * 1.1f, btnBack->getPositionY());
	btnDownload->setVisible(false);

	btnUndo = addButton(BTN_UNDO_ID, "gameBubble/btnUndo.png");
	btnUndo->setPosition(btnSound->getPositionX() - btnSound->getWidth() * 1.1f, btnBack->getPositionY());
	btnUndo->setVisible(false);

	btnAchievement = addButton(BTN_ACHIEVEMENT_ID, "gameBubble/btnAchievementSmall.png");
	btnAchievement->setPosition(btnUndo->getPositionX() - btnUndo->getWidth() * 1.1f, btnBack->getPositionY());
    btnAchievement->setVisible(false);

	bgScore = Scale9Sprite::create("480_800/bgScoreNormal.png");
	addChild(bgScore);
	bgScore->setContentSize(Size(120, 55));
	bgScore->setPosition(bgScore->getContentSize().width * 0.6, btnBack->getPositionY());

	Text* lbScore = Text::create("SCORE", "fonts/tahomabd.ttf", 18);
	bgScore->addChild(lbScore);
	lbScore->enableOutline(Color4B(3, 85, 188, 255), 2);
	lbScore->setPosition(Vec2(bgScore->getContentSize().width * 0.5, bgScore->getContentSize().height * 0.75));

	bgBest = Scale9Sprite::create("480_800/bgScoreBest.png");
	addChild(bgBest);
	bgBest->setContentSize(bgScore->getContentSize());
	bgBest->setPosition(bgScore->getPositionX() + bgScore->getContentSize().width * 1.25, bgScore->getPositionY());


	Text* lbBest = Text::create("BEST", "fonts/tahomabd.ttf", 18);
	bgBest->addChild(lbBest);
	lbBest->enableOutline(Color4B(175, 108, 3, 255), 2);
	lbBest->setPosition(Vec2(bgBest->getContentSize().width * 0.5, bgBest->getContentSize().height * 0.75));

	labelScore = Text::create("0", "fonts/tahomabd.ttf", 22);
	labelScore->setTextHorizontalAlignment(TextHAlignment::CENTER);
	labelScore->setAnchorPoint(Vec2(0.5f, 0.5f));
	labelScore->enableOutline(Color4B(3, 85, 188, 255), 3);
	bgScore->addChild(labelScore);
	labelScore->setPosition(Vec2(bgScore->getContentSize().width * 0.5, bgScore->getContentSize().height * 0.3));

	labelHighscore = Text::create("0", "fonts/tahomabd.ttf", 22);
	labelHighscore->setTextHorizontalAlignment(TextHAlignment::CENTER);
	labelHighscore->setAnchorPoint(Vec2(0.5f, 0.5f));
	labelHighscore->enableOutline(Color4B(175, 108, 3, 255), 3);
	bgBest->addChild(labelHighscore);
	labelHighscore->setPosition(Vec2(bgBest->getContentSize().width * 0.5, bgBest->getContentSize().height * 0.3));

	ballMove = new Bubble("gameBubble/bgNumber.png");
	this->addChild(ballMove);
	ballMove->setVisible(false);
	ballMove->setZOrder(1);

	for(int i = 0; i < MAX_NEXT; i++)
	{
		arrayNext[i] = new Bubble("gameBubble/bgBubble.png");
		this->addChild(arrayNext[i]);
		//arrayNext[i]->setVisible(false);
		arrayNext[i]->setWidth(size.width * 0.06f);
		arrayNext[i]->setHeight(arrayNext[i]->getRealWidth());
		
		arrayNext[i]->setPos(arrayNext[i]->getRealWidth() * i, btnBack->getPositionY());
		arrayNext[i]->setNumber(1);
		
	}
    
    bgProgress = addImage("gameBubble/bgWhite.jpg");
    bgProgress->setAnchorPointImage(ccp(0, 0.5f));
    bgProgress->setWidth(arrayNext[0]->getRealWidth() * 3);
    bgProgress->setHeight(arrayNext[0]->getRealHeight() * 0.2f);
    bgProgress->setPos(arrayNext[1]->getPositionX() - bgProgress->getRealWidth() * 0.5f, arrayNext[1]->getPositionY() - arrayNext[1]->getRealHeight() * 0.4f);
    bgProgress->setColor(ccc3(50, 50, 50));
    
    progress = addImage("gameBubble/bgWhite.jpg");
    progress->setAnchorPointImage(ccp(0, 0.5f));
    progress->setWidth(bgProgress->getRealWidth());
    progress->setHeight(bgProgress->getRealHeight());
    progress->setPos(bgProgress->getPositionX(), bgProgress->getPositionY());
    

	float pad = size.width * 0.0117f;

	for (int i = 0; i < MAX_ROW; i++)
		for (int j = 0; j < MAX_COLUMN; j++)
		{
			arrayBgBall[i][j] = this->addImage("gameBubble/cell.png");

		}

	for(int i = 0; i < MAX_ROW; i++)
		for(int j = 0; j < MAX_COLUMN; j++)
		{
			arrayBall[i][j] = new Bubble("gameBubble/bgBubble.png");
			arrayBall[i][j]->nameImage = "gameBubble/bgNumber";
			addChild(arrayBall[i][j]);
		}

	bubbleText = new BubbleText();
	this->addChild(bubbleText);
	bubbleText->setText("Khi nao can mua ao giap sat");
	bubbleText->setPosition(100, 100);

	iconHand = this->addImage("gameBubble/iconHand.png");
	iconHand->setZOrder(1);
	bubbleText->setZOrder(1);

	//bg->setVisible(false);
	board = new BoardDataBubble();
	setLevel(0);
	setKeypadEnabled(true);
	stateTutorial = 0;
	//newGame();
}

void okFunction1Bubble()
{
	
}

void cancelFunction1Bubble()
{
	if(GUIManager::getInstance().guiBubble.typeMode == 0)
	{
		game->isPlayingBubble = false;
		CCUserDefault::sharedUserDefault()->setBoolForKey("isPlayingBubble", false);
	}
	else
	{
		game->isPlayingTime = false;
		CCUserDefault::sharedUserDefault()->setBoolForKey("isPlayingTime", false);
	}
	CCUserDefault::sharedUserDefault()->flush();
	GUIManager::getInstance().guiBubble.newGame();
}


void GUIBubble::newGame()
{
//	game->showHelp = true;
	iconHand->setVisible(false);
	bubbleText->setVisible(false);
	time = 0;
	canTouch = true;
	currentScore = 0;
	currentRow = -1;
	gameState = PLAY_BUBBLE;
	canUndo = false;
	btnUndo->setEnable(canUndo);
	progress->setVisible(false);
	bgProgress->setVisible(false);
	if(game->showHelpBubble)
	{
		GUIManager::getInstance().guiDialog.showGUI("Let's try tutorial!", NULL, true);
		setLevel(3);
		stateTutorial = 0;
		board->newGame();
		showTutorial();
	}
	else
	{
		if(typeMode == 0)
		{
			if (game->isPlayingBubble)
			{
				board->loadGame();
				updateScore(game->saveScoreBubble);

				/*GUIManager::getInstance().guiDialog.showGUI("Do you want to continue the last game?", &okFunction1Bubble, false, &cancelFunction1Bubble,
					NULL, "btnNewGame.png");*/
			}
			else
			{
				board->newGame();
				updateScore(0);
			}
			progress->setVisible(false);
			bgProgress->setVisible(false);
			labelHighscore->setText(GameUtility::standardizeNumber(game->highscoreBubble).c_str());
		}
		else
		{
			if (game->isPlayingTime)
			{
				board->loadGameTime();
				updateScore(game->saveScoreTime);

				GUIManager::getInstance().guiDialog.showGUI("Do you want to continue the last game?", &okFunction1Bubble, false, &cancelFunction1Bubble,
					NULL, "gameBubble/btnNewGame.png");
			}
			else
			{
				board->newGame();
				updateScore(0);
			}
			labelHighscore->setText(GameUtility::standardizeNumber(game->highscoreTime).c_str());
		//	progress->setVisible(true);
		//	bgProgress->setVisible(true);
			//newTimer();
		}

		
	}
	
	for (int i = 0; i < MAX_ROW; i++)
		for (int j = 0; j < MAX_COLUMN; j++)
		{
			arrayBall[i][j]->setVisible(false);
			arrayBgBall[i][j]->setVisible(false);
		}

		for (int i = 0; i < NUM_ROW_GAME; i++)
		{
			string s = "";
			for (int j = 0; j < NUM_COLUMN_GAME; j++) {
				arrayOldBall[i][j] = 0;
				saveBall[i][j] = board->arrayBall[i][j];
				s = s + " " + GameUtility::toString(board->arrayBall[i][j]);
				arrayBgBall[i][j]->setVisible(true);
			}
		}



		updateNextBall();
		updateViewBall();

	//showTutorial();
}

void GUIBubble::newTimer()
{
	if(typeMode == 0)
		return;
    progress->setVisible(true);
   
    progress->cleanup();
    progress->setScaleX(bgProgress->getScaleX());
    progress->runAction(CCSequence::create(CCScaleTo::create(7.0f, 0, progress->getScaleY()), CCCallFunc::create(this, callfunc_selector(GUIBubble::autoBiggerBall)), NULL));
}

void GUIBubble::callbackTimer()
{
    makeBiggerBall();
    checkEatPoint();
    newTimer();
}

void GUIBubble::showGui()
{
    BaseGUI::showGUI();
    setVisible(true);
    GUIManager::getInstance().addToListGui(this);

	newGame();
    
   /* time = 0;
    board->loadGame();
    updateScore(game->saveScoreBubble);
    for (int i = 0; i < NUM_ROW_GAME; i++)
        for (int j = 0; j < NUM_COLUMN_GAME; j++) {
            arrayOldBall[i][j] = 0;
            saveBall[i][j] = board->arrayBall[i][j];
        }
    updateNextBall();
    updateViewBall();
    game->isPlayingBubble = true;
    
    
    gameState = PLAY_BUBBLE;
    canUndo = false;
    btnUndo->setEnable(canUndo);*/
}

void GUIBubble::showGuiWithMode(int typeMode)
{
	
    BaseGUI::showGUI();
	this->typeMode = typeMode;
	this->setLevel(typeMode);
    setVisible(true);
    GUIManager::getInstance().addToListGui(this);
	newGame();
}

void GUIBubble::updateScore( int score )
{
	this->score = score;
	labelScore->cleanup();
	if(score != currentScore)
	{
		deltaScore = (score - currentScore) / 10;
		if(deltaScore == 0)
		{
			if(score > currentScore)
				deltaScore = 1;
			else
			{
				deltaScore = -1;
			}
		}
		this->effectScore();
	}
	else
	{
		labelScore->setText(GameUtility::standardizeNumber(score).c_str());
	}

    if(typeMode == 0)
    {
        if(this->score > game->highscoreBubble)
        {
            
            game->highscoreBubble = this->score;
            CCUserDefault::sharedUserDefault()->setIntegerForKey("highscoreBubble", game->highscoreBubble);
            CCUserDefault::sharedUserDefault()->flush();
			labelHighscore->setText(GameUtility::standardizeNumber(game->highscoreBubble).c_str());
        }
        
    }
    else
    {
       /* if(this->score > game->highscoreTime)
        {
            
            game->highscoreTime = this->score;
            CCUserDefault::sharedUserDefault()->setIntegerForKey("highscoreTime", game->highscoreTime);
            CCUserDefault::sharedUserDefault()->flush();
        }*/
        
    }
}

bool GUIBubble::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint point = pTouch->getLocation();

	if(point.y < startY)
		return BaseGUI::onTouchBegan(pTouch, pEvent);
	if (canTouch == false)
		return BaseGUI::onTouchBegan(pTouch, pEvent);

	int column = (int) ((point.x  - startX) / sizeCell);
	int row;
	if(column % 2 == 0)
		row = (int) ((point.y - startY) / sizeCell);
	else
	{
		row = (int)((point.y - startY - sizeCell * 0.5f) / sizeCell);
	}

	row = -1; column = -1;
	for (int i = 0; i < NUM_ROW_GAME; i++) {
		for (int j = 0; j < NUM_COLUMN_GAME; j++) {
			if (checkInHexagon(arrayBall[i][j]->rootX, arrayBall[i][j]->rootY, Vec2(point.x,point.y))) {
				row = i;
				column = j;
				break;
			}
		}
	}

	if (row < 0)
		return BaseGUI::onTouchBegan(pTouch, pEvent);

	if (row < 0 || column < 0 || row >= NUM_ROW_GAME || column >= NUM_COLUMN_GAME || (gameState != NORMAL_GAME_BUBBLE && gameState != PLAY_BUBBLE && gameState != TOUCH_BUBBLE))
		return BaseGUI::onTouchBegan(pTouch, pEvent);

	if (board->level > 2)
	{
		switch (stateTutorial)
		{
		case 0:
		{
			if (row != 4 || column != 0)
			{
				return BaseGUI::onTouchBegan(pTouch, pEvent);
			}
			else
			{
				iconHand->setVisible(false);
				bubbleText->setVisible(false);
				stateTutorial++;
				showTutorial();
			}
		}
			break;
		case 1:
		{
			if (row != 3 || column != 2)
			{
				return BaseGUI::onTouchBegan(pTouch, pEvent);
			}
			else
			{
				iconHand->setVisible(false);
				bubbleText->setVisible(false);
			}
		}
		break;
		case 2:
		{
			if (row != 5 || column != 2)
			{
				return BaseGUI::onTouchBegan(pTouch, pEvent);
			}
			else
			{
				iconHand->setVisible(false);
				bubbleText->setVisible(false);
				stateTutorial++;
				showTutorial();
			}
		}
		break;
		case 3:
		{
			if (row != 2 || column != 3)
			{
				return BaseGUI::onTouchBegan(pTouch, pEvent);
			}
			else
			{
				iconHand->setVisible(false);
				bubbleText->setVisible(false);
			}
		}
		break;
		case 4:
		{
			if (row != 5 || column != 3)
			{
				return BaseGUI::onTouchBegan(pTouch, pEvent);
			}
			else
			{
				iconHand->setVisible(false);
				bubbleText->setVisible(false);
				stateTutorial++;
				showTutorial();
			}
		}
		break;
		case 5:
		{
			if (row != 8 || column != 0)
			{
				return BaseGUI::onTouchBegan(pTouch, pEvent);
			}
			else
			{
				iconHand->setVisible(false);
				bubbleText->setVisible(false);
				stateTutorial++;
				//showTutorial();
			}
		}
		break;
		case 6:
		case 7:
		{
			return BaseGUI::onTouchBegan(pTouch, pEvent);
		}
		break;
		case 8:
		{
			if (row != 7 || column != 1)
			{
				return BaseGUI::onTouchBegan(pTouch, pEvent);
			}
			else
			{
				iconHand->setVisible(false);
				bubbleText->setVisible(false);
				stateTutorial++;
				showTutorial();
			}
		}
		break;
		case 9:
		{
			if (row != 6 || column != 3)
			{
				return BaseGUI::onTouchBegan(pTouch, pEvent);
			}
			else
			{
				iconHand->setVisible(false);
				bubbleText->setVisible(false);
			}
		}
		break;
		case 10:
		{
			if (row != 5 || column != 3)
			{
				return BaseGUI::onTouchBegan(pTouch, pEvent);
			}
			else
			{
				iconHand->setVisible(false);
				bubbleText->setVisible(false);
				stateTutorial++;
				showTutorial();
			}
		}
		break;
		case 11:
		{
			if (row != 8 || column != 0)
			{
				return BaseGUI::onTouchBegan(pTouch, pEvent);
			}
			else
			{
				iconHand->setVisible(false);
				bubbleText->setVisible(false);
			}
			
		}
		break;
		default:
			break;
		}
		
	}
	else
	{
		bubbleText->setVisible(false);
		bubbleText->cleanup();
	}
	CCLOG("RUN HERE 1");

	if (board->arrayBall[row][column] > 0) {
		if (arrayBall[row][column]->state == JUMP_BUBBLE) {
			arrayBall[row][column]->setState(NORMAL_BUBBLE);
			gameState = PLAY_BUBBLE;
			currentRow = -1;
		} else {
			if (currentRow >= 0)
				arrayBall[currentRow][currentColumn]->setState(NORMAL_BUBBLE);
			arrayBall[row][column]->setState(JUMP_BUBBLE);
			board->updatePoint(column, row);
            gameState = TOUCH_BUBBLE;
			currentRow = row;
			currentColumn = column;
		}
		CCLOG("RUN HERE 1sd");
		GameSound::playChooseBall();
	} else {
		if (gameState == TOUCH_BUBBLE) {

			board->setWay(row, column);
			if (board->arrayPoint.size() > 0) {
				gameState = MOVE_BUBBLE;
				SPEED = 100 / board->arrayPoint.size();
				ballMove->setVisible(true);
				string s = "gameBubble/bubble_" + GameUtility::toString(board->arrayBall[currentRow][currentColumn] - 1) + ".png";
				ballMove->setNumber(board->arrayBall[currentRow][currentColumn]);
				//ballMove->setImage(s.c_str());
				ballMove->setWidth(sizeCell * SIZE_BALL);
				ballMove->setHeight(sizeCell * SIZE_BALL);
				ballMove->setPositionX(arrayBall[currentRow][currentColumn]->getPositionX());
				ballMove->setPositionY(arrayBall[currentRow][currentColumn]->getPositionY());
				GameSound::playMove();

				saveNumRand = board->numRand;
				for(int i = 0; i < MAX_NEXT; i++)
					saveNext[i] = board->arrayNext[i];
				oldScore = score;
				// luu lai mang gia tri
				for (int i = 0; i < NUM_ROW_GAME; i++)
					for (int j = 0; j < NUM_COLUMN_GAME; j++) {
						saveBall[i][j] = board->arrayBall[i][j];
					}
					SPEED = 0.1f / board->arrayPoint.size();
					
				
					doMoveBall();
					if(typeMode == 0)
						game->isPlayingBubble = true;
					else
					{
						game->isPlayingTime = true;
					}
					arrayBall[currentRow][currentColumn]->setVisible(false);
					arrayBgBall[currentRow][currentColumn]->setVisible(true);
					visibleBgBall(currentRow, currentColumn);

					int saveValue = board->arrayBall[currentRow][currentColumn];
					int saveValue2 = board->arrayBall[row][column];
					board->updateValue(currentRow, currentColumn, 0);

					board->updateValue(row, column, saveValue);

					arrayOldBall[currentRow][currentColumn] = 0;
					arrayOldBall[row][column] = board->arrayBall[currentRow][currentColumn];
					currentRow = -1;

					nextRow = row;
					nextColumn = column;

					// check xem co kha nang an quan ko, neu co thi ko lam bong
					// lon len
					arrayChange.clear();
					arrayChange.push_back(new PointGame(column, row));
					checkGenNextBall();
					canTouch = false;
// 					if (genNext)
// 						makeBiggerBall();
// 					else
// 					{
// 						newTimer();
// 					}
			} else {
				CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();
				GameSound::playFail();
				//bubbleText->setVisible(true);
			//	bubbleText->setText("Can not move because it's surrounded by other bubbles");
				Toast::makeToast(2, "Can not move because it's surrounded by other bubbles");
				bubbleText->setPosition(size.width * 0.5f, size.height * 0.5f);
				bubbleText->setOpacity(0);
				if(stateTutorial == 6)
				{
					stateTutorial++;
					bubbleText->runAction(CCSequence::create(CCFadeOut::create(0.5f), CCDelayTime::create(1.0f), CCFadeOut::create(0.5f)
						, CCCallFunc::create(this, callfunc_selector(GUIBubble::showTutorial)), NULL));
				}
				else
				{
					//bubbleText->runAction(CCSequence::create(CCFadeIn::create(0.5f), CCDelayTime::create(2.0f), CCFadeOut::create(0.5f), NULL));
				}
				
				//bubbleText->
				//bubbleText->runAction(CCFadeOut::create(0.5f));
				countVibrate = 0;
				//JNIUtils::vibrate();
				vibrate();
			}
		}
	}
	CCLOG("RUN HERE 2");
	return BaseGUI::onTouchBegan(pTouch, pEvent);
}

void GUIBubble::genBall(int i, int j) {

	arrayBall[i][j]->setNumber(board->arrayBall[i][j]);
	//arrayBall[i][j]->setWidth(sizeCell * SIZE_BALL);
	//arrayBall[i][j]->setHeight(sizeCell * SIZE_BALL);
	//arrayBall[i][j]->rootScaleX = arrayBall[i][j]->getScaleX();
	//arrayBall[i][j]->rootScaleY = arrayBall[i][j]->getScaleY();
	arrayBall[i][j]->setState(NORMAL_BUBBLE);
	//arrayBall[i][j]->setPos(sizeCell * (j + 0.5f) + startX, startY + sizeCell * (i + 0.5f) + sizeCell * (j % 2 == 0 ? 0 : 1) * 0.5f);
	arrayBgBall[i][j]->setVisible(false);
	
}

void GUIBubble::updateViewBall() {
	for (int i = 0; i < NUM_ROW_GAME; i++)
		for (int j = 0; j < NUM_COLUMN_GAME; j++) {
			if (board->arrayBall[i][j] > 0 && board->arrayBall[i][j] != arrayOldBall[i][j]) {
				genBall(i, j);
				arrayOldBall[i][j] = board->arrayBall[i][j];
			//	arrayBgBall[i][j]->setVisible(false);
			} else if (board->arrayBall[i][j] <= 0)
			{
				arrayBall[i][j]->setVisible(false);
				visibleBgBall(i, j);
			}
			
		}

}

void GUIBubble::updateNextBall() {
	
	int count = 0;
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();
	float startX = size.width * 0.5f - (arrayNext[0]->getRealWidth() * 1.2f * board->numRand) / 2;
	for (int i = 0; i < board->numRand; i++)
	{
		arrayNext[i]->setNumber(board->arrayNext[i]);
		arrayNext[i]->setPositionX(startX + arrayNext[0]->getRealWidth() * (i + 0.5f) + i * arrayNext[0]->getRealWidth() * 0.2f);
		arrayNext[i]->setVisible(false);
	}
	
	for (int i = board->numRand; i < MAX_NEXT; i++) {
		arrayNext[i]->setVisible(false);
	}
}

void GUIBubble::checkGenNextBall() {
	board->result.clear();
	board->resetCheck();
	ResultData* resultData = new ResultData();
	board->result.push_back(resultData);
	for (int i = 0; i < arrayChange.size(); i++) {
		board->getListBall(arrayChange.at(i)->y, arrayChange.at(i)->x, board->arrayBall[arrayChange.at(i)->y][arrayChange.at(i)->x], 0);
	}

	if (board->result.at(0)->arrayPoint.size() < 4)
		genNext = true;
	else
		genNext = false;
}

void okEndFunction1Bubble()
{
	GUIManager::getInstance().guiBubble.newGame();
}

void GUIBubble::callbackDelayBigger(CCNode* pSender, void* data)
{
	PointGame* p = (PointGame*) data;
	genBall(p->y, p->x);
	arrayBall[p->y][p->x]->setState(BIGGER_BUBBLE);
	arrayBall[p->y][p->x]->setVisible(true);
	GameSound::playClick();
}

void GUIBubble::makeBiggerBall() {
	board->randomNext();
	for (int i = 0; i < board->numRand; i++)
	{

		PointGame* p = board->arrayPointNext[i];
		arrayBall[p->y][p->x]->setNumber(board->arrayNext[i]);
		float scaleX = arrayBall[p->y][p->x]->rootScaleX;
		float scaleY = arrayBall[p->y][p->x]->rootScaleY;
		arrayBall[p->y][p->x]->setVisible(true);
		arrayBall[p->y][p->x]->setPosition(arrayBgBall[p->y][p->x]->getPosition());
		arrayBall[p->y][p->x]->setScale(0);
		arrayBall[p->y][p->x]->stopAllActions();
		arrayBall[p->y][p->x]->runAction(CCSequence::create(
			CCDelayTime::create(0.05f * i),
			CCEaseBackOut::create(CCScaleTo::create(0.4, scaleX, scaleY)),
			//CCScaleTo::create(0.4, scaleX, scaleY),
			NULL
		));
		//arrayBall[p->y][p->x]->setVisible(true);
// 		arrayBgBall[p->y][p->x]->setColor(ccc3(255, 255, 255));
// 		arrayBgBall[p->y][p->x]->setVisible(true);
// 		arrayBgBall[p->y][p->x]->getImg()->setOpacity(255);
// 		arrayBgBall[p->y][p->x]->getImg()->runAction(CCSequence::create(CCDelayTime::create(0.1f * i), CCFadeOut::create(0.5f), NULL));
		arrayBall[p->y][p->x]->runAction(CCSequence::create(CCDelayTime::create(0.05f * i + 0.41), CCCallFuncND::create(this, callfuncND_selector(GUIBubble::callbackDelayBigger), (void*)p), NULL));
		//arrayBall[board->arrayPointNext[i]->y][board->arrayPointNext[i]->x]->setState(BIGGER);
		arrayChange.push_back(board->arrayPointNext[i]);
	}
	runAction(CCSequence::create(CCDelayTime::create(0.05f * (board->numRand + 1) + 0.41), CCCallFunc::create(this, callfunc_selector(GUIBubble::callbackFinishMove)), NULL));

		
}
// ko dung ham nay nua
void GUIBubble::onFinish() {
	// TODO Auto-generated method stub
// 	if (GUIManager::getInstance().guiBubble.valueSaveBall >= 8) {
// 		int row = GUIManager::getInstance().guiBubble.positionSaveBall / 9;
// 		int column = GUIManager::getInstance().guiBubble.positionSaveBall % 9;
// 		GUIManager::getInstance().guiBubble.board->updateValue(row, column, GUIManager::getInstance().guiBubble.valueSaveBall);
// 		GUIManager::getInstance().guiBubble.updateNextBall();
// 		GUIManager::getInstance().guiBubble.updateViewBall();
// 	}
}

void GUIBubble::doMoveBall() {
	
	if (board->arrayPoint.size() > 0) {
		int nextRow = board->arrayPoint.at(board->arrayPoint.size() - 1)->y;
		int nextColumn = board->arrayPoint.at(board->arrayPoint.size() - 1)->x;
		CCLOG("Move %i %i ", nextRow, nextColumn);
		board->arrayPoint.erase(board->arrayPoint.begin() + board->arrayPoint.size() - 1);

		ballMove->cleanup();
		ballMove->runAction(CCSequence::create(CCMoveTo::create(SPEED,ccp(arrayBgBall[nextRow][nextColumn]->getPositionX(), arrayBgBall[nextRow][nextColumn]->getPositionY()))
			, CCCallFunc::create(this, callfunc_selector(GUIBubble::doMoveBall)), NULL));

		
	} else {
		if(genNext)
		{
			makeBiggerBall();
		}
		else
		{
			runAction(CCSequence::create(CCDelayTime::create(0.1f), CCCallFunc::create(this, callfunc_selector(GUIBubble::callbackFinishMove)), NULL));
		}
		
		ballMove->setVisible(false);
		genBall(nextRow, nextColumn);
		
	}
}

void GUIBubble::checkEatPoint() {
	board->result.clear();
	board->resetCheck();
	for (int i = 0; i < arrayChange.size(); i++) {
		if (board->arrayBall[arrayChange.at(i)->y][arrayChange.at(i)->x] < board->arrayMaxNumber[board->level])
		{
			ResultData* resultData = new ResultData();
			board->result.push_back(resultData);
			board->getListBall(arrayChange.at(i)->y, arrayChange.at(i)->x, board->arrayBall[arrayChange.at(i)->y][arrayChange.at(i)->x], i);
		}
		else
		{
			int addPoint = board->arrayBall[arrayChange.at(i)->y][arrayChange.at(i)->x] * 4;
			board->arrayBall[arrayChange.at(i)->y][arrayChange.at(i)->x] = 0;
			arrayBall[arrayChange.at(i)->y][arrayChange.at(i)->x]->setState(AUTO_SCORE_BUBBLE);
			runAction(CCSequence::create(CCDelayTime::create(0.8f), CCCallFunc::create(this, callfunc_selector(GUIBubble::callbackAutoScore)), NULL));
			return;
		}
	}
	int addPoint = 0;
	int max = 0;
	for (int i = 0; i < board->result.size(); i++)
	{
		if (board->result.at(i)->arrayPoint.size() >= 4)
		{
			if (board->result.at(i)->arrayPoint.size() > max)
				max = board->result.at(i)->arrayPoint.size();
			PointGame* p1 = board->result.at(i)->arrayPoint.at(0);

		//	arrayBall[p->y][p->x]->setNumber(board->arrayBall[p->y][p->x] * 4);
			//arrayBall[p->y][p->x]->setState(NORMAL);
			addPoint = addPoint + board->arrayBall[p1->y][p1->x] * 4;
			Text* label = getLabelEffect();
			label->setText(GameUtility::toString(board->arrayBall[p1->y][p1->x] * 4).c_str());
			label->setPosition(arrayBall[p1->y][p1->x]->getPosition());
			//label->runAction(CCSpawn::create(CCScaleTo::create(1.3f, 3.0f), CCFadeOut::create(1.3f), NULL));
			//label->setColor(GameUtility::getColor(board->arrayBall[p1->y][p1->x] * 4));
		//	label->runAction(CCSequence::create(CCSpawn::create(CCScaleTo::create(0.6f, 2.5f), CCFadeOut::create(1.5f), NULL), CCCallFuncN::create(this, callfuncN_selector(GUIBubble::callbackVisibleEatPoint)), NULL));
			label->runAction(CCSequence::create(CCDelayTime::create(0.3), CCEaseBackOut::create(CCMoveBy::create(0.7f, ccp(0, 100))), CCFadeOut::create(0.5), CCHide::create(), NULL));

			if (board->result.at(i)->arrayPoint.size() > 5)
			{
				label = getLabelEffect();
				//label->setScale(1.2f);
				label->setText("Excellent");
				label->setPosition(arrayBall[p1->y][p1->x]->getPosition());
				label->runAction(CCSequence::create(CCSpawn::create(CCScaleTo::create(1.2f, 0.8f), CCMoveBy::create(1.2f, ccp(0, 160)), CCFadeOut::create(1.2f), NULL), CCCallFuncN::create(this, callfuncN_selector(GUIBubble::callbackVisibleEatPoint)), NULL));
			}

			for (int j = 4; j < board->result.at(i)->arrayPoint.size(); j++)
				addPoint = addPoint + board->arrayBall[p1->y][p1->x] * (j + 1);
			arrayOldBall[p1->y][p1->x] = board->arrayBall[p1->y][p1->x] * 4;
			board->updateValue(p1->y, p1->x, board->arrayBall[p1->y][p1->x] * 4);
			//genBall(p->y, p->x);
			
			for (int j = 1; j < board->result.at(i)->arrayPoint.size(); j++){
				PointGame* p = board->result.at(i)->arrayPoint.at(j);
				arrayBall[p->y][p->x]->runAction(CCSequence::create(CCMoveTo::create(0.2f, arrayBall[p1->y][p1->x]->getPosition()), CCHide::create(), NULL));
				visibleBgBall(p->y, p->x);
				
				board->updateValue(p->y, p->x, 0);
				arrayOldBall[p->y][p->x] = 0;
			}
			
		}
	}
	if(addPoint > 0)
	{
		int i;
		
		runAction(CCSequence::create(CCDelayTime::create(0.2f), CCCallFunc::create(this, callfunc_selector(GUIBubble::callbackEatPoint)), NULL));
		score = score + addPoint;
		updateScore(score);
		switch (max)
		{
		case 4:
			GameSound::playScore1();
			break;
		case 5:
		{
			GameSound::playScore2();
			
		}
			break;
		case 6:
			GameSound::playScore3();
			break;
		case 7:
			GameSound::playScore4();
			break;
		default:
			GameSound::playScore5();
			break;
		}
	}
	else
	{
		canTouch = true;
		if (board->checkEndGame())
		{
			if (typeMode == 0)
			{
				game->isPlayingBubble = false;
				CCUserDefault::sharedUserDefault()->setBoolForKey("isPlayingBubble", false);
			}
			else
			{
				game->isPlayingTime = false;
				CCUserDefault::sharedUserDefault()->setBoolForKey("isPlayingTime", false);
			}
			CCUserDefault::sharedUserDefault()->flush();
			progress->cleanup();
			//MyCaro.game.caroScreen.showScoreLayer(score);
            GUIManager::getInstance().guiResult.showGUI(score, game->highscoreBubble);
			
			canUndo = false;
			btnUndo->setEnable(canUndo);
			//UtilityGettor.inst().showPopup();
			
		}
		
	}

	if (board->level > 2)
	{
		if (stateTutorial == 1)
		{
			stateTutorial++;
			showTutorial();
		}
		else if (stateTutorial == 9)
		{
			stateTutorial++;
			showTutorial();
		}
	}
	
	
}


void GUIBubble::updateHighScore() {
	
}

void GUIBubble::undo() {
	board->loadGame(saveBall);
	for(int i = 0; i < MAX_NEXT; i++)
	{
		board->arrayNext[i] = saveNext[i];
		board->numRand = saveNumRand;
	}
	for (int i = 0; i < NUM_ROW_GAME; i++)
		for (int j = 0; j < NUM_COLUMN_GAME; j++) {
			arrayOldBall[i][j] = 0;
		}
		updateNextBall();
		updateViewBall();
		updateScore(oldScore);
}

void GUIBubble::showParticle( float posX, float posY , int id)
{

	Layer *layer = layerMgr->getLayerByIndex(LAYER_EFFECT_GAME);
	ParticleEffect *effect = new ParticleEffect();
	effect->create("particles/explode.plist", layer);
	effect->particle->setPosition(ccp(posX, posY));
	effect->particle->setBlendAdditive(false);
	effect->particle->setAutoRemoveOnFinish(true);

	string s = ("480_800/" + GameUtility::getTextureColor(id));
	effect->particle->setTexture(CCTextureCache::sharedTextureCache()->addImage(s.c_str()));
}

void GUIBubble::act()
{
	time = time + game->deltaTime;
	if(time > 60 * 10 + GameUtility::getRandom() * 60)
	{
		
		time = 0;
	}
}

void GUIBubble::autoBiggerBall()
{
	arrayChange.clear();
	makeBiggerBall();
//	board->randomNext();
	updateNextBall();
	updateViewBall();
//	gameState = PLAY;
	checkEatPoint();
	canUndo = false;
	GameSound::playMove();
}

void GUIBubble::updateSizeBall()
{
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();
	float w = size.width * 0.85f;
	float h = size.height * 0.75f;
	if( NUM_COLUMN_GAME * 1.0f/ NUM_ROW_GAME > w / h)
	{
		
		sizeCell = w / NUM_COLUMN_GAME;
	}
	else
	{
		sizeCell = h / NUM_ROW_GAME;
	}
//	sizeCell = bg->getRealWidth() * 0.99f * (1.0f / NUM_COLUMN_GAME);
	startX = size.width * 0.5f - sizeCell * NUM_COLUMN_GAME * 0.5f;
	startY = size.height * 0.5f - sizeCell * NUM_ROW_GAME * 0.5f;

	ballMove->setWidth(sizeCell * 0.5f);
	ballMove->setHeight(sizeCell * 0.5f);
	for (int i = 0; i < NUM_ROW_GAME; i++)
		for (int j = 0; j < NUM_COLUMN_GAME; j++)
		{
			arrayBall[i][j]->setWidth(sizeCell * SIZE_BALL);
			arrayBall[i][j]->setHeight(sizeCell * SIZE_BALL);
			arrayBall[i][j]->rootScaleX = arrayBall[i][j]->getScaleX();
			arrayBall[i][j]->rootScaleY = arrayBall[i][j]->getScaleY();
			arrayBall[i][j]->setPos(sizeCell * (j + 0.5f) + startX, startY + sizeCell * (i + 0.5f) + sizeCell * (j % 2 == 0 ? 0 : 1) * 0.5f);

			arrayBgBall[i][j]->setVisible(true);
			arrayBgBall[i][j]->setWidth(sizeCell * SIZE_BALL);
			arrayBgBall[i][j]->setHeight(sizeCell * SIZE_BALL);
			arrayBgBall[i][j]->setPosition(arrayBall[i][j]->getPosition());

		}

	cellW = 122;
	cellH = 106;
	
	float rateX = 0.77;
	float rateY = 1.02;
	float w1 = cellW * (NUM_COLUMN_GAME - 1) * rateX + cellW;
	float h1 = cellH * (NUM_ROW_GAME + 0.5) * rateY;

	float scale = 1;
	if (w / h > w1 / h1)
	{

		scale = h / h1;
	}
	else
	{
		scale = w / w1;
	}

	startX = size.width * 0.5 - w1 * 0.5 * scale;
	startY = size.height * 0.5 - h1 * 0.5 * scale;
	cellW = cellW * scale;
	cellH = cellH * scale;
	for (int i = 0; i < NUM_ROW_GAME; i++)
		for (int j = 0; j < NUM_COLUMN_GAME; j++)
		{
			arrayBall[i][j]->setWidth(cellW * 0.975);
			arrayBall[i][j]->setHeight(cellH * 0.975);
			arrayBall[i][j]->rootScaleX = arrayBall[i][j]->getScaleX();
			arrayBall[i][j]->rootScaleY = arrayBall[i][j]->getScaleY();
			arrayBall[i][j]->setPos(startX + cellW * (0.5) + cellW * rateX * (j), startY + cellH * (i + 0.5) * rateY + cellH * (j % 2 == 0 ? 0 : 1) * 0.5);

			arrayBgBall[i][j]->setVisible(true);
			arrayBgBall[i][j]->setWidth(cellW * 0.975);
			arrayBgBall[i][j]->setHeight(cellH * 0.975);
			arrayBgBall[i][j]->setPosition(arrayBall[i][j]->getPosition());

		}

	for(int i = NUM_ROW_GAME; i < MAX_ROW; i++)
	{
		for(int j = 0; j < MAX_COLUMN; j++)
		{
			arrayBgBall[i][j]->setVisible(false);
			arrayBall[i][j]->setVisible(false);
		}
	}

	for(int i = 0; i < NUM_ROW_GAME; i++)
		for(int j = NUM_COLUMN_GAME; j < MAX_COLUMN; j++)
		{
			arrayBall[i][j]->setVisible(false);
			arrayBgBall[i][j]->setVisible(false);
		}

	
}

void GUIBubble::callbackFinishMove()
{
	if (board->level == 3)
		board->level++;

	if (genNext)
	{
		board->randomNextId();
	}
	updateNextBall();
	updateViewBall();
	gameState = PLAY_BUBBLE;
	checkEatPoint();
	canUndo = true;
	btnUndo->setEnable(canUndo);
	
}

void GUIBubble::visibleBgBall( int row, int column )
{
	arrayBgBall[row][column]->setVisible(true);
	arrayBgBall[row][column]->getImg()->setColor(ccc3(255, 255, 255));
	arrayBgBall[row][column]->getImg()->setOpacity(255);
}

void GUIBubble::callbackVisibleEatPoint( CCNode* pSender )
{
	pSender->setVisible(false);
}

void okTutorialBubble()
{
	game->isPlayingBubble = false;
	game->isPlayingTime = false;
	GUIManager::getInstance().guiBubble.setLevel(GUIManager::getInstance().guiBubble.typeMode);
	GUIManager::getInstance().guiBubble.newGame();
}

void GUIBubble::callbackEatPoint()
{
	for(int i =0; i < board->result.size(); i++)
		if (board->result.at(i)->arrayPoint.size() >= 4)
		{
			PointGame* p1 = board->result.at(i)->arrayPoint.at(0);
			genBall(p1->y, p1->x);
			showParticle(arrayBall[p1->y][p1->x]->rootX, arrayBall[p1->y][p1->x]->rootY, board->arrayBall[p1->y][p1->x] / 4);
			this->arrayChange.clear();
			this->arrayChange.push_back(p1);
		}
	if (board->level > 2)
	{
		if (stateTutorial == 3)
		{
			stateTutorial++;
			showTutorial();
		}
		else if (stateTutorial == 11)
		{
			// ket thuc tutorial
			GUIManager::getInstance().guiDialog.showGUI("Are you ready to start?", &okTutorialBubble, true);
			game->showHelpBubble = false;
			CCUserDefault::sharedUserDefault()->setBoolForKey("showHelpBubble", false);
			CCUserDefault::sharedUserDefault()->flush();
		}
	}
	
	checkEatPoint();
}

void GUIBubble::showTutorial()
{
	switch (stateTutorial)
	{
	case 0:
	{
		//bubbleText->setText("Touch it to select");
		Toast::makeToast(2, "Touch it to select");
		setPosIconHand(0, 4);
		
	}
		break;
	case 1:
	{
		//bubbleText->setText("Touch empty cell to move");
		Toast::makeToast(2, "Touch empty cell to move");
		setPosIconHand(2, 3);
		
	}
	break;
	case 2:
	{
	//	bubbleText->setText("Touch it");
		Toast::makeToast(2, "Touch it");
		setPosIconHand(2, 5);
		
	}
	break;
	case 3:
	{
		//bubbleText->setText("Connect at least 4 bubble to get point");
		Toast::makeToast(2, "Connect at least 4 bubble to get point");
		setPosIconHand(3, 2);
		
	}
	break;
	case 4:
	{
		//bubbleText->setText("Touch it");
		Toast::makeToast(2, "Touch it");
		setPosIconHand(3, 5);
		
	}
	break;
	case 5:
	{
	//	bubbleText->setText("Try touch empty cell");
		Toast::makeToast(2, "Try touch empty cell");
		setPosIconHand(0, 8);
		
	}
	break;
	case 6:
	{
		//	bubbleText->setText("Cannot move, it is surrounded by other balls");
			Toast::makeToast(2, "Cannot move, it is surrounded by other balls");
		iconHand->setVisible(false);
		//bubbleText->setVisible(true);
	
		stateTutorial++;
		runAction(CCSequence::create(CCDelayTime::create(4.0f), CCCallFunc::create(this, callfunc_selector(GUIBubble::showTutorial)), NULL));
	}
	break;
	case 7:
	{
			//bubbleText->setText("Touch it");
			Toast::makeToast(2, "Touch it");
		setPosIconHand(1, 7);
	
		stateTutorial++;
	}
	break;
	case 9:
	{
	//	bubbleText->setText("Touch empty cell to move");
		Toast::makeToast(2, "Touch empty cell to move");
		setPosIconHand(3, 6);
		
	}
	break;
	case 10:
	{
		//bubbleText->setText("Touch it");
		Toast::makeToast(2, "Touch it");
		setPosIconHand(3, 5);
		
	}
	break;
	case 11:
	{
		//bubbleText->setText("Try touch empty cell");
		Toast::makeToast(2, "Try touch empty cell");
		setPosIconHand(0, 8);
		
	}
	break;
	default:
		break;
	}
}

Text* GUIBubble::getLabelEffect()
{
    Text* label;
	int i;
	for (i = 0; i < arrayLabelEffect.size(); i++)
	{
		if (!arrayLabelEffect.at(i)->isVisible())
		{
			label = arrayLabelEffect.at(i);
			label->setVisible(true);
			label->setOpacity(255);
			label->setScale(1);
			return label;
		}
	}
	if (i == arrayLabelEffect.size())
	{
		label = Text::create("100", "fonts/tahomabd.ttf", 40);
        label->enableOutline(Color4B(100, 100, 100, 255), 2);
		label->setAnchorPoint(ccp(0.5f, 0.75f));
		//label->setColor(ccc3(0, 0, 0));
		label->setZOrder(1);
		arrayLabelEffect.push_back(label);
		this->addChild(label);
		return label;
	}
}

void GUIBubble::callbackLabelEffect(CCNode* pSender)
{
	pSender->setVisible(false);
}

void GUIBubble::callbackAutoScore()
{
	canTouch = true;
	PointGame* p1 = this->arrayChange.at(0);
	Text* label = getLabelEffect();
	label->setText(GameUtility::toString(arrayBall[p1->y][p1->x]->id).c_str());
	label->setPosition(arrayBall[p1->y][p1->x]->getPosition());
	//label->runAction(CCSpawn::create(CCScaleTo::create(1.3f, 3.0f), CCFadeOut::create(1.3f), NULL));
	label->setColor(Color3B(200, 200, 200));
	//label->runAction(CCSequence::create(CCSpawn::create(CCScaleTo::create(0.8f, 3.0f), CCFadeOut::create(2.0f), NULL), CCCallFuncN::create(this, callfuncN_selector(GUIBubble::callbackVisibleEatPoint)), NULL));
	label->runAction(CCSequence::create(CCDelayTime::create(0.3), CCEaseBackOut::create(CCMoveBy::create(0.7f, ccp(0, 100))), CCFadeOut::create(0.5), CCHide::create(), NULL));
	arrayBall[p1->y][p1->x]->setVisible(false);
	arrayBgBall[p1->y][p1->x]->setVisible(true);

	score = score + arrayBall[p1->y][p1->x]->id;
	updateScore(score);
}

void GUIBubble::setPosIconHand( int x, int y )
{
	iconHand->cleanup();
	iconHand->setVisible(true);
	iconHand->setPos(arrayBall[y][x]->getPositionX() + sizeCell * 0.1f, arrayBall[y][x]->getPositionY() - sizeCell * 0.15f - iconHand->getHeight() * 0.55f);
	iconHand->runAction(CCRepeatForever::create(CCSequence::create(CCScaleTo::create(0.5f, 0.8f), CCScaleTo::create(0.5f, 1.0f), NULL)));
	bubbleText->setPosition(ccp(iconHand->getPositionX(), iconHand->getPositionY() - iconHand->getHeight() * 0.6f - bubbleText->getContentSize().height * 0.5f));
	//bubbleText->setVisible(true);
	bubbleText->setOpacity(255);
//	bubbleText->setPosition(iconHand->getPositionX(), bubbleText->getContentSize().height * 0.5f);
//	bubbleText->setPosition(iconHand->getPositionX(), 0);
}

void GUIBubble::vibrate()
{
	if (countVibrate > 6)
	{
		setRotation(0);
		return;
	}
	countVibrate++;
	float random = GameUtility::getRandom() * 0.5f;
	random = GameUtility::getRandom() > 0.5f ? random : -random;
	runAction(CCSequence::create(CCRotateTo::create(0.02f, random), CCCallFunc::create(this, callfunc_selector(GUIBubble::vibrate)), NULL));
}

void GUIBubble::setLevel( int level )
{
	board->level = level;
	NUM_ROW_GAME = 9;
	switch (level)
	{
	case 0:
		NUM_COLUMN_GAME = 5;
		break;
	case 1:
		NUM_COLUMN_GAME = 7;
		break;
	case 3:
		NUM_COLUMN_GAME = 5;
		break;
	default:
		break;
	}
	//NUM_ROW_GAME = 5;
//	NUM_COLUMN_GAME = 5;
	updateSizeBall();
}

void GUIBubble::effectScore()
{
	currentScore = currentScore + deltaScore;
	if(abs(currentScore - score) <= abs(2 * deltaScore))
	{
		currentScore = score;
		labelScore->setText(GameUtility::standardizeNumber(currentScore).c_str());
		return;
	}
	labelScore->setText(GameUtility::standardizeNumber(currentScore).c_str());
	labelScore->runAction(CCSequence::create(CCDelayTime::create(0.01f), CCCallFunc::create(this, callfunc_selector(GUIBubble::effectScore)), NULL));
}

LabelBM* GUIBubble::getLabelEffectSmall()
{
	LabelBM* label;
	int i;
	for (i = 0; i < arrayLabelEffectSmall.size(); i++)
	{
		if (!arrayLabelEffectSmall.at(i)->isVisible())
		{
			label = arrayLabelEffectSmall.at(i);
			label->setVisible(true);
			label->setOpacity(255);
			label->setScale(1);
			return label;
		}
	}
	if (i == arrayLabelEffectSmall.size())
	{
		label = LabelBM::create("100", FONT_SMALL_NORMAL_TYPE);
		label->setAnchorPoint(ccp(0.5f, 0.75f));
		label->setColor(ccc3(0, 0, 0));
		label->setZOrder(1);
		arrayLabelEffectSmall.push_back(label);
		this->addChild(label);
		return label;
	}
}

/**
	 * Create hexagon vertices based on the node's size.
	 */
bool GUIBubble::checkInHexagon(float centerX, float centerY, Vec2 pos) {
	float width = cellW;
	float height = cellH;

	// const centerX = center.x;
	//const centerY = center.y;
	float radius = (width > height ? height : width) / 2;

	vector<Vec2> hexagonVertices;
	// Calculate vertices of the hexagon
	for (int i = 0; i < 6; i++) {
		float angle = (PI / 3) * i;
		float x = centerX + radius * cos(angle);
		float y = centerY + radius * sin(angle);
		hexagonVertices.push_back(Vec2(x, y));
	}
	return isPointInHexagon(pos, hexagonVertices);
}

bool GUIBubble::isPointInHexagon(Vec2 point, vector<Vec2> hexagonVertices){
	bool inside = false;
	vector<Vec2> vertices = hexagonVertices;
	int n = vertices.size();

	for (int i = 0, j = n - 1; i < n; j = i++) {
		Vec2 vi = vertices[i];
		Vec2 vj = vertices[j];

		if (
			(vi.y > point.y) != (vj.y > point.y) &&
			point.x < ((vj.x - vi.x) * (point.y - vi.y)) / (vj.y - vi.y) + vi.x
			) {
			inside = !inside;
		}
	}
	return inside;
}


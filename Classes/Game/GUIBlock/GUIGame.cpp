#include "GUIGame.h"
#include "../../Engine/Utility/ScreenUtils.h"
#include "../../Engine/GlobalVar.h"
//#include "../../Engine/Utility/CCLocalizedString.h"
#include "../GUIManager.h"
#include "../Utility/JNIUtils.h"
#include "../Data/GlobalData.h"
#include "../Utility/GameUtility.h"
#include "Game/Data/GlobalData.h"
#include "Engine/Utility/CStringUtils.h"
#include "../Utility/GameSound.h"
#include "Game/Data/GlobalData.h"
#include "../LogicBlock/SquareBrick.h"
#include "../LogicBlock/LBrick.h"
#include "../LogicBlock/BigSquareBrick.h"
#include "../LogicBlock/BigLBrick.h"
#include "../LogicBlock/FiveRowBrick.h"
#include "../LogicBlock/FourColumnBrick.h"
#include "../LogicBlock/LSortBrick.h"
#include "../LogicBlock/OneBrick.h"
#include "../LogicBlock/TBrick.h"
#include "../LogicBlock/ThreeRowBrick.h"
#include "../LogicBlock/TwoColumnBrick.h"
#include "Engine/GUI/ParticleEffect.h"
//#include "Engine/GUI/CoinEffectLayer.h"
#include "ui/UIText.h"
#include "../LogicBlock/ConfigData.h"

#define BACKGROUND_RES "loading/bgPortalCenterZP.jpg"
#define PROGRESS_RES "loading/bgProgress.png"
#define ICON_GAME "loading/iconGame.png"
#define BG_PROGRESS "loading/black.png"

#define BTN_BACK_ID 1
#define BTN_SOUND_ID 2
#define BTN_EXCHANGE_ID 3
#define BTN_DOWNLOAD 4
#define BTN_HELP 5

GUIGame::GUIGame(void) : BaseGUI()
{

	BaseGUI();
	currentEntity = NULL;
	setKeypadEnabled(true);
}


GUIGame::~GUIGame(void)
{
}

void GUIGame::initGUI(){
	BaseGUI::initGUI();
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();
	// 	CCTextureCache::sharedTextureCache()->addImage(ScreenUtils::fileFull(BACKGROUND_RES).c_str());//
	// 	CCTextureCache::sharedTextureCache()->addImage(ScreenUtils::fileFull(PROGRESS_RES).c_str());
	// 	CCTextureCache::sharedTextureCache()->addImage(ScreenUtils::fileFull("loading/LG2.png").c_str());
	// 	CCTextureCache::sharedTextureCache()->addImage(ScreenUtils::fileFull("loading/LG2.png").c_str());
	//Image *bg1 = addImage("loading/LG2.png");
	//bg1->setWidth(size.width);
	//bg1->setHeight(size.height);
	//bg1->getImg()->runAction(CCSequence::create(CCFadeIn::create(0.8f), CCDelayTime::create(.8f), CCFadeOut::create(0.8f), CCCallFunc::create(this, callfunc_selector(GUIGame::callBackSplash)), NULL));
	//	runAction(CCSequence::create(CCDelayTime::create(0.1f), CCCallFunc::create(this, callfunc_selector(GUIGame::callBackSplash)), NULL));
	//bg1->setPos(size.width / 2, size.height / 2);

	callBackSplash();
}


void GUIGame::callBackSplash()
{
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();
	GameImage* background = addImage("background.jpg");
	background->setWidth(size.width);
	background->setHeight(size.height);
	background->setPos(size.width * 0.5f, size.height * 0.5f);
	//background->setVisible(false);

	DBCCFactory::getInstance()->loadDragonBonesData("effect/no_top/skeleton.xml", "no_top");
	DBCCFactory::getInstance()->loadTextureAtlas("effect/no_top/texture.plist", "no_top");

	DBCCFactory::getInstance()->loadDragonBonesData("effect/cast_skill_cuong_phong/skeleton.xml", "cast_skill_cuong_phong");
	DBCCFactory::getInstance()->loadTextureAtlas("effect/cast_skill_cuong_phong/texture.plist", "cast_skill_cuong_phong");

	DBCCFactory::getInstance()->loadDragonBonesData("effect/eff_button_daily_gift/skeleton.xml", "eff_button_daily_gift");
	DBCCFactory::getInstance()->loadTextureAtlas("effect/eff_button_daily_gift/texture.plist", "eff_button_daily_gift");

	DBCCFactory::getInstance()->loadDragonBonesData("effect/skill_elect/skeleton.xml", "skill_elect");
	DBCCFactory::getInstance()->loadTextureAtlas("effect/skill_elect/texture.plist", "skill_elect");

	DBCCFactory::getInstance()->loadDragonBonesData("effect/tile_light/skeleton.xml", "tile_light");
	DBCCFactory::getInstance()->loadTextureAtlas("effect/tile_light/texture.plist", "tile_light");

	DBCCFactory::getInstance()->loadDragonBonesData("effect/Chest/skeleton.xml", "Chest");
	DBCCFactory::getInstance()->loadTextureAtlas("effect/Chest/texture.plist", "Chest");

	initMenu();
	initBottom();
	initBonus();
	initBoard();

	iconBomb = addImage("gameBlockPuzzel/iconBomb.png");
	iconBomb->setVisible(false);
	iconBomb->setZOrder(5);
	
    iconHand = addImage("gameBlockPuzzel/iconHand.png");
    iconHand->setVisible(false);
    iconHand->getImg()->setAnchorPoint(ccp(0.2f, 0.8f));
    iconHand->setZOrder(5);
    
	//newGame();
	
    //GameSound::playBackground();
	//GameSound::playBackground();

}

void GUIGame::initAds()
{
   
}

void GUIGame::initMenu()
{
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();
	bgMenu = Scale9Sprite::create("480_800/gameBlockPuzzel/board.png");
	addChild(bgMenu);
	bgMenu->setContentSize(Size(size.width, 70));
	bgMenu->setPosition(size.width * 0.5, size.height - bgMenu->getContentSize().height * 0.5);
	bgMenu->setVisible(false);

	btnBack = addButton(BTN_BACK_ID, "btnBack.png");
	btnBack->setPosition(size.width - btnBack->getWidth() * 0.8f, bgMenu->getPositionY());

	if (size.width / size.height < 11.0 / 20.0)
		btnBack->setPosition(size.width - btnBack->getWidth() * 0.6f, size.height - btnBack->getHeight() * 1.4f);
	else
		btnBack->setPosition(size.width - btnBack->getWidth() * 0.6f, size.height - btnBack->getHeight() * 0.8f);

	BaseButton* btnHelp = addButton(BTN_HELP, "btnHelp.png", new BubbleBehavior(), NULL, true);
	btnHelp->setPosition(btnBack->getPositionX() - btnBack->getWidth() * 1.1f, btnBack->getPositionY());
    btnHelp->setVisible(false);

	btnSound = addButton(BTN_SOUND_ID, "btnSoundOn.png");
	btnSound->setPosition(btnBack->getPositionX() - btnBack->getWidth() * 1.1f, btnBack->getPositionY());
	if (game->music)
	{
		btnSound->normalImage->setImage("btnSoundOn.png");
	}
	else
	{
		btnSound->normalImage->setImage("btnSoundOff.png");
	}
//	btnSound->setVisible(false);
	Scale9Sprite* bgScore = Scale9Sprite::create("480_800/bgScoreNormal.png");
	addChild(bgScore);
	bgScore->setContentSize(Size(110, 50));
	bgScore->setPosition(Vec2(bgScore->getContentSize().width * 0.54, btnBack->getPositionY()));

	Text* lbScore = Text::create("SCORE", "fonts/tahomabd.ttf", 14);
	bgScore->addChild(lbScore);
	lbScore->enableOutline(Color4B(3, 85, 188, 255), 1);
	lbScore->setPosition(Vec2(bgScore->getContentSize().width * 0.5, bgScore->getContentSize().height * 0.75));

	Scale9Sprite* bgBest = Scale9Sprite::create("480_800/bgScoreBest.png");
	addChild(bgBest);
	bgBest->setContentSize(bgScore->getContentSize());
	bgBest->setPosition(bgScore->getPositionX() + bgScore->getContentSize().width * 1.05, bgScore->getPositionY());

	Text* lbBest = Text::create("BEST", "fonts/tahomabd.ttf", 14);
	bgBest->addChild(lbBest);
	lbBest->enableOutline(Color4B(175, 108, 3, 255), 1);
	lbBest->setPosition(Vec2(bgBest->getContentSize().width * 0.5, bgBest->getContentSize().height * 0.75));


	labelScore = Text::create("0", "fonts/tahomabd.ttf", 18);
	labelScore->setTextHorizontalAlignment(TextHAlignment::CENTER);
	labelScore->setAnchorPoint(Vec2(0.5f, 0.5f));
	labelScore->enableOutline(Color4B(3, 85, 188, 255), 1);
	bgScore->addChild(labelScore);
	labelScore->setPosition(Vec2(bgScore->getContentSize().width * 0.5, bgScore->getContentSize().height * 0.3));

	labelHighscore = Text::create(GameUtility::standardizeNumber(game->highscoreBlock), "fonts/tahomabd.ttf", 18);
	labelHighscore->setTextHorizontalAlignment(TextHAlignment::CENTER);
	labelHighscore->setAnchorPoint(Vec2(0.5f, 0.5f));
	labelHighscore->enableOutline(Color4B(175, 108, 3, 255), 1);
	bgBest->addChild(labelHighscore);
	labelHighscore->setPosition(Vec2(bgBest->getContentSize().width * 0.5, bgBest->getContentSize().height * 0.3));
}

void GUIGame::initBoard()
{
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();
	
	startX = size.width * 0.5f - widthBoard * 0.5f;
	float wCenter = widthBoard + 20;
	float d = bgMenu->getPositionY() - bgMenu->getContentSize().height * 0.5 - (bgBottom->getPositionY() + bgBottom->getContentSize().height * 0.5);
	d = d - wCenter - bonusBomb->getHeight();
	d = d / 3;
	startY = bgMenu->getPositionY() - bgMenu->getContentSize().height * 0.5 - d - widthBoard - 10;
	sizeCell = widthBoard / 8;

	bgCenter = Scale9Sprite::create("480_800/gameBlockPuzzel/board.png");
	addChild(bgCenter);
	
	bgCenter->setContentSize(Size(wCenter, wCenter));
	bgCenter->setPosition(size.width * 0.5, startY + widthBoard * 0.5);

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			arrayBgCell[i][j] = new GameImage("gameBlockPuzzel/bgCell.png");
			addChild(arrayBgCell[i][j]);

			arrayCell[i][j] = new CellBlock();
			this->addChild(arrayCell[i][j]);
			arrayCell[i][j]->setWidth(sizeCell * ConfigDataBlock::RATE_NORMAL_CELL);
			arrayCell[i][j]->setHeight(sizeCell * ConfigDataBlock::RATE_NORMAL_CELL);
			arrayCell[i][j]->setPosition(startX + (j + 0.5f) * sizeCell, startY + (i + 0.5) * sizeCell);

			arrayBgCell[i][j]->setWidth(arrayCell[i][j]->getRealWidth());
			arrayBgCell[i][j]->setHeight(arrayCell[i][j]->getRealHeight());
			arrayBgCell[i][j]->setPosition(arrayCell[i][j]->getPosition());
		}
	}
	bonusExchange->setPosition(size.width * 0.5 - bonusExchange->getWidth() * 1.2f, bgBottom->getPositionY() + bgBottom->getContentSize().height * 0.5 + bonusExchange->getHeight() * 0.5 + d);
	bonusX3->setPosition(size.width * 0.5, bonusExchange->getPositionY());
	bonusBomb->setPosition(size.width * 0.5 + bonusBomb->getWidth() * 1.2f, bonusExchange->getPositionY());
	BaseButton* btnDownload = addButton(BTN_DOWNLOAD, "btnDownload.png");
	btnDownload->setPosition(btnDownload->getWidth() * 0.55, bonusExchange->getPositionY());
	btnDownload->setVisible(false);
}

void GUIGame::initBonus()
{
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();

	bonusExchange = addButton(BTN_EXCHANGE_ID, "gameBlockPuzzel/bonusExchange.png");
	bonusX3 = addImage("gameBlockPuzzel/bonusX3.png");
	bonusBomb = addImage("gameBlockPuzzel/bonusBomb.png");

	effX3 = DBCCFactory::getInstance()->buildArmatureNode("eff_button_daily_gift");
	if (effX3)
	{
		bonusX3->addChild(effX3);
		//effIcon->setPosition(arrayNextEntity[i]->getPositionX(), bgBottom->getPositionY());
		effX3->gotoAndPlay("vienkhung", -1, -1, -1);
		effX3->setScale(0.43);
		/*effIcon->setCompleteListener([](dragonBones::DBCCArmatureNode* armature) {
			armature->setVisible(false);
		});*/
	}

	Scale9Sprite* bgNum = Scale9Sprite::create("480_800/gameBlockPuzzel/bgNumber.png");
	bonusX3->addChild(bgNum);
	bgNum->setContentSize(Size(bonusX3->getWidth(), 30));
	bgNum->setPosition(0, -bonusX3->getHeight() * 0.5 + 15);
	bgNum->setOpacity(150);

	lbX3 = Text::create("0", "fonts/tahomabd.ttf", 22);
	lbX3->enableOutline(Color4B(115, 37, 31, 255), 2);
	lbX3->setTextHorizontalAlignment(TextHAlignment::CENTER);
	lbX3->setAnchorPoint(ccp(0.5f, 0.5f));
	bonusX3->addChild(lbX3);
	lbX3->setPosition(Vec2(0, bgNum->getPositionY() + 3));

	bgNum = Scale9Sprite::create("480_800/gameBlockPuzzel/bgNumber.png");
	bonusBomb->addChild(bgNum);
	bgNum->setContentSize(Size(bonusBomb->getWidth(), 30));
	bgNum->setPosition(0, -bonusBomb->getHeight() * 0.5 + 15);
	bgNum->setOpacity(150);

	lbBomb = Text::create("0", "fonts/tahomabd.ttf", 22);
	lbBomb->enableOutline(Color4B(115, 37, 31, 255), 2);
	lbBomb->setTextHorizontalAlignment(TextHAlignment::CENTER);
	lbBomb->setAnchorPoint(ccp(0.5f, 0.5f));
	bonusBomb->addChild(lbBomb);
	lbBomb->setPosition(Vec2(0, bgNum->getPositionY() + 3));

	bgNum = Scale9Sprite::create("480_800/gameBlockPuzzel/bgNumber.png");
	bonusExchange->normalImage->addChild(bgNum);
	bgNum->setContentSize(Size(bonusExchange->getWidth(), 30));
	bgNum->setPosition(0, -bonusExchange->getHeight() * 0.5 + 15);
	bgNum->setOpacity(150);

	lbExchange = Text::create("0", "fonts/tahomabd.ttf", 22);
	lbExchange->enableOutline(Color4B(115, 37, 31, 255), 2);
	lbExchange->setTextHorizontalAlignment(TextHAlignment::CENTER);
	lbExchange->setAnchorPoint(ccp(0.5f, 0.5f));
	bonusExchange->normalImage->addChild(lbExchange);
	lbExchange->setPosition(Vec2(0, bgNum->getPositionY() + 3));

	
}

void GUIGame::initBottom()
{
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();

	if (size.width * 1.0f / size.height >= 2.99f / 4.0f)
		widthBoard = size.width * 0.7f;
	else if (size.width * 1.0f / size.height >= 1.99f / 3.0f)
		widthBoard = size.width * 0.8f;
	else if (size.width * 1.0f / size.height >= 2.99f / 5.0f)
		widthBoard = size.width * 0.9f;
	else
		widthBoard = size.width * 0.95f;

	bgBottom = Scale9Sprite::create("480_800/gameBlockPuzzel/board.png");
	addChild(bgBottom);
	float w = widthBoard * 1.05;
	bgBottom->setContentSize(Size(w, w / 4));
	bgBottom->setPosition(size.width * 0.5, size.height * 0.12 + bgBottom->getContentSize().height * 0.5);

	for (int i = 0; i < 3; i++) {
		arrayNextEntity[i] = new BaseEntity();
		arrayNextEntity[i]->setVisible(false);
	}
}

void okFunction() {
	game->endGame();
}

void GUIGame::onButtonRelease(int buttonID, CCTouch* touch)
{
	switch (buttonID)
	{
	case BTN_DOWNLOAD:
	{
		JNIUtils::openApp("com.lightgames.blockPuzzleExtreme");
	}
	break;
	case BTN_BACK_ID:
	{
       
		saveGame();
		GUIManager::getInstance().removeAllGui();
		GUIManager::getInstance().showGui(&GUIManager::getInstance().guiMinigames);
	}
	break;
	case BTN_HELP:
	{
		//GUIManager::getInstance().removeAllGui();
		GUIManager::getInstance().showGui(&GUIManager::getInstance().guiHelpBlock);
	}
	break;
	case BTN_SOUND_ID:
	{
		
		game->music = !game->music;
		if (game->music)
		{
			//GameSound::playBackground();
			btnSound->normalImage->setImage("btnSoundOn.png");
		}
		else
		{
			//GameSound::stopBackground();
			btnSound->normalImage->setImage("btnSoundOff.png");
		}

		CCUserDefault::sharedUserDefault()->setBoolForKey("music", game->music);
		CCUserDefault::sharedUserDefault()->flush();
	}
	break;
	case BTN_EXCHANGE_ID:
	{
		if (numExchange > 0) {
			this->genNextEntity(true);
			numExchange--;
			lbExchange->setText(GameUtility::toString(numExchange));
		}
		break;
	}
	default:
		break;
	}
}

void GUIGame::update(float delta) {
	if (isInitted() == false)
		return;
	if (timeX3 > 0) {
		timeX3 = timeX3 - delta;
		int time = timeX3;
		lbX3->setText(GameUtility::toString(time));
	}
	else {
		lbX3->setText("0");
		effX3->setVisible(false);
	}
}


void GUIGame::showGUI()
{
	BaseGUI::showGUI();
	setVisible(true);
	GUIManager::getInstance().addToListGui(this);
	game->showHelpBlock = false;
	if (game->showHelpBlock) {
		countHelp = 1;
		makeHelp1();
		UserDefault::getInstance()->setBoolForKey("showHelpBlock", false);
	}
	else {
		countHelp = 0;
		newGame();
	}
	//newGame();
}

void GUIGame::newGame()
{
	for (int i = 0; i < arrayLabelEffect.size(); i++) {
		arrayLabelEffect[i]->setVisible(false);
	}
	for (int i = 0; i < arrayBlockEffect.size(); i++)
	{
		arrayBlockEffect[i]->setVisible(false);
	}
	//game->isPlayingBlock = false;
	countNoBonus = 0;
	isExtraTime = false;
	isNewBest = false;
	for (int i = 0; i < 3; i++) {
		if (arrayNextEntity[i]->isVisible()) {
			arrayNextEntity[i]->removeFromParent();
		}
	}

	if (game->isPlayingBlock) {
		numBomb = game->arrayBonus[2];
		numExchange = game->arrayBonus[0];
		timeX3 = game->arrayBonus[1];
		score = game->saveScore;
		currentScore = score;
		updateScore();
		currentEntity = NULL;
		loadNextEntity(game->arrayNextBlock);
		updateCell();
	}
	else {
		score = 0;
		currentScore = 0;
		updateScore();
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++) {
				game->dataBlockPuzzel[i][j] = 0;
			}
		currentEntity = NULL;
		genNextEntity();
		updateCell();
		numBomb = 0;
		numExchange = 0;
		timeX3 = 0;
	}
	updateBomb();
	updateExchange();
	updateX3();
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++) {
			arrayCell[i][j]->newGame();
		}
	for (int i = 0; i < 8; i++) {
		float scale = arrayBgCell[i][i]->getScale();
		for (int j = 0; j < i; j++) {
			arrayBgCell[i][j]->setScale(0);
			arrayBgCell[i][j]->runAction(Sequence::create(
				DelayTime::create(0.05 * i),
				EaseExponentialOut::create(ScaleTo::create(0.5, scale)),
				NULL
			));
			arrayBgCell[j][i]->setScale(0);
			arrayBgCell[j][i]->runAction(Sequence::create(
				DelayTime::create(0.05 * i),
				EaseExponentialOut::create(ScaleTo::create(0.5, scale)),
				NULL
			));
		}
		arrayBgCell[i][i]->setScale(0);
		arrayBgCell[i][i]->runAction(Sequence::create(
			DelayTime::create(0.05 * i),
			EaseExponentialOut::create(ScaleTo::create(0.5, scale)),
			NULL
		));
	}
	
	
	gameState = GameStateBlock::PLAY_BLOCK;
	GameSound::playStart();
}

void GUIGame::effectScore()
{
	currentScore = currentScore + deltaScore;

	if (abs(currentScore - score) <= abs(2 * deltaScore))
	{
		currentScore = score;
		labelScore->setText(GameUtility::toString(currentScore).c_str());
		return;
	}
	labelScore->setText(GameUtility::toString(currentScore).c_str());
	labelScore->runAction(CCSequence::create(CCDelayTime::create(0.05f), CCCallFunc::create(this, callfunc_selector(GUIGame::effectScore)), NULL));

}

void GUIGame::updateScore()
{
	if (score != currentScore) {
		deltaScore = (score - currentScore) / 10;
		if (deltaScore == 0) {
			if (score > currentScore)
				deltaScore = 1;
			else {
				deltaScore = -1;
			}
		}
		this->effectScore();
	}
	else {
		labelScore->setText(GameUtility::toString(score).c_str());
	}


	if (this->score > game->highscoreBlock) {
		game->highscoreBlock = this->score;
		CCUserDefault::sharedUserDefault()->setIntegerForKey("highscoreBlock", game->highscoreBlock);
		CCUserDefault::sharedUserDefault()->flush();
	}
	labelHighscore->setText(GameUtility::toString(game->highscoreBlock).c_str());
}

void okEnd() {
	GUIManager::getInstance().guiGame.newGame();
}

void GUIGame::endGame()
{
	GUIManager::getInstance().guiResult.showGUI(score, game->highscoreBlock);
    
}

void GUIGame::updateBomb()
{
	lbBomb->setText(GameUtility::toString(numBomb));
	if (numBomb > 0) {
		bonusBomb->setOpacity(255);
	}
	else {
		bonusBomb->setOpacity(100);
	}
}

void GUIGame::updateX3()
{
	lbX3->setText(GameUtility::toString((int)(timeX3)));
	if (timeX3 > 0) {
		effX3->setVisible(true);
		bonusX3->setOpacity(255);
	}
	else {
		effX3->setVisible(false);
		bonusX3->setOpacity(100);
	}
}

void GUIGame::updateExchange()
{
	lbExchange->setText(GameUtility::toString(numExchange));
	if (numExchange > 0) {
		bonusExchange->normalImage->setOpacity(255);
	}
	else {
		bonusExchange->normalImage->setOpacity(100);
	}
}

void GUIGame::updateCell(bool canGen)
{
	arrayNewCell.clear();
	
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++) {
			arrayCell[i][j]->setBg(game->dataBlockPuzzel[i][j]);
			arrayCell[i][j]->setWidth(sizeCell * ConfigDataBlock::RATE_NORMAL_CELL * 0.95);
			arrayCell[i][j]->setHeight(sizeCell * ConfigDataBlock::RATE_NORMAL_CELL * 0.95);
			if (game->dataBlockPuzzel[i][j] >= 40) {
				arrayNewCell.push_back(arrayCell[i][j]);
				arrayCell[i][j]->setOpacity(255);
				arrayCell[i][j]->setWidth(sizeCell * ConfigDataBlock::RATE_CURRENT_NEXT_CELL);
				arrayCell[i][j]->setHeight(sizeCell * ConfigDataBlock::RATE_CURRENT_NEXT_CELL);
				game->dataBlockPuzzel[i][j] = game->dataBlockPuzzel[i][j] - 40;
				float scale = sizeCell * ConfigDataBlock::RATE_NORMAL_CELL * 0.9 / arrayCell[i][j]->getWidth();
				arrayCell[i][j]->runAction(ScaleTo::create(0.2, scale));
			}
			else if (game->dataBlockPuzzel[i][j] > 20) {
				arrayCell[i][j]->setOpacity(100);
				arrayCell[i][j]->setWidth(sizeCell * ConfigDataBlock::RATE_CURRENT_NEXT_CELL);
				arrayCell[i][j]->setHeight(sizeCell * ConfigDataBlock::RATE_CURRENT_NEXT_CELL);
			}
			else if (game->dataBlockPuzzel[i][j] == 0){
				arrayCell[i][j]->setOpacity(0);
			}
			else {
				arrayCell[i][j]->setOpacity(255);
			}
		}
	if (canGen) {
		int i = 0;
		for (i = 0; i < 3; i++) {
			if (arrayNextEntity[i]->isVisible())
				break;
		}
		if (i == 3) {
			// gen khoi block tiep theo
			genNextEntity();
		}
	}
}

void GUIGame::checkWillScore()
{
	bool newVibrate = false;
	vector <PointGame> arrayPoint;
	for (int i = 0; i < 8; i++) {
		int j;
		for (j = 0; j < 8; j++) {
			if (game->dataBlockPuzzel[i][j] == 0)
				break;
		}
		if (j == 8) { // an diem
			for (j = 0; j < 8; j++) {
				if (!arrayCell[i][j]->isVibrate)
				{
					newVibrate = true;
				}
				arrayCell[i][j]->doVibrate(true);
				PointGame p;
				p.x = i;
				p.y = j;
				arrayPoint.push_back(p);
			}
		}
	}

	for (int i = 0; i < 8; i++) {
		int j;
		for (j = 0; j < 8; j++) {
			if (game->dataBlockPuzzel[j][i] == 0) {
				break;
			}
		}
		if (j == 8) {
			for (j = 0; j < 8; j++) {
				if (!arrayCell[j][i]->isVibrate)
				{
					newVibrate = true;
				}
				arrayCell[j][i]->doVibrate(true);
				PointGame p;
				p.x = j;
				p.y = i;
				arrayPoint.push_back(p);
			}
		}
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (arrayCell[i][j]->isVibrate) {
				int k;
				for (k = 0; k < arrayPoint.size(); k++) {
					if (arrayPoint[k].x == i && arrayPoint[k].y == j) {
						break;
					}
				}
				if (k >= arrayPoint.size()) {
					arrayCell[i][j]->setBg(game->dataBlockPuzzel[i][j]);
					arrayCell[i][j]->doVibrate(false);
				}
				else {
					arrayCell[i][j]->setBg(currentEntity->idBlock);
				}
			}
		}
	}
	if (newVibrate)
	{
		JNIUtils::vibrate(10);
		GameSound::playOpenCell();
	}
}

bool GUIGame::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint p = pTouch->getLocation();
	if (gameState == PLAY) {
		if (currentEntity == NULL) {
			for (int i = 0; i < 3; i++) {
				if (this->countHelp == 1) {
					if (i != 1) {
						continue;
					}
				}
				else if (this->countHelp == 2) {
					continue;
				}
				else if (this->countHelp == 3) {
					if (i != 0) {
						continue;
					}
				}
				if (arrayNextEntity[i] != NULL && arrayNextEntity[i]->isVisible()) {
					float w = bgBottom->getContentSize().width / 3;
					float h = bgBottom->getContentSize().height;
					float sX = bgBottom->getPositionX() - bgBottom->getContentSize().width * 0.5 + w * i;
					float sY = bgBottom->getPositionY() - bgBottom->getContentSize().height * 0.5;

					if (p.x > sX && p.x < sX + w && p.y > sY && p.y < sY + h) {
						currentEntity = arrayNextEntity[i];
						currentEntity->setPosition(p.x, p.y + 50);
						currentEntity->setIsNext(false);
						currentEntity->idArray = i;
						GameSound::playClick();
						return true;
					}
					//	currentEntity->setPos(pTouch->getLocation().x + 20, pTouch->getLocation().y + 20);
				}
			}
		}
		
		if (numBomb > 0) {
			if (this->countHelp > 0 && this->countHelp != 2)
				return BaseGUI::onTouchBegan(pTouch, pEvent);
			iconBomb->setOpacity(255);
			float w = bonusBomb->getWidth();
			float sX = bonusBomb->getPositionX() - bonusBomb->getWidth() * 0.5;
			float sY = bonusBomb->getPositionY() - bonusBomb->getHeight() * 0.5;
			if (p.x > sX && p.x < sX + w && p.y > sY && p.y < sY + w) {
				iconBomb->setVisible(true);
				iconBomb->stopAllActions();
				iconBomb->setOpacity(255);
				iconBomb->setPosition(p.x, p.y + iconBomb->getHeight() * 0.5 + 40);
				GameSound::playClick();
				return true;
			}
		}
	}
	return BaseGUI::onTouchBegan(pTouch, pEvent);
}

void GUIGame::onTouchMoved(CCTouch* touch, CCEvent* event) {
	BaseGUI::onTouchMoved(touch, event);
	if (currentEntity != NULL && gameState == PLAY) {
		CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();
		currentEntity->setPosition(touch->getLocation().x, touch->getLocation().y + 50);
		normalData();
		currentEntity->changeNextMap();
		updateCell();
		checkWillScore();
	}
	else if (iconBomb->isVisible()) {
		iconBomb->setPosition(Vec2(touch->getLocation().x, touch->getLocation().y + iconBomb->getHeight() * 0.5 + 40));
		PointGame p = getPointInBoard(iconBomb->getPositionX() - iconBomb->getWidth() * 0.4, iconBomb->getPositionY() - iconBomb->getHeight() * 0.4);
		if (p.x >= 0 && p.y >= 0 && p.x < 8 && p.y < 8 && game->dataBlockPuzzel[p.y][p.x] > 0) {
			arrayCell[p.y][p.x]->doVibrate(true);
		}
		
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++) {
				if (arrayCell[i][j]->isVibrate && (i != p.y || j != p.x)) {
					arrayCell[i][j]->doVibrate(false);
				}
			}
	}
}

void GUIGame::onTouchEnded(CCTouch* touch, CCEvent* event) {
	BaseGUI::onTouchEnded(touch, event);
	
	if (currentEntity != NULL && gameState == PLAY) {
	//	currentEntity->setPosition(touch->getLocation().x, touch->getLocation().y + 30);
		normalData();
        bool canPut = false;
		if (currentEntity->validInMap()) {
			
            if (countHelp > 0) {
                PointGame p = currentEntity->getPointInMap();
                if (countHelp == 1) {
                    if (p.x == 0 && p.y == 0)
                        canPut = true;
                }
                else if (countHelp == 3){
					if (p.y == 0 && p.x == 2) {
						canPut = true;
						iconHand->stopAllActions();
						iconHand->setVisible(false);
					}
                }
            }
            else {
                canPut = true;
            }
			
			if (canPut) {
                currentEntity->changeCurrentMap();
                lastTouchEnd = touch->getLocation();
                gameState = GameStateBlock::TOUCH_BLOCK;
                runAction(CCSequence::create(CCDelayTime::create(0.1f), CCCallFunc::create(this, callfunc_selector(GUIGame::callbackTouchEnd)), NULL));
                GameSound::playMove();
            }
            else {
                updateCell();
                int idArray = currentEntity->idArray;
                currentEntity = NULL;
                arrayNextEntity[idArray]->setIsNext(true);
                GameSound::playFail();
            }
			
		}
		else {
			int idArray = currentEntity->idArray;
			currentEntity = NULL;
			arrayNextEntity[idArray]->setIsNext(true);
			GameSound::playFail();
		}
		//updateCell();
	}
	else if (iconBomb->isVisible()) {
		PointGame p = getPointInBoard(iconBomb->getPositionX() - iconBomb->getWidth() * 0.4, iconBomb->getPositionY() - iconBomb->getHeight() * 0.4);
		bool valid = true;
		if (countHelp == 2) {
			if (p.x != 2 || p.y != 2)
				valid = false;
		}
		if (p.x >= 0 && p.y >= 0 && p.x < 8 && p.y < 8 && game->dataBlockPuzzel[p.y][p.x] > 0) {
			if (valid) {
				arrayCell[p.y][p.x]->setOpacity(0);
				game->dataBlockPuzzel[p.y][p.x] = 0;
				DBCCArmatureNode* effIcon = DBCCFactory::getInstance()->buildArmatureNode("no_top");
				if (effIcon)
				{
					addChild(effIcon);
					effIcon->setPosition(arrayCell[p.y][p.x]->getPosition());
					effIcon->setVisible(true);
					effIcon->gotoAndPlay("run", -1, -1, -1);
				}
				numBomb--;
				lbBomb->setText(GameUtility::toString(numBomb));
				iconBomb->setVisible(false);
				checkEndGame();
				GameSound::playBomb();
				if (countHelp == 2) {
					countHelp = 3;
					makeHelp3();
				}
				bonusBomb->stopAllActions();
				bonusExchange->normalImage->stopAllActions();
				JNIUtils::vibrate(20);
			}
			else {
				arrayCell[p.y][p.x]->doVibrate(false);
			}
		}
		else {
			iconBomb->runAction(Sequence::create(
				EaseExponentialOut::create(MoveTo::create(0.5, bonusBomb->getPosition())),
				FadeOut::create(0.5),
				Hide::create(),
				NULL
			));
			GameSound::playFail();
		}
	}
	
}

void GUIGame::callbackTouchEnd()
{
	
	gameState = GameStateBlock::PLAY_BLOCK;
	if (game->isPlayingBlock == false) {
		game->isPlayingBlock = true;
	}
	
	int idArray = currentEntity->idArray;
	arrayNextEntity[idArray]->setVisible(false);
	arrayNextEntity[idArray]->removeFromParent();
	
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++) {
			if (arrayCell[i][j]->isVibrate) {
				arrayCell[i][j]->doVibrate(false);
				game->dataBlockPuzzel[i][j] = currentEntity->idBlock;
			}
		}
	updateCell(false); // ko cho gen next luon de phong con co the an duoc diem
	//return;
	int score = checkScore();
	
	// gen Bonus, genBonus
	if (score == 0) {
		// random Bonus
		float rand1 = GameUtility::getRandom();
		int posRand = -1;
		float rate = (10 - countNoBonus * 1.5) / 10;
		if (rate < 0.1) {
			rate = 0.1;
		}
		if (rand1 > rate) {
			posRand = arrayNewCell.size() * GameUtility::getRandom() * 0.99999;
		}
		if (posRand >= 0) {
			CellBlock* cell = arrayNewCell[posRand];
			float randomValue = GameUtility::getRandom();
			int randomNum = GameUtility::getRandom() * 3 + 2;
			if (randomValue < 0.4) {
				cell->setBonus(CellBonus::X2, randomNum);
			}
			else if (randomValue < 0.78) {
				cell->setBonus(CellBonus::BOMB, randomNum);
			}
			else if (randomValue < 0.93) {
				cell->setBonus(CellBonus::EXCHANGE, randomNum);
			}
			else {
				cell->setBonus(CellBonus::EXTRA, randomNum);
			}
			//	cell->setBonus(CellBonus::EXTRA);
			countNoBonus = 0;
		}
		else {
			countNoBonus++;
		}
		this->checkIsNewBest(currentEntity->getNumCell());
		this->score = this->score + currentEntity->getNumCell();
		updateScore();
	}
	else {
		
	}
	currentEntity = NULL;
	if (gameState == GameStateBlock::PLAY_BLOCK || gameState == GameStateBlock::EFFECT_BLOCK)
	{
		int i = 0;
		for (i = 0; i < 3; i++) {
			if (arrayNextEntity[i]->isVisible())
				break;
		}
		if (i == 3) {
			// gen khoi block tiep theo
			genNextEntity();
		}
	}
	saveGame();
}

void GUIGame::normalData()
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (game->dataBlockPuzzel[i][j] > 20)
				game->dataBlockPuzzel[i][j] = 0;
		}
	}
}

CCPoint GUIGame::getPosCell(int x, int y)
{
	float posX = sizeCell * (x + 0.5f) + startX;
	float posY = sizeCell * (y + 0.5f) + startY;
	return ccp(posX, posY);
}

int GUIGame::checkScore()
{
	int score = 0;
	vector<int>arrayScoreRow;
	vector<int>arrayScoreColumn;
	for (int i = 0; i < 8; i++) {
		int j;
		for (j = 0; j < 8; j++) {
			if (game->dataBlockPuzzel[i][j] == 0)
				break;
		}
		if (j == 8) { // an diem
			arrayScoreRow.push_back(i);
		}
	}

	for (int i = 0; i < 8; i++) {
		int j;
		for (j = 0; j < 8; j++) {
			if (game->dataBlockPuzzel[j][i] == 0) {
				break;
			}
		}
		if (j == 8) {
			arrayScoreColumn.push_back(i);
		}
	}

	int count = 0;
	vector <PointGame> arrayEat;
	// effect hinh anh
	for (int i = 0; i < arrayScoreRow.size(); i++) {
		for (int j = 0; j < 8; j++) {
			arrayCell[arrayScoreRow.at(i)][j]->runAction(Sequence::create(
				DelayTime::create(0.08 * j),
				CCCallFuncN::create(CC_CALLBACK_1(GUIGame::callbackShowParticle, this, arrayScoreRow.at(i), j, currentEntity->idBlock)),
				NULL
			));
			game->dataBlockPuzzel[arrayScoreRow.at(i)][j] = 0;
			count++;
			score = score + count;
			arrayEat.push_back(PointGame(arrayScoreRow.at(i), j));
			if (arrayCell[arrayScoreRow.at(i)][j]->idBonus == EXTRA)
				gameState = GameStateBlock::EFFECT_BLOCK;
		}
	}

	for (int i = 0; i < arrayScoreColumn.size(); i++) {
		for (int j = 0; j < 8; j++) {
			arrayCell[j][arrayScoreColumn.at(i)]->runAction(Sequence::create(
				DelayTime::create(0.08 * j),
				CCCallFuncN::create(CC_CALLBACK_1(GUIGame::callbackShowParticle, this, j, arrayScoreColumn.at(i), currentEntity->idBlock)),
				NULL
			));
			game->dataBlockPuzzel[j][arrayScoreColumn.at(i)] = 0;
			count++;
			score = score + count;
			arrayEat.push_back(PointGame(j, arrayScoreColumn.at(i)));
			if (arrayCell[j][arrayScoreColumn.at(i)]->idBonus == EXTRA)
				gameState = GameStateBlock::EFFECT_BLOCK;
		}
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			bool inEat = false;
			for (int k = 0; k < arrayEat.size(); k++) {
				if (i == arrayEat.at(k).x && j == arrayEat.at(k).y) {
					inEat = true;
					break;
				}
			}
			if (!inEat) {
				arrayCell[i][j]->decreaseBonus();
			}
		}
	}

	if (score > 0) {
		if (count > 8) {
			string s;
			if (count <= 14) {
				s = "480_800/gameBlockPuzzel/iconGood.png";
				JNIUtils::vibrate(20);
			}
			else if (count <= 21) {
				s = "480_800/gameBlockPuzzel/iconGreat.png";
				JNIUtils::vibrate(30);
			}
			else {
				s = "480_800/gameBlockPuzzel/iconCool.png";
				JNIUtils::vibrate(40);
			}
			showEffectLabel(s);
			GameSound::playScoreExtra();

			bgCenter->runAction(Repeat::create(
				Sequence::create(
					RotateBy::create(0.04, 2),
					RotateBy::create(0.08, -4),
					RotateBy::create(0.04, 2),
					NULL
				), 2
			));

			for (int i = 0; i < 8; i++)
				for (int j = 0; j < 8; j++) {
					if (game->dataBlockPuzzel[i][j] > 0) {
						arrayCell[i][j]->doVibrateNTime(2);
					}
				}
		}
		else {
			JNIUtils::vibrate(10);
			GameSound::playScore1();
		}
		addScore(score, currentEntity->getPosition());
		runAction(CCSequence::create(CCDelayTime::create(0.08f * 8), CCCallFunc::create(this, callfunc_selector(GUIGame::callbackCheckScore)), NULL));
		gameState = GameStateBlock::SCORE_BLOCK;
        
        if(game->showHelpBlock) {
             iconHand->setVisible(false);
        }
	}
	else {
		checkEndGame();
	}
	return score;
}

void GUIGame::addScore(int add, Vec2 pos)
{
	if (timeX3 > 0) {
		add = add * 3;
	}
	Text* labeleffect = getLabelEffect();
	if (timeX3 > 0) {
		labeleffect->setText((GameUtility::toString(add) + "*3").c_str());
		add = add * 3;
	}
	else {
		labeleffect->setText((GameUtility::toString(add) + "").c_str());
	}
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();
	if (pos.x < size.width * 0.1) {
		pos.x = size.width * 0.1;
	}
	else if (pos.x > size.width * 0.9) {
		pos.x = size.width * 0.9;
	}
	labeleffect->setPosition(pos);
	labeleffect->setScale(0);
	labeleffect->runAction(Sequence::create(
		EaseBackOut::create(ScaleTo::create(0.5, 1)),
		DelayTime::create(1.0),
		FadeOut::create(0.5),
		NULL
	));
	labeleffect->runAction(EaseBackOut::create(MoveBy::create(0.5, Vec2(0, 100))));
	checkIsNewBest(add);
	this->score = this->score + add;
	updateScore();
}

void GUIGame::callbackShowParticle(Node* pSender, int row, int column, int id)
{
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();
	this->arrayCell[row][column]->runAction(FadeOut::create(0.2f));
	showParticle(arrayCell[row][column]->getPositionX(), arrayCell[row][column]->getPositionY(), id);
	if (this->arrayCell[row][column]->idBonus != CellBonus::NONE) {
		Sprite* iconBonus = Sprite::create("480_800/gameBlockPuzzel/iconBomb.png");
		addChild(iconBonus, 1);
		iconBonus->setPosition(this->arrayCell[row][column]->getPosition());
		if (this->arrayCell[row][column]->idBonus != CellBonus::EXTRA) {
			Vec2 posEnd;
			if (this->arrayCell[row][column]->idBonus == CellBonus::BOMB) {
				numBomb++;
				posEnd = bonusBomb->getPosition();
				iconBonus->setTexture("480_800/gameBlockPuzzel/iconBomb.png");
			}
			else if (this->arrayCell[row][column]->idBonus == CellBonus::EXCHANGE) {
				numExchange++;
				posEnd = bonusExchange->getPosition();
				iconBonus->setTexture("480_800/gameBlockPuzzel/iconExchange.png");
			}
			else {
				timeX3 = timeX3 + 25;
				posEnd = bonusX3->getPosition();
				iconBonus->setTexture("480_800/gameBlockPuzzel/iconX3.png");
				effX3->setVisible(true);
			}
			
			auto posStart = this->arrayCell[row][column]->getPosition();
			auto pCX = CCRANDOM_0_1() * size.width;
			auto pCY = CCRANDOM_0_1() * size.height;
			auto posCenter = Vec2(pCX, pCY);
			ccBezierConfig config;
			config.controlPoint_1 = posStart;
			config.controlPoint_2 = posCenter;
			config.endPosition = posEnd;
			auto actMove = EaseExponentialOut::create(BezierTo::create(0.7, config));
			iconBonus->runAction(Sequence::create(
				actMove,
				FadeOut::create(0.5),
				CCCallFunc::create(this, callfunc_selector(GUIGame::callbackEffectBonus)),
				NULL
			));
			arrayCell[row][column]->setBonus(CellBonus::NONE);
		}
		else {
			if (!isExtraTime) {
				iconBonus->setTexture("480_800/gameBlockPuzzel/iconExtra.png");
				iconBonus->runAction(Sequence::create(
					EaseExponentialOut::create(MoveTo::create(0.5, bgCenter->getPosition())),
					DelayTime::create(0.5),
					ScaleTo::create(1.0, 10),
					RemoveSelf::create(),
					CCCallFunc::create(this, callfunc_selector(GUIGame::callbackEffectExtra)),
					NULL
				));
				iconBonus->runAction(Sequence::create(
					DelayTime::create(1.0),
					FadeOut::create(0.5),
					NULL
				));
				GameSound::playScore5();
				gameState = GameStateBlock::EFFECT_BLOCK;
				isExtraTime = true;
			}
			else {
				iconBonus->removeFromParent();
			}
		}
	}
	this->arrayCell[row][column]->setBonus(CellBonus::NONE);
}

void GUIGame::callbackEffectExtra()
{
	auto eff = DBCCFactory::getInstance()->buildArmatureNode("skill_elect");
	if (eff) {
		this->addChild(eff);
		eff->setPosition(bgCenter->getPosition());
		eff->gotoAndPlay("step1", -1, -1, 1);
		eff->setCompleteListener([](dragonBones::DBCCArmatureNode* armature) {
			armature->gotoAndPlay("step2", -1, -1, 1);
			armature->setCompleteListener([](dragonBones::DBCCArmatureNode* armature) {
				armature->removeFromParent();
			});
		});
	}
	runAction(Sequence::create(
		DelayTime::create(0.6),
		CCCallFunc::create(this, callfunc_selector(GUIGame::eatAll)),
		NULL
	));
	GameSound::playThunder();
}

void callbackShowHelp() {
	GUIManager::getInstance().guiGame.newGame();
}

void GUIGame::eatAll()
{
	int score = 0;
	int count = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (game->dataBlockPuzzel[i][j] > 0) {
				arrayCell[i][j]->setBonus(CellBonus::NONE);
				arrayCell[i][j]->runAction(Sequence::create(
					DelayTime::create(0.08 * j),
					CCCallFuncN::create(CC_CALLBACK_1(GUIGame::callbackShowParticle, this, i, j, game->dataBlockPuzzel[i][j])),
					NULL
				));
				game->dataBlockPuzzel[i][j] = 0;
				count++;
				score = score + count;
			}
		}
	}
	addScore(score, bgCenter->getPosition());
	GameSound::playScore5();
	if (countHelp > 0) {
		countHelp = 0;
		game->showHelpBlock = false;
		CCUserDefault::sharedUserDefault()->setBoolForKey("showHelpBlock", false);
		CCUserDefault::sharedUserDefault()->flush();
		game->isPlayingBlock = false;
		GUIManager::getInstance().guiDialog.showGUI("Are you ready to start the Game?", &callbackShowHelp, true);
	}
	gameState = GameStateBlock::PLAY_BLOCK;
	isExtraTime = false;
}

void GUIGame::callbackEffectBonus()
{
	updateBomb();
	updateX3();
	updateExchange();
}

void GUIGame::showParticle(float posX, float posY, int id)
{
	CCSprite* sprite = getBlockEffect();
	// addChild(sprite);
	sprite->setPosition(ccp(posX, posY));
	sprite->setTexture(CCTextureCache::sharedTextureCache()->addImage(GameUtility::getTextureCell(id).c_str()));
	sprite->setScale(arrayCell[0][0]->getScaleX());
	sprite->runAction(CCSequence::create(
		CCSpawn::create(
			CCEaseExponentialIn::create(CCMoveBy::create(0.4, ccp(0, 100))),
			// CCFadeOut::create(0.5),
			CCEaseBackIn::create(CCScaleTo::create(0.4, 0)),
			NULL),
		CCHide::create(),
		NULL));

	Layer *layer = layerMgr->getLayerByIndex(LAYER_EFFECT_GAME);
	ParticleEffect *effect = new ParticleEffect();
	effect->create("particles/explode.plist", layer);
	effect->particle->setTexture(TextureCache::sharedTextureCache()->addImage(GameUtility::getTextureCell(id)));

	effect->particle->setPosition(posX, posY);
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	float scale = (size.width / DEFAULT_SCREEN_WIDTH) > (size.height / DEFAULT_SCREEN_HEIGHT) ? (size.width / DEFAULT_SCREEN_WIDTH) : (size.height / DEFAULT_SCREEN_HEIGHT);
		effect->particle->setScale(0.4);
	effect->particle->setAutoRemoveOnFinish(true);
	effect->particle->setBlendAdditive(false);
}

void GUIGame::genNextEntity(bool isEffect)
{
	bonusBomb->stopAllActions();
	bonusExchange->normalImage->stopAllActions();
	int arrayRand[3];
	for (int i = 0; i < 3; i++) {
		arrayRand[i] = GameUtility::getRandom() * 11 + 1;
	}
	loadNextEntity(arrayRand, isEffect);
	GameSound::playClick();
}

void GUIGame::loadNextEntity(int arrayNext[3], bool isEffect)
{
	for (int i = 0; i < 3; i++) {
		arrayNextEntity[i]->removeFromParent();
	}
	float widthX = bgBottom->getContentSize().width / 3;
	float sX = bgBottom->getPositionX() - bgBottom->getContentSize().width * 0.5;
	float sY = bgBottom->getPositionY();
	for (int i = 0; i < 3; i++) {
		int randomValue = arrayNext[i];
		if (randomValue == 0) {
			arrayNextEntity[i] = getEntity(1);
			arrayNextEntity[i]->setVisible(false);
		}
		else
			arrayNextEntity[i] = getEntity(randomValue);
		game->arrayNextBlock[i] = randomValue;
		arrayNextEntity[i]->isNext = true;
		this->addChild(arrayNextEntity[i]);

		arrayNextEntity[i]->setPosition(sX + (i + 0.5) * widthX, sY - arrayNextEntity[i]->getRealHeight() * 0.5f);
		arrayNextEntity[i]->saveRoot();
		//arrayNextEntity[i]->setOpacity(0);
		float s = arrayNextEntity[i]->getScale();
		arrayNextEntity[i]->setScale(0);
		arrayNextEntity[i]->runAction(Sequence::create(
			DelayTime::create(isEffect ? 0.3 : 0),
			EaseBackOut::create(ScaleTo::create(0.5, s)),
			NULL
		));
		if (isEffect) {
			DBCCArmatureNode* effIcon = DBCCFactory::getInstance()->buildArmatureNode("cast_skill_cuong_phong");
			if (effIcon)
			{
				addChild(effIcon);
				effIcon->setPosition(arrayNextEntity[i]->getPositionX(), bgBottom->getPositionY());
				effIcon->setVisible(true);
				effIcon->gotoAndPlay("run", -1, -1, 1);
				effIcon->setCompleteListener([](dragonBones::DBCCArmatureNode* armature) {
					armature->setVisible(false);
				});
			}
		}
	}
	checkEndGame();
}

void GUIGame::callbackCheckScore()
{
    gameState = GameStateBlock::PLAY_BLOCK;
    if (countHelp > 0) {
        if (countHelp == 1) {
            countHelp = 2;
            makeHelp2();
        }
    }
    else {
        updateCell();
        checkEndGame();
    }
}

void GUIGame::checkEndGame()
{
	if (gameState == GameStateBlock::END_GAME_EFFECT_BLOCK)
		return;

	int i;
	for (i = 0; i < 3; i++) {
		if (arrayNextEntity[i]->isVisible()) {
			arrayNextEntity[i]->canPut();
		}
	}

	bool hasVisible = false;
	for (i = 0; i < 3; i++) {
		if (arrayNextEntity[i]->isVisible()) {
			hasVisible = true;
			if (arrayNextEntity[i]->canPut())
				break;
		}
	}
	if (i == 3 && hasVisible != false) {
		if (numBomb > 0 || numExchange > 0) {
			if (numBomb > 0) {
				bonusBomb->runAction(Repeat::create(
					Sequence::create(ScaleTo::create(0.2, 1.1), ScaleTo::create(0.2, 1.0), NULL), 100
				));
			}
			else {
				bonusExchange->normalImage->runAction(Repeat::create(
					Sequence::create(ScaleTo::create(0.2, 1.1), ScaleTo::create(0.2, 1.0), NULL), 100
				));
			}
		}
		else {
			startEndGame();
		}
	}
}

void GUIGame::startEndGame()
{
	gameState = END_GAME_EFFECT_BLOCK;
	game->isPlayingBlock = false;
	CCUserDefault::sharedUserDefault()->setBoolForKey("isPlaying", false);
	CCUserDefault::sharedUserDefault()->flush();
	int count = 0;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++) {
			if (game->dataBlockPuzzel[i][j] != 0) {
				//arrayCell[i][j]->runAction(CCSequence::create(CCDelayTime::create(0.01f * count)
					//, CCTintTo::create(0.05f, 191, 183, 183), NULL));
				arrayCell[i][j]->endGame(0.03 * count);
				count++;
			}
		}

	for (int i = 0; i < 3; i++) {
		if (arrayNextEntity[i]->isVisible()) {
			arrayNextEntity[i]->endGame();
		}
	}
	runAction(CCSequence::create(CCDelayTime::create(count * 0.03f + 0.5), CCCallFunc::create(this, callfunc_selector(GUIGame::endGame)), NULL));
	JNIUtils::sendEvent("end_game_block", "1");
}

Text* GUIGame::getLabelEffect()
{
	Text* label;
	int i;
	for (i = 0; i < arrayLabelEffect.size(); i++)
	{
		if (!arrayLabelEffect.at(i)->isVisible())
		{
			label = arrayLabelEffect.at(i);
			
		}
	}
	if (i == arrayLabelEffect.size())
	{
		label = Text::create("0", "fonts/tahomabd.ttf", 40);
		label->enableOutline(Color4B(115, 37, 31, 255), 4);
		label->setTextHorizontalAlignment(TextHAlignment::CENTER);
		label->setAnchorPoint(ccp(0.5f, 0.5f));

		arrayLabelEffect.push_back(label);
		this->addChild(label);
	}
	label->setVisible(true);
	label->setOpacity(255);
	label->setScale(1);
	return label;
}

BaseEntity* GUIGame::getEntity(int id)
{
	switch (id)
	{
	case 11:
		return new BigLBrick();
		break;
	case 1:
		return  new BigSquareBrick();
		break;
	case 2:
		return  new FiveRowBrick();
		break;
	case 3:
		return  new FourColumnBrick();
		break;
	case 4:
		return  new LBrick();
		break;
	case 5:
		return  new LSortBrick();
		break;
	case 6:
		return  new OneBrick();
		break;
	case 7:
		return  new SquareBrick();
		break;
	case 8:
		return  new TBrick();
		break;
	case 9:
		return  new ThreeRowBrick();
		break;
	case 10:
		return  new TwoColumnBrick();
		break;
	default:
		break;
	}
}

void GUIGame::makeHelp1() {
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++) {
            game->dataBlockPuzzel[i][j] = 0;
        }
    
    for (int i = 3; i < 8; i++)
        for (int j = 3; j < 5; j++) {
                game->dataBlockPuzzel[i][j] = 1;
            }
	game->dataBlockPuzzel[2][2] = 2;
	game->dataBlockPuzzel[2][5] = 2;
	for (int i = 0; i < 2; i++) {
		for (int j = 2; j < 8; j++) {
			game->dataBlockPuzzel[i][j] = 4;
		}
	}
	int arrayRand[] = { 1, 7, 4 };
	loadNextEntity(arrayRand, false);
    updateCell();
	arrayCell[1][6]->setBonus(CellBonus::BOMB, 3);
	arrayCell[5][3]->setBonus(CellBonus::EXTRA, 4);
    iconHand->setVisible(true);
	this->callbackHelp1();
}

void GUIGame::callbackHelp1() {
    iconHand->setPos(arrayNextEntity[1]->getPositionX(), arrayNextEntity[1]->getPositionY());
    iconHand->runAction(CCSequence::create(
		DelayTime::create(0.3f),
		CCMoveTo::create(1.0f, ccp(arrayCell[0][0]->getPosition().x + sizeCell * 0.2f, arrayCell[0][0]->getPositionY())),
		DelayTime::create(0.2f),
		CCMoveTo::create(0.0, ccp(arrayNextEntity[1]->getPositionX(), arrayNextEntity[1]->getPositionY())),
		CCCallFunc::create(this, callfunc_selector(GUIGame::callbackHelp1)),
		NULL
	));
}

void GUIGame::makeHelp2() {
	iconHand->stopAllActions();
	iconHand->setVisible(true);
	iconHand->setPos(bonusBomb->getPositionX(), bonusBomb->getPositionY() - bonusBomb->getHeight() * 0.5);
	iconHand->runAction(CCSequence::create(
		DelayTime::create(0.3f),
		CCMoveTo::create(0.5f, ccp(arrayCell[2][2]->getPosition().x, arrayCell[2][2]->getPositionY() - sizeCell * 0.2f)),
		DelayTime::create(0.2f),
		CCMoveTo::create(0.0, ccp(bonusBomb->getPositionX(), bonusBomb->getPositionY() - bonusBomb->getHeight() * 0.5)),
		CCCallFunc::create(this, callfunc_selector(GUIGame::makeHelp2)),
		NULL
	));
}

void GUIGame::makeHelp3() {
	iconHand->stopAllActions();
	iconHand->setVisible(true);
	iconHand->setPos(arrayNextEntity[0]->getPositionX(), arrayNextEntity[0]->getPositionY());
	iconHand->runAction(CCSequence::create(
		DelayTime::create(0.3f),
		CCMoveTo::create(1.0f, ccp(arrayCell[0][3]->getPosition().x, arrayCell[0][3]->getPositionY() - sizeCell * 0.2f)),
		DelayTime::create(0.2f),
		CCMoveTo::create(0.0, ccp(arrayNextEntity[0]->getPositionX(), arrayNextEntity[0]->getPositionY())),
		CCCallFunc::create(this, callfunc_selector(GUIGame::makeHelp3)),
		NULL
	));
}

PointGame GUIGame::getPointInBoard(float x, float y)
{
	int posX = (x - startX) / sizeCell + 0.5;
	int posY = (y - startY) / sizeCell + 0.5;
	PointGame p;
	p.x = posX;
	p.y = posY;
	return p;
}

void GUIGame::showEffectLabel(string s)
{
	auto eff = DBCCFactory::getInstance()->buildArmatureNode("tile_light");
	if (eff) {
		this->addChild(eff);
		eff->setPosition(bgCenter->getPosition());
		eff->gotoAndPlay("run", 0.5, -1, 1);
		eff->setCompleteListener([](dragonBones::DBCCArmatureNode* armature) {
			armature->removeFromParent();
		});
	}
	Sprite* img = Sprite::create(s.c_str());
	addChild(img);
	img->setPosition(bgCenter->getPosition());
	img->setOpacity(0);
	img->setScale(6);
	img->runAction(Sequence::create(
		EaseBounceOut::create(ScaleTo::create(0.6, 1.5)),
		DelayTime::create(2.0),
		FadeOut::create(0.5),
		RemoveSelf::create(),
		NULL
	));
	img->runAction(FadeIn::create(0.5));
}

void GUIGame::saveGame()
{
	if (game->isPlayingBlock && countHelp == 0) {
		string s = "";
		int index = 0;
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
			{
				if (i == 0 && j == 0)
				{
					s = s + GameUtility::toString(game->dataBlockPuzzel[i][j]);
				}
				else
				{
					s = s + "," + GameUtility::toString(game->dataBlockPuzzel[i][j]);
				}

			}
		for (int i = 0; i < 3; i++) {
			if (arrayNextEntity[i]->isVisible()) {
				CCUserDefault::sharedUserDefault()->setIntegerForKey(("dataNextBlock" + GameUtility::toString(i)).c_str(), game->arrayNextBlock[i]);
			}
			else {
				CCUserDefault::sharedUserDefault()->setIntegerForKey(("dataNextBlock" + GameUtility::toString(i)).c_str(), 0);
			}
			int bonus;
			if (i == 0) {
				bonus = numExchange;
			}
			else if (i == 1) {
				bonus = timeX3;
				if (bonus < 0) {
					bonus = 0;
				}
			}
			else {
				bonus = numBomb;
			}
			CCUserDefault::sharedUserDefault()->setIntegerForKey(("dataBonusBlock" + GameUtility::toString(i)).c_str(), bonus);
		}
		CCUserDefault::sharedUserDefault()->setIntegerForKey("scoreBlock", score);
		CCUserDefault::sharedUserDefault()->setStringForKey("dataBlock", s);
		CCUserDefault::sharedUserDefault()->setBoolForKey("isPlayingBlock", true);
		CCUserDefault::sharedUserDefault()->flush();
	}
}

void GUIGame::checkIsNewBest(int add)
{
	if (isNewBest)
		return;
	if (!isNewBest && this->score <= game->highscoreBlock && game->highscoreBlock > 0 && this->score + add > game->highscoreBlock) {
		// show Effect Best Score
		isNewBest = true;
		showEffectLabel("480_800/gameBlockPuzzel/iconNewBest.png");
		GameSound::playWin();
	}
}

CCSprite* GUIGame::getBlockEffect()
{
	CCSprite* label;
	int i;
	for (i = 0; i < arrayBlockEffect.size(); i++)
	{
		if (!arrayBlockEffect.at(i)->isVisible())
		{
			label = arrayBlockEffect.at(i);

		}
	}
	if (i == arrayBlockEffect.size())
	{
		label = CCSprite::create("480_800/gameBlockPuzzel/cell_1.png");
		arrayBlockEffect.push_back(label);
		this->addChild(label);
	}
	label->setZOrder(2);
	label->setVisible(true);
	label->setOpacity(255);
	return label;
}

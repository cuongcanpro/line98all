#include "GUIResult.h"
#include "../../Engine/GlobalVar.h"
#include "../GUIManager.h"
#include "../../Engine/Utility/LocalizedString.h"
#include "../Utility/GameSound.h"
#include "../Utility/GameUtility.h"
#include "../Utility/JNIUtils.h"

#define GUI_RESULT_BTN_OK 1

void GUIResult::initGUI()
{
	BaseGUI::initGUI();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();

	eff = DBCCFactory::getInstance()->buildArmatureNode("Chest");
	if (eff)
	{
		this->addChild(eff);
		//effIcon->setPosition(arrayNextEntity[i]->getPositionX(), bgBottom->getPositionY());
		eff->gotoAndPlay("1", -1, -1, -1);
		eff->setVisible(true);
		
		/*effIcon->setCompleteListener([](dragonBones::DBCCArmatureNode* armature) {
			armature->setVisible(false);
		});*/
	}

	bg = Scale9Sprite::create("480_800/bgDialogGame.png");
	addChild(bg);
	bg->setPosition(size.width * 0.5, size.height * 0.55);
	bg->setContentSize(Size(400, 400 * 0.95));
	
	eff->setPosition(size.width * 0.5, bg->getPositionY() + bg->getContentSize().height * 0.5);

	title = new GameImage("iconCongrat.png");
	bg->addChild(title);
	title->setPosition(bg->getContentSize().width * 0.5, bg->getContentSize().height * 0.9);

	float pad = 50;

	lbScore1 = Text::create("SCORE", "fonts/tahomabd.ttf", 18);
	bg->addChild(lbScore1);
	lbScore1->enableOutline(Color4B(115, 37, 31, 255), 1);
	lbScore1->setPosition(Vec2(bg->getContentSize().width * 0.5, title->getPositionY() - title->getHeight() * 0.5));

	bgScore = Scale9Sprite::create("480_800/bgScore1.png");
	bg->addChild(bgScore);
	bgScore->setContentSize(Size(150, 50));
	bgScore->setPosition(lbScore1->getPositionX(), lbScore1->getPositionY() - pad);

	lbScore = Text::create("0", "fonts/tahomabd.ttf", 25);
	lbScore->setTextHorizontalAlignment(TextHAlignment::CENTER);
	lbScore->setAnchorPoint(ccp(0.5f, 0.5f));
	bgScore->addChild(lbScore);
	lbScore->setPosition(Vec2(bgScore->getContentSize().width * 0.5, bgScore->getContentSize().height * 0.53));

	lbBestScore1 = Text::create("BEST", "fonts/tahomabd.ttf", 18);
	bg->addChild(lbBestScore1);
	lbBestScore1->enableOutline(Color4B(115, 37, 31, 255), 1);
	lbBestScore1->setPosition(Vec2(bg->getContentSize().width * 0.5, bgScore->getPositionY() - pad));

	bgBest = Scale9Sprite::create("480_800/bgBest.png");
	bg->addChild(bgBest);
	bgBest->setContentSize(Size(150, 50));
	bgBest->setPosition(bg->getContentSize().width * 0.5, lbBestScore1->getPositionY() - pad);

	lbBestScore = Text::create("0", "fonts/tahomabd.ttf", 25);
	lbBestScore->setTextHorizontalAlignment(TextHAlignment::CENTER);
	lbBestScore->setAnchorPoint(ccp(0.5f, 0.5f));
	bgBest->addChild(lbBestScore);
	lbBestScore->setPosition(Vec2(bgBest->getContentSize().width * 0.5, bgBest->getContentSize().height * 0.53));
	

	btnPlay = addButton(GUI_RESULT_BTN_OK, new GameImage("btnNewGameBig.png", false), bg);
	btnPlay->setPosition(bg->getContentSize().width * 0.5, bg->getContentSize().height * 0.15);
	btnPlay->addBehavior(new BubbleBehavior());
	
	iconBest = Sprite::create("480_800/iconNewBest.png");
	bg->addChild(iconBest);
	iconBest->setPosition(bg->getContentSize().width * 0.83, bgBest->getPositionY());

	effBest = DBCCFactory::getInstance()->buildArmatureNode("fire_work");
	if (effBest)
	{
		addChild(effBest);
		effBest->setPosition(Vec2(size.width * 0.5, bg->getPositionY() + bg->getContentSize().height * 0.6));
		effBest->setVisible(false);
		//effBest->gotoAndPlay("run", -1, -1, -1);
	}
}

void GUIResult::onButtonRelease(int buttonId, CCTouch* event)
{
    GameSound::playClick();
	switch(buttonId)
	{
	case GUI_RESULT_BTN_OK:
		bg->runAction(Sequence::create(
			EaseBackIn::create(ScaleTo::create(0.5, 0)),
			CCCallFunc::create(this, callfunc_selector(GUIResult::hideGUI)),
			NULL
		));
		
       // JNIUtils::showAdsFull();

		
		break;
	}
}

void GUIResult::hideGUI()
{
	setVisible(false);
	GUIManager::getInstance().removeFromListGui();
	if (GUIManager::getInstance().guiLine.isInitted() && GUIManager::getInstance().guiLine.isVisible())
		GUIManager::getInstance().guiLine.newGame();
	else if (GUIManager::getInstance().guiGame.isInitted() && GUIManager::getInstance().guiGame.isVisible())
		GUIManager::getInstance().guiGame.newGame();
	else if (GUIManager::getInstance().guiTwenty.isInitted() && GUIManager::getInstance().guiTwenty.isVisible())
		GUIManager::getInstance().guiTwenty.newGame();
	else if (GUIManager::getInstance().guiEgg.isInitted() && GUIManager::getInstance().guiEgg.isVisible())
		GUIManager::getInstance().guiEgg.newGame();
	else if (GUIManager::getInstance().guiBubble.isInitted() && GUIManager::getInstance().guiBubble.isVisible())
		GUIManager::getInstance().guiBubble.newGame();
	else if (GUIManager::getInstance().guiMerge.isInitted() && GUIManager::getInstance().guiMerge.isVisible())
		GUIManager::getInstance().guiMerge.newGame();
	else if (GUIManager::getInstance().guiPop.isInitted() && GUIManager::getInstance().guiPop.isVisible())
		GUIManager::getInstance().guiPop.newGame();
    else if (GUIManager::getInstance().guiPikachu.isInitted() && GUIManager::getInstance().guiPikachu.isVisible())
        GUIManager::getInstance().guiPikachu.makeNewLevel();
	
}

void GUIResult::showGUI(int score, int highscore, bool isTime)
{
	game->showAdsFull();
	BaseGUI::showGUI();
	setVisible(true);
	GUIManager::getInstance().addToListGui(this);
	/*schedule(schedule_selector(GUIResult::updateResult), 0.1);
	this->score = score;
	this->highscore = highscore;
	currentScore = 0;
	currentBest = 0;
	deltaScore = (score - currentScore) / 20.0f;
	deltaBest = (highscore - currentBest) / 20.0f;*/
	this->isTime = isTime;
	if (!this->isTime) {
		schedule(CC_SCHEDULE_SELECTOR(GUIResult::updateResult), 0.1);
		this->score = score;
		this->highscore = highscore;
		currentScore = 0;
		currentBest = 0;
		deltaScore = (score - currentScore) / 20.0f;
		deltaBest = (highscore - currentBest) / 20.0f;
	}
	else
	{
		string timeGame = GameUtility::convertToTime(score);
		lbScore->setString(timeGame);

		string timeBest = GameUtility::convertToTime(highscore);
		this->lbBestScore->setString(timeGame);
	}

	bg->setScale(1);
	//bg->runAction(EaseBackOut::create(ScaleTo::create(0.5, 1)));

	if (score == highscore) {
		title->setImage("iconCongrat.png");
		GameSound::playWin();
	}
	else {
		title->setImage("iconGameOver.png");
		GameSound::playLose();
	}
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();
	bg->setPositionY(size.height * 1.1);
	bg->runAction(EaseBackOut::create(MoveTo::create(0.5, Vec2(size.width * 0.5, size.height * 0.55))));
	bg->setScaleY(0.7);
	bg->runAction(EaseBounceOut::create(ScaleTo::create(0.5, 1.0, 1.0)));

	moveEffect(title, 1, 0.5);
	moveEffect(lbScore1, 1, 0.4);
	moveEffect(bgScore, 1, 0.3);
	moveEffect(lbBestScore1, 1, 0.2);
	moveEffect(bgBest, 1, 0.1);
	moveEffect(btnPlay->normalImage, 1, 0.0);
	if (isTime) {
		title->setImage("iconCongrat.png", false);
		title->setPositionY(bg->getContentSize().height * 0.91);
		GameSound::playWin();
		if (score <= highscore)
		{
			iconBest->setVisible(true);
			iconBest->setOpacity(0);
			iconBest->setScale(10);
			iconBest->runAction(
				Sequence::create(DelayTime::create(1.5), EaseExponentialOut::create(ScaleTo::create(0.5, 0.5)), NULL));
			iconBest->runAction(Sequence::create(DelayTime::create(1.5), FadeIn::create(0.5), NULL));
			eff->setVisible(true);
			effBest->setVisible(true);
			effBest->gotoAndPlay("run", -1, -1, -1);
		}
		else
		{
			iconBest->setVisible(false);
			eff->setVisible(false);
			effBest->setVisible(false);
		}
	}
	else {
		if (score == highscore) {
			iconBest->setVisible(true);
			iconBest->setOpacity(0);
			iconBest->setScale(10);
			iconBest->runAction(Sequence::create(
				DelayTime::create(1.5),
				EaseExponentialOut::create(ScaleTo::create(0.5, 0.5)),
				NULL
			));
			iconBest->runAction(Sequence::create(
				DelayTime::create(1.5),
				FadeIn::create(0.5),
				NULL
			));
			eff->setVisible(true);
			effBest->setVisible(true);
			effBest->gotoAndPlay("run", -1, -1, -1);
		}
		else {
			iconBest->setVisible(false);
			eff->setVisible(false);
			effBest->setVisible(false);
		}
	}
}

void GUIResult::moveEffect(Node* node, int rate, float delay)
{
	float save = node->getPositionY();
	node->setPositionY(save + 100 * rate);
	node->runAction(Sequence::create(
		DelayTime::create(delay),
		EaseBackOut::create(MoveBy::create(0.7, Vec2(0, -100 * rate))),
		NULL
	));
}

void GUIResult::updateResult(float dt)
{
	if (currentScore != score) {
		currentScore = currentScore + deltaScore;
		if (abs(currentScore - score) <= deltaScore) {
			currentScore = score;
		}
		lbScore->setText(GameUtility::toString(currentScore));
	}
	if (currentBest != highscore) {
		currentBest = currentBest + deltaBest;
		if (abs(currentBest - highscore) <= deltaBest) {
			currentBest = highscore;
			if (score == highscore) {

			}
		}
		lbBestScore->setText(GameUtility::toString(currentBest));
	}
}

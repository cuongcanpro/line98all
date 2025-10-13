#include "GUIPop.h"
#include "../../Engine/GlobalVar.h"
#include "../GUIManager.h"
#include "../../Engine/Utility/LocalizedString.h"
#include "../Utility/GameSound.h"
#include "../Utility/GameUtility.h"
#include "../Utility/JNIUtils.h"
#include "SimpleAudioEngine.h"
#include "../Utility/Toast.h"
using namespace CocosDenshion;

#define BTN_BACK_ID 1
#define BTN_SOUND_ID 2
#define BTN_PAUSE_ID 3
#define BTN_PLAY_ID 4
#define BTN_TOP_ID 5
#define BTN_OK_ID 6
#define BTN_MUSIC_ID 7
#define BTN_VIBRATE_ID 8
#define BTN_PAUSE_ID 9
#define BTN_RESUME_ID 10
#define BTN_BOMB 11

void okPlayPop() {
   
    if (game->isIOS())
        JNIUtils::openApp("https://apps.apple.com/app/id6473006848");
    else
        JNIUtils::openApp("com.bcsofts.popNumber");
}

void cancelPlayPop() {

}

void GUIPop::initGUI()
{
	BaseGUI::initGUI();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();

	DBCCFactory::getInstance()->loadDragonBonesData("effect/tile_light/skeleton.xml", "tile_light");
	DBCCFactory::getInstance()->loadTextureAtlas("effect/tile_light/texture.plist", "tile_light");

	DBCCFactory::getInstance()->loadDragonBonesData("effect/cast_skill_vua_le_hoi/skeleton.xml", "cast_skill_vua_le_hoi");
	DBCCFactory::getInstance()->loadTextureAtlas("effect/cast_skill_vua_le_hoi/texture.plist", "cast_skill_vua_le_hoi");

	DBCCFactory::getInstance()->loadDragonBonesData("effect/eff_button_daily_gift/skeleton.xml", "eff_button_daily_gift");
	DBCCFactory::getInstance()->loadTextureAtlas("effect/eff_button_daily_gift/texture.plist", "eff_button_daily_gift");

	GameImage* background = addImage("lobby_background.png");
	background->setWidth(size.width);
	background->setHeight(size.height);
	background->setPos(size.width * 0.5f, size.height * 0.5f);
	//Color3B color = ccc3(50, 50, 50);
	//background->setColor(color);

	btnBack = addButton(BTN_BACK_ID, "btnBack.png");
	if (size.width / size.height < 11.0 / 20.0)
		btnBack->setPosition(size.width - btnBack->getWidth() * 0.6f, size.height - btnBack->getHeight() * 1.3f);
	else
		btnBack->setPosition(size.width - btnBack->getWidth() * 0.6f, size.height - btnBack->getHeight() * 0.9f);
	//	btnBack->setPosition(size.width - btnBack->getWidth() * 0.6f, size.height - btnBack->getHeight() * 0.7f);

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

	btnBomb = addButton(BTN_BOMB, "btnBomb.png");
	btnBomb->setPosition(btnBomb->getWidth() * 0.7, btnBack->getPositionY());

	btnTop = addButton(BTN_TOP_ID, "btnTop.png");
	btnTop->setPosition(btnSound->getPositionX() - btnSound->getWidth() * 1.1f, btnBack->getPositionY());
	btnTop->setVisible(false);

	labelScore = this->addLabelBM("Number: 0");
	labelScore->setColor(ccc3(50, 50, 50));
	labelScore->setPositionX(size.width * 0.15f);
	labelScore->setPositionY(btnBack->getPositionY());
	labelScore->setAlignment(CCTextAlignment::LEFT);
	labelScore->setVisible(false);

	highscore = game->highscorePop;
	labelHighscore = this->addLabelBM("Best: " + GameUtility::toString(game->highscorePop));
	//labelHighscore->setColor(ccc3(50, 50, 50));
	labelHighscore->setPositionX(size.width * 0.5f);
	labelHighscore->setPositionY(labelScore->getPositionY());
	labelHighscore->setAlignment(CCTextAlignment::LEFT);
	labelHighscore->setVisible(false);

	bgScore = Scale9Sprite::create("bgScoreNormal.png");
	//bgScore->setColor(ccc3(25, 25, 25));
	addChild(bgScore);
	bgScore->setContentSize(Size(120, 45));
	bgScore->setPosition(btnBomb->getPositionX() + btnBomb->getWidth() * 0.5 + bgScore->getContentSize().width * 0.55, btnBomb->getPositionY());

	Text* lbScore = Text::create("SCORE", "fonts/tahomabd.ttf", 15);
	bgScore->addChild(lbScore);
	lbScore->enableOutline(Color4B(115, 37, 31, 255), 1);
	lbScore->setPosition(Vec2(bgScore->getContentSize().width * 0.5, bgScore->getContentSize().height * 1.0));

	bgBest = Scale9Sprite::create("bgScoreBest.png");
	//bgBest->setColor(ccc3(25, 25, 25));
	addChild(bgBest);
	bgBest->setContentSize(bgScore->getContentSize());
	bgBest->setPosition(bgScore->getPositionX() + bgScore->getContentSize().width * 1.05, bgScore->getPositionY());

	Text* lbBest = Text::create("BEST", "fonts/tahomabd.ttf", 15);
	bgBest->addChild(lbBest);
	lbBest->enableOutline(Color4B(115, 37, 31, 255), 1);
	lbBest->setPosition(Vec2(bgBest->getContentSize().width * 0.5, bgBest->getContentSize().height * 1.0));

	

	labelScoreSum = Text::create(GameUtility::standardizeNumber(score).c_str(), "fonts/tahomabd.ttf", 22);
	labelScoreSum->setTextHorizontalAlignment(TextHAlignment::CENTER);
	labelScoreSum->setAnchorPoint(ccp(0.5f, 0.5f));
	bgScore->addChild(labelScoreSum);
	labelScoreSum->setPosition(Vec2(bgScore->getContentSize().width * 0.5, bgScore->getContentSize().height * 0.46));

	labelHighscoreSum = Text::create("0", "fonts/tahomabd.ttf", 22);
	labelHighscoreSum->setTextHorizontalAlignment(TextHAlignment::CENTER);
	labelHighscoreSum->setAnchorPoint(ccp(0.5f, 0.5f));
	bgBest->addChild(labelHighscoreSum);
	labelHighscoreSum->setPosition(Vec2(bgBest->getContentSize().width * 0.5, bgBest->getContentSize().height * 0.46));
	labelHighscoreSum->setText(GameUtility::standardizeNumber(highscore).c_str());
	
	updateScoreSum();

	bgCenter = Sprite::create("480_800/bgWhite.png");
	bgCenter->setAnchorPoint(ccp(0.5, 0));
	addChild(bgCenter);
	bgCenter->setColor(ccColor3B(0, 0, 0));

	iconBomb = Sprite::create("480_800/iconBomb.png");
	float widthProgress = size.width * 0.96 - iconBomb->getContentSize().width * 1.2;
	bgProgress = addImage("progress_bgPop.png");
	//bgProgress->setColor(ccc3(100, 100, 100));
	bgProgress->setWidth(widthProgress);
	bgProgress->setHeight(btnBack->getHeight() * 0.75f);
	bgProgress->setPos(size.width * 0.02 + widthProgress * 0.5, btnBack->getPositionY() - btnBack->getHeight() * 1.2);

	progress = CCProgressTimer::create(CCSprite::create("480_800/progressPop.png"));
	progress->setType(kCCProgressTimerTypeBar);
	progress->setMidpoint(ccp(0, 0.5));
	progress->setBarChangeRate(ccp(1, 0));
	progress->setPercentage(50);
	progress->setPositionX(bgProgress->getWidth() * 0.495 - progress->getContentSize().width * 0.5);
	progress->setPositionY(bgProgress->getHeight() * 0.45 - progress->getContentSize().height * 0.5);
	bgProgress->addChild(progress);
	
	addChild(iconBomb);
	iconBomb->setPosition(bgProgress->getRealWidth() * 0.5 + bgProgress->getPositionX() + iconBomb->getContentSize().width * 0.6, bgProgress->getPositionY());

	iconBombEffect = Sprite::create("480_800/iconBomb.png");
	addChild(iconBombEffect, 5);
	iconBombEffect->setPosition(iconBomb->getPosition());

	lbBomb = Text::create(GameUtility::standardizeNumber(numBomb).c_str(), "fonts/tahomabd.ttf", 22);
	lbBomb->enableOutline(ccc4(105, 70, 9, 255), 2);
	lbBomb->setTextHorizontalAlignment(TextHAlignment::CENTER);
	lbBomb->setAnchorPoint(ccp(0.5f, 0.5f));
	//this->addChild(lbBomb, 2);
	btnBomb->normalImage->addChild(lbBomb);
	//lbBomb->setPosition(Vec2(btnBomb->getPositionX(), btnBomb->getPositionY() - 15));

	groupCenter = new BoardPop();
	groupCenter->setAnchorPoint(ccp(0.5, 0));
	widthCenter = size.width * 0.95f;
	float posY = bgProgress->getPositionY() - bgProgress->getRealHeight() - widthCenter;
	if (posY < size.height * 0.15) {
		widthCenter = bgProgress->getPositionY() - bgProgress->getRealHeight() - size.height * 0.15;
        posY = bgProgress->getPositionY() - bgProgress->getRealHeight() - widthCenter;
	}
	addChild(groupCenter);
	groupCenter->setClippingEnabled(true);

	imgNewBest = Sprite::create("480_800/iconNewBest.png");
	addChild(imgNewBest);
	imgNewBest->setLocalZOrder(3);
	imgNewBest->setVisible(false);

	groupNewNumber = new GroupNewNumberPop();
	addChild(groupNewNumber, 100);

	setKeypadEnabled(true);

	showEffect();
	newGame();
	
}

void GUIPop::onBackKey()
{
	if (GUIManager::getInstance().isCallBackPress == false && GUIManager::getInstance().getLastGui() == this)
	{
		if (score > 0) {
			groupCenter->saveGame();
		}
	//	game->endGame();
		GUIManager::getInstance().removeAllGui();
		GUIManager::getInstance().showGui(&GUIManager::getInstance().guiMinigames);
		GUIManager::getInstance().isCallBackPress = true;
	}
}

void GUIPop::onButtonRelease(int buttonId, CCTouch* event)
{
    GameSound::playClick();
	switch (buttonId)
	{
	case BTN_BACK_ID:
	{
		onBackKey();
	}
	break;
	case BTN_TOP_ID:
	{
		JNIUtils::submitScore(highscore, 0);
	}

	break;
	case BTN_SOUND_ID:
	{
		//groupNewNumber->showNewNumber(10, ccp(200, 200), 1);
		game->music = !game->music;
		if (game->music)
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
	case BTN_BOMB:
	{
		if (numBomb > 0) {
			useBomb();
		}
		else {
			Toast::makeToast(2.0, "You don't have any bomb");
		}
	}
	break;
	}
}

void GUIPop::hideGUI()
{
	
}

void GUIPop::showGUI()
{
	BaseGUI::showGUI();
	setVisible(true);
	GUIManager::getInstance().addToListGui(this);

	showEffect();
	if (game->highscorePop > 1200) {
		string s = CCLocalizedString("INSTALL_GAME");
		GUIManager::getInstance().guiDialog.showGUI(s.c_str(), &okPlayPop, false, &cancelPlayPop);
	}
}

void GUIPop::showEffect()
{
	bgCenter->setOpacity(0);
	float scale = bgCenter->getScaleX();
	bgCenter->runAction(
		CCSpawn::create(
			CCFadeIn::create(1.5),
		//	CCScaleTo::create(2.5, scale * 0.5, bgCenter->getScaleY()),
			NULL
		)
	);
	//bgCenter->setScaleX(bgCenter->getScaleX() * 5);
//	moveEffect(groupCenter, 0, -500, 0);

	moveEffectSineOut(bgScore, -500, 0, 0.2);
	moveEffectSineOut(bgBest, -500, 0, 0.1);
	moveEffectSineOut(btnBomb->normalImage, -500, 0, 0.3);

	moveEffect(btnSound->normalImage, 500, 0, 0.1);
	moveEffect(btnBack->normalImage, 500, 0, 0.2);

	moveEffect(bgProgress, 500, 0, 0.1);
	moveEffect(iconBomb, 500, 0, 0.2);
}

void GUIPop::moveEffect(Node* node, float dx, float dy, float delay)
{
	node->setPosition(node->getPositionX() + dx, node->getPositionY() + dy);
	node->runAction(Sequence::create(
		DelayTime::create(delay),
		EaseBackOut::create(MoveBy::create(0.7, Vec2(-dx, -dy))),
		NULL
	));
}

void GUIPop::moveEffectSineOut(Node* node, float dx, float dy, float delay)
{
	node->setPosition(node->getPositionX() + dx, node->getPositionY() + dy);
	node->runAction(Sequence::create(
		DelayTime::create(delay),
		EaseSineOut::create(MoveBy::create(0.7, Vec2(-dx, -dy))),
		NULL
	));
}

void GUIPop::update()
{
	if (currentScore != targetScore) {
		if ((targetScore - currentScore) * deltaScore < 0) {
			currentScore = targetScore;
		}
		else {
			currentScore = currentScore + deltaScore;
		}
		updateScoreSum();
	}
	groupCenter->update(game->deltaTime);

	if (groupCenter->state != POP_BOMB) {
		if (targetMana != manaPoint) {
			if ((targetMana - manaPoint) * deltaMana < 0) {
				manaPoint = targetMana;
				deltaMana = 0;
			}
			else {
				manaPoint = manaPoint + deltaMana;
			}
		}
		else {
			manaPoint = manaPoint - 0.02;
			targetMana = manaPoint;
		}

		if (manaPoint < 0)
			manaPoint = 0;
		float targetBonus = 150 * groupCenter->data->maxNum / 5.0f;
		float percent = manaPoint / targetBonus * 100;
		progress->setPercentage(percent);
		if (percent >= 100) {
			manaPoint = targetBonus - 1;
			addMana(-targetMana);
			numBomb = numBomb + 1;
			iconBombEffect->setVisible(true);
			iconBombEffect->setOpacity(255);
			iconBombEffect->setPosition(iconBomb->getPosition());
			iconBombEffect->runAction(
				Sequence::create(
					EaseBackOut::create(MoveBy::create(0.5, Vec2(0, 40))),
					EaseExponentialOut::create(MoveTo::create(1.0, btnBomb->getPosition())),
					FadeOut::create(0.5),
					Hide::create(),
					CCCallFunc::create(this, callfunc_selector(GUIPop::updateBomb)),
					NULL
				)
			);
			GameSound::playLevelUp();
		}
		groupCenter->update(game->deltaTime);
	}
}

void GUIPop::onTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	Vec2 convertPoint = groupCenter->convertToNodeSpace(pTouch->getLocation());
	groupCenter->doTouchEnd(convertPoint.x, convertPoint.y);
	BaseGUI::onTouchEnded(pTouch, pEvent);
}

bool GUIPop::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	Vec2 convertPoint = groupCenter->convertToNodeSpace(pTouch->getLocation());
	//initAds();
	return BaseGUI::onTouchBegan(pTouch, pEvent);
}

void GUIPop::onTouchMoved(CCTouch*touch, CCEvent* event)
{
	BaseGUI::onTouchMoved(touch, event);
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	Vec2 convertPoint = groupCenter->convertToNodeSpace(touch->getLocation());
}

void GUIPop::addScore(int _score)
{
	targetScore = targetScore + _score;
	deltaScore = (targetScore - currentScore) / 10.0f;
	addMana(_score);
	updateScoreSum();
	CCUserDefault::sharedUserDefault()->setIntegerForKey("saveScorePop", targetScore);
	if (targetScore > game->highscorePop) {
		game->highscorePop = targetScore;
		CCUserDefault::sharedUserDefault()->setIntegerForKey("highscorePop", game->highscorePop);
		showNewBest();
	}
	CCUserDefault::sharedUserDefault()->flush();
}

void GUIPop::addMana(int mana)
{
	targetMana = targetMana + mana;
	deltaMana = (targetMana - deltaMana) / 20.0f;
}

void GUIPop::updateScoreSum()
{
	int oldScore = score;
	score = (int)currentScore;
	if (oldScore != score) {
		labelScoreSum->setText(("" + GameUtility::standardizeNumber(score)).c_str());
		labelScoreSum->stopAllActions();
		labelScoreSum->setScale(1);
		labelScoreSum->runAction(
			CCSequence::create(
				CCScaleTo::create(0.05, 1.3),
				CCScaleTo::create(0.05, 1),
				NULL
			)
		);

		if (score > highscore) {
			highscore = score;
			labelHighscoreSum->setText(("" + GameUtility::standardizeNumber(score)).c_str());
		}
	}
}

void GUIPop::updateBomb()
{
	lbBomb->setString(GameUtility::toString(numBomb));
}

void GUIPop::useBomb()
{
	numBomb--;
	updateBomb();
	groupCenter->useBomb();
	iconBombEffect->setPosition(btnBomb->getPosition());
	iconBombEffect->setOpacity(255);
	iconBombEffect->runAction(
		Sequence::create(
			MoveBy::create(0.5, Vec2(0, 40)),
			DelayTime::create(0.5),
			FadeOut::create(0.5),
			NULL
		)
	);
}

void GUIPop::endGame()
{
	GUIManager::getInstance().guiResult.showGUI(targetScore, game->highscorePop);
	score = 0;
}

void GUIPop::newGame()
{
	score = 0;
	numBomb = 1;
	targetScore = 0;
	currentScore = 0;
	labelScoreSum->setText(("" + GameUtility::standardizeNumber(score)).c_str());
	int saveScore = CCUserDefault::sharedUserDefault()->getIntegerForKey("saveScorePop", 0);
	if (saveScore > 0) {
		targetScore = saveScore;
		currentScore = saveScore;
		numBomb = CCUserDefault::sharedUserDefault()->getIntegerForKey("numBomb", 1);
	}
	deltaScore = 0;
	groupNewNumber->setVisible(false);
	iconBombEffect->setVisible(false);
	manaPoint = 0;
	deltaMana = 0;
	targetMana = 0;
	highscore = game->highscorePop;
	if (game->highscorePop == 0 || game->highscorePop <= score) {
		isNewBest = true;
	}
	addScore(0);
	groupCenter->newGame();
	updatePosCenter();
	updateScoreSum();
	updateBomb();
}

void GUIPop::showNewBest()
{
	if (isNewBest)
		return;
	// show Effect Best Score
	isNewBest = true;
	showEffectLabel("480_800/gameBlockPuzzel/iconNewBest.png");
	GameSound::playWin();
}

void GUIPop::showEffectLabel(string s)
{
	/*layerColor->setVisible(false);
	layerColor->setOpacity(0);
	layerColor->runAction(
		CCSequence::create(
			CCFadeTo::create(0.5, 100),
			CCDelayTime::create(2.5),
			CCFadeOut::create(0.5),
			CCHide::create(),
			NULL
		)
	);*/


	CCSize size = CCDirector::sharedDirector()->getWinSize();
	Vec2 pos = ccp(size.width * 0.5, size.height * 0.6);

	DBCCArmatureNode* eff = DBCCFactory::getInstance()->buildArmatureNode("tile_light");
	if (eff) {
		this->addChild(eff);
		eff->setLocalZOrder(2);
		eff->setPosition(pos);
		eff->gotoAndPlay("run", 0.5, -1, 1);
		eff->setCompleteListener([](dragonBones::DBCCArmatureNode* armature) {
			armature->removeFromParent();
		});
	}

	DBCCArmatureNode* eff1 = DBCCFactory::getInstance()->buildArmatureNode("cast_skill_vua_le_hoi");
	if (eff1) {
		this->addChild(eff1);
		eff1->setLocalZOrder(2);
		eff1->setPosition(pos.x, pos.y + 50);
		eff1->gotoAndPlay("run", 0.5, -1, 1);
		eff1->setCompleteListener([](dragonBones::DBCCArmatureNode* armature) {
			armature->removeFromParent();
		});
	}
	imgNewBest->setVisible(true);
	imgNewBest->setPosition(pos);
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

void GUIPop::showNewNumber(int number, Vec2 pos, float scale)
{
	groupNewNumber->showNewNumber(number, pos, scale);
}

void GUIPop::initAds()
{
	if (game->isInitAds)
		return;
	game->isInitAds = true;
	string packageApp = JNIUtils::getPackageApp();
	//if (packageApp.compare("com.bcsofts.bubbleConnect") == 0) {
		// google test
		//JNIUtils::initAds("ca-app-pub-3940256099942544~3347511713", "ca-app-pub-3940256099942544/6300978111", "ca-app-pub-3940256099942544/1033173712", idAdsBanner, idAdsFull);
		// my ads
	
		
	
}

void GUIPop::updatePosCenter()
{
	groupCenter->updateBoardSize();
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();
	float scale = widthCenter / groupCenter->getContentSize().width;
	heightCenter = groupCenter->getContentSize().height * scale;
	float posY = bgProgress->getPositionY() - bgProgress->getRealHeight() - groupCenter->getContentSize().height * scale;
	if (posY < size.height * 0.11) {
		heightCenter = bgScore->getPositionY() - bgScore->getContentSize().height - size.height * 0.11;
		scale = heightCenter / groupCenter->getContentSize().height;
		widthCenter = groupCenter->getContentSize().width * scale;
		posY = size.height * 0.11;
	}
	float time = 0.3;
	groupCenter->stopAllActions();
	groupCenter->runAction(
		Spawn::create(
			ScaleTo::create(time, scale),
			MoveTo::create(time, ccp(size.width * 0.5, posY)),
			NULL
		)
	);
	float sX = (groupCenter->getContentSize().width  * scale + 10) / bgCenter->getContentSize().width;
	float sY = (groupCenter->getContentSize().height * scale + 10) / bgCenter->getContentSize().height;
	bgCenter->runAction(
		Spawn::create(
			ScaleTo::create(time, sX, sY),
			MoveTo::create(time, ccp(size.width * 0.5, posY - 5)),
			NULL
		)
	);
}

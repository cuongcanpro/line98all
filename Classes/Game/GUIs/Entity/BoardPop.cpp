#include "BoardPop.h"
#include <cmath>  
#include <string>
#include "../../Utility/GameUtility.h"
#include "Game/Logic/Logic.h"
#include "Game/Logic/PointGame.h"
#include "Engine/GUI/ParticleEffect.h"
#include "Engine/GlobalVar.h"
#include "Game/GUIManager.h"
#include "Game/Utility/GameSound.h"
#include "Game/Utility/JNIUtils.h"

BoardPop::BoardPop(void)
{
	// khoi tao mang cac khoi number
	for (int i = 0; i < BOARD_ROW; i++) {
		for (int j = 0; j < BOARD_COLUMN; j++) {
			arrayNumber[i][j] = new ObjectNumberPop();
			this->addChild(arrayNumber[i][j]);
			//	arrayNumber[i][j]->setNumber(i);
			//arrayNumber[i][j]->setVisible(false);
		}
	}
	sizeCell = arrayNumber[0][0]->getContentSize().width * 1;
	for (int i = 0; i < BOARD_ROW; i++) {
		for (int j = 0; j < BOARD_COLUMN; j++) {
			arrayNumber[i][j]->setPosition(sizeCell * (j + 0.5), sizeCell * (i + 0.5));
			arrayNumber[i][j]->setRootPosition();
		}
	}
	setCascadeColorEnabled(true);
	setCascadeOpacityEnabled(true);

	DBCCFactory::getInstance()->loadDragonBonesData("effect/no_top/skeleton.xml", "no_top");
	DBCCFactory::getInstance()->loadTextureAtlas("effect/no_top/texture.plist", "no_top");
	effBomb = DBCCFactory::getInstance()->buildArmatureNode("no_top");
	if (effBomb)
	{
		this->addChild(effBomb);
		effBomb->setVisible(false);
	}

	lbNotMove = Text::create("No Move, you need to use bomb to destroy block", "fonts/tahomabd.ttf", 20);
	lbNotMove->enableOutline(ccc4(50, 10, 0, 255), 2);
	addChild(lbNotMove, 10);

	data = new BoardDataPop();
}

BoardPop::~BoardPop(void)
{
}

void BoardPop::updateBoardSize()
{
	float width = sizeCell * data->currentSize;
	float height = sizeCell * data->currentSize;
	lbNotMove->setPosition(ccp(width * 0.5, 20));
	setContentSize(CCSize(width, height));
}

void BoardPop::newGame() {
	state = POP_NORMAL;
	lbNotMove->setVisible(false);
	effBomb->setVisible(false);
	data->newGame();
	for (int i = 0; i < BOARD_ROW; i++) {
		for (int j = 0; j < BOARD_COLUMN; j++) {
			arrayNumber[i][j]->setVisible(false);
		}
	}
	for (int i = 0; i < data->currentSize; i++) {
		for (int j = 0; j < data->currentSize; j++) {
		//	arrayNumber[i][j]->setVisible(false);
			arrayNumber[i][j]->setNumber(data->arrayBall[i][j]);
			arrayNumber[i][j]->setAvailable(false);
			arrayNumber[i][j]->resetPosition();
			arrayNumber[i][j]->showBomb(false);
		}
	}
	for (int i = 0; i < arrayLabel.size(); i++) {
		arrayLabel[i]->setVisible(false);
	}

	int saveScoreMerge = CCUserDefault::sharedUserDefault()->getIntegerForKey("saveScorePop", 0);
	//saveScoreMerge = 0;
	if (saveScoreMerge > 0) {
		// dang choi do
		data->loadGame();
		for (int i = 0; i < BOARD_ROW; i++) {
			for (int j = 0; j < BOARD_COLUMN; j++) {
				if (data->arrayBall[i][j] > 0) {
					arrayNumber[i][j]->setNumber(data->arrayBall[i][j]);
					arrayNumber[i][j]->effectNewGame();
				}
			}
		}
		callbackGenNew();
	}
}

void BoardPop::saveGame()
{
	string s = "";
	for (int i = 0; i < BOARD_ROW; i++)
		for (int j = 0; j < BOARD_COLUMN; j++)
		{
			int num = 0;
			if (arrayNumber[i][j]->getAvailable()) {
				num = arrayNumber[i][j]->getNumber();
			}
			else {
				num = 0;
			}
			if (i == 0 && j == 0)
			{
				s = s + GameUtility::toString(num);
			}
			else
			{
				s = s + "," + GameUtility::toString(num);
			}
		}

	CCUserDefault::sharedUserDefault()->setStringForKey("dataPop", s);
	CCUserDefault::sharedUserDefault()->setIntegerForKey("maxNum", data->maxNum);
	CCUserDefault::sharedUserDefault()->setIntegerForKey("numBomb", GUIManager::getInstance().guiPop.numBomb);
	CCUserDefault::sharedUserDefault()->flush();
}

bool BoardPop::checkInBoard(float posX, float posY)
{
	if (posX < 0 || posX > getContentSize().width || posY < 0 || posY > sizeCell * data->currentSize)
		return false;
	return true;
}

/**
 * Khi User tha tay khoi man hinh
 */
void BoardPop::doTouchEnd(float posX, float posY)
{
	if (checkInBoard(posX, posY) == false)
		return;
	int column = (posX / sizeCell);
	if (column >= data->currentSize)
		return;
	int row = (posY / sizeCell);
	if (row >= data->currentSize)
		return;

	// neu dang su dung bomb, dien Effect Bomb va gen number moi
	if (state == POP_BOMB) {
		data->arrayBall[row][column] = 0;
		state = POP_EFFECT;
		for (int i = 0; i < data->currentSize; i++) {
			for (int j = 0; j < data->currentSize; j++) {
				arrayNumber[i][j]->showBomb(false);
			}
		}
		effectBomb(arrayNumber[row][column]->getPosition());
		genNew();
		return;
	}

	// cap nhat diem so cua cac o so khac tinh tu diem cham
	countEat = 0;
	data->updatePoint(column, row);
	float maxTime = 0;
	for (int i = 0; i < data->currentSize; i++)
		for (int j = 0; j < data->currentSize; j++) {
			if ((i != row || j != column) && data->arrayWay[i][j]->point >= 0) {
				// voi nhung diem co cung so voi diem cham, gia tri cua no gan lai = 0 dong thoi di chuyen ve phia diem cham
				data->arrayBall[i][j] = 0;
				countEat++;
				data->setWay(i, j);
				cocos2d::Vector<cocos2d::FiniteTimeAction*> actions;
				int size = data->arrayPoint.size();
				float time = 0.1;
				for (int k = 1; k < size; k++) {
					actions.pushBack(MoveTo::create(time, convertToPosition(data->arrayPoint.at(k)->y, data->arrayPoint.at(k)->x)));
				}
				if (size * time > maxTime) {
					maxTime = size * time;
				}
				actions.pushBack(MoveTo::create(time, convertToPosition(row, column)));
				auto action = Sequence::create(actions);
				arrayNumber[i][j]->runAction(action);
				arrayNumber[i][j]->setLocalZOrder(1);
			}
		}
	if (countEat > 0) {
		// kiem tra cac khoi an sau khi roi xuong
		ObjectNumberPop* obj = arrayNumber[row][column];
		playParticle(obj->getPositionX(), obj->getPositionY(), obj->number);
		runAction(
			CCSequence::create(
				CCDelayTime::create(maxTime),
				CCCallFunc::create(this, callfunc_selector(BoardPop::callbackAfterMove)),
				NULL
			)
		);
		GameSound::playEat(countEat);
	}
}

void BoardPop::callbackAfterMove() {
	int row = data->currentPoint->y;
	int column = data->currentPoint->x;
	int score = countEat * data->arrayBall[row][column];
	effectScore(score, convertToPosition(row, column));
	GUIManager::getInstance().guiPop.addScore(score);

	// tang gia tri cua ho hien tai, neu o hien tai dat moc level moi thi Show Effect
	if (data->updateValueCurrent()) {
		GUIManager::getInstance().guiPop.showNewNumber(data->maxNum, arrayNumber[row][column]->getPosition(), 1);
	}
	genNew();
}

void BoardPop::genNew() {
	data->renewBall();
	for (int i = 0; i < data->currentSize; i++)
		for (int j = 0; j < data->currentSize; j++) {
			arrayNumber[i][j]->setNumber(data->arrayBall[i][j]);
			arrayNumber[i][j]->setLocalZOrder(0);
		}
	for (int i = 0; i < data->arrayMoveEnd.size(); i++) {
		PointGame* pBegin = data->arrayMoveBegin[i];
		PointGame* pEnd = data->arrayMoveEnd[i];
		ObjectNumberPop* number = arrayNumber[pEnd->y][pEnd->x];
		number->setPosition(convertToPosition(pBegin->y, pBegin->x));
		number->moveDown(0.2);
	}
	//GameSound::playDrop(data->arrayMoveBegin.size());
	runAction(
		CCSequence::create(
			CCDelayTime::create(0.2),
			CCCallFunc::create(this, callfunc_selector(BoardPop::callbackGenNew)),
			NULL
		)
	);
	
}

void BoardPop::callbackGenNew() {
	state = POP_NORMAL;
	if (data->checkNoMove()) {
		GameSound::playFail();
	//	JNIUtils::vibrate();
		// Neu khong the di chuyen them nua, dua vao trang thai su dung Bomb hoac End Game
		if (GUIManager::getInstance().guiPop.numBomb > 0) {
			lbNotMove->setVisible(true);
			lbNotMove->setScale(5);
			lbNotMove->runAction(
				CCSequence::create(
					EaseBounceOut::create(ScaleTo::create(0.6, 1)),
					DelayTime::create(1.0),
					CCCallFunc::create(this, callfunc_selector(BoardPop::callbackNoMove)),
					NULL
				)
			);
			saveGame();
		}
		else {
			for (int i = 0; i < data->currentSize; i++) {
				for (int j = 0; j < data->currentSize; j++) {
					arrayNumber[i][j]->effectEndGame();
				}
			}
			state = POP_END;
			CCUserDefault::sharedUserDefault()->setIntegerForKey("saveScorePop", 0);
			CCUserDefault::sharedUserDefault()->flush();
			JNIUtils::sendEvent(("number_" + GameUtility::toString(data->maxNum)).c_str(), "1");
			runAction(CCSequence::create(
				CCDelayTime::create(1.5),
				CCCallFunc::create(this, callfunc_selector(BoardPop::callbackEffectEndGame)),
				NULL
			));
		}
	}
	else {
		saveGame();
	}
}

void BoardPop::callbackNoMove()
{
	if (state != POP_BOMB)
		GUIManager::getInstance().guiPop.useBomb();
}

void BoardPop::useBomb()
{
	state = POP_BOMB;
	for (int i = 0; i < data->currentSize; i++) {
		for (int j = 0; j < data->currentSize; j++) {
			arrayNumber[i][j]->stopAllActions();
			arrayNumber[i][j]->resetPosition();
			arrayNumber[i][j]->showBomb(true);
		}
	}
}

void BoardPop::effectBomb(Vec2 pos)
{
	float dx = 10;
	float dy = 10;
	runAction(
		Sequence::create(
			MoveBy::create(0.1, Vec2(dx  * 0.5 - GameUtility::getRandom() * dx, dy * 0.5 - GameUtility::getRandom() * dy)),
			MoveBy::create(0.1, Vec2(dx  * 0.5 - GameUtility::getRandom() * dx, dy * 0.5 - GameUtility::getRandom() * dy)),
			MoveBy::create(0.1, Vec2(dx  * 0.5 - GameUtility::getRandom() * dx, dy * 0.5 - GameUtility::getRandom() * dy)),
			MoveTo::create(0.1, getPosition()),
			NULL
		)
	);
	lbNotMove->setVisible(false);
	effBomb->setPosition(pos);
	effBomb->setLocalZOrder(1);
	effBomb->setVisible(true);
	effBomb->gotoAndPlay("run", -1, -1, 1);
	GameSound::playBomb();
}

void BoardPop::callbackEffectEndGame()
{
	for (int i = 0; i < data->currentSize; i++)
		for (int j = 0; j < data->currentSize; j++) {
			arrayNumber[i][j]->setVisible(false);
			arrayNumber[i][j]->stopAllActions();
			effectImage(arrayNumber[i][j]);
		}
	runAction(CCSequence::create(
		CCDelayTime::create(1.0),
		CCCallFunc::create(this, callfunc_selector(BoardPop::callbackEffectEndGame1)),
		NULL
	));
	GameSound::playFirework();
}


void BoardPop::callbackEffectEndGame1()
{
	GUIManager::getInstance().guiPop.endGame();
}

void BoardPop::effectImage(ObjectNumberPop* ball)
{
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
	image->setTexture("480_800/brickWhite.png");
	image->setVisible(true);
	image->setOpacity(255);
	image->setColor(GameUtility::getColorMerge(ball->getNumber()));
	//image->setScale(ball->rootScaleX * 1.1);
	//image->setTexture("480_800/bgNumber.png");
	image->initCoin(ImageEffect::TYPE_FLOW, 0, ball->getPositionX(), ball->getPositionY());
}

void BoardPop::playParticle(float posX, float posY, int id)
{
	Vec2 globalPos = convertToWorldSpace(ccp(posX, posY));
	globalPos.y = globalPos.y - sizeCell * 0.4;
	Layer *layer = layerMgr->getLayerByIndex(LAYER_EFFECT_GAME);

	ParticleEffect *effect = new ParticleEffect();
	effect->create("particles/FlyUp.plist", layer);
	//ParticleEffect *effect =  effectMgr->addParticleEffect("particles/twenty.plist", ccp (posX, posY), layer);
	effect->particle->setPosition(globalPos.x, globalPos.y);
	effect->particle->setBlendAdditive(true);
	ccColor4F color1 = ccc4FFromccc3B(GameUtility::getColorMerge(id));
	/*color1.r = 1;
	color1.g = 1;
	color1.b = 1;*/
	color1.a = 1;
	ccColor4F color2 = ccc4FFromccc3B(GameUtility::getColorMerge(id));
	effect->particle->setStartColor(color1);
	effect->particle->setStartColorVar(ccColor4F(0, 0, 0, 0));
	/*color2.r = 1;
	color2.g = 1;
	color2.b = 1;*/
	color2.a = 0;
	effect->particle->setEndColor(color2);
	effect->particle->setCascadeOpacityEnabled(true);
	effect->particle->setEndColorVar(ccColor4F(0, 0, 0, 0));
	effect->particle->setAutoRemoveOnFinish(true);
	//effect->particle->setTexture(TextureCache::sharedTextureCache()->addImage(("480_800/cell_" + GameUtility::toString(id % 10) + ".png").c_str()));

	ParticleEffect *effectSlow = new ParticleEffect();
	effectSlow->create("particles/FlyUpSlow.plist", layer);
	//ParticleEffect *effect =  effectMgr->addParticleEffect("particles/twenty.plist", ccp (posX, posY), layer);
	effectSlow->particle->setPosition(globalPos.x, globalPos.y);
	effectSlow->particle->setBlendAdditive(true);
	effectSlow->particle->setStartColor(color1);
	effectSlow->particle->setStartColorVar(ccColor4F(0, 0, 0, 0));
	effectSlow->particle->setEndColor(color2);
	effectSlow->particle->setCascadeOpacityEnabled(true);
	effectSlow->particle->setEndColorVar(ccColor4F(0, 0, 0, 0));
	effectSlow->particle->setAutoRemoveOnFinish(true);
}


Sprite* BoardPop::getSmoke()
{
	Sprite* image = NULL;
	for (int i = 0; i < arraySmoke.size(); i++) {
		if (!arraySmoke.at(i)->isVisible()) {
			image = arraySmoke.at(i);
			break;
		}
	}
	if (image == NULL) {
		image = Sprite::create("480_800/smoke.png");
		addChild(image);
		arraySmoke.push_back(image);
	}
	image->setVisible(true);
	image->setOpacity(255);
	return  image;
}

void BoardPop::update(float delta)
{
	for (int i = 0; i < arrayImageEffect.size(); i++) {
		if (arrayImageEffect.at(i)->isVisible()) {
			arrayImageEffect.at(i)->updateCoin(game->deltaTime);
		}
	}
}

void BoardPop::effectScore(int score, Vec2 pos)
{
	Text* label = NULL;
	for (int i = 0; i < arrayLabel.size(); i++) {
		if (!arrayLabel.at(i)->isVisible()) {
			label = arrayLabel.at(i);
			break;
		}
	}
	if (label == NULL) {
		label = Text::create("SCORE", "fonts/tahomabd.ttf", 35);
		addChild(label);
		//label->enableOutline(Color4B(115, 37, 31, 255), 1);
		arrayLabel.push_back(label);
	}
	label->setVisible(true);
	label->setOpacity(0);
	label->setLocalZOrder(2);
	label->setPosition(pos);
	label->setString(GameUtility::toString(score));
	label->runAction(
		CCSequence::create(
			CCSpawn::create(
				CCFadeTo::create(0.3, 180),
				CCEaseBackOut::create(CCMoveBy::create(0.5, ccp(0, 70))),
				NULL
			),
			CCDelayTime::create(0.5),
			CCFadeOut::create(0.5),
			NULL
		)
	);
}

cocos2d::Vec2 BoardPop::convertToPosition(int row, int column)
{
	return Vec2((column + 0.5) * sizeCell, (row + 0.5) * sizeCell);
}


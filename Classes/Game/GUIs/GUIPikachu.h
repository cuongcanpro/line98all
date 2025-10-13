#pragma once
#ifndef GUIPikachu_h__
#define GUIPikachu_h__

#include "../../Engine/GUI/BaseGUI.h"
#include "../GameClient.h"
#include "Game/Logic/PointGame.h"
#include "Entity/BlockItem.h"
#include "../LogicPikachu/BoardDataPikachu.h"
#include "spine/spine-cocos2dx.h"
#include "ui/UIText.h"
#include "dragonbones/DragonBones.h"
#include "dragonbones/renderer/DBCCFactory.h"
using namespace cocos2d::ui;
using namespace std;
using namespace cocos2d::extension;
using namespace spine;
using namespace dragonBones;
enum GameStatePika{
	PIKA_PLAY, PIKA_END, PIKA_PAUSE, PIKA_TOUCH, PIKA_EFFECT
};

enum GameMode {
	NORMAL_MODE, EXTEND_MODE, CHALLENGE_MODE
};

enum GameTypePika
{
	NORMAL_PIKA, DOWN_PIKA, UP_PIKA, LEFT_PIKA, RIGHT_PIKA, CENTER_PIKA
};

class GUIPikachu : public BaseGUI
{
public:
	GUIPikachu(void);
	~GUIPikachu(void);
public:
	void initGUI();
private:
	

public:
	GameStatePika state;
	void callBackSplash();
	void onButtonRelease(int buttonID, CCTouch* touch);
	void onBackKey(void);
	
	void act();
	void makeNewLevel();
	void resetGame();
	void newGame();
	void showParticle(BlockItem* number);
	void showParticleFire(float posX, float posY, int id);
	void finishEat();
	void newData();
	void doCenter(int row);
	GameStatePika gameState;
	int score, countGame;
	GameImage* bgProgress;
	CCProgressTimer* progress;
	Text* labelScore, *labelHighscore;
	Text *labelLife, *labelLevel;
	BaseButton* btnBack, *btnSound, *btnPause, *btnHelp, *btnSearch;
	BlockItem* arrayNumber[BOARD_ROW_PIKA][BOARD_COLUMN_PIKA];
	int level;
	GameMode gameMode;
	float rootProgress;
	PointGame* currentTouch;
	int idCurrentNumber;
	vector<BlockItem*> currentNumber;
	int timeGame;
	float currentTime;
	int currentRow;

	float moveY;

	//ProgressTimer progress;
	int maxNumber;
	GameTypePika gameType;
	float timeAds;

	BoardDataPikachu* boardData;
	GameImage* arrayLine[4];
	PointGame* touchPoint1;
	PointGame* touchPoint2;
	vector<BlockItem*> arrayEffectN;
	vector<BlockItem*> getListTouch(BlockItem* number);
	void startMode();
	void startTime(float time, float currentTime = 0);
	void setSelect(bool isSelect);
	float pad;
	int countLife;
	void endGame();
	void callbackEndGame();
	GameImage* bgDark;
	BaseButton* btnPlay;
	bool onTouchBegan( CCTouch *pTouch, CCEvent *pEvent );
	PointGame* convertPoint(float x, float y);
	PointGame* checkNotMove(PointGame* center, int id);
	void updateScore();
	void onPause();
	void callbackEffect();
	int getFirstVisible();
	float saveTime;
	float widthProgress;
	bool checkCanMove(PointGame* newpoint, PointGame* oldPoint);
	void showGui(GameMode mode);

	vector<spine::SkeletonAnimation*> arrayFire;
	vector<int>indexFire;
	float targetScore;
	float deltaScore;
	void checkNewLevel();
	void effectStar(Vec2 posStart, Vec2 posEnd, float time);
	void callbackEffectStar(CCNode* sender);
	GameImage* background;
	Scale9Sprite *bgScore;
	bool arrayPlayTime[10];
	vector<DBCCArmatureNode*> arrayEffectBomb;
	DBCCArmatureNode* getEffectBomb();
	void saveData();
	void genLevel();
	void genRowColumnTime();
	void genData();
	void startGameAfterGen();
	void resumeGame();

	float deltaBonus;
	float targetBonus;
	GameImage* bgProgressBonus;
	CCProgressTimer* progressBonus;
	float timeBonus;
	GameImage* iconGift, *iconBomb;
	GameImage* imgEffectBomb;
	void callbackBomb();
	DBCCArmatureNode* effectBomb;
	Text* labelEffectStar;
	GameImage* iconHeart;
	Node* groupBonus;
};
#endif // GUIPikachu_h__


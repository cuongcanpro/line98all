#pragma once
#include "../../Engine/GUI/BaseGUI.h"
#include "../GameClient.h"

#include "Entity/Arrow.h"
#include "Entity/Ball.h"
#include "Entity/RowBall.h"
#include "Entity/Bird.h"
#include "Entity/BonusEffect.h"
#include "Entity/BonusEffect.h"
#include "Entity/GroupScoreEgg.h"
#include "dragonbones/renderer/DBCCArmature.h"
#include "dragonbones/renderer/DBCCFactory.h"
#include "Engine/GUI/ImageEffect.h"
#include "Effekseer/Effekseer.h"
using namespace std;
using namespace dragonBones;
using namespace efk;

#define SPLASH_LAYER 0
#define LEVEL_LAYER 1
#define RACE_LAYER 2
#define TETRIS_LAYER 3
#define GUN_LAYER 4
#define FULL_LAYER 5
#define EMPTY_LAYER 6
#define SNAKE_LAYER 7
#define HIT_LAYER 8
#define JUMP_LAYER 9
#define SAME_LAYER 10

enum GameStateEgg
{
	PLAY_EGG, END_GAME_EGG, WAIT_PLAY_EGG, PAUSE_EGG
};
enum GameType
{
	ENDLESS, STOMP, TIME, FAKE
};

class GUIEgg : public BaseGUI
{
public:
	GUIEgg(void);
	~GUIEgg(void);
public:
	void initGUI();
private:
	

public:
	void onBackKey(void);
	
	Arrow *arrow;

	void update();
	void onButtonRelease(int buttonID, CCTouch* touch);
	void callBackSplash();
	
	GameStateEgg gameState;

	void newGame();
	

	bool isUpdate;

	vector<RowBall*> arrayRow;
	vector<Ball*> arrayEatBall;
	vector<Ball*> arrayEffectBall;
	vector<GroupScoreEgg*> arrayGroupScore;
	Ball* getBall(int idRow, int idColumn);
	
	void resetCheckConnect();
	Ball* genBall;

	float countTime;
	int level;
	Ball* moveBall;
	Ball* nextBall;
	GameImage* cannon1;
	GameImage* bgRow;
	float speedX, speedY, speed;
	GameImage* rope;
	int oldRow, oldColumn;
	CCNode* groupBall;

	float countTimeVisible;
	int countVisible;
	bool delay;

	GameStateEgg state;
	Bird* ani;
	bool increaseSpeed;

	CCProgressTimer* progress;
	GameImage* bgProgress;

	float countTimeVibrate;
	int countGenBonus;

	float oldX, oldY;
	bool nextBonus;
	int currentMul;

	LabelBM* labelScore;
	LabelBM* labelHighscore;
	LabelBM* labelRow;

	int score;
	BonusEffect* bonusEffect;

	bool isMoving;
	int numRowScore;
	int countRowScore;
	GameType gameType;
	GameImage* bar;
	float distanceY;
	float countDistance;
	bool isNewhigh;
	GameImage* rightWall;
	GameImage* upWall;
	GameImage* leftWall;

	BaseButton* btnSound;
	BaseButton* btnPause;
	BaseButton* btnBack;
	GameImage* fakeBall;

	void act(float deltaTime);

	bool onTouchBegan( CCTouch *pTouch, CCEvent *pEvent );
	void onTouchMoved(CCTouch*touch, CCEvent* event);
	void onTouchEnded( CCTouch *pTouch, CCEvent *pEvent );
	void moveArrow(int screenX, int screenY);
	float getTag(int screenX, int screenY);
	void delayReturn();
	void updateArrayBall();
	PointGame* getPoint(float x, float y);
	 void getNearBall(float x, float y);
	 bool checkNearBall(float x, float y, int row, int column,
		 int dRow, int dColumn);
	 void addMoveBall(int row, int column);
	 double getDistance(Ball* ball, float x, float y);
	 bool checkEndGame();
	 void endGame();
	 void makeGenBall();
	 void showParticle(float px, float py, int id);
	 void makeBonus();
	 void updateScore();
	 void initGame();
	 void updateTime();
	 string convertTime(float countTime);
	 void onPause();
	 GroupScoreEgg* getGroupScore();

	 void callbackRemove(CCNode* pSender);
	 void callbackNextBall();
	 void callbackProgress();
	 void callbackEndGame();
	 void makeEffectScore();
	 void showGui(GameType gameType);
	 void showGui(int level);

	 DBCCArmatureNode* effectShootBall = NULL;
	 
	 DBCCArmatureNode* effectLight = NULL;
	 DBCCArmatureNode* effectShoot = NULL;
	 DBCCArmatureNode* effectWin = NULL;
    efk::EffectManager* manager;
    efk::EffectEmitter* effectBreakBall;
	 void initDragonbone();

	 void dropBall(int id, float posX, float posY);
	 Ball* getEffectBall();

	 vector <ImageEffect*> arrayImageEffect;
	 void effectImage(int id);
	 void addNewBall();
};


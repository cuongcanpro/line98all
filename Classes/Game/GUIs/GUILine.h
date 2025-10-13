#pragma once
#include "../../Engine/GUI/BaseGUI.h"
#include "../GameClient.h"

#include "Entity/BallAnimationNew.h"
#include "../Logic/BoardData.h"
#include "Entity/ScoreGroup.h"
#include "dragonbones/DragonBones.h"
#include "dragonbones/renderer/DBCCFactory.h"
#include "ui/UIText.h"
using namespace std;
using namespace dragonBones;
using namespace cocos2d::ui;

class GUILine : public BaseGUI
{
public:
	GUILine(void);
	~GUILine(void);
public:
	void initGUI();
	void onBackKey(void);
	DBCCArmatureNode *effIcon;

	BaseButton* btnBack, *btnSound, *btnUndo, *btnBall, *btnTrophy;
	BaseButton* btnHelp;
	
	void update(float dt);
	void onButtonRelease(int buttonID, CCTouch* touch);
	void callBackSplash();
	GameImage *ballMove;
	GameImage *bg;
	GameImage *arrayNext[3];
	BallAnimationNew* arrayBall[9][9];
	ScoreGroup *scoreGroup;
	ScoreGroup *highscoreGroup;
	Text *labelScore;
	LabelBM *labelUndo;
	int score;
	
	int oldScore;
	BoardData* board;
	int arrayOldBall[9][9]; // dung de cap nhat trang thai cac qua bong sau khi
	// random hoac di chuyen
	int saveBall[9][9]; // luu lai mang gia tri truoc khi di chuyen
	vector<PointGame*> arrayChange; // mang ghi cac bong thay doi
	int valueSaveBall;
	int positionSaveBall;

	int currentRow;
	int currentColumn;
	int nextRow, nextColumn;
	float SPEED;
	bool canUndo;
	bool genNext;
	int typeBall;
	int saveValue2;
	GameImage* effect;
	vector <GameImage*> arrayEffectBall;

	float startX, startY, pad, sizeCell;
	GameState gameState;
	BaseButton* btnSave;

	GameImage* getEffectBall();
	void newGame();
	void updateScore(int score);
	void updateNextBall();
	void updateViewBall();
	void doMoveBall();
	void checkGenNextBall();
	void makeBiggerBall();
	void genBall(int i, int j);
	void checkEatPoint();
	void updateHighScore();
	void undo();
	void onFinish();
	void showParticle(float posX, float posY, int id, float time);
	bool isUpdate;
	void act();
    void showGui();
    void showGuiWithMode(int typeMode);
	void showGuiWithData(int data[81], int score);
    void newTimer();
    void callbackTimer();
    int typeMode;
	GameImage* progress;
	GameImage* bgProgress;
	bool onTouchBegan( CCTouch *pTouch, CCEvent *pEvent );
	void autoBiggerBall();
	string getResourceBall();
	void savePreference();
	void checkAfterMove();
	void checkAfterMove2();
	void checkEndGame();
	void callbackEffectEndGame();
	void callbackEffectEndGame1();
	int convertIdBall(int id);

	extension::ControlSlider* slider;
	extension::ControlSlider* sliderBright;
	BaseButton* btnResize;
	BaseButton* btnNewGame;
	GameImage* iconHand;
	void showHand(CCPoint pos);
	void doTutorial();
	void waitNextStep();
	void showToast1(const char* content);
	void showToast2(const char* content);
	void showFinishTutorial();
	Sprite* imgNewBest;
	bool isNewBest;
	void checkIsNewBest(int add);
	void showEffectLabel(string s);
	void loadAdsFull();
	void callbackLoadAdsFull();
	cocos2d::LayerColor* layerColor;
	BaseButton* btnSkip;
	Text* lbKnowRule;
	GameImage* arrayMoveBall[4];
	MotionStreak* _streak;
	int numUndo;
};


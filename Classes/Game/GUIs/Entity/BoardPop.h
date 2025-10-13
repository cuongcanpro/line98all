#ifndef _BoardPop_h__
#define _BoardPop_h__
#include <cocos2d.h>
#include "Engine/GUI/GameImage.h"
#include "Engine/GUI/LabelBM.h"
#include "ui/UIText.h"
#include "ui/UILayout.h"
#include "ObjectNumberPop.h"
#include "Game/Data/GlobalData.h"
#include "Game/Logic/PointGame.h"
#include <vector>
#include "Engine/GUI/ImageEffect.h"
#include "Game/Logic/BoardDataPop.h"
using namespace std;
using namespace cocos2d;
using namespace cocos2d::ui;
#define RATE_SIZE 1.05
#define MOVE_DOWN_TIME 0.13
#define DELAY_CHECK_DOWN_TIME 0.16
#define MOVE_EAT_TIME 0.13
#define DELAY_CHECK_EAT_TIME 0.16
#define MOVE_NUMBER_SPEED -1.1

enum PopState {
	POP_NORMAL, POP_BOMB, POP_EFFECT, POP_END
};
class BoardPop : public Layout
{
public:
	BoardPop(void);
	~BoardPop(void);
	BoardDataPop* data;
	PopState state;
	ObjectNumberPop* arrayNumber[BOARD_ROW][BOARD_COLUMN];
	float sizeCell;
	vector<PointGame> arrayChange;
	vector <Text*> arrayLabel;
	int countEat;
	DBCCArmatureNode* effBomb;
	vector <ImageEffect*> arrayImageEffect;
	Text* lbNotMove;

	void updateBoardSize();
	void newGame();
	void saveGame();

	void doTouchEnd(float posX, float posY);
	void callbackEffectEndGame();
	void callbackEffectEndGame1();
	void effectImage(ObjectNumberPop* ball);
	bool checkInBoard(float posX, float posY);

	void playParticle(float posX, float posY, int id);
	void update(float delta);
	void effectScore(int score, Vec2 pos);
	Vec2 convertToPosition(int row, int column);
	void callbackAfterMove();
	void genNew();
	void callbackGenNew();
	void callbackNoMove();
	void useBomb();
	void effectBomb(Vec2 pos);

	vector <Sprite*> arraySmoke;
	Sprite* getSmoke();
};
#endif

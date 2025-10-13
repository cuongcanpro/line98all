#ifndef GUIMerge_H
#define GUIMerge_H

#include "../../Engine/GUI/BaseGUI.h"
#include "ui/UIText.h"
#include "dragonbones/DragonBones.h"
#include "dragonbones/renderer/DBCCFactory.h"
#include "Entity/GroupCenter.h"
#include "Entity/GroupNewNumber.h"
using namespace cocos2d::ui;
using namespace dragonBones;
class GUIMerge : public BaseGUI
{
private:
	GroupCenter* groupCenter;
	
public:
	LabelBM* labelScore;
	LabelBM* labelHighscore;
	Text* labelScoreSum, *labelHighscoreSum;
	LabelBM* tutorialLabel;
	LabelBM* labelAddScore;
	BaseButton* btnBack, *btnSound, *btnPause, *btnPlay, *btnTop, *btnVibrate, *btnDownload;
	GameImage* border;
	int score, highscore;
	GroupNewNumber* groupNewNumber;
	float widthCenter, heightCenter;
	Scale9Sprite* bgScore, *bgBest;
	Sprite* bgCenter;

	void initGUI();
	void onBackKey();
	void onButtonRelease(int buttonId, CCTouch* event);
	void hideGUI();
	void showGUI();
	void showEffect();
	void moveEffect(Node* node, float dx, float dy, float delay = 0);
	void update();

	void onTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	bool onTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void onTouchMoved(CCTouch*touch, CCEvent* event);

	void addScore(int _score);
	void updateScoreSum();
	void endGame();
	void newGame();
	void showNewNumber(int number, Vec2 pos, float scale);
	void resumeGame();
};
#endif
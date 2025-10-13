#ifndef GUIPop_H
#define GUIPop_H

#include "../../Engine/GUI/BaseGUI.h"
#include "ui/UIText.h"
#include "dragonbones/DragonBones.h"
#include "dragonbones/renderer/DBCCFactory.h"
#include "Entity/GroupCenter.h"
#include "Entity/GroupNewNumberPop.h"
#include "Entity/BoardPop.h"
using namespace cocos2d::ui;
using namespace dragonBones;
class GUIPop : public BaseGUI
{
private:
	BoardPop* groupCenter;
	
public:
	LabelBM* labelScore;
	LabelBM* labelHighscore;
	Text* labelScoreSum, *labelHighscoreSum;
	LabelBM* tutorialLabel;
	LabelBM* labelAddScore;
	BaseButton* btnBack, *btnSound, *btnPause, *btnPlay, *btnTop, *btnMusic, *btnVibrate, *btnResume, *btnBomb;
	GroupNewNumberPop* groupNewNumber;
	int score, highscore;
	float widthCenter, heightCenter;
	Scale9Sprite* bgScore, *bgBest;
	Sprite* bgCenter;
	float deltaScore;
	float targetScore;
	float currentScore;
	float scaleResume;
	float manaPoint;
	float deltaMana;
	float targetMana;
	int numBomb;
	Sprite* iconBomb;
	Sprite* iconBombEffect;
	Text* lbBomb;
	
	GameImage* bgProgress;
	CCProgressTimer* progress;

	void initGUI();
	void onBackKey();
	void onButtonRelease(int buttonId, CCTouch* event);
	void hideGUI();
	void showGUI();
	void showEffect();
	void moveEffect(Node* node, float dx, float dy, float delay = 0);
	void moveEffectSineOut(Node* node, float dx, float dy, float delay = 0);
	void update();

	void onTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	bool onTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void onTouchMoved(CCTouch*touch, CCEvent* event);

	void addScore(int _score);
	void addMana(int mana);
	void updateScoreSum();
	void updateBomb();
	void useBomb();
	void endGame();
	void newGame();
	void showNewNumber(int number, Vec2 pos, float scale);
	void initAds();
	void updatePosCenter();

	Sprite* imgNewBest;
	bool isNewBest;
	void showNewBest();
	void showEffectLabel(string s);
};
#endif
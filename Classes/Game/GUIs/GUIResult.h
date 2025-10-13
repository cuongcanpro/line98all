#ifndef GUIResult_H
#define GUIResult_H

#include "../../Engine/GUI/BaseGUI.h"
#include "ui/UIText.h"
#include "dragonbones/DragonBones.h"
#include "dragonbones/renderer/DBCCFactory.h"
using namespace cocos2d::ui;
using namespace dragonBones;
class GUIResult : public BaseGUI
{
private:
	Scale9Sprite* bg;
	Text* lbScore, *lbScore1;
	Text* lbBestScore, *lbBestScore1;
	Scale9Sprite *bgBest;
	Scale9Sprite *bgScore;
	BaseButton* btnPlay;
	GameImage* title;
	Sprite* iconBest;
	DBCCArmatureNode* eff;
	DBCCArmatureNode* effBest;
	int score;
	float currentScore;
	int highscore;
	float currentBest;
	float deltaScore;
	float deltaBest;
	bool isTime;
public:
	void initGUI();
	void onButtonRelease(int buttonId, CCTouch* event);
	void hideGUI();
	void showGUI(int score, int highscore, bool isTime = false);
	void moveEffect(Node* node, int rate, float delay = 0);
	void updateResult(float dt);
};
#endif
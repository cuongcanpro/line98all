#pragma once
#ifndef Bubble_h__
#define Bubble_h__
#include "../../Engine/GUI/GameImage.h"
#include "string"
using namespace std;
enum BubbleState {
	JUMP_BUBBLE, NORMAL_BUBBLE, DISAPPEAR_BUBBLE, SMALL_BUBBLE, BIGGER_BUBBLE, AUTO_SCORE_BUBBLE
};
class Bubble : public CCNode
{
public:
	Bubble(void);
	~Bubble(void);

	Bubble(const char *nameImg, bool frame = false);
	GameImage* bg;
	LabelBM* label;
	int id;
	string nameImage;
	void update();
	void setState(BubbleState _state);
	void setImage(const char* nameImg);

	float countTime;
	float frameTime;
	int currentFrame;

	BubbleState state;
	float rootX, rootY;
	float rootScaleX, rootScaleY;
	bool isAct;
	void setNumber(int number);
	void setPos(float x, float y);
	void setWidth(float width);
	void setHeight(float height);
	float getRealHeight();
	float getRealWidth();
	int nextScore;
	int currentScore;
	float deltaScore;
	void updateNumber();
};
#endif // Bubble_h__


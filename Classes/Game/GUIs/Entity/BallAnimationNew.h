#pragma once
#ifndef BallAnimationNew_h__
#define BallAnimationNew_h__
#include "Engine/GUI/GameImage.h"
#include "BallAnimation.h"
#include "string"
using namespace std;

class BallAnimationNew : public GameImage
{
public:
	BallAnimationNew(void);
	~BallAnimationNew(void);

	BallAnimationNew(const char *nameImg, bool frame = false);
	string nameImage;
	void update();
	void setState(BallState _state);
	void setImage(const char* nameImg);
	void setIdBall(int idBall);
	int idBall;

	float countTime;
	float frameTime;
	int currentFrame;

	BallState state;
	float rootX, rootY;
	float rootScaleX, rootScaleY;
	bool isAct;
	void setPos(float x, float y);
	void setNumber(int _id);
	void animationNewGame();
	void effectEndGame(float delay);
	void doBreak();
	void effectVibrate();
	void doVibrate();
	int numVibrate;
};
#endif // BallAnimationNew_h__


#pragma once
#ifndef MiniBoard_h__
#define MiniBoard_h__
#include "Engine/GUI/GameImage.h"
#include "BallAnimation.h"
#include "string"
using namespace std;

class MiniBoard : public GameImage
{
public:
	MiniBoard(void);
	~MiniBoard(void);

	MiniBoard(const char *nameImg, bool frame = false);
	int data[9][9];
	GameImage* arrayBall[9][9];
	void loadArrayBall(int data[9][9]);
	void loadArrayBall(int data[81]);
	void updateBall(int row, int column, int id);
	void udpateListBall(vector <int> pos, vector <int> id);
	void resetData();
	float sizeCell;
};
#endif // MiniBoard_h__


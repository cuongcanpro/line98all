#pragma once
#include "Way.h"
#include <vector>
#include "PointGame.h"
using namespace std;

#define BIG_RED  2
#define BIG_PINK  1
#define BIG_SEA_BLUE  3
#define BIG_SKY_BLUE  4
#define BIG_GREEN  5
#define BIG_VIOLET  6
#define BIG_YELLOW  7

#define SMALL_RED  9
#define SMALL_PINK  8
#define SMALL_SEA_BLUE  10
#define SMALL_SKY_BLUE  11
#define SMALL_GREEN  12
#define SMALL_VIOLET  13
#define SMALL_YELLOW  14

#define BOARD_ROW 10
#define BOARD_COLUMN 10
#define LIMIT_SIZE_POP 9
class BoardDataPop
{
public:
	BoardDataPop(void);
	~BoardDataPop(void);

	vector <int> arrayNewBall;
	vector <int> arrayNewBallGen;
	vector <PointGame*> arrayNewPos;
	int arrayBall[BOARD_ROW][BOARD_COLUMN];
	int arrayMap[BOARD_ROW][BOARD_COLUMN];
	Way* arrayWay[BOARD_ROW][BOARD_COLUMN];
	vector<int> arrayEmpty;
	vector<PointGame*> arrayPoint;
	vector<PointGame*> arrayMoveEnd;
	vector<PointGame*> arrayMoveBegin;

	PointGame* currentPoint;
	int maxNum;
	int currentSize;

	void reset();
	void newGame();
	void loadGame();
	void loadCurrentSize();
	void updatePoint(int currentX, int currentY);
	void calculatePoint(int x, int y);
	void setWay(int targetY, int targetX);
	bool updateValueCurrent();
	vector<PointGame*> getListBall(int row, int column);
	bool checkExist(PointGame* value, vector<PointGame*> array2) ;
	bool checkNoMove();
	bool checkEndGame();
	bool checkNewBall();
	int getNumBall();
	void renewBall();
	int genBall();
};


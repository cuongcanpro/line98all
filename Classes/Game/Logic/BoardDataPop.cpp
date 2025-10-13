#include "BoardDataPop.h"
#include "Engine/GlobalVar.h"
#include "../Utility/GameUtility.h"


BoardDataPop::BoardDataPop(void)
{
	for (int i = 0; i < BOARD_ROW; i++)
		for (int j = 0; j < BOARD_COLUMN; j++) {
			arrayWay[i][j] = new Way();
		}
		currentPoint = new PointGame();
		currentSize = 5;
		maxNum = 3;
}


BoardDataPop::~BoardDataPop(void)
{
}

void BoardDataPop::reset() {
	arrayEmpty.clear();
	for (int i = 0; i < BOARD_ROW; i++)
		for (int j = 0; j < BOARD_COLUMN; j++) {
			arrayBall[i][j] = 0;
			arrayEmpty.push_back(i * BOARD_COLUMN + j);
		}

}

void BoardDataPop:: newGame() {
	maxNum = 4;
	currentSize = 5;
	for (int i = 0; i < BOARD_ROW; i++)
		for (int j = 0; j < BOARD_COLUMN; j++) {
			arrayBall[i][j] = genBall();
			//arrayBall[i][j] = i * BOARD_COLUMN + j;
			//arrayBall[i][j] = 1;
		}
	int color = 4;
	/*arrayBall[0][2] = color;
	arrayBall[1][1] = color;
	arrayBall[1][3] = color;
	arrayBall[2][0] = color;
	arrayBall[2][4] = color;
	arrayBall[3][1] = color;
	arrayBall[3][3] = color;
	arrayBall[4][2] = color;*/
}

void BoardDataPop::loadGame() {
	string s = CCUserDefault::sharedUserDefault()->getStringForKey("dataPop", "");
	char * pch = new char[s.size() + 1];
	std::copy(s.begin(), s.end(), pch);
	pch[s.size()] = '\0'; // don't forget the terminating 0
	int dataSave[BOARD_COLUMN * BOARD_ROW];
	char *num;
	num = strtok(pch, ",");
	dataSave[0] = atoi(num);
	for (int i = 1; i < BOARD_COLUMN * BOARD_ROW; i++)
	{
		num = strtok(NULL, ",");
		dataSave[i] = atoi(num);
	}
	for (int i = 0; i < BOARD_COLUMN * BOARD_ROW; i++) {
		int row = i / BOARD_COLUMN;
		int column = i % BOARD_COLUMN;
		arrayBall[row][column] = 0;
		if (dataSave[i] > 0) {
			arrayBall[row][column] = dataSave[i];
		}
	}
	maxNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("maxNum", 3);
	loadCurrentSize();
}

void BoardDataPop::loadCurrentSize()
{
	currentSize = 5;
	if (maxNum > LIMIT_SIZE_POP) {
		currentSize = (maxNum - LIMIT_SIZE_POP - 1) / 2 + 1 + currentSize;
	}
    if (currentSize > BOARD_ROW)
        currentSize = BOARD_ROW;
}

void BoardDataPop::updatePoint(int currentX, int currentY) {
	int i, j;
	for (i = 0; i < currentSize; i++) {
		for (j = 0; j < currentSize; j++) {
			arrayWay[i][j]->reset();
			if (arrayBall[currentY][currentX] == arrayBall[i][j]) {
				arrayMap[i][j] = 0;
			}
			else {
				arrayMap[i][j] = 1;
			}
		}
	}

	arrayWay[currentY][currentX]->point = 0;
	currentPoint->x = currentX;
	currentPoint->y = currentY;
	calculatePoint(currentX, currentY);
}

void BoardDataPop:: calculatePoint(int x, int y) {

	bool check[4];
	for(int i = 0; i < 4; i++)
		check[i] = false;

	if(x < 0 || x >= currentSize)
		return;
	if(y < 0 || y >= currentSize)
		return;

	if (x + 1 < currentSize) {
		if (arrayWay[y][x + 1]->point == -1 || arrayWay[y][x + 1]->point - 1 > arrayWay[y][x]->point) {
			if (arrayMap[y][x + 1] <= 0) {
				arrayWay[y][x + 1]->point = arrayWay[y][x]->point + 1;
				arrayWay[y][x + 1]->previousPoint->x = x;
				arrayWay[y][x + 1]->previousPoint->y = y;
				check[0] = true;
			}
		}

	}

	if (x - 1 >= 0) {
		if (arrayWay[y][x - 1]->point == -1 || arrayWay[y][x - 1]->point - 1 > arrayWay[y][x]->point) {
			if (arrayMap[y][x - 1] <= 0) {
				arrayWay[y][x - 1]->point = arrayWay[y][x]->point + 1;
				arrayWay[y][x - 1]->previousPoint->x = x;
				arrayWay[y][x - 1]->previousPoint->y = y;

				check[1] = true;
			}
		}

	}

	if (y + 1 < currentSize) {
		if (arrayWay[y + 1][x]->point == -1 || arrayWay[y + 1][x]->point - 1 > arrayWay[y][x]->point) {
			if (arrayMap[y + 1][x] <= 0) {

				arrayWay[y + 1][x]->point = arrayWay[y][x]->point + 1;
				arrayWay[y + 1][x]->previousPoint->x = x;
				arrayWay[y + 1][x]->previousPoint->y = y;

				check[2] = true;

			}
		}

	}

	if (y - 1 >= 0) {
		if (arrayWay[y - 1][x]->point == -1 || arrayWay[y - 1][x]->point - 1 > arrayWay[y][x]->point) {
			if (arrayMap[y - 1][x] <= 0) {
				arrayWay[y - 1][x]->point = arrayWay[y][x]->point + 1;
				arrayWay[y - 1][x]->previousPoint->x = x;
				arrayWay[y - 1][x]->previousPoint->y = y;

				// calculatePoint(x, y - 1);
				check[3] = true;
			}
		}
	}

	if (check[0]) {
		calculatePoint(x + 1, y);
	}

	if (check[1]) {
		calculatePoint(x - 1, y);
	}

	if (check[2]) {
		calculatePoint(x, y + 1);
	}

	if (check[3]) {
		calculatePoint(x, y - 1);
	}
}

void BoardDataPop::setWay(int targetY, int targetX) {
	int ty = targetY;
	int tx = targetX;
	arrayPoint.clear();
	// arrayPoint.push_back(new Point(targetX, targetY));

	while (arrayWay[targetY][targetX]->point > 0) {
		arrayPoint.push_back(new PointGame(targetX, targetY));
		int oldTargetX = targetX;
		targetX = arrayWay[targetY][targetX]->previousPoint->x;
		targetY = arrayWay[targetY][oldTargetX]->previousPoint->y;
	}
}

bool BoardDataPop::updateValueCurrent() {
	arrayBall[currentPoint->y][currentPoint->x] = arrayBall[currentPoint->y][currentPoint->x] + 1;
	if (arrayBall[currentPoint->y][currentPoint->x] > maxNum) {
		maxNum = arrayBall[currentPoint->y][currentPoint->x];
		if (maxNum > LIMIT_SIZE_POP) {
			loadCurrentSize();
			return true;
		}
	}
	return false;
}

vector<PointGame*> BoardDataPop::getListBall(int row, int column) {

	vector<PointGame*> result1 ;

	return result1;
}

bool BoardDataPop::checkExist(PointGame *value, vector<PointGame*> array2) {
	for (int i = 0; i < array2.size(); i++) {
		if (value->x == array2.at(i)->x && value->y == array2.at(i)->y) {
			return true;
		}
	}

	return false;
}

bool BoardDataPop::checkNoMove()
{
	for (int i = 0; i < currentSize; i++)
		for (int j = 0; j < currentSize; j++) {
			int id = arrayBall[i][j];
			if (i + 1 < currentSize && id == arrayBall[i + 1][j] || j + 1 < currentSize && id == arrayBall[i][j + 1])
				return false;
		}
	return true;
}

bool BoardDataPop::checkEndGame() {
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++) {
			int id = arrayBall[i][j];
			if (i + 1 < currentSize && id == arrayBall[i + 1][j] || j + 1 < currentSize && id == arrayBall[i][j + 1])
				return false;
		}
	return true;
}

bool BoardDataPop::checkNewBall()
{
	
	return false;
}

int BoardDataPop::getNumBall()
{
	int count = 0;
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++) {
			if (arrayBall[i][j] > 0) {
				count++;
			}
		}
	return count;
}

void BoardDataPop::renewBall()
{
	arrayMoveBegin.clear();
	arrayMoveEnd.clear();
	for (int i = 0; i < currentSize; i++) {
		int count = 0;
		for (int j = 0; j < currentSize; j++) {
			if (arrayBall[j][i] <= 0) {
				int k;
				for (k = j + 1; k < currentSize; k++) {
					if (arrayBall[k][i] > 0) {
						arrayBall[j][i] = arrayBall[k][i];
						arrayBall[k][i] = 0;
						arrayMoveBegin.push_back(new PointGame(i, k));
						break;
					}
				}
				if (k == currentSize) {
					arrayBall[j][i] = genBall();
					arrayMoveBegin.push_back(new PointGame(i, currentSize + count));
					count++;
				}
				arrayMoveEnd.push_back(new PointGame(i, j));
			}
		}
	}
}

int BoardDataPop::genBall()
{
	int maxGen;
	if (maxNum >= 8)
		maxGen = maxNum - 3;
	else if (maxNum == 7 || maxNum == 6)
		maxGen = 5;
	else if (maxNum == 5)
		maxGen = 4;
	else
		maxGen = maxNum;
	//maxGen = maxGen > 2 ? maxGen : 3;
	return floor(GameUtility::getRandom() * maxGen) + 1;
}

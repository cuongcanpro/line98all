#include "MiniBoard.h"
#include "Game/GUIManager.h"
#include "Game/Utility/GameUtility.h"


MiniBoard::MiniBoard(void):GameImage()
{
}

MiniBoard::MiniBoard( const char *nameImg, bool frame ): GameImage(nameImg, frame)
{
	float startX = -this->getRealWidth() * 0.495f;
	float startY = -this->getRealHeight() * 0.495f;
	sizeCell = this->getRealWidth() * 0.99f * (1 / 9.0f);
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++) {
			arrayBall[i][j] = new GameImage("lineBall_0_0.png", false);
			this->addChild(arrayBall[i][j]);
			arrayBall[i][j]->setWidth(sizeCell * 0.7f);
			arrayBall[i][j]->setHeight(sizeCell * 0.7f);
			arrayBall[i][j]->setPos(sizeCell * (j + 0.5f) + startX, startY + sizeCell * (i + 0.5f));
		}
}


MiniBoard::~MiniBoard(void)
{
}


void MiniBoard::loadArrayBall(int data[81]) {
	int newData[9][9];
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++) {
			int index = i * 9 + j;
			newData[i][j] = data[index];
		}
	loadArrayBall(newData);
}

void MiniBoard::loadArrayBall(int data[9][9]) {
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++) {
			this->updateBall(i, j, data[i][j]);
		}
}

void MiniBoard::updateBall(int row, int column, int id)
{
	this->data[row][column] = id;
	if (data[row][column] <= 0) {
		arrayBall[row][column]->setVisible(false);
	}
	else {
		arrayBall[row][column]->setVisible(true);

		arrayBall[row][column]->setImage(("lineBall_0_" + GameUtility::toString((data[row][column] - 1) % 7) + ".png").c_str(), false);
		if (data[row][column] > 7) {
			arrayBall[row][column]->setWidth(sizeCell * 0.3);
			arrayBall[row][column]->setHeight(sizeCell * 0.3);
		}
		else {
			arrayBall[row][column]->setWidth(sizeCell * 0.8);
			arrayBall[row][column]->setHeight(sizeCell * 0.8);
		}
	}
}

void MiniBoard::resetData()
{
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++) {
			arrayBall[i][j]->setVisible(false);
		}
}

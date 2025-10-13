#ifndef GAME_CONST_H
#define GAME_CONST_H

class GameConst
{
public:
	const static int MAX_TARGET = 20;
	const static int MAX_ROW = 10;
	const static int MAX_COL = 9;
	const static int MAX_CHESSES = 16;
	const static int MAX_PLAYER = 2;
	const static int MAX_TURN_ATTACK_GENERAL = 2;
	const static int GAME_MODE_OFFLINE = 1;
	const static int GAME_MODE_ONLINE = 2;

	const static int ORIENTATION_LANDSCAPE = 2;
	const static int ORIENTATION_PORTRAIT = 1;

	const static int MIN_TURN_TO_ASK = 30;

	const static int FINISH_STATE_WIN = 1;
	const static int FINISH_STATE_LOSE = 2;
	const static int FINISH_STATE_DRAW = 3;

	const static int ALIGN_LEFT = 1;
	const static int ALIGN_CENTER = 0;
	const static int ALIGN_RIGHT = 2;

	const static int CHANNEL_BEGINNER = 0;
	const static int CHANNEL_MASTER = 1;
	const static int CHANNEL_GRAND_MASTER = 2;
};
#endif
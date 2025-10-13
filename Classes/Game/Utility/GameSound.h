#pragma once
#ifndef GameSound_h__
#define GameSound_h__

class GameSound
{
public:
	GameSound(void);
	~GameSound(void);

	
	static void loadSound();
	static void playSound(const char *sound);
	static void playClick();

	static void playBomb();

	static void playChooseBall();

	static void playFail();

	static void playLose();

	static void playMove();

	static void playScore1();

	static void playScore2();
	static void playScore3();

	static void playScore4();
	static void playScore5();
	static void playScore6();
	static void playWin();
	static void playTime();
	static void playLevelUp();
	static void playStart();
	static void playCountDown();
	static void playOtherScore();
	static void playerUserJoin();
	static void playerUserOut();
	static void playThunder();

	static void playBreakEgg();
	static void playEggLands();
	static void playMama();
	static void playWhirley();
	static void playWhirleyHit();
	static void playWarn();

	static void playUpNumber();
	static void playNewNumber();
	static void playEat();
	static void playHit();
	static void playDrop(int id);
	static void playEat(int index);
	static void playFirework();

	static void playBombGuess();
	static void playBombUnGuess();
	static void playOpenCell();

	static void playCheck();



	static void playMyTurn();

	static void playStartGame();
	static void playMessage();
	static void playEatChess();

	static void playEatPika();
	static void playMoveDown();
	static void playGameOver();
	static void playEatFull();
	static void playScoreExtra();
	static void playRotate();

	// sudoku
	static void playCorrect();
	static void playErase();
	static void playInvalid();
	static void playMark();
	static void playMistake();

	// 2048
	static void playMerge2048();
	static void playMove2048();
	static void playSpawn2048();
	static void playNewNumber2048();
	static void playWin2048();
};
#endif // GameSound_h__


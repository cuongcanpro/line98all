#include "GameSound.h"
#include "audio/include/SimpleAudioEngine.h"
#include "SoundResources.h"
#include "Engine/GlobalVar.h"
#include "GameUtility.h"
using namespace CocosDenshion;
GameSound::GameSound(void)
{
}


GameSound::~GameSound(void)
{
}


void GameSound::playSound( const char *sound )
{
	if(game->music)
	{
		SimpleAudioEngine::getInstance()->playEffect(sound);
	}
	
}

void GameSound::loadSound()
{

  //  game->music = CCUserDefault::sharedUserDefault()->getBoolForKey("sound", true);
	SimpleAudioEngine::getInstance()->preloadEffect(SOUND_CLICK);
	SimpleAudioEngine::getInstance()->preloadEffect(SOUND_CHOOSE_BALL);
	SimpleAudioEngine::getInstance()->preloadEffect(SOUND_FAIL);
	SimpleAudioEngine::getInstance()->preloadEffect(SOUND_LOSE);
	SimpleAudioEngine::getInstance()->preloadEffect(SOUND_MOVE);
	SimpleAudioEngine::getInstance()->preloadEffect(SOUND_WIN);
	SimpleAudioEngine::getInstance()->preloadEffect(SOUND_SCORE1);
	SimpleAudioEngine::getInstance()->preloadEffect(SOUND_SCORE2);
	SimpleAudioEngine::getInstance()->preloadEffect(SOUND_SCORE3);
	SimpleAudioEngine::getInstance()->preloadEffect(SOUND_SCORE4);
	SimpleAudioEngine::getInstance()->preloadEffect(SOUND_SCORE5);
	SimpleAudioEngine::getInstance()->preloadEffect(SOUND_SCORE6);
	SimpleAudioEngine::getInstance()->preloadEffect(SOUND_COUNT_DOWN);
	SimpleAudioEngine::getInstance()->preloadEffect(SOUND_BOMB);
	SimpleAudioEngine::getInstance()->preloadEffect(SOUND_START);
	SimpleAudioEngine::getInstance()->preloadEffect(SOUND_OTHER_SCORE);
	SimpleAudioEngine::getInstance()->preloadEffect(SOUND_PLAYER_JOIN);
	SimpleAudioEngine::getInstance()->preloadEffect(SOUND_PLAYER_OUT);
	SimpleAudioEngine::getInstance()->preloadEffect(SOUND_THUNDER);
	SimpleAudioEngine::getInstance()->preloadEffect(SOUND_EGG_BREAK);
	SimpleAudioEngine::getInstance()->preloadEffect(SOUND_EGG_LAND);
}

void GameSound::playClick()
{
	playSound(SOUND_CLICK);
}

void GameSound::playBomb()
{
	playSound(SOUND_BOMB);
}

void GameSound::playChooseBall()
{
	playSound(SOUND_CHOOSE_BALL);
}

void GameSound::playFail()
{
	playSound(SOUND_FAIL);
}

void GameSound::playLose()
{
	playSound(SOUND_LOSE);
}

void GameSound::playMove()
{
	playSound(SOUND_MOVE);
}

void GameSound::playScore1()
{
	playSound(SOUND_SCORE1);
}

void GameSound::playScore2()
{
	playSound(SOUND_SCORE2);
}
void GameSound::playScore3()
{
	playSound(SOUND_SCORE3);
}

void GameSound::playScore4()
{
	playSound(SOUND_SCORE4);
}
void GameSound::playScore5()
{
	playSound(SOUND_SCORE5);
}
void GameSound::playScore6()
{
	playSound(SOUND_SCORE6);
}
void GameSound::playWin()
{
	playSound(SOUND_WIN);
}
void GameSound::playTime()
{
	playSound(SOUND_TIME);
}
void GameSound::playLevelUp()
{
	playSound(SOUND_LEVEL_UP);
}

void GameSound::playStart()
{
	playSound(SOUND_START);
}

void GameSound::playCountDown()
{
	playSound(SOUND_COUNT_DOWN);
}

void GameSound::playOtherScore()
{
	playSound(SOUND_OTHER_SCORE);
}

void GameSound::playerUserJoin()
{
	playSound(SOUND_PLAYER_JOIN);
}

void GameSound::playerUserOut()
{
	playSound(SOUND_PLAYER_OUT);
}

void GameSound::playThunder()
{
	playSound(SOUND_THUNDER);
}


void GameSound::playBreakEgg()
{
	playSound(SOUND_EGG_BREAK);
}


void GameSound::playEggLands()
{
	playSound(SOUND_EGG_LAND);
}


void GameSound::playWarn()
{
	playSound(SOUND_WARN);
}

void GameSound::playMama()
{
	playSound(SOUND_MAMA);
}

void GameSound::playWhirley()
{
	playSound(SOUND_WHIRLEY_SIREN);
}

void GameSound::playWhirleyHit()
{
	playSound(SOUND_WHIRLEY_HIT);
}

void GameSound::playUpNumber()
{
	playSound(UP_NUMBER);
}

void GameSound::playNewNumber()
{
	playSound(NEW_NUMBER);
}

void GameSound::playHit()
{
	playSound(SOUND_HIT);
}

void GameSound::playEat()
{
	playSound(SOUND_EAT);
}

void GameSound::playDrop(int index)
{
	if (index >= 6)
		index = 6;
	string s = "sounds/mobile/drop" + GameUtility::toString(index) + ".mp3";
	playSound(s.c_str());
}

void GameSound::playFirework()
{
	playSound(SOUND_FIREWORK);
}

void GameSound::playEat(int index)
{
	if (index >= 7)
		index = 7;
	string s = "sounds/mobile/seed_3_0" + GameUtility::toString(index) + ".mp3";
	playSound(s.c_str());
}

void GameSound::playBombGuess()
{
	playSound(SOUND_BOMB_GUESS);
}

void GameSound::playBombUnGuess()
{
	playSound(SOUND_BOMB_UN_GUESS);
}

void GameSound::playOpenCell()
{
	playSound(SOUND_OPEN_CELL);
}

void GameSound::playCheck()
{
   playSound("sounds/GeneralChecked.mp3");
}



void GameSound::playMyTurn()
{
	playSound("sounds/myTurn.mp3");
}

void GameSound::playStartGame()
{
    playSound(SOUND_START);
}

void GameSound::playMessage()
{
	playSound("sounds/message.mp3");
}

void GameSound::playEatChess()
{
	playSound("sounds/eatChess.mp3");
}

void GameSound::playEatPika()
{
	playSound("sounds/mobile/selectBall.mp3");
}

void GameSound::playMoveDown()
{
	playSound("sounds/mobile/moveDown.mp3");
}

void GameSound::playGameOver()
{
}

void GameSound::playEatFull()
{
	playSound("sounds/mobile/eatRow.mp3");
}

void GameSound::playScoreExtra()
{
	playSound("sounds/mobile/scoreExtra.mp3");
}

void GameSound::playRotate()
{
	playSound("sounds/mobile/rotate.mp3");
}

void GameSound::playCorrect()
{
	playSound("sounds/sudoku/correct.mp3");
}

void GameSound::playErase()
{
	playSound("sounds/sudoku/erase.mp3");
}

void GameSound::playInvalid()
{
	playSound("sounds/sudoku/invalid.mp3");
}

void GameSound::playMark()
{
	playSound("sounds/sudoku/mark.mp3");
}

void GameSound::playMistake()
{
	playSound("sounds/sudoku/mistake.mp3");
}

void GameSound::playMove2048()
{
	playSound("sounds/2048/move.mp3");
}

void GameSound::playMerge2048()
{
	int rand = CCRANDOM_0_1() * 2.999 + 1;
	playSound(("sounds/2048/merger_" + to_string(rand) + ".mp3").c_str());
}

void GameSound::playSpawn2048()
{
	int rand = CCRANDOM_0_1() * 2.999 + 1;
	playSound(("sounds/2048/swoosh_" + to_string(rand) + ".mp3").c_str());
}

void GameSound::playNewNumber2048()
{
	playSound("sounds/2048/newNumber.mp3");
}

void GameSound::playWin2048()
{
	playSound("sounds/2048/2048win.mp3");
}

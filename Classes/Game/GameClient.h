
#ifndef GameClient1_h__
#define GameClient1_h__

#include "cocos2d.h"
#include <vector>
#include "Game/Logic/LevelData.h"
#include "Game/Logic/TutorialData.h"
#include "Data/PlayerInfo.h"
#include "LogicPikachu/BoardDataPikachu.h"
using namespace std;

#define NUM_WIDTH 10
#define NUM_HEIGHT 20
#define DELTA_TIME 0.035f


#define TOP_NORMAL 0 // Endless tren server
#define TOP_TIME 1 // normal tren server
#define TOP_DROP 2
#define TOP_TWENTY 3
#define TOP_LINE 4


#define NUM_LEVEL_BOMB 4
#define SIZE_BOARD_BOMB 25
struct TopData {
	string name;
	string id;
	int typeTop;
	int score;
	int index;
	int total;
};

enum GameState
{
	PLAY, NORMAL_GAME, GAME_OVER, TOUCH, MOVE, EFFECT, NEXT_LEVEL, SCORE, PAUSE
};
enum Direct
{
	LEFT, RIGHT, UP, DOWN, UNDEFINE
};

class GameClient : public cocos2d::Ref
{
public:
	GameClient(void);
	~GameClient(void);

	// Application Events
	bool applicationDidFinishLaunching();
	void applicationDidEnterBackground();
	void applicationWillEnterForeground();

	// Game Events
	void init();
	void initGame();
	void update(float delta);
	void loadingCompleted();
	void takeScreenshot();
	void loadShaders();
	void loadPreferences();
	void onPause();
	void onResume();
	void receivePreference(string data);

	// Gamelogic
	void createCow();
	void listenBackToForeground();
	
	static void endGame();
    bool vibrate;
	string standartNum(int num);
	int data[81];
	vector<int> arrayIdGame;
	int extendGame;
	int typeBall;
	float deltaTime;
	int score;
	int saveScore;
	int highscore;
	bool music;
	bool isPlaying;
	bool isPlayingTime;
	int saveScoreTime;
	int dataTime[81];
	int highscoreTime;
	int countUpdate;
	int numUndo;
	bool showSetting;
	
	int arrayBall[9];
	int arrayDataSave[6][81];
	int arrayScoreSave[6];
	string arrayDate[6];
	bool showAnimation;
	float scaleBall;

	int countPlay;
	float timePlay;
	long int timeStart;
	float brightBall;

	float saveTime;
	bool showLanguage;
	int countFinishAds;
	int countNotFinishAds;

	TutorialData* arrayTutorial[10];
	bool showHelp;
	int countHelp;

	int countPlayLevel;
	int dataBlock[8][8];
	

	bool needShowError;

	void loadPlayNormal();
	void loadPlayTime();
	void loadSave();
	void loadColor();

	void resetPlayNormal();
	void resetPlayTime();
	void resetSave();
	void resetColor();
	void onReward(int num);

	int getBiggerId();
	int convertId(int playerId);

	bool isRussia;
	bool isInitAds;
	int isNeedIP;

	int arrayNextBlock[3];
	int arrayBonus[3];
	int dataBlockPuzzel[8][8];
	int highscoreBlock;
	int saveScoreBlock;
	bool isPlayingBlock;
	int numPlayBlock;
	bool showHelpBlock;
	void loadBlock();

	int dataTwenty[8][7];
	bool isFirstTimeTwenty;
	int highscoreSumTwenty;
	int maxNumberTwenty;
	int scoreTwenty;
	int numPlayTwenty;
	void loadTwenty();

	int level;
	int scoreEndless;
	int scoreStomp[21];
	void readDataLevel(int level);
	vector< vector<int> > dataLevel[21];
	int typeRow[21];
	int numBall[21];
	bool isRead[21];
	int scoreTime;
	void loadEgg();

	int saveScoreBubble;
	int highscoreBubble;
	bool isPlayingBubble;
	int dataBubble1[63];
	int dataBubble[45];
	bool showHelpBubble;
	int saveRandBubble[5];
	void loadBubble();
	int numPlayBubble;
	bool isIOS();
	int countPlayAllTime;
	string country;
	float timePlayGame;
	int highscorePop;

	int numPlayBomb;
	int arrBestTime[NUM_LEVEL_BOMB];
	int currentTime;
	int arrBomb[SIZE_BOARD_BOMB][SIZE_BOARD_BOMB];
	int arrCell[SIZE_BOARD_BOMB][SIZE_BOARD_BOMB];
	int currentMode;
	bool showHelpBomb;
	void loadBomb();
	void resetLoad();

	int arrNumRow[10];
	int arrNumColumn[10];
	int dataPika[BOARD_COLUMN_PIKA * BOARD_ROW_PIKA];
	int saveScorePika;
	bool isPlayingPika;
	int levelPika;
	float timePika;
	int numLifePika;
    int highscorePika;
	void loadPika();

	int dataBrick[NUM_HEIGHT][NUM_WIDTH];
	int dataNext[4][4];
	int levelScore[10][10];
	int levelBrick;
	int speedBrick;
	int levelTypeBrick;
	int scoreBrick;
	int highscoreBrick;
	void addScore(int score);
	void setCell(int x, int y);
	GameState state;
	GameState saveState;
	void loadBrick();

	bool showedTop;
	int winCount;
	int lostCount;
	int gold;
	int idAvatar;
	string deviceId;
	string namePlayer;
	vector<TopData> arrayTop[5];
	TopData arrayMyTop[5];
	vector<TopData> arrayTopWin;
	TopData myTopWin;
	vector<TopData> arrayTopGold;
	TopData myTopGold;
	int arrayOldTop[5];
	void pushMyData();
	void insertTop(int type, string name, string score);
	void getTop(int type);
	void getMyTop(int type);
	string getGameId(int type);
	int getGameCode(string gid);
	std::string getAvatarLevel(int level);
	int getLevel(int level);
	bool haveTop();
	bool waitCreateName;
	void pushOneTop(int idTop);

	string getHighscoreData();
	void receiveHighscoreData();

	int targetOldScore;
	int timeShow;

	float timeNoAds;
	void showAdsForOldUser();

	bool showChess;
	void hideGuiWaitting();
    void updateDataFromOld(string username, string password, string deviceId);
    int numPlayGame;
	void initAds();
	void showAdsFull();
};
#endif // GameClient_h__





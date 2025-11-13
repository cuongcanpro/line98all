#include "GameClient.h"
#include "../Engine/GlobalVar.h"
#include "../Engine/Engine.h"
#include "GUIManager.h"
#include "Utility/GameUtility.h"
#include "Game/Utility/Toast.h"
#include <cstdlib>
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//#include "../../Utility/JNIUtils.h"
#endif
#include "Game/Utility//GameSound.h"
#include "Utility/JNIUtils.h"
#include "../Engine/Utility/LocalizedString.h"
#include "../AppDelegate.h"
#define TEST_GUI 0
#include "Engine/Utility/CStringUtils.h"
#include "Engine/Utility/HttpUtils.h"
#include <regex>
//#include "app/GameMgr.h"

using namespace std;


GameClient::GameClient(void)
{
	//
	////connectPortal = false;
	//CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
	//	callfuncO_selector(GameClient::listenBackToForeground),
	//	EVENT_COME_TO_FOREGROUND,
	//	NULL);
}


GameClient::~GameClient(void)
{

}

bool GameClient::applicationDidFinishLaunching()
{
	return true;
}

void GameClient::listenBackToForeground()
{
	loadShaders();
}

void GameClient::applicationDidEnterBackground()
{

}

void GameClient::applicationWillEnterForeground()
{
	
    
}

void GameClient::init()
{
	showChess = false;
	targetOldScore = 500;
	timeShow = 3 * 60;
	timeNoAds = 0;
	timePlayGame = 0;
	isRussia = false;
	isInitAds = false;
	isNeedIP = 0;
	countFinishAds = 0;
	countNotFinishAds = 0;
	srand (time(NULL));
	Engine::init();
	waitCreateName = false;
	loadShaders();
	loadPreferences();

//	countAds = 0;
	deltaTime = 0;
   
	GameSound::loadSound();


	initGame();
    loadBlock();
	string lastDay = CCUserDefault::sharedUserDefault()->getStringForKey("lastDay", "");
	time_t now = time(0);
	tm *ltm = localtime(&now);
	string sDay = GameUtility::toString(ltm->tm_year) + "m" + GameUtility::toString(ltm->tm_mon) + "d" + GameUtility::toString(ltm->tm_mday);
	CCLOG("LAST DAY NE %s ", sDay.c_str());
    

	countPlayAllTime = CCUserDefault::sharedUserDefault()->getIntegerForKey("countPlayAllTime", 0);
	countPlayAllTime = countPlayAllTime + 1;
	CCUserDefault::sharedUserDefault()->setIntegerForKey("countPlayAllTime", countPlayAllTime);
	
	int scale = game->scaleBall * 100;
	int bright = game->brightBall * 100;

	if (highscore > 0) {
		JNIUtils::sendEvent("type_ball", GameUtility::toString(game->typeBall).c_str());
	}

	CCUserDefault::sharedUserDefault()->flush();
	for (int i = 0; i < 5; i++) {
		TopData topData;
		topData.typeTop = i;
		topData.score = -1;
		topData.index = -1;
		arrayMyTop[i] = topData;
	}
	
	deviceId = JNIUtils::getDeviceId();
	CCLOG("Device Id %s ", deviceId.c_str());
	namePlayer = CCUserDefault::sharedUserDefault()->getStringForKey("namePlayer", "");
	for (int i = 0; i < 5; i++) {
		arrayOldTop[i] = CCUserDefault::sharedUserDefault()->getIntegerForKey(("top" + to_string(i)).c_str(), -1);
	}
	//lostCount = CCUserDefault::sharedUserDefault()->getIntegerForKey("lostCount", 0);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//string _arrayName[] = { "OnetConnect","EggShoot","BubbleConnect","TwentyFour","BlockPuzzel","Lines98" };
//string _arrayPackage[] = { "com.bcsofts.linklink","com.lightgames.eggShoot2017","com.bcsofts.bubbleConnect","com.bcsofts.twentyFour","com.lightgames.blockPuzzleExtreme","com.bcsofts.colorLinesReborn" };
//string _arrayInstall[] = { "com.bcsofts.linklink","com.lightgames.eggShoot2017","com.bcsofts.bubbleConnect","com.bcsofts.twentyFour","com.lightgames.blockPuzzleExtreme","com.bcsofts.colorLinesReborn" };

	string _arrayName[] = { "Tien Len", "Drop Number","Lines98" };
	string _arrayPackage[] = { "com.bcsofts.tienlen","com.bcsofts.dropNumber","com.bcsofts.colorLinesReborn" };
	string _arrayInstall[] = { "com.bcsofts.tienlen","com.bcsofts.dropNumber","com.bcsofts.colorLinesReborn" };
	for (int i = 0; i < 2; i++) {
		arrayName.push_back(_arrayName[i]);
		arrayPackage.push_back(_arrayPackage[i]);
		arrayInstall.push_back(_arrayInstall[i]);
		arrayWaitingInstall.push_back(false);
		//s = "https://us-central1-cloudfunction-54e7c.cloudfunctions.net/packageAndroid";
		//GameUtility::callHttpRequest(s.c_str(), httpresponse_selector(HttpRequestHandler::onCompleteGetPackage), handler);
	}
#else
	
//	GameUtility::callHttpRequest(s.c_str(), httpresponse_selector(HttpRequestHandler::onCompleteGetPackage), handler);
#endif
}

void GameClient::receivePreference(string data) {
	
}

void GameClient::loadPreferences() {
	string arrayGame = UserDefault::getInstance()->getStringForKey("arrayIdGame", "0,1,2,3,4,5,6,7,8,9");
	std::stringstream ss(arrayGame);
	std::string token;

	while (std::getline(ss, token, ','))
	{
		arrayIdGame.push_back(std::stoi(token));
	}
	numPlayGame = UserDefault::getInstance()->getIntegerForKey("numPlayGame", 0);
	numPlayGame = numPlayGame + 1;
	//if (numPlayGame > 4)
		//extendGame = 1;
    UserDefault::getInstance()->setIntegerForKey("numPlayGame", numPlayGame);

	int a = -3 % 7;
	//oldVersion = CCUserDefault::sharedUserDefault()->getBoolForKey("oldVersion", false);
//	CCLOG("LOAD PREFERENCE ");
	idAdsBanner = CCUserDefault::sharedUserDefault()->getIntegerForKey("idAdsBanner", 1);
    idAdsFull = CCUserDefault::sharedUserDefault()->getIntegerForKey("idAdsFull", 1);
    adBannerUnit = CCUserDefault::sharedUserDefault()->getStringForKey("adBannerUnit", "ca-app-pub-7169368956692170/5524463808");
    adInterUnit = CCUserDefault::sharedUserDefault()->getStringForKey("adInterUnit", "ca-app-pub-7169368956692170/5053690514");
    adRewardUnit = CCUserDefault::sharedUserDefault()->getStringForKey("adRewardUnit", "ca-app-pub-7169368956692170/4213212447");
//	idAdsBanner = 1;
	//idAdsFull = idAdsBanner;
	saveScore = CCUserDefault::sharedUserDefault()->getIntegerForKey("saveScore", 0);
	//if (this->isIOS())
		isPlaying = CCUserDefault::sharedUserDefault()->getBoolForKey("isPlaying", false);
		CCLOG("Is Playing =========== %s ", isPlaying ? "true" : "false");
	//else
		//isPlaying = CCUserDefault::sharedUserDefault()->getBoolForKey("isPlaying", false);
	highscore = CCUserDefault::sharedUserDefault()->getIntegerForKey("highscoreLine", 0);
	music = CCUserDefault::sharedUserDefault()->getBoolForKey("music", true);
    typeBall = CCUserDefault::sharedUserDefault()->getIntegerForKey("typeBallNew", 0);
	typeBall = 0;
	countUpdate = CCUserDefault::sharedUserDefault()->getIntegerForKey("countUpdate", 0);
	numUndo = CCUserDefault::sharedUserDefault()->getIntegerForKey("numUndo", 3);
	showLanguage = CCUserDefault::sharedUserDefault()->getBoolForKey("showLanguage", false);
	language = CCUserDefault::sharedUserDefault()->getIntegerForKey("language", 0);

	saveScoreTime = CCUserDefault::sharedUserDefault()->getIntegerForKey("scoreTime", 0);
	isPlayingTime = CCUserDefault::sharedUserDefault()->getBoolForKey("isPlayingTime", false);
	highscoreTime = CCUserDefault::sharedUserDefault()->getIntegerForKey("highscoreTime", 0);
	
	if (this->isIOS()) {
		showSetting = CCUserDefault::sharedUserDefault()->getBoolForKey("showSetting", false);
		showAnimation = CCUserDefault::sharedUserDefault()->getBoolForKey("showAnimation", false);
	}
	else {
		showSetting = CCUserDefault::sharedUserDefault()->getBoolForKey("showSetting2", false);
		showAnimation = CCUserDefault::sharedUserDefault()->getBoolForKey("showAnimation2", false);
	}
	scaleBall = CCUserDefault::sharedUserDefault()->getFloatForKey("scaleBall", 0.75f);
	brightBall = CCUserDefault::sharedUserDefault()->getFloatForKey("brightBall", 1.0f);

	showHelp = false;
  
	game->isRussia = CCUserDefault::sharedUserDefault()->getBoolForKey("isRussia", false);
	game->isNeedIP = CCUserDefault::sharedUserDefault()->getIntegerForKey("isNeedIP", 0);
	if (game->isRussia)
		JNIUtils::setRussia(1);
	//showHelp = true;
	//isPlaying = false;
	if (highscore > 0)
		showHelp = false;


	loadColor();
	//loadSave();
	//loadPlayNormal();
	//loadPlayLevel();
	//loadPlayTime();
	//loadPlayExtra();

	arrayTutorial[0] = new TutorialData(3, 6, 0.5, CCLocalizedString("TUTORIAL_1"));
	arrayTutorial[1] = new TutorialData(4, 3, 0.5, CCLocalizedString("TUTORIAL_2"));
	arrayTutorial[2] = new TutorialData(3, 7, 0.5, CCLocalizedString("TUTORIAL_3"));
	arrayTutorial[3] = new TutorialData(4, 4, 0.5, CCLocalizedString("TUTORIAL_4"));
	arrayTutorial[4] = new TutorialData(2, 7, 2.5, CCLocalizedString("TUTORIAL_5"));
	arrayTutorial[5] = new TutorialData(4, 8, 0.5, CCLocalizedString("TUTORIAL_6"));
	arrayTutorial[6] = new TutorialData(0, 0, 2.5, CCLocalizedString("TUTORIAL_7"));
	arrayTutorial[7] = new TutorialData(3, 4, 0.5, CCLocalizedString("TUTORIAL_8"));
	arrayTutorial[8] = new TutorialData(-1, -1, 1.0, CCLocalizedString("TUTORIAL_9"));
	arrayTutorial[9] = new TutorialData(0, 0, 2.0, CCLocalizedString("TUTORIAL_10"));


	//showHelp = true;
	//isPlaying = false;
	countPlayLevel = 0;
	//loadBubble();
	//loadTwenty();
	highscorePop = CCUserDefault::sharedUserDefault()->getIntegerForKey("highscorePop", 0);
	//gameMgr->startGame();
}

void GameClient::loadColor() {
	string s = CCUserDefault::sharedUserDefault()->getStringForKey("arrayBall", "");
	if (s.size() <= 10) {
		resetColor();
		return;
	}
	else {
		char * pch = new char[s.size() + 1];
		std::copy(s.begin(), s.end(), pch);
		pch[s.size()] = '\0'; // don't forget the terminating 0
		char *num;
		num = strtok(pch, ",");
		if (num == NULL) {
			resetColor();
			return;
		}
		try {
			arrayBall[0] = std::stoi(num); //don't call c_str() 
		}
		catch (std::exception const & e)
		{
			resetColor();
			return;
		}
		for (int j = 1; j < 9; j++)
		{
			num = strtok(NULL, ",");
			if (num != NULL) {
				//arrayBall[j] = atoi(num);
				try {
					arrayBall[j] = std::stoi(num); //don't call c_str() 
				}
				catch (std::exception const & e)
				{
					resetColor();
					return;
				}
			}
			else {
				resetColor();
				return;
			}

		}
	}
}

void GameClient::loadPlayNormal() {
	CCLOG("LOAD XONG %i ", isPlaying);
	if (isPlaying)
	{
		bool loadPlayNormal = CCUserDefault::sharedUserDefault()->getBoolForKey("loadPlayNormal", false);
		if (loadPlayNormal) {
			resetPlayNormal();
			return;
		}
		CCUserDefault::sharedUserDefault()->setBoolForKey("loadPlayNormal", true);
		CCUserDefault::sharedUserDefault()->flush();
		string s;
//if (isIOS())
	//	s = CCUserDefault::sharedUserDefault()->getStringForKey("dataNormal", "");
//else
		s = CCUserDefault::sharedUserDefault()->getStringForKey("data", "");
		if (s.size() <= 10) {
			resetPlayNormal();
			return;

		}
		else {
			char * pch = new char[s.size() + 1];
			std::copy(s.begin(), s.end(), pch);
			pch[s.size()] = '\0'; // don't forget the terminating 0
			char *num;
			num = strtok(pch, ",");
			if (num == NULL) {
				resetPlayNormal();
				return;
			}
			try {
				data[0] = std::stoi(num); //don't call c_str() 
			}
			catch (std::exception const & e)
			{
				resetPlayNormal();
				return;
			}
			for (int i = 1; i < 81; i++)
			{
				num = strtok(NULL, ",");
				if (num == NULL) {
					resetPlayNormal();
					return;
				}
				try {
					data[i] = std::stoi(num); //don't call c_str() 
				}
				catch (std::exception const & e)
				{
					resetPlayNormal();
					return;
				}
			}
			CCLOG("DATA %s", s.c_str());
		}
		CCUserDefault::sharedUserDefault()->setBoolForKey("loadPlayNormal", false);
		CCUserDefault::sharedUserDefault()->flush();
	}
}

void GameClient::loadPlayTime() {
	if (isPlayingTime)
	{
		bool loadPlayTime = CCUserDefault::sharedUserDefault()->getBoolForKey("loadPlayTime", false);
		if (loadPlayTime) {
			resetPlayTime();
			return;
		}
		CCUserDefault::sharedUserDefault()->setBoolForKey("loadPlayTime", true);
		CCUserDefault::sharedUserDefault()->flush();

		string s = CCUserDefault::sharedUserDefault()->getStringForKey("dataTime", "");
		if (s.size() <= 10) {
			resetPlayTime();
			return;
		}
		else {
			char * pch = new char[s.size() + 1];
			std::copy(s.begin(), s.end(), pch);
			pch[s.size()] = '\0'; // don't forget the terminating 0
			char *num;
			num = strtok(pch, ",");
			if (num == NULL) {
				resetPlayTime();
				return;
			}
			try {
				dataTime[0] = std::stoi(num); //don't call c_str() 
			}
			catch (std::exception const & e)
			{
				resetPlayTime();
				return;
			}
			for (int i = 1; i < 81; i++)
			{
				num = strtok(NULL, ",");
				if (num == NULL) {
					resetPlayTime();
					return;
				}
				try {
					dataTime[i] = std::stoi(num); //don't call c_str() 
				}
				catch (std::exception const & e)
				{
					resetPlayTime();
					return;
				}
			}
		}
		CCUserDefault::sharedUserDefault()->setBoolForKey("loadPlayTime", false);
		CCUserDefault::sharedUserDefault()->flush();
	}
}

void GameClient::loadSave() {

	for (int i = 0; i < 6; i++) {

		arrayScoreSave[i] = CCUserDefault::sharedUserDefault()->getIntegerForKey(("arrayScoreSave" + GameUtility::toString(i)).c_str(), -1);
		if (arrayScoreSave[i] >= 0) {
			string s = CCUserDefault::sharedUserDefault()->getStringForKey(("arrayDataSave" + GameUtility::toString(i)).c_str(), "");
			if (s.size() <= 10) {
				resetSave();
				return;
			}
			char * pch = new char[s.size() + 1];
			std::copy(s.begin(), s.end(), pch);
			pch[s.size()] = '\0'; // don't forget the terminating 0
			char *num;
			num = strtok(pch, ",");
			if (num == NULL) {
				resetSave();
				return;
			}
			try {
				arrayDataSave[i][0] = std::stoi(num); //don't call c_str() 
			}
			catch (std::exception const & e)
			{
				resetSave();
				return;
			}
			for (int j = 1; j < 81; j++)
			{
				num = strtok(NULL, ",");
				if (num == NULL) {
					resetSave();
					return;
				}
				try {
					arrayDataSave[i][j] = std::stoi(num); //don't call c_str() 
				}
				catch (std::exception const & e)
				{
					resetSave();
					return;
				}
			}
			arrayDate[i] = CCUserDefault::sharedUserDefault()->getStringForKey(("arrayDate" + GameUtility::toString(i)).c_str(), "");
		}
	}
}

void GameClient::resetPlayNormal() {
	isPlaying = false;
	if (isIOS())
		CCUserDefault::sharedUserDefault()->setBoolForKey("isPlayingNormal", false);
	else
		CCUserDefault::sharedUserDefault()->setBoolForKey("isPlaying", false);
	CCUserDefault::sharedUserDefault()->setBoolForKey("loadPlayNormal", false);

	CCUserDefault::sharedUserDefault()->flush();
}

void GameClient::resetPlayTime() {
	isPlayingTime = false;
	CCUserDefault::sharedUserDefault()->setBoolForKey("loadPlayTime", false);
	CCUserDefault::sharedUserDefault()->setBoolForKey("isPlayingTime", false);
	CCUserDefault::sharedUserDefault()->flush();
}

void GameClient::resetSave() {
	for (int i = 0; i < 6; i++) {
		arrayScoreSave[i] = -1;
		CCUserDefault::sharedUserDefault()->setIntegerForKey(("arrayScoreSave" + GameUtility::toString(i)).c_str(), -1);
	}
	CCUserDefault::sharedUserDefault()->flush();
}


void GameClient::resetColor() {
	string s = "";
	for (int i = 0; i < 9; i++) {
		arrayBall[i] = i;
		if (i == 0) {
			s = s + GameUtility::toString(i);
		}
		else {
			s = s + "," + GameUtility::toString(i);
		}
	}
	CCUserDefault::sharedUserDefault()->setStringForKey("arrayBall", s.c_str());
	CCUserDefault::sharedUserDefault()->flush();
}

void GameClient::initGame()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("480_800/gamePika/texture.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("480_800/texture.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("texture.plist");
	GameSound::loadSound();

    HttpRequestHandler *handler = new HttpRequestHandler();
    
    string s ;

		// game egg
		if (isIOS())
			s = "https://news.beansofts.com/?a=722&v=1&p=1";

        GameUtility::callHttpRequest(s.c_str(), httpresponse_selector(HttpRequestHandler::onCompleteGetVersion), handler);
	
	
	GUIManager::getInstance().showGui(&GUIManager::getInstance().guiTypeSudoku);
	//	GUIManager::getInstance().guiSudoku.showGUIWithMode(LEVEL_SUDOKU);

//    //CCLog("CHECK INSTALL %i ", IOSConnection::checkInstallApp(urlCheck.c_str()));
//    //GUIManager::getInstance().guiBoard.startOffline();
//    
//	
	//string s1 = CCLocalizedString("TEST_JSON");
	//s1 = "{\"highscore\":5,\"highscoreTime\":0,\"isPlaying\":1,\"isPlayingTime\":1,\"data\":\"0,5,0,0,14,0,0,6,0,0,0,0,0,5,0,0,0,7,7,1,0,5,0,-1,6,1,0,0,5,6,0,1,0,-1,-1,0,0,14,0,-1,-1,-1,-1,-1,0,0,7,0,-1,0,0,0,0,0,3,0,0,-1,0,0,0,0,0,4,4,4,1,0,0,0,0,2,0,7,8,0,-1,-1,0,6,0,\",\"dataTime\":\"0,0,14,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,0,0,0,0,0,0,7,2,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,0,0,0,0,1,0,0,0,7,0,0,0,0,0,0,0,0,10,0,0,0,0,0,0,3,0,0,0,0,0,0,4,0,0,0,\",\"score\":5,\"scoreTime\":0}";
	//receivePreference(s1);
}

void GameClient::takeScreenshot()
{

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCRenderTexture* texture = CCRenderTexture::create((int)size.width, (int)size.height);
	texture->setPosition(ccp(size.width/2, size.height/2));
	texture->begin();
	CCDirector::sharedDirector()->getRunningScene()->visit();
	texture->end();
	texture->saveToFile("chessLightgame.png", kCCImageFormatPNG);
    std::string path = CCFileUtils::sharedFileUtils()->getWritablePath() + "chessLightgame.png";
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
	//FacebookController::sharePhoto(path.c_str());
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	JNIUtils::sharePhoto(path.c_str());
#endif

}


void GameClient::loadShaders()
{
#if CC_TARGET_PLATFORM != CC_PLATFORM_WP8
	CCGLProgram* shader=new CCGLProgram();
	shader->initWithVertexShaderFilename("shaders/shaderGray.vsh","shaders/shaderGray.fsh");
	//shader->bindAttribLocation(kCCAttributeNamePosition,kCCVertexAttrib_Position);
	//shader->addAttribute(kCCAttributeNameTexCoord,kCCVertexAttrib_TexCoords);
	shader->link();
	shader->updateUniforms();
	CCShaderCache::sharedShaderCache()->addProgram(shader,kShaderGrayProgram);

	shader=new CCGLProgram();
	shader->initWithVertexShaderFilename("shaders/shaderGray.vsh","shaders/shaderNormal.fsh");
	//shader->addAttribute(kCCAttributeNamePosition,kCCVertexAttrib_Position);
	//shader->addAttribute(kCCAttributeNameTexCoord,kCCVertexAttrib_TexCoords);
	shader->link();
	shader->updateUniforms();
	CCShaderCache::sharedShaderCache()->addProgram(shader,kShaderNormal);

	shader=new CCGLProgram();
	shader->initWithVertexShaderFilename("shaders/shaderGray.vsh","shaders/shaderLighter.fsh");
	//shader->addAttribute(kCCAttributeNamePosition,kCCVertexAttrib_Position);
	//shader->addAttribute(kCCAttributeNameTexCoord,kCCVertexAttrib_TexCoords);
	shader->link();
	shader->updateUniforms();
	CCShaderCache::sharedShaderCache()->addProgram(shader,kShaderLighter);

#endif
}


void GameClient::update(float delta)
{
	GUIManager::getInstance().isCallBackPress = false;
	game->deltaTime = delta;
	timeNoAds = timeNoAds + delta;
	
	if (GUIManager::getInstance().guiLine.isInitted() && GUIManager::getInstance().guiLine.isVisible()) {
		GUIManager::getInstance().guiLine.update(delta);
	}
	
	if (GUIManager::getInstance().guiGame.isInitted() && GUIManager::getInstance().guiGame.isVisible()) {
		GUIManager::getInstance().guiGame.update(delta);
	}
	if (GUIManager::getInstance().guiTwenty.isInitted() && GUIManager::getInstance().guiTwenty.isVisible()) {
		GUIManager::getInstance().guiTwenty.update();
	}
	if (GUIManager::getInstance().guiEgg.isInitted() && GUIManager::getInstance().guiEgg.isVisible()) {
		GUIManager::getInstance().guiEgg.act(delta);
	}
	if (GUIManager::getInstance().guiMerge.isInitted() && GUIManager::getInstance().guiMerge.isVisible()) {
		GUIManager::getInstance().guiMerge.update();
	}
	if (GUIManager::getInstance().guiPop.isInitted() && GUIManager::getInstance().guiPop.isVisible()) {
		GUIManager::getInstance().guiPop.update();
	}
	if (GUIManager::getInstance().guiBomb.isInitted() && GUIManager::getInstance().guiBomb.isVisible()) {
		GUIManager::getInstance().guiBomb.update(deltaTime);
	}
	
    if (GUIManager::getInstance().guiPikachu.isInitted() && GUIManager::getInstance().guiPikachu.isVisible())
    {
        GUIManager::getInstance().guiPikachu.act();
    }
	if (GUIManager::getInstance().guiBrick.isInitted() && GUIManager::getInstance().guiBrick.isVisible())
	{
		GUIManager::getInstance().guiBrick.update();
	}

}

void GameClient::onPause()
{
}

void GameClient::onResume()
{
}


void GameClient::endGame()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	
	exit(1);
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//JNIUtils::openPortal();
	CCDirector::sharedDirector()->end();
	
#endif

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	exit(1);
#endif
}

string GameClient::standartNum( int num )
{
	if(num > 999999)
		num = 999999;
	string result = CStringUtils::toString(num);
	int add = 6 - result.length();
	for(int i = 0; i < add; i++)
	{
		result = "0" + result;
	}
	return result;
}


void GameClient::onReward(int num)
{
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	Size frameSize = glview->getFrameSize();
	if ((frameSize.height / frameSize.width) <= (1.0f))
	{
		//gameMgr->onReward(num);
		return;
	}
	if (num > 0) {
        if (GUIManager::getInstance().guiSudoku.isInitted() && GUIManager::getInstance().guiSudoku.isVisible()) {
            GUIManager::getInstance().guiSudoku.onHint();
        }
	}
	else {
		game->countNotFinishAds++;
		GUIManager::getInstance().guiDialog.showGUI(CCLocalizedString("NOT_FINISH_REWARD").c_str(), NULL, true);
		JNIUtils::sendEvent("not_finish_show_ads", GameUtility::toString(game->countNotFinishAds).c_str());
	}
	}

int GameClient::getBiggerId()
{
	
	return -1;
}

int GameClient::convertId(int playerId)
{
	
	return 1;
}

void GameClient::loadBlock()
{
	game->showHelpBlock = CCUserDefault::sharedUserDefault()->getIntegerForKey("showHelpBlock", true);
	game->highscoreBlock = CCUserDefault::sharedUserDefault()->getIntegerForKey("highscoreBlock", 0);
	//game->isPlayingBlock = false;
	game->isPlayingBlock = UserDefault::getInstance()->getBoolForKey("isPlayingBlock", false);
	if (game->isPlayingBlock)
	{
		string s = (string)(UserDefault::getInstance()->getStringForKey("dataBlock", ""));
		char* pch = new char[s.size() + 1];
		std::copy(s.begin(), s.end(), pch);
		pch[s.size()] = '\0';  // don't forget the terminating 0
		char* num;
		num = strtok(pch, ",");
		dataBlockPuzzel[0][0] = atoi(num);
		for (int i = 1; i < 64; i++)
		{
			num = strtok(NULL, ",");
			int row = i / 8;
			int column = i % 8;
			dataBlockPuzzel[row][column] = atoi(num);
		}

		for (int i = 0; i < 3; i++)
		{
			arrayNextBlock[i] =
				UserDefault::getInstance()->getIntegerForKey(
				("dataNextBlock" + to_string(i)).c_str(), 0);
			if (arrayNextBlock[i] < 0 || arrayNextBlock[i] > 11)
				arrayNextBlock[i] = 0;
		}

		for (int i = 0; i < 3; i++) {
			arrayBonus[i] =
				UserDefault::getInstance()->getIntegerForKey(("dataBonusBlock" +
					to_string(i)).c_str(), 0);
		}
	}
}

void GameClient::loadTwenty()
{
	isFirstTimeTwenty = CCUserDefault::sharedUserDefault()->getBoolForKey("isFirstTimeTwenty", true);
	scoreTwenty = CCUserDefault::sharedUserDefault()->getIntegerForKey("saveScoreTwenty", 0);
	//highscore = 10;
	highscoreSumTwenty = CCUserDefault::sharedUserDefault()->getIntegerForKey("highscoreSum", 5);
	numPlayTwenty = CCUserDefault::sharedUserDefault()->getIntegerForKey("numPlayTwenty", 0);
	//highscoreSum = 10;
}


void GameClient::loadEgg()
{
    scoreTime = CCUserDefault::sharedUserDefault()->getIntegerForKey("scoreTime", 0);
	scoreEndless = CCUserDefault::sharedUserDefault()->getIntegerForKey("scoreEndless", 0);
	for (int i = 0; i < 21; i++) {
		isRead[i] = false;
	}
    level = CCUserDefault::sharedUserDefault()->getIntegerForKey("level", 1);
	for (int i = 0; i < 21; i++)
		scoreStomp[i] = CCUserDefault::sharedUserDefault()->getIntegerForKey(("scoreStomp" + GameUtility::toString(i)).c_str(), 0);
	
}

void GameClient::readDataLevel(int levelIndex)
{
	if (isRead[levelIndex])
		return;
	isRead[levelIndex] = true;
	string line;
	//ifstream myfile ("common/level" + CStringUtils::toString(levelType) + ".txt");
	string s = ScreenUtils::fileCommon((GameUtility::toString(levelIndex) + ".txt").c_str());
	std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(s.c_str());
	//CCLog("FULLPATH %s	", fullPath.c_str());
	//ifstream myfile ("common/splash.txt");

	ssize_t fileSize;
	unsigned char * fileContents = NULL;
	string contents;
	fileContents = CCFileUtils::sharedFileUtils()->getFileData(fullPath.c_str(), "r", &fileSize);
	contents.append((char *)fileContents);
	//CCLog(contents.c_str());
	istringstream myfile(contents);

	int count = 0;
	int countLevel = 1;
	int numRow = 0, numCol = 0;

	vector< vector<int> > arrayRow;
	while (getline(myfile, line))
	{
		int i = 0;

		if (count == 0) {
			// doc so hang
			numRow = stoi(line);
			/*for (int i = 0; i < line.length(); i++)
			{
				if (line.at(i) <= '9' && line.at(i) >= '0')
				{
					if (i == 0)
					{
						numRow = numRow + (int)(line.at(i) - '0');
					}
					else
					{
						numRow = numRow + pow(10, i) * (int)(line.at(i) - '0');
					}
				}
			}*/
			//CCLog("NUMROW %i ", numRow);
			//numRow = std::stoi (line,nullptr,10);

		}
		else if (count == 1) {
			numCol = stoi(line);
			/*for (int i = 0; i < line.length(); i++)
			{
				if (line.at(i) <= '9' && line.at(i) >= '0')
				{
					if (i == 0)
					{
						numCol = numCol + (int)(line.at(i) - '0');
					}
					else
					{
						numCol = numCol + pow(10, i) * (int)(line.at(i) - '0');
					}
				}
			}*/
			//CCLog("numCol %i ", numCol);
			//numCol = std::stoi (line,nullptr,10);
			//data = new int[numRow][numCol];
		}
		else if (count == 2) {
			typeRow[levelIndex] = stoi(line);
			/*for (int i = 0; i < line.length(); i++)
			{
				if (line.at(i) <= '9' && line.at(i) >= '0')
				{
					if (i == 0)
					{
						typeRow[levelIndex] = typeRow[levelIndex] + (int)(line.at(i) - '0');
					}
					else
					{
						typeRow[levelIndex] = typeRow[levelIndex] + pow(10, i) * (int)(line.at(i) - '0');
					}
				}
			}*/
			//typeRow[levelIndex] =  std::stoi (line,nullptr,10);
		}
		else if (count == 3) {
			numBall[levelIndex] = stoi(line);
			/*for (int i = 0; i < line.length(); i++)
			{
				if (line.at(i) <= '9' && line.at(i) >= '0')
				{
					if (i == 0)
					{
						numBall[levelIndex] = numBall[levelIndex] + (int)(line.at(i) - '0');
					}
					else
					{
						numBall[levelIndex] = numBall[levelIndex] + pow(10, i) * (int)(line.at(i) - '0');
					}
				}
			}*/
			//	numBall[levelIndex] =  std::stoi (line,nullptr,10);
		}
		else {
			vector<int> arrayBall;
			for (int i = 0; i < line.length(); i++) {
				if (line.at(i) == '-')
					arrayBall.push_back(-1);
				else if (line.at(i) <= '9' && line.at(i) >= '0') {
					arrayBall.push_back(line.at(i) - '0' - 1);
					//CCLog("array ball %i ", arrayBall.at(arrayBall.size() - 1));
				}
			}
			if (arrayRow.size() < numRow)
				arrayRow.push_back(arrayBall);
		}
		dataLevel[levelIndex] = arrayRow;
		count++;
	}
	//HttpRequestHandler *handler = new HttpRequestHandler();
	//s = "http://news.beansofts.com/?a=10&v=5";
	//GameUtility::callHttpRequest(s.c_str(), httpresponse_selector(HttpRequestHandler::onCompleteGetVersion), handler);
}


void GameClient::loadBubble() {
	
	showHelpBubble = CCUserDefault::sharedUserDefault()->getBoolForKey("showHelpBubble", true);
//	showHelpBubble = true;
	saveScoreBubble = CCUserDefault::sharedUserDefault()->getIntegerForKey("scoreBubble", 0);
	isPlayingBubble = CCUserDefault::sharedUserDefault()->getBoolForKey("isPlayingBubble", false);
	highscoreBubble = CCUserDefault::sharedUserDefault()->getIntegerForKey("highscoreBubble", 0);

	string s = CCUserDefault::sharedUserDefault()->getStringForKey("saveRandBubble", "00000");
	for (int i = 0; i < 5; i++)
	{
		saveRandBubble[i] = s.at(i) - '0';
	}


	if (isPlayingBubble)
	{
		string s = CCUserDefault::sharedUserDefault()->getStringForKey("dataBubble", "");
		char * pch = new char[s.size() + 1];
		std::copy(s.begin(), s.end(), pch);
		pch[s.size()] = '\0'; // don't forget the terminating 0
		char *num;
		num = strtok(pch, ",");
		dataBubble[0] = atoi(num);
		for (int i = 1; i < 45; i++)
		{
			num = strtok(NULL, ",");
			dataBubble[i] = atoi(num);
		}
	}
	numPlayBubble = CCUserDefault::sharedUserDefault()->getIntegerForKey("numPlayBubble", 0);
}

bool GameClient::isIOS()
{
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	return true;
#endif
	return false;
}


void GameClient::loadBomb()
{
	numPlayBomb = CCUserDefault::sharedUserDefault()->getIntegerForKey("numPlayBomb", 0);
	showHelpBomb = CCUserDefault::sharedUserDefault()->getBoolForKey("showHelpBomb", true);
	for (int i = 0; i < NUM_LEVEL_BOMB; i++) {
		arrBestTime[i] = CCUserDefault::sharedUserDefault()->getIntegerForKey(("bestTime" + to_string(i)).c_str(), 0);
	}
	currentTime = CCUserDefault::sharedUserDefault()->getIntegerForKey("currentTime", 0);
	currentMode = CCUserDefault::sharedUserDefault()->getIntegerForKey("currentMode", 0);

	if (currentTime > 0)
	{
		string s = CCUserDefault::sharedUserDefault()->getStringForKey("arrBomb", "");
		if (s.size() <= 10) {
			resetLoad();
			return;
		}
		else {
			char * pch = new char[s.size() + 1];
			std::copy(s.begin(), s.end(), pch);
			pch[s.size()] = '\0'; // don't forget the terminating 0
			char *num;
			num = strtok(pch, ",");
			if (num == NULL) {
				resetLoad();
				return;
			}
			try {
				arrBomb[0][0] = std::stoi(num); //don't call c_str() 
			}
			catch (std::exception const & e)
			{
				resetLoad();
				return;
			}
			for (int i = 1; i < SIZE_BOARD_BOMB * SIZE_BOARD_BOMB; i++)
			{
				num = strtok(NULL, ",");
				if (num == NULL) {
					resetLoad();
					return;
				}
				try {
					int row = i / SIZE_BOARD_BOMB;
					int column = i % SIZE_BOARD_BOMB;
					arrBomb[row][column] = std::stoi(num); //don't call c_str() 
				}
				catch (std::exception const & e)
				{
					resetLoad();
					return;
				}
			}
		}

		s = CCUserDefault::sharedUserDefault()->getStringForKey("arrCell", "");
		if (s.size() <= 10) {
			resetLoad();
			return;
		}
		else {
			char * pch = new char[s.size() + 1];
			std::copy(s.begin(), s.end(), pch);
			pch[s.size()] = '\0'; // don't forget the terminating 0
			char *num;
			num = strtok(pch, ",");
			if (num == NULL) {
				resetLoad();
				return;
			}
			try {
				arrCell[0][0] = std::stoi(num); //don't call c_str() 
			}
			catch (std::exception const & e)
			{
				resetLoad();
				return;
			}
			for (int i = 1; i < SIZE_BOARD_BOMB * SIZE_BOARD_BOMB; i++)
			{
				num = strtok(NULL, ",");
				if (num == NULL) {
					resetLoad();
					return;
				}
				try {
					int row = i / SIZE_BOARD_BOMB;
					int column = i % SIZE_BOARD_BOMB;
					arrCell[row][column] = std::stoi(num); //don't call c_str() 
				}
				catch (std::exception const & e)
				{
					resetLoad();
					return;
				}
			}
		}

	}
}

void GameClient::resetLoad()
{
	CCUserDefault::sharedUserDefault()->setIntegerForKey("currentTime", 0);
	CCUserDefault::sharedUserDefault()->flush();
	currentTime = 0;
}

void GameClient::loadPika() {
    highscorePika = CCUserDefault::sharedUserDefault()->getIntegerForKey("highscorePika", 0);
	isPlayingPika = CCUserDefault::sharedUserDefault()->getBoolForKey("isPlayingPika1", false);
	if (isPlayingPika)
	{
		numLifePika = CCUserDefault::sharedUserDefault()->getIntegerForKey("numLifePika", 10);
		levelPika = CCUserDefault::sharedUserDefault()->getIntegerForKey("levelPika", 0);
		timePika = CCUserDefault::sharedUserDefault()->getFloatForKey("timePika", 0);
		//timePika = 300;
		saveScorePika = CCUserDefault::sharedUserDefault()->getIntegerForKey("saveScorePika", 0);
		string s = CCUserDefault::sharedUserDefault()->getStringForKey("dataPika", "");
		if (s.size() <= 10) {
			CCUserDefault::sharedUserDefault()->setBoolForKey("isPlayingPika1", false);
			game->isPlayingPika = false;
			return;
		}
		else {
			char * pch = new char[s.size() + 1];
			std::copy(s.begin(), s.end(), pch);
			pch[s.size()] = '\0'; // don't forget the terminating 0
			char *num;
			num = strtok(pch, ",");
			if (num == NULL) {
				CCUserDefault::sharedUserDefault()->setBoolForKey("isPlayingPika1", false);
				game->isPlayingPika = false;
				return;
			}
			try {
				dataPika[0] = std::stoi(num); //don't call c_str() 
			}
			catch (std::exception const & e)
			{
				CCUserDefault::sharedUserDefault()->setBoolForKey("isPlayingPika1", false);
				game->isPlayingPika = false;
				return;
			}
			for (int i = 1; i < BOARD_ROW_PIKA * BOARD_COLUMN_PIKA; i++)
			{
				num = strtok(NULL, ",");
				if (num == NULL) {
					CCUserDefault::sharedUserDefault()->setBoolForKey("isPlayingPika1", false);
					game->isPlayingPika = false;
					return;
				}
				try {
					dataPika[i] = std::stoi(num); //don't call c_str() 
				}
				catch (std::exception const & e)
				{
					CCUserDefault::sharedUserDefault()->setBoolForKey("isPlayingPika1", false);
					game->isPlayingPika = false;
					return;
				}
			}
			CCLOG("DATA %s", s.c_str());
		}
	}
}

void GameClient::pushMyData()
{
	if (haveTop() == false) {
		getTop(TOP_NORMAL);
		getTop(TOP_TIME);
	}
	else {
		insertTop(TOP_NORMAL, namePlayer, to_string(game->highscore));
		insertTop(TOP_TIME, namePlayer, to_string(game->highscoreTime));
	}
}

void GameClient::pushOneTop(int idTop)
{
	if (haveTop()) {
		// kiem tra xem co su khac biet ve Score cua top nay khong
		int score = 0;
		switch (idTop)
		{
		case TOP_TIME:
			score = game->scoreTime;
			break;
		case TOP_NORMAL:
			score = game->scoreEndless;
			break;
		
		case TOP_DROP:
			score = CCUserDefault::sharedUserDefault()->getIntegerForKey("highscoreMerge", 0);
			break;
		default:
			break;
		}
		if (score != game->arrayMyTop[idTop].score || namePlayer.compare(game->arrayMyTop[idTop].name) != 0) {
			// can phai day du lieu cua minh len
			insertTop(idTop, namePlayer, to_string(score));
		}
		else {
			// neu co mang Top roi thi cung khong lay lai nua
			if (arrayTop[idTop].size() == 0) {
				getTop(idTop);
			}
		}
	}
	else {
		// Lay thong tin ve bang TOP
		if (arrayTop[idTop].size() == 0) {
			getTop(idTop);
		}
	}
}


std::string GameClient::getHighscoreData()
{
	string data = "";
	data = "highscore_" + to_string(highscore) + "_";
	data = "highscoreTime_" + to_string(highscoreTime) + "_";
	
	return data;
}

void GameClient::receiveHighscoreData()
{
	loadPreferences();
	CCUserDefault::sharedUserDefault()->setBoolForKey("restoreData", true);
	CCUserDefault::sharedUserDefault()->flush();
	/*std::regex regexz("_");
	std::vector<std::string> arrData = { std::sregex_token_iterator(data.begin(), data.end(), regexz, -1), std::sregex_token_iterator() };
	for (int i = 0; i < arrData.size(); i++) {
		if (arrData[i].compare("highscore") == 0 && i + 1 < arrData.size()) {
			game->highscore = stoi(arrData[i + 1]);
			CCUserDefault::sharedUserDefault()->setIntegerForKey("highscore", game->highscore);
		}
		else if (arrData[i].compare("highscoreTime") == 0 && i + 1 < arrData.size()) {
			game->highscoreTime = stoi(arrData[i + 1]);
			CCUserDefault::sharedUserDefault()->setIntegerForKey("highscoreTime", game->highscore);
		}
		else if (arrData[i].compare("highscoreExtra") == 0 && i + 1 < arrData.size()) {
			game->highscoreExtra = stoi(arrData[i + 1]);
			CCUserDefault::sharedUserDefault()->setIntegerForKey("highscoreExtra", game->highscore);
		}
		else if (arrData[i].compare("highscoreLevel") == 0 && i + 1 < arrData.size()) {
			game->highscoreLevel = stoi(arrData[i + 1]);
			CCUserDefault::sharedUserDefault()->setIntegerForKey("highscoreLevel", game->highscore);
		}
		else if (arrData[i].compare("highscoreChallenge") == 0 && i + 1 < arrData.size()) {
			game->highscoreChallenge = stoi(arrData[i + 1]);
			CCUserDefault::sharedUserDefault()->setIntegerForKey("highscoreChallenge", game->highscore);
		}
		i++;
	}
	CCUserDefault::sharedUserDefault()->flush();*/
}


void GameClient::addScore(int score)
{
	game->scoreBrick = game->scoreBrick + score;
	GUIManager::getInstance().guiBrick.updateScore();

	if (speedBrick == 9)
		return;
	else
	{
		if (game->scoreBrick >= levelScore[levelTypeBrick][speedBrick + 1])
		{
			speedBrick++;
		}
		GUIManager::getInstance().guiBrick.updateSpeed();
	}
}

void GameClient::setCell(int x, int y)
{
	if (x < 0 || x > NUM_WIDTH - 1)
		return;
	if (y < 0 || y > NUM_HEIGHT - 1)
		return;
	dataBrick[y][x] = 1;
}


void GameClient::showAdsForOldUser()
{
  //  targetOldScore = 1;
  //  timeShow = 10;
	if (timeNoAds > timeShow && idAdsBanner != 3) {
		//if (game->highscore > 500 && timeNoAds > 4 * 60 && idAdsBanner != 3) {
		JNIUtils::showAdsFull();
	}
}

void okInsertTop() {
	//GUIManager::getInstance().showGui(&GUIManager::getInstance().guiTop);
}

void GameClient::insertTop(int type, string name, string score)
{
	//score = "1";
	string s = "";
	if (type == TOP_TIME) {
		s = "&order=asc";
	}
    if (stoi(score) == 0) {
        game->getTop(type);
        return;
    }
	string urlRequest1 = "https://news.beansofts.com/?a=2000&sa=1" + s;
	urlRequest1 = urlRequest1 + "&id=" + deviceId;
	urlRequest1 = urlRequest1 + "&name=" + name;
	urlRequest1 = urlRequest1 + "&score=" + score;
	urlRequest1 = urlRequest1 + "&gid=" + getGameId(type);
	string data1 = "";
	//CCLOG("Request insertTop %s ", urlRequest1.c_str());
	HttpUtils::addRequestPost(urlRequest1, data1, [this](bool isSuccess, std::string data) {
		CCLOG("Data Insert Top %s ", data.c_str());
		rapidjson::Document doc;
		doc.Parse<0>(data.c_str());
		if (!doc.HasParseError() && doc.IsObject()) {
			string status = "";
			if (doc.HasMember("status"))
				status = doc["status"].GetString();
			if (status.compare("OK") == 0) {
				string gid = "";
				if (doc.HasMember("gid"))
					gid = doc["gid"].GetString();
				int topCode = getGameCode(gid);
				game->getTop(topCode);
				game->getMyTop(topCode);
				if (game->waitCreateName) {
					game->waitCreateName = false;
					GUIManager::getInstance().guiDialog.showGUI(CCLocalizedString("FINISH_INPUT_NAME").c_str(), &okInsertTop, true);
				}
				else {
					/*GUITop* guiTop = (GUITop*)sceneMgr->getGUIByClassName(GUITop::className);
					if (guiTop != nullptr) {
						guiTop->insertDone();
					}*/

				}
			}
		}
	});
}

void GameClient::getTop(int type)
{
	string s = "";
	if (type == TOP_TIME) {
		s = "&order=asc";
	}
	string urlRequest1 = "https://news.beansofts.com/?a=2000&sa=2&top=20" + s;
	urlRequest1 = urlRequest1 + "&gid=" + getGameId(type);
	CCLOG("Request getTop %s ", urlRequest1.c_str());
	string data1 = "";

	HttpUtils::addRequestPost(urlRequest1, data1, [this](bool isSuccess, std::string data) {
		CCLOG("push %s ", data.c_str());
		rapidjson::Document doc;
		doc.Parse<0>(data.c_str());
		if (!doc.HasParseError() && doc.IsObject()) {
			string status = "";
			if (doc.HasMember("status"))
				status = doc["status"].GetString();
			if (status.compare("OK") == 0) {
				string gid = "";
				if (doc.HasMember("gid"))
					gid = doc["gid"].GetString();

				if (doc.HasMember("users")) {
					const rapidjson::Value& users = doc["users"];
					int topCode = getGameCode(gid);
					arrayTop[topCode].clear();
					for (rapidjson::SizeType i = 0; i < users.Size(); i++)
					{
						TopData topData;
						if (users[i].HasMember("name")) {
							topData.name = users[i]["name"].GetString();
						}
						if (users[i].HasMember("score")) {
							topData.score = stoi(users[i]["score"].GetString());
						}
						if (users[i].HasMember("id")) {
							topData.id = users[i]["id"].GetString();
						}
						topData.index = i + 1;
						topData.typeTop = topCode;
						arrayTop[topCode].push_back(topData);
					}
					if (GUIManager::getInstance().guiTopEgg.isInitted() && GUIManager::getInstance().guiTopEgg.isVisible()) {
						GUIManager::getInstance().guiTopEgg.reloadTopData();
					}
				}
			}
		}
	});

	/*for (rapidjson::Value::ConstValueIterator itr = doc.Begin(); itr != doc.End(); ++itr) {
		const rapidjson::Value& attribute = *itr;
		TopData topData;
		if (attribute.HasMember("name")) {
			topData.name = attribute["name"].GetString();
		}
		if (attribute.HasMember("score")) {
			topData.score = stoi(attribute["score"].GetString());
		}
		switch (gameMgr->typeTop)
		{
		case TOP_WIN:
			arrayTopWin.clear();
			arrayTopWin.push_back(topData);
			break;
		case TOP_GOLD:
			arrayTopGold.clear();
			arrayTopGold.push_back(topData);
			break;
		default:
			break;
		}

	}*/
	CCLOG("Finish Get Top");


}


void GameClient::getMyTop(int type)
{
	string s = "";
	if (type == TOP_TIME) {
		s = "&order=asc";
	}
	string urlRequest = "https://news.beansofts.com/?a=2000&sa=3" + s;
	urlRequest = urlRequest + "&id=" + deviceId;
	urlRequest = urlRequest + "&gid=" + getGameId(type);
	//CCLOG("getmy top %s ", urlRequest.c_str());
	string data = "";
	HttpUtils::addRequestPost(urlRequest, data, [this](bool isSuccess, std::string data) {
		CCLOG("MyInfo %s ", data.c_str());
		rapidjson::Document attribute;
		attribute.Parse<0>(data.c_str());
		if (attribute.HasParseError()) {
			// chua co du lieu trong Top
		}
		else {
			if (attribute.IsObject()) {
				if (attribute.HasMember("status") && attribute.HasMember("user")) {
					string status = attribute["status"].GetString();
					if (status.compare("OK") == 0) {
						string gid = "";
						rapidjson::Value& user = attribute["user"];
						if (attribute.HasMember("gid")) {
							gid = attribute["gid"].GetString();
						}
						int topCode = getGameCode(gid);
						CCLOG("User is NULL ============= %i ", user.IsNull());
						if (!user.IsNull() && user.IsObject()) {
							if (user.HasMember("name")) {
								arrayMyTop[topCode].name = user["name"].GetString();
								namePlayer = user["name"].GetString();
							}
							if (user.HasMember("score")) {
								arrayMyTop[topCode].score = stoi(user["score"].GetString());
								/*if (topCode == TOP_NORMAL) {
									if (arrayMyTop[topCode].score > game->highscore) {
										game->highscore = arrayMyTop[topCode].score;
									}
								}*/
							}
							if (user.HasMember("top_position")) {
								arrayMyTop[topCode].index = user["top_position"].GetInt();
								CCUserDefault::sharedUserDefault()->setIntegerForKey(("top" + to_string(topCode)).c_str(), arrayMyTop[topCode].index);
							}
							arrayMyTop[topCode].id = deviceId;
							CCUserDefault::sharedUserDefault()->setStringForKey("namePlayer", namePlayer);
							CCUserDefault::sharedUserDefault()->flush();

							// cap nhat du lieu GUI Top neu GUI Top dang hien thi
							if (GUIManager::getInstance().guiTopEgg.isInitted() && GUIManager::getInstance().guiTopEgg.isVisible()) {
								GUIManager::getInstance().guiTopEgg.reloadMyData();
							}
						}
					}
				}
			}
		}
	});
}


int GameClient::getLevel(int winCount)
{
	/*if (true)
		return WinCount();*/
	int level = winCount / 5;
	level = (int)log2(level);
	if (level < 0)
		level = 0;
	return level;
}

bool GameClient::haveTop()
{
	return arrayMyTop[0].index >= 0;
}

string GameClient::getGameId(int type) {
	string gid = "egg_normal";
	
		switch (type)
		{
		case TOP_NORMAL:
			gid = "egg_endless";
			break;
		case TOP_TIME:
			gid = "egg_normal";
			break;
		case TOP_DROP:
			gid = "drop";
			break;
		case TOP_TWENTY:
			gid = "twenty";
			break;
		case TOP_LINE:
			gid = "lines98_normal";
			break;
		default:
			break;
		}

	//gid = "lines98";
	return gid;
}

int GameClient::getGameCode(string gid)
{
	//return 0;
	if (gid.compare("egg_normal") == 0)
			return TOP_TIME;
		if (gid.compare("egg_endless") == 0)
			return TOP_NORMAL;
		if (gid.compare("drop") == 0)
			return TOP_DROP;
		if (gid.compare("twenty") == 0)
			return TOP_TWENTY;
		if (gid.compare("lines98_normal") == 0)
			return TOP_LINE;
}


void GameClient::loadBrick()
{
	highscoreBrick = UserDefault::getInstance()->getIntegerForKey("highscoreBrick", 0);
	// isFirstTimeTwenty = true;
	levelTypeBrick = 3;
	game->scoreBrick = 0;
	levelScore[3][1] = 0;
	levelScore[3][2] = 200;
	levelScore[3][3] = 500;
	levelScore[3][4] = 1000;
	levelScore[3][5] = 2000;
	levelScore[3][6] = 5000;
	levelScore[3][7] = 10000;
	levelScore[3][8] = 20000;
	levelScore[3][9] = 50000;
}

void GameClient::hideGuiWaitting()
{
	if (GUIManager::getInstance().guiLoadingAds.isInitted() && GUIManager::getInstance().guiLoadingAds.isVisible()) {
		GUIManager::getInstance().removeFromListGui();
	}
}

void GameClient::updateDataFromOld(string username, string password, string deviceId) {
    CCUserDefault::sharedUserDefault()->setStringForKey("newUsername", username);
    CCUserDefault::sharedUserDefault()->setStringForKey("newPassword", password);
    CCUserDefault::sharedUserDefault()->setStringForKey("deviceId", deviceId);
    CCUserDefault::sharedUserDefault()->flush();
}

void GameClient::initAds() {
	//return;
	if (isInitAds)
		return;
	isInitAds = true;
	JNIUtils::initAds(adBannerUnit.c_str(), adInterUnit.c_str(), adRewardUnit.c_str(), idAdsBanner, idAdsFull);
}

void GameClient::showAdsFull()
{
	if (game->timeNoAds < 120)
	{
		// if (game->timeNoAds < 20) {
		return;
	}
	JNIUtils::showAdsFull();
	//GUIManager::getInstance().guiWaiting.showAds(false);
}

/*****************************  Native Callback method  *****************************/
extern "C" {
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)

	void Java_org_cocos2dx_cpp_AppActivity_nativeDataPreference(JNIEnv* env, jobject thiz, jstring accessToken)
	{
		std::string resultData = env->GetStringUTFChars(accessToken, 0);
		game->receivePreference(resultData);
	}

	void Java_org_cocos2dx_cpp_AppActivity_highscoreDataPreference(JNIEnv* env, jobject thiz, jstring accessToken)
	{
		std::string resultData = env->GetStringUTFChars(accessToken, 0);
		game->receiveHighscoreData();
        
	}
#endif
}

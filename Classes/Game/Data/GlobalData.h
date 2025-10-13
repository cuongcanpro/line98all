#pragma once

#ifndef GlobalData_h__
#define GlobalData_h__

#include "string"

extern std::string versionApp;
extern int port;
extern std::string ip;
extern std::string urlVersion;
extern std::string urlTop;
extern std::string deviceId;
extern std::string gameCode;
extern std::string urlCheck;
extern std::string appName;

extern int platformId;
extern std::string platformString;
extern std::string source;
extern std::string urlUpdate;
extern std::string urlPromote;
extern int isApp;
extern std::string urlForum;
extern std::string urlHelp;
extern int updateGame;
extern int maintain;
extern bool isZingphone;

extern int defaultLogin;
extern bool isNetwork;
extern int xuChange;
extern int fakeApp;

extern bool gameInit;
extern int giftIndex;
extern int timeSupport;
extern int numSupport;
extern bool isHolding;
extern int channelHold;
extern int roomHold;
extern std::string passHold;
extern bool isSound;
extern bool showSupportTime;
extern std::string typeSocialLogin;
extern int isPromote;

extern int idAdsFull;
extern int idAdsBanner;
extern int haveModeOnline;
extern std::string adBannerUnit;
extern std::string adInterUnit;
extern std::string adRewardUnit;


extern float WIDTH;
extern float RATE;
extern float WIDTH_BALL;
extern int NUM_ROW;
extern int NUM_COLUMN;
extern float START_X;
extern float START_Y;
extern float WIDTH_SQUARE;
extern float LIMIT_Y;
extern float HEIGH_BALL;
extern float WIDTH_BALL_TWENTY;
extern float START_X_TWENTY;
extern float START_Y_TWENTY;

extern float WIDTH_BALL_EGG;
extern int EIGHT_ROW;
extern int NINE_ROW;
extern float START_X_EGG;
extern float START_Y_EGG;
extern float LIMIT_X;
extern float HEIGH_BALL_EGG;
extern float WIDTH_GATE;
extern float START_BALL_X;
extern float START_BALL_Y;
extern int NUM_BALL;
extern float SPEED_BIRD;

extern int NUM_ROW_GAME;
extern int NUM_COLUMN_GAME;
extern float SIZE_BALL;
static const int NUM_ROW_MERGE = 6;
static const int NUM_COLUMN_MERGE = 5;

#endif // GlobalData_h__



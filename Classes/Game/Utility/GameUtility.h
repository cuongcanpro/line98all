#ifndef GAME_UTILITY_H
#define GAME_UTILITY_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cocos2d.h>
#include <cocos-ext.h>
#include "Game/NetworkGame/HttpRequestHandler.h"
#include "network/HttpClient.h"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace cocos2d::network;
using namespace std;

class GameUtility
{
public:
	static vector<string> split(const string& s, const string& delim, const bool keep_empty = true);
	static std::string standartTime(int num);
	static string toString(int value);
	static string standardizeString(string value, int numCharacter = 10);
	static string standardizeNumber(int value);
	
	static string urlEncode(const std::string &value);
	static float getRandom();
	static string standartNum(int num, int max);
    static void callHttpRequest(const char* url, SEL_HttpResponse callBack, HttpRequestHandler* handler);
	static cocos2d::ccColor3B getColorLine(int id);
	static const char* getTexture(int id);
	static string getTextureCell(int id);
	static string getResourceBall(int id);
	static string getTextureColor(int id);
	static cocos2d::ccColor3B getColorTwenty(int id);
	static cocos2d::ccColor3B getColor(int id);
	static cocos2d::ccColor3B getColorMerge(int id);
	static cocos2d::ccColor3B getColorPop(int id);
	static string convertToTime(int time);
    static string convertTime(int value);
#ifdef ANDROID
	static string imei;
	static string getIMEI();
#endif
	static int convertExp2Level(int exp);
//	static void callHttpRequest(const char* url, SEL_HttpResponse callBack, HttpRequestHandler* handler);
	std::string getClockDay( double timeValue );
};
#endif

#include "GameUtility.h"
#include <cocos2d.h>
#include "../GUIManager.h"
#include "Engine/Utility/LocalizedString.h"
#include "Engine/Utility/CStringUtils.h"
#include <cctype>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include "Engine/GlobalVar.h"
using namespace cocos2d;

vector<string> GameUtility::split(const string& s, const string& delim, const bool keep_empty)
{
	vector<string> result;
	if (delim.empty()) {
		result.push_back(s);
		return result;
	}
	string::const_iterator substart = s.begin(), subend;
	while (true) {
		subend = search(substart, s.end(), delim.begin(), delim.end());
		string temp(substart, subend);
		if (keep_empty || !temp.empty()) {
			result.push_back(temp);
		}
		if (subend == s.end()) {
			break;
		}
		substart = subend + delim.size();
	}
	return result;
}

std::string GameUtility::standartTime(int num)
{
	if(num < 10)
		return "0" + GameUtility::toString(num);
	else
		return GameUtility::toString(num);
}


string GameUtility::toString(int value)
{
	ostringstream ss;
	ss << value;
	return ss.str();
}

string GameUtility::standardizeString(string value, int numCharacter)
{
	if(value.length() > numCharacter)
	{
		string result = value.substr(0, numCharacter - 2);
		return result + "...";
	}
	else
	{
		return value;
	}
	
}

string GameUtility::standardizeNumber(int value)
{
	string num = toString(value);
	string result = "";
	for(int i = num.length() -1 ; i >= 0; i--)
	{
		result = num.at(i) + result;
		if((num.length() - i)%3 == 0 && i != 0)
		{
			result = "." + result;
		}
	}
	return result;
}


#ifdef ANDROID

#include "cocos2d.h"
#include <string.h>
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include "platform/CCCommon.h"

string GameUtility::imei = "";

string GameUtility::getIMEI(){
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t,
	                                            "com/gsn/jni/JNIConnection",
	                                            "getIMEI",
	                                            "()Ljava/lang/String;"))
	{
	    jobject result = t.env->CallStaticObjectMethod(t.classID, t.methodID);
	    
	    jstring value = jstring(result);
	    string finalResult = JniHelper::jstring2string(value);
		//CCLOG("result = %s", finalResult);
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(result);
		return finalResult;
	}
	return "";
}
#endif

int GameUtility::convertExp2Level(int exp)
{
	int level = 0;
	if (exp <= 1600) {
		level = 0;
	} else if (exp <= 1690) {
		level = 1;
	} else if (exp <= 1780) {
		level = 2;
	} else if (exp <= 1870) {
		level = 3;
	} else if (exp <= 1960) {
		level = 4;
	} else if (exp <= 2050) {
		level = 5;
	} else if (exp <= 2140) {
		level = 6;
	} else if (exp <= 2230) {
		level = 7;
	} else if (exp <= 2320) {
		level = 8;
	} else {
		level = 9;
	}
	return level;
}

// void GameUtility::callHttpRequest(const char* url, SEL_HttpResponse callBack, HttpRequestHandler* handler)
// {
// 	CCLOG("url = %s", url);
// 	cocos2d::extension::CCHttpRequest* request = new cocos2d::extension::CCHttpRequest();
// 	request->setUrl(url);
// 	request->setRequestType(cocos2d::extension::CCHttpRequest::kHttpGet);
// 
// 	/*request->setRequestType(cocos2d::extension::CCHttpRequest::kHttpPost);
// 	string postData = "pid=25&u1=http%3A%2F%2Flogin.me.zing.vn%2Flogin%2Fsuccess&fp=http%3A%2F%2Flogin.me.zing.vn%2Flogin%2Ffai&apikey=6bfea26364a08c4ad330dceef4e999a7&u=" + string(userName) + "&p=" + string(password) + "&longtime=1";
// 	int length = strlen(postData.c_str());
// 	request->setRequestData(postData.c_str(), length);*/
// 
// 	request->setResponseCallback(handler, callBack);
// 	cocos2d::extension::CCHttpClient::getInstance()->send(request);
// 	request->release();
// }

float GameUtility::getRandom()
{
	float r = (float)(rand()) / RAND_MAX;
	return r;
}

string GameUtility::standartNum( int num, int max )
{
	int maxConvert = pow(10, max);
	maxConvert = maxConvert - 1;
	if(num > maxConvert)
		num = maxConvert;
	string result = CStringUtils::toString(num);
	int add = max - 1 - result.length();
	for(int i = 0; i < add; i++)
	{
		result = "0" + result;
	}
	return result;
}

void GameUtility::callHttpRequest(const char* url, SEL_HttpResponse callBack, HttpRequestHandler* handler)
{
    CCLOG("url = %s", url);
	HttpRequest* request = new (std::nothrow) HttpRequest();
	request->setUrl(url);
	request->setRequestType(HttpRequest::Type::GET);
	request->setResponseCallback(handler, callBack);
	request->setTag("GET immediate test1");
	HttpClient::getInstance()->sendImmediate(request);
	request->release();

    //cocos2d::extension::CCHttpRequest* request = new cocos2d::extension::CCHttpRequest();
    //request->setUrl(url);
    //request->setRequestType(cocos2d::extension::CCHttpRequest::kHttpGet);
    //
    ///*request->setRequestType(cocos2d::extension::CCHttpRequest::kHttpPost);
    // string postData = "pid=25&u1=http%3A%2F%2Flogin.me.zing.vn%2Flogin%2Fsuccess&fp=http%3A%2F%2Flogin.me.zing.vn%2Flogin%2Ffai&apikey=6bfea26364a08c4ad330dceef4e999a7&u=" + string(userName) + "&p=" + string(password) + "&longtime=1";
    // int length = strlen(postData.c_str());
    // request->setRequestData(postData.c_str(), length);*/
    //
    //request->setResponseCallback(handler, callBack);
    //cocos2d::extension::CCHttpClient::getInstance()->send(request);
    //request->release();
}


cocos2d::ccColor3B GameUtility::getColorLine(int id)
{
	switch (id) {
	case 1:
		return ccc3(255, 0, 0);
		break;
	case 2:
		return ccc3(0, 0, 255);
		break;
	case 3:
		return ccc3(0, 255, 0);
		break;
	case 4:
		return ccc3(255, 255, 0);
		break;
	case 5:
		return ccc3(255, 51, 204);
		break;
	case 6:
		return ccc3(153, 102, 51);
		break;
	case 0:
		return ccc3(0, 204, 255);
		break;

	}
}

const char* GameUtility::getTexture(int id)
{
	/*switch (id % 20) {
	case 0:
		return "lineBall_2_0.png";
		break;
	case 1:
		return "lineBall_2_0.png";
		break;
	case 2:
		return "lineBall_2_1.png";
		break;
	case 3:
		return "lineBall_2_1.png";
		break;
	case 4:
		return "lineBall_2_2.png";
		break;
	case 5:
		return "lineBall_2_2.png";
		break;
	case 6:
		return "lineBall_2_3.png";
		break;
	case 7:
		return "lineBall_2_3.png";
		break;
	case 8:
		return "lineBall_2_4.png";
		break;
	case 9:
		return "lineBall_2_4.png";
		break;
	case 10:
		return "lineBall_2_5.png";
		break;
	case 11:
		return "lineBall_2_5.png";
		break;
	default:
		return "lineBall_2_0.png";
		break;
	}
*/
	switch (id % 20) {
	case 0:
		return "gameBlockPuzzel/cell_0.png";
		break;
	case 1:
		return "gameBlockPuzzel/cell_0.png";
		break;
	case 2:
		return "gameBlockPuzzel/cell_1.png";
		break;
	case 3:
		return "gameBlockPuzzel/cell_1.png";
		break;
	case 4:
		return "gameBlockPuzzel/cell_2.png";
		break;
	case 5:
		return "gameBlockPuzzel/cell_2.png";
		break;
	case 6:
		return "gameBlockPuzzel/cell_3.png";
		break;
	case 7:
		return "gameBlockPuzzel/cell_3.png";
		break;
	case 8:
		return "gameBlockPuzzel/cell_4.png";
		break;
	case 9:
		return "gameBlockPuzzel/cell_4.png";
		break;
	case 10:
		return "gameBlockPuzzel/cell_5.png";
		break;
	case 11:
		return "gameBlockPuzzel/cell_5.png";
		break;
	default:
		return "gameBlockPuzzel/cell_0.png";
		break;
	}
}

string GameUtility::getTextureCell(int id)
{
	string s = "480_800/";
	s.append(getTexture(id));
	return s;
}

std::string GameUtility::getResourceBall(int id)
{
	game->typeBall = 0;
	string s = "lineBall_" + GameUtility::toString(game->typeBall) + "_";
	if (id < 100) {
		if (id < 1 || id > 7) {
			id = 1;
		}
		s = s + GameUtility::toString(game->arrayBall[id - 1]) + ".png";
	}
	else {
		s = "cell.png";
	}
	
	return s;
}

string GameUtility::getTextureColor(int id)
{
	int color = 0;
	int _id = id;
	while (_id / 2 != 0)
	{
		color++;
		_id = _id / 2;

	}
	return "gameBubble/cell_" + GameUtility::toString(color % 9) + ".png";
}


cocos2d::ccColor3B GameUtility::getColor(int id)
{
	int color = 0;
	int _id = id;
	while (_id / 2 != 0)
	{
		color++;
		_id = _id / 2;

	}
	color = color + 1;
	switch (color % 20) {
	case 1:

		return ccc3(0, 153, 255);
		break;
	case 2:
		return ccc3(255, 204, 0);
		break;
	case 3:
		return ccc3(255, 0, 0);
		break;
	case 4:
		return ccc3(204, 0, 153);
		break;
	case 5:
		return ccc3(0, 204, 0);
		break;
	case 6:
		return ccc3(255, 102, 0);
		break;
	case 7:
		return ccc3(0, 0, 255);
		break;
	case 8:
		return ccc3(153, 102, 51);
		break;
	case 9:
		return ccc3(102, 102, 153);
		break;
	case 10:
		return ccc3(0, 102, 0);
		break;
	case 11:
		return ccc3(0.0f * 255, 0.11f * 255, 0.4f * 255);
		break;
	case 12:
		return ccc3(1.0f * 255, 0.6f * 255, 0.78f * 255);
		break;
	case 13:
		return ccc3(0.5f * 255, 0.0f * 255, 0.1f * 255);
		break;
	case 14:
		return ccc3(0.6f * 255, 0.7f * 255, 0.9f * 255);
		break;
	case 15:
		return ccc3(0.9f * 255, 0.84f * 255, 0.76f * 255);
		break;
	case 16:
		return ccc3(0.77f * 255, 0.59f * 255, 0.31f * 255);
		break;
	case 17:
		return ccc3(0.7f * 255, 0.0f * 255, 0.15f * 255);
		break;
	case 18:
		return ccc3(0.44f * 255, 0.34f * 255, 0.99f * 255);
		break;
	case 19:
		return ccc3(0.0f * 255, 0.39f * 255, 0.19f * 255);
		break;
	case 0:
		return ccc3(0.96f * 255, 0.53f * 255, 0.47f * 255);
		break;
	}
}

cocos2d::ccColor3B GameUtility::getColorTwenty(int id)
{
	switch (id % 25)
	{
	case 0:
		return ccc3(135, 162, 81);
		break;
	case 1:
		return ccc3(255, 51, 52);
		break;
	case 2:
		return ccc3(56, 170, 56);
		break;
	case 3:
		return ccc3(255, 204, 0);
		break;
	case 4:
		return ccc3(50, 204, 254);
		break;
	case 5:
		return ccc3(255, 103, 154);
		break;
	case 6:
		return ccc3(199, 95, 60);
		break;
	case 7:
		return ccc3(191, 67, 191);
		break;
	case 8:
		return ccc3(203, 204, 102);
		break;
	case 9:
		return ccc3(255, 102, 0);
		break;
	case 10:
		return ccc3(102, 154, 204);
		break;
	case 11:
		return ccc3(150, 150, 150);
		break;
	case 12:
		return ccc3(138, 73, 95);
		break;
	case 13:
		return ccc3(153, 204, 51);
		break;
	case 14:
		return ccc3(255, 153, 52);
		break;
	case 15:
		return ccc3(255, 51, 102);
		break;
	case 16:
		return ccc3(75, 120, 205);
		break;
	case 17:
		return ccc3(255, 51, 154);
		break;
	case 18:
		return ccc3(53, 51, 255);
		break;
	case 19:
		return ccc3(255, 51, 87);
		break;
	case 20:
		return ccc3(129, 59, 40);
		break;
	case 21:
		return ccc3(117, 63, 146);
		break;
	case 22:
		return ccc3(56, 121, 40);
		break;
	case 23:
		return ccc3(204, 204, 204);
		break;
	case 24:
		return ccc3(55, 88, 150);
		break;
	default:
		return ccc3(255, 255, 255);
		break;
	}
}

cocos2d::ccColor3B GameUtility::getColorMerge(int id)
{
	switch (id % 25)
	{
	case 0:
		return ccc3(104, 124, 187);
		break;
	case 1:
		return ccc3(255, 51, 52);
		break;
	case 2:
		return ccc3(56, 170, 56);
		break;
	case 3:
		return ccc3(255, 204, 0);
		break;
	case 4:
		return ccc3(50, 204, 254);
		break;
	case 5:
		return ccc3(255, 103, 154);
		break;
	case 6:
		return ccc3(199, 95, 60);
		break;
	case 7:
		return ccc3(191, 67, 191);
		break;
	case 8:
		return ccc3(203, 204, 102);
		break;
	case 9:
		return ccc3(205, 102, 0);
		break;
	case 10:
		return ccc3(178, 24, 25);
		break;
	case 11:
		return ccc3(45, 18, 176);
		break;
	case 12:
		return ccc3(117, 194, 140);
		break;
	case 13:
		return ccc3(203, 184, 131);
		break;
	case 14:
		return ccc3(139, 119, 196);
		break;
	case 15:
		return ccc3(255, 210, 51);
		break;
	case 16:
		return ccc3(139, 255, 51);
		break;
	case 17:
		return ccc3(48, 255, 255);
		break;
	case 18:
		return ccc3(143, 8, 241);
		break;
	case 19:
		return ccc3(255, 56, 87);
		break;
	case 20:
		return ccc3(79, 216, 255);
		break;
	case 21:
		return ccc3(214, 255, 47);
		break;
	case 22:
		return ccc3(192, 134, 112);
		break;
	case 23:
		return ccc3(12, 173, 94);
		break;
	case 24:
		return ccc3(23, 115, 182);
		break;
	default:
		return ccc3(255, 255, 255);
		break;
	}
}



cocos2d::ccColor3B GameUtility::getColorPop(int id)
{
	switch (id % 25)
	{
	case 0:
		return ccc3(240, 0, 0);
		break;
	case 1:
		return ccc3(240, 0, 0);
		break;
	case 2:
		return ccc3(0, 240, 0);
		break;
	case 3:
		return ccc3(0, 0, 240);
		break;
	case 4:
		return ccc3(240, 240, 0);
		break;
	case 5:
		return ccc3(255, 157, 0);
		break;
	case 6:
		return ccc3(255, 142, 214);
		break;
	case 7:
		return ccc3(1, 200, 201);
		break;
	case 8:
		return ccc3(21, 180, 2);
		break;
	case 9:
		return ccc3(91, 18, 3);
		break;
	case 10:
		return ccc3(255, 1, 162);
		break;
	case 11:
		return ccc3(212, 186, 6);
		break;
	case 12:
		return ccc3(99, 1, 212);
		break;
	case 13:
		return ccc3(203, 184, 131);
		break;
	case 14:
		return ccc3(139, 119, 196);
		break;
	case 15:
		return ccc3(255, 210, 51);
		break;
	case 16:
		return ccc3(139, 255, 51);
		break;
	case 17:
		return ccc3(48, 255, 255);
		break;
	case 18:
		return ccc3(143, 8, 241);
		break;
	case 19:
		return ccc3(255, 56, 87);
		break;
	case 20:
		return ccc3(79, 216, 255);
		break;
	case 21:
		return ccc3(214, 255, 47);
		break;
	case 22:
		return ccc3(192, 134, 112);
		break;
	case 23:
		return ccc3(12, 173, 94);
		break;
	case 24:
		return ccc3(23, 115, 182);
		break;
	default:
		return ccc3(255, 255, 255);
		break;
	}
}

std::string GameUtility::convertToTime(int timeGame)
{
	if (timeGame <= 0)
		return "xx:xx:xx";
	int convertTime = timeGame;
	int hour = convertTime / 3600;
	convertTime = convertTime % 3600;
	int minute = convertTime / 60;
	int second = convertTime % 60;
	string s = hour < 10 ? "0" + to_string(hour) : to_string(hour);
	s = s + ":" + (minute < 10 ? "0" + to_string(minute) : to_string(minute));
	s = s + ":" + (second < 10 ? "0" + to_string(second) : to_string(second));
	return s;
}

std::string GameUtility::convertTime(int countTime)
{
    int minute = (int)(countTime / 60);
    int second = (int)(countTime - minute * 60);

    string minuteS, secondS;
    if (minute < 10) {
        minuteS = "0" + GameUtility::toString(minute);
    }
    else {
        minuteS = "" + GameUtility::toString(minute);
    }

    if (second < 10) {
        secondS = "0" + GameUtility::toString(second);
    }
    else {
        secondS = "" + GameUtility::toString(second);
    }
    return minuteS + ":" + secondS;
}

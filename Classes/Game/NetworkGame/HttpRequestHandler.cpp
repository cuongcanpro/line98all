
#include "HttpRequestHandler.h"
#include <stdlib.h>

#include "../GUIManager.h"
#include "Engine/GlobalVar.h"
#include "../../Engine/Utility/CStringUtils.h"
#include "../Utility/JNIUtils.h"
#include "../GameClient.h"
#include "Game/Data/GlobalData.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "PlatformWrapper.h"
#endif

HttpRequestHandler::HttpRequestHandler(void)
{
}


HttpRequestHandler::~HttpRequestHandler(void)
{
}


void httpUpdateGame()
{

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	// update Game IOS
    PlatformWrapper::openURL(urlUpdate.c_str());
	// PlatformWrapper::openUpdate("http:\/\/itunes.apple.com\/vn\/app\/clash-of-clans\/id529479190?mt=8");
	exit(1);
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID|| CC_TARGET_PLATFORM == CC_PLATFORM_WIN32|| CC_TARGET_PLATFORM == CC_PLATFORM_WP8)

	// update Game Android
	string url = urlUpdate + "&referrer=" + game->getHighscoreData();
	JNIUtils::openApp(url.c_str());
	game->endGame();
#endif
}

void httpConnectGame()
{

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

    
        GUIManager::getInstance().removeAllGui();
        GUIManager::getInstance().showGui(&GUIManager::getInstance().guiMinigames);
    
	
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

		/*if(GUIManager::getInstance().guiLoading.isEndLoading())
		{
			GUIManager::getInstance().removeAllGui();
			GUIManager::getInstance().showGui(&GUIManager::getInstance().guiLogin);
		}
		else{
			updateGame = 0;
		}*/
	
#endif
}

void HttpRequestHandler::onCompleteGetVersion(cocos2d::network::HttpClient *client, cocos2d::network::HttpResponse *response)
{
	if (!response)
	{
		return;
	}

	// You can get original request type from: response->request->reqType
	if (0 != strlen(response->getHttpRequest()->getTag()))
	{
		log("%s completed", response->getHttpRequest()->getTag());
	}

	long statusCode = response->getResponseCode();
	char statusString[64] = {};
	sprintf(statusString, "HTTP Status Code: %ld, tag = %s", statusCode, response->getHttpRequest()->getTag());
	log("response code: %ld", statusCode);
	if(response->getResponseCode() == -1)
	{
		//httpConnectGame();
		return;
	}

	if (!response->isSucceed())
	{
		log("response failed");
		log("error buffer: %s", response->getErrorBuffer());
		return;
	}

	// dump data
	std::vector<char> *buffer = response->getResponseData();
	log("Http Test, dump data: ");
	for (unsigned int i = 0; i < buffer->size(); i++)
	{
		//log("%c", (*buffer)[i]);
	}
	string result(buffer->begin(), buffer->end());
	log("Content %s ", result.c_str());
	rapidjson::Document d;
	d.Parse<0>(result.c_str());
	int error = -1;
	
	string data = "";
	string updateMessage = "";
	string maintainMessage = "";
	updateMessage = "Please update new version app!";
	if(d.GetParseError() == NULL)
	{
		CCLOG("PARSE DATA");
		//if (d.HasMember("need_update")) {
			if (d.HasMember("need_update")) {
				updateGame = d["need_update"].GetInt();
			}
			if (d.HasMember("link_update")) {
				urlUpdate = d["link_update"].GetString();
			}
			if (d.HasMember("support")) {
				fakeApp = d["support"].GetInt();
			}
			if (d.HasMember("idAdsFull"))
			{
				idAdsFull = d["idAdsFull"].GetInt();
                CCUserDefault::sharedUserDefault()->setIntegerForKey("idAdsFull", idAdsFull);
			}
			if (d.HasMember("idAdsBanner"))
			{
				idAdsBanner = d["idAdsBanner"].GetInt();
				CCUserDefault::sharedUserDefault()->setIntegerForKey("idAdsBanner", idAdsBanner);
				
			}
            CCUserDefault::sharedUserDefault()->flush();
            if (d.HasMember("adBannerUnit"))
            {
                adBannerUnit = d["adBannerUnit"].GetString();
                CCUserDefault::sharedUserDefault()->setStringForKey("adBannerUnit", adBannerUnit);
            }
            if (d.HasMember("adInterUnit"))
            {
                adInterUnit = d["adInterUnit"].GetString();
                CCUserDefault::sharedUserDefault()->setStringForKey("adInterUnit", adInterUnit);
            }
            if (d.HasMember("adRewardUnit"))
            {
                adRewardUnit = d["adRewardUnit"].GetString();
                CCUserDefault::sharedUserDefault()->setStringForKey("adRewardUnit", adRewardUnit);
            }
			if (d.HasMember("updateMessage"))
			{
				updateMessage = d["updateMessage"].GetString();
			}
			if (d.HasMember("targetOldScore"))
			{
				game->targetOldScore = d["targetOldScore"].GetInt();
			}
			if (d.HasMember("timeShow"))
			{
				game->timeShow = d["timeShow"].GetInt();
			}
        if (d.HasMember("numGame"))
        {
            int numGame = d["numGame"].GetInt();
            if (game->numPlayGame > numGame) {
                game->extendGame = 1;
            }
        }
			
			//haveModeOnline = 1;
			//updateGame = 1;
	//	}
	}
//	game->countUpdate = 10;
	//updateGame = 3;
	
//	ip = "118.102.3.8";
	//port = 443;
	//fakeApp = 1;
	// updateGame = 1;
	//updateGame = 2;
	CStringUtils::replaceAll(updateMessage, "#", "\n");
	
	if (updateGame != 0) {
			//CCUserDefault::sharedUserDefault()->setIntegerForKey("countUpdate", 0);
			//CCUserDefault::sharedUserDefault()->flush();
		if (updateGame == 1)
		{
			GUIManager::getInstance().guiDialog.showGUI(updateMessage.c_str(), httpUpdateGame, true);
			return;
		}
		else if (updateGame == 2)
		{
			GUIManager::getInstance().guiDialog.showGUI(updateMessage.c_str(), httpUpdateGame, false, httpConnectGame);
			return;
		}
	}
	else {
		
	}
	CCUserDefault::sharedUserDefault()->flush();
}

void HttpRequestHandler::onCompleteGetFake(cocos2d::network::HttpClient *client, cocos2d::network::HttpResponse *response)
{
    if(!response)
        return;
    
    if (0 != strlen(response->getHttpRequest()->getTag()))
    {
    }
    
    if(response->getResponseCode() == -1)
    {
        return;
    }
    
    
    std::vector<char> *buffer = response->getResponseData();
    string result(buffer->begin(), buffer->end());
   // CCLOG("receive = %s", result.c_str());
    rapidjson::Document d;
    d.Parse<0>(result.c_str());
    int error = -1;
    
    string data = "";
    
    string updateMessage = "";
    
    string maintainMessage = "";
    
    
    if(d.GetParseError() == NULL)
    {
        //if (d.HasMember("support"))
    //    fakeApp = d["support"].GetInt();
    }
   // fakeApp = 1;
}

void HttpRequestHandler::onCompleteGetPackage(cocos2d::network::HttpClient *client, cocos2d::network::HttpResponse *response)
{
    if(!response)
        return;
    
    if (0 != strlen(response->getHttpRequest()->getTag()))
    {
    }
    
    if(response->getResponseCode() == -1)
    {
		CCLOG("FAIL NE ");
        return;
    }
    
}

void HttpRequestHandler::onCompleteGetIP(cocos2d::network::HttpClient *client, cocos2d::network::HttpResponse *response)
{
	if (!response)
		return;

	if (0 != strlen(response->getHttpRequest()->getTag()))
	{
	}

	if (response->getResponseCode() == -1)
	{
		CCLOG("GET IP FAIL *** ");
		return;
	}


	std::vector<char> *buffer = response->getResponseData();
	string result(buffer->begin(), buffer->end());
	CCLOG("receive = %s", result.c_str());
	rapidjson::Document d;
	d.Parse<0>(result.c_str());
	int error = -1;

	string data = "";

	string updateMessage = "";

	string maintainMessage = "";


	
}

void HttpRequestHandler::onCompleteGetIP2(cocos2d::network::HttpClient *client, cocos2d::network::HttpResponse *response)
{
	if (!response)
		return;

	if (0 != strlen(response->getHttpRequest()->getTag()))
	{
	}

	if (response->getResponseCode() == -1)
	{
		CCLOG("GET IP FAIL *** ");
		return;
	}


	std::vector<char> *buffer = response->getResponseData();
	string result(buffer->begin(), buffer->end());
	CCLOG("receive = %s", result.c_str());
	rapidjson::Document d;
	d.Parse<0>(result.c_str());
	int error = -1;

	string data = "";

	string updateMessage = "";

	string maintainMessage = "";


}


void HttpRequestHandler::onCompleteGetIP3(cocos2d::network::HttpClient *client, cocos2d::network::HttpResponse *response)
{
	if (!response)
		return;

	if (0 != strlen(response->getHttpRequest()->getTag()))
	{
	}

	if (response->getResponseCode() == -1)
	{
		CCLOG("GET IP FAIL *** ");
		return;
	}


	std::vector<char> *buffer = response->getResponseData();
	string result(buffer->begin(), buffer->end());
	CCLOG("receive = %s", result.c_str());
	rapidjson::Document d;
	d.Parse<0>(result.c_str());
	int error = -1;

	string data = "";

	string updateMessage = "";

	string maintainMessage = "";
}

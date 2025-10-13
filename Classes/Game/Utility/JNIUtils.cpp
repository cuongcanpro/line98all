#include "JNIUtils.h"
#include "cocos2d.h"

USING_NS_CC;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "PlatformWrapper.h"
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include "platform/CCCommon.h"
#endif


#include "../Data/GlobalData.h"
#include "../../Engine/GlobalVar.h"
#include "../GUIManager.h"
//#include "PlatformInterface/IOS/FacebookController.h"



bool JNIUtils::isConnected()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t,
		"org/cocos2dx/cpp/CaroSendFactory",
		"isConnected", "()I"))
	{
		jint s = t.env->CallStaticIntMethod(t.classID, t.methodID);
		return (s == 1 ? true : false);
	}
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	return true;
#endif
}

void JNIUtils::connect()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t,
		"org/cocos2dx/cpp/CaroSendFactory",
		"connect", "()V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
	}
#endif
}

void JNIUtils::sendRegister(const char * username, const char * password)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t,
		"org/cocos2dx/cpp/CaroSendFactory",
		"sendRegister", "(Ljava/lang/String;Ljava/lang/String;)V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID, t.env->NewStringUTF(username), t.env->NewStringUTF(password));
	}
#endif
}

void JNIUtils::loginToRegister()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t,
		"org/cocos2dx/cpp/CaroSendFactory",
		"loginToRegister", "()V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
	}
#endif
}

void JNIUtils::sendLogin(const char * username, const char * password, int type, const char * token)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t,
		"org/cocos2dx/cpp/CaroSendFactory",
		"sendLogin", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;I)V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID, t.env->NewStringUTF(username), t.env->NewStringUTF(password), t.env->NewStringUTF(token), type);
	}
#endif
}

string JNIUtils::getDeviceId()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t,
		"org/cocos2dx/cpp/AppActivity",
		"getDeviceId", "()Ljava/lang/String;"))
	{
		jstring s = (jstring) (t.env->CallStaticObjectMethod(t.classID, t.methodID));
		return JniHelper::jstring2string(s);
	}
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	return "abcfo7";
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return PlatformWrapper::getIMEI();
#endif
}

void JNIUtils::sendResponseDraw(int response)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t,
		"org/cocos2dx/cpp/CaroSendFactory",
		"sendResponseDraw", "(I)V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID, response);
	}
#endif
}

void JNIUtils::sendMove(int rowChose, int colChose, int toRow, int toCol)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t,
        "org/cocos2dx/cpp/CaroSendFactory",
        "sendMove", "(IIII)V"))
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, rowChose, colChose, toRow, toCol);
    }
#endif
}

void JNIUtils::sendGetConfig()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t,
		"org/cocos2dx/cpp/CaroSendFactory",
		"sendGetConfig", "()V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
	}
#endif
}


void JNIUtils::sendGetTop()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t,
		"org/cocos2dx/cpp/CaroSendFactory",
		"sendGetTop", "()V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
	}
#endif
}


void JNIUtils::sendReady()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t,
		"org/cocos2dx/cpp/CaroSendFactory",
		"sendReady", "()V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
	}
#endif
}


void JNIUtils::sendInstall()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t,
		"org/cocos2dx/cpp/CaroSendFactory",
		"sendInstall", "()V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
	}
#endif
}


void JNIUtils::sendLikePage()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t,
		"org/cocos2dx/cpp/CaroSendFactory",
		"sendLikePage", "()V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
	}
#endif
}


void JNIUtils::sendVoteApp()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t,
		"org/cocos2dx/cpp/CaroSendFactory",
		"sendVoteApp", "()V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
	}
#endif
}


void JNIUtils::sendGetAward()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t,
		"org/cocos2dx/cpp/CaroSendFactory",
		"sendGetAward", "()V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
	}
#endif
}


void JNIUtils::sendCreateRoom(int betId, const char* name, const char* pass)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t,
		"org/cocos2dx/cpp/CaroSendFactory",
		"sendCreateRoom", "(Ljava/lang/String;Ljava/lang/String;I)V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID,  t.env->NewStringUTF(name), t.env->NewStringUTF(pass), betId);
	}
#endif
}


void JNIUtils::sendJoinRoom(int id, const char* pass)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t,
		"org/cocos2dx/cpp/CaroSendFactory",
		"sendJoinRoom", "(Ljava/lang/String;I)V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID, t.env->NewStringUTF(pass), id);
	}
#endif
}


void JNIUtils::sendGetListRoom()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t,
		"org/cocos2dx/cpp/CaroSendFactory",
		"sendGetListRoom", "()V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
	}
#endif
}


void JNIUtils::sendAskLose()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t,
		"org/cocos2dx/cpp/CaroSendFactory",
		"sendAskLose", "()V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
	}
#endif
}


void JNIUtils::sendAskDraw()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t,
		"org/cocos2dx/cpp/CaroSendFactory",
		"sendAskDraw", "()V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
	}
#endif
}


void JNIUtils::sendLogout()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t,
		"org/cocos2dx/cpp/CaroSendFactory",
		"sendLogout", "()V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
	}
#endif
}


void JNIUtils::sendLeaveRoom()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t,
		"org/cocos2dx/cpp/CaroSendFactory",
		"sendLeaveRoom", "()V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
	}
#endif
}

void JNIUtils::sendQuickJoinRoom(int betId)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t,
		"org/cocos2dx/cpp/CaroSendFactory",
		"sendQuickJoinRoom", "(I)V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID, betId);
	}
#endif
}



void JNIUtils::sendMessage(const char* message, int type)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t,
		"org/cocos2dx/cpp/CaroSendFactory",
		"sendMessage", "(Ljava/lang/String;I)V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID, t.env->NewStringUTF(message), type);
	}
#endif
}



void JNIUtils::sendChangeUser(const char* name)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t,
		"org/cocos2dx/cpp/CaroSendFactory",
		"changeUser", "(Ljava/lang/String;)V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID, t.env->NewStringUTF(name));
	}
#endif
}

void JNIUtils::sendUpdateScore(int score)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t,
		"org/cocos2dx/cpp/CaroSendFactory",
		"sendUpdateScore", "(I)V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID, score);
	}
#endif
}

void JNIUtils::getAccesstoken()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t,
		"org/cocos2dx/cpp/AppActivity",
		"loginFacebook", "()V"))
	{
		(t.env->CallStaticVoidMethod(t.classID, t.methodID));
	}
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	
#endif
}


bool JNIUtils::checkInstallApp(const char * url)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t,
		"org/cocos2dx/cpp/AppActivity",
		"checkInstallApp", "(Ljava/lang/String;)I"))
	{
		jint s = t.env->CallStaticIntMethod(t.classID, t.methodID, t.env->NewStringUTF(url));
		return (s == 1 ? true : false);
	}
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	return true;
#endif
}


void JNIUtils::openUrl(const char * url) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t,
		"org/cocos2dx/cpp/AppActivity",
		"openUrl", "(Ljava/lang/String;)V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID, t.env->NewStringUTF(url));
	}
#endif
}


void JNIUtils::openApp(const char * url) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t,
		"org/cocos2dx/cpp/AppActivity",
		"openApp", "(Ljava/lang/String;)V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID, t.env->NewStringUTF(url));
	}
#endif
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		PlatformWrapper::openURL(url);
	#endif
}


void JNIUtils::sharePhoto(const char * url) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t,
		"org/cocos2dx/cpp/AppActivity",
		"sharePhoto", "(Ljava/lang/String;)V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID, t.env->NewStringUTF(url));
	}
#endif
}


void JNIUtils::showAdsFull()
{
	CCLOG("Show Ads Full --------------------------");
	game->timeNoAds = 0;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	PlatformWrapper::showInsertial();
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t,
		"org/cocos2dx/cpp/AppActivity",
		"showAdsFull", "()V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
}
#endif
}


void JNIUtils::loadAdsFull()
{

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//PlatformWrapper::showInsertial();
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t,
		"org/cocos2dx/cpp/AppActivity",
		"loadAdsFull", "()V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
	}
#endif
}


void JNIUtils::showRewardedAds()
{

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	PlatformWrapper::showReward();
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t,
		"org/cocos2dx/cpp/AppActivity",
		"showReward", "()V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
	}
#endif
}

void JNIUtils::sendEvent(const char* name, const char* data)
{

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	PlatformWrapper::sendEvent(name, data);
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t,
		"org/cocos2dx/cpp/AppActivity",
		"sendEvent", "(Ljava/lang/String;Ljava/lang/String;)V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID, t.env->NewStringUTF(name), t.env->NewStringUTF(data));
	}
#endif
}


void JNIUtils::sendGetAwardReward()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t,
		"org/cocos2dx/cpp/CaroSendFactory",
		"sendGetAwardReward", "()V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
	}
#endif
}


void JNIUtils::sendUpdateGold(int gold, int win, int lose)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t,
		"org/cocos2dx/cpp/CaroSendFactory",
		"sendUpdateGold", "(III)V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID, gold, win, lose);
	}
#endif
}

int JNIUtils::checkNetworkStatus()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t,
		"org/cocos2dx/cpp/AppActivity",
		"checkNetworkStatus", "()I"))
	{
		jint s = t.env->CallStaticIntMethod(t.classID, t.methodID);
		return s;
	}
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	return 0;
#endif
}


void JNIUtils::initAds(const char* app, const char* banner, const char* full, int idAdsBanner, int idAdsFull)
{

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	PlatformWrapper::initAds(idAdsBanner, idAdsFull);
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t,
		"org/cocos2dx/cpp/AppActivity",
		"initAds", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;II)V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID, t.env->NewStringUTF(app), t.env->NewStringUTF(banner), t.env->NewStringUTF(full), idAdsBanner, idAdsFull);
	}
#endif
}


void JNIUtils::loadOldPreferences() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t,
		"org/cocos2dx/cpp/AppActivity",
		"loadOldPreferences", "()V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
	}
#endif
}


string JNIUtils::getPackageApp()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t,
		"org/cocos2dx/cpp/AppActivity",
		"getPackageApp", "()Ljava/lang/String;"))
	{
		jstring s = (jstring)(t.env->CallStaticObjectMethod(t.classID, t.methodID));
		return JniHelper::jstring2string(s);
	}
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	return "com.classicgames.line98";
#endif
    return "com.classicgames.line98";
}


void JNIUtils::submitScore(int score, int type)
{

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//IOSConnection::showInsertial();
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t,
		"org/cocos2dx/cpp/AppActivity",
		"submitScore", "(II)V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID, score, type);
	}
#endif
}


void JNIUtils::crashlyticSetString(const char* key, const char* value)
{

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//IOSConnection::showInsertial();
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t,
		"org/cocos2dx/cpp/AppActivity",
		"setString", "(Ljava/lang/String;Ljava/lang/String;)V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID, t.env->NewStringUTF(key), t.env->NewStringUTF(value));
	}
#endif
}

void JNIUtils::showAdsBanner(int score)
{

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    PlatformWrapper::showAds(score == 1);
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t,
		"org/cocos2dx/cpp/AppActivity",
		"showAds", "(I)V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID, score);
	}
#endif
}

void JNIUtils::setRussia(int isRussia)
{

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//IOSConnection::showInsertial();
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t,
		"org/cocos2dx/cpp/AppActivity",
		"setRussia", "(I)V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID, isRussia);
	}
#endif
}

void JNIUtils::vibrate(int type)
{
	//if (!game->vibrate)
		//return;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	PlatformWrapper::vibrate(type);
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t,
		"org/cocos2dx/cpp/AppActivity",
		"vibrate", "(I)V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID, type);
	}
#endif
}

void JNIUtils::resetSmartFox()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t,
        "org/cocos2dx/cpp/CaroFactory",
        "resetSmartFox", "()V"))
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
    }
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    PlatformWrapper::resetSmartFox();
#endif
}

void JNIUtils::showFacebook()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JNIUtils::openUrl("fb://facewebmodal/f?href=https://www.facebook.com/gamecotuongonline");
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    PlatformWrapper::showFacebook();
#endif
}

void JNIUtils::notifyGetSupport()
{

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
   // PlatformWrapper::showInsertial();
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t,
        "org/cocos2dx/cpp/AppActivity",
        "notifyGetSupport", "()V"))
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
}
#endif
}

void JNIUtils::cancelNotifyGetSupport()
{

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
   // PlatformWrapper::showInsertial();
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t,
        "org/cocos2dx/cpp/AppActivity",
        "cancelNotifyGetSupport", "()V"))
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
}
#endif
}

void JNIUtils::sendGetBoardInfo()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t,
        "org/cocos2dx/cpp/CaroSendFactory",
        "sendGetBoardInfo", "()V"))
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
    }
#endif
}

void JNIUtils::sendGetAwardPlayGame()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t,
        "org/cocos2dx/cpp/CaroSendFactory",
        "sendGetAwardPlayGame", "()V"))
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
    }
#endif

}

bool JNIUtils::showChess() {
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
   return PlatformWrapper::showChess();
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t,
        "org/cocos2dx/cpp/AppActivity",
        "cancelNotifyGetSupport", "()V"))
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
}
#endif
    return true;
}


void JNIUtils::showTracking()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	PlatformWrapper::showTracking();
#endif
}


void JNIUtils::changeToPortrait()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	PlatformWrapper::changeToPortrait();
#endif
}

void JNIUtils::changeToLandscape()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	PlatformWrapper::changeToLandscape();
#endif
}

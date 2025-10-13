#include "TimeOutHandler.h"
#include "../../Engine/Utility/LocalizedString.h"
#include "../GUIManager.h"

#include "../Utility/JNIUtils.h"

int countTimeOut = -1;
bool TimeOutHandler::showWaiting = false;
TimeOutHandler::TimeOutHandler(void)
{
}


TimeOutHandler::~TimeOutHandler(void)
{
}


void okProcessFail() {
	
	//NetworkSendHandler::sendLogout();
	JNIUtils::resetSmartFox();
	
}


void TimeOutHandler::updateTimeOut()
{

	

}


void TimeOutHandler::resetCountTime()
{
	countTimeOut = -1;
}

void TimeOutHandler::updateCountTime()
{
	countTimeOut = 0;
}

void TimeOutHandler::showLayerWating()
{
	showWaiting = true;
}

#include "ClockCountDownLine.h"
#include "string"
#include <ctime>
#include <chrono>
#include "Game/Utility/GameUtility.h"
#include "Game/Utility/GameSound.h"
using namespace std::chrono;
#define NUMBER_RES "poker/start_"

ClockCountDownLine::ClockCountDownLine(void)
{
	Sprite* bgClock = Sprite::create("480_800/bgClock.png");
	addChild(bgClock);
//	CCSize size = CCDirector::sharedDirector()->getWinSize();

	/*arrayImage[0] = Sprite::create(getResource(0));
	addChild(arrayImage[0]);
	arrayImage[0]->setPositionX(-arrayImage[0]->getContentSize().width * 0.52);

	arrayImage[1] = Sprite::create(getResource(0));
	addChild(arrayImage[1]);
	arrayImage[1]->setPositionX(arrayImage[1]->getContentSize().width * 0.52);*/

	//arrayImage[0]->setPosition(size.width / 2, size.height / 2);
	//arrayImage[1]->setPosition(size.width / 2, size.height / 2);

	setVisible(true);
	pause = false;
	//setContentSize(CCSize(arrayImage[0]->getContentSize().width * 2.2f, arrayImage[0]->getContentSize().height));
	playTime = false;
	schedule(schedule_selector(ClockCountDownLine::update), 1);
	callback = nullptr;

	lbTime = Text::create("0", "fonts/tahomabd.ttf", 18);
	lbTime->setAnchorPoint(Vec2(0.5, 0.5));
	lbTime->enableOutline(ccc4(20, 20, 20, 255), 1);
	lbTime->setTextHorizontalAlignment(TextHAlignment::CENTER);
	addChild(lbTime);
	lbTime->setPositionY(5);
	//lbTime->setPosition(Vec2(bgProgress->getRealWidth() * 0.4, 0));
}

ClockCountDownLine::~ClockCountDownLine(void)
{
}

void ClockCountDownLine::onEnterFinish()
{
	schedule(schedule_selector(ClockCountDownLine::update), 1);
}

void ClockCountDownLine::setPlayTime(bool play)
{
	playTime = play;
}


void ClockCountDownLine::setCallback(const ClockListener& _callback)
{
	callback = _callback;
}

void ClockCountDownLine::callbackTimeOut()
{
	if (callback) {
		callback();
	}
}

std::string ClockCountDownLine::getResource(int number)
{
	std::string content = "poker/start_";
	content = content + std::to_string(number);
	content = content + ".png";
	return content;
}

void ClockCountDownLine::update(float delta)
{
	if (!isVisible())
		return;
	if(!pause) {
		milliseconds ms = duration_cast<milliseconds>(
			system_clock::now().time_since_epoch()
			);
		int remainTime = round((targetTime - ms.count()) / 1000);
		if(remainTime >= 0) {
			convertTime(remainTime);
			if(remainTime < 10) {
				//GameSound::playSoundCountDown();
				if (!arrayCountDown[remainTime]) {
					GameSound::playCountDown();
					arrayCountDown[remainTime] = true;
				}
			}
		}
		else {
			callbackTimeOut();
			setPause(true);
		}
	}
}

void ClockCountDownLine::setPause(bool value)
{
	setVisible(!value);
	pause = value;
}

void ClockCountDownLine::setTime(int time)
{
	milliseconds ms = duration_cast<milliseconds>(
		system_clock::now().time_since_epoch()
		);
	CCLOG("SET TIME %i ", time);
	targetTime = time * 1000 + ms.count();
	schedule(schedule_selector(ClockCountDownLine::update),1);
	convertTime(time);
	setPause(false);
	for (int i = 0; i < 10; i++) {
		arrayCountDown[i] = false;
	}
}

float ClockCountDownLine::getTime()
{
	if (pause)
		return -1;
	milliseconds ms = duration_cast<milliseconds>(
		system_clock::now().time_since_epoch()
		);
	float remainTime = round((targetTime - ms.count()) / 1000.0f);
	return remainTime;
}

void ClockCountDownLine::convertTime(int convertTime)
{
	if (convertTime < 0)
		convertTime = 0;
	lbTime->setString(GameUtility::toString(convertTime));
	lbTime->runAction(CCSequence::create(
		CCScaleTo::create(0.2, 1.2),
		CCEaseBounceOut::create(CCScaleTo::create(0.5, 1.0)),
		NULL
	));
}

ClockGameLine::ClockGameLine() : ClockCountDownLine()
{
	Sprite* bgClock = Sprite::create("poker/bgClock.png");
	addChild(bgClock);
//	bgClock->setPosition(bgClock->getContentSize().width * 0.5, bgClock->getContentSize().height * 0.5);
	arrayImage[0]->setLocalZOrder(1);
	arrayImage[1]->setLocalZOrder(1);
	setContentSize(bgClock->getContentSize());
	arrayImage[0]->setScale(0.8);
	arrayImage[1]->setScale(0.8);
}

ClockGameLine::~ClockGameLine()
{

}

std::string ClockGameLine::getResource(int number)
{
	std::string content = "poker/o";
	content = content + std::to_string(number);
	content = content + ".png";
	return content;
}

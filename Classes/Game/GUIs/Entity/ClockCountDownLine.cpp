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
	bgClock = Sprite::create("480_800/clock.png");
	addChild(bgClock);

	setVisible(true);
	pause = false;
	playTime = false;
	//	schedule(schedule_selector(ClockCountDownLine::update), 1);
	callback = nullptr;

	lbTime = Text::create("0", "fonts/tahomabd.ttf", 25);
	lbTime->setColor(Color3B(240, 129, 130));
	lbTime->setAnchorPoint(Vec2(0.5, 0.5));
	lbTime->enableOutline(Color4B(20, 20, 20, 255), 1);
	lbTime->setTextHorizontalAlignment(TextHAlignment::CENTER);
	bgClock->addChild(lbTime);
	lbTime->setPosition(Vec2(bgClock->getContentSize().width * 0.5, bgClock->getContentSize().height * 0.45));
	//lbTime->setPosition(Vec2(bgProgress->getRealWidth() * 0.4, 0));


}

ClockCountDownLine::~ClockCountDownLine(void)
{
}

void ClockCountDownLine::onEnterFinish()
{
	this->schedule(
		[this](float dt) {
		// Add your task logic here
		this->update(dt);
	},
		1.0f, "one_time_task_key");
}

void ClockCountDownLine::setPlayTime(bool play)
{
	playTime = play;
}

Size ClockCountDownLine::getContentSize()
{
	return bgClock->getContentSize();
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

bool ClockCountDownLine::isPause()
{
	return pause;
}

void ClockCountDownLine::update(float delta)
{
	/*if (!isVisible())
		return;*/
	if (!pause) {
		milliseconds ms = duration_cast<milliseconds>(
			system_clock::now().time_since_epoch()
			);
		targetTime = targetTime - delta;
		int remainTime = targetTime;
		//round((targetTime - ms.count()) / 1000);
		if (remainTime >= 0) {
			convertTime(remainTime);
			if (remainTime < 10) {
				//GameSound::playSoundCountDown();
				if (!arrayCountDown[remainTime]) {
					GameSound::playCountDown();
					arrayCountDown[remainTime] = true;
					bgClock->runAction(
						Spawn::create(
							Sequence::create(
								MoveTo::create(0.2, Vec2(0, 50)),
								EaseBounceOut::create(MoveTo::create(0.5, Vec2(0, 0))),
								NULL
							),
							Sequence::create(
								ScaleTo::create(0.2, 1, 1.2),
								ScaleTo::create(0.2, 1, 0.6),
								EaseBounceOut::create(ScaleTo::create(0.5, 1, 1)),
								NULL
							),
							NULL
						)
					);
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
	//setVisible(!value);
	pause = value;
}

void ClockCountDownLine::setTime(int time)
{
	milliseconds ms = duration_cast<milliseconds>(
		system_clock::now().time_since_epoch()
		);
	CCLOG("SET TIME %i ", time);
	targetTime = time;
	//targetTime = time * 1000 + ms.count();
	//schedule(schedule_selector(ClockCountDownLine::update),1);
	convertTime(time);
	setPause(false);
	for (int i = 0; i < 10; i++) {
		arrayCountDown[i] = false;
	}
}

float ClockCountDownLine::getTime()
{
	//if (pause)
		//return -1;
	return targetTime;
	/*milliseconds ms = duration_cast<milliseconds>(
		system_clock::now().time_since_epoch()
		);
	float remainTime = round((targetTime - ms.count()) / 1000.0f);
	return remainTime;*/
}

void ClockCountDownLine::convertTime(int convertTime)
{
	if (convertTime < 0)
		convertTime = 0;
	lbTime->setString(GameUtility::toString(convertTime));
	lbTime->runAction(Sequence::create(
		ScaleTo::create(0.2, 1.2),
		EaseBounceOut::create(ScaleTo::create(0.5, 1.0)),
		NULL
	));
}


std::string ClockCountDownLine::getResource(int number)
{
	return "";
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

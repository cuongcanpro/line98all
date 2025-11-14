#ifndef _ClockCountDownLine_h__
#define _ClockCountDownLine_h__

#include <cocos2d.h>
#include "ui/UIText.h"
using namespace cocos2d;
using namespace cocos2d::ui;
typedef std::function<void()> ClockListener;
class ClockCountDownLine : public Node
{
public:
	ClockCountDownLine(void);
	~ClockCountDownLine(void);
	void onEnterFinish();
	void update(float delta);
	void setPause(bool value);
	bool isPause();
	void setTime(int time);
	float getTime();
	void convertTime(int time);
	void setPlayTime(bool play);
	void setCallback(const ClockListener& _callback);
	virtual void callbackTimeOut();
	virtual std::string getResource(int number);
	ClockListener callback;
	Size getContentSize();
protected:
	Sprite* bgClock;
	Sprite *arrayImage[2];
	Text* lbTime;
	int standardTime;
	double targetTime;
	bool pause;
	float pad;
	bool playTime;
	bool arrayCountDown[10];
};

class ClockGameLine : public ClockCountDownLine
{
public:
    ClockGameLine();
	~ClockGameLine();
	std::string getResource(int number);
private:
};
#endif


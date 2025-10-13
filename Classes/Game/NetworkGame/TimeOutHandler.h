#pragma once
#ifndef TimeOutHandler_h__
#define TimeOutHandler_h__

extern int countTimeOut;

class TimeOutHandler
{
public:
	TimeOutHandler(void);
	~TimeOutHandler(void);
	static void updateTimeOut();
	static void resetCountTime();
	static void updateCountTime();

	static bool showWaiting;
	static void showLayerWating();
};
#endif // PingpongHandler_h__


#pragma once
#ifndef ConfigModel_h__
#define ConfigModel_h__
#include <vector>
#include "ExpModel.h"
#include "RoomModel.h"
#include "PlayerInfo.h"
#include "string"
#include "ChatModel.h"
using namespace std;
class ConfigModel
{
public:
	ConfigModel(void);
	~ConfigModel(void);
	int currentTop;
	vector<int> bet;
	vector<ExpModel> exp;
	vector<RoomModel> listRoom;
	vector<PlayerInfo> listTopScore;
	vector<PlayerInfo> listTopCount;
	vector<ChatModel> listMessage;
	static ConfigModel* config;
	static ConfigModel* getInstance();
    
	bool arraySortDown[3];
	int currentSort;
    void sortNum();
	void sortName();
	void sortBet();
    static string getNameExp(int exp);
    static int getLevel(int exp);
    
    
};
#endif // ConfigModel_h__


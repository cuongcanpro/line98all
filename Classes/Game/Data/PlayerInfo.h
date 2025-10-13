#pragma once
#ifndef PlayerInfo_h__
#define PlayerInfo_h__
#include <string>
using namespace std;
class PlayerInfo
{
public:
	PlayerInfo(void);
	~PlayerInfo(void);

	int gold;
	int win;
	int lose;
	int exp;
	int id;
	int playerId;
	string name;
	string avatar;
	bool liked;
	int count;
    int roomId;
    bool isRate;
};
#endif // PayerInfo_h__


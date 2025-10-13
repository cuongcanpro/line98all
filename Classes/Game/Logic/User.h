#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User
{
public:
	User(void)
	{
        displayName = "";
		avatar = "";
		userName = "";
		zMoney = 0;
		gold = 0;
		exp = 0;
		highestLevel = 0;
	}
	string avatar;
	string userName;
    string displayName;
	int id;
	int openId;
	long long zMoney;
	long long gold;
	long long exp;
	int numWin;
	int numDraw;
	int numLose;
	long lastTimeSupport;
	int highestLevel;

};
#endif  

#ifndef EnemyInfo_h__
#define EnemyInfo_h__

#include <string>

using namespace std;

class EnemyInfo
{
public:
	int uId;
	string avatarURL;
	string uName;
	long long bean;
	long long levelScore;
	int winCount;
	int lostCount;
	int nChair;
	int usingItem;
public:
	EnemyInfo(void) {}
	~EnemyInfo(void) {}
};

#endif // EnemyInfo_h__


#pragma once
#ifndef RoomModel_h__
#define RoomModel_h__
#include "string"

class RoomModel
{
public:
	RoomModel(void);
	~RoomModel(void);
	int id;
	std::string name;
	int numPlayer;
	int betId;
	bool hasPass;
};
#endif // RoomModel_h__


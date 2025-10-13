#pragma once
#include "string"
using namespace std;
class ChatModel
{
public:
	ChatModel(void);
	~ChatModel(void);

	string message;
	string name;
	bool isMy;
	string getMessage();
};


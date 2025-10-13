#include "ChatModel.h"


ChatModel::ChatModel(void)
{
}


ChatModel::~ChatModel(void)
{
}

std::string ChatModel::getMessage()
{
	return name + ": " + message;
}

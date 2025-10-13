#include "ConfigModel.h"
#include "Game/Utility/GameUtility.h"

ConfigModel *ConfigModel::config = NULL;

ConfigModel::ConfigModel(void)
{
	bet.push_back(100);
	bet.push_back(200);
	bet.push_back(300);
	bet.push_back(400);
	bet.push_back(500);

	for(int i = 0; i < 10; i++)
	{
		ChatModel chatModel;
		chatModel.name = "PlayerC";
		chatModel.isMy = (GameUtility::getRandom() > 0.5f ? true : false);
		chatModel.message = "khi nao can mua ao";
		listMessage.push_back(chatModel);
	}

	for(int i = 0; i < 10; i++)
	{
		PlayerInfo info;
		info.name = "PlayerC";
		info.exp = GameUtility::getRandom() * 200;
		info.count = GameUtility::getRandom() * 100;
		info.win = GameUtility::getRandom() * 100;
		info.lose = GameUtility::getRandom() * 100;
		listTopCount.push_back(info);
	}


	for(int i = 0; i < 10; i++)
	{
		PlayerInfo info;
		info.name = "PlayerC";
		info.exp = GameUtility::getRandom() * 200;
		info.count = GameUtility::getRandom() * 100;
		info.win = GameUtility::getRandom() * 100;
		info.lose = GameUtility::getRandom() * 100;
		listTopScore.push_back(info);
	}

	for(int i = 0; i < 10; i++)
	{
		RoomModel room;
		room.name = "Cao thu co tuong";
		room.numPlayer = GameUtility::getRandom() * 2 + 1;
		room.hasPass = GameUtility::getRandom() > 0.5f ? true : false;
		room.betId = GameUtility::getRandom() * 5;
		listRoom.push_back(room);
	}
    listRoom.clear();
	currentTop = 0; // top exp;

	for(int i = 0; i < 6; i++)
	{
		ExpModel expmodel;
		expmodel.begin = 0;
		expmodel.end = 100;

		exp.push_back(expmodel);
	}
	for(int i = 0; i < 3; i++)
		arraySortDown[i] = true;
}


ConfigModel::~ConfigModel(void)
{
}

ConfigModel* ConfigModel::getInstance()
{
	if(config == NULL)
	{
		config = new ConfigModel();
	}
	return config;
}

string ConfigModel::getNameExp(int exp){
    
    for(int i = 0; i < 6; i++)
    {
        if(ConfigModel::getInstance()->exp.at(i).end > exp || i == 6)
        {
            return ConfigModel::getInstance()->exp.at(i).name;
        }
    }
    return ConfigModel::getInstance()->exp.at(5).name;

}

int ConfigModel::getLevel(int exp){
    
    for(int i = 0; i < 6; i++)
    {
        if(ConfigModel::getInstance()->exp.at(i).end > exp || i == 6)
        {
            return i;
        }
    }
    return 5;
}

void ConfigModel::sortNum()
{
	currentSort = 2;
	arraySortDown[2] = !arraySortDown[2];
    //CCLog("SIZE %i ", listRoom.size());
    if(listRoom.size() == 0)
        return;
	if(arraySortDown[2])
	{
		//sap xep giam dan
		for(int i = 0; i < listRoom.size() - 1; i++)
		{
			for(int j = i+1; j < listRoom.size(); j++)
			{
				if(listRoom.at(i).numPlayer < listRoom.at(j).numPlayer)
				{
					swap(listRoom.at(i), listRoom.at(j));
				}
			}
		}

	}
	else
	{
		for(int i = 0; i < listRoom.size() - 1; i++)
		{
			for(int j = i+1; j < listRoom.size(); j++)
			{
				if(listRoom.at(i).numPlayer > listRoom.at(j).numPlayer)
				{
					swap(listRoom.at(i), listRoom.at(j));
				}
			}
		}
	}
}

void ConfigModel::sortName()
{
    
	currentSort = 0;
	arraySortDown[0] = !arraySortDown[0];
    if(listRoom.size() == 0)
        return;
	if(arraySortDown[0])
	{
		//sap xep giam dan
		for(int i = 0; i < listRoom.size() - 1; i++)
		{
			for(int j = i+1; j < listRoom.size(); j++)
			{
				if(listRoom.at(i).name.compare(listRoom.at(j).name) < 0)
				{
					swap(listRoom.at(i), listRoom.at(j));
				}
			}
		}
	
	}
	else
	{
		for(int i = 0; i < listRoom.size() - 1; i++)
		{
			for(int j = i+1; j < listRoom.size(); j++)
			{
				if(listRoom.at(i).name.compare(listRoom.at(j).name) > 0)
				{
					swap(listRoom.at(i), listRoom.at(j));
				}
			}
		}
	}
}

void ConfigModel::sortBet()
{
	currentSort = 1;
	arraySortDown[1] = !arraySortDown[1];
    if(listRoom.size() == 0)
        return;
	if(arraySortDown[1])
	{
		//sap xep giam dan
		for(int i = 0; i < listRoom.size() - 1; i++)
		{
			for(int j = i+1; j < listRoom.size(); j++)
			{
				if(listRoom.at(i).betId < listRoom.at(j).betId)
				{
					swap(listRoom.at(i), listRoom.at(j));
				}
			}
		}

	}
	else
	{
		for(int i = 0; i < listRoom.size() - 1; i++)
		{
			for(int j = i+1; j < listRoom.size(); j++)
			{
				if(listRoom.at(i).betId > listRoom.at(j).betId)
				{
					swap(listRoom.at(i), listRoom.at(j));
				}
			}
		}
	}
}


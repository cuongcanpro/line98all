#include "cocos2d.h"
#include "GameConfig.h"

USING_NS_CC;
using namespace std;

static bool _isFirstRun = true;
static const char* GAME_CONFIG = "config.csv";
GameConfig* GameConfig::shared()
{
	if (_isFirstRun)
	{
		_isFirstRun = false;
		_gameConfig = new GameConfig();
		_gameConfig->loadData();
	}
	return _gameConfig;
}

GameConfig* GameConfig::_gameConfig;
GameConfig::GameConfig(void)
{
}


GameConfig::~GameConfig(void)
{

}

void GameConfig::loadData()
{
	//load file config
// 	ACSVParser csvParser;
// 	// Set the header and data type rows.
// 	csvParser.SetHeaderRow(0);
// 	csvParser.SetTypeRow(1);       
// 	std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(GAME_CONFIG);
// 	CCAssert(csvParser.ParseFile(fullPath, ACSVParser::Slurp,false),"Khong load duoc screen config");
// 	//server
// 	string wstr = csvParser.GetContentForHeaderAt("serverIp",0).GetString();
// 	_serverIp.assign(wstr.begin(),wstr.end());
// 	_serverPort = csvParser.GetContentForHeaderAt("serverPort",0).GetInt();
// 	//version
// 	_version = csvParser.GetContentForHeaderAt("clientVersion",0).GetInt();
// 	//store
// 	_storeType = csvParser.GetContentForHeaderAt("storeType",0).GetInt();
// 	//encrypt Image
// 	_encryptImage = csvParser.GetContentForHeaderAt("encryptImage",0).GetInt()>0;
// 	//encrypt Common
// 	_encryptCommon = csvParser.GetContentForHeaderAt("encryptCommon",0).GetInt()>0;

}

std::string GameConfig::getServerIp()
{
	return _serverIp;
}

int GameConfig::getServerPort()
{
	return _serverPort;
}
bool GameConfig::hasNewVersion(int versionOnServer)
{
	return versionOnServer > _version;
}

void GameConfig::setLink( std::string linkDownload )
{
	_linkDownload = linkDownload;
}

std::string GameConfig::getLinkDownLoad()
{
	return _linkDownload;
}

int GameConfig::getStoreType()
{
	return _storeType;
}

bool GameConfig::isEncryptImage()
{
	return true;
	//return _encryptImage;
}

bool GameConfig::isEncryptCommon()
{
	return _encryptCommon;
}

void GameConfig::updateMoneyRubyCard( std::vector<std::string> _listRubyCard )
{
	_listMoneyToRubyCard.clear();
	for (int i = 0; i < _listRubyCard.size(); i++)
	{
		_listMoneyToRubyCard.push_back(_listRubyCard.at(i));
	}
}

std::vector<std::string> GameConfig::getListMoneyCardToRuby()
{
	return _listMoneyToRubyCard;
}

int GameConfig::getCurrentVersion()
{
	return _version;
}


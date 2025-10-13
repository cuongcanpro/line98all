#ifndef GameConfig_h__
#define GameConfig_h__
#include <string>
#include <vector>

class GameConfig
{
public:
	static GameConfig* shared();
private:
	static GameConfig* _gameConfig;
public:
	GameConfig(void);
	~GameConfig(void);
public:
	std::string getServerIp();
	int getServerPort();
	bool hasNewVersion(int versionOnServer);
	int getCurrentVersion();
	void setLink(std::string linkDownload);
	std::string getLinkDownLoad();
	int getStoreType();
	bool isEncryptImage();
	bool isEncryptCommon();
	void updateMoneyRubyCard(std::vector<std::string> _listRubyCard);
	std::vector<std::string> getListMoneyCardToRuby();
private:
	void loadData();
	std::string _serverIp;
	int _serverPort;
	int _version;
	std::string _linkDownload;
	int _storeType;
	bool _encryptImage;
	bool _encryptCommon;
	std::vector<std::string> _listMoneyToRubyCard;
};
#endif // GameConfig_h__


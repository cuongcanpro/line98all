#ifndef JNIUtils_h
#define JNIUtils_h

#include <string>
using namespace std;
class JNIUtils
{
public:
	static void showAdsFull();
	static void loadAdsFull();
	static void openUrl(const char * url);
	static bool checkInstallApp(const char* url);
	static bool isConnected();
	static void connect();
	static void sendRegister(const char* username, const char* password);
	static void loginToRegister();
	static void sendLogin(const char* username, const char* password, int type, const char* token);
	
	static void sendResponseDraw(int response);
    static void sendMove(int rowChose, int colChose, int toRow, int toCol);
	static void sendGetConfig();
	static void sendGetTop();
	static void sendReady();
	static void sendInstall();
	static void sendLikePage();
	static void sendVoteApp();
	static void sendGetAward();
	static void sendCreateRoom(int betId, const char* name, const char* pass);
	static void sendJoinRoom(int id, const char* pass);
	static void sendGetListRoom();
	static void sendLeaveRoom();
	static void sendAskLose();
	static void sendAskDraw();
	static void sendLogout();
	static void sendQuickJoinRoom(int betId);
	static void sendMessage(const char* message, int type);
	static void sendChangeUser(const char* name);

	static void sendUpdateScore(int score);

	static void loadOldPreferences();
	static string getDeviceId();
	static void getAccesstoken();
	static void openApp(const char* packageApp);
	static void sharePhoto(const char* sharePhoto);
	static void initAds(const char* app, const char* banner, const char* full, int idAdsBanner, int idAdsFull);
	static string getPackageApp();
	static void submitScore(int score, int type);
	static void crashlyticSetString(const char* key, const char* value);
	static void showRewardedAds();
	static void sendEvent(const char* name, const char* data);
	static void sendGetAwardReward();
   
    static void sendGetAwardPlayGame();
	static void sendUpdateGold(int gold, int win, int lose);
	static int checkNetworkStatus();
	static void resetSmartFox();
	static void showAdsBanner(int show);
	static void setRussia(int isRussia);
	static void vibrate(int type);
    
    static void sendGetBoardInfo();
    //static void resetSmartFox();
    static void showFacebook();
    static void notifyGetSupport();
    static void cancelNotifyGetSupport();
    static bool showChess();
	static void showTracking();
	static void changeToLandscape();
	static void changeToPortrait();
};
#endif


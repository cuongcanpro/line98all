#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H
#define GUI_LOGIN 2
#include "GUIs/GUILoadingGame.h"
#include "GUIs/GUIDialog.h"
#include "GUIs/GUILine.h"
#include "GUIs/GUIHelp.h"
#include "GUIs/GUISetting.h"
#include "GUIs/GUISave.h"
#include "GUIs/GUIResult.h"
#include "GUIs/GUILanguage.h"
#include "GUIBlock/GUIGame.h"
#include "GUIBlock/GUIHelpBlock.h"
#include "GUITwenty/GUIGameTwenty.h"
#include "GUIEgg/GUIEgg.h"
#include "GUIBubble/GUIBubble.h"
#include "GUIs/GUIMerge.h"
#include "GUIs/GUIPop.h"
#include "GUIs/GUIBomb.h"
#include "GUIs/GUIMenuBomb.h"
#include "GUIs/GUIMinigames.h"

#include "GUIs/GUIWaiting.h"
#include "GUIs/GUIDialog.h"
#include "GUIs/GUILoadingAds.h"
#include "GUIs/GUIPikachu.h"
#include "GUIBrick/GUIBrick.h"
#include "GUIEgg/GUILevelEgg.h"
#include "GUIEgg/GUIChoose.h"
#include "GUIs/GUITopEgg.h"
#include "GUIs/GUIChangeNameEgg.h"

#include "GUISudoku/GUIMenuSudoku.h"
#include "GUISudoku/GUISudoku.h"
#include "GUI2048/GUI2048.h"

using namespace std;
class GUIManager 
{
public:
	GUIManager(void);
	~GUIManager(void);
	void update();
	static GUIManager& getInstance();

	//guis
	GUILoadingGame guiLoadingGame;
	GUIDialog guiDialog;
	GUILine guiLine;
	
	GUIHelp guiHelp;
	GUISetting guiSetting;
	GUISave guiSave;
	GUIResult guiResult;
	GUILanguage guiLanguage;
	GUIGame guiGame;
	GUIHelpBlock guiHelpBlock;
	GUIGameTwenty guiTwenty;
	GUIEgg guiEgg;
	GUIBubble guiBubble;
	GUIMerge guiMerge;
	GUIPop guiPop;
	GUIBomb guiBomb;
	GUIMenuBomb guiMenuBomb;
	GUIMinigames guiMinigames;
	GUIPikachu guiPikachu;
	GUIBrick guiBrick;

	GUIWaiting guiWaiting;
	GUILevelEgg guiLevelEgg;
	GUIChoose guiChoose;
	GUITopEgg guiTopEgg;
    GUIChangeNameEgg guiChangeNameEgg;

    GUILoadingAds guiLoadingAds;

	GUIMenuSudoku guiMenuSudoku;
	GUISudoku guiSudoku;
	GUI2048 gui2048;

	/*guidialog guidialog;
    guiline guiline;
    guiloadinggame guiloadinggame;
    guilobby guilobby;*/
	bool isCallBackPress;
	std::vector <BaseGUI*> *GUIList;
	void addToListGui(BaseGUI* gui);
	void removeFromListGui();
	void showGui(BaseGUI* gui, CCNode *parent = NULL, bool fog = true);
	void removeAllGui();
	BaseGUI* getLastGui();
	void setVisibleWaiting(bool visible);
};
#endif

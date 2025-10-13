
#ifndef GUIRemoveApp_h__
#define GUIRemoveApp_h__
#include "Engine/GUI/BaseGUI.h"

using namespace std;
using namespace cocos2d::extension;

class GUIRemoveApp : public BaseGUI
{
public:
	GUIRemoveApp(void);
	~GUIRemoveApp(void);
public:
	ui::Scale9Sprite *bg;
	void initGUI();
	void showGUI(CCNode* parent = NULL, bool hasFog = true);
	static std::string className;
	void onBackKey();
};
#endif // GUIRemoveApp_h__


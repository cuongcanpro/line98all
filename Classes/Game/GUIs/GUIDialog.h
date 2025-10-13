#ifndef GUI_DIALOG_H
#define GUI_DIALOG_H

#include "../../Engine/GUI/BaseGUI.h"
#include "ui/UIText.h"
using namespace cocos2d::ui;
class GUIDialog : public BaseGUI
{
private:
	Label* labelMessage;
	void (*okFunction)();
	void (*cancelFunction)();
	BaseButton* btnOk;
	BaseButton* btnCancel;
	CCNode* groupAll;

	
public:
	void initGUI();
	void onButtonRelease(int buttonId, CCTouch* event);
	void showGUI(const char* message, void (*okFunction)() = NULL, bool onlyOk = false, void (*cancelFunction)() = NULL, const char* sourceOk = NULL, const char* sourceCancel = NULL);
	void onHideGUI();
};
#endif
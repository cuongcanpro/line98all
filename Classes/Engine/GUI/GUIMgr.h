#ifndef _GUI_MGR_H_
#define _GUI_MGR_H_
#include "cocos2d.h"
#include "BaseGUI.h"

using namespace cocos2d;

class GUIMgr
{
private:
	CCLayerColor* fog;
	void creatFog();
	std::map<int, BaseGUI*> GUIList;

public:
	GUIMgr(void);
	~GUIMgr(void);
public:
	void showFog();
	void hideFog();

public:
	void onUpdate(float delta);
	//static CCRenderTexture* creatStroke(CCSprite* sprite,int size,ccColor3B color, GLubyte opacity);
	void hideAll();
	void clean();

public:
	void addGUI(int guiID, BaseGUI* gui);
	void addGUI(int guiID, BaseGUI* gui, int LayerID);
	BaseGUI* getGUI(int guiID);
};
#endif
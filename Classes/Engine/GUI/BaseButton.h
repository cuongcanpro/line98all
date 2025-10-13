#ifndef BaseButton_h__
#define BaseButton_h__

#include "GameImage.h"
#include <vector>
#include "LabelBM.h"
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class BaseBehavior;
class BaseGUI;
class BaseButton
{

// Data
public:
	GameImage* normalImage;
	LabelBM* _label;
	int buttonID;
	string idObjet;
	CCRect touchArea;
	// Only avalaible in buttons using touchArea
	CCNode* parent;
	CCPoint	touchPosition;

	// Buttons Behavior list
	vector<BaseBehavior*> behaviorList;
	bool canTouch;
	bool canMove;
	bool canTouchOut;
	BaseGUI* baseGui;
public:
	BaseButton(void);
	BaseButton(int buttonID, GameImage* image);
	BaseButton(int buttonID, CCRect touchArea, CCNode* parent);
	~BaseButton(void);
	void setEnable(bool enable=true);
	void setDisable();
	void setText(const char* text, FontType fontType = FONT_SMALL_OUTLINE_TYPE, CCPoint point = ccp(0,0));
	void addIcon(GameImage* icon, CCPoint pos);
	void setPosText(float x,float y);

public:
	bool containsTouchLocation(CCTouch* touch);
	void setPosition(float x, float y);
	CCPoint getPosition();
	float getPositionX();
	float getPositionY();
	float getWidth();
	float getHeight();
	void updatePosOfBehavior();

	// Add a behavior to the list
	void addBehavior(BaseBehavior* behavior);
	bool hasBehavior(int idBehavior);

	void setVisible(bool visible,bool visibleBehavior);
	void setVisible(bool visible);
	bool getVisible();
	bool isEnable();
	BaseBehavior* getBehavior(int id);
	void clear();
	void setParent(BaseGUI* baseGui);
public:
	virtual void onTouched();
	virtual void onReleased();
private:
	BaseGUI* _baseGui;
};

#endif // BaseButton_h__

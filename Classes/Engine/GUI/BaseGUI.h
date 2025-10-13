#ifndef BaseGUI_h__
#define BaseGUI_h__

#include "cocos2d.h"
//#include "Gui/Image.h"

#include <map>
//#include "RenderingSurface.h"
#include "BaseButton.h"
//#include "LabelBM.h"
#include "../Layers/GameLayer.h"
#include "cocos-ext.h"
#include "BubbleBehavior.h"
#include "ui/UIText.h"
using namespace cocos2d;
using namespace cocos2d::ui;
using namespace std;

class BaseGUI : public CCLayer
{
protected:
	// Rendering Unit (CCLayer)
//	RenderingSurface* RenderLayer;
	bool _hasFog;
	bool isTouchFog;
	GameImage* bgGui;
	CCLayerColor* fog;
	bool _isShown;

	// Check to init this GUI once
	bool isInit;

	vector<GameImage*> listImage;
	vector<LabelBM*> listLabel;
	CCNode* parent;
public:
	map<int, BaseButton*> buttonList;
	bool isShown();
protected:



	// Current touched button
	// TODO: replace for multitouches on multiple buttons
	BaseButton *touchedButton;

public:
	BaseGUI(void);
	~BaseGUI(void);

	void initWithParent(CCLayer* layer);
	void initWithParent(int LayerID);
	void addToLayer(int LayerID);
	void addToLayer(GameLayer* layer);
	void setFog(bool fog);
	bool hasFog();
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	//void keyBackClicked();
	virtual void onBackKey();
	virtual void showGUI(CCNode* parent = NULL, bool hasFog = true);
	void hideGUI();
	void onHideGUI();
	bool isInitted();
	int lastGUI;

public:
	BaseButton* addButton(int buttonID, GameImage* buttonImage, CCNode* parent = NULL);
	BaseButton* addButton(int buttonID, const char *pszFilename, BaseBehavior* behavior = new BubbleBehavior(), CCNode* parent = NULL, bool isFrame = NULL);
	BaseButton* addButton(int buttonID, CCRect touchArea);
	void addButton(BaseButton* btn,int id, CCNode* parent = NULL);

	BaseButton* getButton(int buttonID);
	void initRenderSurface();
	
	GameImage* addImage(const char* nameImg, float x = 0, float y = 0, int imageId = 0, bool frame = false);
	GameImage* addImageToNode(const char* nameImg, CCNode* parent = NULL, float x = 0, float y = 0, int imageId = 0, bool frame = false);
	void addImage(GameImage *image, int imageId = 0);
	Text* addText(string text, Node* parent = NULL);
	GameImage* getImage(int imageId);
	virtual void	setVisible(bool visible);

	virtual void setPos(float x, float y);
	CCPoint getPos();
// Event Handlers
public:
	void onEnter();
	void onExit();

// Inherit events
public:
	// Call backs for input events
	virtual bool onTouchBegan(CCTouch*touch, CCEvent* event);
	virtual void onTouchMoved(CCTouch*touch, CCEvent* event);
	virtual void onTouchEnded(CCTouch*touch, CCEvent* event);

	// Call backs to execute button behaviors

	void runTouchBehavior(CCTouch*touch, BaseButton* touchButton);
	void runDragBehavior(CCTouch*touch, BaseButton* dragButton);
	void runReleaseBehavior(CCTouch*touch, BaseButton* releaseButton);
	void runCancelBehavior( BaseButton* touchButton);

	// Call backs to derived button behaviors execution
	virtual void executeTouchBehavior(BaseBehavior* behavior, CCTouch* touch, BaseButton* touchButton);
	virtual void executeDragBehavior(BaseBehavior* behavior, CCTouch* touch, BaseButton* dragButton);
	virtual void executeReleaseBehavior(BaseBehavior* behavior, CCTouch* touch, BaseButton* releaseButton);
	virtual void executeCancelBehavior(BaseBehavior* behavior,BaseButton* touchButton);

	// Call backs to derived logic execution
	virtual void onButtonTouched(int ButtonID, CCTouch* touch);
	virtual void onButtonDrag(int buttonID, CCTouch* touch);
	virtual void onButtonRelease(int buttonID, CCTouch* touch);
	virtual void onButtonAction(int buttonID, int index);
	
	// Call backs to GUIs initialisation
	virtual void initGUI();
	virtual void disableGUI();
	virtual void enableGUI();

	CCAction* runAction(CCAction* action);


	void removeImage(int idImage);
	void removeImage(GameImage* image);
	void removeLabelBM(int idLabel);
	void removeButton(int idButton);

	LabelBM* addLabelBM(int idLabel,string text,FontType typeFont, Color3B color = Color3B::WHITE,float widthText=0);
	LabelBM* addLabelBM(string text, int align = 0, int idLabel = 0, FontType typeFont = FONT_NORMAL_TYPE, Color3B color = Color3B::WHITE,float widthText=0);
	LabelBM* getLabelBM(int idLabel);
	BaseButton* getTouchedButton();
	void moveHorizontal(Node* btn, float sX, float dX, float delay);
	void moveVertical(Node* btn, float sY, float dY, float delay);

public:
	virtual void show();
	virtual void hide();
public:
	virtual void onTouchFirstBegan(CCTouch*touch, CCEvent* event);
	virtual void onUpdate(float delta);
	void addToListButton(BaseButton *btn, int id);
    void moveElement(CCNode* btn, float dx, float dy, float delay);
};

#endif // BaseGUI_h__

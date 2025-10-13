#include "GUIRemoveApp.h"

#include "Engine/GlobalVar.h"
#include "../GUIManager.h"
#include "../Utility/Toast.h"
#include "../Utility/JNIUtils.h"

#define BTN_OK 11

GUIRemoveApp::GUIRemoveApp(void) : BaseGUI()
{
	BaseGUI();
	//setKeypadEnabled(true);
}

GUIRemoveApp::~GUIRemoveApp(void)
{

}

void GUIRemoveApp::initGUI(){
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();

	//bg = ui::Scale9Sprite::create("Board/table/top/bgTop1.png"); bgDialog
		bg = ui::Scale9Sprite::create("480_800/bgDialog.png"); 
	bg->setContentSize(CCSize(size.width * 0.9, 370));
	bg->setPosition(size.width * 0.5f, size.height * 0.52f);
	addChild(bg, 10);

	Text* labelStt = Text::create(CCLocalizedString("RESTORE_DATA_HELP").c_str(), "fonts/tahomabd.ttf", 22);
	labelStt->setColor(ccc3(250, 250, 250));
	labelStt->setTextHorizontalAlignment(TextHAlignment::CENTER);
	bg->addChild(labelStt);
	labelStt->setTag(2);
	labelStt->setAnchorPoint(ccp(0.5, 0.5f));
	labelStt->setPosition(ccp(bg->getContentSize().width * 0.5, bg->getContentSize().height * 0.3));
	labelStt->setTextAreaSize(Size(bg->getContentSize().width * 0.9, 200));

	Sprite* iconLine = Sprite::create("iconLineOld.png");
	bg->addChild(iconLine);
	iconLine->setPosition(bg->getContentSize().width * 0.5, bg->getContentSize().height * 0.8);

	string resource = "btnOk.png";
	Button* btnOk = Button::create(resource, resource, resource, Widget::TextureResType::PLIST);
	btnOk->setPosition(ccp(bg->getContentSize().width * 0.5 - 100, bg->getContentSize().height * 0.15));
	bg->addChild(btnOk);

	btnOk->addClickEventListener([this](Ref*) {
		//onBackKey();
		if (JNIUtils::checkInstallApp("com.bcsofts.colorLinesReborn"))
			JNIUtils::openUrl("https://news.beansofts.com/Line98Restore.apk");
		else
			JNIUtils::openUrl("https://news.beansofts.com/Lines98Restore.apk");
		game->endGame();
	});

	string resource1 = "btnCancel.png";
	Button* btnCancel = Button::create(resource1, resource1, resource1, Widget::TextureResType::PLIST);
	btnCancel->setPosition(ccp(bg->getContentSize().width * 0.5 + 100, bg->getContentSize().height * 0.15));
	bg->addChild(btnCancel);

	btnCancel->addClickEventListener([this](Ref*) {
		onBackKey();
	});

}

void GUIRemoveApp::showGUI(CCNode* parent /*= NULL*/, bool hasFog /*= true*/)
{
	BaseGUI::showGUI(parent, hasFog);
}

std::string GUIRemoveApp::className = "GUIRemoveApp";

void GUIRemoveApp::onBackKey()
{
	GUIManager::getInstance().removeFromListGui();
}




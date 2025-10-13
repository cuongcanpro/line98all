#include "GUIChangeNameEgg.h"
#include "Engine/GlobalVar.h"
#include "../GUIManager.h"
#include "../Utility/Toast.h"

#define BTN_OK 11

GUIChangeNameEgg::GUIChangeNameEgg(void) : BaseGUI()
{
	BaseGUI();
	//setKeypadEnabled(true);
}

GUIChangeNameEgg::~GUIChangeNameEgg(void)
{

}

void GUIChangeNameEgg::initGUI(){
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();

	bg = ui::Scale9Sprite::create("Board/table/top/bgTop1.png");
	bg->setContentSize(CCSize(400, 250));
	bg->setPosition(size.width * 0.5f, size.height * 0.52f);
	addChild(bg, 10);

	Text* labelStt = Text::create(CCLocalizedString("INPUT_NAME").c_str(), "fonts/tahomabd.ttf", 22);
	labelStt->setColor(ccc3(250, 250, 250));
	labelStt->setTextHorizontalAlignment(TextHAlignment::CENTER);
	bg->addChild(labelStt);
	labelStt->setTag(2);
	labelStt->setAnchorPoint(ccp(0.5, 0.5f));
	labelStt->setPosition(ccp(bg->getContentSize().width * 0.5, bg->getContentSize().height * 0.8));

	float heightInput = 40;
	nameBox = ui::EditBox::create(CCSizeMake(0.7f * bg->getContentSize().width ,heightInput), ui::Scale9Sprite::create("Board/table/bgSubResult.png"));
	bg->addChild(nameBox);
	nameBox->setPosition(ccp(bg->getContentSize().width * 0.5f, bg->getContentSize().height * 0.5));
	nameBox->setFontColor(Color3B::WHITE);
	nameBox->setPlaceHolder("Name Player");
	//nameBox->setPlaceholderFontSize(1);
	nameBox->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	nameBox->setInputMode(ui::EditBox::InputMode::SINGLE_LINE);
	nameBox->setInputFlag(ui::EditBox::InputFlag::SENSITIVE);
	nameBox->setPlaceholderFontSize(25);
	nameBox->setFontSize(25);

	string resource = "480_800/btnOk.png";
	Button* btnOk = Button::create(resource, resource, resource);
	btnOk->setPosition(ccp(bg->getContentSize().width * 0.5, bg->getContentSize().height * 0.15));
	bg->addChild(btnOk);

	btnOk->addClickEventListener([this](Ref*) {
		string s = nameBox->getText();
		if (s.compare("") == 0) {
			Toast::makeToast(2.0, CCLocalizedString("NEED_INPUT_NAME").c_str());
			return;
		}
		game->namePlayer = s;
		game->waitCreateName = true;
		int score = 0;
		switch (currentTop)
		{
		case TOP_NORMAL:
			score = game->scoreEndless;
			break;
		case TOP_TIME:
			score = game->scoreTime;
			break;
		case TOP_DROP:
			score = CCUserDefault::sharedUserDefault()->getIntegerForKey("highscoreMerge", 0);
			break;
		case TOP_TWENTY:
		//	score = game->highscoreSum;
			break;
		case TOP_LINE:
			//score = game->highscoreLine;
			break;
		default:
			break;
		}
		game->insertTop(currentTop, game->namePlayer, to_string(score));
		if (currentTop != TOP_NORMAL)
			game->insertTop(TOP_NORMAL, game->namePlayer, to_string(game->scoreEndless));
		onBackKey();
	});

	resource = "Board/table/btnClose.png";
	Button* btnClose = Button::create(resource, resource, resource);
	btnClose->setPosition(ccp(bg->getContentSize().width * 0.95, bg->getContentSize().height * 0.95));
	bg->addChild(btnClose);

	btnClose->addClickEventListener([this](Ref*) {
		onBackKey();
	});
}

void GUIChangeNameEgg::showGUI(CCNode* parent /*= NULL*/, bool hasFog /*= true*/)
{
	BaseGUI::showGUI(parent, hasFog);
}

std::string GUIChangeNameEgg::className = "GUIChangeNameEgg";

void GUIChangeNameEgg::onBackKey()
{
	GUIManager::getInstance().removeFromListGui();
}




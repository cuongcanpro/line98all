#include "GroupNumber.h"
#include <cmath>  
#include <string>
#include "../../Utility/GameUtility.h"


GroupNumber::GroupNumber(void)
{
	ball = new GameImage("1.png");
	addChild(ball);
	setContentSize(ball->getImg()->getContentSize());

	label = LabelBM::create("SCORE: 0", FONT_BOLD_TYPE);
	label->setAnchorPoint(ccp(0.5, 0.75));
	addChild(label);

	ball->setLocalZOrder(2);
	label->setLocalZOrder(2);

	setNumber(0);

	setCascadeColorEnabled(true);
	setCascadeOpacityEnabled(true);
}

void GroupNumber::setNumber(int number)
{
	this->number = number;
	label->setText(GameUtility::toString(number).c_str());
	string s = "480_800/" + GameUtility::toString(number % 25) + ".png";
	ball->getImg()->setTexture(s.c_str());
}


void GroupNumber::increaseNumber()
{
	number = number + 1;

	for (int i = 0; i < 3; i++) {
		GameImage *ball = new GameImage("bgNumber.png");
		addChild(ball);
		ball->setColor(this->ball->getImg()->getColor());
		ball->getImg()->setVisible(false);
		ball->runAction(
			CCSequence::create(
				CCDelayTime::create(0.1 * i),
				CCShow::create(),
				CCSpawn::create(
					CCScaleTo::create(0.5, 10),
					CCFadeOut::create(0.5),
					NULL
				),
				CCRemoveSelf::create(),
				NULL
			)
		);
	}

	runAction(
		CCSequence::create(
			CCDelayTime::create(0.2),
			CCCallFunc::create(this, callfunc_selector(GroupNumber::callback1)),
			NULL
		)
	);
}

void GroupNumber::callback1()
{
	label->runAction(
		CCSequence::create(
			CCEaseBackIn::create(CCScaleTo::create(0.4, 0)),
			CCCallFunc::create(this, callfunc_selector(GroupNumber::callback2)),
			NULL
		)
	);
}

void GroupNumber::callback2()
{
	setNumber(number);
	label->runAction(
		CCSequence::create(
			CCEaseBounceOut::create(CCScaleTo::create(0.5, 1)),
			//CCCallFunc::create(this, callfunc_selector(Number::effectEndGame)),
			NULL
		)
	);
}

GroupNumber::~GroupNumber(void)
{
}

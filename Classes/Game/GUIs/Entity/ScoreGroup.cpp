#include "ScoreGroup.h"
#include <cmath>  
#include "Engine/GUI/GameImage.h"
#include "Engine/Utility/Utility.h"
#include "Engine/Utility/CStringUtils.h"
#include <string>
#include "../../Utility/GameUtility.h"


ScoreGroup::ScoreGroup(void)
{
}

ScoreGroup::ScoreGroup(long money, int max): CCNode()
{
	this->max = max;
	setMoney(money);
	
}

void ScoreGroup::setMoney(double money)
{
	removeAllChildren();

	float width  = 0;
	float pad = 0;
	float height = 0;
	float centerHeight = 0;

	
		
		money = abs(money);
		Utility utility;
		std::string moneyString = GameUtility::standartNum(money, max);

		const char * arrayChar = moneyString.c_str();
		int size = strlen(moneyString.c_str());
		int i;

		for(i = 0; i<size; i++)
		{

			string s = "digits_";
			s = s + moneyString.at(i) + ".png";
		
				GameImage *image = new GameImage(s.c_str(), true);
				this->addChild(image);
				if(pad == 0)
					pad = image->getWidth() * 0.1f;
				image->setPosition(width + pad+ image->getWidth() / 2, image->getHeight() * 0.6f);
				width = width + image->getWidth() + pad;
				height = image->getHeight();

		}
	
	setContentSize(CCSizeMake(width, height));
}


ScoreGroup::~ScoreGroup(void)
{
}

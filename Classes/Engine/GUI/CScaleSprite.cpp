#include "CScaleSprite.h"
#include <string>
#include "../Utility/Utility.h"
#include "../GlobalVar.h"


// CScaleSprite* CScaleSprite::create()
// {
// 	CScaleSprite *pSprite = new CScaleSprite();
// 	if (pSprite && pSprite->init())
// 	{
// 		pSprite->autorelease();
// 		return pSprite;
// 	}
// 	CC_SAFE_DELETE(pSprite);
// 	return NULL;
// }
CScaleSprite* CScaleSprite::create(const char *pszFileName, bool frame){
	
	CScaleSprite *pobSprite = new CScaleSprite();
	string path = ScreenUtils::fileFull(pszFileName);
	//CCTexture2D* pTexture = utility->createTexture(ScreenUtils::fileFull(pszFileName).c_str());
	//if (pobSprite && pTexture && pobSprite->initWithTexture(pTexture))
	//{
	//	pobSprite->autorelease();
	//	//pobSprite->setScale(1);
	//	return pobSprite;
	//}

	//if (pobSprite && pobSprite->initWithSpriteFrameName(pszFileName))
	//{
	//	pobSprite->autorelease();
	//	//pobSprite->setScale(1);
	//	return pobSprite;
	//}
	if(!frame)
	{
		if (pobSprite && pobSprite->initWithFile(ScreenUtils::fileFull(pszFileName).c_str()))
		{
			pobSprite->autorelease();
			//pobSprite->setScale(1);
			//pobSprite->updateSize();
			return pobSprite;
		}
	}
	else
	{
		if (pobSprite && pobSprite->initWithSpriteFrameName(pszFileName))
		{
			pobSprite->autorelease();
			//pobSprite->setScale(1);
			return pobSprite;
		}
	}

	/*if (pobSprite && pobSprite->initWithFile(ScreenUtils::fileFull(pszFileName).c_str()))
	{
		pobSprite->autorelease();
		pobSprite->setScale(1);
		pobSprite->updateSize();
		return pobSprite;
	}
	*/
	std::string s;
	s="khong co anh?";
	s+=pszFileName;
	//CCMessageBox(s.c_str(),"Thong bao");

	CCAssert(false, "cant create CScaleSprite");
	CC_SAFE_DELETE(pobSprite);
	return NULL;
};
float CScaleSprite::getWidth(){
	return this->getContentSize().width;//* ScreenUtils::imageScale();
}
float CScaleSprite::getHeight(){
	return this->getContentSize().height;//* ScreenUtils::imageScale();
}
void CScaleSprite::setScale(float scale){
	CCSprite::setScale(scale);// * ScreenUtils::imageScale());
}
void CScaleSprite::setScaleX(float scale){
	CCSprite::setScaleX(scale);// * ScreenUtils::imageScale());
}
void CScaleSprite::setScaleY(float scale){
	CCSprite::setScaleY(scale);// * ScreenUtils::imageScale());
}
float CScaleSprite::getScaleX(){
	return CCSprite::getScaleX();///ScreenUtils::imageScale();
}
float CScaleSprite::getScaleY(){
	return CCSprite::getScaleY();///ScreenUtils::imageScale();
}
float CScaleSprite::getScale(){
	return CCSprite::getScale();///ScreenUtils::imageScale();
}
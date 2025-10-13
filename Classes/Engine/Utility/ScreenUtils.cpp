#include "ScreenUtils.h"
#include "GameConfig.h"
//namespace
static bool s_bFirstRun = true;
static ScreenUtils* s_shareScale;
static const char* SCREEN_CONFIG = "screen.csv";
CCSize defauleSpriteSize = CCSizeMake(1,1);
ScreenUtils* ScreenUtils::share(){
	if (s_bFirstRun)
	{
		s_shareScale = new ScreenUtils();
		s_shareScale->init();
		s_bFirstRun = false;
	}
	return s_shareScale;
}
bool ScreenUtils::init(){
	//load file config
// 	ACSVParser csvParser;
// 	// Set the header and data type rows.
// 	csvParser.SetHeaderRow(0);
// 	csvParser.SetTypeRow(1);       
// 	std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(SCREEN_CONFIG);
// 	CCAssert(csvParser.ParseFile(fullPath, ACSVParser::Slurp,false),"Khong load duoc screen config");
// 
// 
// 
// 	selectScale = csvParser.GetContentForHeaderAt("selectScale",0).GetFloat();
// 	limitZoom = csvParser.GetContentForHeaderAt("limitZoom",0).GetFloat();
// 	float wScr,hScr;
// 	wScr = csvParser.GetContentForHeaderAt("defaultWidth",0).GetFloat();
// 	hScr = csvParser.GetContentForHeaderAt("defaultHeight",0).GetFloat();
// 	defauleSpriteSize =  CCSizeMake(wScr,hScr);
// 	//lay kich thuoc man hinh
// 	int rowCount = csvParser.GetRowCount();
// 	list.clear();
// 	for(int i = 0;i<rowCount;i++)
// 	{
// 		ScreenProperty screenProperty;
// 		screenProperty.width = csvParser.GetContentForHeaderAt("width",i).GetInt();
// 		screenProperty.height = csvParser.GetContentForHeaderAt("height",i).GetInt();
// 		screenProperty.textureRatio = csvParser.GetContentForHeaderAt("textureRatio",i).GetFloat();
// 		list.push_back(screenProperty);
// 	}

	selectScale = 0.4f;
	limitZoom = 0.1f;
	defauleSpriteSize = CCSizeMake(1536, 2048);

	ScreenProperty screenProperty;
	screenProperty.width = 480;
	screenProperty.height = 800;
	screenProperty.textureRatio = 0.4f;
	list.push_back(screenProperty);

	findSize();
	return true;
}
void ScreenUtils::findSize(){
	CCSize size = CCDirector::sharedDirector()->getWinSizeInPixels();
	//tinh scale theo kich thuoc 2048*1536
	float wScale = size.width/defauleSpriteSize.width;
	float hScale = size.height/defauleSpriteSize.height;
	m_ImageScale = 1;
	m_Scale = wScale<hScale?wScale:hScale;
	//tinh toan lay du lieu anh, can tinh lai sau
	for(int i = 0;i<list.size();i++){
		ScreenProperty s = list.at(i);
		wScale = size.width/s.width;
		hScale = size.height/s.height;
		float scale = wScale<hScale ? wScale : hScale;

		CCLOG("scale: %f",scale);
		if((1/scale>=1)||(i==list.size()-1 && 1/scale<=1)){
			m_ImageScale = scale;
			m_spriteSize = CCSizeMake(s.width,s.height);
			_texture_Ratio = s.textureRatio;
			break;
		}
		if(i<list.size()-1){
			ScreenProperty nextSize = list.at(i+1);
			wScale = size.width/nextSize.width;
			hScale = size.height/nextSize.height;
			float nextScale = wScale<hScale ? wScale : hScale;
			if(1/nextScale>1){
				float avgScale = 1/scale + (1/nextScale-1/scale)*selectScale;
				if(avgScale>1){
					m_ImageScale = scale;
					m_spriteSize = CCSizeMake(s.width,s.height);
					_texture_Ratio = s.textureRatio;
				}else{
					m_ImageScale = nextScale;
					m_spriteSize = CCSizeMake(nextSize.width,nextSize.height);
					_texture_Ratio = nextSize.textureRatio;
				}
				break;
			}
		}
	}
	wScale = m_spriteSize.width/defauleSpriteSize.width;
	hScale = m_spriteSize.height/defauleSpriteSize.height;

	//tinh toan co nen scale anh khong
	float dz = (::fabs(m_ImageScale-1)/m_ImageScale);
	if(dz<=limitZoom)
		m_ImageScale = 1;
}
std::string ScreenUtils::fileFull(const char* fileName){
	std::stringstream ss;
// 	if(GameConfig::shared()->isEncryptImage()){
// 		ss<<""<<(int)ScreenUtils::share()->getSpriteSize().width<<"_"<<(int)ScreenUtils::share()->getSpriteSize().height<<"_encrypt"<<"/"<<fileName;
// 	}
// 	else
// 	{
		ss<<""<<(int)ScreenUtils::share()->getSpriteSize().width<<"_"<<(int)ScreenUtils::share()->getSpriteSize().height<<"/"<<fileName;
	//}

	return ss.str();
}
std::string ScreenUtils::fileCommon(const char* fileName){
	std::stringstream ss;
// 	if(GameConfig::shared()->isEncryptCommon()){
// 		ss<<"common_encrypt"<<"/"<<fileName;
// 	}
// 	else
// 	{
		ss<<"common/"<<fileName;
//	}
	return ss.str();
}
float ScreenUtils::defaultScale(){
	return ScreenUtils::share()->getScale();
}
float ScreenUtils::imageScale(){
	return ScreenUtils::share()->getImageScale();
}
// Khong su dung cho CScaleSprite....
void ScreenUtils::scale(CCNode* node){
	node->setScale(ScreenUtils::share()->getImageScale());
}
void ScreenUtils::sketchX(CCNode* node, float width){
	CCSize s = node->getContentSize();
	node->setScaleX(width/s.width);
}
void ScreenUtils::sketchY(CCNode* node, float height){
	CCSize s = node->getContentSize();
	node->setScaleY(height/s.height);
}
float ScreenUtils::getWidth(CCNode* node){
	return node->getContentSize().width*node->getScaleX();
}
float ScreenUtils::getHeight(CCNode* node){
	return node->getContentSize().height*node->getScaleY();
}

float ScreenUtils::textureRatio()
{
	return ScreenUtils::share()->_texture_Ratio;
}

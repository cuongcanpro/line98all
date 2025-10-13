#include "LabelBM.h"
#include "../Utility/ScreenUtils.h"
#include "..//GlobalVar.h"

static bool _isFirstRun = true;
static const char* SCREEN_CONFIG = "fonts/config.csv";

LabelBM* LabelBM::create(CCNode*parent, const char* text,float size,const char* fontID,float width, CCTextAlignment alignment){
	FontConfig fontConfig = getFontConfig(fontID,size);
	LabelBM *pRet = new LabelBM();
	if(pRet && pRet->initWithString(text, fontConfig.file.c_str(),width, alignment, ccp(0, 0)))
	{
		pRet->autorelease();
		pRet->setDefaulScale(size/fontConfig.size*ScreenUtils::defaultScale());
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}
LabelBM* LabelBM::create(const char* text,FontType typeFont ,float width, CCTextAlignment alignment)
{
	FontItem fontItem = getFontItem(typeFont);
	LabelBM *pRet = new LabelBM();
	if(pRet && pRet->initWithString(text, fontItem.file.c_str(),width, alignment, ccp(0,0)))
	{
		pRet->autorelease();
		pRet->setDefaulScale(fontItem.defauleScale);
		pRet->setColor(fontItem.color);
		return pRet;
	}
//	CCLog("LabelBM::create: %s, %d",fontItem.file.c_str(),typeFont);
	CC_SAFE_DELETE(pRet);
	return NULL;
}

LabelBM* LabelBM::create( const char* text,FontType typeFont, ccColor3B color, float width /*= kCCLabelAutomaticWidth*/, CCTextAlignment alignment /*= kCCTextAlignmentCenter*/ )
{
	FontItem fontItem = getFontItem(typeFont);
	fontItem.color = color;
	LabelBM *pRet = new LabelBM();
	if(pRet && pRet->initWithString(text, fontItem.file.c_str(),width, alignment, ccp(0, 0)))
	{
		pRet->autorelease();
		pRet->setDefaulScale(fontItem.defauleScale);
		pRet->setColor(fontItem.color);
		return pRet;
	}
	//CCLog("LabelBM::create: %s, %d",fontItem.file.c_str(),typeFont);
	CC_SAFE_DELETE(pRet);
	return NULL;
}

FontItem LabelBM::getFontItem(FontType fontType)
{
	if(mapLoadedFont.find(fontType) == mapLoadedFont.end())
	{
		float fontSize = 80;
		std::string fntId = "outline";
		Color3B color = Color3B::WHITE;
		switch (fontType)
		{
		case FONT_SMALL_NORMAL_TYPE:
			fntId = "game";
			fontSize = 60;
			break;
		case FONT_NORMAL_TYPE:
			fntId = "normal";
			fontSize = 80;
			break;
		case FONT_OUTLINE_TYPE:
			fntId = "outline";
			fontSize = 80;
			break;
		case FONT_SMALL_OUTLINE_TYPE:
			fntId = "outline";
			fontSize = 60;
			break;
		case FONT_BOLD_TYPE:
			fntId = "bold";
			fontSize = 80;
			break;
		case FONT_GAME_TYPE:
			fntId = "game";
			fontSize = 80;
			break;
		default:
			break;
		}
		CCSize size = CCDirector::sharedDirector()->getWinSize();

		float scaleSize = fontSize*ScreenUtils::defaultScale();
		if ((size.width/size.height) == (4.0f/3.0f))
		{
			scaleSize = fontSize*ScreenUtils::defaultScale()*0.8;
		}
		
		FontConfig fontConfig = getFontConfig(fntId.c_str(),scaleSize);
		FontItem fontItem;
		fontItem.defauleScale = scaleSize/fontConfig.size;
		fontItem.file = fontConfig.file;
		fontItem.color = color;
		// Dai Zingphone, font chu xau nen phai tang ti le scale
		if((size.width == 320))
			fontItem.defauleScale = fontItem.defauleScale * 1.4f;
		else
			fontItem.defauleScale = fontItem.defauleScale * 0.9f;
		fontItem.defauleScale = 0.75;
		//CCLog("getFontItem %f , %s",fontItem.defauleScale, fontItem.file.c_str());
		mapLoadedFont.insert(std::pair<FontType,FontItem>(fontType,fontItem));
	}
	return mapLoadedFont.at(fontType);
}
void LabelBM::setScale(float scale)
{
	CCLabelBMFont::setScale(scale*_defaultScale);	
}
float LabelBM::getScale()
{
	return CCLabelBMFont::getScale()/_defaultScale;
}
float LabelBM::getWidth()
{
	if(CCLabelBMFont::getContentSize().width == 0)
		return 0 * _defaultScale;
	return CCLabelBMFont::getContentSize().width*_defaultScale;
}
float LabelBM::getHeight()
{
	return CCLabelBMFont::getContentSize().height*_defaultScale;
}
void LabelBM::setDefaulScale( float defaultScale )
{
	_defaultScale = defaultScale;
	CCLabelBMFont::setScale(CCLabelBMFont::getScale()*_defaultScale);	
}

FontConfig LabelBM::getFontConfig(const char* fntFile, float size)
{
	if(_isFirstRun){
		loadFontConfig();
		_isFirstRun = false;
	}
	FontList fontList = mapFont.at(fntFile);
	for (int i = 0;i< fontList.size();i++)
	{
		FontConfig fontConfig = fontList.at(i);
		if((i == 0 && size <= fontConfig.size)||(i==fontList.size()-1 && size >= fontConfig.size)){
			return fontConfig;
		}
		if(i<fontList.size()-1){
			FontConfig nextFontConfig = fontList.at(i+1);
			if(nextFontConfig.size > size){
				float avgScale = (size - fontConfig.size)/ (nextFontConfig.size - size);
				if(avgScale>0.1f){
					return nextFontConfig;
				}else{
					return fontConfig;
				}
				break;
			}
		}
	}
	CCAssert(false,"Khong pick dc font");
}
void LabelBM::loadFontConfig()
{
	//load file config
 	//ACSVParser csvParser;
// 	// Set the header and data type rows.
// 	csvParser.SetHeaderRow(0);
// 	csvParser.SetTypeRow(1);       
// 	std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(SCREEN_CONFIG);
// 	CCAssert(csvParser.ParseFile(fullPath, ACSVParser::Slurp),"Khong load duoc screen config");
// 
// 	int rowCount = csvParser.GetRowCount();
// 	FontConfig* fontConfig = new FontConfig();
// 	std::string fontId;
// 	std::string fileName = "";
// 	FontList* fontList = new FontList();
// 	for(int i = 0;i<rowCount;i++){
// 		std::string wstr = csvParser.GetContentAt(i,0).GetString();
// 		if(wstr.size()>0){
// 			fontId.assign(wstr.begin(),wstr.end());
// 			wstr = csvParser.GetContentAt(i,1).GetString();
// 			CCAssert(wstr.size()>0,"Ten armature khong duoc trong");
// 			fileName = "fonts/"+fontId+"/";
// 		}
// 		FontConfig* fontConfig = new FontConfig();
// 		fontConfig->size = csvParser.GetContentForHeaderAt("size",i).GetFloat();
// 		fontConfig->file = fileName + utility->convertIntLongToString((int)fontConfig->size) + ".fnt";
// 		fontList->push_back(*fontConfig);
// 		if((i==rowCount-1)||(csvParser.GetContentAt(i+1,0).GetString().size()>0)){
// 			mapFont.insert(std::pair<std::string, FontList>(fontId,*fontList));
// 			fontList = new FontList();
// 		}
// 
// 	
// 	}

	FontList* fontList = new FontList();

	FontConfig* fontConfig = new FontConfig();
	fontConfig->size = 20;
	fontConfig->file = "fonts/outline/20.fnt";
	fontList->push_back(*fontConfig);

	fontConfig = new FontConfig();
	fontConfig->size = 30;
	fontConfig->file = "fonts/outline/30.fnt";
	fontList->push_back(*fontConfig);

	fontConfig = new FontConfig();
	fontConfig->size = 50;
	fontConfig->file = "fonts/outline/50.fnt";
	fontList->push_back(*fontConfig);

	fontConfig = new FontConfig();
	fontConfig->size = 80;
	fontConfig->file = "fonts/outline/80.fnt";
	fontList->push_back(*fontConfig);

	mapFont.insert(std::pair<std::string, FontList>("outline", *fontList));

	fontList = new FontList();

	fontConfig = new FontConfig();
	fontConfig->size = 20;
	fontConfig->file = "fonts/normal/20.fnt";
	fontList->push_back(*fontConfig);

	fontConfig = new FontConfig();
	fontConfig->size = 30;
	fontConfig->file = "fonts/normal/30.fnt";
	fontList->push_back(*fontConfig);

	fontConfig = new FontConfig();
	fontConfig->size = 50;
	fontConfig->file = "fonts/normal/50.fnt";
	fontList->push_back(*fontConfig);

	fontConfig = new FontConfig();
	fontConfig->size = 80;
	fontConfig->file = "fonts/normal/80.fnt";
	fontList->push_back(*fontConfig);

	mapFont.insert(std::pair<std::string, FontList>("normal", *fontList));

	fontList = new FontList();

	fontConfig = new FontConfig();
	fontConfig->size = 20;
	fontConfig->file = "fonts/bold/20.fnt";
	fontList->push_back(*fontConfig);

	fontConfig = new FontConfig();
	fontConfig->size = 30;
	fontConfig->file = "fonts/bold/30.fnt";
	fontList->push_back(*fontConfig);

	fontConfig = new FontConfig();
	fontConfig->size = 50;
	fontConfig->file = "fonts/bold/50.fnt";
	fontList->push_back(*fontConfig);

	fontConfig = new FontConfig();
	fontConfig->size = 80;
	fontConfig->file = "fonts/bold/80.fnt";
	fontList->push_back(*fontConfig);

	mapFont.insert(std::pair<std::string, FontList>("bold", *fontList));


	fontConfig = new FontConfig();
	fontConfig->size = 20;
	fontConfig->file = "fonts/game/20.fnt";
	fontList->push_back(*fontConfig);

	fontConfig = new FontConfig();
	fontConfig->size = 30;
	fontConfig->file = "fonts/game/30.fnt";
	fontList->push_back(*fontConfig);

	fontConfig = new FontConfig();
	fontConfig->size = 50;
	fontConfig->file = "fonts/game/50.fnt";
	fontList->push_back(*fontConfig);

	fontConfig = new FontConfig();
	fontConfig->size = 80;
	fontConfig->file = "fonts/game/80.fnt";
	fontList->push_back(*fontConfig);

	mapFont.insert(std::pair<std::string, FontList>("game", *fontList));
}

void LabelBM::setPos( float x, float y )
{
	setPosition(ccp(x,y));
}
void LabelBM::setText(const char* text)
{
	setString(text);
}

void LabelBM::setEnable( bool enable )
{

}

void LabelBM::setFontType( FontType typeFont )
{
	FontItem fontItem = getFontItem(typeFont);
	LabelBM *pRet = new LabelBM();
	setFntFile( fontItem.file.c_str());
	setDefaulScale(fontItem.defauleScale);
	setColor(fontItem.color);
}

void LabelBM::purge()
{
	_isFirstRun = true;
	mapLoadedFont.clear();
	mapFont.clear();
}

std::map<FontType,FontItem> LabelBM::mapLoadedFont;

std::map<std::string,FontList> LabelBM::mapFont;



float LabelBM::getDefaultScale()
{
	return _defaultScale;
}
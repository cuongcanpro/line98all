#ifndef LabelBM_h__
#define LabelBM_h__

#include "cocos2d.h"
#include <string>
#include <map>
#include <vector>
using namespace cocos2d;
enum FontType
{
	FONT_SMALL_NORMAL_TYPE,
	FONT_SMALL_OUTLINE_TYPE,
	FONT_NORMAL_TYPE,
	FONT_OUTLINE_TYPE,
	FONT_GAME_TYPE,
	FONT_BOLD_TYPE,
	FONT_20_ARIALRB_TYPE,
	FONT_30_ARIALRB_TYPE,
	FONT_50_ARIALRB_TYPE,
	
};
struct FontItem
{
	float defauleScale;
	std::string file;
	ccColor3B color;
};
struct FontConfig
{
	int size;
	std::string file;
};
typedef  std::vector<FontConfig> FontList;
class LabelBM:
	public CCLabelBMFont
{
	
public:
	static void purge();
	static LabelBM* create(CCNode*parent, const char* text,float size,const char* fontID,float width  = 0, CCTextAlignment alignment = kCCTextAlignmentCenter);
	static LabelBM* create(const char* text,FontType typeFont,float width  = 0, CCTextAlignment alignment = kCCTextAlignmentCenter);
	static LabelBM* create(const char* text,FontType typeFont, ccColor3B color, float width  = 0, CCTextAlignment alignment = kCCTextAlignmentCenter);
	//size: kich thuoc font
	//static LabelBM* create(const char* text,float size, const char* fntFile);
	int id;
	float getWidth();
	float getHeight();
	void setDefaulScale(float defaultScale);
	void setScale(float scale);
	float getScale();
	void setPos( float x, float y );
	void setText(const char* text);
	void setEnable(bool enable);
	void setFontType(FontType typeFont);
	static void loadFontConfig();

	float getDefaultScale();
private:
	//LabelBM();
	float _defaultScale;
	static FontItem getFontItem(FontType fontType);
	static FontConfig getFontConfig(const char* fntFile, float size);
	static std::map<std::string,FontList> mapFont;
	static std::map<FontType,FontItem> mapLoadedFont;
};

#endif // LabelBM_h__


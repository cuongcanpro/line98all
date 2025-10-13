#ifndef _SCREEN_UTILS__
#define _SCREEN_UTILS__

#include "cocos2d.h"
#include <sstream>
#include <fstream>
#include <map>
 #include <vector>  
USING_NS_CC;
struct ScreenProperty
{
	float width;
	float height;
	float textureRatio;
};
class ScreenUtils: public CCObject{
	CC_SYNTHESIZE_READONLY(float, m_Scale, Scale);
	CC_SYNTHESIZE_READONLY(float, m_ImageScale, ImageScale);
	CC_SYNTHESIZE_READONLY(CCSize, m_spriteSize, SpriteSize);
private:
	std::vector<ScreenProperty> list;
	//float scale;
	void findSize();
	//
	float selectScale;
	float limitZoom;
	float _texture_Ratio;
protected:
	bool init ();
public:
	static ScreenUtils* share();
	static float textureRatio();
	static float imageScale();
	static float defaultScale();
	static std::string fileFull(const char* fileName);
	static std::string  fileCommon(const char* fileName);
	static void scale(CCNode* node);
	static void sketchX(CCNode* node, float width);
	static void sketchY(CCNode* node, float height);
	static float getWidth(CCNode* node);
	static float getHeight(CCNode* node);
};
#endif

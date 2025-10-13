#include "DBCCSprite.h"
#include <string.h>
#include <stdlib.h>

USING_NS_CC;

NAME_SPACE_DRAGON_BONES_BEGIN

#define SHADER_FILE_CHANGE_COLOR "shaders/change_color.fsh"
#define RATIO_ADJUST_COLOR 1.0f
#define R_REPLACE "%r%"
#define G_REPLACE "%g%"
#define B_REPLACE "%b%"

static std::string shaderFileContent = "";
static std::map<int, GLProgram*> listProgramColor;

bool replace(std::string& str, const std::string& from, const std::string& to){
	if (from.empty())
		return false;
	
	size_t start = 0U;
	size_t pos = str.find(from);
	if (pos != std::string::npos){
		str.replace(pos, from.length(), to);
	}
	return true;
}
bool replace(std::string& str, const std::string& from, float to){
	char s_to[20];
	int size = sprintf(s_to, "%.5f", to);
	std::string st = std::string(s_to, size);
	cocos2d::log("str: %s", st.c_str());
	return replace(str, from, st);
}

static GLProgram* getProgramColor(int r, int g, int b)
{
	int key = r * 1000000 + g * 1000 + b;
	if (listProgramColor.find(key) == listProgramColor.end())
	{
		if (shaderFileContent.size() == 0)
		{
			auto fileUltils = FileUtils::getInstance();
			auto fragmentFullPath = fileUltils->fullPathForFilename("shaders/change_color.fsh");
			shaderFileContent = fileUltils->getStringFromFile(fragmentFullPath);
		}
		auto fragSource = shaderFileContent;

		float rValue = RATIO_ADJUST_COLOR*r / 255.0f;
		float gValue = RATIO_ADJUST_COLOR*g / 255.0f;
		float bValue = RATIO_ADJUST_COLOR*b / 255.0f;

		replace(fragSource, R_REPLACE, rValue);
		replace(fragSource, G_REPLACE, gValue);
		replace(fragSource, B_REPLACE, bValue);

		auto glprogram = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, fragSource.c_str());
		glprogram->retain();
		listProgramColor.insert(std::pair<int, GLProgram*>(key, glprogram));
	}
	return listProgramColor.at(key);
}


DBCCSprite::DBCCSprite()
{
	_glprogramstate = nullptr;
}

DBCCSprite::~DBCCSprite()
{

}

DBCCSprite* DBCCSprite::createWithSpriteFrame(cocos2d::SpriteFrame *spriteFrame)
{
	DBCCSprite *sprite = new (std::nothrow) DBCCSprite();
	if (sprite && spriteFrame && sprite->initWithSpriteFrame(spriteFrame))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}
void DBCCSprite::setColorByShader(int r, int g, int b)
{
	if (!this)
		return;

	_glprogramstate = GLProgramState::getOrCreateWithGLProgram(getProgramColor(r,g,b));
	this->setGLProgramState(_glprogramstate);
}

NAME_SPACE_DRAGON_BONES_END
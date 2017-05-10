#pragma once
/**
* creator: Kiet Duong
* date: 2017-02-09
* file: Helper4String.h, Helper4String.cpp
*/
#include "cocos2d.h"

using namespace std;
class Helper4Sprite
{
public:

	/// <summary>
	/// set blend mode add for sprite
	/// </summary>
	/// <param name="sprite"></param>
	static void setBlendModeAdd(cocos2d::Sprite * sprite);
	/// <summary>
	/// set color for part of label
	/// </summary>
	/// <param name="label"></param>
	/// <param name="from"></param>
	/// <param name="to"></param>
	/// <param name="color"></param>
	static void setColor4RangeOfLabel(cocos2d::Label * label, int from, int to, cocos2d::Color3B color);
	/// <summary>
	/// append string to label with new color
	/// </summary>
	/// <param name="label"></param>
	/// <param name="appendString"></param>
	/// <param name="color"></param>
	static void labelAppendString(cocos2d::Label * label, std::string appendString, cocos2d::Color3B color);

	/// <summary>
	/// create sprite on background thread base on optimize plan
	/// </summary>
	/// <param name="filepath"></param>
	/// <param name="callback"></param>
	static void addOptimizeImageAsync(const std::string &filepath, const std::function<void(cocos2d::Texture2D*)>& callback);
	/// <summary>
	/// get texture from frame name
	/// </summary>
	/// <param name="filename"></param>
	/// <returns></returns>
	static cocos2d::Texture2D* getTextureFromSpriteFramename(const std::string& filename);
	/// <summary>
	/// create sprite with frame name
	/// </summary>
	/// <param name="filename"></param>
	/// <returns></returns>
	static cocos2d::Sprite* createWithSpriteFrameName(const std::string& filename);
	/// <summary>
	/// create sprite base on optimize plan
	/// </summary>
	/// <param name="filename">file name</param>
	/// <returns></returns>
	static cocos2d::Sprite* createOptimizeSprite(const std::string& filename);
	/// <summary>
	/// create sprite base on optimize plan
	/// </summary>
	/// <param name="filename">file name</param>
	/// <param name="rect">rect of sprite</param>
	/// <returns></returns>
	static cocos2d::Sprite* createOptimizeSprite(const std::string& filename, const cocos2d::Rect& rect);
	/// <summary>
	/// create sprite base on optimize plan
	/// </summary>
	/// <returns></returns>
	static cocos2d::Sprite* createOptimizeSprite();

};
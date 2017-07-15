#pragma once
/**
* creator: Dat
* date: 2017-02-09
* file: AnimationManager.h, AnimationManager.cpp
*/

#include "cocos2d.h"

class ScaleManager
{
private:
	ScaleManager();
	static ScaleManager* s_instance;
	float ratio;
public:
	/**
	* get instance class
	*/
	static ScaleManager* getInstance();

	/// <summary>
	/// init with game size info
	/// </summary>
	/// <param name="visibleSize"></param>
	/// <param name="original"></param>
	void init(cocos2d::Size visibleSize, cocos2d::Vec2 original);

	/// <summary>
	/// return ratio > 1 compare with ipad size
	/// </summary>
	/// <returns></returns>
	float getScaleUpRatio();

	/// <summary>
	/// return ratio < 1 compare with ipad size
	/// </summary>
	/// <returns></returns>
	float getExactlyScaleDownRatio();

	/// <summary>
	/// return ratio < 1 compare with ipad size
	/// </summary>
	/// <returns></returns>
	float getLookGoodScaleDownRatio();
};
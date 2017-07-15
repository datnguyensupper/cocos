#pragma once
/**
* creator: Dat
* date: 2017-02-09
* file: AnimationManager.h, AnimationManager.cpp
*/

#include "cocos2d.h"

class AnimationManager
{
private:
	AnimationManager();
	static AnimationManager* s_instance;
public:
	/**
	* 2017-02-09: Kiet: get instance class
	*/
	static AnimationManager* getInstance();
	/// <summary>
	/// play coin animation
	/// </summary>
	/// <param name="from">from position</param>
	/// <param name="to">to position</param>
	/// <param name="parent">parent contain animation</param>
	void playCoinAnimation(cocos2d::Vec2 from, cocos2d::Vec2 to, cocos2d::Node * parent);
};
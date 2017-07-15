#pragma once
/**
* creator: Kiet Duong
* date: 2017-03-28
* file: CrownFlareWithLensFlare.h, CrownFlareWithLensFlare.cpp
*/
#include "cocos2d.h"

#include "ui/CocosGUI.h"

class CirclePink : public cocos2d::Node
{
private:
	cocos2d::Sprite *circleSprite;
public:
	/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();
	/// <summary>
	/// reset and play animation
	/// </summary>
	/// <param name="loopTimes">number of loop animation</param>
	void resetAndPlay(int loopTimes = kRepeatForever);
	/// <summary>
	/// reset UI animation
	/// </summary>
	void reset() {
		this->circleSprite->setVisible(false);
	}
	// implement the "static create()" method manually
	/// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(CirclePink);
};

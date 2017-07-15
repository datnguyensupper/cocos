#pragma once
/**
* creator: Kiet Duong
* date: 2017-03-28
* file: CoinFlare.h, CoinFlare.cpp
*/
#include "cocos2d.h"

#include "ui/CocosGUI.h"

class CoinFlare : public cocos2d::Node
{
private:
	cocos2d::Sprite *coinSprite;
public:
	/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();
	/// <summary>
	/// reset and play animation
	/// </summary>
	/// <param name="loopTimes"></param>
	void resetAndPlay(int loopTimes = kRepeatForever);
	/// <summary>
	/// reset UI
	/// </summary>
	void reset() {
		this->coinSprite->setVisible(false);
	}
	// implement the "static create()" method manually
	/// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(CoinFlare);
};

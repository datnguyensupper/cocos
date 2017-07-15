#pragma once
/**
* creator: Kiet Duong
* date: 2017-03-28
* file: CrownFlareWithLensFlare.h, CrownFlareWithLensFlare.cpp
*/
#include "cocos2d.h"

#include "ui/CocosGUI.h"

class CrownFlareWithLensFlare : public cocos2d::Node
{
private:
	cocos2d::Sprite *crownFlareAnimation;
	cocos2d::Sprite *lensFlareAnimation;
	/// <summary>
	/// create crown flare animaiton
	/// </summary>
	/// <param name="loopTimes">number of loop animation</param>
	/// <returns></returns>
	cocos2d::FiniteTimeAction *createCrownFlareAction(int loopTimes);
	/// <summary>
	/// create lens flare animation
	/// </summary>
	/// <param name="loopTimes">number of loop animation</param>
	/// <returns></returns>
	cocos2d::FiniteTimeAction *createLensFlareAction(int loopTimes);
public:
	/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();
	/// <summary>
	/// reset and play all animation
	/// </summary>
	/// <param name="loopTimes"></param>
	void resetAndPlay(int loopTimes = kRepeatForever);
	/// <summary>
	/// reset UI animation
	/// </summary>
	void reset() {
		this->crownFlareAnimation->setVisible(false);
		this->lensFlareAnimation->setVisible(false);
	}
	// implement the "static create()" method manually
	/// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(CrownFlareWithLensFlare);
};

#pragma once
/**
* creator: Dat
* date: 2017-02-06
* file: CoinAnimationTestScene.h, CoinAnimationTestScene.cpp
*/
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Scene/BaseScene.h"

class CoinAnimationTestScene : public BaseScene
{
public:
	static cocos2d::Scene* createScene();

	/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();

	// implement the "static create()" method manually
	/// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(CoinAnimationTestScene);
};

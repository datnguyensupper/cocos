#pragma once
/**
* creator: Kiet Duong
* date: 2017-03-28
* file: AnimationCoinCrown.h, AnimationCoinCrown.cpp
*/
#include "cocos2d.h"

#include "ui/CocosGUI.h"

enum AnimationType
{
	CoinAnimation,
	CrownAnimation
};
class AnimationCoinCrown : public cocos2d::Layer
{
private:
	cocos2d::ParticleSystemQuad *particalInclude;
	cocos2d::Vec2 startPos;
	std::vector<cocos2d::MenuItemSprite*> objects;
	AnimationType currentType = AnimationType::CoinAnimation;
	double increment = 0;
	/// <summary>
	/// call back after click to UI animation
	/// </summary>
	/// <param name="ref">clicked object</param>
	void callbackAfterClickObject(cocos2d::Ref* ref);
public:

	/// <summary>
	/// 2017-02-06: Kiet: create AnimationCoinCrown
	/// </summary>
	/// <param name="parentScene">parent scene contain animation</param>
	/// <param name="startPosInWorld">animation position</param>
	/// <param name="increment">number of reward</param>
	/// <param name="type">coin or crow</param>
	/// <returns></returns>
	static AnimationCoinCrown* create(
		cocos2d::Scene* parentScene,
		cocos2d::Vec2 startPosInWorld,
		double increment,
		AnimationType type = AnimationType::CoinAnimation);

	/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();
};

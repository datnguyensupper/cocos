#pragma once
/**
* creator: Kiet Duong
* date: 2017-04-24
* file: HeaderMagicItemBtn.h, HeaderMagicItemBtn.cpp
*/
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Constant/PPEnums.h"
#include "Constant/LobbyConstant.h"
#include "Custom/Common/ButtonScaleChild.h"

class HeaderMagicItemBtn : public ButtonScaleChild
{
private:
	cocos2d::Sprite *additionSprite;
	cocos2d::Sprite *animationSprite;
	cocos2d::Sprite *additionSprite1;
	cocos2d::Vec2 defaultPos = cocos2d::Vec2::ZERO;

	LobbyConstant::MagicItemType currentType;

	void reset();
	/// <summary>
	/// setup pink halo background position
	/// </summary>
	void setupPosForPinkBG();
	/// <summary>
	/// setup yello halo background position
	/// </summary>
	void setupPosForYellowBG();
public:
	void changeItemType(LobbyConstant::MagicItemType newItemType);
	/**
	* 2017-04-24: Kiet: init function
	*/
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
	CREATE_FUNC(HeaderMagicItemBtn);
};


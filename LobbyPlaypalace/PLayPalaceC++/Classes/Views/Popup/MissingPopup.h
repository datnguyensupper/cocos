#pragma once
/**
* creator: Kiet Duong
* date: 2017-04-05
* file: MissingPopup.h, MissingPopup.cpp
*/
#include "BasePopup.h"
#include "Manager/LanguageManager.h"
#include "Constant/LanguageConstant.h"
#include "Constant/PPEnums.h"

class MissingPopup : public BasePopup
{
private:
	cocos2d::Label *missingCoinLabel;
	cocos2d::Sprite *currencySprite;
	cocos2d::Label *moreLabel;

	cocos2d::ui::Button *leftBtn;
	cocos2d::ui::Button *rightBtn;

	ppEnum::PPCurrency currentMissingCurrency;
public:
	/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();

	/// <summary>
	/// 2017-04-05: Kiet: prepare and show popup
	/// </summary>
	/// <param name="parent">parent of popup</param>
	/// <param name="missingCurrency">currency of amount show in popup</param>
	/// <param name="amount">missing amount</param>
	void prepareAndShow(
		cocos2d::Node *parent,
		ppEnum::PPCurrency missingCurrency,
		double amount
	);

	/// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(MissingPopup);
};
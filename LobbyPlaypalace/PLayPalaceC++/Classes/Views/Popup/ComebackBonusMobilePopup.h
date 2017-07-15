#pragma once
/**
* creator: Kiet Duong
* date: 2017-02-22
* file: ComebackBonusMobilePopup.h, ComebackBonusMobilePopup.cpp
*/
#include "BasePopup.h"
#include "Manager/LanguageManager.h"
#include "Constant/LanguageConstant.h"

class ComebackBonusMobilePopup : public BasePopup
{
private:
	cocos2d::ui::Button *collectButton;
	cocos2d::Label *coinRewardLabel;
	cocos2d::Label *expBonusLabel;

	/// <summary>
	/// 2017-04-12: Kiet: on collect comeback bonus touched
	/// </summary>
	/// <param name="sender">button info</param>
	/// <param name="type">type of touched</param>
	void collectTouched(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType type);
public:
	/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();
	virtual void reset() override;
	virtual void show() override;

	/**
	* prepare and show
	*/
	virtual void prepareAndShow(cocos2d::Node* parent);
	/**
	* dat: update ui after change language
	*/
	virtual void updateAfterChangeLanguage();

	/// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(ComebackBonusMobilePopup);
};
#pragma once
#include "../BasePopup.h"
#include "Info/SpecialOfferInfo.h"

class SpecialOfferPopup : public BasePopup
{
private:
	SpecialOfferInfo info;

	cocos2d::Label* txtRemainingTime;
	cocos2d::Label* txtRemainingAmount;
	cocos2d::ui::Button* btnBuyNow;

	void updateTime(float dt);
	void onButtonTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
public:
	/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();

	virtual void reset();
	/**
	* prepare and show
	*/
	virtual bool prepareAndShow(rapidjson::Value& rawData, cocos2d::Node* parent);

	/// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(SpecialOfferPopup);
};
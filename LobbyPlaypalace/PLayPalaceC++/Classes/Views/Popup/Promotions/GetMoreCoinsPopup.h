#pragma once
#include "../BasePopup.h"

class GetMoreCoinsPopup : public BasePopup
{
private:
	cocos2d::Label* txtCoin;
	cocos2d::ui::Button* btnShop;
	cocos2d::ui::Button* btnBuyNow;
	void onButtonTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
public:
	/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();

	/**
	* prepare and show
	*/
	bool prepareAndShow(cocos2d::Node* parent);

	/// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(GetMoreCoinsPopup);
};
#pragma once
#include "../BasePopup.h"

class StarterPackPopup : public BasePopup
{
private:
	cocos2d::ui::Button* btnBuy;
	cocos2d::Label* txtCoin;

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
	virtual void prepareAndShow(cocos2d::Node* parent);

	/// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(StarterPackPopup);
};
#pragma once
#include "Views/Popup/BasePopup.h"

class DailyLuckySpinInfoPopup : public BasePopup
{
private:
	cocos2d::ui::Button * btnOK;
public:
	/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();

	/**
	* prepare and show
	*/
	void prepareAndShow(cocos2d::Node* parent);

	/// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(DailyLuckySpinInfoPopup);
};
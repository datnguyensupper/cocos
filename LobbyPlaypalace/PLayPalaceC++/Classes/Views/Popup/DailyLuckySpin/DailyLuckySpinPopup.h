#pragma once
#include "Views/Popup/BasePopup.h"

class DailyLuckySpinInfoPopup;
class CSpinMachine;
class DailyBonusLuckySpinInfo;
class DailyLuckySpinPopup : public BasePopup
{
private:
	DailyBonusLuckySpinInfo* info;

	DailyLuckySpinInfoPopup* infoPopup;
	CSpinMachine* spinMachine;

	cocos2d::Sprite* btn;
	/// <summary>
	/// enable btn spin
	/// </summary>
	/// <param name="isEnable"></param>
	void setBtnEnabled(bool isEnable);
public:
	/**
	* init function
	*/
	/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();
	/**
	* on spin function
	*/
	void onSpin();
	/**
	* prepare and show
	*/
	void prepareAndShow(cocos2d::Node* parent);

	/// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(DailyLuckySpinPopup);
};
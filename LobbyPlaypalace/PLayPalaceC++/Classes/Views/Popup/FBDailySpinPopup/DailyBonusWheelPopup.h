/**
* creator: Kiet Duong
* date: 2017-04-03
* file: DailyBonusWheelPopup.h, DailyBonusWheelPopup.cpp
*/
#pragma once
#include "Views/Popup/BasePopup.h"

class DailyBonusWheelResultPopup;
class DailyBonusWheelSpinPopup;
class DailyBonusWheelPopup : public BasePopup
{
private:
	DailyBonusWheelSpinPopup *wheelPopup;
	DailyBonusWheelResultPopup *resultPopup;
public:
	/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();
	/// <summary>
	/// reset UI
	/// </summary>
	virtual void reset() override;
	/// <summary>
	/// show popup
	/// </summary>
	virtual void show() override;

	/**
	* 2017-03-04: Kiet: process after spin, called after wheelPopup spin finish
	*/
	void processAfterSpin();
	/**
	* 2017-03-04: Kiet: process collect coin reward
	*/
	void collectCoin(cocos2d::Vec2 worldBtnPos);

	/**
	* 2017-03-04: Kiet: prepare and show
	*/
	void prepareAndShow(cocos2d::Node* parent);


	/// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(DailyBonusWheelPopup);
};
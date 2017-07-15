/**
* creator: Kiet Duong
* date: 2017-04-03
* file: DailyBonusWheelSpinPopup.h, DailyBonusWheelSpinPopup.cpp
*/
#pragma once
#include "Views/Popup/BasePopup.h"

class DailyBonusWheelPopup;
class DailyBonusWheelSpinPopup : public BasePopup
{
private:
	cocos2d::Sprite *wheelBG;
	cocos2d::Sprite *wheelInner;
	cocos2d::Sprite *gear;
	cocos2d::Sprite *light;
	cocos2d::ui::Button *spinButton;
	cocos2d::ParticleSystemQuad *particalCircleForWheelBG;
	cocos2d::ParticleSystemQuad *particalCircleForSpinBtn;

	std::map<int, int> factorsWithAnglePosWheel; //key = factor, value = angle corresponding with "bg-wheel.png"
	std::map<double, int> coinValuesWithAnglePosInnerWheel; //key = coin, value = angle corresponding with "wheel_round_inner.png"

	DailyBonusWheelPopup *_parent;
	/**
	* 2017-03-04: Kiet: spin
	*/
	void spin();
public:
	static DailyBonusWheelSpinPopup* create(DailyBonusWheelPopup *parent);

	/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();
	/// <summary>
	/// reset UI
	/// </summary>
	virtual void reset() override;

	/**
	* 2017-03-04: Kiet: prepare and show popup with parent
	*/
	void prepareAndShow();
};
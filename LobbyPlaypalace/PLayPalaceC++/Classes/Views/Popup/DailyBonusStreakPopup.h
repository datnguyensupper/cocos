#pragma once
#include "BasePopup.h"

enum DailyBonusStreakItemType {
	PASSED_DAY,
	NOT_PASSED_DAY,
	STREAK_DAY
};
class DailyBonusStreakItem : public cocos2d::Node {
protected:
	cocos2d::Label* txtMoney;
	cocos2d::Label* txtDay;

	cocos2d::Sprite* sprtBg;
	cocos2d::Sprite* sprtCoin;
	cocos2d::Sprite* sprtCheck;
public:
	/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();
	/// <summary>
	/// set daily bonus streak info
	/// </summary>
	/// <param name="iDay">number of day</param>
	/// <param name="iMoney">coin reward</param>
	/// <param name="type">type of bonus streak not_pass,pass or streak day</param>
	void setInfo(int iDay, double iMoney, DailyBonusStreakItemType type);

	/// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(DailyBonusStreakItem);
};

class DailyBonusStreakPopup : public BasePopup
{
protected:
	cocos2d::Sprite* spriteBg;

	cocos2d::ParticleSystemQuad* particle;
	cocos2d::ui::Button* btnCollect;

	cocos2d::Sprite* spriteLightRay;

	std::vector<DailyBonusStreakItem*> aDayUI;
	/// <summary>
	/// collect daily bonus streak
	/// </summary>
	/// <param name="sender">button info</param>
	/// <param name="type">type of touched</param>
	void onCollect(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
public:
	/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();
	/// <summary>
	/// reset ui
	/// </summary>
	virtual void reset() override;
	/**
	* prepare and show
	*/
	void prepareAndShow(cocos2d::Node* parent);

	/// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(DailyBonusStreakPopup);
};
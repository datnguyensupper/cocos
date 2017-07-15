#pragma once
#include "BasePopup.h"

class PiggyBankInfo;
class BreakingPiggyBankUI;
class PiggyBankPopup : public BasePopup
{
private:
	PiggyBankInfo* piggyBankInfo;

	cocos2d::Node* groupNormal;
	BreakingPiggyBankUI* groupBreaking;

	cocos2d::Sprite* sprtLightRay;
	cocos2d::Sprite* sprtPigGlow;
	cocos2d::Sprite* sprtCoinLightRay;

	cocos2d::Node* groupPig;
	cocos2d::Sprite* sprtPigTail;
	cocos2d::Sprite* sprtPigBreakMask;

	cocos2d::Node* groupInfo;
	cocos2d::Label* txtInfo;
	cocos2d::Label* txtCoin;

	cocos2d::Sprite* sprtHammer;

	cocos2d::ui::Button* btnBreak;
	cocos2d::Sprite* btnBreakMask;

	cocos2d::ui::Button* closeBtn;

	std::vector<cocos2d::Vec2> aCoinPos;
	std::vector<cocos2d::Sprite*> aCoins;
	std::vector<cocos2d::Vec2> aCoinLocalPosition;

	/// <summary>
	/// init ui idle of piggy bank
	/// </summary>
	void initGroupNormal();

	/// <summary>
	/// create group coins on top of piggy bank
	/// </summary>
	/// <param name="pos">position of coins</param>
	void createGroupCoins(const cocos2d::Vec2& pos);

	/// <summary>
	/// start idle animation
	/// </summary>
	void startIdleAnimation();

	/// <summary>
	/// stop idle pig animaion
	/// </summary>
	void stopIdleAnimation();

	/// <summary>
	/// stop all animaion
	/// </summary>
	void stopAllAnimations();

	/// <summary>
	/// purchase pig fail
	/// </summary>
	void onPurchaseFailed();

	/// <summary>
	/// click on btn break the pig
	/// </summary>
	/// <param name="sender">button info</param>
	/// <param name="type">type of touched</param>
	void onBreakTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

	/// <summary>
	/// run break pig animation
	/// </summary>
	void breakingPig();

	/// <summary>
	/// running coin animation
	/// </summary>
	/// <param name="index">index of coin</param>
	void runCoinAnimation(int index);
public:
	/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();

	/**
	* 2017-02-27: Kiet: reset popup by set visible to false and ishowing to false
	*/
	virtual void reset();

	void prepareAndShow(cocos2d::Node* parent);

	/// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(PiggyBankPopup);
};

class BreakingPiggyBankUI : public cocos2d::Node {
private:
	cocos2d::Sprite* pigGlow;
	cocos2d::Sprite* pigHead;
	cocos2d::Sprite* pigBodyBehind;
	cocos2d::Sprite* pigBodyFront1;
	cocos2d::Sprite* pigBodyFront2;
	cocos2d::Sprite* flashLight;

	cocos2d::Sprite* coinsBehind;
	cocos2d::Sprite* coinsFront;

	/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();

	void playAnimation();
	void stopAnimation();

	/// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(BreakingPiggyBankUI);

	friend class PiggyBankPopup;
};
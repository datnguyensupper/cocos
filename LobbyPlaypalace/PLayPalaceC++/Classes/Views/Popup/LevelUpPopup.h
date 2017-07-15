#pragma once
#include "BasePopup.h"
#include "Manager/LanguageManager.h"
#include "Constant/LanguageConstant.h"
#include "SlotGame/GameSlotScene.h"

struct LevelUpInfo;
class LevelUpPopup : public BasePopup
{
private:
	GameSlot::GameSlotScene* scene;

	cocos2d::Sprite* oStars;
	cocos2d::Sprite* oLightRay;

	cocos2d::Label* oCoinReward;
	cocos2d::Label* oCrownReward;

	cocos2d::Label* oCurrentLevel;
	cocos2d::Label* oNewLevel;

	cocos2d::ui::Button* btnCollect;
	cocos2d::ui::Button* btnCollectAndShare;

	cocos2d::ui::Button* infoButton;
	cocos2d::Sprite* infoGroup;
	cocos2d::Sprite* boosterIconBg;
	cocos2d::Sprite* boosterIcon;
	cocos2d::ui::Button* boosterMultiplierCoin; //using button to have image and label in a object
	cocos2d::ui::Button* boosterMultiplierCrown; //using button to have image and label in a object

	cocos2d::ParticleSystemQuad* particalBoosterCoin;
	cocos2d::ParticleSystemQuad* particalBoosterCrown;

	int64_t iCoinReward;
	int64_t iCrownReward;

	long iCurrentLevel;
	long iNewLevel;

	bool isCollected = false;

	/// <summary>
	/// run collect animation
	/// </summary>
	void collectCoin();

	/// <summary>
	/// process after click collect Button
	/// </summary>
	/// <param name="sender"></param>
	/// <param name="type"></param>
	void onCollect(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

	/// <summary>
	/// process after click collect and share Button
	/// </summary>
	/// <param name="sender">button info</param>
	/// <param name="type">type of touched</param>
	void onCollectAndShare(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	/// <summary>
	/// run animation for level text
	/// </summary>
	/// <param name="iCurrentLevel"></param>
	/// <param name="iNewLevel"></param>
	void runNumberAnimation(
		int iCurrentLevel,
		int iNewLevel);

	/**
	* 2017-04-18: Kiet: run action for booster multiplier coin
	*/
	void runActionForBoosterCoin();
	/**
	* 2017-04-18: Kiet: run action for booster multiplier crown
	*/
	void runActionForBoosterCrown();
public:
	/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();
	/**
	* reset popup by set visible to false and ishowing to false
	*/
	void reset() override;

	/**
	* show popup directly with current info and UI (old popup were init before) without change parent
	*/
	virtual void show() override;

	/// <summary>
	/// prepare and show
	/// </summary>
	/// <param name="iCurrentLevel">old level</param>
	/// <param name="iNewLevel">new level</param>
	/// <param name="iCoinReward">coin reward</param>
	/// <param name="iCrownReward">corwn reward</param>
	/// <param name="isBoosterPackage">is activate booster</param>
	/// <param name="isX10">is x10 rule</param>
	void prepareAndShow(
		int iCurrentLevel,
		int iNewLevel,
		const int64_t& iCoinReward,
		const int64_t& iCrownReward,
		bool isBoosterPackage,
		bool isX10
	);
	/// <summary>
	/// save current game scene
	/// </summary>
	/// <param name="scene">current game scene</param>
	void setGame(GameSlot::GameSlotScene* scene) { this->scene = scene;  scene->addChild(this); }
	/// <summary>
	/// update text ui after change language
	/// </summary>
	void updateAfterChangeLanguage();

	/// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(LevelUpPopup);
};
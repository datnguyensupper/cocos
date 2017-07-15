#pragma once
/**
* creator: Kiet Duong
* date: 2017-02-15
* file: HeaderLobbyLayout.h, HeaderLobbyLayout.cpp
*/
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Constant/PPEnums.h"
#include "Constant/LobbyConstant.h"

class LobbyScene;
class UserInfo;
struct LevelUpInfo;
//animations
class CrownFlareWithLensFlare;
class CoinFlare;
class CirclePink;
class HeaderMagicItemBtn;
struct ReloadUIInfo
{
	std::function<void(bool isSuccess, LevelUpInfo* levelUpInfo)> callback = nullptr;
	bool isRunAnimationIncreaseCoin = true;
	bool isRunAnimationIncreaseCrown = true;
	ReloadUIInfo(
		std::function<void(bool isSuccess, LevelUpInfo* levelUpInfo)> callback = nullptr,
		bool isRunAnimationIncreaseCoin = true,
		bool isRunAnimationIncreaseCrown = true
	)
	{
		this->callback = callback;
		this->isRunAnimationIncreaseCoin = isRunAnimationIncreaseCoin;
		this->isRunAnimationIncreaseCrown = isRunAnimationIncreaseCrown;
	}
};
class HeaderLobbyLayout : public cocos2d::ui::Layout
{
private:
	cocos2d::Sprite* avatarSprite;
	cocos2d::Label* nameLabel;
	cocos2d::Label* levelLabel;
	cocos2d::Label* levelProgressBarLabel;
	cocos2d::ProgressTimer* levelProgressBar;
	cocos2d::Sprite* doubleExpBgProgressBar;
	cocos2d::Sprite* doubleExpFlareProgressBar;

	cocos2d::Label* coinLabel;
	cocos2d::Label* crownLabel;

	HeaderMagicItemBtn* headerMagicItemBtn;
	cocos2d::ui::Button* settingsButton;
	cocos2d::ui::Button* friendButton;
	cocos2d::ui::Button* backHomeButton;
	cocos2d::ui::Button* infoGameSlotButton;
	cocos2d::Node* bgLevel;

	CrownFlareWithLensFlare *crownFlareAnimation;
	CoinFlare *coinFlareAnimation;
	CirclePink *circlePinkAnimation;

	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	float scaleDownRatio;


	float deltaTimeRunCoinFlareAnimation = 0;
	double nextCoin = 0;
	long nextCrown = 0;
	std::vector<ReloadUIInfo*> reloadUIInfoQueue;
	bool isReloadingInfoAndUI = false;
	/**
	* 2017-02-20: Kiet: process after click settings button
	*/
	void onSettingsTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	/**
	* 2017-02-20: Kiet: process after click friend button
	*/
	void onFriendTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	/**
	* 2017-02-20: Kiet: process after click back home button
	*/
	void onBackHomeTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	/**
	* 2017-02-20: Kiet: process after click info game slot button
	*/
	void onInfoGameSlotTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

	/**
	* 2017-02-20: Kiet: update UI from user info
	*/
	void updateAllUIByUserInfo(UserInfo* userInfo, bool isUpdateCoinLabel = true, bool isUpdateCrownLabel = true);
	/**
	* 2017-02-20: Kiet: set visible 3 button right top screen
	* if in game -> show 3 button: info, back, setting
	* if in lobby -> show 3 or 2 button: friend, settings,...
	*/
	void initButtonsBaseOnCurrentScene(ppEnum::GameScene scene);
	/**
	* 2017-02-27: Kiet: run animation increase
	*/
	void runAnimationIncrease(double numberIncrease, cocos2d::Label* label);

	/**
	* 2017-02-27: Kiet: call to server from info reload ui
	*/
	void reloadWithReloadUIInfo(ReloadUIInfo* reloadUIInfo);
	/**
	* 2017-03-29: Kiet: schedule animation for header coin flare and crown flare
	* and subtract time left magic items
	*/
	void headerSchedule(float dt);
	/**
	* 2017-04-26: Kiet: check and show double exp progess bar effect (magic item double exp)
	*/
	void checkAndShowEffectDoubleExpProgressBar();
public:
	// implement the "static create()" method manually
	/// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(HeaderLobbyLayout);
	/**
	* 2017-02-20: Kiet: init function
	*/
    /// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();
	virtual void onEnter() override;
	virtual void onExit() override;
	/**
	* 2017-02-20: Kiet: update avatar sprite
	*/
	void updateAvatar(cocos2d::Texture2D* texture);
	/**
	* 2017-02-20: Kiet: update name label ui
	*/
	void updateName(std::string newName);
	/**
	* 2017-02-20: Kiet: update level progess bar 
	*/
	void updateLevelProcessBar(float percent, bool isRunAnimation = true);
	/**
	* 2017-02-20: Kiet: increase coin for UI and update coin for Info->getInstant()->userInfo.coin by increment
	* @param isRunAnimation: is run animation for text?
	*/
	void increaseCoin(double increment, bool isRunAnimation = true);
	/**
	* 2017-02-20: Kiet: decrease coin for UI and update coin for Info->getInstant()->userInfo.coin by decrement
	* @return: is decrease success (is enought coin to decrease?)
	*/
	bool decreaseCoin(double decrement, bool isRunAnimation = true);

	/**
	* 2017-02-20: Kiet: increase Crown for UI and update coin for Info->getInstant()->userInfo.crown by increment
	* @param isRunAnimation: is run animation for text?
	*/
	void increaseCrown(double increment, bool isRunAnimation = true);
	/**
	* 2017-02-20: Kiet: decrease Crown for UI and update coin for Info->getInstant()->userInfo.crown by decrement
	* @return: is decrease success (is enought crown to decrease?)
	*/
	bool decreaseCrown(double decrement, bool isRunAnimation = true);
	/**
	* 2017-02-22: Kiet: reload userinfo in infomanager from server -> update all ui header and show popup level up if up level.
	* if in game slot and up level, this function will update without increase coin up level
	* if you want update coin went up level too. call function increaseCoin() in callback collect button of popup level up
	*/
	void reloadUIHeaderAndCheckShowPopupLevelUp(
		std::function<void(bool isSuccess, LevelUpInfo* levelUpInfo)> callback = nullptr,
		bool isRunAnimationIncreaseCoin = true,
		bool isRunAnimationIncreaseCrown = true);
	/**
	* 2017-02-27: Kiet: go to lobby scene
	*/
	void gotoLobbyScene();
	/**
	* set coin text
	*/
	void setCoin(double coin);
	/**
	* set crown text
	*/
	void setCrown(double crown);
	/**
	* 2017-03-13: Kiet: get coin in header ui
	*/
	double getCoinInHeaderUI();

	/**
	* 2017-03-13: Kiet: get coin in header ui
	*/
	long getCrownInHeaderUI();

	/**
	* 2017-03-13: Kiet: on change scene
	*/
	void onChangeScene(ppEnum::GameScene scene);

	void hightLightExpBar(double gainedEXP);

	/**
	* 2017-04-24: Kiet: show magic item btn
	*/
	void showMagicItemBtn(LobbyConstant::MagicItemType magicItemType);
	/**
	* 2017-04-24: Kiet: hide magic item btn
	*/
	void hideMagicItemBtn();
};
#pragma once
/**
* creator: Kiet Duong
* date: 2017-02-18
* file: PopupManager.h, PopupManager.cpp
*/

#include "cocos2d.h"
class NotiLoginPopup;
class NotificationPopup;
class SettingPopup;
class LoadingAnimation;
class ShopPopup;
class LevelUpPopup;
class LuckyBoxPopup;
class FriendPopup;
class GameSlotInfoPopup;
class GameUnlockedPopup;
class ChangeNamePopup;
class AddRefereeCodePopup;
class ProfilePopup;
class AchievementPopup;
class DailyBonusWheelPopup;
class ComebackBonusMobilePopup;
class BasePopup;
class HeaderLobbyLayout;
class BodyLobbyLayout;
class BottomLobbyLayout;
class DailyBonusStreakPopup;
class DailyLuckySpinPopup;
class DailyChallengePopup;
class PiggyBankPopup;
class MascotNotificationPopup;
class MagicItemPopup;
class MissingPopup;
struct PopupQueueStruct
{
	BasePopup* popup;
	cocos2d::Node* parent;
	int previousSceneTag;
	bool forceShowAfterReleaseScene;
};
class PopupManager
{
private:
	PopupManager();
	~PopupManager();
	static PopupManager* s_instance;

	NotiLoginPopup* notiLoginPopup = nullptr;
	NotificationPopup* notificationPopup = nullptr;
	ProfilePopup* profilePopup = nullptr;
	SettingPopup* settingPopup = nullptr;
	LoadingAnimation* loadingAnimation = nullptr;
	ShopPopup* shopPopup = nullptr;
	LevelUpPopup* levelupPopup = nullptr;
	LuckyBoxPopup* luckyBoxPopup = nullptr;
	FriendPopup* friendPopup = nullptr;
	GameSlotInfoPopup* gameSlotInfoPopup = nullptr;
	GameUnlockedPopup* gameUnlockedPopup = nullptr;
	ChangeNamePopup* changeNamePopup = nullptr;
	AddRefereeCodePopup* addRefereeCodePopup = nullptr;
	AchievementPopup* achievementPopup = nullptr;
	DailyBonusWheelPopup* dailyBonusWheelPopup = nullptr;
	ComebackBonusMobilePopup* comebackBonusMobilePopup = nullptr;
	DailyBonusStreakPopup* dailyBonusStreak = nullptr;
	DailyLuckySpinPopup* dailyLuckySpinPopup = nullptr;
	DailyChallengePopup* dailyChallengePopup = nullptr;
	PiggyBankPopup* piggyBankPopup = nullptr;
	MascotNotificationPopup* mascotNotiPopup = nullptr;
	MagicItemPopup* magicItemPopup = nullptr;
	MissingPopup* missingPopup = nullptr;

	std::deque<PopupQueueStruct*> *popupQueue;

	HeaderLobbyLayout* headerLobbyLayout = nullptr;
	BodyLobbyLayout *bodyLobbyLayout = nullptr;
	BottomLobbyLayout *bottomLobbyLayout = nullptr;

	cocos2d::Scene* currentScene = nullptr;

public:
	/**
	* 2017-02-18: Kiet: get instance class
	*/
	static PopupManager* getInstance();
	/**
	* 2017-02-27: Kiet: init popups in initsession scene
	*/
	void initAllPopupLobbyScene();
	/**
	* 2017-02-27: Kiet: init loading animation
	*/
	void initThingsLoginScene();
	/**
	* 2017-03-02: Kiet: reset popups
	*/
	void reset();
	/**
	* 2017-02-27: Kiet: push popup to show queue
	* @param: forceShowAfterReleaseScene: get current scene and set as parent if parent were release
	*/
	void pushBackShowPopup(BasePopup* popup, cocos2d::Node* parent, bool forceShowAfterReleaseScene = false);
	/**
	* 2017-02-27: Kiet: push popup to show queue, called after hide any popup, there for, need to check
	* which popup added to queue
	* @param frontPopup to check front of queue is frontPopup
	*/
	void popFrontShowPopup(BasePopup* frontPopup, bool popupOnly = false);
	/**
	* 2017-02-27: Kiet: check popup in queue
	*/
	bool isPopupInQueue(BasePopup* popup);
	/**
	* 2017-02-27: Kiet: check and show popup in queue
	*/
	void checkAndShowPopupInQueue();
	/**
	* 2017-02-18: Kiet: get notification login popup
	*/
	NotiLoginPopup* getNotificationLoginPopup() {
		return this->notiLoginPopup;
	}
	/**
	* 2017-02-18: Kiet: get notification popup
	*/
	NotificationPopup* getNotificationPopup() {
		return this->notificationPopup;
	}
	/**
	* 2017-02-22: Kiet: get setting popup
	*/
	ProfilePopup* getProfilePopup() {
		return this->profilePopup;
	}
	/**
	* 2017-02-22: Kiet: get setting popup
	*/
	SettingPopup* getSettingPopup() {
		return this->settingPopup;
	}
	/**
	* 2017-02-22: Kiet: get loading animation
	*/
	LoadingAnimation* getLoadingAnimation() {
		return this->loadingAnimation;
	}
	/**
	* 2017-03-01: Kiet: get shop popup
	*/
	ShopPopup* getShopPopup() {
		return this->shopPopup;
	}
	/**
	* get level up popup
	*/
	LevelUpPopup* getLevelUpPopup() {
		return this->levelupPopup;
	}
	/**
	* get lucky box popup
	*/
	LuckyBoxPopup* getLuckyBoxPopup() {
		return this->luckyBoxPopup;
	}
	/**
	* 2017-03-01: Kiet: get friend popup
	*/
	FriendPopup* getFriendPopup() {
		return this->friendPopup;
	}
	/**
	* get game slot info popup
	*/
	GameSlotInfoPopup* getInfoPopup() {
		return this->gameSlotInfoPopup;
	}

	/**
	* get game unlocked popup
	*/
	GameUnlockedPopup* getGameUnlockedPopup() {
		return this->gameUnlockedPopup;
	}

	/**
	* get game change name popup
	*/
	ChangeNamePopup* getChangeNamePopup() {
		return this->changeNamePopup;
	}

	/**
	* get game change name popup
	*/
	AddRefereeCodePopup* getAddRefereeCodePopup() {
		return this->addRefereeCodePopup;
	}
	/**
	* get achievement popup
	*/
	AchievementPopup* getAchievementPopup() {
		return this->achievementPopup;
	}
	/**
	* 2017-04-04: Kiet: get daily bonus wheel popup
	*/
	DailyBonusWheelPopup* getDailyBonusWheelPopup() {
		return this->dailyBonusWheelPopup;
	}
	/**
	* 2017-04-04: Kiet: get comeback bonus mobile popup
	*/
	ComebackBonusMobilePopup* getComebackBonusMobilePopup() {
		return this->comebackBonusMobilePopup;
	}
	/**
	* get bonus streak popup
	*/
	DailyBonusStreakPopup* getDailyBonusStreakPopup() {
		return this->dailyBonusStreak;
	}
	/**
	* get daily spin popup
	*/
	DailyLuckySpinPopup* getDailyLuckySpinPopup() {
		return this->dailyLuckySpinPopup;
	}
	/**
	* get daily chellenge popup
	*/
	DailyChallengePopup* getDailyChallengePopup() {
		return this->dailyChallengePopup;
	}

	/**
	* get piggy bank popup
	*/
	PiggyBankPopup* getPiggyBankPopup() {
		return this->piggyBankPopup;
	}
	/**
	* get masecot notification popup
	*/
	MascotNotificationPopup* getMascotNotificationPopup() {
		return this->mascotNotiPopup;
	}
	/**
	* 2017-04-26: Kiet: get magic item popup
	*/
	MagicItemPopup* getMagicItemPopup() {
		return this->magicItemPopup;
	}
	/**
	* 2017-04-26: Kiet: get missing popup
	*/
	MissingPopup* getMissingPopup() {
		return this->missingPopup;
	}
	/**
	* 2017-03-01: Kiet: get header lobby layout 
	*/
	HeaderLobbyLayout* getHeaderLobbyLayout() {
		return this->headerLobbyLayout;
	}
	/**
	* 2017-03-01: Kiet: set header lobby layout (call on enter headerLobbyLayout)
	*/
	void setHeaderLobbyLayout(HeaderLobbyLayout* _headerLobbyLayout) {
		this->headerLobbyLayout = _headerLobbyLayout;
	}
	/**
	* Dat: get body lobby layout 
	*/
	BodyLobbyLayout* getBodyLobbyLayout() {
		return this->bodyLobbyLayout;
	}
	/**
	* Dat: set body lobby layout
	*/
	void setBodyLobbyLayout(BodyLobbyLayout* _bodyLobbyLayout) {
		this->bodyLobbyLayout = _bodyLobbyLayout;
	}
	/**
	* 2017-03-01: Kiet: get header lobby layout
	*/
	BottomLobbyLayout* getBottomLobbyLayout() {
		return this->bottomLobbyLayout;
	}
	/**
	* 2017-03-01: Kiet: set header lobby layout (call on enter headerLobbyLayout)
	*/
	void setBottomLobbyLayout(BottomLobbyLayout* _bottomLobbyLayout) {
		this->bottomLobbyLayout = _bottomLobbyLayout;
	}
};
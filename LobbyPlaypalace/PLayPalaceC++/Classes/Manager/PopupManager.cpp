#include "PopupManager.h"
#include "Views/Popup/BasePopup.h"
#include "Views/Login/NotiLoginPopup.h"
#include "Views/Popup/NotificationPopup.h"
#include "Views/Popup/ProfilePopup.h"
#include "Views/Popup/SettingPopup.h"
#include "Views/Popup/LoadingAnimation.h"
#include "Views/Popup/Shop/ShopPopup.h"
#include "Views/Popup/LevelUpPopup.h"
#include "Views/Popup/LuckyBoxPopup.h"
#include "Views/Popup/FriendPopup/FriendPopup.h"
#include "Views/Popup/GameSlotInfoPopup.h"
#include "Views/Popup/GameUnlockedPopup.h"
#include "Views/Popup/AddRefereeCodePopup.h"
#include "Views/Popup/Achievement/AchievementPopup.h"
#include "Views/Popup/FBDailySpinPopup/DailyBonusWheelPopup.h"
#include "Views/Popup/ComebackBonusMobilePopup.h"
#include "Views/Popup/DailyBonusStreakPopup.h"
#include "Views/Popup/DailyLuckySpin/DailyLuckySpinPopup.h"
#include "Views/Popup/DailyChallengePopup.h"
#include "Views/Popup/MascotNotificationPopup.h"
#include "Views/Popup/MagicItemPopup.h"
#include "Views/Popup/PiggyBankPopup.h"
#include "Views/Popup/MissingPopup.h"

#include "Views/Popup/Promotions/SpecialOfferPopup.h"
#include "Views/Popup/Promotions/StarterPackPopup.h"
#include "Views/Popup/Promotions/PayToPlayPopup.h"
#include "Views/Popup/Promotions/FreeToPlayPopup.h"
#include "Views/Popup/Promotions/GetMoreCoinsPopup.h"
#include "Views/Popup/ScratchCardPopup.h"

#include "Helper/Helper4Scene.h"

using namespace std;
USING_NS_CC;
#pragma region init singleton
PopupManager* PopupManager::s_instance = nullptr;

PopupManager* PopupManager::getInstance()
{
	if (s_instance == nullptr) {
		s_instance = new PopupManager();
	}
	auto runningScene = Helper4Scene::getRunningScene();
	if (s_instance->currentScene != runningScene) {
		s_instance->currentScene = runningScene;
		//s_instance->reset();
	}
	return s_instance;
}
#pragma endregion

PopupManager::PopupManager()
{
	this->popupQueue = new std::deque<PopupQueueStruct*>();
}

PopupManager::~PopupManager()
{
	CC_SAFE_RELEASE_NULL(this->notificationPopup);
	CC_SAFE_RELEASE_NULL(this->settingPopup);
	CC_SAFE_RELEASE_NULL(this->loadingAnimation);

	CC_SAFE_DELETE(s_instance);
}
void PopupManager::initAllPopupLobbyScene()
{
	//already init
	if (this->notificationPopup
		|| this->settingPopup
		|| this->shopPopup)
	{
		return;
	}

	// preload img magic item
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PLIST_MAGIC_ITEM);
	// preload img popup level up
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PNG_LVUP_POPUP_PLIST);
	// preload img popup button
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PNG_POPUP_BUTTON_PLIST);
	// preload img general icon
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PNG_GENERAL_ICON_PLIST);
	// preload img header
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PLIST_HEADER);

	this->notificationPopup = NotificationPopup::create();
	this->notificationPopup->retain();
	this->profilePopup = ProfilePopup::create();
	this->profilePopup->retain();
	this->settingPopup = SettingPopup::create();
	this->settingPopup->retain();
	this->shopPopup = ShopPopup::create();
    this->shopPopup->retain();
    this->dailyBonusWheelPopup = DailyBonusWheelPopup::create();
    this->dailyBonusWheelPopup->retain();
	this->levelupPopup = LevelUpPopup::create();
	this->levelupPopup->retain();
	this->luckyBoxPopup = LuckyBoxPopup::create();
	this->luckyBoxPopup->retain();
	this->friendPopup = FriendPopup::create();
	this->friendPopup->retain();
	this->gameSlotInfoPopup = GameSlotInfoPopup::create();
	this->gameSlotInfoPopup->retain();
	this->gameUnlockedPopup = GameUnlockedPopup::create();
	this->gameUnlockedPopup->retain();
	this->changeNamePopup = ChangeNamePopup::create();
	this->changeNamePopup->retain();
	this->addRefereeCodePopup = AddRefereeCodePopup::create();
	this->addRefereeCodePopup->retain();
	this->achievementPopup = AchievementPopup::create();
	this->achievementPopup->retain();
	this->comebackBonusMobilePopup = ComebackBonusMobilePopup::create();
	this->comebackBonusMobilePopup->retain();
	this->dailyBonusStreak = DailyBonusStreakPopup::create();
	this->dailyBonusStreak->retain();
	this->dailyLuckySpinPopup = DailyLuckySpinPopup::create();
	this->dailyLuckySpinPopup->retain();
	this->dailyChallengePopup = DailyChallengePopup::create();
	this->dailyChallengePopup->retain();
	this->piggyBankPopup = PiggyBankPopup::create();
	this->piggyBankPopup->retain();
	this->mascotNotiPopup = MascotNotificationPopup::create();
	this->mascotNotiPopup->retain();
	this->magicItemPopup = MagicItemPopup::create();
	this->magicItemPopup->retain();
	this->missingPopup = MissingPopup::create();
	this->missingPopup->retain();

	this->specialOfferPopup = SpecialOfferPopup::create();
	this->specialOfferPopup->retain();
	this->starterPackPopup = StarterPackPopup::create();
	this->starterPackPopup->retain();
	this->payToPlayPopup = PayToPlayPopup::create();
	this->payToPlayPopup->retain();
	this->freeToPlayPopup = FreeToPlayPopup::create();
	this->freeToPlayPopup->retain();
	this->getMoreCoinsPopup = GetMoreCoinsPopup::create();
	this->getMoreCoinsPopup->retain();

	this->scratchCardPopup = ScratchCardPopup::create();
	this->scratchCardPopup->retain();
}
void PopupManager::initThingsLoginScene()
{
	//already init
	if (this->loadingAnimation
		|| this->notiLoginPopup)
	{
		return;
	}
	this->loadingAnimation = LoadingAnimation::create();
	this->loadingAnimation->retain();
	this->notiLoginPopup = NotiLoginPopup::create();
	this->notiLoginPopup->setVisible(false);
	this->notiLoginPopup->retain();
}

void PopupManager::reset()
{
	for (int i = 0; i < this->popupQueue->size(); i++)
	{
		if (this->popupQueue->at(i)
			&& !this->popupQueue->at(i)->forceShowAfterReleaseScene)
		{
			CC_SAFE_DELETE(popupQueue->at(i));
			popupQueue->at(i) = nullptr;
			popupQueue->erase(popupQueue->begin() + i);
			i--;
		}
	}

	if (this->notiLoginPopup) {
		this->notiLoginPopup->reset();
	}
	if (this->notificationPopup) {
		this->notificationPopup->reset();
	}
	if (this->profilePopup) {
		this->profilePopup->reset();
	}
	if (this->settingPopup) {
		this->settingPopup->reset();
	}
	if (this->loadingAnimation) {
		this->loadingAnimation->reset();
	}
	if (this->gameUnlockedPopup) {
		this->gameUnlockedPopup->reset();
	}
	if (this->shopPopup) {
		this->shopPopup->reset();
	}
	if (this->levelupPopup) {
		this->levelupPopup->reset();
	}
	if (this->luckyBoxPopup) {
		this->luckyBoxPopup->reset();
	}
	if (this->friendPopup) {
		this->friendPopup->reset();
	}
	if (this->gameSlotInfoPopup) {
		this->gameSlotInfoPopup->reset();
	}
	if (this->changeNamePopup) {
		this->changeNamePopup->reset();
	}
	if (this->addRefereeCodePopup) {
		this->addRefereeCodePopup->reset();
	}
	if (this->achievementPopup) {
		this->achievementPopup->reset();
	}
	if (this->dailyBonusWheelPopup) {
		this->dailyBonusWheelPopup->reset();
	}
	if (this->comebackBonusMobilePopup) {
		this->comebackBonusMobilePopup->reset();
	}
	if (this->dailyBonusStreak) {
		this->dailyBonusStreak->reset();
	}
	if (this->dailyLuckySpinPopup) {
		this->dailyLuckySpinPopup->reset();
	}
	if (this->dailyChallengePopup) {
		this->dailyChallengePopup->reset();
	}
	if (this->piggyBankPopup) {
		this->piggyBankPopup->reset();
	}
	if (this->magicItemPopup) {
		this->magicItemPopup->reset();
	}
	if (this->missingPopup) {
		this->missingPopup->reset();
	}

	if (this->specialOfferPopup) {
		this->specialOfferPopup->reset();
	}
	if (this->starterPackPopup) {
		this->starterPackPopup->reset();
	}
	if (this->payToPlayPopup) {
		this->payToPlayPopup->reset();
	}
	if (this->freeToPlayPopup) {
		this->freeToPlayPopup->reset();
	}
	if (this->getMoreCoinsPopup) {
		this->getMoreCoinsPopup->reset();
	}

	if (this->scratchCardPopup) {
		this->scratchCardPopup->reset();
	}

	this->checkAndShowPopupInQueue();
}

void PopupManager::pushBackShowPopup(BasePopup* popup, cocos2d::Node* parent, bool forceShowAfterReleaseScene)
{
	auto popupQueueStruct = new PopupQueueStruct();
	popupQueueStruct->popup = popup;
	popupQueueStruct->parent = parent;
	popupQueueStruct->forceShowAfterReleaseScene = forceShowAfterReleaseScene;
	popupQueueStruct->previousSceneTag = Helper4Scene::getRunningScene()->getTag();
	popupQueue->push_back(popupQueueStruct);
	checkAndShowPopupInQueue();
}

void PopupManager::popFrontShowPopup(BasePopup * frontPopup, bool popupOnly)
{
	if (this->popupQueue->size() > 0
		&& frontPopup == popupQueue->at(0)->popup)
	{
		CC_SAFE_DELETE(popupQueue->at(0));
		popupQueue->at(0) = nullptr;
		popupQueue->pop_front();
		if (!popupOnly) {
			this->checkAndShowPopupInQueue();
		}
	}
}

bool PopupManager::isPopupInQueue(BasePopup * popup)
{
	for (int i = 0; i < this->popupQueue->size(); i++)
	{
		if(popupQueue->at(i) != nullptr
			&& popupQueue->at(i)->popup == popup)
		{
			return true;
		}
	}
	return false;
}

void PopupManager::checkAndShowPopupInQueue()
{
	if (this->popupQueue->size() > 0
		&& popupQueue->at(0)
		&& popupQueue->at(0)->popup
		&& !popupQueue->at(0)->popup->isVisible()
		&& !popupQueue->at(0)->popup->isShowing())
	{
		if (popupQueue->at(0)->previousSceneTag != Helper4Scene::getRunningScene()->getTag())
		{
			if (popupQueue->at(0)->forceShowAfterReleaseScene)
			{
				popupQueue->at(0)->parent = Helper4Scene::getRunningScene();
				this->popupQueue->at(0)->popup->show(popupQueue->at(0)->parent);
			}
			else
			{
				popFrontShowPopup(popupQueue->at(0)->popup);
			}
		}
		else
		{
			this->popupQueue->at(0)->popup->show(popupQueue->at(0)->parent);
		}
	}
}


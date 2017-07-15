#include "HeaderLobbyLayout.h"
#include "HeaderMagicItemBtn.h"
#include "Scene/LobbyScene.h"
#include "Util/UtilFunction.h"
#include "Custom/Common/LabelAutoSize.h"
#include "Custom/Common/ButtonAdjustClikableAreaSize.h"
#include "Info/AdditionalInfo.h"
#include "Manager/InfoManager.h"
#include "Manager/PopupManager.h"
#include "Manager/NetworkManager.h"
#include "Manager/DownloadImageManager.h"
#include "Manager/ScaleManager.h"
#include "Manager/SoundManager.h"
#include "SlotGame/base/utils/CSpriteButton.h"
#include "SlotGame/base/manager/Manager4Sound.h"

#include "Views/Popup/NotificationPopup.h"
#include "Views/Popup/ProfilePopup.h"
#include "Views/Popup/SettingPopup.h"
#include "Views/Popup/Shop/ShopPopup.h"
#include "Views/Popup/LevelUpPopup.h"
#include "Views/Popup/FriendPopup/FriendPopup.h"
#include "Views/Popup/GameSlotInfoPopup.h"
#include "Views/Popup/MagicItemPopup.h"

#include "Views/Effects/CrownFlareWithLensFlare.h"
#include "Views/Effects/CoinFlare.h"
#include "Views/Effects/CirclePink.h"

#include "Helper/AnimationHelper.h"
#include "Helper/Helper4Sprite.h"

#define RADIUS_CIRCLE_AVATAR 55
#define DISTANCE_BETWEEN_SMALL_BUTTON 50
#define DURATION_ACTION_INCREASE_COIN 0.7f
#define MAX_LENGTH_NAME 14
#define HEADER_SCHEDULE_KEY "header_schedule"
#define INTERVAL_HEADER_SCHEDULE 2 //2s

#define PLAY_COIN_ANIMATION_INTERVAL 180 // 180 second 
#define PLAY_CROWN_ANIMATION_AFTER_COIN_ANIMATION 2 //2second after
USING_NS_CC;
using namespace std;

// on "init" you need to initialize your instance
bool HeaderLobbyLayout::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layout::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	scaleDownRatio = ScaleManager::getInstance()->getExactlyScaleDownRatio();

	auto avatarPos = Vec2::ZERO;

	// create the sprite, which should be clipped
	this->avatarSprite = GameSlot::CSpriteButton::createButtonWithFile(PNG_HEADER_AVATAR_ICON, nullptr, [this]() {
		PopupManager::getInstance()->getProfilePopup()->prepareAndShow(this->getParent());
});
	this->avatarSprite->setScale(RADIUS_CIRCLE_AVATAR  * 2.0f / this->avatarSprite->getContentSize().width);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID && CALL_NATIVE_CROP_AVATAR)
	this->avatarSprite->setPosition(avatarPos);
	this->addChild(avatarSprite);
#else
	//MAKE AVATAR
	auto circleMask = UtilFunction::createCircleMask(RADIUS_CIRCLE_AVATAR);
	circleMask->addChild(this->avatarSprite);
	// add the clipping node to the main node
	this->addChild(circleMask);
#endif

	//DOUBLE EXP PROGRESS BAR
	this->doubleExpBgProgressBar = Sprite::createWithSpriteFrameName(PNG_FRAME_MAGIC_ITEM_BG_DOUBLE_EXP_BAR);
	this->doubleExpBgProgressBar->setPosition(Vec2(avatarPos.x + RADIUS_CIRCLE_AVATAR * 4.6f,
		avatarPos.y - 10));
	this->doubleExpBgProgressBar->setVisible(false);
	this->addChild(this->doubleExpBgProgressBar);

	//PROGESS BAR LEVEL
	bgLevel = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_HEADER_LEVEL_PROGESS_BAR);
	bgLevel->setPosition(Vec2(avatarPos.x + RADIUS_CIRCLE_AVATAR * 4.6f,
		avatarPos.y - 10));
	this->addChild(bgLevel);

	this->levelProgressBar = CCProgressTimer::create(CCSprite::createWithSpriteFrameName(PNG_FRAME_HEADER_LEVEL_MASK_PROGESS_BAR));
	if (this->levelProgressBar != NULL)
	{
		this->levelProgressBar->setType(kCCProgressTimerTypeBar);
		this->levelProgressBar->setMidpoint(ccp(0, 0));
		this->levelProgressBar->setBarChangeRate(ccp(1, 0));
		this->levelProgressBar->setPercentage(100);
		this->levelProgressBar->setPosition(ccp(bgLevel->getContentSize().width / 2, bgLevel->getContentSize().height / 2));
		bgLevel->addChild(this->levelProgressBar);

		//LABEL PROGRESS BAR LEVEL
		this->levelProgressBarLabel = Label::createWithTTF("100%", FONT_PassionOne_Regular, 35);
		this->levelProgressBarLabel->enableShadow();
		this->levelProgressBarLabel->setPosition(this->levelProgressBar->getContentSize().width / 2,
			this->levelProgressBar->getContentSize().height / 2);
		this->levelProgressBar->addChild(this->levelProgressBarLabel);
	}
	//DOUBLE EXP FLARE
	this->doubleExpFlareProgressBar = Sprite::createWithSpriteFrameName(PNG_FRAME_MAGIC_ITEM_FLARE_DOUBLE_EXP_BAR);
	this->doubleExpFlareProgressBar->setVisible(false);
	this->doubleExpFlareProgressBar->setPosition(this->doubleExpBgProgressBar->getPosition()
		+ Vec2(-90, this->doubleExpBgProgressBar->getContentSize().height / 2 - 10)
	);
	this->addChild(this->doubleExpFlareProgressBar);

	//START LEVEL
	auto start = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_HEADER_START_LEVEL_ICON);
	start->setPosition(Vec2(-start->getContentSize().width / 12,
		bgLevel->getContentSize().height / 2 + 5));
	bgLevel->addChild(start);
	//LEVEL LABEL
	this->levelLabel = LabelAutoSize::createWithTTF("1", FONT_PassionOne_Regular, 46);
	this->levelLabel->setTextColor(Color4B::BLACK);
	this->levelLabel->setPosition(Vec2(start->getContentSize().width / 2,
		start->getContentSize().height / 2 - 3));
	((LabelAutoSize*)this->levelLabel)->setTextAreaSize(Size(start->getContentSize().width / 3.0f, start->getContentSize().height / 2.0f));
	start->addChild(this->levelLabel);

	//NAME LABEL
	this->nameLabel = LabelAutoSize::createWithTTF("Anonymus", FONT_PassionOne_Regular, 40);
	((LabelAutoSize*)this->nameLabel)->setAutoFitType(LabelAutoFitType::TrimString);
	((LabelAutoSize*)this->nameLabel)->setTextAreaSize(Size(230, 0));
	this->nameLabel->enableShadow();
	this->nameLabel->setHorizontalAlignment(TextHAlignment::LEFT);
	this->nameLabel->setAnchorPoint(Vec2(0, 0.5f));
	this->nameLabel->setPosition(Vec2(bgLevel->getPosition().x - bgLevel->getContentSize().width / 2.9f-10,
		bgLevel->getPosition().y + 40));
	this->addChild(this->nameLabel);

#pragma region Coin + Show Coin Shop Popup
	//BUY COIN BG
	auto bgBuyCoin = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_HEADER_BUY_COIN_BG);
	bgBuyCoin->setPosition(Vec2(
		this->levelProgressBar->getPosition().x + this->levelProgressBar->getContentSize().width + 170,
		this->levelProgressBar->getPosition().y - 19
		));
	this->addChild(bgBuyCoin);
	//SHOW COIN SHOP BUTTON
	auto showCoinShopButton = ButtonAdjustClikableAreaSize::create(PNG_FRAME_ADDITION_BUTTON, "", "", ui::Widget::TextureResType::PLIST);
	showCoinShopButton->setAnchorClickableAreaSize(Vec2(1, 0.5f));
	showCoinShopButton->setClickableAreaSize(Size(bgBuyCoin->getContentSize().width, bgBuyCoin->getContentSize().height));
	showCoinShopButton->setZoomScale(Configs::BUTTON_ZOOM_SCALE_VALUE);
	bgBuyCoin->addChild(showCoinShopButton);
	showCoinShopButton->setPosition(Vec2(
		bgBuyCoin->getContentSize().width - showCoinShopButton->getContentSize().width / 2 - 5,
		bgBuyCoin->getContentSize().height / 2 + 2
	));
	showCoinShopButton->addTouchEventListener([this](cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
	{
		if (type != cocos2d::ui::Widget::TouchEventType::ENDED) {
			return;
		}
		this->coinFlareAnimation->resetAndPlay(1);
		PopupManager::getInstance()->getShopPopup()->prepareAndShow(
			this->getParent(),
			ShopType::CoinShop
		);
	});
	//COIN LABEL
	this->coinLabel = LabelAutoSize::createWithTTF(UtilFunction::FormatWithCommas(0), FONT_PassionOne_Regular, 52);
	this->coinLabel->setPosition(Vec2(bgBuyCoin->getContentSize().width / 2, bgBuyCoin->getContentSize().height / 2));
	((LabelAutoSize*)this->coinLabel)->setTextAreaSize(Size(bgBuyCoin->getContentSize().width / 2, bgBuyCoin->getContentSize().height));
	bgBuyCoin->addChild(this->coinLabel);

	//ANIMATION COIN
	this->coinFlareAnimation = CoinFlare::create();
	this->coinFlareAnimation->setPosition(35, bgBuyCoin->getContentSize().height / 2);
	bgBuyCoin->addChild(this->coinFlareAnimation);
#pragma endregion

#pragma region Crown + Show Crown Shop Popup
	//BUY CROWN BG
	auto bgBuyCrown = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_HEADER_BUY_CROWN_BG);
	bgBuyCrown->setPosition(Vec2(
		bgBuyCoin->getPosition().x + bgBuyCoin->getContentSize().width + 30,
		bgBuyCoin->getPosition().y + 3
	));
	this->addChild(bgBuyCrown);
	//SHOW CROWN SHOP BUTTON
	auto showCrownShopButton = ButtonAdjustClikableAreaSize::create(PNG_FRAME_ADDITION_BUTTON, "", "", ui::Widget::TextureResType::PLIST);
	showCrownShopButton->setAnchorClickableAreaSize(Vec2(1, 0.5f));
	showCrownShopButton->setClickableAreaSize(Size(bgBuyCrown->getContentSize().width, bgBuyCrown->getContentSize().height));
	showCrownShopButton->setZoomScale(Configs::BUTTON_ZOOM_SCALE_VALUE);
	bgBuyCrown->addChild(showCrownShopButton);
	showCrownShopButton->setPosition(Vec2(
		bgBuyCrown->getContentSize().width - showCrownShopButton->getContentSize().width / 2 - 5,
		bgBuyCrown->getContentSize().height / 2
	));
	showCrownShopButton->addTouchEventListener([this](cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
	{
		if (type != cocos2d::ui::Widget::TouchEventType::ENDED) {
			return;
		}
		this->crownFlareAnimation->resetAndPlay(1);
		PopupManager::getInstance()->getShopPopup()->prepareAndShow(
			this->getParent(),
			ShopType::CrownShop
		);
	});
	//CROWN LABEL
	this->crownLabel = LabelAutoSize::createWithTTF(UtilFunction::FormatWithCommas(0), FONT_PassionOne_Regular, 52);
	this->crownLabel->setPosition(Vec2(bgBuyCrown->getContentSize().width / 2 + 17, bgBuyCrown->getContentSize().height / 2 - 4));
	((LabelAutoSize*)this->crownLabel)->setTextAreaSize(Size(bgBuyCrown->getContentSize().width / 2 - 10, bgBuyCrown->getContentSize().height));
	bgBuyCrown->addChild(this->crownLabel);

	//ANIMATION CROWN
	this->crownFlareAnimation = CrownFlareWithLensFlare::create();
	this->crownFlareAnimation->setRotation(35);
	this->crownFlareAnimation->setPosition(49, bgBuyCrown->getContentSize().height / 2 - 5);
	bgBuyCrown->addChild(this->crownFlareAnimation);
#pragma endregion


#pragma region Buttons Header

	int distanceBetweenButtons = DISTANCE_BETWEEN_SMALL_BUTTON;
	//SETTINGS BUTTON
	this->settingsButton = ButtonAdjustClikableAreaSize::create(PNG_FRAME_HEADER_SETTINGS_BUTTON_HEADER,"","",ui::Widget::TextureResType::PLIST);
	this->settingsButton->setZoomScale(Configs::BUTTON_ZOOM_SCALE_VALUE);
	this->settingsButton->setPosition(Vec2(origin.x*2 + visibleSize.width - 90 - this->settingsButton->getContentSize().width / 2, bgBuyCrown->getPosition().y));
	this->settingsButton->addTouchEventListener(CC_CALLBACK_2(HeaderLobbyLayout::onSettingsTouched, this));
	this->addChild(this->settingsButton);

	//FRIEND BUTTON
	this->friendButton = ButtonAdjustClikableAreaSize::create(PNG_FRAME_HEADER_FRIEND_BUTTON_HEADER,"","",ui::Widget::TextureResType::PLIST);
	this->friendButton->setZoomScale(Configs::BUTTON_ZOOM_SCALE_VALUE);
	this->friendButton->setPosition(Vec2(this->settingsButton->getPosition().x - this->settingsButton->getContentSize().width / 2 - distanceBetweenButtons,
		this->settingsButton->getPosition().y));
	this->friendButton->addTouchEventListener(CC_CALLBACK_2(HeaderLobbyLayout::onFriendTouched, this));
	this->addChild(this->friendButton);

	//BACK HOME BUTTON
	this->backHomeButton = ButtonAdjustClikableAreaSize::create(PNG_FRAME_HEADER_HOME_BUTTON_HEADER,"","",ui::Widget::TextureResType::PLIST);
	this->backHomeButton->setZoomScale(Configs::BUTTON_ZOOM_SCALE_VALUE);
	this->backHomeButton->setPosition(Vec2(this->friendButton->getPosition().x - this->friendButton->getContentSize().width / 2 - distanceBetweenButtons,
		this->friendButton->getPosition().y));
	this->backHomeButton->addTouchEventListener(CC_CALLBACK_2(HeaderLobbyLayout::onBackHomeTouched, this));
	this->addChild(this->backHomeButton);

	//INFO GAME SLOT BUTTON
	this->infoGameSlotButton = ButtonAdjustClikableAreaSize::create(PNG_FRAME_HEADER_INFO_BUTTON_HEADER,"","",ui::Widget::TextureResType::PLIST);
	this->infoGameSlotButton->setZoomScale(Configs::BUTTON_ZOOM_SCALE_VALUE);
	this->infoGameSlotButton->setPosition(Vec2(this->friendButton->getPosition().x, this->friendButton->getPosition().y));
	this->infoGameSlotButton->addTouchEventListener(CC_CALLBACK_2(HeaderLobbyLayout::onInfoGameSlotTouched, this));
	this->addChild(this->infoGameSlotButton);

	//MAGIC ITEM BTN
	this->headerMagicItemBtn = HeaderMagicItemBtn::create();
	this->headerMagicItemBtn->setPosition(this->infoGameSlotButton->getPosition() + Vec2(-190, 0));
	this->headerMagicItemBtn->setScale(0.7f);
	this->headerMagicItemBtn->setZoomScale(Configs::BUTTON_ZOOM_SCALE_VALUE);
	this->headerMagicItemBtn->addTouchEventListener(
		[this](Ref* ref, ui::Widget::TouchEventType touchType) {
		if (touchType != ui::Widget::TouchEventType::ENDED)
		{
			return;
		}
		PopupManager::getInstance()->getMagicItemPopup()->prepareAndShow(this->getParent());
	}
	);
	this->addChild(this->headerMagicItemBtn);

	//ANIMATION CIRCLE PINK
	this->circlePinkAnimation = CirclePink::create();
	this->addChild(circlePinkAnimation);
#pragma endregion

	// scale down by ratio
	this->setScale(scaleDownRatio);

	return true;
}

void HeaderLobbyLayout::onEnter()
{
	Layout::onEnter();
	this->retain();
	PopupManager::getInstance()->setHeaderLobbyLayout(this);

	this->coinLabel->setString("0");
	this->crownLabel->setString("0");
	this->setPosition(Vec2(origin.x + 70 * scaleDownRatio, origin.y + visibleSize.height - 60*scaleDownRatio));

	//reset all animation
	if (this->coinFlareAnimation) this->coinFlareAnimation->reset();
	if (this->crownFlareAnimation) this->crownFlareAnimation->reset();
	if (this->circlePinkAnimation) this->circlePinkAnimation->reset();
	/*Director::getInstance()->getScheduler()->scheduleSelector(
		schedule_selector(HeaderLobbyLayout::headerSchedule),
		Director::getInstance(), 2.0f, false);*/
	Director::getInstance()->getScheduler()->schedule(
		[this](float dt)
	{
		this->headerSchedule(dt);
	}, Director::getInstance(), INTERVAL_HEADER_SCHEDULE, false, HEADER_SCHEDULE_KEY
		);
}
void HeaderLobbyLayout::onExit()
{
	Layout::onExit();
	//PopupManager::getInstance()->setHeaderLobbyLayout(nullptr);
}

void HeaderLobbyLayout::onSettingsTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != ui::Widget::TouchEventType::ENDED) {
		return;
	}
	this->circlePinkAnimation->setPosition(this->settingsButton->getPosition());
	this->circlePinkAnimation->resetAndPlay(1);
	PopupManager::getInstance()->getSettingPopup()->prepareAndShow(
		this->getParent()
	);
}

void HeaderLobbyLayout::onFriendTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != ui::Widget::TouchEventType::ENDED) {
		return;
	}
	/*PopupManager::getInstance()->getNotificationPopup()->showUnfinishJobPopup(
		this->getParent()
	);*/
	this->circlePinkAnimation->setPosition(this->friendButton->getPosition());
	this->circlePinkAnimation->resetAndPlay(1);
	OpenTab openTab = OpenTab::Leaderboard;
	switch (InfoManager::getInstance()->getUserInfo()->role)
	{
	case USER_ROLE::FACEBOOK:
		openTab = OpenTab::Friend;
		break;
	default:
		break;
	}
	PopupManager::getInstance()->getFriendPopup()->prepareAndShow(
		this->getParent(),
		openTab
	);
}

void HeaderLobbyLayout::onBackHomeTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != ui::Widget::TouchEventType::ENDED) {
		return;
	}
	this->gotoLobbyScene();
}

void HeaderLobbyLayout::onInfoGameSlotTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != ui::Widget::TouchEventType::ENDED) {
		return;
	}
	this->circlePinkAnimation->setPosition(this->infoGameSlotButton->getPosition());
	this->circlePinkAnimation->resetAndPlay(1);
	PopupManager::getInstance()->getInfoPopup()->prepareAndShow(this->getParent());
}

void HeaderLobbyLayout::updateAllUIByUserInfo(UserInfo* userInfo, bool isUpdateCoinLabel, bool isUpdateCrownLabel)
{
	DownloadImageManager::getInstance()->loadImageFromCacheOrDownload(
		userInfo->getAvatarURL(),
		[this](cocos2d::Texture2D* texture)
	{
		this->updateAvatar(texture);
	}
	);
	//UPDATE NAME
	this->updateName(userInfo->name);

	//UPDATE LEVEL
	this->updateLevelProcessBar(userInfo->exp_bar);
	this->levelLabel->setString(ToString(userInfo->level + 1));
	//UPDATE COIN+CROWN LABEL
	if (UserDefault::getInstance()->getBoolForKey((STORING_KEY_TUTORIAL_FIRST_LOGIN + ToString(userInfo->id)).c_str(), false)) return;
	if (isUpdateCoinLabel)
	{
		this->coinLabel->setString(UtilFunction::FormatWithCommas(userInfo->coin));
	}
	if (isUpdateCrownLabel)
	{
		this->crownLabel->setString(UtilFunction::FormatWithCommas(userInfo->crown));
	}
}

void HeaderLobbyLayout::initButtonsBaseOnCurrentScene(ppEnum::GameScene scene)
{
	switch (scene)
	{
		//Lobby or luckywheel scene
	case ppEnum::GameScene::Lobby:
	{
		this->friendButton->setVisible(true);
		this->backHomeButton->setVisible(false);
		this->infoGameSlotButton->setVisible(false);
		this->hideMagicItemBtn();
		break;
	}
	case ppEnum::GameScene::LuckyWheel:
	{
		this->friendButton->setVisible(false);
		this->backHomeButton->setPosition(this->friendButton->getPosition());
		this->backHomeButton->setVisible(true);
		this->infoGameSlotButton->setVisible(false);
		this->hideMagicItemBtn();
		break;
	}
	//GAME SLOTS
	default:
	{
		this->friendButton->setVisible(false);
		this->backHomeButton->setPosition(Vec2(this->friendButton->getPosition().x - this->friendButton->getContentSize().width / 2 - DISTANCE_BETWEEN_SMALL_BUTTON,
			this->friendButton->getPosition().y));
		this->backHomeButton->setVisible(true);
		this->infoGameSlotButton->setVisible(true);
		auto currentActivateMGItem = InfoManager::getInstance()->getAdditionalInfo()->magicItemInfo->activeMagicItemType;
		this->showMagicItemBtn(static_cast<LobbyConstant::MagicItemType>(currentActivateMGItem));
		break;
	}
	}
}

void HeaderLobbyLayout::runAnimationIncrease(double numberIncrease, cocos2d::Label* label)
{
	double currentValueInUI = UtilFunction::getDoubleByFormatWithCommas(label->getString());
	if (!label->getNumberOfRunningActions())
	{
		auto actionIcreaseCoin = ActionFloat::create(
			DURATION_ACTION_INCREASE_COIN,
			currentValueInUI,
			currentValueInUI + numberIncrease,
			[label](double value) {
			label->setString(UtilFunction::FormatWithCommas(value));
		}
		);
		label->runAction(actionIcreaseCoin);
	}
}

void HeaderLobbyLayout::reloadWithReloadUIInfo(ReloadUIInfo * reloadUIInfo)
{
	auto callback = reloadUIInfo->callback;
	auto isRunAnimationIncreaseCoin = reloadUIInfo->isRunAnimationIncreaseCoin;
	auto isRunAnimationIncreaseCrown = reloadUIInfo->isRunAnimationIncreaseCrown;
	CC_SAFE_DELETE(reloadUIInfo);
	this->isReloadingInfoAndUI = true;

	long oldLevel = InfoManager::getInstance()->getUserInfo()->level;

	//CALLBACK UPDATE UI INFO
	auto updateUIInfo = [this, oldLevel, isRunAnimationIncreaseCoin, isRunAnimationIncreaseCrown](UserInfo* newUserInfo)
	{
	double oldCoin = this->nextCoin;//InfoManager::getInstance()->getUserInfo()->coin;
	long oldCrown = this->nextCrown;//InfoManager::getInstance()->getUserInfo()->crown;
	LevelUpInfo* levelUpInfo = nullptr;
	if (newUserInfo->level > oldLevel)
	{
		double coinRewardFromLevelUp = 0;
		long crownRewardFromLevelUp = 0;
		UtilFunction::calculateCrownAndCoinBonusWhenLevelUp(coinRewardFromLevelUp, crownRewardFromLevelUp, oldLevel, newUserInfo->level);
		//Subtract coin and crown level up
		if (newUserInfo->coin - coinRewardFromLevelUp >= 0)
		{
			newUserInfo->coin -= coinRewardFromLevelUp;
		}
		if (newUserInfo->crown - crownRewardFromLevelUp >= 0)
		{
			newUserInfo->crown -= crownRewardFromLevelUp;
		}
		//SHOW POPUP LEVEL HERE
		levelUpInfo = new LevelUpInfo(oldLevel, newUserInfo->level, coinRewardFromLevelUp, crownRewardFromLevelUp);
	}
	//if is run animation = true -> don't need update coin and vice versa
	this->updateAllUIByUserInfo(InfoManager::getInstance()->getUserInfo(), !isRunAnimationIncreaseCoin, !isRunAnimationIncreaseCrown);
	this->increaseCoin(newUserInfo->coin - oldCoin, isRunAnimationIncreaseCoin);
	this->increaseCrown(newUserInfo->crown - oldCrown, isRunAnimationIncreaseCrown);
	return levelUpInfo;
	};

	InfoManager::getInstance()->reloadUserInfo(
		[updateUIInfo, callback, this](bool isSuccess, UserInfo* newUserInfo)
	{
		if (isSuccess) {
			auto levelUpInfo = updateUIInfo(newUserInfo);
			if (callback) callback(isSuccess, levelUpInfo);
			CC_SAFE_DELETE(levelUpInfo);
		}
		else if (callback) callback(isSuccess, nullptr);

		this->isReloadingInfoAndUI = false;
		this->reloadUIInfoQueue.erase(this->reloadUIInfoQueue.begin());
		if (this->reloadUIInfoQueue.size() > 0)
		{
			this->reloadWithReloadUIInfo(this->reloadUIInfoQueue[0]);
		}
	}
	);
}

void HeaderLobbyLayout::headerSchedule(float dt)
{
	//magic items
	int magicItemType = InfoManager::getInstance()->getAdditionalInfo()->magicItemInfo->activeMagicItemType;
	bool isTurnOffMagicItem = false;
	switch (magicItemType)
	{
	case LobbyConstant::MAGIC_ITEM_TYPE_100_PERCENT_BIG_WIN:
		isTurnOffMagicItem = InfoManager::getInstance()->getAdditionalInfo()->magicItemInfo->remainingSpinOfMagicItem100PercentBigWin <= 0;
		break;
	case LobbyConstant::MAGIC_ITEM_TYPE_100_PERCENT_MEGA_WIN:
		isTurnOffMagicItem = InfoManager::getInstance()->getAdditionalInfo()->magicItemInfo->remainingSpinOfMagicItem100PercentMegaWin <= 0;
		break;
	case LobbyConstant::MAGIC_ITEM_TYPE_LUCKY_SPIN_TYPE_1:
		isTurnOffMagicItem = InfoManager::getInstance()->getAdditionalInfo()->magicItemInfo->remainingSpinOfMagicItemLuckySpinType1 <= 0;
		break;
	case LobbyConstant::MAGIC_ITEM_TYPE_LUCKY_SPIN_TYPE_2:
		isTurnOffMagicItem = InfoManager::getInstance()->getAdditionalInfo()->magicItemInfo->remainingSpinOfMagicItemLuckySpinType2 <= 0;
		break;
	case LobbyConstant::MAGIC_ITEM_TYPE_DOUBLE_EXP:
		InfoManager::getInstance()->getAdditionalInfo()->magicItemInfo->remainingTimeOfMagicItemDoubleExp -= (dt * 1000);
		isTurnOffMagicItem = InfoManager::getInstance()->getAdditionalInfo()->magicItemInfo->remainingTimeOfMagicItemDoubleExp <= 0;
		break;
	case LobbyConstant::MAGIC_ITEM_TYPE_LUCKY_SYMBOL:
		InfoManager::getInstance()->getAdditionalInfo()->magicItemInfo->remainingTimeOfMagicItemLuckySymbol -= (dt * 1000);
		isTurnOffMagicItem = InfoManager::getInstance()->getAdditionalInfo()->magicItemInfo->remainingTimeOfMagicItemLuckySymbol <= 0;
		break;
	default:
		isTurnOffMagicItem = true;
		break;
	}
	if (isTurnOffMagicItem) {
		InfoManager::getInstance()->getAdditionalInfo()->magicItemInfo->activeMagicItemType = LobbyConstant::MAGIC_ITEM_TYPE_DEFAULT;
		this->hideMagicItemBtn();
	}

	//coin + crown icon animation lens flare
	this->deltaTimeRunCoinFlareAnimation += dt;
	if (deltaTimeRunCoinFlareAnimation >= PLAY_COIN_ANIMATION_INTERVAL)
	{
		this->coinFlareAnimation->resetAndPlay(1);
		this->scheduleOnce([this](float dt)
		{
			this->crownFlareAnimation->resetAndPlay(1);
		}, PLAY_CROWN_ANIMATION_AFTER_COIN_ANIMATION, "run_animation_crown_header");
		this->deltaTimeRunCoinFlareAnimation = 0;
	}
}

void HeaderLobbyLayout::checkAndShowEffectDoubleExpProgressBar()
{
	if(InfoManager::getInstance()->getAdditionalInfo()->magicItemInfo->activeMagicItemType == LobbyConstant::MagicItemType::MAGIC_ITEM_TYPE_DOUBLE_EXP)
	{
		this->doubleExpBgProgressBar->setVisible(true);
		this->doubleExpBgProgressBar->stopAllActions();
		this->doubleExpBgProgressBar->setOpacity(0);

		this->doubleExpFlareProgressBar->setVisible(true);
		this->doubleExpFlareProgressBar->stopAllActions();
		this->doubleExpFlareProgressBar->setOpacity(0);
		this->doubleExpFlareProgressBar->setRotation(0);
		this->doubleExpFlareProgressBar->setPosition(this->doubleExpBgProgressBar->getPosition()
			+ Vec2(-90, this->doubleExpBgProgressBar->getContentSize().height / 2 - 10)
		);

		this->doubleExpBgProgressBar->runAction(
			RepeatForever::create(
				Sequence::create(
					FadeIn::create(0.7f),
					DelayTime::create(0.1f),
					FadeOut::create(0.7f),
					nullptr
				)
			)
		);
		this->doubleExpFlareProgressBar->runAction(
			RepeatForever::create(
				Sequence::create(
					FadeIn::create(0.6f),
					DelayTime::create(0.3f),
					FadeOut::create(0.6f),
					nullptr
				)
			));
		this->doubleExpFlareProgressBar->runAction(
			RepeatForever::create(
				Sequence::createWithTwoActions(
					MoveBy::create(1.5f, Vec2(190, 0)),
					MoveBy::create(0, Vec2(-190, 0))
				)
			)
		);

		this->doubleExpFlareProgressBar->runAction(
			RepeatForever::create(
				Sequence::createWithTwoActions(
					RotateBy::create(1.5f, 200),
					RotateBy::create(0, -200)
				)
			)
		);

	}
	else
	{
		this->doubleExpBgProgressBar->setVisible(false);
		this->doubleExpFlareProgressBar->setVisible(false);
	}
}

void HeaderLobbyLayout::gotoLobbyScene()
{
	GameSlot::Manager4Sound::getInstance()->turnOffAllSound();
	Director::getInstance()->replaceScene(
		TransitionFade::create(
			Configs::TIME_TRANSITION_FADE_SCENE,
			LobbyScene::createScene(ppEnum::GameScene::GameSlot)
		)
	);
}

void HeaderLobbyLayout::setCoin(double coin)
{
	this->coinLabel->stopAllActions();

	this->nextCoin = coin;
	this->coinLabel->setString(UtilFunction::FormatWithCommas(this->nextCoin));
}

void HeaderLobbyLayout::setCrown(double crown)
{
	this->crownLabel->stopAllActions();

	this->nextCrown = crown;
	this->coinLabel->setString(UtilFunction::FormatWithCommas(this->nextCrown));
}

double HeaderLobbyLayout::getCoinInHeaderUI()
{
	return UtilFunction::getDoubleByFormatWithCommas(this->coinLabel->getString());
}

long HeaderLobbyLayout::getCrownInHeaderUI()
{
	return UtilFunction::getDoubleByFormatWithCommas(this->crownLabel->getString());
}

void HeaderLobbyLayout::onChangeScene(ppEnum::GameScene scene)
{
	//set buttons
	this->initButtonsBaseOnCurrentScene(scene);

	//reset
	this->nextCoin = InfoManager::getInstance()->getUserInfo()->coin;
	this->nextCrown = InfoManager::getInstance()->getUserInfo()->crown;


	//UPDATE ALL UI (update from old data then call to server to reload
	this->updateAllUIByUserInfo(InfoManager::getInstance()->getUserInfo());
	InfoManager::getInstance()->reloadUserInfo([this](bool isSuccess, UserInfo* userInfo)
	{
		this->updateAllUIByUserInfo(userInfo);
	});
}

void HeaderLobbyLayout::hightLightExpBar(double gainedEXP)
{
	this->bgLevel->runAction(
		Sequence::create(
			//CallFunc::create([this, gainedEXP]() {
			//	auto userInfo = InfoManager::getInstance()->getUserInfo();
			//	auto expBar = min(1.0, userInfo->exp_bar + gainedEXP * (1 - userInfo->exp_bar) / userInfo->remainingExp) * 100;
			//	this->levelProgressBar->setPercentage(expBar);
			//	this->levelProgressBarLabel->setString(ToString((int)expBar) + "%");
			//	//this->levelProgressBar
			//}),		
			ScaleTo::create(0.1f, 1.1f),
			DelayTime::create(0.05f),
			ScaleTo::create(0.1f, 1.0f),
			NULL
		));
}

void HeaderLobbyLayout::showMagicItemBtn(LobbyConstant::MagicItemType magicItemType)
{
	if (magicItemType != LobbyConstant::MagicItemType::MAGIC_ITEM_TYPE_DEFAULT)
	{
		this->headerMagicItemBtn->changeItemType(magicItemType);
		this->headerMagicItemBtn->setVisible(true);
		this->checkAndShowEffectDoubleExpProgressBar();
	}
	else
	{
		this->hideMagicItemBtn();
	}
}

void HeaderLobbyLayout::hideMagicItemBtn()
{
	this->headerMagicItemBtn->setVisible(false);
	this->doubleExpBgProgressBar->setVisible(false);
	this->doubleExpFlareProgressBar->setVisible(false);
}

void HeaderLobbyLayout::updateAvatar(cocos2d::Texture2D* texture)
{
	this->avatarSprite->setTexture(texture);
}

void HeaderLobbyLayout::updateName(std::string newName)
{
	UtilFunction::detectFontAndSetStringForLabel(this->nameLabel, FONT_PassionOne_Regular, 
		newName);
}

void HeaderLobbyLayout::updateLevelProcessBar(float percent, bool isRunAnimation)
{
	if (isRunAnimation){
		float duration = 0.2f;
		this->levelProgressBar->runAction(
			ProgressFromTo::create(duration, 
				this->levelProgressBar->getPercentage(),
				percent * 100));
	}
	else {
		this->levelProgressBar->setPercentage(percent * 100);
	}
	this->levelProgressBarLabel->setString(ToString((int)(percent * 100)) + "%");
}

void HeaderLobbyLayout::increaseCoin(double increment, bool isRunAnimation)
{
	if (increment == 0) {
		return;
	}
	this->coinLabel->stopAllActions();
	if (increment > 0)
	{
		SoundManager::getInstance()->playSoundEffectIncreaseCoin();
	}
	else
	{
		SoundManager::getInstance()->playSoundEffectDecreaseCoin();
	}
	if (this->nextCoin > 0)
	{
		this->coinLabel->setString(UtilFunction::FormatWithCommas(this->nextCoin));
	}
	this->nextCoin = getCoinInHeaderUI() + increment;
	if (isRunAnimation)
	{
		runAnimationIncrease(increment, this->coinLabel);
	}
	else
	{
		this->coinLabel->setString(UtilFunction::FormatWithCommas(this->nextCoin));
	}
}

bool HeaderLobbyLayout::decreaseCoin(double decrement, bool isRunAnimation)
{
	if (getCoinInHeaderUI() - decrement < 0) {
		return false;
	}
	this->increaseCoin(-decrement, isRunAnimation);
	return true;
}

void HeaderLobbyLayout::increaseCrown(double increment, bool isRunAnimation)
{
	if (increment == 0) {
		return;
	}
	this->crownLabel->stopAllActions();
	if (this->nextCrown > 0)
	{
		this->crownLabel->setString(UtilFunction::FormatWithCommas(this->nextCrown));
	}
	this->nextCrown = UtilFunction::getDoubleByFormatWithCommas(this->crownLabel->getString()) + increment;
	if (isRunAnimation)
	{
		runAnimationIncrease(increment, this->crownLabel);
	}
	else
	{
		this->crownLabel->setString(UtilFunction::FormatWithCommas(this->nextCrown));
	}
}
bool HeaderLobbyLayout::decreaseCrown(double decrement, bool isRunAnimation)
{
	if (UtilFunction::getDoubleByFormatWithCommas(this->crownLabel->getString()) - decrement < 0) {
		return false;
	}
	this->increaseCrown(-decrement, isRunAnimation);
	return true;
}

void HeaderLobbyLayout::reloadUIHeaderAndCheckShowPopupLevelUp(std::function<void(bool isSuccess, LevelUpInfo* levelUpInfo)> callback, bool isRunAnimationIncreaseCoin, bool isRunAnimationIncreaseCrown)
{
	auto reloadInfo = new ReloadUIInfo(callback, isRunAnimationIncreaseCoin, isRunAnimationIncreaseCrown);
	this->reloadUIInfoQueue.push_back(reloadInfo);
	if (!this->isReloadingInfoAndUI)
	{
		this->reloadWithReloadUIInfo(reloadInfo);
	}
}
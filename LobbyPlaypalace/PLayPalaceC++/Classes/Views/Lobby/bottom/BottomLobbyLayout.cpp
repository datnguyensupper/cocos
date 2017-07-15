#include "BottomLobbyLayout.h"
#include "Scene/LobbyScene.h"
#include "Custom/Common/ButtonAdjustClikableAreaSize.h"
#include "Manager/LanguageManager.h"
#include "Manager/PopupManager.h"
#include "Manager/InfoManager.h"
#include "Manager/NetworkManager.h"
#include "Manager/ScaleManager.h"
#include "Views/Lobby/body/BodyLobbyLayout.h"
#include "Views/Popup/NotificationPopup.h"
#include "Views/Popup/FriendPopup/FriendPopup.h"
#include "Views/Popup/Achievement/AchievementPopup.h"
#include "Views/Popup/DailyLuckySpin/DailyLuckySpinPopup.h"
#include "Views/Popup/DailyChallengePopup.h"
#include "Views/Popup/MascotNotificationPopup.h"
#include "Views/Popup/PiggyBankPopup.h"
#include "Views/Lobby/bottom/BottomItem.h"
#include "Custom/Common/ReuseItemListView_Horizontal.h"
#include "Custom/Common/ReuseItemListView_Vertical.h"

#include "Helper/Helper4Scene.h"
#include "Helper/Helper4Sprite.h"

USING_NS_CC;
using namespace std;

#define X_OFFSET_ITEMS -560
#define X_DISTANCE 10
#define X_SPEED 100

BottomLobbyLayout* BottomLobbyLayout::create(LobbyScene* parent)
{
	auto layer = BottomLobbyLayout::create();
	layer->lobbyScene = parent;
	return layer;
}
// on "init" you need to initialize your instance
bool BottomLobbyLayout::init()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PNG_BOTTOM_PLIST);
	//////////////////////////////
	// 1. super init first
	if (!Layout::init())
	{
		return false;
	}


	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->setPosition(Vec2(visibleSize.width / 2 + origin.x, origin.y));

	float scaleDownRatio = ScaleManager::getInstance()->getExactlyScaleDownRatio();
	// background
	auto bgBottom = Sprite::createWithSpriteFrameName(FRAME_BOTTOM_BG);
	bgBottom->setScaleX(scaleDownRatio);
	bgBottom->setAnchorPoint(Vec2(0.5, 0));
	bgBottom->setPositionY(-15);
	this->addChild(bgBottom);

	this->initItems();

	// background
	auto bgMask = Sprite::createWithSpriteFrameName(FRAME_BOTTOM_BG_MASK);
	bgMask->setScaleX(scaleDownRatio);
	bgMask->setAnchorPoint(Vec2(0.5, 0));
	bgMask->setPositionX(5);
	this->addChild(bgMask);

	this->achievements = this->createSideButton(
		Vec2(-bgBottom->getContentSize().width*scaleDownRatio / 2.45f, 35),
		Vec2((-bgBottom->getContentSize().width / 2.45f - 90) * scaleDownRatio, 70),
		LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::FOOTER_ACHIEVEMENT_LABLE),
		CC_CALLBACK_2(BottomLobbyLayout::onBtnAchievementClicked, this)
	);
	this->achievements.btn->setScale(scaleDownRatio + (1-scaleDownRatio)/2);
	this->achievements.noti->setScale(scaleDownRatio + (1 - scaleDownRatio) / 2);
	this->achievements.notiLabel->setScale(scaleDownRatio + (1 - scaleDownRatio) / 2);

	this->gifts = this->createSideButton(
		Vec2(-this->achievements.btn->getPosition().x, this->achievements.btn->getPosition().y),
		Vec2(-this->achievements.noti->getPosition().x, this->achievements.noti->getPosition().y),
		LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::FOOTER_GIFT_LABLE),
		CC_CALLBACK_2(BottomLobbyLayout::onBtnGiftClicked, this)
	);
	this->gifts.btn->setScale(scaleDownRatio + (1 - scaleDownRatio) / 2);
	this->gifts.noti->setScale(scaleDownRatio + (1 - scaleDownRatio) / 2);
	this->gifts.notiLabel->setScale(scaleDownRatio + (1 - scaleDownRatio) / 2);


	LanguageManager::getInstance()->pushBackToUpdateLanguageList(this);
	updateAfterChangeLanguage();

	return true;
}

void BottomLobbyLayout::onEnter()
{
	Layout::onEnter();
	this->retain();
	PopupManager::getInstance()->setBottomLobbyLayout(this);

	for (auto item : _aItems) {
		((BottomItem*)item)->playAnimation();
	}

	this->bAutoScroll = true;

	this->scheduleUpdate();

	this->updateNotificationAchievements(0);
	this->updateNotificationGifts({});

	time4ReloadNotificationGifts = Configs::TIME_4_RELOADING_BOTTOM;
	this->updateNotificationGiftsFromSV();
	this->updateNotificationAchievementsFromSV();


	//this->setVisible(false);
}

SideOptionUI BottomLobbyLayout::createSideButton(
	const cocos2d::Vec2& posBtn,
	const cocos2d::Vec2& posNoti,
	const std::string& text,
	const std::function<void(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType touchType)>& cb)
{
	//create button show popup achievement
	auto btn = ButtonAdjustClikableAreaSize::create();
	btn->setAnchorClickableAreaSize(Vec2(0.5, 0.5));
	btn->setClickableAreaSize(Size(250, 150));
	btn->setTouchEnabled(true);
	btn->setPosition(Vec2(posBtn));
	btn->addTouchEventListener(cb);
	//BONUS Open Popup noti
	auto labelBtn = Label::createWithTTF(
		text,
		FONT_PassionOne_Regular,
		30
	);
	UtilFunction::setLabelFontByLanguage(labelBtn);
	btn->setTitleLabel(labelBtn);

	labelBtn->enableShadow();
	labelBtn->setTextColor(Color4B::WHITE);
	labelBtn->setPosition(0, 0);
	labelBtn->setZOrder(1);


	auto notiBG = Helper4Sprite::createOptimizeSprite(PNG_BOTTOM_NOTI_GREEN);
	notiBG->setPosition(posNoti);

	auto labelNumberOfNoti = Label::createWithTTF(
		"0",
		FONT_PassionOne_Bold,
		35
	);
	labelNumberOfNoti->setAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);
	labelNumberOfNoti->setPosition(notiBG->getContentSize() / 2);
	labelNumberOfNoti->setTextColor(Color4B::WHITE);
	notiBG->addChild(labelNumberOfNoti);

	this->addChild(btn);
	this->addChild(notiBG);

	SideOptionUI sideOption;
	sideOption.noti = notiBG;
	sideOption.notiLabel = labelNumberOfNoti;
	sideOption.btn = btn;

	return sideOption;
}

void BottomLobbyLayout::initItems()
{

	float scaleDownRatio = ScaleManager::getInstance()->getExactlyScaleDownRatio();

	freeCoinGiftItem = FreeCoinGiftItem::create();
	this->_aItems.push_back(freeCoinGiftItem);
	auto luckyWheel = BottomItem::create(FRAME_BOTTOM_LW_ANIM_FORMAT, 0, 38, FRAME_BOTTOM_LW_TEXT, CC_CALLBACK_1(BottomLobbyLayout::onLuckyWheel, this));
	luckyWheel->setElementsPos(
		luckyWheel->getSpriteSymbol()->getPosition() + Vec2(5, 0),
		luckyWheel->getSpriteLabel()->getPosition() + Vec2(20, 0));
	auto luckySpin = BottomItem::create(FRAME_BOTTOM_LS_ANIM_FORMAT, 0, 44, FRAME_BOTTOM_LS_TEXT, CC_CALLBACK_1(BottomLobbyLayout::onLuckySpin, this));
	luckySpin->setElementsPos(
		luckySpin->getSpriteSymbol()->getPosition() - Vec2(12, 0),
		luckySpin->getSpriteLabel()->getPosition() + Vec2(16, 0));
	this->luckyBox = BottomItem::create(FRAME_BOTTOM_LB_ANIM_FORMAT, 0, 59, FRAME_BOTTOM_LB_TEXT, CC_CALLBACK_1(BottomLobbyLayout::onLuckyBox, this), false, true);
	auto dailyChallenge = BottomItem::create(FRAME_BOTTOM_DC_ANIM_FORMAT, 0, 44, FRAME_BOTTOM_DC_TEXT, CC_CALLBACK_1(BottomLobbyLayout::onDailyChallenge, this), true);
	dailyChallenge->setElementsPos(
		dailyChallenge->getSpriteSymbol()->getPosition() - Vec2(15, 0),
		dailyChallenge->getSpriteLabel()->getPosition() + Vec2(5, 0));
	auto piggyBank = BottomItem::create(FRAME_BOTTOM_PB_ANIM_FORMAT, 0, 45, FRAME_BOTTOM_PB_TEXT, CC_CALLBACK_1(BottomLobbyLayout::onPiggyBank, this), true);
	piggyBank->setElementsPos(
		piggyBank->getSpriteSymbol()->getPosition() - Vec2(5, 0),
		piggyBank->getSpriteLabel()->getPosition() + Vec2(5, 0));

	this->_aItems.push_back(luckyWheel);
	this->_aItems.push_back(luckySpin);
	this->_aItems.push_back(luckyBox);
	this->_aItems.push_back(dailyChallenge);
	this->_aItems.push_back(piggyBank);
	//LIST CELL LIST VIEW 
	auto width = this->_aItems[0]->getContentSize().width;
	auto size = this->_aItems.size() * 2;

	bottomScrollView = ReuseItemListView_Horizontal::create();
	bottomScrollView->setPosition(Vec2(
		X_OFFSET_ITEMS*scaleDownRatio,
		-20
	));
	bottomScrollView->setScrollBarEnabled(false);
	bottomScrollView->setCascadeOpacityEnabled(true);
	bottomScrollView->setContentSize(Size(
		4.6f * width,
		150));


	bottomScrollView->initWithNewData(this->_aItems, size, width, X_DISTANCE, width + X_DISTANCE + 5);
	bottomScrollView->setSelectedItemEventScrollViewCallback(CC_CALLBACK_2(BottomLobbyLayout::onScroll, this));
	bottomScrollView->setSelectedItemEventCallback(CC_CALLBACK_2(BottomLobbyLayout::onItemSelected, this));
	bottomScrollView->setInfinity(true);
	bottomScrollView->setClippingEnabled(false);


	auto clipper = ClippingNode::create();

	auto stencil = DrawNode::create();
	
	Vec2* p = new Vec2[4];
	p[0] = Vec2(X_OFFSET_ITEMS*scaleDownRatio, 0);
	p[1] = Vec2((X_OFFSET_ITEMS + 80) * scaleDownRatio, 200);
	p[2] = Vec2((X_OFFSET_ITEMS + bottomScrollView->getContentSize().width - 80)* scaleDownRatio, 200);
	p[3] = Vec2((X_OFFSET_ITEMS + bottomScrollView->getContentSize().width)*scaleDownRatio, 0);

	stencil->drawSolidPoly(p, 4, Color4F::WHITE);

	clipper->setStencil(stencil);

	clipper->addChild(bottomScrollView);

	this->addChild(clipper);
}

void BottomLobbyLayout::update(float delta) {
	if (this->bAutoScroll) {
		timeNotAutoScroll = 0;
		this->bottomScrollView->autoScroll(-X_SPEED * delta);
	}
	else {
		timeNotAutoScroll += delta;
		if (timeNotAutoScroll >= 5) this->bAutoScroll = true;
	}

	// auto update gift and archievement
	if (time4ReloadNotificationGifts <= 0) {
		if (time4ReloadNotificationGifts < 0) {
			time4ReloadNotificationGifts = 0;
			updateNotificationGiftsFromSV();
			updateNotificationAchievementsFromSV();
		}
	}else {
		time4ReloadNotificationGifts -= delta;
		if (time4ReloadNotificationGifts <= 0) time4ReloadNotificationGifts = -1;
	}

}

void BottomLobbyLayout::updateNotificationAchievements(int numberOfAchievements) {
	if (numberOfAchievements == 0) {
		// hide achievement noti
		this->achievements.noti->setVisible(false);
	}
	else {
		// show achievement noti
		this->achievements.noti->setVisible(true);
		this->achievements.notiLabel->setString(ToString(numberOfAchievements));
	}
}

void BottomLobbyLayout::updateNotificationGifts(const std::vector<GiftInfo*>& result) {
	int numberOfGifts = result.size();
	if (numberOfGifts == 0) {
		// hide achievement noti
		this->gifts.noti->setVisible(false);
	}
	else {
		// show achievement noti
		this->gifts.noti->setVisible(true);
		this->gifts.notiLabel->setString(ToString(numberOfGifts));
	}

	int luckyBoxNoti = 0;
	for (auto gift : result) {
		if (gift->type == LobbyConstant::GiftType::GIFT_TYPE_LUCKY_BOX_1 ||
			gift->type == LobbyConstant::GiftType::GIFT_TYPE_LUCKY_BOX_2 ||
			gift->type == LobbyConstant::GiftType::GIFT_TYPE_LUCKY_BOX_3)
			luckyBoxNoti++;
	}
	this->luckyBox->reloadNoti(luckyBoxNoti);
}

void BottomLobbyLayout::updateNotificationAchievementsFromSV()
{
	InfoManager::getInstance()->reloadAchievementInfo(
		[this](bool isSucess, AchievementInfo *result){

		time4ReloadNotificationGifts = Configs::TIME_4_RELOADING_BOTTOM;
		if (!isSucess)
			return;
		this->updateNotificationAchievements(result->getTotalCollectableAchievement());
	});
}

void BottomLobbyLayout::updateNotificationGiftsFromSV()
{
	InfoManager::getInstance()->reloadGiftInfoList(
		[this](bool isSucess, std::vector<GiftInfo*> result){

		time4ReloadNotificationGifts = Configs::TIME_4_RELOADING_BOTTOM;
		if (!isSucess) {
			return;
		}
		this->updateNotificationGifts(result);
	}
	);
}

void BottomLobbyLayout::onBtnAchievementClicked(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType touchType) {
	if (touchType != ui::Widget::TouchEventType::ENDED) {
		return;
	}
	/*PopupManager::getInstance()->getNotificationPopup()->showUnfinishJobPopup(
		this->getParent()
	);*/
	PopupManager::getInstance()->getAchievementPopup()->prepareAndShow(
		this->getParent()
	);
}

void BottomLobbyLayout::onBtnGiftClicked(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType touchType) {
	if (touchType != ui::Widget::TouchEventType::ENDED) {
		return;
	}
	/*PopupManager::getInstance()->getNotificationPopup()->showUnfinishJobPopup(
		this->getParent()
	);*/
	PopupManager::getInstance()->getFriendPopup()->prepareAndShow(
		this->getParent(),
		OpenTab::Inbox
	);
}

void BottomLobbyLayout::onItemSelected(cocos2d::Ref * sender, cocos2d::ui::ListView::EventType type)
{
	if (type == ui::ListView::EventType::ON_SELECTED_ITEM_END) {
		auto item = (BottomItem*)this->bottomScrollView->getRealItem(this->bottomScrollView->getCurSelectedIndex());
		item->onSelected();
		this->bAutoScroll = false;

		this->stopAllActions();
		auto action = Sequence::createWithTwoActions(
			DelayTime::create(delayTime4StopScrollBottom),
			CallFunc::create([this]() {
			this->bAutoScroll = true;
		}));
		action->setTag(1);
		this->runAction(action);
	}
}

void BottomLobbyLayout::onScroll(cocos2d::Ref * pSender, cocos2d::ui::ScrollView::EventType type)
{
	if (type == ui::ScrollView::EventType::SCROLLING) this->bAutoScroll = false;
	else if(type == ui::ScrollView::EventType::AUTOSCROLL_ENDED && !this->getActionByTag(1)){
		this->stopAllActions();
		auto action = Sequence::createWithTwoActions(
			DelayTime::create(delayTime4StopScrollBottom),
			CallFunc::create([this]() {
			this->bAutoScroll = true;
		}));
		action->setTag(1);
		this->runAction(action);
	}
}

void BottomLobbyLayout::onLuckyWheel(BottomItem* sender)
{
	/*PopupManager::getInstance()->getNotificationPopup()->showUnfinishJobPopup(
		this->getParent()
	);
	return;
	sender->showLock();*/
	((BaseScene*)Helper4Scene::getRunningScene())->gotoLuckyWheelScene(0);
}

void BottomLobbyLayout::onLuckySpin(BottomItem* sender)
{
	/*PopupManager::getInstance()->getNotificationPopup()->showUnfinishJobPopup(
		this->getParent()
	);
	return;
	sender->showLock();*/
	PopupManager::getInstance()->getDailyLuckySpinPopup()->prepareAndShow(this->getParent());
}

void BottomLobbyLayout::onLuckyBox(BottomItem* sender)
{
	/*PopupManager::getInstance()->getNotificationPopup()->showUnfinishJobPopup(
		this->getParent()
	);
	return;
	sender->showLock();*/
	PopupManager::getInstance()->getFriendPopup()->prepareAndShow(this->getParent(), OpenTab::Inbox);
}

void BottomLobbyLayout::onDailyChallenge(BottomItem* sender)
{
	/*PopupManager::getInstance()->getNotificationPopup()->showUnfinishJobPopup(
		this->getParent()
	);
	return;*/

	if (InfoManager::getInstance()->getUserInfo()->level + 1 >= InfoManager::getInstance()->getUnlockFeatureByLevelConfig().dailyChallenge) {
		PopupManager::getInstance()->getDailyChallengePopup()->prepareAndShow(this->getParent());
	}
	else {
		sender->showLock();
		PopupManager::getInstance()->getMascotNotificationPopup()->show(
			this->getParent(),
			"You need to reach level " + ToString(InfoManager::getInstance()->getUnlockFeatureByLevelConfig().dailyChallenge) + " to unlock this feature!"
		);
	}
}

void BottomLobbyLayout::onPiggyBank(BottomItem* sender)
{
	/*PopupManager::getInstance()->getNotificationPopup()->showUnfinishJobPopup(
		this->getParent()
	);
	return;
	sender->showLock();*/
	if (InfoManager::getInstance()->getUserInfo()->level + 1 >= InfoManager::getInstance()->getUnlockFeatureByLevelConfig().piggyBank) {
		PopupManager::getInstance()->getPiggyBankPopup()->prepareAndShow(this->getParent());
	}
	else {
		sender->showLock();
		PopupManager::getInstance()->getMascotNotificationPopup()->show(
			this->getParent(),
			"You need to reach level " + ToString(InfoManager::getInstance()->getUnlockFeatureByLevelConfig().piggyBank) + " to unlock this feature!"
		);
	}
}


void BottomLobbyLayout::updateAfterChangeLanguage() {
	freeCoinGiftItem->updateUI();
	this->achievements.btn->getTitleLabel()->setString(LanguageManager::getInstance()->getStringForKeys(this->achievements.btn->getTitleLabel(), LanguageConstant::FOOTER_ACHIEVEMENT_LABLE));
	this->gifts.btn->getTitleLabel()->setString(LanguageManager::getInstance()->getStringForKeys(this->gifts.btn->getTitleLabel(), LanguageConstant::FOOTER_GIFT_LABLE));

}
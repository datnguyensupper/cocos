#include "LuckyBoxPopup.h"
#include "Constant/Defination.h"
#include "Constant/LobbyConstant.h"
#include "Constant/ResultCodeConstant.h"

#include "Manager/PopupManager.h"
#include "Manager/NetworkManager.h"
#include "Manager/InfoManager.h"
#include "Manager/SoundManager.h"
#include "Manager/PluginManager.h"

#include "Views/Popup/NotificationPopup.h"
#include "Views/Popup/LoadingAnimation.h"
#include "Views/Lobby/body/BodyLobbyLayout.h"
#include "Views/Lobby/header/HeaderLobbyLayout.h"
#include "Views/Effects/AnimationCoinCrown.h"

#include "Helper/Action/FShake.h"
#include "Helper/Helper4Sprite.h"
#include "Helper/Helper4String.h"
#include "Helper/Helper4Scene.h"

USING_NS_CC;
using namespace std;


#pragma region LuckyBoxPopup

bool LuckyBoxPopup::init()
{

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PNG_LUCKY_BOX_PLIST);

	if (!BasePopup::init()) {
		return false;
	}


	auto parent = Node::create();
	parent->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 20));

	//auto background = Sprite::createWithSpriteFrameName(FRAME_LUCKY_BOX_BG);
	background = Helper4Sprite::createOptimizeSprite(PNG_NOTIFICATION_POPUP_BACKGROUND);
	background->setContentSize(Size(844, 674));
	parent->addChild(background);

	buyAndDoubleUI = BuyAndDoubleUI::create(this);
	buyAndDoubleUI->setPositionY(-10);
	parent->addChild(buyAndDoubleUI);

	oLightRay = createLightRayBG(Vec2(0, 0));
	parent->addChild(oLightRay);

	oLogo = Helper4Sprite::createOptimizeSprite(PNG_UNLCOKED_POPUP_TITLE);
	parent->addChild(oLogo);


	chestUI = LuckyBoxChestUI::create(this);
	parent->addChild(chestUI);

	addChild(parent);

	return true;
}


void LuckyBoxPopup::prepareAndShow(cocos2d::Node* parent, GiftInfo* _giftInfo, int _numberOfLuckyBox, bool _isCollectAll, std::function<void(void)> callback){
	giftInfo = _giftInfo;
	numberOfLuckyBox = _numberOfLuckyBox;
	isCollectAll = _isCollectAll;
	callbackWhenCollectLuckyBoxDone = callback;

	LuckyBox boxInfo;
	switch (giftInfo->type) {
	case LobbyConstant::LUCKY_BOX_SILVER_CHEST: {
		chestSpriteName = FRAME_LUCKY_BOX_CHEST_SILVER;
		luckyBoxMessageName = LobbyConstant::LUCKY_BOX_NAME_SILVER;
		boxInfo = InfoManager::getInstance()->getLuckyBoxConfig().box1;
		packagePurchaseX2Name = IAP_LUCKY_BOX_X2_COMMONER;
		break;
	}
	case LobbyConstant::LUCKY_BOX_GOLD_CHEST: {
		chestSpriteName = FRAME_LUCKY_BOX_CHEST_GOLD;
		luckyBoxMessageName = LobbyConstant::LUCKY_BOX_NAME_GOLD;
		boxInfo = InfoManager::getInstance()->getLuckyBoxConfig().box2;
		packagePurchaseX2Name = IAP_LUCKY_BOX_X2_NOBLE;
		break;
	}
	case LobbyConstant::LUCKY_BOX_RED_CHEST: {
		chestSpriteName = FRAME_LUCKY_BOX_CHEST_RED;
		luckyBoxMessageName = LobbyConstant::LUCKY_BOX_NAME_RED;
		boxInfo = InfoManager::getInstance()->getLuckyBoxConfig().box3;
		packagePurchaseX2Name = IAP_LUCKY_BOX_X2_KING;
		break;
	}
	default:
		chestSpriteName = FRAME_LUCKY_BOX_CHEST_SILVER;
		luckyBoxMessageName = LobbyConstant::LUCKY_BOX_NAME_SILVER;
		packagePurchaseX2Name = IAP_LUCKY_BOX_X2_COMMONER;
	}

	float price = boxInfo.price;
	if (!isCollectAll) {
		giftInfo->coinReward = boxInfo.coins;
		giftInfo->crownReward = boxInfo.crowns;
		giftInfo->luckyWheelReward = boxInfo.luckyWheels;
	}
	if (price == 1 || price == 0) price = 0.99;
	else if (price == 2 || price == 0) price = 1.99;
	else if (price == 5 || price == 0) price = 4.99;
	saleBuyAndDoubleText = "Only $" + ToString(price);


	auto currentActiveBackground = background;
	if (isCollectAll) {
		if (numberOfLuckyBox == 1) luckyBoxMessageName = "CHEST";
		else luckyBoxMessageName = "CHESTS";
		buyAndDoubleUI->setVisible(false);
		currentActiveBackground = background;
		background->setVisible(true);
	}else {
		numberOfLuckyBox = 1;
		background->setVisible(false);
		currentActiveBackground = buyAndDoubleUI->background;
		buyAndDoubleUI->setEnabled(true);
		buyAndDoubleUI->setVisible(true);
	}

	oLogo->setPositionY(currentActiveBackground->getContentSize().height / 2 - 30);
	oLightRay->setPositionY(currentActiveBackground->getContentSize().height / 2 - 320);
	chestUI->setPositionY(oLightRay->getPosition().y);
	chestUI->reset();
	BasePopup::show(parent);
	this->oLightRay->runAction(createActionRotateLightRay());
	chestUI->playLittleShakeAnimation();
	buyAndDoubleUI->reset();
}


void LuckyBoxPopup::hide() {
	chestUI->hide();
	this->oLightRay->stopAllActions();
	BasePopup::hide();

	CC_SAFE_DELETE(giftInfo);
}


cocos2d::ui::Button* LuckyBoxPopup::createButton(std::string titleText, float fontSize) {
	return BasePopup::createGreenButton(titleText,fontSize);
}


void LuckyBoxPopup::setEnabled(bool enable, bool _isBuyingDouble) {
	chestUI->setEnabled(enable);
	buyAndDoubleUI->setEnabled(enable);
	isBuyingDouble = _isBuyingDouble;
}

void LuckyBoxPopup::callbackAfterBuyingDouble(bool isSuccess, LuckyBox buyInfo) {
	if (!isBuyingDouble) {
		return;
	}
	isBuyingDouble = false;
	if (!isVisible()) return;

	if (!isSuccess) setEnabled(true, false);
	else {
		// buy success
		giftInfo->coinReward += buyInfo.coins;
		giftInfo->crownReward += buyInfo.crowns;
		giftInfo->luckyWheelReward += buyInfo.luckyWheels;
		chestUI->setEnabled(true);
		chestUI->onTouchEnded(nullptr, nullptr);
	}
}

void LuckyBoxPopup::callback4Click2DarkLayer() {
	chestUI->playLittleShakeAnimation();
}

#pragma endregion

#pragma region LuckyBoxChestUI

LuckyBoxChestUI::LuckyBoxChestUI() : cocos2d::Node(){
}

LuckyBoxChestUI * LuckyBoxChestUI::create(LuckyBoxPopup * _parent){
	auto item = LuckyBoxChestUI::create();
	if (item) item->parent = _parent;
	return item;
}

bool LuckyBoxChestUI::init(){
	if (!Node::init()) return false;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	chest = Sprite::createWithSpriteFrameName(FRAME_LUCKY_BOX_CHEST_SILVER);
	addChild(chest);


	labelChest = Label::createWithTTF("", FONT_PassionOne_Regular, 38);
	labelChest->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	labelChest->setVerticalAlignment(TextVAlignment::CENTER);
	labelChest->setHorizontalAlignment(TextHAlignment::CENTER);
	labelChest->setDimensions(750, 200);
	addChild(labelChest);

	labelTouch2Open = Label::createWithTTF("Touch to open now", FONT_PassionOne_Regular, 38);
	labelTouch2Open->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	labelTouch2Open->setVerticalAlignment(TextVAlignment::CENTER);
	labelTouch2Open->setHorizontalAlignment(TextHAlignment::CENTER);
	labelTouch2Open->setPosition(Vec2(0, -230));
	addChild(labelTouch2Open);

	resetChestTransformAndAction();
	createSprite4OpenChestAnimation();

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = [this](Touch* touch, Event* event) -> bool {

		if (currentState == ChestUIState::CHEST_UI_STATE_START ||currentState == ChestUIState::CHEST_UI_STATE_CAN_RELOAD) {
			auto visibleSize = Director::getInstance()->getVisibleSize();
			auto origin = Director::getInstance()->getVisibleOrigin();
			if (event->getCurrentTarget() != chest) return false;
			auto bounds = event->getCurrentTarget()->getBoundingBox();
			bounds.setRect(bounds.getMinX() + visibleSize.width / 2, bounds.getMinY() + visibleSize.height / 2, bounds.getMaxX() - bounds.getMinX(), bounds.getMaxY() - bounds.getMinY());
			cocos2d::Vec2 location = touch->getLocation();
			if (!bounds.containsPoint(touch->getLocation())) return false;
			
			return true;
		}else return false;
	};
	touchListener->setSwallowTouches(true);
	touchListener->onTouchEnded = CC_CALLBACK_2(LuckyBoxChestUI::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, chest);


	return true;
}

void LuckyBoxChestUI::hide() {
	resetChestTransformAndAction();
	resetGroupOpenChestTransformAndAction();
}

void LuckyBoxChestUI::setEnabled(bool enable) {
	if(enable) currentState = ChestUIState::CHEST_UI_STATE_START;
	else currentState = ChestUIState::CHEST_UI_STATE_DISABLE;
}

void LuckyBoxChestUI::reset() {
	currentState = ChestUIState::CHEST_UI_STATE_START;

	if (parent->isCollectAll) {
		labelChest->setPosition(Vec2(0, -230));
		labelTouch2Open->setVisible(false);
	}else {
		labelChest->setPosition(Vec2(0, -180));
		labelTouch2Open->setVisible(true);
	}
	chest->setSpriteFrame(parent->chestSpriteName+"_closed");
	updateTextMessage();

}



void LuckyBoxChestUI::onTouchEnded(Touch* touch, Event* event) {

	if (currentState == ChestUIState::CHEST_UI_STATE_START) {
		currentState = ChestUIState::CHEST_UI_STATE_COLLECTING;
		parent->buyAndDoubleUI->setEnabled(false);
		playOpenChestAnimation();
		callAPIAcceptGift();
	}
	else if (currentState == ChestUIState::CHEST_UI_STATE_CAN_RELOAD) {
		callAPIAndAnimReloadHeaderAndClosePopup(0);
	}
	
}


void LuckyBoxChestUI::resetChestTransformAndAction() {
	chest->setRotation(0);
	chest->setPosition(Vec2::ZERO);
	chest->setAnchorPoint(Vec2(0.5, 0.5));
	chest->setScale(chestScale);
	chest->stopAllActions();
}


void LuckyBoxChestUI::resetGroupOpenChestTransformAndAction() {

	groupOpenChestAnimation->setVisible(false);
	groupOpenChestAnimation->setOpacity(255);
	groupOpenChestAnimation->setScale(1.0);
	for (const auto &star : groupOpenChestAnimation->getChildren()) {
		star->stopAllActions();
		if (star->getTag() == 4) {
			star->setOpacity(0);
			star->setScale(0);
			star->setRotation(0);
		}else if (star->getTag()==2) star->setScale(1);
		
		star->setVisible(true);

		star->stopAllActions();
	}

	labelChest->stopAllActions();
	groupOpenChestAnimation->stopAllActions();

}

void LuckyBoxChestUI::playLittleShakeAnimation() {


	if (currentState != ChestUIState::CHEST_UI_STATE_START) return;

	resetChestTransformAndAction();
	resetGroupOpenChestTransformAndAction();

	float speed = 1;
	float speed2 = 1;
	
	Repeat * rotateAction = Repeat::create(Sequence::create(RotateTo::create(0.1*speed, -25), RotateTo::create(0.15 * speed, 25), RotateTo::create(0.15 * speed, -20), RotateTo::create(0.15 * speed, 20), RotateTo::create(0.15 * speed, -15), RotateTo::create(0.15 * speed, 15), RotateTo::create(0.1 * speed, 0), DelayTime::create(0.5f*speed), nullptr), 2);


	float newAnchorY = -0.2;
	float newPositionY = (newAnchorY - chest->getAnchorPoint().y)*chest->getContentSize().height*chestScale;
	Sequence * translate4Jump = Sequence::create(
		CallFunc::create([=]() {/*change anchor for chest*/chest->setAnchorPoint(Vec2(0.5, newAnchorY));}), 
		MoveTo::create(0, Vec2(0, newPositionY)),
		MoveTo::create(0.2*speed2, Vec2(0, newPositionY)),
		CallFunc::create([=]() {
		SoundManager::getInstance()->stopSoundEffectLuckyBoxChestBounce();
		SoundManager::getInstance()->playSoundEffectLuckyBoxChestBounce();
		}),
		MoveTo::create(0.2*speed2, Vec2(0, newPositionY+100)),
		MoveTo::create(0.2*speed2, Vec2(0, newPositionY)),
		MoveTo::create(0.2*speed2, Vec2(0, newPositionY)),
		MoveTo::create(0.2*speed2, Vec2(0, newPositionY)),
		nullptr);
	Sequence * scale4jump = Sequence::create(
		ScaleTo::create(0.2*speed2, 1.2*chestScale, 0.5*chestScale),
		ScaleTo::create(0.2*speed2, 0.5*chestScale, 1.2*chestScale),
		ScaleTo::create(0.2*speed2, 1 * chestScale,   1 * chestScale),
		ScaleTo::create(0.2*speed2, 1.2*chestScale, 0.6*chestScale),
		EaseBounceOut::create(ScaleTo::create(0.2*speed2,chestScale, chestScale)),
		nullptr); 
	Action * jumpAction = Spawn::createWithTwoActions(translate4Jump, scale4jump);

	auto littleShakeAction = Sequence::create(rotateAction, jumpAction, CallFunc::create([=]() {
		resetChestTransformAndAction();
	}),nullptr);
	chest->runAction(littleShakeAction);


}

void LuckyBoxChestUI::updateTextMessage() {
	int numberOfLuckyBox = parent->numberOfLuckyBox;
	std::string luckyBoxMessageName = parent->luckyBoxMessageName;

	//if(messala)
	////INIT MESSAGE
	labelChest->setVisible(true);
	labelChest->setString("");
	Helper4Sprite::labelAppendString(labelChest, "You've got ", Color3B::WHITE);
	std::string stringNumber = "0 ";
	if (numberOfLuckyBox == 1) stringNumber = "a ";
	else stringNumber = ToString(numberOfLuckyBox) + " ";
	Helper4Sprite::labelAppendString(labelChest, stringNumber, Color3B::WHITE);
	Helper4Sprite::labelAppendString(labelChest, luckyBoxMessageName, Color3B::YELLOW);
	Helper4Sprite::labelAppendString(labelChest, " !!!", Color3B::WHITE);

	//this->addChild(messageLabel);
}

void LuckyBoxChestUI::createSprite4OpenChestAnimation() {

	groupOpenChestAnimation = Node::create();
	groupOpenChestAnimation->setCascadeOpacityEnabled(true);
	addChild(groupOpenChestAnimation);

	resetGroupOpenChestTransformAndAction();

	auto lens_flare = Sprite::createWithSpriteFrameName(FRAME_LUCKY_BOX_LENS_FLARE);
	groupOpenChestAnimation->addChild(lens_flare);
	Helper4Sprite::setBlendModeAdd(lens_flare);

	for (int i = 0; i < 12; i++) {
		auto star = Sprite::createWithSpriteFrameName(FRAME_LUCKY_BOX_STAR);
		star->setTag(2);
		if(i < 3) star->setPosition(Vec2(RandomHelper::random_int(-100, 0), RandomHelper::random_int(0, 100)));
		else if(i < 6) star->setPosition(Vec2(RandomHelper::random_int(-100, 0), RandomHelper::random_int(-100, 0)));
		else if(i < 9) star->setPosition(Vec2(RandomHelper::random_int(0, 100), RandomHelper::random_int(0, 100)));
		else star->setPosition(Vec2(RandomHelper::random_int(0, 100), RandomHelper::random_int(-100, 0)));
		groupOpenChestAnimation->addChild(star);
	}

	const std::function<void(float)>& createLight = [this](float angle) {
		auto light = Sprite::createWithSpriteFrameName(FRAME_LUCKY_BOX_LIGHT_RAY); 
		light->setAnchorPoint(Vec2(0.5, 0)); 
		light->setRotation(angle); 
		light->setTag(3); 
		groupOpenChestAnimation->addChild(light);
	
	};
	createLight(90);createLight(90+20);createLight(90-20);createLight(-90);createLight(-90-20);createLight(-90+20);

	const std::function<void(Vec2)>& createStarFlare = [this](Vec2 position) {
		auto starFlare = Sprite::createWithSpriteFrameName(FRAME_LUCKY_BOX_STAR_FLARE_WHITE);
		starFlare->setPosition(position);
		starFlare->setAnchorPoint(Vec2(0.5, 0.5));
		starFlare->setScale(0);
		starFlare->setTag(4);
		starFlare->setOpacity(0);
		groupOpenChestAnimation->addChild(starFlare);
		Helper4Sprite::setBlendModeAdd(starFlare);
	};
	createStarFlare(Vec2(0,0));
	createStarFlare(Vec2(-10,-10));
	createStarFlare(Vec2(30,10));
	createStarFlare(Vec2(-100,5));
}

void LuckyBoxChestUI::playOpenChestAnimation() {

	resetChestTransformAndAction();
	resetGroupOpenChestTransformAndAction();

	float speed0 = 1;
	float speed1 = 1;
	float speed2 = 1;

	FShake* shakeAction = FShake::actionWithDuration(2.0f*speed0, 10.0f);
	chest->runAction(shakeAction);
	labelChest->setVisible(false);
	labelTouch2Open->setVisible(false);

	SoundManager::getInstance()->stopSoundEffectLuckyBoxChestBounce();
	SoundManager::getInstance()->playSoundEffectLuckyBoxChestShake();
	chest->runAction(Sequence::create(shakeAction, CallFunc::create([this,speed1,speed2]() {
		SoundManager::getInstance()->stopSoundEffectLuckyBoxChestShake();
		SoundManager::getInstance()->playSoundEffectLuckyBoxChestOpen();

		groupOpenChestAnimation->setVisible(true);

		chest->setSpriteFrame(parent->chestSpriteName);
		/*groupOpenChestAnimation->runAction(Sequence::create(DelayTime::create(2.0f*speed2), CallFunc::create([this]() {
			if (currentState == ChestUIState::CHEST_UI_STATE_COLLECTING) currentState = ChestUIState::CHEST_UI_STATE_FINISHED_ANIMATION;
			else reloadAndTimerPlayAnimateCoinInfo();
		})));
		return;*/
		for (const auto &star : groupOpenChestAnimation->getChildren()) {
			if (star->getTag() == 2) /*this is star*/
				star->runAction(ScaleTo::create(1.0*speed1, 1.0 / 4.0));
		}

		groupOpenChestAnimation->runAction(ScaleTo::create(1.5*speed1, 4));
		groupOpenChestAnimation->runAction(FadeTo::create(1.5*speed1,0.7));

		groupOpenChestAnimation->runAction(Sequence::create(DelayTime::create(1.5f*speed1), CallFunc::create([this,speed2]() {

			playTextAnimation();
			float delay = 0;

			groupOpenChestAnimation->setOpacity(255);
			groupOpenChestAnimation->setScale(1.0);
			for (const auto &starFlare : groupOpenChestAnimation->getChildren()) {
				if (starFlare->getTag() == 4) { /*this is star*/
					starFlare->setVisible(true);
					Action * showStar = Spawn::create(RotateBy::create(0.5 * speed2, RandomHelper::random_int(30, 90)),
						ScaleTo::create(0.5 * speed2, 0.7), FadeIn::create(0.5 * speed2), nullptr);
					Action * hideStar = Spawn::create(ScaleTo::create(0.5*speed2, 0), FadeOut::create(0.5*speed2), nullptr);
					Action * sequenceShowStar = Sequence::create(DelayTime::create(delay), showStar, hideStar, DelayTime::create(2* speed2 - delay), nullptr);
					starFlare->runAction(RepeatForever::create((ActionInterval*)sequenceShowStar));
					delay += 0.5f;
				}
				else starFlare->setVisible(false);
			}

		}), DelayTime::create(2.0f*speed2), CallFunc::create([this]() {
			if (currentState == ChestUIState::CHEST_UI_STATE_COLLECTING) currentState = ChestUIState::CHEST_UI_STATE_FINISHED_ANIMATION;
			else reloadAndTimerPlayAnimateCoinInfo(); 
		}), nullptr));


	}), nullptr));

}


void LuckyBoxChestUI::playTextAnimation() {
	labelChest->setVisible(true);
	labelTouch2Open->setVisible(false);
	labelChest->setPosition(Vec2(0, -230));

	const std::function<void(float percent)>& updateReward = [this](float percent) {
		labelChest->setString("");
		Helper4Sprite::labelAppendString(labelChest, "You've got ", Color3B::WHITE);
		int coin = parent->giftInfo->coinReward * percent;
		int crown = parent->giftInfo->crownReward * percent;
		int luckyWheelReward = parent->giftInfo->luckyWheelReward * percent;

		Helper4Sprite::labelAppendString(labelChest, Helper4String::FormatWithCommas(coin), Color3B::YELLOW);
		Helper4Sprite::labelAppendString(labelChest, " COINS", Color3B::WHITE);

		if (parent->giftInfo->crownReward > 0) {
			if (parent->giftInfo->luckyWheelReward > 0)
				Helper4Sprite::labelAppendString(labelChest, ", ", Color3B::WHITE);
			else
				Helper4Sprite::labelAppendString(labelChest, " and ", Color3B::WHITE);

			Helper4Sprite::labelAppendString(labelChest, Helper4String::FormatWithCommas(crown), Color3B::YELLOW);
			Helper4Sprite::labelAppendString(labelChest, " CROWNS", Color3B::WHITE);
		}

		if (parent->giftInfo->luckyWheelReward > 0) {
			Helper4Sprite::labelAppendString(labelChest, " and ", Color3B::WHITE);
			Helper4Sprite::labelAppendString(labelChest, Helper4String::FormatWithCommas(luckyWheelReward), Color3B::YELLOW);
			Helper4Sprite::labelAppendString(labelChest, " LUCKY WHEELS", Color3B::WHITE);
		}
	};

	SoundManager::getInstance()->playSoundEffectIncreaseCoin();
	auto actionIcreaseCoin = ActionFloat::create(
		1,0,1000,[this,updateReward](double value) {
		updateReward(value*1.0 / 1000);
	});
	labelChest->stopAllActions();
	labelChest->runAction(actionIcreaseCoin);
}


void LuckyBoxChestUI::callAPIAcceptGift() {

	std::function<void(int coreResultCode, rapidjson::Value&responseAsDocument, std::string responseAsString)> result = [this](int coreResultCode, rapidjson::Value &response, std::string responseAsString) {
		if (coreResultCode == RESULT_CODE_VALID) {
			if (currentState == ChestUIState::CHEST_UI_STATE_COLLECTING) currentState = ChestUIState::CHEST_UI_STATE_COLLECTED;
			else reloadAndTimerPlayAnimateCoinInfo();
		}
		else {
			PopupManager::getInstance()->getNotificationPopup()->showServerErrorPopup(parent->getParent());
			parent->hide();
		}
	};
	std::function<void(std::string result)> callbackError = [this](std::string) {
		parent->hide();
	};
	if (parent->isCollectAll) {
		NetworkManager::getInstance()->acceptGiftAll(result, callbackError);
	}else {
		NetworkManager::getInstance()->acceptGift(parent->giftInfo->id,result,callbackError);
	}
}

void LuckyBoxChestUI::callAPIAndAnimReloadHeaderAndClosePopup(float dt) {


	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	unschedule(schedule_selector(LuckyBoxChestUI::callAPIAndAnimReloadHeaderAndClosePopup));

	currentState = ChestUIState::CHEST_UI_STATE_RELOADING;
	if (parent->callbackWhenCollectLuckyBoxDone) parent->callbackWhenCollectLuckyBoxDone();
	if (PopupManager::getInstance()->getHeaderLobbyLayout() != nullptr) {

		AnimationCoinCrown::create(
			Helper4Scene::getRunningScene(),
			Vec2(Director::getInstance()->getVisibleSize().width / 2 + origin.x, Director::getInstance()->getVisibleSize().height / 2 + origin.y),
			parent->giftInfo->coinReward,
			AnimationType::CoinAnimation
		);
		AnimationCoinCrown::create(
			Helper4Scene::getRunningScene(),
			Vec2(Director::getInstance()->getVisibleSize().width / 2 + origin.x, Director::getInstance()->getVisibleSize().height / 2 + origin.y),
			parent->giftInfo->crownReward,
			AnimationType::CrownAnimation
		);
		Helper4Scene::getRunningScene()->scheduleOnce([](float dt) {
			PopupManager::getInstance()->getHeaderLobbyLayout()->reloadUIHeaderAndCheckShowPopupLevelUp(
				[](bool isSucess, LevelUpInfo* levelupInfo) {
			});
		},2.5,"LuckyBoxChestUI::callAPIAndAnimReloadHeaderAndClosePopup");
	}
	parent->hide();
}

void LuckyBoxChestUI::reloadAndTimerPlayAnimateCoinInfo() {
	currentState = ChestUIState::CHEST_UI_STATE_CAN_RELOAD;
		
	this->scheduleOnce(schedule_selector(LuckyBoxChestUI::callAPIAndAnimReloadHeaderAndClosePopup), 2.0f);
	
}

#pragma endregion



#pragma region BuyAndDoubleUI
BuyAndDoubleUI * BuyAndDoubleUI::create(LuckyBoxPopup * _parent) {
	auto item = BuyAndDoubleUI::create();
	if (item) {
		item->parent = _parent;
		item->setUpUI();
	}
	return item;
}

void BuyAndDoubleUI::setUpUI() {

	background = Sprite::createWithSpriteFrameName(FRAME_LUCKY_BOX_BG);
	addChild(background);

	auto backgroundBottom = Sprite::createWithSpriteFrameName(FRAME_LUCKY_BOX_BUY_AND_DOUBLE_BG);
	backgroundBottom->setPositionY (-background->getContentSize().height / 2 + backgroundBottom->getContentSize().height / 2 + 40);
	addChild(backgroundBottom);


	labelSale = Label::createWithTTF("Only $0", FONT_PassionOne_Regular, 55);
	labelSale->enableOutline(Color4B(99, 35, 100, 255),4);
	labelSale->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	labelSale->setVerticalAlignment(TextVAlignment::CENTER);
	labelSale->setHorizontalAlignment(TextHAlignment::CENTER);
	labelSale->setPosition(Vec2(-90, 15)+backgroundBottom->getPosition());
	addChild(labelSale);

	std::string frameName = FRAME_LUCKY_BOX_CHEST_SILVER ;
	chest1 = Sprite::createWithSpriteFrameName(frameName + "_closed_small");
	chest1->setPosition(Vec2(-310, -5) + backgroundBottom->getPosition());
	addChild(chest1);
	chest2 = Sprite::createWithSpriteFrameName(frameName + "_closed_small");
	chest2->setPosition(Vec2(30,-30)+chest1->getPosition());
	addChild(chest2);

	buyButton = parent->createButton(" BUY & DOUBLE ", 20);
	buyButton->setPosition(backgroundBottom->getPosition()+Vec2(220,-15));
	buyButton->addTouchEventListener([this](cocos2d::Ref* sender, ui::Widget::TouchEventType touchEvent) {
		if (touchEvent != ui::Widget::TouchEventType::ENDED) return;


		std::function<void()> callbackFail = [this]() {
			// fail
			PopupManager::getInstance()->getLoadingAnimation()->hide();
			LuckyBox boxInfo;
			PopupManager::getInstance()->getLuckyBoxPopup()->callbackAfterBuyingDouble(false, boxInfo);

		};

		bool isCanPurchase = PluginManager::getInstance()->getIAPController()->purchase(
			parent->packagePurchaseX2Name,
			[callbackFail,this](int core_result_code, MobilePaymentInfo mobilePaymentInfo){
			if (core_result_code != RESULT_CODE_VALID){
				callbackFail();
			}else {
				LuckyBox boxInfo;
				boxInfo.coins = mobilePaymentInfo.coinReward;
				boxInfo.crowns = mobilePaymentInfo.crownReward;
				boxInfo.luckyWheels = mobilePaymentInfo.spinOfLuckyWheelReward;
				PopupManager::getInstance()->getLuckyBoxPopup()->callbackAfterBuyingDouble(true, boxInfo);
				PopupManager::getInstance()->getLoadingAnimation()->hide();
			}
		},nullptr,[callbackFail](sdkbox::Product const&p, const std::string&msg){// fail
			callbackFail();
		},[callbackFail](sdkbox::Product const&p){//cancel
			callbackFail();
		});
		if (isCanPurchase) {
			parent->setEnabled(false, true);
			PopupManager::getInstance()->getLoadingAnimation()->prepareAndShow(this->getParent());
		}else {
			PopupManager::getInstance()->getNotificationPopup()->showDontSupportPopup(
				parent->getParent()
			);
		}
	});
	addChild(buyButton);

}

void BuyAndDoubleUI::setEnabled(bool enable) {
	buyButton->setEnabled(enable);
}

void BuyAndDoubleUI::reset() {
	labelSale->setString(parent->saleBuyAndDoubleText);
	chest1->setSpriteFrame(parent->chestSpriteName + "_closed_small");
	chest2->setSpriteFrame(parent->chestSpriteName + "_closed_small");
}

#pragma endregion
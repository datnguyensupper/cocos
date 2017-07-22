#include "LobbyScene.h"
#include "LuckyWheelScene.h"
#include "testScene/CoinAnimationTestScene.h"

#include "SlotGame/base/utils/CSpriteButton.h"

#include "Manager/SoundManager.h"
#include "Manager/PopupManager.h"
#include "Manager/PromotionsManager.h"
#include "Manager/InfoManager.h"
#include "Manager/NetworkManager.h"
#include "Manager/ScaleManager.h"

#if IS_DEBUG
#include "Manager/Test/TestManager.h"
#endif

#include "Info/AdditionalInfo.h"

#include "Views/Lobby/body/BodyLobbyLayout.h"
#include "Views/Lobby/header/HeaderLobbyLayout.h"
#include "Views/Lobby/bottom/BottomLobbyLayout.h"

#include "Views/Popup/FBDailySpinPopup/DailyBonusWheelPopup.h"
#include "Views/Popup/ComebackBonusMobilePopup.h"
#include "Views/Popup/DailyBonusStreakPopup.h"
#include "Views/Popup/GameUnlockedPopup.h"
#include "Views/Tutorial/Tutorial.h"

USING_NS_CC;
void LobbyScene::checkAndShowStrategyPopups()
{
	auto infoMNG = InfoManager::getInstance();
	auto additionalInfo = infoMNG->getAdditionalInfo();

	this->layerSwallowTouched->setVisible(true);
	//CHECK AND SHOW DAILY BONUS WHEEL
	if (infoMNG->getUserInfo()->role == USER_ROLE::FACEBOOK
		&& additionalInfo->dailyBonusWheelInfo->canCollect)
	{
		NetworkManager::getInstance()->collectDailyBonusWheel(
			[this, infoMNG](int coreResultCode, rapidjson::Value&responseAsDocument, std::string responseAsString)
		{

			this->layerSwallowTouched->setVisible(false);
			if (coreResultCode == RESULT_CODE_VALID)
			{
				infoMNG->getAdditionalInfo()->dailyBonusWheelInfo->updateInfoByValue(responseAsDocument);
				PopupManager::getInstance()->getDailyBonusWheelPopup()->prepareAndShow(this);
			}
		},
			[this](std::string result)
		{
			this->layerSwallowTouched->setVisible(false);
		},
			[this](std::string result)
		{
			this->layerSwallowTouched->setVisible(false);
		}
		);
	}
	else {
		this->layerSwallowTouched->setVisible(false);
	}

	//CHECK AND SHOW COMEBACK BONUS MOBILE 
//	if (additionalInfo->comebackBonusMobileInfo->canCollect)
//	{
//		this->layerSwallowTouched->setVisible(false);
//		PopupManager::getInstance()->getComebackBonusMobilePopup()->prepareAndShow(this);
//	}
	//CHECK AND SHOW DAILY BONUS STREAK
//#if IS_DEBUG
//	if (additionalInfo->dailyBonusStreakInfo->canCollect) {
//		this->layerSwallowTouched->setVisible(false);
//		PopupManager::getInstance()->getDailyBonusStreakPopup()->prepareAndShow(this);
//	}
//#endif

//	PromotionsManager::getInstance()->checkStartupPromotions([this](bool isHavePromotions) {
//		this->layerSwallowTouched->setVisible(false);
//	});
}
Scene* LobbyScene::createScene(ppEnum::GameScene lastScene)
{
	// 'scene' is an autorelease object
	auto scene = LobbyScene::create();
	scene->setTag(ppEnum::GameScene::Lobby);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();


	if (lastScene != ppEnum::GameScene::InitSession) {
		scene->isShowLoading = true;
		auto bgLoading = GameSlot::CSpriteButton::createButtonWithFile(PNG_LOADING_BACKGROUND, nullptr, nullptr);
		bgLoading->setIsBlock(true);
		bgLoading->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
		scene->addChild(bgLoading, 1000);
		bgLoading->runAction(Sequence::create(
			DelayTime::create(1.5f), 
			FadeOut::create(0.5f), 
			CallFunc::create([scene, bgLoading]() {
			bgLoading->setVisible(false);
			scene->onBegin();
		}), NULL));
	}
	else {
		PromotionsManager::getInstance()->reset();
	}

	// return the scene
	return scene;
}

void LobbyScene::onBegin()
{
	PopupManager::getInstance()->reset();
	Tutorial::getInstance()->setFinishCallback(CC_CALLBACK_0(LobbyScene::checkAndShowStrategyPopups, this));
	Tutorial::getInstance()->checkAndShow(this);
	log("***************************start CCTextureCache::getInstance()->getDescription() ***********************");
	//CCTextureCache::getInstance()->removeUnusedTextures();
	log(CCTextureCache::getInstance()->getDescription().c_str());
	log("***************************finish CCTextureCache::getInstance()->getDescription() ***********************");
#if IS_DEBUG
	TestManager::getInstance()->createTestButton(this);
	TestManager::getInstance()->check4AutoTest(this);

#endif
}



void LobbyScene::onEnter()
{
	BaseScene::onEnter();
	//play bg music
	SoundManager::getInstance()->playBackgroundMusic();
	if (!this->isShowLoading) {
		this->onBegin();
	}
}
void LobbyScene::onExit()
{
	BaseScene::onExit();
	SoundManager::getInstance()->stopBackgroundMusic();
}
// on "init" you need to initialize your instance
bool LobbyScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!BaseScene::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	//BODY LAYOUT
	float scaleDownRatio = ScaleManager::getInstance()->getExactlyScaleDownRatio();
	this->bodyLayout = BodyLobbyLayout::create(this);
	this->bodyLayout->setPosition(Vec2(origin.x+(1- scaleDownRatio)*visibleSize.width/2,
		origin.y + (1 - scaleDownRatio)*visibleSize.height / 2
	));
	this->bodyLayout->setScale(scaleDownRatio);
	this->bodyLayout->resetChildPosition4ScaleProblem();
	this->addChild(this->bodyLayout);

	//HEADER LAYOUT
	if (PopupManager::getInstance()->getHeaderLobbyLayout()) {
		this->headerLayout = PopupManager::getInstance()->getHeaderLobbyLayout();
		if (this->headerLayout->getParent())
		{
			this->headerLayout->getParent()->removeChild(this->headerLayout);
		}
	}
	else {
		this->headerLayout = HeaderLobbyLayout::create();
	}
	this->headerLayout->setVisible(true);
	this->addChild(this->headerLayout);
	this->headerLayout->onChangeScene(ppEnum::GameScene::Lobby);

	//BOTTOM LAYOUT
	if (PopupManager::getInstance()->getBottomLobbyLayout()) {
		this->bottomLayout = PopupManager::getInstance()->getBottomLobbyLayout();
		if (this->bottomLayout->getParent())
		{
			this->bottomLayout->getParent()->removeChild(this->bottomLayout);
		}
	}
	else {
		this->bottomLayout = BottomLobbyLayout::create();
	}
	this->bottomLayout->setVisible(true);
	this->addChild(this->bottomLayout);

	//swallow touch
	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->setSwallowTouches(true);
	listener1->onTouchBegan = [this](Touch* touch, Event* event) {
		if (Configs::printConsoleLog)
		{
			CCLOG("LAYER SWALLOW TOUCH LOBBY");
		}
		return this->layerSwallowTouched->isVisible();
	};

	//layerSwallowTouched
	this->layerSwallowTouched = CCLayerColor::create(ccc4(0, 0, 0, 0));
	this->layerSwallowTouched->setScale(100);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this->layerSwallowTouched);
	this->addChild(this->layerSwallowTouched, 1);
	this->layerSwallowTouched->setVisible(false);
    
	// turn timer on and call for bottom
	this->scheduleUpdate();

	return true;
}

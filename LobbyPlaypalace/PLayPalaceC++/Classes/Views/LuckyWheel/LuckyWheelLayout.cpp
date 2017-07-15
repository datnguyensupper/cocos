#include "LuckyWheelLayout.h"
#include "Util/CLoader.h"
#include "Constant/Defination.h"
#include "LuckyWheelAnimationObject.h"
#include "LuckyWheelShopPopup.h"
#include "Manager/PopupManager.h"
#include "Manager/InfoManager.h"
#include "Manager/NetworkManager.h"
#include "Manager/StrategyManager.h"
#include "Manager/SoundManager.h"
#include "Info/AdditionalInfo.h"
#include "Views/Lobby/header/HeaderLobbyLayout.h"
#include "Custom/Common/CSpinWheel.h"
#include "Constant/ResultCodeConstant.h"
#include "Custom/Common/LabelAutoSize.h"
#include "Util/UtilFunction.h"
#include "Helper/AnimationHelper.h"
#include "Helper/Helper4Sprite.h"

USING_NS_CC;
using namespace std;

namespace LuckyWheel {
#pragma region Lucky Wheel

#define PNG_LUCKY_WHEEL_BG "luckywheel/bg.png"
#define PLIST_LUCKY_WHEEL "luckywheel/lucky_wheel.plist"
#define PLIST_LUCKY_WHEEL_HOVER_BLUE "luckywheel/hover_blue.plist"
#define PLIST_LUCKY_WHEEL_HOVER_PURPLE "luckywheel/hover_purple.plist"
#define PLIST_LUCKY_WHEEL_BUTTON_INNER "luckywheel/button_inner.plist"
#define PLIST_LUCKY_WHEEL_BUTTON_ANIM "luckywheel/button_anim.plist"
#pragma endregion

	bool LuckyWheelLayout::init()
	{
		if (!Node::init()) {
			return false;
		}

		this->initLoading();
		this->loadingRes();

		return true;
	}

	void LuckyWheelLayout::initLoading()
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto origin = Director::getInstance()->getVisibleOrigin();

		this->oLoadingGroup = Node::create();
		this->addChild(this->oLoadingGroup, 1000);

		auto background = Helper4Sprite::createOptimizeSprite(PNG_LOADING_BACKGROUND);
		background->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
		this->oLoadingGroup->addChild(background);

		auto bgLoadingBar = Helper4Sprite::createOptimizeSprite(PNG_LOADING_BAR_BACKGROUND);
		bgLoadingBar->setPosition(Vec2(
			background->getPosition().x,
			background->getPosition().y - 180));
		this->oLoadingGroup->addChild(bgLoadingBar);

		this->oLoadingProgessTimer = ProgressTimer::create(CCSprite::create(PNG_LOADING_BAR_FILL));
		if (this->oLoadingProgessTimer != NULL)
		{
			this->oLoadingProgessTimer->setType(kCCProgressTimerTypeBar);
			this->oLoadingProgessTimer->setMidpoint(ccp(0, 0));
			this->oLoadingProgessTimer->setBarChangeRate(ccp(1, 0));
			this->oLoadingProgessTimer->setPercentage(0);
			this->oLoadingProgessTimer->setPosition(Vec2(bgLoadingBar->getContentSize().width / 2, bgLoadingBar->getContentSize().height / 2));
			bgLoadingBar->addChild(this->oLoadingProgessTimer);
		}

		//LOADING LABEL
		this->oLoadingLabel = Label::createWithTTF(TTFConfig(FONT_PassionOne_Regular, 35), "Loading Lucky Wheel");
		this->oLoadingLabel->setPosition(Vec2(
			bgLoadingBar->getPosition().x,
			bgLoadingBar->getPosition().y - 120
		));
		this->oLoadingGroup->addChild(oLoadingLabel);
	}

	void LuckyWheelLayout::loadingRes()
	{
		this->aRes.push_back(PNG_LUCKY_WHEEL_BG);
		this->aRes.push_back(PLIST_LUCKY_WHEEL);
		this->aRes.push_back(PLIST_LUCKY_WHEEL_HOVER_BLUE);
		this->aRes.push_back(PLIST_LUCKY_WHEEL_HOVER_PURPLE);
		this->aRes.push_back(PLIST_LUCKY_WHEEL_BUTTON_INNER);
		this->aRes.push_back(PLIST_LUCKY_WHEEL_BUTTON_ANIM);

		this->scheduleOnce([this](float dt) {
			CLoader::getInstance()->startLoadingResources(
				this->aRes,
				CC_CALLBACK_0(LuckyWheelLayout::finishLoadingRes, this),
				CC_CALLBACK_1(LuckyWheelLayout::onFileLoaded, this), true);
		}, 0.75f, "luck_wheel_loading_res");
	}
	void LuckyWheelLayout::onFileLoaded(float progress)
	{
		this->oLoadingProgessTimer->setPercentage(progress * 90);
	}
	void LuckyWheelLayout::finishLoadingRes()
	{

		this->oLoadingProgessTimer->setPercentage(95);
		InfoManager::getInstance()->reloadAdditionalInfo([this](bool isSuccess, AdditionalInfo*result) {
			this->oLoadingProgessTimer->setPercentage(100);
			this->oLoadingProgessTimer->setPercentage(100);
			this->initLuckyWheel();

			auto visibleSize = Director::getInstance()->getVisibleSize();
			auto origin = Director::getInstance()->getVisibleOrigin();

			this->oHeader = PopupManager::getInstance()->getHeaderLobbyLayout();
			this->oHeader->setPosition(origin + Vec2(70, visibleSize.height - 60));

			if (this->oHeader->getParent())
			{
				this->oHeader->getParent()->removeChild(this->oHeader);
			}
			this->addChild(this->oHeader);
			this->oHeader->onChangeScene(ppEnum::GameScene::LuckyWheel);

			this->scheduleOnce([this](float dt) {

				SoundManager::getInstance()->playBackgroundMusic(ppEnum::GameScene::LuckyWheel);
				this->oLoadingGroup->removeFromParent();
			}, 0.25f, "luck_wheel_finish_loading_res");
		});
	}

	void LuckyWheelLayout::initLuckyWheel()
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto origin = Director::getInstance()->getVisibleOrigin();

		cocos2d::Vec2 posWheel = origin + visibleSize / 2;

		auto bg = Helper4Sprite::createOptimizeSprite(PNG_LUCKY_WHEEL_BG);
		bg->setPosition(posWheel);
		this->addChild(bg);

		this->addChild(UtilFunction::createDarkLayer(125));

		this->oLuckyWheelGroup = Node::create();
		this->oLuckyWheelGroup->setPosition(posWheel + Vec2(0, -25));
		this->oLuckyWheelGroup->setScale(0.9f);
		this->addChild(this->oLuckyWheelGroup);

		//create shiny background animation
		this->shinyBackgroud = ShinyBackground::create();
		this->oLuckyWheelGroup->addChild(this->shinyBackgroud);

		//create wheel background back
		auto bgBack = Sprite::createWithSpriteFrameName("lucky_wheel_wheel_bg_back");
		this->oLuckyWheelGroup->addChild(bgBack);

		//create wheel spin
		this->spinWheel = CSpinWheel::createSpinWheelWithSpriteFrameName(
			"lucky_wheel_wheel_bg",
			std::vector<float>{600000, 400000, 200000, 5, 3000000, 1000000},
			2, 3.0f
		);
		this->oLuckyWheelGroup->addChild(this->spinWheel);

		//create circle bound animation
		this->circleBound = CircleBound::create();
		this->oLuckyWheelGroup->addChild(this->circleBound);

		//create slot hover animation
		this->slotHover = SlotHover::create();
		this->oLuckyWheelGroup->addChild(this->slotHover);

		//create button spin bg back
		auto btnSpinBG = Sprite::createWithSpriteFrameName("lucky_wheel_spin_bg");
		this->oLuckyWheelGroup->addChild(btnSpinBG);

		//create button spin with animation
		this->btnSpin = ButtonSpin::create();
		this->btnSpin->setOnTouched(CC_CALLBACK_0(LuckyWheelLayout::onSpin, this));
		this->oLuckyWheelGroup->addChild(this->btnSpin);

		//create wheel top bg
		auto model = Sprite::createWithSpriteFrameName("lucky_wheel_model");
		model->setPosition(-bgBack->getContentSize().width / 1.75, 0);
		this->oLuckyWheelGroup->addChild(model);

		//create wheel top bg
		auto wheelTopBG = Sprite::createWithSpriteFrameName("lucky_wheel_wheel_top");
		wheelTopBG->setPositionY(37);
		this->oLuckyWheelGroup->addChild(wheelTopBG);

		//create circle flash light aniamtion
		this->cirlceFlashLight = CircleFlashLight::create();
		this->oLuckyWheelGroup->addChild(this->cirlceFlashLight);

		//create slot coin effect
		this->slotCoinEffect = SlotCoinEffect::create();
		this->oLuckyWheelGroup->addChild(this->slotCoinEffect);

		//create wheel sting
		this->wheelSting = WheelSting::create();
		this->wheelSting->setPosition(Vec2(0, 310));
		this->oLuckyWheelGroup->addChild(this->wheelSting);

		//create footer
		auto footerGroup = Node::create();
		this->addChild(footerGroup);

		auto footerBG = Sprite::createWithSpriteFrameName("lucky_wheel_footer");
		footerBG->setPosition(origin*2 + Vec2(visibleSize.width / 2, footerBG->getContentSize().height / 2));
		footerGroup->addChild(footerBG);

		this->txtRemainingSpin = LabelAutoSize::createWithTTF(ToString(this->info->remainingSpin), FONT_PassionOne_Bold, 80);
		this->txtRemainingSpin->setPosition(origin.x+ 85, footerBG->getPositionY());
		((LabelAutoSize*)this->txtRemainingSpin)->setTextAreaSize(Size(100, 150));
		footerGroup->addChild(this->txtRemainingSpin);

		auto btnBuy = GameSlot::CSpriteButton::createButtonWithSpriteFrameName(
			"lucky_wheel_buy_spin_normal", 
			nullptr, 
			CC_CALLBACK_0(LuckyWheelLayout::openLuckyWheelShopPopup, this));
		btnBuy->setImageEvent("lucky_wheel_buy_spin_selected");
		btnBuy->setPosition(footerBG->getContentSize().width - btnBuy->getContentSize().width / 2.75f - origin.x, footerBG->getPositionY());
		footerGroup->addChild(btnBuy);

		this->stopWinAnimation();
		this->playIdleAnimation();

		this->reloadRemaining();

		this->oPopupShop = LuckyWheelShopPopup::create();
		this->getParent()->addChild(oPopupShop);
	}

	void LuckyWheelLayout::playIdleAnimation()
	{
		this->cirlceFlashLight->startAnimation();
	}

	void LuckyWheelLayout::playSpinAnimation()
	{
		this->cirlceFlashLight->startSpinAnimation();
		this->btnSpin->startInnerAnimation();
		this->btnSpin->startFlashAnimation();
	}

	void LuckyWheelLayout::playWinAnimation()
	{
		this->shinyBackgroud->startAnimation();
		this->circleBound->startAnimation();
		this->slotHover->startAnimation(this->winValue == 1000000 || 
			this->winValue == 5 || this->winValue == 400000);
		this->btnSpin->startOuterAnimation();
		this->slotCoinEffect->startAnimation();
		this->wheelSting->startAnimation();
	}

	void LuckyWheelLayout::stopWinAnimation()
	{
		this->shinyBackgroud->stopAnimation();
		this->circleBound->stopAnimation();
		this->slotHover->stopAnimation();
		this->btnSpin->stopAnimation();
		this->slotCoinEffect->stopAnimation();
		this->wheelSting->stopAnimation();
	}

	void LuckyWheelLayout::openLuckyWheelShopPopup()
	{
		this->oPopupShop->prepareAndShow(CC_CALLBACK_0(LuckyWheelLayout::reloadRemaining, this));
	}

	void LuckyWheelLayout::reloadRemaining()
	{
		//this->info->remainingSpin = 100;
		this->txtRemainingSpin->setString(ToString(this->info->remainingSpin)); txtRemainingSpin->setScaleY(1.05);
	}

	void LuckyWheelLayout::onSpin()
	{
		if (this->info->remainingSpin > 0) {
			this->btnSpin->getButton()->setTouchEnabled(false);
			SoundManager::getInstance()->playSoundEffectLuckyWheelStart();
			NetworkManager::getInstance()->spinLuckyWheel(
				[this](int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString) {
				if (coreResultCode == RESULT_CODE_VALID) {
					this->info->updateInfoByValue(responseAsDocument);
					this->winValue = this->info->coinReward == 0 ? this->info->crownReward : this->info->coinReward;

					this->reloadRemaining();

					this->stopWinAnimation();
					this->playSpinAnimation();

					auto delay = 0;
					auto step = 20;
					auto soundId = -1;
					this->schedule([this, delay, step, soundId](float dt) mutable{
						if (delay % step == 0) {
							step += 4;
							SoundManager::getInstance()->stopSound(soundId);
							soundId = SoundManager::getInstance()->playSoundEffectLuckyWheelSpin(false, 2.0f);
							delay = 0;
						}
						delay++;
					}, "spinning_sound");

					this->spinWheel->spin(this->winValue, [this, soundId]() {
						this->oHeader->reloadUIHeaderAndCheckShowPopupLevelUp();
						this->playWinAnimation();
						this->playIdleAnimation();
						this->btnSpin->getButton()->setTouchEnabled(true);

						SoundManager::getInstance()->stopSound(soundId);
						this->unschedule("spinning_sound");
						SoundManager::getInstance()->playSoundEffectLuckyWheelStop();
					}, EaseQuadraticActionOut::create(RotateBy::create(3.0, this->spinWheel->getNextRotation(this->winValue))));
				}else {
					NetworkFailProcessInfo failInfo;
					failInfo.core_result_code = coreResultCode;
					StrategyManager::getInstance()->handleFailResultNewStrategy(failInfo, true, false);
					this->btnSpin->getButton()->setTouchEnabled(true);
				}
			});
		}
		else {
			this->openLuckyWheelShopPopup();
		}
	}

	void LuckyWheelLayout::onEnter()
	{
		Node::onEnter();
		this->info = InfoManager::getInstance()->getAdditionalInfo()->luckyWheelInfo;
	}

	void LuckyWheelLayout::onExit()
	{
		Node::onExit();
		AnimationHelper::getInstance()->release();
		for (auto res : this->aRes) {
			UtilFunction::releaseCache(res);
		}
	}
}
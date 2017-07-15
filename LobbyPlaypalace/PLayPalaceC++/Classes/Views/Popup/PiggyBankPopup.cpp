#include "PiggyBankPopup.h"
#include "Constant/Defination.h"
#include "Constant/ResultCodeConstant.h"
#include "Custom/Common/LabelAutoSize.h"
#include "Manager/InfoManager.h"
#include "Manager/SoundManager.h"
#include "Manager/PopupManager.h"
#include "Views/Popup/LoadingAnimation.h"
#include "Views/Popup/NotificationPopup.h"
#include "Views/Lobby/header/HeaderLobbyLayout.h"
#include "Views/Effects/AnimationCoinCrown.h"
#include "Info/AdditionalInfo.h"
#include "Util/UtilFunction.h"
#include "Custom/Common/ButtonScaleChild.h"
#include "Helper/Action/FShake.h"
#include "Helper/Helper4Scene.h"
#include "Manager/PluginManager.h"
#include "Manager/DeviceManager.h"

USING_NS_CC;
using namespace std;


bool PiggyBankPopup::init()
{
	if (!BasePopup::init()) {
		return false;
	}

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PLIST_PIGGY_BANK);

	this->initGroupNormal();

	return true;
}

void PiggyBankPopup::initGroupNormal()
{

	this->groupBreaking = BreakingPiggyBankUI::create();
	this->groupBreaking->setPosition(origin + visibleSize / 2);
	this->addChild(this->groupBreaking);

	this->groupNormal = Node::create();
	this->groupNormal->setCascadeOpacityEnabled(true);
	this->addChild(this->groupNormal);

	this->sprtLightRay = this->createLightRayBG(origin + visibleSize / 2);
	this->sprtLightRay->setScale(2);
	this->groupNormal->addChild(this->sprtLightRay);

	this->sprtPigGlow = Sprite::createWithSpriteFrameName(FRAME_PIGGY_BANK_PIG_GLOW);
	this->sprtPigGlow->setPosition(this->sprtLightRay->getPosition() + Vec2(20, 35));
	this->groupNormal->addChild(this->sprtPigGlow);

	this->groupPig = Node::create();
	this->groupPig->setCascadeOpacityEnabled(true);
	this->groupPig->setPosition(this->sprtLightRay->getPosition());
	this->groupNormal->addChild(this->groupPig);

	auto sprtPig = Sprite::createWithSpriteFrameName(FRAME_PIGGY_BANK_PIG);
	this->groupPig->addChild(sprtPig, 1);

	auto sprtPigMask = Sprite::createWithSpriteFrameName(FRAME_PIGGY_BANK_PIG_MASK_BEHIND);
	sprtPigMask->setPosition(sprtPig->getContentSize().width / 4.5f, sprtPig->getContentSize().height / 2.64f);
	this->groupPig->addChild(sprtPigMask, 0);

	this->sprtCoinLightRay = Sprite::createWithSpriteFrameName(FRAME_PIGGY_BANK_PIG_COIN_LIGHT_RAY);
	this->sprtCoinLightRay->setPosition(sprtPigMask->getPosition() - Vec2(sprtPigMask->getContentSize().width / 12, 0));
	this->groupPig->addChild(this->sprtCoinLightRay);

	this->createGroupCoins(sprtPigMask->getPosition() - Vec2(sprtPigMask->getContentSize().width / 12, sprtPigMask->getContentSize().height / 3));

	this->sprtPigTail = Sprite::createWithSpriteFrameName(FRAME_PIGGY_BANK_PIG_TAIL);
	this->sprtPigTail->setPosition(sprtPig->getContentSize().width / 2.48f, sprtPig->getContentSize().height / 3.47f);
	this->sprtPigTail->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	this->sprtPigTail->setRotation(50);
	this->groupPig->addChild(this->sprtPigTail, 2);

	this->sprtPigBreakMask = Sprite::createWithSpriteFrameName(FRAME_PIGGY_BANK_BREAK_MARK);
	this->sprtPigBreakMask->setOpacity(0);
	this->sprtPigBreakMask->setPosition(0, -50);
	this->groupPig->addChild(this->sprtPigBreakMask, 2);

	this->groupInfo = Node::create();
	this->groupInfo->setCascadeOpacityEnabled(true);
	this->groupInfo->setPosition(this->sprtLightRay->getPosition() + Vec2(20, 0));
	this->groupNormal->addChild(this->groupInfo);

	this->txtInfo = Label::createWithTTF("You have saved\n\n\ncoins", FONT_PassionOne_Regular, 50);
	this->txtInfo->setAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);
	this->txtInfo->setTextColor(Color4B(66, 35, 7, 255));
	this->groupInfo->addChild(this->txtInfo);

	this->txtCoin = LabelAutoSize::createWithBMFont(FONT_BITMAP_PIGGY_BANK, "");
	this->txtCoin->setBMFontSize(90);
	((LabelAutoSize*)this->txtCoin)->setTextAreaSize(Size(sprtPig->getContentSize().width * 0.75f, 100));
	this->groupInfo->addChild(this->txtCoin);

	this->btnBreak = this->createButtonWithFrameName(PNG_FRAME_GREEN_POPUP_BUTTON_NEW, "Break now for $2.99", 30);
	this->btnBreak->setCascadeOpacityEnabled(true);
	this->btnBreak->setScaleX(1.1f);
	this->btnBreak->setPosition(this->groupInfo->getPosition() - Vec2(0, sprtPig->getContentSize().height / 4));
	this->btnBreak->addTouchEventListener(CC_CALLBACK_2(PiggyBankPopup::onBreakTouched, this));
	this->groupNormal->addChild(this->btnBreak);

	this->btnBreakMask = Sprite::createWithSpriteFrameName(PNG_FRAME_GREEN_POPUP_BUTTON_NEW);
	((ButtonScaleChild*)this->btnBreak)->addScaleNode(this->btnBreakMask);

	this->sprtHammer = Sprite::createWithSpriteFrameName(FRAME_PIGGY_BANK_HAMMER);
	this->sprtHammer->setAnchorPoint(Vec2(0.5, 0));
	this->sprtHammer->setPosition(this->btnBreak->getPosition() + Vec2(this->btnBreak->getContentSize().width / 1.8f, -this->sprtHammer->getContentSize().height / 2));
	this->groupNormal->addChild(this->sprtHammer);

	closeBtn = this->createCloseButton();
	closeBtn->setPosition(Vec2(
		this->groupPig->getPositionX() + sprtPig->getContentSize().width / 1.7f,
		this->groupPig->getPositionY() + sprtPig->getContentSize().height / 2.3f
	));
	this->groupNormal->addChild(closeBtn);
}

void PiggyBankPopup::createGroupCoins(const cocos2d::Vec2& pos)
{
	aCoinLocalPosition = {
		Vec2(10, 45),
		Vec2(50, 40),
		Vec2(-50, 40),
		Vec2(0, 35),
		Vec2(35, 10),
		Vec2(-30, 20),
		Vec2::ZERO,
	};

	for (auto p : aCoinLocalPosition) {
		aCoinPos.push_back(pos + p);
	}


	for (int i = aCoinPos.size() - 1; i > -1; --i) {
		auto coin = Sprite::create(PNG_SHOP_COIN_ICON);
		coin->setScale(1.3f);
		coin->setPosition(aCoinPos[i]);
		this->groupPig->addChild(coin);

		this->aCoins.push_back(coin);
	}
}

void PiggyBankPopup::startIdleAnimation()
{
	this->sprtLightRay->runAction(RepeatForever::create(
		Sequence::createWithTwoActions(
			ScaleTo::create(0.4f, 3), 
			ScaleTo::create(0.4f, 2.5f))
	));

	this->sprtCoinLightRay->runAction(RepeatForever::create(
		Sequence::createWithTwoActions(
			ScaleTo::create(0.4f, 0.5f),
			ScaleTo::create(0.4f, 0.3f))
	));

	this->sprtPigGlow->runAction(RepeatForever::create(
		Sequence::createWithTwoActions(
			FadeTo::create(0.4f, 75),
			FadeTo::create(0.4f, 255))
	));
	this->sprtPigTail->runAction(RepeatForever::create(
		Sequence::createWithTwoActions(
			ScaleTo::create(0.4f, 1.0f, 0.6f),
			ScaleTo::create(0.35f, 1.0f, 1.0f))
	));
	this->groupPig->runAction(RepeatForever::create(
		Sequence::create(
			RotateTo::create(0.3f, -2),
			RotateTo::create(0.3f, 2),
			RotateTo::create(0.2f, 0),
			NULL
		)));
	this->groupPig->runAction(RepeatForever::create(
		Sequence::createWithTwoActions(
			ScaleTo::create(0.4f, 1.05f),
			ScaleTo::create(0.4f, 1.0f))
	));

	for (int i = 0, size = aCoins.size(); i < size; ++i) {
		aCoins[i]->runAction(Sequence::createWithTwoActions(
			DelayTime::create(RandomHelper::random_int(10, 30) / 60.0f),
			CallFunc::create([this, i]() {
			this->runCoinAnimation(i);
		})));
	}

	this->groupInfo->runAction(RepeatForever::create(
		Sequence::createWithTwoActions(
			ScaleTo::create(0.6f, 0.95f),
			ScaleTo::create(0.6f, 1.0f))
	));

	this->btnBreakMask->setOpacity(150);
	this->btnBreakMask->runAction(RepeatForever::create(
		Sequence::create(
			DelayTime::create(0.5f),
			CallFunc::create([this]() {
		this->btnBreakMask->setOpacity(150);
	}), FadeTo::create(0.5f, 0), NULL)));

	this->btnBreakMask->runAction(RepeatForever::create(
		Sequence::create(
			DelayTime::create(0.5f),
			CallFunc::create([this]() {
		this->btnBreakMask->setScaleY(1.0f);
	}), ScaleTo::create(0.5f, 1.0f, 1.4f), NULL)));
}

void PiggyBankPopup::stopIdleAnimation()
{
	this->sprtLightRay->stopAllActions();

	this->sprtCoinLightRay->stopAllActions();

	this->sprtPigGlow->stopAllActions();

	this->sprtPigTail->stopAllActions();

	this->groupPig->stopAllActions();

	for (int i = 0, size = aCoins.size(); i < size; ++i) {
		aCoins[i]->stopAllActions();
	}

	this->groupInfo->stopAllActions();

	this->btnBreakMask->stopAllActions();
}

void PiggyBankPopup::stopAllAnimations()
{
	this->stopIdleAnimation();
	this->sprtLightRay->stopAllActions();
	this->sprtPigGlow->stopAllActions();
	this->groupInfo->stopAllActions();
	this->btnBreak->stopAllActions();
	this->sprtHammer->stopAllActions();
	this->groupBreaking->stopAnimation();
}

void PiggyBankPopup::onPurchaseFailed()
{
	this->btnBreak->setTouchEnabled(true);
	closeBtn->setVisible(true);
	this->hide();
}

void PiggyBankPopup::onBreakTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != ui::Widget::TouchEventType::ENDED) return;

	this->btnBreak->setTouchEnabled(false);
	closeBtn->setVisible(false);

#ifdef SDKBOX_ENABLED
	PopupManager::getInstance()->getLoadingAnimation()->prepareAndShow(this->getParent());
	PluginManager::getInstance()->getIAPController()->purchase(
		IAP_PIGGY_BANK_P1,
		[this](int core_result_code, MobilePaymentInfo mobilePaymentInfo)
	{
		if (core_result_code == RESULT_CODE_VALID)
		{
			//Debug
			this->stopIdleAnimation();
			this->sprtLightRay->runAction(ScaleTo::create(0.2f, 0));
			this->sprtCoinLightRay->runAction(ScaleTo::create(0.2f, 0));
			this->sprtPigGlow->runAction(ScaleTo::create(0.2f, 0));

			this->groupInfo->runAction(FadeOut::create(0.2f));
			this->groupInfo->runAction(ScaleTo::create(0.2f, 2));
			this->btnBreak->runAction(FadeOut::create(0.2f));
			this->btnBreak->runAction(ScaleTo::create(0.2f, 2));

			this->sprtHammer->runAction(ScaleTo::create(0.2f, 2));
			this->sprtHammer->runAction(Sequence::create(
				MoveTo::create(0.2f, this->btnBreak->getPosition() + Vec2(175, 100)),
				ScaleTo::create(0.05f, -2, 2),
				ScaleTo::create(0.05f, 2, 2),
				ScaleTo::create(0.05f, -2, 2),
				RotateBy::create(0.15f, 45),
				RotateBy::create(0.1f, -100),
				CallFunc::create([this]() {
				SoundManager::getInstance()->playSoundEffectPiggyBankBreakPig2();
			}),
				CallFunc::create([this]() {
				SoundManager::getInstance()->playSoundEffectPiggyBankCrackPig();
			}),
				FadeOut::create(0.1f),
				CallFunc::create([this]() {
				SoundManager::getInstance()->playSoundEffectPiggyBankBreakPig();
				this->breakingPig();
			}), NULL));
		}
		else {
			this->onPurchaseFailed();
		}
		PopupManager::getInstance()->getLoadingAnimation()->hide();
	},
		nullptr,
		[this](sdkbox::Product const&p, const std::string&msg)
	{
		PopupManager::getInstance()->getLoadingAnimation()->hide();
		this->onPurchaseFailed();
	},
		[this](sdkbox::Product const&p)
	{
		PopupManager::getInstance()->getLoadingAnimation()->hide();
		this->onPurchaseFailed();
	}
	);
#else

#if IS_DEBUG
	/*test: break the pig*/
	/*this->stopIdleAnimation();
	this->sprtLightRay->runAction(ScaleTo::create(0.2f, 0));
	this->sprtCoinLightRay->runAction(ScaleTo::create(0.2f, 0));
	this->sprtPigGlow->runAction(ScaleTo::create(0.2f, 0));

	this->groupInfo->runAction(FadeOut::create(0.2f));
	this->groupInfo->runAction(ScaleTo::create(0.2f, 2));
	this->btnBreak->runAction(FadeOut::create(0.2f));
	this->btnBreak->runAction(ScaleTo::create(0.2f, 2));

	this->sprtHammer->runAction(ScaleTo::create(0.2f, 2));
	this->sprtHammer->runAction(Sequence::create(
		MoveTo::create(0.2f, this->btnBreak->getPosition() + Vec2(175, 100)),
		ScaleTo::create(0.05f, -2, 2),
		ScaleTo::create(0.05f, 2, 2),
		ScaleTo::create(0.05f, -2, 2),
		RotateBy::create(0.15f, 45),
		RotateBy::create(0.1f, -100),
		CallFunc::create([this]() {
			SoundManager::getInstance()->playSoundEffectPiggyBankBreakPig2();
	}),
		CallFunc::create([this]() {
		SoundManager::getInstance()->playSoundEffectPiggyBankCrackPig();
	}),
		FadeOut::create(0.1f),
		CallFunc::create([this]() {
		SoundManager::getInstance()->playSoundEffectPiggyBankBreakPig();
		this->breakingPig();
	}), NULL));
	return;*/
	PopupManager::getInstance()->getNotificationPopup()->showDontSupportPopup(
		this->getParent()
	);
	this->onPurchaseFailed();
#else
	PopupManager::getInstance()->getNotificationPopup()->showDontSupportPopup(
		this->getParent()
	);
	this->onPurchaseFailed();
#endif
#endif
}

void PiggyBankPopup::breakingPig()
{
	this->groupPig->runAction(FShake::actionWithDuration(1.5f, 15));
	this->sprtPigBreakMask->runAction(
		Sequence::createWithTwoActions(
			FadeIn::create(1.5f),
			CallFunc::create([this]() {
		this->groupPig->runAction(ScaleTo::create(0.2f, 1.1f));
		this->groupPig->runAction(FadeOut::create(0.2f));
		this->groupBreaking->playAnimation();

		this->runAction(Sequence::createWithTwoActions(DelayTime::create(1.5f), CallFunc::create([this]() {
			this->hide();
		})));
		PopupManager::getInstance()->getHeaderLobbyLayout()->reloadUIHeaderAndCheckShowPopupLevelUp();
		SoundManager::getInstance()->playSoundEffectPiggyBankFinish();
		AnimationCoinCrown::create(Helper4Scene::getRunningScene(), this->aCoins[0]->getParent()->convertToWorldSpace(this->aCoinPos[aCoinPos.size() - 1]), this->piggyBankInfo->piggyBankCoin);
	})));
}

void PiggyBankPopup::runCoinAnimation(int index)
{
	float randValue = RandomHelper::random_int(100, 200) / 7.5f;

	Vec2 position = aCoinLocalPosition[index] + Vec2(0, 50);
	position.normalize();
	position *= randValue;
	if (index == 3) {
		aCoins[index]->runAction(Sequence::create(
			MoveTo::create(0.35f, aCoinPos[index] + position),
			MoveTo::create(0.35f, aCoinPos[index]),
			CallFunc::create([this, index]() {
			SoundManager::getInstance()->playSoundEffectPiggyBankCoinShake();
		}),
			DelayTime::create(2),
			CallFunc::create([this, index]() {
			this->runCoinAnimation(index);
		}), NULL));
		return;
	}
	aCoins[index]->runAction(Sequence::create(
		MoveTo::create(0.35f, aCoinPos[index] + position),
		MoveTo::create(0.35f, aCoinPos[index]),
		CallFunc::create([this, index]() {
		this->runCoinAnimation(index);
	}), NULL));
}

void PiggyBankPopup::reset()
{
	this->stopAllAnimations();
	closeBtn->setVisible(true);
	BasePopup::reset();
}

void PiggyBankPopup::prepareAndShow(cocos2d::Node * parent)
{
	this->sprtLightRay->setOpacity(255);
	this->sprtPigGlow->setOpacity(255);
	this->sprtLightRay->setScale(1);
	this->sprtPigGlow->setScale(1);
	this->sprtPigBreakMask->setOpacity(0);

	this->sprtPigTail->setScaleY(1);
	this->groupPig->setScale(1);
	this->groupPig->setRotation(0);
	this->groupPig->setOpacity(255);
	for (int i = 0, size = aCoins.size(); i < size; ++i) {
		aCoins[i]->setPosition(aCoinPos[i]);
	}
	this->groupInfo->setOpacity(255);
	this->groupInfo->setScale(1.0f);
	this->btnBreak->setScale(1.1f, 1);
	this->btnBreak->setOpacity(255);
	this->btnBreak->setTouchEnabled(true);
	this->btnBreakMask->setScaleY(1.0f);
	this->btnBreakMask->setOpacity(0);
	this->sprtHammer->setScale(1);
	this->sprtHammer->setOpacity(255);
	this->sprtHammer->setRotation(0);
	this->sprtHammer->setPosition(this->btnBreak->getPosition() + Vec2(this->btnBreak->getContentSize().width / 1.8f, -this->sprtHammer->getContentSize().height / 2));

	PopupManager::getInstance()->getLoadingAnimation()->prepareAndShow(parent);
	InfoManager::getInstance()->reloadAdditionalInfo([this, parent](bool isSuccess, AdditionalInfo* result) {
		if (isSuccess) {
			this->piggyBankInfo = InfoManager::getInstance()->getAdditionalInfo()->piggyBankInfo;

			this->txtCoin->setString(UtilFunction::FormatWithCommas(this->piggyBankInfo->piggyBankCoin));
			/*if (this->piggyBankInfo->piggyBankCoin > 0) {
				this->btnBreak->setVisible(true);
				this->sprtHammer->setVisible(true);
			}else {
				this->btnBreak->setVisible(false);
				this->sprtHammer->setVisible(false);
			}*/

			this->startIdleAnimation();
			BasePopup::showWithQueue(parent);
		}
		PopupManager::getInstance()->getLoadingAnimation()->hide();
	});
}

bool BreakingPiggyBankUI::init()
{
	if (!Node::init()) return false;
	pigGlow = Sprite::createWithSpriteFrameName(FRAME_PIGGY_BANK_BREAK_PIG_GLOW);
	pigGlow->setPositionY(-70);
	this->addChild(pigGlow);

	pigBodyBehind = Sprite::createWithSpriteFrameName(FRAME_PIGGY_BANK_BREAK_PIG_BODY_BEHIND);
	this->addChild(pigBodyBehind);

	coinsBehind = Sprite::createWithSpriteFrameName(FRAME_PIGGY_BANK_BREAK_COIN_BEHIND);
	this->addChild(coinsBehind);

	pigHead = Sprite::createWithSpriteFrameName(FRAME_PIGGY_BANK_BREAK_PIG_HEAD);
	this->addChild(pigHead);

	pigBodyFront1 = Sprite::createWithSpriteFrameName(FRAME_PIGGY_BANK_BREAK_PIG_BODY_FRONT_1);
	this->addChild(pigBodyFront1);

	pigBodyFront2 = Sprite::createWithSpriteFrameName(FRAME_PIGGY_BANK_BREAK_PIG_BODY_FRONT_2);
	this->addChild(pigBodyFront2);

	coinsFront = Sprite::createWithSpriteFrameName(FRAME_PIGGY_BANK_BREAK_COIN_FRONT);
	this->addChild(coinsFront);

	flashLight = Sprite::createWithSpriteFrameName(FRAME_PIGGY_BANK_BREAK_LIGHT);
	this->addChild(flashLight);

	coinsFront->setPositionX(30);
	coinsBehind->setPositionX(30);
	coinsFront->setScale(0.5);
	coinsBehind->setScale(0.5);
	pigBodyBehind->setPosition(235, 110);
	pigHead->setPosition(-110, 120);
	pigBodyFront1->setPosition(-50, -50);
	pigBodyFront2->setPosition(225, -50);
	flashLight->setScale(6, 3);

	this->setVisible(false);

	this->setCascadeOpacityEnabled(true);

	return true;
}

void BreakingPiggyBankUI::playAnimation()
{

	this->setOpacity(0);
	flashLight->setOpacity(255);
	pigGlow->setOpacity(0);
	pigHead->setRotation(0);

	coinsBehind->setScale(0.25f);
	coinsFront->setScale(0.25f);
	pigBodyBehind->setPosition(235, 110);
	pigHead->setPosition(-110, 120);
	pigBodyFront1->setPosition(-50, -50);
	pigBodyFront2->setPosition(225, -50);
	flashLight->setScale(6, 3);

	coinsBehind->setPositionY(0);
	coinsFront->setPositionY(0);

	this->runAction(FadeIn::create(0.2f));
	this->runAction(Sequence::createWithTwoActions(
		DelayTime::create(0.05f),
		CallFunc::create([this]() {
		this->coinsBehind->runAction(ScaleTo::create(0.15f, 1.0f));
		this->coinsBehind->runAction(MoveBy::create(0.2f, Vec2(0, -145)));
		this->coinsFront->runAction(ScaleTo::create(0.15f, 1.0f));
		this->coinsFront->runAction(MoveBy::create(0.2f, Vec2(0, -145)));
	})));

	this->flashLight->runAction(ScaleTo::create(0.4f, 12, 6));
	this->flashLight->runAction(FadeOut::create(0.6f));
	this->pigGlow->runAction(FadeIn::create(0.4f));

	this->pigHead->runAction(MoveBy::create(0.4f, Vec2(-140, -130)));
	this->pigHead->runAction(Sequence::create(
		RotateTo::create(0.2, 10),
		RotateTo::create(0.1, -5),
		RotateTo::create(0.1, 0),
		NULL));

	this->pigBodyBehind->runAction(MoveBy::create(0.5f, Vec2(90, -80)));
	this->pigBodyBehind->runAction(Sequence::create(
		RotateTo::create(0.2, 5),
		RotateTo::create(0.1, -10),
		RotateTo::create(0.1, 0),
		NULL));

	this->pigBodyFront1->runAction(MoveBy::create(0.5f, Vec2(-10, -80)));

	this->pigBodyFront2->runAction(MoveBy::create(0.5f, Vec2(10, -80)));
	this->pigBodyFront2->runAction(Sequence::create(
		RotateTo::create(0.2, 5),
		RotateTo::create(0.1, -10),
		RotateTo::create(0.1, 0),
		NULL));

	this->setVisible(true);
}

void BreakingPiggyBankUI::stopAnimation()
{
	this->setVisible(false);
	this->stopAllActions();
	for (auto child : this->getChildren()) {
		child->stopAllActions();
	}
}

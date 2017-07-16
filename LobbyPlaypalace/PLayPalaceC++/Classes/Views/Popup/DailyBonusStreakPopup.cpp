#include "DailyBonusStreakPopup.h"
#include "Manager/InfoManager.h"
#include "Manager/NetworkManager.h"
#include "Manager/PopupManager.h"
#include "Manager/StrategyManager.h"
#include "Views/Popup/LoadingAnimation.h"
#include "Views/Effects/AnimationCoinCrown.h"
#include "Views/Lobby/header/HeaderLobbyLayout.h"
#include "Constant/Defination.h"
#include "Constant/ResultCodeConstant.h"
#include "Constant/LanguageConstant.h"
#include "Info/AdditionalInfo.h"
#include "Util/UtilFunction.h"
#include "Custom/Common/LabelAutoSize.h"
#include "Configs.h"
#include "Helper/Helper4Scene.h"

USING_NS_CC;
using namespace std;



bool DailyBonusStreakItem::init()
{
	if (!Node::init()) return false;
	this->setCascadeOpacityEnabled(true);

	this->sprtBg = Sprite::createWithSpriteFrameName(FRAME_DAILY_BONUS_DAY);
	this->addChild(this->sprtBg);

	this->sprtCoin = Sprite::createWithSpriteFrameName(FRAME_DAILY_BONUS_COIN_1);
	//this->sprtCoin->setPosition(this->sprtBg->getContentSize() / 2);
	this->addChild(this->sprtCoin, 1);

	this->txtMoney = LabelAutoSize::createWithTTF("10,000", FONT_PassionOne_Bold, 34);
	((LabelAutoSize*)this->txtMoney)->setTextAreaSize(Size(this->sprtBg->getContentSize().width * 0.9f, 100));
	this->addChild(this->txtMoney, 1);

	this->txtDay = LabelAutoSize::createWithTTF("DAY 1", FONT_PassionOne_Bold, 25);
	((LabelAutoSize*)this->txtDay)->setTextAreaSize(Size(this->sprtBg->getContentSize().width * 0.6f, 100));
	this->addChild(this->txtDay);

	this->sprtCheck = Sprite::createWithSpriteFrameName(FRAME_DAILY_BONUS_DAY_CHECK);
	this->sprtCheck->setPosition(-this->sprtBg->getContentSize().width * 3 / 10, -this->sprtBg->getContentSize().height * 3 / 8);
	this->sprtCheck->setVisible(false);
	this->addChild(this->sprtCheck);

	return true;
}

void DailyBonusStreakItem::setInfo(int iDay, double iMoney, DailyBonusStreakItemType type)
{
	this->txtDay->setString("DAY " + ToString(iDay));
	this->txtMoney->setString(UtilFunction::FormatWithCommas(iMoney));
	if (iDay == 7)
	{
		this->txtMoney->setString("Magic Item");
	}

	bool isNotPassed = false;
	switch (type)
	{
	case PASSED_DAY:
		this->sprtCheck->setVisible(true);

		this->txtMoney->disableEffect(LabelEffect::SHADOW);
		this->txtMoney->setPosition(0, this->sprtBg->getContentSize().height / 3);
		this->txtMoney->setTextColor(Color4B(255, 255, 0, 255));

		this->txtDay->setPosition(0, -this->sprtBg->getContentSize().height * 3 / 7.5f);
		this->txtDay->setRotation(0);

		this->sprtBg->setSpriteFrame(FRAME_DAILY_BONUS_DAY);
		break;
	case NOT_PASSED_DAY:
		this->sprtCheck->setVisible(false);

		this->txtMoney->disableEffect(LabelEffect::SHADOW);
		this->txtMoney->setPosition(0, this->sprtBg->getContentSize().height / 3);
		this->txtMoney->setTextColor(Color4B(129, 96, 159, 255));

		this->txtDay->setPosition(0, -this->sprtBg->getContentSize().height * 3 / 7.5f);
		this->txtDay->setRotation(0);

		this->sprtBg->setSpriteFrame(FRAME_DAILY_BONUS_DAY_NEXT);

		isNotPassed = true;
		break;
	case STREAK_DAY:
		this->sprtCheck->setVisible(false);

		this->txtMoney->enableShadow();
		this->txtMoney->setPosition(0, -this->sprtBg->getContentSize().height / 3);
		this->txtMoney->setTextColor(Color4B(255, 255, 0, 255));

		this->txtDay->setPosition(-this->sprtBg->getContentSize().width / 4, this->sprtBg->getContentSize().height / 3);
		this->txtDay->setRotation(-45);

		this->sprtBg->setSpriteFrame(FRAME_DAILY_BONUS_DAY_STREAK);
		break;
	default:
		break;
	}



	auto frameCoin = "";
	switch (iDay)
	{
	case 1:
		frameCoin = isNotPassed ? FRAME_DAILY_BONUS_COIN_NEXT_1 : FRAME_DAILY_BONUS_COIN_1;
		break;
	case 2:
		frameCoin = isNotPassed ? FRAME_DAILY_BONUS_COIN_NEXT_1 : FRAME_DAILY_BONUS_COIN_1;
		break;
	case 3:
	case 4:
		frameCoin = isNotPassed ? FRAME_DAILY_BONUS_COIN_NEXT_3_4 : FRAME_DAILY_BONUS_COIN_3_4;
		break;
	case 5:
	case 6:
		frameCoin = isNotPassed ? FRAME_DAILY_BONUS_COIN_NEXT_5_6 : FRAME_DAILY_BONUS_COIN_5_6;
		break;
	case 7:
		frameCoin = isNotPassed ? PNG_DAILY_BONUS_MG_ITEM_NEXT_7 : PNG_DAILY_BONUS_MG_ITEM_7;
		break;
	default:
		break;
	}

	if (iDay == 7)
	{
		this->sprtCoin->initWithFile(frameCoin);
		this->sprtCoin->setScale(0.8f);
	}
	else
	{
		this->sprtCoin->setSpriteFrame(frameCoin);
		this->sprtCoin->setScale(1.0f);
	}
}

bool DailyBonusStreakPopup::init()
{
	if (!BasePopup::init()) {
		return false;
	}

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PLIST_DAILY_BONUS_STREAK);



	spriteBg = Sprite::createWithSpriteFrameName(FRAME_DAILY_BONUS_BG);
	spriteBg->setPosition((Vec2)visibleSize / 2 + Vec2(0, -50) + origin);
	this->addChild(spriteBg);

	this->spriteLightRay = Sprite::createWithSpriteFrameName(FRAME_DAILY_BONUS_DAY_SHINY);
	this->addChild(this->spriteLightRay);

	int itemWidth = 166;
	int distanceX = itemWidth + 11;
	float posX = spriteBg->getPosition().x - spriteBg->getContentSize().width / 2 + 55 + itemWidth / 2;
	float posY = spriteBg->getPosition().y - 15;

	for (int i = 0; i < 7; ++i) {
		auto day = DailyBonusStreakItem::create();
		day->setPosition(posX, posY);
		this->addChild(day);

		this->aDayUI.push_back(day);

		posX += distanceX;
	}

	auto logo = Sprite::createWithSpriteFrameName(FRAME_DAILY_BONUS_LOGO);
	logo->setPosition(spriteBg->getPosition() + Vec2(0, spriteBg->getContentSize().height / 2));
	this->addChild(logo, 1);

	this->particle = ParticleSystemQuad::create(PARTICLE_DAILY_BONUS_STREAK);
	this->particle->setCascadeOpacityEnabled(true);
	this->particle->setPositionType(ParticleSystem::PositionType::GROUPED);
	this->particle->setPosition(logo->getPosition() + Vec2(0, -15));
	this->addChild(this->particle, 1);

	this->btnCollect = this->createGreenButton(true,Language(nullptr, LanguageConstant::COLLECT));
	this->btnCollect->addTouchEventListener(CC_CALLBACK_2(DailyBonusStreakPopup::onCollect, this));
	this->btnCollect->setPosition(spriteBg->getPosition() + Vec2(0, -spriteBg->getContentSize().height / 2.8f));
	this->addChild(this->btnCollect);

	return true;
}

void DailyBonusStreakPopup::reset()
{
	this->particle->stop();
	this->spriteLightRay->stopAllActions();
	BasePopup::reset();
}


void DailyBonusStreakPopup::onCollect(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED) {
		PopupManager::getInstance()->getLoadingAnimation()->prepareAndShow(this->getParent());
		double coinReward = InfoManager::getInstance()->getAdditionalInfo()->dailyBonusStreakInfo->coinReward;
		NetworkManager::getInstance()->collectDailyBonusStreak(
			[this, coinReward](int coreResultCode, rapidjson::Value&responseAsDocument, std::string responseAsString) {
			if (coreResultCode == RESULT_CODE_VALID) {
				InfoManager::getInstance()->getAdditionalInfo()->dailyBonusStreakInfo->canCollect = false;
				PopupManager::getInstance()->getHeaderLobbyLayout()->increaseCoin(coinReward);
				AnimationCoinCrown::create(
					Helper4Scene::getRunningScene(),
					this->btnCollect->getPosition(),
					coinReward
				);
			}
			else {
				NetworkFailProcessInfo info;
				info.core_result_code = coreResultCode;
				StrategyManager::getInstance()->handleFailResultNewStrategy(info, false, true);
			}
			PopupManager::getInstance()->getLoadingAnimation()->hide();
			this->hide();
		},
			[this](std::string result) {
			NetworkFailProcessInfo info;
			info.errorMessage = result;
			StrategyManager::getInstance()->handleFailResultNewStrategy(info, false, false);
			PopupManager::getInstance()->getLoadingAnimation()->hide();
			this->hide();
		},
			[this](std::string result) {
			NetworkFailProcessInfo info;
			info.errorMessage = result;
			StrategyManager::getInstance()->handleFailResultNewStrategy(info, false, false);
			PopupManager::getInstance()->getLoadingAnimation()->hide();
			this->hide();
		});
	}
}

void DailyBonusStreakPopup::prepareAndShow(cocos2d::Node * parent)
{
	auto currentBonusStreak = InfoManager::getInstance()->getAdditionalInfo()->dailyBonusStreakInfo;
	if (!currentBonusStreak->canCollect) return;

	this->particle->start();
	this->btnCollect->getTitleRenderer()->setString(Language(btnCollect->getTitleRenderer(),LanguageConstant::COLLECT));

	auto bonusStreakConfig = InfoManager::getInstance()->getListDailyBonusStreakConfig();

	for (int i = 0, size = this->aDayUI.size(); i < size; ++i) {
		auto day = this->aDayUI[i];
		day->setLocalZOrder(currentBonusStreak->dailyStreak - 1 == i ? 1 : 0);
		day->setInfo(i + 1, bonusStreakConfig[i]->info,
			currentBonusStreak->dailyStreak - 1 > i ?
			DailyBonusStreakItemType::PASSED_DAY : (
				currentBonusStreak->dailyStreak - 1 == i ?
				DailyBonusStreakItemType::STREAK_DAY :
				DailyBonusStreakItemType::NOT_PASSED_DAY
				)
		);
	}
	this->spriteLightRay->retain();
	this->spriteLightRay->removeFromParent();
	this->aDayUI[currentBonusStreak->dailyStreak - 1]->addChild(this->spriteLightRay);
	this->spriteLightRay->autorelease();

	this->spriteLightRay->setOpacity(255);
	this->spriteLightRay->runAction(RepeatForever::create(RotateBy::create(0.5f, 60)));
	this->spriteLightRay->runAction(RepeatForever::create(
		Sequence::createWithTwoActions(
			ScaleTo::create(0.7f, 0.7f),
			ScaleTo::create(0.7f, 1.0f)
	)));
	this->spriteLightRay->runAction(RepeatForever::create(
		Sequence::createWithTwoActions(
			FadeTo::create(0.7f, 150),
			FadeTo::create(0.7f, 255)
		)));

	BasePopup::showWithQueue(parent);
}

#include "DailyBonusWheelResultPopup.h"
#include "DailyBonusWheelPopup.h"
#include "Constant/Defination.h"
#include "Constant/LanguageConstant.h"
#include "Manager/InfoManager.h"
#include "Info/AdditionalInfo.h"
#include "Helper/Helper4Sprite.h"


USING_NS_CC;
#define DELAY_TIME_SHOW_LABELS 0.7f
#define DELAY_TIME_BETWEEN_SHOWS 0.5f

DailyBonusWheelResultPopup * DailyBonusWheelResultPopup::create(DailyBonusWheelPopup * parent)
{
	DailyBonusWheelResultPopup* resultPopup = new (std::nothrow) DailyBonusWheelResultPopup();
	resultPopup->_parent = parent;
	if (resultPopup && resultPopup->init())
	{
		resultPopup->autorelease();
		return resultPopup;
	}
	CC_SAFE_DELETE(resultPopup);
	return nullptr;
}

bool DailyBonusWheelResultPopup::init()
{
	if (!BasePopup::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	//BG
	auto bg = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_DAILY_BONUS_WHEEL_RESULT_POPUP_BACKGROUND);
	bg->setPosition(origin + visibleSize / 2);
	bg->setCascadeOpacityEnabled(true);
	this->addChild(bg);

	auto ttfConfig = TTFConfig(FONT_PassionOne_Regular, 50);
	auto titleColor = Color4B::WHITE;
	auto valueColor = Color4B(233, 193, 82, 255);

	//WHEEL BONUS
	auto wheelBonusTitleLabel = Label::createWithTTF(
		ttfConfig,
		"Wheel Bonus"
	);
	wheelBonusTitleLabel->setTextColor(titleColor);

	auto wheelBonusValueLabel = Label::createWithTTF(
		ttfConfig,
		"1000"
	);
	wheelBonusValueLabel->setTextColor(valueColor);

	this->wheelBonusLabel = TitleValueLabel::create(wheelBonusTitleLabel, wheelBonusValueLabel, 15);
	this->wheelBonusLabel->setPosition(bg->getContentSize() / 2 + Size(0, 110));
	bg->addChild(this->wheelBonusLabel);

	//LEVEL BONUS
	auto levelBonusTitleLabel = Label::createWithTTF(
		ttfConfig,
		"Level Bonus"
	);
	levelBonusTitleLabel->setTextColor(titleColor);

	auto levelBonusValueLabel = Label::createWithTTF(
		ttfConfig,
		"x1000"
	);
	levelBonusValueLabel->setTextColor(valueColor);

	this->levelBonusLabel = TitleValueLabel::create(levelBonusTitleLabel, levelBonusValueLabel, 15);
	this->levelBonusLabel->setPosition(this->wheelBonusLabel->getPosition() + Vec2(0, -55));
	bg->addChild(this->levelBonusLabel);

	//FRIEND BONUS
	auto friendBonusTitleLabel = Label::createWithTTF(
		ttfConfig,
		"Friend Bonus"
	);
	friendBonusTitleLabel->setTextColor(titleColor);

	auto friendBonusValueLabel = Label::createWithTTF(
		ttfConfig,
		"x1000"
	);
	friendBonusValueLabel->setTextColor(valueColor);

	this->friendBonusLabel = TitleValueLabel::create(friendBonusTitleLabel, friendBonusValueLabel, 15);
	this->friendBonusLabel->setPosition(this->levelBonusLabel->getPosition() + Vec2(0, -55));
	bg->addChild(this->friendBonusLabel);

	//VIP
	auto vipBonusTitleLabel = Label::createWithTTF(
		ttfConfig,
		"VIP"
	);
	vipBonusTitleLabel->setTextColor(titleColor);

	auto vipBonusValueLabel = Label::createWithTTF(
		ttfConfig,
		"+100%"
	);
	vipBonusValueLabel->setTextColor(valueColor);

	this->vipLabel = TitleValueLabel::create(vipBonusTitleLabel, vipBonusValueLabel, 15);
	this->vipLabel->setPosition(this->friendBonusLabel->getPosition() + Vec2(0, -55));
	bg->addChild(this->vipLabel);

	//TOTAL COIN
	this->coinSprite = Helper4Sprite::createOptimizeSprite(PNG_SHOP_COIN_ICON);
	this->coinSprite->setPosition(this->vipLabel->getPosition() + Vec2(-50, -75));
	this->coinSprite->setCascadeOpacityEnabled(true);
	bg->addChild(this->coinSprite);

	this->totalCoinLabel = Label::createWithTTF(
		ttfConfig,
		"9,000"
	);
	this->totalCoinLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	this->totalCoinLabel->setHorizontalAlignment(TextHAlignment::LEFT);
	this->totalCoinLabel->setPosition(80, this->coinSprite->getContentSize().height / 2);
	this->coinSprite->addChild(this->totalCoinLabel);

	//LENS FLARE YELLOW
	this->lensFlareYellowGroup = Node::create();
	this->lensFlareYellowGroup->setCascadeOpacityEnabled(true);
	for (int i = 0; i < 8; i++)
	{
		auto spriteYellow = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_DAILY_BONUS_WHEEL_RESULT_POPUP_START_YELLOW);
		spriteYellow->setBlendFunc(BlendFunc::ADDITIVE);
		spriteYellow->setPosition(
			RandomHelper::random_int(-50, 50),
			RandomHelper::random_int(-30, 30)
		);
		this->lensFlareYellowGroup->addChild(spriteYellow);
	}
	this->lensFlareYellowGroup->setPosition(this->coinSprite->getPosition());
	bg->addChild(this->lensFlareYellowGroup);

	//LENS FLARE WHITE
	this->lensFlareWhiteGroup = Node::create();
	this->lensFlareWhiteGroup->setCascadeOpacityEnabled(true);

	int xPosition = -100;
	for (int i = 0; i < 5; i++)
	{
		auto spriteWhite = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_DAILY_BONUS_WHEEL_RESULT_POPUP_START_WHITE);
		spriteWhite->setBlendFunc(BlendFunc::ADDITIVE);
		spriteWhite->setPosition(xPosition,/*Helper::random_int(-80, 80),*/30/*RandomHelper::random_int(-30, 30)*/);
		this->lensFlareWhiteGroup->addChild(spriteWhite);

		spriteWhite = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_DAILY_BONUS_WHEEL_RESULT_POPUP_START_WHITE);
		spriteWhite->setBlendFunc(BlendFunc::ADDITIVE);
		spriteWhite->setPosition(xPosition/*RandomHelper::random_int(-80, 80)*/,-30/*RandomHelper::random_int(-30, 30)*/);
		this->lensFlareWhiteGroup->addChild(spriteWhite);
		xPosition += 30;
	}
	this->lensFlareWhiteGroup->setPosition(this->coinSprite->getPosition() + Vec2(170, 0));
	bg->addChild(this->lensFlareWhiteGroup);

	//COLLECT BUTTON
	this->collectButton = this->createGreenButton(true,LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::COLLECT));
	this->collectButton->setPosition(bg->getContentSize() / 2 
		+ Size(0, -bg->getContentSize().height / 2 + this->collectButton->getContentSize().height * 1.4f)
	);
	this->collectButton->addTouchEventListener([this](cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
	{
		if (type != cocos2d::ui::Widget::TouchEventType::ENDED) {
			return;
		}

		this->_parent->collectCoin(this->collectButton->getParent()->convertToWorldSpace(this->collectButton->getPosition()));
	});
	bg->addChild(this->collectButton);
	
	return true;
}

void DailyBonusWheelResultPopup::reset()
{
	BasePopup::reset();
	this->coinSprite->setOpacity(0);
	this->wheelBonusLabel->setOpacityForLabels(0);
	this->levelBonusLabel->setOpacityForLabels(0);
	this->friendBonusLabel->setOpacityForLabels(0);
	this->vipLabel->setOpacityForLabels(0);
	this->collectButton->setVisible(false);

	this->lensFlareWhiteGroup->stopAllActions();
	this->lensFlareWhiteGroup->setOpacity(0);
	this->lensFlareWhiteGroup->setRotation(0);
	this->lensFlareWhiteGroup->setScale(0.3f);


	this->lensFlareYellowGroup->stopAllActions();
	this->lensFlareYellowGroup->setOpacity(0);
	this->lensFlareYellowGroup->setRotation(0);
	this->lensFlareYellowGroup->setScale(0.3f);
}

void DailyBonusWheelResultPopup::prepareAndShow()
{
	this->reset();
	BasePopup::show(this->_parent);

	auto dailyWheelBonusInfo = InfoManager::getInstance()->getAdditionalInfo()->dailyBonusWheelInfo;
	auto showWheelBonusLabel = CallFunc::create([this, dailyWheelBonusInfo]()
	{
		this->wheelBonusLabel->getValueLabel()->setString(UtilFunction::FormatWithCommas(dailyWheelBonusInfo->coin * dailyWheelBonusInfo->factor));
		this->wheelBonusLabel->resetPosAndShowWithPartical();
	});
	auto showLevelBonusLabel = CallFunc::create([this, dailyWheelBonusInfo]()
	{
		this->levelBonusLabel->getValueLabel()->setString(UtilFunction::FormatWithCommas(dailyWheelBonusInfo->levelBonus));
		this->levelBonusLabel->resetPosAndShowWithPartical();
	});
	auto showFriendBonusLabel = CallFunc::create([this, dailyWheelBonusInfo]()
	{
		this->friendBonusLabel->getValueLabel()->setString("x" + ToString(dailyWheelBonusInfo->numberOfFriend));
		this->friendBonusLabel->resetPosAndShowWithPartical();
	});
	auto showVipLabel = CallFunc::create([this, dailyWheelBonusInfo]()
	{
		this->vipLabel->getValueLabel()->setString("+" + ToString((int)(dailyWheelBonusInfo->vipBenefit * 100)) + "%");
		this->vipLabel->resetPosAndShowWithPartical();
	});
	auto showTotalCoin = CallFunc::create([this, dailyWheelBonusInfo]()
	{
		this->coinSprite->runAction(FadeIn::create(0.1f));
		this->totalCoinLabel->setString(UtilFunction::FormatWithCommas(dailyWheelBonusInfo->totalCoin));

		auto runActionLensFlare = [](cocos2d::Node *group)
		{
			group->runAction(ScaleTo::create(0.3f, 1));
			group->runAction(FadeIn::create(0.3f));
			group->runAction(Sequence::createWithTwoActions(
				DelayTime::create(0.3f),
				FadeOut::create(0.3f)
			));
			for (auto child : group->getChildren()){
				child->runAction(Sequence::createWithTwoActions(
					RotateBy::create(0.3f, 80),
					RotateTo::create(0.3f, 0)
				));
			}
		};
		runActionLensFlare(this->lensFlareWhiteGroup);
		runActionLensFlare(this->lensFlareYellowGroup);
	});
	auto showCollectButton = CallFunc::create([this]()
	{
		this->collectButton->setVisible(true);
	});

	this->runAction(Sequence::create(
		DelayTime::create(DELAY_TIME_SHOW_LABELS),
		showWheelBonusLabel,
		DelayTime::create(DELAY_TIME_BETWEEN_SHOWS),
		showLevelBonusLabel,
		DelayTime::create(DELAY_TIME_BETWEEN_SHOWS),
		showFriendBonusLabel,
		DelayTime::create(DELAY_TIME_BETWEEN_SHOWS),
		showVipLabel,
		DelayTime::create(DELAY_TIME_BETWEEN_SHOWS),
		showTotalCoin,
		DelayTime::create(DELAY_TIME_BETWEEN_SHOWS),
		showCollectButton,
		nullptr
	));
}

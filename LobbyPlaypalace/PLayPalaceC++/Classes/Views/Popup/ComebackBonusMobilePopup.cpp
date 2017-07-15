#include "ComebackBonusMobilePopup.h"
#include "Manager/InfoManager.h"
#include "Manager/NetworkManager.h"
#include "Manager/PopupManager.h"
#include "Views/Popup/LoadingAnimation.h"
#include "Views/Lobby/header/HeaderLobbyLayout.h"
#include "Views/Effects/AnimationCoinCrown.h"
#include "Constant/Defination.h"
#include "Constant/ResultCodeConstant.h"
#include "Info/AdditionalInfo.h"
#include "Util/UtilFunction.h"
#include "Configs.h"
#include "Helper/Helper4Sprite.h"

USING_NS_CC;
using namespace std;
#define INCREASE_REWARD_COIN_ACTION_DURATION 2 

void ComebackBonusMobilePopup::collectTouched(cocos2d::Ref * ref, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != cocos2d::ui::Widget::TouchEventType::ENDED) 
	{
		return;
	}
	PopupManager::getInstance()->getLoadingAnimation()->prepareAndShow(this->getParent());
	NetworkManager::getInstance()->collectComebackBonusMobile(
		[this](int coreResultCode, rapidjson::Value&responseAsDocument, std::string responseAsString)
	{
		PopupManager::getInstance()->getLoadingAnimation()->hide();
		if (coreResultCode == RESULT_CODE_VALID)
		{
			auto comebackBonusMobileInfo = InfoManager::getInstance()->getAdditionalInfo()->comebackBonusMobileInfo;
			
			//increase coin on header and run animation
			PopupManager::getInstance()->getHeaderLobbyLayout()->increaseCoin(comebackBonusMobileInfo->coinReward);
			AnimationCoinCrown::create(
				Director::getInstance()->getRunningScene(),
				this->collectButton->getParent()->convertToWorldSpace(this->collectButton->getPosition()),
				comebackBonusMobileInfo->coinReward
			);


			comebackBonusMobileInfo->updateInfoByValue(responseAsDocument);
			comebackBonusMobileInfo->canCollect = false;
		}
		this->hide();
	},
		[this](std::string result)
	{
		PopupManager::getInstance()->getLoadingAnimation()->hide();
		this->hide();
	},
		[this](std::string result)
	{
		PopupManager::getInstance()->getLoadingAnimation()->hide();
		this->hide();
	}
	);
}

bool ComebackBonusMobilePopup::init()
{
	if (!BasePopup::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//BACKGROUND
	auto bg = Helper4Sprite::createOptimizeSprite(PNG_COMEBACK_BONUS_MOBILE_BACKGROUND);
	bg->setCascadeOpacityEnabled(true);
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(bg);

	//COIN LABEL
	this->coinRewardLabel = Label::createWithBMFont(
		FONT_BITMAP_COMEBACK_BONUS_MOBILE,
		"0",
		TextHAlignment::CENTER
	);
	this->coinRewardLabel->setBMFontSize(30);
	this->coinRewardLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	this->coinRewardLabel->setPosition(
		bg->getContentSize() / 2 + Size(-110, -140)
	);
	bg->addChild(this->coinRewardLabel);

	//EXP INCREASE LABEL
	this->expBonusLabel = Label::createWithBMFont(
		FONT_BITMAP_COMEBACK_BONUS_MOBILE,
		"5%",
		TextHAlignment::CENTER
	);
	this->expBonusLabel->setBMFontSize(30);
	this->expBonusLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	this->expBonusLabel->setPosition(
		this->coinRewardLabel->getPosition() + Size(300, 0)
	);
	bg->addChild(this->expBonusLabel);

	//COLLECT BUTTON
	this->collectButton = this->createGreenButton(
		LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::COLLECT)
	);
	this->collectButton->setPosition(
		bg->getContentSize() / 2 + Size(0, -bg->getContentSize().height / 2 + this->collectButton->getContentSize().height / 0.8f)
	);
	this->collectButton->addTouchEventListener(CC_CALLBACK_2(ComebackBonusMobilePopup::collectTouched, this));
	bg->addChild(this->collectButton);

	return true;
}

void ComebackBonusMobilePopup::reset()
{
	BasePopup::reset();
	this->collectButton->setVisible(false);
	this->coinRewardLabel->setString("0");
	this->expBonusLabel->setString("");
}

void ComebackBonusMobilePopup::show()
{
	BasePopup::show();
	auto comebackBonusMobileInfo = InfoManager::getInstance()->getAdditionalInfo()->comebackBonusMobileInfo;
	auto increaseAction = ActionFloat::create(
		INCREASE_REWARD_COIN_ACTION_DURATION,
		0,
		comebackBonusMobileInfo->coinReward,
		[this](double value)
		{
			this->coinRewardLabel->setString(UtilFunction::FormatWithCommas(value));
		}
	);
	this->coinRewardLabel->runAction(Sequence::createWithTwoActions(
		increaseAction,
		CallFunc::create([this]()
		{
			this->collectButton->setVisible(true);
		})
	));
	this->expBonusLabel->setString(ToString(comebackBonusMobileInfo->increasedPercentageOfExp) + "%");
	updateAfterChangeLanguage();
}

void ComebackBonusMobilePopup::prepareAndShow(cocos2d::Node * parent)
{
	/*//DEBUG INFO
	auto comebackBonusMobileInfo = InfoManager::getInstance()->getAdditionalInfo()->comebackBonusMobileInfo;
	comebackBonusMobileInfo->coinReward = 50000;
	comebackBonusMobileInfo->increasedPercentageOfExp = 5;*/

	BasePopup::showWithQueue(parent);
	updateAfterChangeLanguage();
}

void ComebackBonusMobilePopup::updateAfterChangeLanguage(){
	this->collectButton->getTitleLabel()->setString(LanguageManager::getInstance()->getStringForKeys(this->collectButton->getTitleLabel(), LanguageConstant::COLLECT));
}

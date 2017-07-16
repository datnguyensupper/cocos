#include "SpecialOfferPopup.h"
#include "Constant/Defination.h"
#include "Constant/ResultCodeConstant.h"
#include "Constant/LanguageConstant.h"
#include "Manager/PopupManager.h"
#include "Views/Lobby/header/HeaderLobbyLayout.h"
#include "Views/Popup/LoadingAnimation.h"
#include "Util/UtilFunction.h"
#include "Helper/Helper4Time.h"

USING_NS_CC;
using namespace std;


bool SpecialOfferPopup::init()
{
	if (!BasePopup::init()) {
		return false;
	}

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PNG_PROMOTIONS_PLIST);

	auto bg = Sprite::createWithSpriteFrameName(FRAME_SPECIAL_OFFER_BG);
	bg->setPosition(origin + Vec2(visibleSize.width / 2.1f, visibleSize.height / 1.9f));
	this->addChild(bg);

	this->txtRemainingTime = Label::createWithTTF("00:00:00", FONT_PassionOne_Bold, 25);
	this->txtRemainingTime->enableShadow();
	this->txtRemainingTime->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	this->txtRemainingTime->setPosition(bg->getPosition() + Vec2(bg->getContentSize().width * 0.3f, -bg->getContentSize().height * 0.295f));
	this->txtRemainingTime->setTextColor(Color4B(255, 255, 191, 255));
	this->addChild(this->txtRemainingTime);

	this->txtRemainingAmount = Label::createWithTTF("0", FONT_PassionOne_Bold, 25);
	this->txtRemainingAmount->enableShadow();
	this->txtRemainingAmount->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	this->txtRemainingAmount->setPosition(this->txtRemainingTime->getPosition() + Vec2(0, -50));
	this->txtRemainingAmount->setTextColor(Color4B(255, 255, 191, 255));
	this->addChild(this->txtRemainingAmount);

	this->btnBuyNow = this->createGreenButton(true, "");
	this->btnBuyNow->setPosition(bg->getPosition() + Vec2(25, -bg->getContentSize().height * 0.35f));
	this->btnBuyNow->addTouchEventListener(CC_CALLBACK_2(SpecialOfferPopup::onButtonTouched, this));
	this->addChild(this->btnBuyNow);

	auto closeBtn = this->createCloseButton();
	closeBtn->setPosition(bg->getPosition() + Vec2(bg->getContentSize().width / 2.1f, bg->getContentSize().height / 2.2f));
	this->addChild(closeBtn);

	return true;
}

void SpecialOfferPopup::reset()
{
	BasePopup::reset();
	this->unschedule(schedule_selector(SpecialOfferPopup::updateTime));
	this->unscheduleAllSelectors();
	this->unscheduleAllCallbacks();
}

void SpecialOfferPopup::updateTime(float dt)
{
	this->info.remainingTime -= dt * 1000;
	this->txtRemainingTime->setString(Helper4Time::millisecondTimeToNormalTimeHourMinAndSecString(this->info.remainingTime));
}

void SpecialOfferPopup::onButtonTouched(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != ui::Widget::TouchEventType::ENDED) return;
	UtilFunction::purchaseItem(IAP_SPECIAL_OFFER, false, [this](int core_result_code, MobilePaymentInfo* info) {
		if (core_result_code == RESULT_CODE_VALID) {
			PopupManager::getInstance()->getHeaderLobbyLayout()->reloadUIHeaderAndCheckShowPopupLevelUp(
				[this](bool isSuccess, LevelUpInfo* info) {
				PopupManager::getInstance()->getLoadingAnimation()->hide();
			}
			);
			this->hide();
		}
	});
}

bool SpecialOfferPopup::prepareAndShow(rapidjson::Value& rawData, cocos2d::Node * parent)
{
	this->info.updateInfoByValue(rawData);

	if (this->info.remainingTime < 5) return false;

	this->btnBuyNow->getTitleLabel()->setString(Language(this->btnBuyNow->getTitleLabel(), LanguageConstant::BUYNOW));

	this->txtRemainingTime->setString(Helper4Time::millisecondTimeToNormalTimeHourMinAndSecString(this->info.remainingTime));
	this->txtRemainingAmount->setString("Left: " + ToString(this->info.remainingAmount));

	this->schedule(schedule_selector(SpecialOfferPopup::updateTime), 1.0f);

	BasePopup::showWithQueue(parent);

	return true;
}

#include "PayToPlayPopup.h"
#include "Constant/Defination.h"
#include "Constant/ResultCodeConstant.h"
#include "Constant/LanguageConstant.h"
#include "Manager/PopupManager.h"
#include "Views/Lobby/header/HeaderLobbyLayout.h"
#include "Views/Popup/LoadingAnimation.h"
#include "Util/UtilFunction.h"

USING_NS_CC;
using namespace std;

bool PayToPlayPopup::init()
{
	if (!BasePopup::init()) {
		return false;
	}

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PNG_PROMOTIONS_PLIST);

	bg = Sprite::createWithSpriteFrameName(FRAME_PAY_TO_PLAY_BG);
	bg->setPosition(origin + visibleSize / 2.0f);
	this->addChild(bg);

	this->txtBonusNow = Label::createWithTTF("200%", FONT_PassionOne_Bold, 60);
	this->txtBonusNow->setPosition(bg->getPosition() +
		Vec2(bg->getContentSize().width * 0.015f, bg->getContentSize().height * 0.11f));
	this->addChild(this->txtBonusNow);

	this->txtCoinNow = this->createText(38, -0.35f, -0.1f);
	this->txtCoinPkgBig = this->createText(30, -0.18f, -0.2f);
	this->txtCoinPkgSmall = this->createText(30, 0.265f, -0.2f);
	this->txtCrownNow = this->createText(38, 0.01f, -0.1f);
	this->txtCrownPkgBig = this->createText(30, -0.08f, -0.245f);
	this->txtCrownPkgSmall = this->createText(30, 0.36f, -0.245f);

	this->btnBuyNow = this->createButtonBuy(1, 1, 0.282f, 0.05f);
	this->btnBuyPkgBig = this->createButtonBuy(0.6f, 0.7f, -0.1f, -0.376f);
	this->btnBuyPkgSmall = this->createButtonBuy(0.6f, 0.7f, 0.34f, -0.376f);

	this->txtMoneyNow = this->createText(50);
	this->txtMoneyNow->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	this->txtMoneyNow->setPosition(this->btnBuyNow->getPosition() + Vec2(0, this->btnBuyNow->getContentSize().height * this->btnBuyPkgBig->getScaleY() / 1.5f));

	this->txtMoneyPkgBig = this->createText(35);
	this->txtMoneyPkgBig->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
	this->txtMoneyPkgBig->setPosition(this->btnBuyPkgBig->getPosition() - Vec2(this->btnBuyPkgBig->getContentSize().width * this->btnBuyPkgBig->getScaleX() / 1.9f, 0));

	this->txtMoneyPkgSmall = this->createText(35);
	this->txtMoneyPkgSmall->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
	this->txtMoneyPkgSmall->setPosition(this->btnBuyPkgSmall->getPosition() - Vec2(this->btnBuyPkgSmall->getContentSize().width * this->btnBuyPkgBig->getScaleX() / 1.9f, 0));

	auto closeBtn = this->createCloseButton();
	closeBtn->setPosition(bg->getPosition() + bg->getContentSize() / 2.1f);
	this->addChild(closeBtn);

	return true;
}

cocos2d::Label * PayToPlayPopup::createText(int fontSize, float percentX, float precentY)
{
	auto txt = Label::createWithTTF("", FONT_PassionOne_Bold, fontSize);
	txt->enableShadow();
	txt->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	txt->setTextColor(Color4B(255, 255, 191, 255));
	txt->setPosition(bg->getPosition() +
		Vec2(bg->getContentSize().width * percentX, bg->getContentSize().height * precentY));
	this->addChild(txt);

	return txt;
}

cocos2d::ui::Button * PayToPlayPopup::createButtonBuy(float scaleX, float scaleY, float percentX, float precentY)
{
	auto btn = this->createGreenButton(true);
	btn->setPosition(bg->getPosition() +
		Vec2(bg->getContentSize().width * percentX, bg->getContentSize().height * precentY));
	btn->setScale(scaleX, scaleY);
	btn->addTouchEventListener(CC_CALLBACK_2(PayToPlayPopup::onButtonTouched, this));
	this->addChild(btn);

	return btn;
}

void PayToPlayPopup::onButtonTouched(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != ui::Widget::TouchEventType::ENDED) return;
	std::string itemID = "";
	if (sender = this->btnBuyPkgSmall) {
		itemID = IAP_PAY_TO_PLAY_P1;
	}
	else if (sender = this->btnBuyPkgBig) {
		itemID = IAP_PAY_TO_PLAY_P2;
	}
	else {
		itemID = IAP_PAY_TO_PLAY_P3;
	}
	UtilFunction::purchaseItem(itemID, false, [this](int core_result_code, MobilePaymentInfo* info) {
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

void PayToPlayPopup::prepareAndShow(cocos2d::Node * parent)
{
	this->btnBuyNow->getTitleLabel()->setString(Language(this->btnBuyNow->getTitleLabel(), LanguageConstant::BUYNOW));
	this->btnBuyPkgBig->getTitleLabel()->setString(Language(this->btnBuyPkgBig->getTitleLabel(), LanguageConstant::BUY));
	this->btnBuyPkgSmall->getTitleLabel()->setString(Language(this->btnBuyPkgSmall->getTitleLabel(), LanguageConstant::BUY));

	this->txtCoinNow->setString(UtilFunction::FormatWithCommas(210000000));
	this->txtCoinPkgBig->setString(UtilFunction::FormatWithCommas(72000000));
	this->txtCoinPkgSmall->setString(UtilFunction::FormatWithCommas(4320000));

	this->txtCrownNow->setString(UtilFunction::FormatWithCommas(25));
	this->txtCrownPkgBig->setString(UtilFunction::FormatWithCommas(10));
	this->txtCrownPkgSmall->setString(UtilFunction::FormatWithCommas(5));

	this->txtMoneyNow->setString("$49.99");
	this->txtMoneyPkgBig->setString("$19.99");
	this->txtMoneyPkgSmall->setString("$4.99");

	BasePopup::showWithQueue(parent);
}

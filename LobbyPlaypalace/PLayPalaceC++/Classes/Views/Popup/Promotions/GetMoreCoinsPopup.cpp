#include "GetMoreCoinsPopup.h"
#include "Constant/Defination.h"
#include "Constant/ResultCodeConstant.h"
#include "Constant/LanguageConstant.h"
#include "Manager/PopupManager.h"
#include "Views/Lobby/header/HeaderLobbyLayout.h"
#include "Views/Popup/LoadingAnimation.h"
#include "Views/Popup/Shop/ShopPopup.h"
#include "Util/UtilFunction.h"


USING_NS_CC;
using namespace std;
bool GetMoreCoinsPopup::init()
{
	if (!BasePopup::init()) {
		return false;
	}

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PNG_PROMOTIONS_PLIST);

	auto bg = Sprite::createWithSpriteFrameName(FRAME_GET_MORE_COINS_BG);
	bg->setPosition(origin + visibleSize / 2.0f + Vec2(-52, 19));
	this->addChild(bg);

	this->txtCoin = Label::createWithTTF("", FONT_PassionOne_Bold, 45);
	this->txtCoin->enableShadow();
	this->txtCoin->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	this->txtCoin->setTextColor(Color4B(255, 255, 191, 255));
	this->txtCoin->setPosition(origin + visibleSize / 2.0f +
		Vec2(bg->getContentSize().width * 0.07f, -bg->getContentSize().height * 0.17f));
	this->addChild(this->txtCoin);

	this->btnShop = this->createGreenButton(true);
	this->btnShop->setPosition(origin + visibleSize / 2.0f -
		Vec2(bg->getContentSize().width * 0.16f, bg->getContentSize().height * 0.3f));
	this->btnShop->addTouchEventListener(CC_CALLBACK_2(GetMoreCoinsPopup::onButtonTouched, this));
	this->addChild(this->btnShop);

	this->btnBuyNow = this->createGreenButton(true);
	this->btnBuyNow->setPosition(origin + visibleSize / 2.0f -
		Vec2(-bg->getContentSize().width * 0.16f, bg->getContentSize().height * 0.3f));
	this->btnBuyNow->addTouchEventListener(CC_CALLBACK_2(GetMoreCoinsPopup::onButtonTouched, this));
	this->addChild(this->btnBuyNow);

	auto closeBtn = this->createCloseButton();
	closeBtn->setPosition(bg->getPosition() + Vec2(bg->getContentSize().width / 2.1f, bg->getContentSize().height / 2.5f));
	this->addChild(closeBtn);

	return true;
}

void GetMoreCoinsPopup::onButtonTouched(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != ui::Widget::TouchEventType::ENDED) return;
	if (sender == this->btnBuyNow) {
		UtilFunction::purchaseItem(IAP_GET_MORE_COINS, false, [this](int core_result_code, MobilePaymentInfo* info) {
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
	else {
		this->hide();
		PopupManager::getInstance()->getShopPopup()->prepareAndShow(this->getParent(), ShopType::CoinShop);
	}
}

bool GetMoreCoinsPopup::prepareAndShow(cocos2d::Node * parent)
{
	if (PopupManager::getInstance()->isPopupInQueue(this) || this->isVisible()) {
		return false;
	}

	this->txtCoin->setString(UtilFunction::FormatWithCommas(3600000));
	this->btnShop->getTitleLabel()->setString(Language(this->btnShop->getTitleLabel(), LanguageConstant::HEADER_SHOP_TOOLTIP));
	this->btnBuyNow->getTitleLabel()->setString(Language(this->btnBuyNow->getTitleLabel(), LanguageConstant::BUYNOW));

	BasePopup::showWithQueue(parent);

	return true;
}

#include "MissingPopup.h"
#include "Constant/Defination.h"
#include "Util/UtilFunction.h"
#include "Manager/PopupManager.h"
#include "Views/Popup/Shop/ShopPopup.h"
#include "Views/Lobby/header/HeaderLobbyLayout.h"
#include "Configs.h"
#include "Views/Effects/AnimationCoinCrown.h"
#include "Helper/Helper4Scene.h"
#include "Helper/Helper4Sprite.h"

USING_NS_CC;
using namespace std;


bool MissingPopup::init()
{
	if (!BasePopup::init()) {
		return false;
	}

	//BACKGROUND
	auto background = Helper4Sprite::createOptimizeSprite(PNG_NOTIFICATION_POPUP_BACKGROUND);
	background->setCascadeOpacityEnabled(true);
	background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(background);

	//MISSING LABEL
	this->missingCoinLabel = Label::createWithTTF(
		TTFConfig(FONT_PassionOne_Regular, 36),
		"You need...",
		TextHAlignment::RIGHT
	);
	this->missingCoinLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
	this->missingCoinLabel->setPosition(background->getContentSize() / 2 + Size(50, 50));
	background->addChild(this->missingCoinLabel);

	//CURRENCY SPRITE
	this->currencySprite = Helper4Sprite::createOptimizeSprite(PNG_SHOP_COIN_ICON);
	this->currencySprite->setPosition(this->missingCoinLabel->getPosition() + Vec2(50, 0));
	background->addChild(this->currencySprite);

	//MORE TXT
	this->moreLabel = Label::createWithTTF(
		TTFConfig(FONT_PassionOne_Regular, 36),
		"more",
		TextHAlignment::LEFT
	);
	this->moreLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	this->moreLabel->setPosition(this->currencySprite->getPosition() + Vec2(50, 0));
	background->addChild(this->moreLabel);

	//LEFT BTN
	this->leftBtn = this->createButtonWithFrameName(PNG_FRAME_PURPLE_POPUP_BUTTON, Language(nullptr, LanguageConstant::CANCEL));
	this->leftBtn->setPosition(background->getContentSize() / 2 
		+ Size(-this->leftBtn->getContentSize().width / 1.5f, -background->getContentSize().height / 5)
	);
	this->leftBtn->addTouchEventListener([this](Ref *ref, ui::Widget::TouchEventType touchType)
	{
		if (touchType != ui::Widget::TouchEventType::ENDED) {
			return;
		}
		switch (this->currentMissingCurrency)
		{
		case ppEnum::COIN_CURRENCY:
			PopupManager::getInstance()->getShopPopup()->prepareAndShow(
				this->getParent(),
				ShopType::MagicItemShop
			);
			break;
		case ppEnum::CROWN_CURRENCY:
			break;
		default:
			return;
		}
		this->hide();
	});
	background->addChild(this->leftBtn);

	//RIGHT BTN
	this->rightBtn = this->createButtonWithFrameName(PNG_FRAME_YELLOW_POPUP_BUTTON, "BUY COINS");
	this->rightBtn->setPosition(background->getContentSize() / 2
		+ Size(this->rightBtn->getContentSize().width / 1.5f, -background->getContentSize().height / 5)
	);
	this->rightBtn->addTouchEventListener([this](Ref *ref, ui::Widget::TouchEventType touchType)
	{
		if (touchType != ui::Widget::TouchEventType::ENDED) {
			return;
		}
		switch (this->currentMissingCurrency)
		{
		case ppEnum::COIN_CURRENCY:
			PopupManager::getInstance()->getShopPopup()->prepareAndShow(
				this->getParent(),
				ShopType::CoinShop
			);
			break;
		case ppEnum::CROWN_CURRENCY:
			PopupManager::getInstance()->getShopPopup()->prepareAndShow(
				this->getParent(),
				ShopType::CrownShop
			);
			break;
		default:
			return;
		}
		this->hide();
	});
	background->addChild(this->rightBtn);

	//CLOSE BUTTON
	auto exitButton = BasePopup::createCloseButton();
	exitButton->setPosition(Vec2(
		origin.x + visibleSize.width / 2 + background->getContentSize().width / 2.1f,
		origin.y + visibleSize.height / 2 + background->getContentSize().height / 2.3f
	));
	this->addChild(exitButton);

	return true;
}

void MissingPopup::prepareAndShow(cocos2d::Node * parent, ppEnum::PPCurrency missingCurrency, double amount)
{
	switch (missingCurrency)
	{
	case ppEnum::COIN_CURRENCY:
		this->currencySprite->initWithFile(PNG_SHOP_COIN_ICON);
		this->leftBtn->loadTextureNormal(PNG_FRAME_GREEN_POPUP_BUTTON, ui::Widget::TextureResType::PLIST);
		this->leftBtn->getTitleLabel()->setString("BUY MAGIC ITEMS");
		this->rightBtn->getTitleLabel()->setString("BUY COINS");
		break;
	case ppEnum::CROWN_CURRENCY:
		this->currencySprite->initWithFile(PNG_SHOP_CROWN_ICON);
		this->leftBtn->loadTextureNormal(PNG_FRAME_PURPLE_POPUP_BUTTON, ui::Widget::TextureResType::PLIST);
		this->leftBtn->getTitleLabel()->setString(Language(leftBtn->getTitleLabel(),LanguageConstant::CANCEL));
		this->rightBtn->getTitleLabel()->setString("BUY CROWNS");
		break;
	default:
		return;
	}
	this->currentMissingCurrency = missingCurrency;
	this->missingCoinLabel->setString("You need " + UtilFunction::FormatWithCommas(amount) + " x");
	BasePopup::show(parent);
}
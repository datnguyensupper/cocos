#include "FreeToPlayPopup.h"
#include "Constant/Defination.h"
#include "Constant/ResultCodeConstant.h"
#include "Constant/LanguageConstant.h"
#include "Manager/PopupManager.h"
#include "Views/Lobby/header/HeaderLobbyLayout.h"
#include "Views/Popup/LoadingAnimation.h"
#include "Util/UtilFunction.h"


USING_NS_CC;
using namespace std;
bool FreeToPlayPopup::init()
{
	if (!BasePopup::init()) {
		return false;
	}

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PNG_PROMOTIONS_PLIST);

	bg = Sprite::createWithSpriteFrameName(FRAME_FREE_TO_PLAY_BG);
	bg->setPosition(origin + visibleSize / 2.0f);
	this->addChild(bg);

	this->txtCoinPkgSmall = this->createText(38, -0.29f, -0.195f);
	this->txtCoinPkgBig = this->createText(38, -0.29f, -0.333f);

	this->txtCrownPkgSmall = this->createText(38, 0.08f, -0.195f);
	this->txtCrownPkgBig = this->createText(38, 0.08f, -0.333f);

	this->btnBuyPkgSmall = this->createButtonBuy(0.8f, 0.8f, 0.323f, -0.195f);
	this->btnBuyPkgBig = this->createButtonBuy(0.8f, 0.8f, 0.323f, -0.333f);

	auto closeBtn = this->createCloseButton();
	closeBtn->setPosition(bg->getPosition() + Vec2(bg->getContentSize().width / 2.1f, bg->getContentSize().height / 2.2f));
	this->addChild(closeBtn);

	return true;
}

cocos2d::Label * FreeToPlayPopup::createText(int fontSize, float percentX, float precentY)
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

cocos2d::ui::Button * FreeToPlayPopup::createButtonBuy(float scaleX, float scaleY, float percentX, float precentY)
{
	auto btn = this->createGreenButton(true);
	btn->setPosition(bg->getPosition() +
		Vec2(bg->getContentSize().width * percentX, bg->getContentSize().height * precentY));
	btn->setScale(scaleX, scaleY);
	btn->addTouchEventListener(CC_CALLBACK_2(FreeToPlayPopup::onButtonTouched, this));
	this->addChild(btn);

	return btn;
}

void FreeToPlayPopup::onButtonTouched(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != ui::Widget::TouchEventType::ENDED) return;
	std::string itemID = "";
	if (sender = this->btnBuyPkgSmall) {
		itemID = IAP_FREE_TO_PLAY_P1;
	}
	else {
		itemID = IAP_FREE_TO_PLAY_P2;
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

bool FreeToPlayPopup::prepareAndShow(cocos2d::Node * parent)
{
	if (PopupManager::getInstance()->isPopupInQueue(this) || this->isVisible()) {
		return false;
	}
	this->txtCoinPkgSmall->setString(UtilFunction::FormatWithCommas(3600000));
	this->txtCoinPkgBig->setString(UtilFunction::FormatWithCommas(10800000));
	this->txtCrownPkgSmall->setString(UtilFunction::FormatWithCommas(5));
	this->txtCrownPkgBig->setString(UtilFunction::FormatWithCommas(10));

	this->btnBuyPkgSmall->getTitleLabel()->setString("$4.99");
	this->btnBuyPkgBig->getTitleLabel()->setString("$9.99");

	BasePopup::showWithQueue(parent);
	return true;
}

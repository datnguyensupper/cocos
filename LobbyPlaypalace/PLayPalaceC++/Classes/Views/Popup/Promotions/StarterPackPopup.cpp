#include "StarterPackPopup.h"
#include "Constant/Defination.h"
#include "Constant/ResultCodeConstant.h"
#include "Constant/LanguageConstant.h"
#include "Manager/PopupManager.h"
#include "Views/Lobby/header/HeaderLobbyLayout.h"
#include "Views/Popup/LoadingAnimation.h"
#include "Util/UtilFunction.h"

USING_NS_CC;
using namespace std;


bool StarterPackPopup::init()
{
	if (!BasePopup::init()) {
		return false;
	}

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PNG_PROMOTIONS_PLIST);

	auto bg = Sprite::createWithSpriteFrameName(FRAME_STARTER_PACK_BG);
	bg->setPosition(origin + Vec2(visibleSize.width / 2.0f, visibleSize.height / 1.8f));
	this->addChild(bg);

	btnBuy = this->createGreenButton(true);
	btnBuy->setPosition(bg->getPosition() + Vec2(bg->getContentSize().width * 0.285f, -bg->getContentSize().height * 0.28f));
	btnBuy->addTouchEventListener(CC_CALLBACK_2(StarterPackPopup::onButtonTouched, this));
	this->addChild(btnBuy);

	txtCoin = Label::createWithTTF("880,000", FONT_PassionOne_Bold, 60);
	txtCoin->enableShadow();
	txtCoin->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	txtCoin->setPosition(bg->getPosition() + Vec2(-bg->getContentSize().width * 0.275f, -bg->getContentSize().height * 0.37f));
	txtCoin->setTextColor(Color4B(255, 255, 191, 255));
	this->addChild(txtCoin);

	auto closeBtn = this->createCloseButton();
	closeBtn->setPosition(bg->getPosition() + 
		Vec2(bg->getContentSize().width / 2.1f, bg->getContentSize().height / 2.7f));
	this->addChild(closeBtn);

	return true;
}

void StarterPackPopup::onButtonTouched(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != ui::Widget::TouchEventType::ENDED) return;
	UtilFunction::purchaseItem(IAP_STARTER_PACK, false, [this](int core_result_code, MobilePaymentInfo* info) {
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

void StarterPackPopup::prepareAndShow(cocos2d::Node * parent)
{
	btnBuy->getTitleLabel()->setString(Language(btnBuy->getTitleLabel(), LanguageConstant::BUYNOW));

	BasePopup::showWithQueue(parent);
}

#include "NotificationPopup.h"
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


bool NotificationPopup::init()
{
	if (!BasePopup::init()) {
		return false;
	}

	//BACKGROUND
	auto background = Helper4Sprite::createOptimizeSprite(PNG_NOTIFICATION_POPUP_BACKGROUND);

	background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(background);

	//LABEL TITLE
	this->titleLabel = Label::createWithTTF("", FONT_PassionOne_Regular, 36);
	this->titleLabel->setPosition(Vec2(
		origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2 + background->getContentSize().height / 2.5f
	));
	this->titleLabel->setAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);
	this->titleLabel->setTextColor(Color4B::WHITE);
	this->titleLabel->setDimensions(720, 200);
	this->addChild(this->titleLabel);

	//LABEL BODY
	this->bodyLabel = Label::createWithTTF("", FONT_PassionOne_Regular, 36);
	this->bodyLabel->setPosition(Vec2(
		this->titleLabel->getPosition().x, 
		this->titleLabel->getPosition().y - background->getContentSize().height / 3.55f
	));
	this->bodyLabel->setAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);
	this->bodyLabel->setTextColor(Color4B::WHITE);
	this->bodyLabel->setDimensions(720, 300);
	this->addChild(this->bodyLabel);

	//LABEL INFO
	this->infoLabel = Label::createWithTTF("", FONT_PassionOne_Regular, 28);
	this->infoLabel->setPosition(Vec2(
		this->bodyLabel->getPosition().x + background->getContentSize().width / 18,
		this->bodyLabel->getPosition().y - background->getContentSize().height / 2.0f
	));
	this->infoLabel->setAlignment(TextHAlignment::LEFT, TextVAlignment::CENTER);
	this->infoLabel->setTextColor(Color4B::WHITE);
	this->infoLabel->setDimensions(750, 100);
	this->addChild(this->infoLabel);

	//INFO ICON SPRITE
	this->infoIconSprite = Helper4Sprite::createOptimizeSprite(PNG_NOTIFICATIO_POPUP_INFO_ICON);

	this->infoIconSprite->setPosition(Vec2(
		this->infoLabel->getPosition().x - this->infoLabel->getDimensions().width / 2 - 35,
		this->infoLabel->getPosition().y
	));
	this->addChild(this->infoIconSprite);

	//CLOSE BUTTON
	auto exitButton = BasePopup::createCloseButton();
	exitButton->setPosition(Vec2(
		origin.x + visibleSize.width / 2 + background->getContentSize().width / 2.1f,
		origin.y + visibleSize.height / 2 + background->getContentSize().height / 2.3f
	));
	exitButton->addTouchEventListener(CC_CALLBACK_2(NotificationPopup::closePopupButtonTouched, this));
	this->addChild(exitButton);

	//OK BUTTON
	this->okButton = BasePopup::createGreenButton("", 50);
	this->okButton->setPosition(Vec2(
		origin.x + visibleSize.width / 2 + this->okButton->getContentSize().width / 1.8f,
		origin.y + visibleSize.height / 2 - background->getContentSize().height / 5
	));
	this->okButton->addTouchEventListener(CC_CALLBACK_2(NotificationPopup::okButtonTouched, this));
	this->addChild(this->okButton);

	//CANCEL BUTTON
	this->cancelButton = BasePopup::createPurpleButton("", 50);
	this->cancelButton->setPosition(Vec2(
		origin.x + visibleSize.width / 2 - this->cancelButton->getContentSize().width / 1.8, 
		origin.y + this->okButton->getPosition().y
	));
	this->cancelButton->addTouchEventListener(CC_CALLBACK_2(NotificationPopup::closePopupButtonTouched, this));
	this->addChild(this->cancelButton);

	return true;
}

void NotificationPopup::okButtonTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
		if (callbackOK)
		{
			callbackOK();
		}

		BasePopup::hide();
	}
}

void NotificationPopup::closePopupButtonTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
		if (callbackCancel)
		{
			callbackCancel();
		}

		BasePopup::hide();
	}
}

void NotificationPopup::prepareAndShow(
	cocos2d::Node* parent,
	const std::string &title,
	const std::string &body,
	const std::string &okText,
	const std::string &cancelText,
	const std::string &info,
	const std::function <void(void)> callbackOK,
	const std::function <void(void)> callbackCancel
)
{
	UtilFunction::setLabelFontByLanguage(this->titleLabel);
	this->titleLabel->setString(title);
	UtilFunction::setLabelFontByLanguage(this->bodyLabel);
	if (LanguageManager::getInstance()->getCurrentLanguageName() == CN_TEXT ||
		LanguageManager::getInstance()->getCurrentLanguageName() == TAIWAN_TEXT)
	{
		this->bodyLabel->setLineBreakWithoutSpace(true);
	}
	else
	{
		this->bodyLabel->setLineBreakWithoutSpace(false);
	}
	this->bodyLabel->setString(body);
	UtilFunction::setLabelFontByLanguage(this->infoLabel);
	this->infoLabel->setString(info);
	UtilFunction::setLabelFontByLanguage(this->okButton->getTitleLabel());
	this->okButton->getTitleLabel()->setString(okText);
	UtilFunction::setLabelFontByLanguage(this->cancelButton->getTitleLabel());
	this->cancelButton->getTitleLabel()->setString(cancelText);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	if (!cancelText.empty())
	{
		this->okButton->setPosition(Vec2(
			origin.x + visibleSize.width / 2 + this->okButton->getContentSize().width / 1.8,
			this->okButton->getPosition().y
		));

		this->cancelButton->setVisible(true);
	}
	else 
	{
		this->okButton->setPosition(Vec2(
			origin.x + visibleSize.width / 2,
			this->okButton->getPosition().y
		));

		this->cancelButton->setVisible(false);
	}
	if (!info.empty())
	{
		this->infoIconSprite->setVisible(true);
		this->infoLabel->setVisible(true);
	}
	else
	{
		this->infoIconSprite->setVisible(false);
		this->infoLabel->setVisible(false);
	}

	this->callbackOK = callbackOK;
	this->callbackCancel = callbackCancel;

	BasePopup::show(parent);
	this->setLocalZOrder(INT_MAX);
}

/**
* show unfinish job popup
*/
void NotificationPopup::showUnfinishJobPopup(
	cocos2d::Node* parent
) {

	prepareAndShow(
		parent,
		"Comming soon",
		"We are working hard to bring you new content!",
		LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::OK),
		""
	);

}

/**
* show unfinish job popup
*/
void NotificationPopup::showDontSupportPopup(
	cocos2d::Node* parent) {

	prepareAndShow(
		parent,
		"Warning",
		"This platform is not supported in this release",
		LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::OK),
		""
	);

}

void NotificationPopup::showPopupMissingCoin(
	cocos2d::Node * parent,
	const int64_t & iCoinMissing)
{
	this->showPopupMissing(parent, iCoinMissing);
}

void NotificationPopup::showPopupMissingCrown(
	cocos2d::Node * parent,
	const int64_t & iCrownMissing)
{
	this->showPopupMissing(parent, iCrownMissing, true);
}

void NotificationPopup::showPopupMissing(
	cocos2d::Node * parent, 
	const int64_t & iValue,
	bool isCrown)
{
	std::string missingText = "Buy the missing\n" + UtilFunction::FormatWithCommas(iValue);

	if (isCrown) {
		missingText += " Crown";
	}
	else {

		missingText += " Coin";
	}
	if (iValue > 1) {
		missingText += "s";
	}
	missingText += "?";

	this->prepareAndShow(
		parent, 
		"", 
		missingText, 
		"GO TO SHOP", 
		LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::CANCEL),
		"",
		[parent, isCrown]() {
		PopupManager::getInstance()->getShopPopup()->prepareAndShow(parent, isCrown ? ShopType::CrownShop : ShopType::CoinShop);
	});
}

void NotificationPopup::showServerErrorPopup(
	cocos2d::Node * parent,
	const std::function<void()> funcReload,
	bool forceToCloseOpeningPopup,
	const std::function <void(void)> callbackOK,
	const std::function <void(void)> callbackCancel)
{
	if (forceToCloseOpeningPopup) {
		PopupManager::getInstance()->reset();
	}
	this->prepareAndShow(
		parent,
		"",
		"Can not connect to server! Please try again later ...",
		Language(nullptr, LanguageConstant::OK),
		Language(nullptr, LanguageConstant::CANCEL),
		"",
		[funcReload, callbackOK]() {
		if (funcReload) {
			funcReload();
		}
		else if(callbackOK){
			//LOGOUT
			callbackOK();
		}
	},
		[callbackCancel]() {
		//If playing game -> force go to lobby
		if (Helper4Scene::getRunningScene()->getTag() == ppEnum::GameScene::GameSlot) {
			PopupManager::getInstance()->getHeaderLobbyLayout()->gotoLobbyScene();
		}
		else if (callbackCancel) {
			//LOGOUT
			callbackCancel();
		}
	});
}

#include "ChangeNamePopup.h"
#include "Manager/InfoManager.h"
#include "Manager/NetworkManager.h"
#include "Manager/PopupManager.h"
#include "Views/Popup/NotificationPopup.h"
#include "Views/Popup/LoadingAnimation.h"
#include "Views/Popup/ProfilePopup.h"
#include "Views/Lobby/header/HeaderLobbyLayout.h"
#include "Constant/Defination.h"
#include "Constant/ResultCodeConstant.h"
#include "Util/UtilFunction.h"
#include "Configs.h"
#include "Helper/Helper4Sprite.h"
USING_NS_CC;
using namespace std;


bool ChangeNamePopup::init()
{
	if (!BasePopup::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//BACKGROUND
	auto bg = Helper4Sprite::createOptimizeSprite(PNG_NOTIFICATION_POPUP_BACKGROUND);
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(bg);

	//LABEL TITLE
	this->titleLabel = Label::createWithTTF(LanguageText(nullptr, LanguageConstant::POPUP_EDIT_NAME, "title"), FONT_PassionOne_Regular, 50); 
	LanguageText(titleLabel, LanguageConstant::POPUP_EDIT_NAME, "title");
	this->titleLabel->setPosition(Vec2(
		origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2 + bg->getContentSize().height / 3.5f
	));
	this->titleLabel->setAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);
	this->addChild(this->titleLabel);

	//LABEL BODY
	this->bodyLabel = Label::createWithTTF("", FONT_PassionOne_Regular, 40);
	this->bodyLabel->setPosition(Vec2(
		this->titleLabel->getPosition().x,
		origin.y + visibleSize.height / 2 + bg->getContentSize().height / 5.5f - 20
	));
	this->bodyLabel->setAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);
	this->addChild(this->bodyLabel);

	auto inputField = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_INPUT_FIELD_BG);
	inputField->setPosition(bg->getPosition());
	inputField->setPositionY(bg->getPosition().y - 20);
	inputField->setScale(0.75f);
	this->addChild(inputField);

	this->nameEditBox = ui::EditBox::create(Size(inputField->getContentSize().width * 0.7f, inputField->getContentSize().height * 0.75f), ui::Scale9Sprite::create());
	this->nameEditBox->setCascadeOpacityEnabled(true);
	this->nameEditBox->setPosition(inputField->getPosition());
	this->nameEditBox->setMaxLength(254);
	this->nameEditBox->setInputFlag(ui::EditBox::InputFlag::SENSITIVE);
	this->nameEditBox->setInputMode(ui::EditBox::InputMode::SINGLE_LINE);
	if ((CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
		&& (CC_TARGET_PLATFORM != CC_PLATFORM_MAC)
		&& (CC_TARGET_PLATFORM != CC_PLATFORM_LINUX))
	{
		this->nameEditBox->setFontName(FONT_PassionOne_Regular);
        if(CC_TARGET_PLATFORM != CC_PLATFORM_IOS){
            this->nameEditBox->setPlaceholderFont(FONT_PassionOne_Regular, 40);
        }
	}
	this->nameEditBox->setReturnType(ui::EditBox::KeyboardReturnType::SEND);
	this->nameEditBox->setTextHorizontalAlignment(TextHAlignment::CENTER);
    if(CC_TARGET_PLATFORM != CC_PLATFORM_IOS)
        this->nameEditBox->setPlaceHolder("                                ...");
    else
        this->nameEditBox->setPlaceHolder("                            ...");
        
    
    if(CC_TARGET_PLATFORM != CC_PLATFORM_IOS){
        this->nameEditBox->setPlaceholderFontColor(Color3B::GRAY);
    }
	this->nameEditBox->setFontSize(40);
	this->addChild(this->nameEditBox);

	//CLOSE BUTTON
	auto exitButton = BasePopup::createCloseButton();
	exitButton->setAnchorPoint(cocos2d::Vec2(0.9f,0.9f));
	exitButton->setPosition(Vec2(
		origin.x + visibleSize.width / 2 + bg->getContentSize().width / 2,
		origin.y + visibleSize.height / 2 + bg->getContentSize().height / 2
	));
	this->addChild(exitButton);

	//Send BUTTON
	btnSend = BasePopup::createGreenButton("Send");
	btnSend->setPosition(Vec2(
		origin.x + visibleSize.width / 2 + btnSend->getContentSize().width / 1.8,
		origin.y + visibleSize.height / 2 - bg->getContentSize().height / 2 + btnSend->getContentSize().height + 20
	));
	btnSend->addTouchEventListener(CC_CALLBACK_2(ChangeNamePopup::sendButtonTouched, this));
	this->addChild(btnSend);

	//CANCEL BUTTON
	btnCancel = BasePopup::createPurpleButton("Cancel");
	btnCancel->setPosition(Vec2(
		origin.x + visibleSize.width / 2 - btnCancel->getContentSize().width / 1.8,
		btnSend->getPosition().y
	));
	btnCancel->addTouchEventListener([this](cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED) {
			this->hide();
		}
	});
	this->addChild(btnCancel);

	return true;
}

void ChangeNamePopup::sendButtonTouched(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != ui::Widget::TouchEventType::ENDED) 	return;
	
	std::string newName = this->nameEditBox->getText();

	this->hide();

	if (newName.empty()) {
		PopupManager::getInstance()->getNotificationPopup()->prepareAndShow(this->getParent(), 
			LanguageText(nullptr, LanguageConstant::POPUP_EDIT_NAME, "title"), LanguageText(nullptr, LanguageConstant::POPUP_EDIT_NAME, "fail"));
	}
	else {
		PopupManager::getInstance()->getLoadingAnimation()->prepareAndShow(this->getParent());
		NetworkManager::getInstance()->updateName(newName,
			[this](int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString) {
			PopupManager::getInstance()->getLoadingAnimation()->hide();
			switch (coreResultCode)
			{
			case RESULT_CODE_VALID:
			{
				std::string newName = this->nameEditBox->getText();
				InfoManager::getInstance()->getUserInfo()->name = newName;
				PopupManager::getInstance()->getHeaderLobbyLayout()->updateName(newName);
				PopupManager::getInstance()->getProfilePopup()->updateName(newName);
				PopupManager::getInstance()->getNotificationPopup()->prepareAndShow(this->getParent(),
					LanguageText(nullptr, LanguageConstant::POPUP_EDIT_NAME, "title"), LanguageText(nullptr, LanguageConstant::POPUP_EDIT_NAME, "success"));
				this->hide();
			}
			break;
			case RESULT_CODE_EXCEED_MAX_NUMBER_OF_TIME_CHANGE_NAME:
				PopupManager::getInstance()->getNotificationPopup()->prepareAndShow(this->getParent(), 
					LanguageText(nullptr, LanguageConstant::POPUP_EDIT_NAME, "title"), LanguageText(nullptr, LanguageConstant::POPUP_EDIT_NAME, "reachLimit"));
				break;
			default:
				PopupManager::getInstance()->getNotificationPopup()->prepareAndShow(this->getParent(), 
					LanguageText(nullptr, LanguageConstant::POPUP_EDIT_NAME, "title"), LanguageText(nullptr, LanguageConstant::POPUP_EDIT_NAME, "fail"));
				break;
			}
		});
	}
}

void ChangeNamePopup::prepareAndShow(cocos2d::Node * parent)
{
	nameEditBox->setText("");
	UtilFunction::setLabelFontByLanguage(btnSend->getTitleLabel());
	btnSend->getTitleLabel()->setString(Language(nullptr, LanguageConstant::SEND));
	UtilFunction::setLabelFontByLanguage(btnCancel->getTitleLabel());
	btnCancel->getTitleLabel()->setString(Language(nullptr, LanguageConstant::CANCEL));
	UtilFunction::setLabelFontByLanguage(titleLabel);
	titleLabel->setString(LanguageText(nullptr, LanguageConstant::POPUP_EDIT_NAME, "title"));

	UtilFunction::detectFontAndSetStringForLabel(this->bodyLabel, FONT_PassionOne_Regular,
		UtilFunction::trimStringAndAdd3Dots(InfoManager::getInstance()->getUserInfo()->name, 30));

	BasePopup::show(parent);

	this->setLocalZOrder(INT_MAX - 1);
}

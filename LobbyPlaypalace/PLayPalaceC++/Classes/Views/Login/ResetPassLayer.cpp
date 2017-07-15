#include "ResetPassLayer.h"
#include "Scene/LoginScene.h"
#include "Custom/Common/ButtonAdjustClikableAreaSize.h"
#include "Util/UtilFunction.h"
#include "Manager/PopupManager.h"
#include "Views/Popup/LoadingAnimation.h"
#include "Helper/Helper4Sprite.h"

USING_NS_CC;
using namespace std;

#define RESET_PASSWORD_TEXT "RESET PASSWORD"
#define EMAIL_ADDRESS_TEXT "Email address"
#define SUBMIT_TEXT "Submit"
ResetPassLayer* ResetPassLayer::create(LoginScene* parentScene)
{
	auto layer = ResetPassLayer::create();
	layer->loginScene = parentScene;
	return layer;
}

// on "init" you need to initialize your instance
bool ResetPassLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//BACKGROUND 
	auto background = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_LOGIN_BACKGROUND);
	background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(background);

	//BACK BUTTON
	auto backButton = ButtonAdjustClikableAreaSize::create(PNG_FRAME_LOGIN_BACK, "", "", ui::Widget::TextureResType::PLIST);
	backButton->setClickableAreaSize(Size(200, 200));
	backButton->setAnchorClickableAreaSize(Vec2(0.5f, 0.5f));
	backButton->setPosition(Vec2(origin.x + 50, origin.y + visibleSize.height - 72));
	backButton->setZoomScale(Configs::BUTTON_ZOOM_SCALE_VALUE);
	backButton->addTouchEventListener(CC_CALLBACK_2(ResetPassLayer::onBackToLoginViewTouched, this));
	this->addChild(backButton);

	//LOGO PLAYPALACE
	auto logo = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_LOGIN_LOGO);
	logo->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 353));
	this->addChild(logo);

	//LOGIN LABEL
	auto loginLabel = Label::createWithTTF(RESET_PASSWORD_TEXT, FONT_HelveticaNeue_Light, 50);
	loginLabel->setPosition(Vec2(origin.x + visibleSize.width / 2 + 2, origin.y + visibleSize.height / 2 + 202));
	loginLabel->setTextColor(Color4B::BLACK);
	this->addChild(loginLabel);

	//EMAIL
#pragma region email
	auto emailLabel = Label::createWithTTF(EMAIL_ADDRESS_TEXT, FONT_HelveticaNeue_Thin, 35);
	emailLabel->setPosition(Vec2(origin.x + visibleSize.width / 2 - 285, origin.y + visibleSize.height / 2 + 100));
	emailLabel->setTextColor(Color4B::BLACK);
	this->addChild(emailLabel);

	auto emailLine = DrawNode::create();
	emailLine->drawLine(
		Vec2(emailLabel->getPosition().x - emailLabel->getContentSize().width / 2, emailLabel->getPosition().y - 32),
		Vec2(1210, emailLabel->getPosition().y - 32),
		Color4F(0.0, 0.0, 0.0, 0.5));
	this->addChild(emailLine);

	this->emailEditBox = ui::EditBox::create(Size(563, 50), ui::Scale9Sprite::create());
	this->emailEditBox->setAnchorPoint(Vec2(0, 0.5f));
	this->emailEditBox->setPosition(Vec2(emailLabel->getPosition().x + 135, emailLabel->getPosition().y));
	this->emailEditBox->setFontColor(Color4B::BLACK);
	this->emailEditBox->setMaxLength(254);
	this->emailEditBox->setReturnType(ui::EditBox::KeyboardReturnType::SEND);
	this->emailEditBox->setInputFlag(ui::EditBox::InputFlag::SENSITIVE);
	this->emailEditBox->setInputMode(ui::EditBox::InputMode::SINGLE_LINE);
	if ((CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
		&& (CC_TARGET_PLATFORM != CC_PLATFORM_MAC)
		&& (CC_TARGET_PLATFORM != CC_PLATFORM_LINUX))
	{
		this->emailEditBox->setFontName(FONT_HelveticaNeue_Light);
	}
	this->emailEditBox->setFontSize(35);
	this->addChild(this->emailEditBox);

#pragma endregion

	//BUTTON SUBMIT
	auto buttonSubmit = ui::Button::create(PNG_FRAME_LOGIN_BUTTON_LOGIN_PP, "", "", ui::Widget::TextureResType::PLIST);
	buttonSubmit->setTitleText(SUBMIT_TEXT);
	buttonSubmit->setTitleFontName(FONT_HelveticaNeue_Thin);
	buttonSubmit->setTitleFontSize(35);
	buttonSubmit->setTitleColor(Color3B::BLACK);
	buttonSubmit->setPosition(Vec2(origin.x + visibleSize.width / 2, emailLabel->getPosition().y - 135));
	buttonSubmit->setZoomScale(Configs::BUTTON_ZOOM_SCALE_VALUE);
	buttonSubmit->addTouchEventListener(CC_CALLBACK_2(ResetPassLayer::onSubmitResetPasswordTouched, this));
	this->addChild(buttonSubmit);

    return true;
}

void ResetPassLayer::onBackToLoginViewTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED)
	{
		this->loginScene->moveCameraToView(LoginViews::PPLoginView);
	}
}

void ResetPassLayer::onSubmitResetPasswordTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED)
	{
		string emailAddress = emailEditBox->getText();
		if (emailAddress.empty())
		{
			loginScene->showNotificationLoginPopup(
				MessageConstant::RESET_PASSWORD,
				MessageConstant::LOGIN_FAIL_EMPTY_FIELD_EMAIL
			);
			return;
		}
		else if (!UtilFunction::checkValidEmail(emailAddress))
		{
			loginScene->showNotificationLoginPopup(
				MessageConstant::RESET_PASSWORD,
				MessageConstant::LOGIN_FAIL_INVALID_EMAIL
			);
			return;
		}

		auto callback = [this, emailAddress](
			int coreResultCode,
			rapidjson::Value &doc,
			string responseAsString)
		{
			switch (coreResultCode)
			{
			case RESULT_CODE_VALID:
			{
				loginScene->showNotificationLoginPopup(
					MessageConstant::RESET_PASSWORD,
					MessageConstant::RESET_PASSWORD_EMAIL_SENT_TO + emailAddress + MessageConstant::RESET_PASSWORD_FURTHER_INSTRUCTION
				);
				break;
			}
			default:
				loginScene->handleErrorResultCodeForLoginScene(
					coreResultCode,
					MessageConstant::RESET_PASSWORD
					);
				break;
			}
			PopupManager::getInstance()->getLoadingAnimation()->hide();
		};
		PopupManager::getInstance()->getLoadingAnimation()->prepareAndShow(this->getParent());
		NetworkManager::getInstance()->resetPassword(
			emailAddress,
			callback,
			[this](std::string result)
		{
			PopupManager::getInstance()->getLoadingAnimation()->hide();
		},
			[this](std::string result)
		{
			PopupManager::getInstance()->getLoadingAnimation()->hide();
		}
		);
	}
}

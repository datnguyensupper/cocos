#include "SignUpLayer.h"
#include "Scene/LoginScene.h"
#include "Custom/Common/ButtonAdjustClikableAreaSize.h"
#include "Util/UtilFunction.h"
#include "Manager/PopupManager.h"
#include "Views/Popup/LoadingAnimation.h"
#include "Helper/Helper4Sprite.h"

USING_NS_CC;
using namespace std;

#define SIGN_UP_UPCASE_TEXT "SIGN UP"
#define EMAIL_TEXT "Email *"
#define PASSWORD_TEXT "Password *"
#define RETYPE_PASSWORD_TEXT "Retype Password *"
#define REFERENCE_CODE_TEXT "Reference Code"
#define SIGN_UP_TEXT "Sign Up"

SignUpLayer* SignUpLayer::create(LoginScene* parentScene)
{
	auto layer = SignUpLayer::create();
	layer->loginScene = parentScene;
	return layer;
}

// on "init" you need to initialize your instance
bool SignUpLayer::init()
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
	backButton->addTouchEventListener(CC_CALLBACK_2(SignUpLayer::onBackToLoginViewTouched, this));
	this->addChild(backButton);

	//LOGO PLAYPALACE
	auto logo = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_LOGIN_LOGO);
	logo->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 353));
	this->addChild(logo);

	//SIGN UP LABEL
	auto loginLabel = Label::createWithTTF(SIGN_UP_UPCASE_TEXT, FONT_HelveticaNeue_Light, 50);
	loginLabel->setPosition(Vec2(origin.x + visibleSize.width / 2 + 2, origin.y + visibleSize.height / 2 + 202));
	loginLabel->setTextColor(Color4B::BLACK);
	this->addChild(loginLabel);

	//EMAIL
#pragma region email
	auto emailLabel = Label::createWithTTF(EMAIL_TEXT, FONT_HelveticaNeue_Thin, 35);
	emailLabel->setPosition(Vec2(origin.x + visibleSize.width / 2 - 348, origin.y + visibleSize.height / 2 + 125));
	emailLabel->setTextColor(Color4B::BLACK);
	this->addChild(emailLabel);

	auto emailLine = DrawNode::create();
	emailLine->drawLine(
		Vec2(emailLabel->getPosition().x - emailLabel->getContentSize().width / 2, emailLabel->getPosition().y - 32),
		Vec2(1252, emailLabel->getPosition().y - 32),
		Color4F(0.0, 0.0, 0.0, 0.5));
	this->addChild(emailLine);

	this->emailEditBox = ui::EditBox::create(Size(553, 50), ui::Scale9Sprite::create());
	this->emailEditBox->setAnchorPoint(Vec2(0, 0.5f));
	this->emailEditBox->setPosition(Vec2(emailLabel->getPosition().x + 250, emailLabel->getPosition().y));
	this->emailEditBox->setFontColor(Color4B::BLACK);
	this->emailEditBox->setMaxLength(254);
	this->emailEditBox->setReturnType(ui::EditBox::KeyboardReturnType::NEXT);
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

	//PASSWORD
#pragma region password
	auto passwordLabel = Label::createWithTTF(PASSWORD_TEXT, FONT_HelveticaNeue_Thin, 35);
	passwordLabel->setPosition(Vec2(emailLabel->getPosition().x + 32, emailLabel->getPosition().y - 85));
	passwordLabel->setTextColor(Color4B::BLACK);
	this->addChild(passwordLabel);

	auto passwordLine = DrawNode::create();
	passwordLine->drawLine(
		Vec2(passwordLabel->getPosition().x - passwordLabel->getContentSize().width / 2, passwordLabel->getPosition().y - 32),
		Vec2(1252, passwordLabel->getPosition().y - 32),
		Color4F(0.0, 0.0, 0.0, 0.5));
	this->addChild(passwordLine);

	this->passwordEditBox = ui::EditBox::create(this->emailEditBox->getSize(), ui::Scale9Sprite::create());
	this->passwordEditBox->setAnchorPoint(Vec2(0, 0.5f));
	this->passwordEditBox->setPosition(Vec2(this->emailEditBox->getPosition().x, passwordLabel->getPosition().y));
	this->passwordEditBox->setFontColor(Color4B::BLACK);
	this->passwordEditBox->setMaxLength(100);
	this->passwordEditBox->setReturnType(ui::EditBox::KeyboardReturnType::NEXT);
	this->passwordEditBox->setInputFlag(ui::EditBox::InputFlag::PASSWORD);
	this->passwordEditBox->setInputMode(ui::EditBox::InputMode::SINGLE_LINE);
	if ((CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
		&& (CC_TARGET_PLATFORM != CC_PLATFORM_MAC)
		&& (CC_TARGET_PLATFORM != CC_PLATFORM_LINUX))
	{
		this->passwordEditBox->setFontName(FONT_HelveticaNeue_Light);
	}
	this->passwordEditBox->setFontSize(35);
	this->addChild(this->passwordEditBox);
#pragma endregion

	//RETYPE PASSWORD
#pragma region retype password
	auto retypePasswordLabel = Label::createWithTTF(RETYPE_PASSWORD_TEXT, FONT_HelveticaNeue_Thin, 35);
	retypePasswordLabel->setPosition(Vec2(passwordLabel->getPosition().x + 55, passwordLabel->getPosition().y - 85));
	retypePasswordLabel->setTextColor(Color4B::BLACK);
	this->addChild(retypePasswordLabel);

	auto retypePasswordLine = DrawNode::create();
	retypePasswordLine->drawLine(
		Vec2(retypePasswordLabel->getPosition().x - retypePasswordLabel->getContentSize().width / 2, retypePasswordLabel->getPosition().y - 32),
		Vec2(1252, retypePasswordLabel->getPosition().y - 32),
		Color4F(0.0, 0.0, 0.0, 0.5));
	this->addChild(retypePasswordLine);

	this->retypePasswordEditBox = ui::EditBox::create(this->emailEditBox->getSize(), ui::Scale9Sprite::create());
	this->retypePasswordEditBox->setAnchorPoint(Vec2(0, 0.5f));
	this->retypePasswordEditBox->setPosition(Vec2(this->emailEditBox->getPosition().x, retypePasswordLabel->getPosition().y));
	this->retypePasswordEditBox->setFontColor(Color4B::BLACK);
	this->retypePasswordEditBox->setMaxLength(100);
	this->retypePasswordEditBox->setReturnType(ui::EditBox::KeyboardReturnType::NEXT);
	this->retypePasswordEditBox->setInputFlag(ui::EditBox::InputFlag::PASSWORD);
	this->retypePasswordEditBox->setInputMode(ui::EditBox::InputMode::SINGLE_LINE);
	if ((CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
		&& (CC_TARGET_PLATFORM != CC_PLATFORM_MAC)
		&& (CC_TARGET_PLATFORM != CC_PLATFORM_LINUX))
	{
		this->retypePasswordEditBox->setFontName(FONT_HelveticaNeue_Light);
	}
	this->retypePasswordEditBox->setFontSize(35);
	this->addChild(this->retypePasswordEditBox);
#pragma endregion

	//REFERENCE CODE
#pragma region reference code
	auto referenceCodeLabel = Label::createWithTTF(REFERENCE_CODE_TEXT, FONT_HelveticaNeue_Thin, 35);
	referenceCodeLabel->setPosition(Vec2(retypePasswordLabel->getPosition().x - 19, retypePasswordLabel->getPosition().y - 85));
	referenceCodeLabel->setTextColor(Color4B::BLACK);
	this->addChild(referenceCodeLabel);

	auto referenceCodeLine = DrawNode::create();
	referenceCodeLine->drawLine(
		Vec2(referenceCodeLabel->getPosition().x - referenceCodeLabel->getContentSize().width / 2, referenceCodeLabel->getPosition().y - 32),
		Vec2(1252, referenceCodeLabel->getPosition().y - 32),
		Color4F(0.0, 0.0, 0.0, 0.5));
	this->addChild(referenceCodeLine);

	this->referenceCodeEditBox = ui::EditBox::create(this->emailEditBox->getSize(), ui::Scale9Sprite::create());
	this->referenceCodeEditBox->setAnchorPoint(Vec2(0, 0.5f));
	this->referenceCodeEditBox->setPosition(Vec2(this->emailEditBox->getPosition().x, referenceCodeLabel->getPosition().y));
	this->referenceCodeEditBox->setFontColor(Color4B::BLACK);
	this->referenceCodeEditBox->setMaxLength(100);
	this->referenceCodeEditBox->setReturnType(ui::EditBox::KeyboardReturnType::SEND);
	this->referenceCodeEditBox->setInputFlag(ui::EditBox::InputFlag::SENSITIVE);
	this->referenceCodeEditBox->setInputMode(ui::EditBox::InputMode::SINGLE_LINE);
	if ((CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
		&& (CC_TARGET_PLATFORM != CC_PLATFORM_MAC)
		&& (CC_TARGET_PLATFORM != CC_PLATFORM_LINUX))
	{
		this->referenceCodeEditBox->setFontName(FONT_HelveticaNeue_Light);
	}
	this->referenceCodeEditBox->setFontSize(35);
	this->addChild(this->referenceCodeEditBox);
#pragma endregion

	//BUTTON SIGN UP
	auto buttonSignUp = ui::Button::create(PNG_FRAME_LOGIN_BUTTON_LOGIN_PP, "", "", ui::Widget::TextureResType::PLIST);
	buttonSignUp->setTitleText(SIGN_UP_TEXT);
	buttonSignUp->setTitleFontName(FONT_HelveticaNeue_Thin);
	buttonSignUp->setTitleFontSize(35);
	buttonSignUp->setTitleColor(Color3B::BLACK);
	buttonSignUp->setPosition(Vec2(origin.x + visibleSize.width / 2, visibleSize.height / 2 - 250));
	buttonSignUp->setZoomScale(Configs::BUTTON_ZOOM_SCALE_VALUE);
	buttonSignUp->addTouchEventListener(CC_CALLBACK_2(SignUpLayer::onSignUpTouched, this));
	this->addChild(buttonSignUp);

    return true;
}

void SignUpLayer::onBackToLoginViewTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
	{
		this->loginScene->moveCameraToView(LoginViews::PPLoginView);
		break;
	}
	default:
		break;
	}
}

void SignUpLayer::onSignUpTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED)
	{
		string username = emailEditBox->getText();
		string password = passwordEditBox->getText();
		string retypePassword = retypePasswordEditBox->getText();
		string referenceCode = referenceCodeEditBox->getText();
		if (username.empty())
		{
			loginScene->showNotificationLoginPopup(
				MessageConstant::SIGNUP_FAIL,
				MessageConstant::SIGNUP_FAIL_EMPTY_FIELD_EMAIL
			);
			return;
		}
		else if (password.empty())
		{
			loginScene->showNotificationLoginPopup(
				MessageConstant::SIGNUP_FAIL,
				MessageConstant::SIGNUP_FAIL_EMPTY_FIELD_PASSWORD
			);
			return;
		}
		else if (retypePassword.empty()
			|| password != retypePassword)
		{
			loginScene->showNotificationLoginPopup(
				MessageConstant::SIGNUP_FAIL,
				MessageConstant::SIGNUP_FAIL_RETYPE_PASSWORD_INCORRECT
			);
			return;
		}
		else if (!UtilFunction::checkValidEmail(username)) {
			loginScene->showNotificationLoginPopup(
				MessageConstant::SIGNUP_FAIL,
				MessageConstant::SIGNUP_FAIL_INVALID_EMAIL
			);
			return;
		}
		auto callback = [this](
			int coreResultCode,
			rapidjson::Value &doc,
			string responseAsString)
		{
			switch (coreResultCode)
			{
			case RESULT_CODE_VALID:
			{
				//go to init session scene
				loginScene->showNotificationLoginPopup(
					MessageConstant::SIGNUP_FAIL,
					MessageConstant::SIGNUP_SUCESS + " " + MessageConstant::SIGNUP_SUCESS_MESSAGE,
					[this]()
					{	
						this->onBackToLoginViewTouched(nullptr, cocos2d::ui::Widget::TouchEventType::ENDED);
					}
				);
				break;
			}
			default:
				loginScene->handleErrorResultCodeForLoginScene(
					coreResultCode,
					MessageConstant::SIGNUP_FAIL
				);
				break;
			}
			PopupManager::getInstance()->getLoadingAnimation()->hide();
		};

		NetworkManager::getInstance()->signUpPlayPalaceAccount(
			username,
			password,
			referenceCode,
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
		PopupManager::getInstance()->getLoadingAnimation()->prepareAndShow(this->getParent());
	}
}

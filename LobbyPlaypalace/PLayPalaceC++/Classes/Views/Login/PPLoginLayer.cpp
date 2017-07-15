#include "PPLoginLayer.h"
#include "Scene/LoginScene.h"
#include "Scene/InitSessionScene.h"
#include "Custom/Common/ButtonAdjustClikableAreaSize.h"
#include "Util/UtilFunction.h"
#include "Manager/PopupManager.h"
#include "Manager/InfoManager.h"
#include "Views/Popup/LoadingAnimation.h"
#include "Helper/Helper4Sprite.h"


USING_NS_CC;
using namespace std;
#define LOGIN_UPCASE_TEXT "LOGIN"
#define LOGIN_LOWCASE_TEXT "Login"
#define EMAIL_TEXT "Email"
#define PASSWORD_TEXT "Password"
#define CREATE_NEW_ACCOUNT_TEXT "Create new account"
#define FORGOT_YOUR_PASSWORD "Forgot your password?"
PPLoginLayer* PPLoginLayer::create(LoginScene* parentScene)
{
	auto layer = PPLoginLayer::create();
	layer->loginScene = parentScene;
	return layer;
}

// on "init" you need to initialize your instance
bool PPLoginLayer::init()
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
	auto backButton = ButtonAdjustClikableAreaSize::create(PNG_FRAME_LOGIN_BACK,"","",ui::Widget::TextureResType::PLIST);
	backButton->setClickableAreaSize(Size(200, 200));
	backButton->setAnchorClickableAreaSize(Vec2(0.5f, 0.5f));
	backButton->setPosition(Vec2(origin.x + 50, origin.y + visibleSize.height - 72));
	backButton->setZoomScale(Configs::BUTTON_ZOOM_SCALE_VALUE);
	backButton->addTouchEventListener(CC_CALLBACK_2(PPLoginLayer::onBackToMainViewTouched, this));
	this->addChild(backButton);

	//LOGO PLAYPALACE
	auto logo = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_LOGIN_LOGO);
	logo->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 353));
	this->addChild(logo);

	//LOGIN LABEL
	auto loginLabel = Label::createWithTTF(LOGIN_UPCASE_TEXT, FONT_HelveticaNeue_Light, 50);
	loginLabel->setPosition(Vec2(origin.x + visibleSize.width / 2 + 2, origin.y + visibleSize.height / 2 + 202));
	loginLabel->setTextColor(Color4B::BLACK);
	this->addChild(loginLabel);

	//EMAIL
#pragma region email
	auto emailLabel = Label::createWithTTF(EMAIL_TEXT, FONT_HelveticaNeue_Thin, 35);
	emailLabel->setPosition(Vec2(origin.x + visibleSize.width / 2 - 348, origin.y + visibleSize.height / 2 + 80));
	emailLabel->setTextColor(Color4B::BLACK);
	this->addChild(emailLabel);

	auto emailLine = DrawNode::create();
	emailLine->drawLine(
		Vec2(emailLabel->getPosition().x - emailLabel->getContentSize().width / 2, emailLabel->getPosition().y - 32),
		Vec2(1252, emailLabel->getPosition().y - 32),
		Color4F(0.0, 0.0, 0.0, 0.5));
	this->addChild(emailLine);

	this->emailEditBox = ui::EditBox::create(Size(670, 50), ui::Scale9Sprite::create());
	this->emailEditBox->setAnchorPoint(Vec2(0, 0.5f));
	this->emailEditBox->setPosition(Vec2(emailLabel->getPosition().x + 135 , emailLabel->getPosition().y));
	this->emailEditBox->setFontColor(Color4B::BLACK);
	this->emailEditBox->setMaxLength(254);
	this->emailEditBox->setInputFlag(ui::EditBox::InputFlag::SENSITIVE);
	this->emailEditBox->setInputMode(ui::EditBox::InputMode::EMAIL_ADDRESS);
	this->emailEditBox->setReturnType(ui::EditBox::KeyboardReturnType::NEXT);
	if ((CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
		&& (CC_TARGET_PLATFORM != CC_PLATFORM_MAC)
		&& (CC_TARGET_PLATFORM != CC_PLATFORM_LINUX))
	{
		this->emailEditBox->setFontName(FONT_HelveticaNeue_Light);
	}
	this->emailEditBox->setFontSize(35);
	this->emailEditBox->setText(CCUserDefault::getInstance()->getStringForKey(STORING_KEY_USER_NAME_PLAYPALACE).c_str());
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
	this->passwordEditBox->setInputFlag(ui::EditBox::InputFlag::PASSWORD);
	this->passwordEditBox->setInputMode(ui::EditBox::InputMode::SINGLE_LINE);
	if((CC_TARGET_PLATFORM != CC_PLATFORM_WIN32) 
		&& (CC_TARGET_PLATFORM != CC_PLATFORM_MAC) 
		&& (CC_TARGET_PLATFORM != CC_PLATFORM_LINUX))
	{
		this->passwordEditBox->setFontName(FONT_HelveticaNeue_Light);
	}
	this->passwordEditBox->setFontSize(35);
	this->passwordEditBox->setDelegate(this);
	this->passwordEditBox->setReturnType(ui::EditBox::KeyboardReturnType::NEXT);
	this->addChild(this->passwordEditBox);
#pragma endregion

	//BUTTON LOGIN
	auto buttonLogin = ui::Button::create(PNG_FRAME_LOGIN_BUTTON_LOGIN_PP, "", "", ui::Widget::TextureResType::PLIST);
	buttonLogin->setTitleText(LOGIN_LOWCASE_TEXT);
	buttonLogin->setTitleFontName(FONT_HelveticaNeue_Thin);
	buttonLogin->setTitleFontSize(35);
	buttonLogin->setTitleColor(Color3B::BLACK);
	buttonLogin->setPosition(Vec2(origin.x + visibleSize.width / 2 , visibleSize.height / 2 - 135));
	buttonLogin->setZoomScale(Configs::BUTTON_ZOOM_SCALE_VALUE);
	buttonLogin->addTouchEventListener(CC_CALLBACK_2(PPLoginLayer::onLoginTouched, this));
	this->addChild(buttonLogin);

	//CREATE NEW ACCOUNT (GO TO SIGN UP VIEW)
	auto createNewAccount = ui::Button::create();
	createNewAccount->setPosition(Vec2(buttonLogin->getPosition().x, buttonLogin->getPosition().y - 122));
	createNewAccount->setTitleText(CREATE_NEW_ACCOUNT_TEXT);
	createNewAccount->setTitleFontName(FONT_HelveticaNeue_Thin);
	createNewAccount->setTitleColor(Color3B::BLACK);
	createNewAccount->setTitleFontSize(31);
	createNewAccount->setZoomScale(0);
	createNewAccount->addTouchEventListener(CC_CALLBACK_2(PPLoginLayer::onCreateNewAccountTouched, this));
	this->addChild(createNewAccount);

	//RESET PASSWORD ( FORGOT PASSWORD )
	auto resetPassword = ui::Button::create();
	resetPassword->setPosition(Vec2(createNewAccount->getPosition().x, createNewAccount->getPosition().y - 71));
	resetPassword->setTitleText(FORGOT_YOUR_PASSWORD);
	resetPassword->setTitleFontName(FONT_HelveticaNeue_Thin);
	resetPassword->setTitleColor(Color3B::BLACK);
	resetPassword->setTitleFontSize(31);
	resetPassword->setZoomScale(0);
	resetPassword->addTouchEventListener(CC_CALLBACK_2(PPLoginLayer::onForgotPasswordTouched, this));
	this->addChild(resetPassword);

    return true;
}

void PPLoginLayer::editBoxReturn(cocos2d::ui::EditBox * editBox)
{
	if (Configs::printConsoleLog)
	{
		CCLOG("editBoxReturn PP LOGIN SCENE");
	}
	//this->onLoginTouched(nullptr, cocos2d::ui::Widget::TouchEventType::ENDED);
}

void PPLoginLayer::editBoxEditingDidEndWithAction(
	cocos2d::ui::EditBox * editBox, 
	cocos2d::ui::EditBoxDelegate::EditBoxEndAction action)
{
	if (Configs::printConsoleLog)
	{
		CCLOG("editBoxEditingDidEndWithAction PP LOGIN SCENE with action = %d", action);
	}
	if (action == cocos2d::ui::EditBoxDelegate::EditBoxEndAction::TAB_TO_NEXT)
	{
		this->onLoginTouched(nullptr, cocos2d::ui::Widget::TouchEventType::ENDED);
	}
}

void PPLoginLayer::onLoginTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED) 
	{
		string username = emailEditBox->getText();
		string password = passwordEditBox->getText();
		if (username.empty())
		{
			loginScene->showNotificationLoginPopup(
				MessageConstant::LOGIN_FAIL,
				MessageConstant::LOGIN_FAIL_EMPTY_FIELD_EMAIL
			);
			return;
		}
		else if (password.empty())
		{
			loginScene->showNotificationLoginPopup(
				MessageConstant::LOGIN_FAIL,
				MessageConstant::LOGIN_FAIL_EMPTY_FIELD_PASSWORD
			);
			return;
		}
		else if (!UtilFunction::checkValidEmail(username)) {
			loginScene->showNotificationLoginPopup(
				MessageConstant::LOGIN_FAIL,
				MessageConstant::LOGIN_FAIL_INVALID_EMAIL
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
				InfoManager::getInstance()->updateUserInfo(doc);
				NetworkManager::getInstance()->setLoginToken(doc[JSONFieldConstant::LOGIN_TOKEN.c_str()].GetString());
				CCUserDefault::getInstance()->setStringForKey(STORING_KEY_USER_NAME_PLAYPALACE, emailEditBox->getText());
				CCUserDefault::getInstance()->flush();
				// Go to init session scene
				loginScene->gotoInitSessionScene(0, ppEnum::LoginAndInitSSFrom::PPAccount);
				break;
			}
			default:
				loginScene->handleErrorResultCodeForLoginScene(coreResultCode);
				break;
			}
			PopupManager::getInstance()->getLoadingAnimation()->hide();
		};

		PopupManager::getInstance()->getLoadingAnimation()->prepareAndShow(this->getParent());
		NetworkManager::getInstance()->loginPPAcount(
			username,
			password,
			callback,
			[](std::string result)
		{
			PopupManager::getInstance()->getLoadingAnimation()->hide();
		},
			[](std::string result)
		{
			PopupManager::getInstance()->getLoadingAnimation()->hide();
		}
		);
	}
}


void PPLoginLayer::onCreateNewAccountTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED)
	{
		this->loginScene->moveCameraToView(LoginViews::SignUpView);
	}
}

void PPLoginLayer::onForgotPasswordTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED)
	{
		this->loginScene->moveCameraToView(LoginViews::ResetPassView);
	}
}


void PPLoginLayer::onBackToMainViewTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED)
	{
		this->loginScene->moveCameraToView(LoginViews::MainLoginView);
	}
}

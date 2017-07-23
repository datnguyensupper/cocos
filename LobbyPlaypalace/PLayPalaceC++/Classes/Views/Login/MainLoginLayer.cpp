#include "MainLoginLayer.h"
#include "Custom/Common/ButtonAdjustClikableAreaSize.h"
#include "Manager/NetworkManager.h"
#include "Manager/InfoManager.h"
#include "Manager/PopupManager.h"
#include "Manager/PluginManager.h"
#include "Scene/LoginScene.h"
#include "Scene/InitSessionScene.h"

#include "Views/Popup/LoadingAnimation.h"
#include "Helper/Helper4Sprite.h"
#if IS_DEBUG
#include "Manager/Test/TestManager.h"
#endif

USING_NS_CC;
using namespace std;

#define PLAY_AS_GUESS "Play as guest"
#define LOGIN_WITH_PLAYPALACE "Login with\nPlayPalace"
MainLoginLayer* MainLoginLayer::create(LoginScene* parentScene)
{
	auto layer = MainLoginLayer::create();
	layer->loginScene = parentScene;
	return layer;
}
// on "init" you need to initialize your instance
bool MainLoginLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if (!cocos2d::Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto background = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_LOGIN_BACKGROUND);
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(background);

	auto logo = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_LOGIN_LOGO);
	logo->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 353));
	this->addChild(logo);

	auto orSprite = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_LOGIN_OR);
	orSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(orSprite);

	auto buttonFacebookLogin = ui::Button::create(PNG_FRAME_LOGIN_LOGIN_WITH_FB,"","",ui::Widget::TextureResType::PLIST);
	buttonFacebookLogin->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 150));
	buttonFacebookLogin->setZoomScale(0);
	buttonFacebookLogin->addTouchEventListener(CC_CALLBACK_2(MainLoginLayer::onLoginFacebookTouched, this));
	this->addChild(buttonFacebookLogin);

	auto buttonGuessLogin = ButtonAdjustClikableAreaSize::create(PNG_FRAME_LOGIN_GUESS_ICON,"","",ui::Widget::TextureResType::PLIST);
	buttonGuessLogin->setPosition(Vec2(visibleSize.width / 2 - 317, visibleSize.height / 2 - 155));
	buttonGuessLogin->setClickableAreaSize(Size(buttonGuessLogin->getContentSize().width * 2, buttonGuessLogin->getContentSize().height));
	buttonGuessLogin->setZoomScale(0);
	buttonGuessLogin->setPressedActionEnabled(false);
	buttonGuessLogin->addTouchEventListener(CC_CALLBACK_2(MainLoginLayer::onLoginGuessTouched, this));
	this->addChild(buttonGuessLogin);

	auto buttonAcountPPLogin = ButtonAdjustClikableAreaSize::create(PNG_FRAME_LOGIN_LOGIN_WITH_PP,"","",ui::Widget::TextureResType::PLIST);
	buttonAcountPPLogin->setPosition(Vec2(visibleSize.width / 2 + 160, visibleSize.height / 2 - 155));
	buttonAcountPPLogin->setClickableAreaSize(Size(buttonAcountPPLogin->getContentSize().width * 2, buttonAcountPPLogin->getContentSize().height));
	buttonAcountPPLogin->setZoomScale(0);
	buttonAcountPPLogin->addTouchEventListener(CC_CALLBACK_2(MainLoginLayer::onLoginAccountPPTouched, this));
	this->addChild(buttonAcountPPLogin);

	auto bottomSprite = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_LOGIN_BOTTOM_TEXT);
	bottomSprite->setPosition(Vec2(visibleSize.width / 2, 67));
	this->addChild(bottomSprite);

	auto playAsGuessText = Label::createWithTTF(PLAY_AS_GUESS, FONT_HelveticaNeue_Thin, 30);
	playAsGuessText->setTextColor(Color4B::BLACK);
	playAsGuessText->setPosition(Vec2(visibleSize.width / 2 - 117, visibleSize.height / 2 - 151));
	this->addChild(playAsGuessText);

	auto playPPAcountText = Label::createWithTTF(LOGIN_WITH_PLAYPALACE, FONT_HelveticaNeue_Thin, 30);
	playPPAcountText->setTextColor(Color4B::BLACK);
	playPPAcountText->setPosition(Vec2(visibleSize.width / 2 + 338, visibleSize.height / 2 - 142));
	this->addChild(playPPAcountText);

    
#if IS_RUN_WITHOUT_NW
    if (!Configs::isProduction)
    {
        auto testVersionLabel = Label::createWithTTF(
                                                     TTFConfig(FONT_HelveticaNeue_Thin, 40),
                                                     "Test version: " + Configs::versionName
                                                     );
        testVersionLabel->setTextColor(Color4B::BLACK);
        testVersionLabel->setPosition(Vec2(
                                           testVersionLabel->getContentSize().width / 2 + 20,
                                           testVersionLabel->getContentSize().height / 2 + 20
                                           ));
        this->addChild(testVersionLabel);
    }
#endif


	return true;
}

#if IS_DEBUG
void MainLoginLayer::forceCallBtnLoginGuest(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
	this->isClickedLogin = false;
	onLoginGuessTouched(sender, type);
}
#endif

void MainLoginLayer::onLoginGuessTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != ui::Widget::TouchEventType::ENDED
		|| this->isClickedLogin)
	{
		return;
	}
    
#if IS_RUN_WITHOUT_NW
    autoLogin();
    return;
#endif

	this->isClickedLogin = true;
	string usernameLocal = UserDefault::getInstance()->getStringForKey(STORING_KEY_USER_NAME_GUESS);
	string passwordLocal = UserDefault::getInstance()->getStringForKey(STORING_KEY_PASSWORD_GUESS);
	//if user or pass local empty => call generate guess account
	if (usernameLocal.empty()
		|| passwordLocal.empty())
	{
		auto loginScene = this->loginScene;
		//callback after generate account
		auto callback = [this, loginScene](
			int coreResultCode,
			rapidjson::Value &doc,
			string responseAsString
			) {
			this->isClickedLogin = false;
			switch (coreResultCode)
			{
			case RESULT_CODE_VALID:
			{
				if (Configs::printConsoleLog)
				{
					CCLOG("SIGN UP GESS SUCESS");
				}
				string usernameLocalNew = "";
				string passwordLocalNew = "";
				//storing username and password local
				if (doc.HasMember(JSONFieldConstant::USER_NAME.c_str()))
				{
					usernameLocalNew = doc[JSONFieldConstant::USER_NAME.c_str()].GetString();
					UserDefault::getInstance()->setStringForKey(STORING_KEY_USER_NAME_GUESS, usernameLocalNew);
				}
				if (doc.HasMember(JSONFieldConstant::INFO.c_str()))
				{
					passwordLocalNew = doc[JSONFieldConstant::INFO.c_str()].GetString();
					UserDefault::getInstance()->setStringForKey(STORING_KEY_PASSWORD_GUESS, passwordLocalNew);
				}
				UserDefault::getInstance()->flush();
				this->loginGuess(
					usernameLocalNew,
					passwordLocalNew
				);
				break;
			}
			default:
			{
				loginScene->showNotificationLoginPopup(
					MessageConstant::LOGIN_FAIL,
					MessageConstant::MESSAGE_SOMETHING_WRONG
				);
			}
			}
			PopupManager::getInstance()->getLoadingAnimation()->hide();
		};
		PopupManager::getInstance()->getLoadingAnimation()->prepareAndShow(this->getParent());
		NetworkManager::getInstance()->generateGuessAcount(
			callback,
			[this](std::string result)
		{
			this->isClickedLogin = false;
			PopupManager::getInstance()->getLoadingAnimation()->hide();
		},
			[this](std::string result)
		{
			this->isClickedLogin = false;
			PopupManager::getInstance()->getLoadingAnimation()->hide();
		}
		);
	}
	//case username and pass local were exist
	else
	{
		this->loginGuess(
			usernameLocal,
			passwordLocal
		);
	}
}

void MainLoginLayer::onLoginAccountPPTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
    
#if IS_RUN_WITHOUT_NW
    autoLogin();
    return;
#endif
	if (type == ui::Widget::TouchEventType::ENDED)
	{
		this->loginScene->moveCameraToView(LoginViews::PPLoginView);
	}
}

void MainLoginLayer::onLoginFacebookTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{

    
    
#if IS_RUN_WITHOUT_NW
    autoLogin();
    return;
#endif
	if (type != ui::Widget::TouchEventType::ENDED
		|| this->isClickedLogin)
	{
		return;
	}
	this->isClickedLogin = true;
	PopupManager::getInstance()->getLoadingAnimation()->prepareAndShow(this->getParent());
#ifdef SDKBOX_ENABLED
	PluginManager::getInstance()->getFacebookController()->login(
		[this](bool isSuccess, const std::string &error)
	{
		this->isClickedLogin = false;
		PopupManager::getInstance()->getLoadingAnimation()->hide();
		if (isSuccess)
			this->loginScene->gotoInitSessionScene(0, ppEnum::LoginAndInitSSFrom::Facebook);
		else if (error == "cancelled" || error == "cancel") {}
		else if (error == "CONNECTION_FAILURE: CONNECTION_FAILURE")
			this->loginScene->gotoLoginSceneLostConnection();
        else
		    this->loginScene->gotoLoginScene(false,MessageConstant::MESSAGE_LOGIN_FACEBOOK,MessageConstant::MESSAGE_SOMETHING_WRONG);
		
	});
#else
	PopupManager::getInstance()->getLoadingAnimation()->hide();
	this->loginScene->showNotificationLoginPopup(
		"CHUA HO TRO WIN 32",
		"CHUA HO TRO WIN 32",
		[this]()
	{
		this->isClickedLogin = false;
		PopupManager::getInstance()->getLoadingAnimation()->hide();
	}
	);
#endif
}

void MainLoginLayer::loginGuess(
	std::string username,
	std::string password
)
{
	if (Configs::printConsoleLog)
	{
		CCLOG("LOGIN GUESS");
	}
    
    
	//callback onLoginTouched account pp 
	auto callback = [this](
		int coreResultCode,
		rapidjson::Value &doc,
		string responseAsString)
	{
		this->isClickedLogin = false;
		StringBuffer strbuf;
		Writer<StringBuffer> writer(strbuf);
		doc.Accept(writer);

		string stringBeanResult = string(strbuf.GetString());
		switch (coreResultCode)
		{
		case RESULT_CODE_VALID:{
                log("User Info\n %s\n",responseAsString.c_str());
			InfoManager::getInstance()->updateUserInfo(doc);
			NetworkManager::getInstance()->setLoginToken(doc[JSONFieldConstant::LOGIN_TOKEN.c_str()].GetString());
			//go to init session scene
			loginScene->gotoInitSessionScene(0, ppEnum::LoginAndInitSSFrom::Guess);
			break;
		}
		default:
			loginScene->handleErrorResultCodeForLoginScene(coreResultCode);
			break;
		}
		PopupManager::getInstance()->getLoadingAnimation()->hide();
	};
	PopupManager::getInstance()->getLoadingAnimation()->prepareAndShow(this->getParent());
    
#if IS_RUN_WITHOUT_NW
    TestManager::getInstance()->loginGuessAcount(callback);
    return;
#endif
    
	NetworkManager::getInstance()->loginGuessAcount(
		username,
		password,
		callback,
		[this](std::string result)
	{
		this->isClickedLogin = false;
		PopupManager::getInstance()->getLoadingAnimation()->hide();
	},
		[this](std::string result)
	{
		this->isClickedLogin = false;
		PopupManager::getInstance()->getLoadingAnimation()->hide();
	}
	);
}

void MainLoginLayer::autoLogin() {
    loginGuess("","");
}

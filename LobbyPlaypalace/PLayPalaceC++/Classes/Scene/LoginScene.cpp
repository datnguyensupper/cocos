#include "Scene/LoginScene.h"
#include "Scene/InitSessionScene.h"
#include "Scene/LobbyScene.h"
#include "Scene/testScene/GameSlotTestScene.h"

#include "Manager/LanguageManager.h"
#include "Manager/PopupManager.h"
#include "Manager/PluginManager.h"
#include "Manager/ScaleManager.h"
#if IS_DEBUG
#include "Manager/Test/TestManager.h"
#endif

#include "Views/Login/MainLoginLayer.h"
#include "Views/Login/PPLoginLayer.h"
#include "Views/Login/ResetPassLayer.h"
#include "Views/Login/SignUpLayer.h"
#include "Views/Login/NotiLoginPopup.h"
#include "Views/Tutorial/Tutorial.h"

#include "Util/UtilFunction.h"
USING_NS_CC;
Scene* LoginScene::createScene(std::string title, std::string message)
{
    // 'scene' is an autorelease object
    auto scene = LoginScene::create();
	scene->setTag(ppEnum::GameScene::Login);
	PopupManager::getInstance()->reset();

	if (!message.empty()
		&& PopupManager::getInstance()->getNotificationLoginPopup())
	{
        if(title.empty()) title =MessageConstant::MESSAGE_ERROR;
		scene->showNotificationLoginPopup(
			title,
			message
		);
	}

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LoginScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !BaseScene::init() )
    {
        return false;
    }

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("login/login.plist");

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	ScaleManager::getInstance()->init(visibleSize, origin);

	//INIT POPUP MANAGER IN LOGIN SCENE
	PopupManager::getInstance()->initThingsLoginScene();

#if IS_DEBUG
	/*test:*/
	//this->scheduleOnce(schedule_selector(LoginScene::gotoGameScene), 0.5);
	//return true;
#endif

	parent = Node::create();
	addChild(parent);
	
	//position 1
	this->mainLoginLayer = MainLoginLayer::create(this);
	this->mainLoginLayer->setPosition(Vec2(origin.x , origin.y ));
	parent->addChild(this->mainLoginLayer);

	//position 2
	this->ppLoginLayer = PPLoginLayer::create(this);
	this->ppLoginLayer->setPosition(Vec2(this->mainLoginLayer->getPosition().x + origin.x + visibleSize.width, origin.y));
	parent->addChild(this->ppLoginLayer);

	//position 2
	this->resetPassLayer = ResetPassLayer::create(this);
	this->resetPassLayer->setPosition(Vec2(this->ppLoginLayer->getPosition().x + origin.x + visibleSize.width, origin.y));
	parent->addChild(this->resetPassLayer);

	//position 3
	this->signUpLayer = SignUpLayer::create(this);
	this->signUpLayer->setPosition(resetPassLayer->getPosition());
	parent->addChild(this->signUpLayer);

	this->notificationLoginPopup = PopupManager::getInstance()->getNotificationLoginPopup();



#if IS_DEBUG
	TestManager::getInstance()->createTestButton(this);
#endif

    return true;
}

void LoginScene::moveCameraToView(LoginViews loginView)
{
	if (this->getNumberOfRunningActions() > 0) {
		return;
	}
	int xPosition = 0;
	switch (loginView)
	{
	case MainLoginView:
		xPosition = this->mainLoginLayer->getPosition().x - origin.x;
		break;
	case PPLoginView:
		xPosition = this->ppLoginLayer->getPosition().x ;
		break;
	case ResetPassView:
		xPosition = this->resetPassLayer->getPosition().x;
		this->resetPassLayer->setVisible(true);
		this->signUpLayer->setVisible(false);
		break;
	case SignUpView:
		xPosition = this->signUpLayer->getPosition().x;
		this->resetPassLayer->setVisible(false);
		this->signUpLayer->setVisible(true);
		break;
	default:
		break;
	}
	auto actionMoveByLayer = MoveTo::create(0.2f, Vec2(-xPosition, 0));
	auto ease_in = EaseOut::create(actionMoveByLayer, 0.2f);
	parent->runAction(ease_in);

	//auto defaultCamera = Camera::getDefaultCamera();
	//// 2017-02-06: Kiet: get distance position will move to and current pos of camera 
	//int distancePositionCamera =
	//	position * visibleSize.width - (defaultCamera->getPosition().x - visibleSize.width / 2);
	//auto actionMoveByCamera = MoveBy::create(0.2f, Vec2(distancePositionCamera, 0));
	//defaultCamera->runAction(actionMoveByCamera);
}

void LoginScene::showNotificationLoginPopup(
	std::string title,
	std::string body,
	std::function <void(void)> callbackOK,
	std::function <void(void)> callbackCancle
)
{
	//this->notificationLoginPopup->setPosition(-this->getPosition());
	this->notificationLoginPopup->show(
		this,
		title,
		body,
		callbackOK,
		callbackCancle
	);
}

void LoginScene::handleErrorResultCodeForLoginScene(
	int coreResultCode,
	const std::string &title
)
{
	string titleNotif = title.empty() ? MessageConstant::LOGIN_FAIL : title;
	string bodyNotif = MessageConstant::MESSAGE_SOMETHING_WRONG;
	switch (coreResultCode)
	{
	case RESULT_CODE_USER_NOT_EXIST:
		bodyNotif = MessageConstant::RESET_PASSWORD_USER_NOT_EXIST;
		break;
	case RESULT_CODE_USER_NOT_ACTIVATE:
	{
		bodyNotif = MessageConstant::MESSAGE_USER_NOT_ACTIVE;
		break;
	}
	case RESULT_CODE_SERVER_MAINTENANCE:
	{
		bodyNotif = MessageConstant::MESSAGE_LOGIN_MAINTENANCE;
		break;
	}
	case RESULT_CODE_INVALID_PASSWORD:
	{
		bodyNotif = MessageConstant::LOGIN_FAIL_WRONG_USER_OR_PASSWORD;
		break;
	}
	case RESULT_CODE_USER_EXIST:
	{
		bodyNotif = MessageConstant::SIGNUP_FAIL_USER_EXIST;
		break;
	}
	case RESULT_CODE_PASSWORD_POLICY_ERROR:
	{
		bodyNotif = MessageConstant::SIGNUP_FAIL_PASSWORD_POLICY;
		break;
	}
	default:
		break;
	}
	showNotificationLoginPopup(
		titleNotif,
		bodyNotif
	);
}

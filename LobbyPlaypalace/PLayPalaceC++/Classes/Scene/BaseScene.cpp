#include "BaseScene.h"
#include "Manager/ScaleManager.h"
#include "Manager/PluginManager.h"
#include "Manager/InfoManager.h"
#include "Manager/PopupManager.h"
#include "Constant/LobbyConstant.h"
#include "LoginScene.h"
#include "LobbyScene.h"
#include "LuckyWheelScene.h"
#include "SlotGame/GameSlotScene.h"
#include "Scene/testScene/CoinAnimationTestScene.h"
#include "Configs.h"
#include "Views/Popup/NotificationPopup.h"
#include "Helper/Helper4Scene.h"

USING_NS_CC;


BaseScene* BaseScene::currentScene = nullptr;

// on "init" you need to initialize your instance
bool BaseScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }
    
    currentScene = this;
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    scaleDownRatio = ScaleManager::getInstance()->getExactlyScaleDownRatio();
    messageGoToLoginScene = "";
    
    return true;
    
}

BaseScene* BaseScene::getCurrentScene(){
    return currentScene;
}

void BaseScene::gotoLoginScene(std::string title, std::string message){
	if (getTag() == ppEnum::GameScene::Login) {
		if(!message.empty()) ((LoginScene*)this)->showNotificationLoginPopup(title,message);
		return;
	}
    if(Helper4Scene::isUnexpectedProblemWithCurrentScene()){
        if(isGoingToLoginScene) return;
        messageGoToLoginScene = message;
        titleGoToLoginScene = title;
        isGoingToLoginScene = true;
        this->scheduleOnce(schedule_selector(InitSessionScene::gotoLoginSceneWithDelay), 2.0);
//        gotoLoginSceneWithDelay(message, 2.0f);
    }else{
        Director::getInstance()->replaceScene(
          TransitionFade::create(
             Configs::TIME_TRANSITION_FADE_SCENE,
             LoginScene::createScene(title,message)
             )
          );
    }
    
}

void BaseScene::gotoLoginSceneServerMaintenance(){
    gotoLoginScene(MessageConstant::MESSAGE_SERVER_MAINTENANCE_TITLE,MessageConstant::MESSAGE_LOGIN_MAINTENANCE);
}

void BaseScene::gotoLoginSceneLostConnection(){
    gotoLoginScene(MessageConstant::MESSAGE_NETWORK_ERROR,MessageConstant::MESSAGE_LOST_INTERNET_CONNECTION);
}

void BaseScene::gotoLoginSceneLoginAnotherPlace(){
    gotoLoginScene(MessageConstant::MESSAGE_NETWORK_ERROR,"Your account has been logged in from another location. Please reload the game");
}

void BaseScene::gotoLoginSceneSomethingWrong(){
    gotoLoginSceneLostConnection();
//    gotoLoginScene(MessageConstant::MESSAGE_NETWORK_ERROR,MessageConstant::MESSAGE_SOMETHING_WRONG);
}

void BaseScene::gotoLoginSceneWithDelay(float delay){
    isGoingToLoginScene = false;
    Director::getInstance()->replaceScene(
      TransitionFade::create(
         Configs::TIME_TRANSITION_FADE_SCENE,
         LoginScene::createScene(titleGoToLoginScene,messageGoToLoginScene)
         ));
//    countTimeDelayGoToLoginScene = 0;
//    timerDelayGoToLoginScene = delay;
//    messageGoToLoginScene = message;
}

//void BaseScene::forceGotoLoginScene(std::string message){
//
//    Director::getInstance()->replaceScene(
//      TransitionFade::create(
//         Configs::TIME_TRANSITION_FADE_SCENE,
//         LoginScene::createScene(message)
//         )
//      );
//    
//    messageGoToLoginScene = "";
//    
//}

void BaseScene::gotoLobbyScene(float dt)
{
    //set custom id for adcolony
    PluginManager::getInstance()->getAdcolonyController()->initWithCustomId(
    ToString(InfoManager::getInstance()->getUserInfo()->id)
    );
    Director::getInstance()->replaceScene(
      TransitionFade::create(
         Configs::TIME_TRANSITION_FADE_SCENE,
         LobbyScene::createScene(ppEnum::GameScene::InitSession)
         )
      );
}



void BaseScene::onEnter()
{
    Scene::onEnter();
    //play bg music
    currentScene = this;
}

void BaseScene::update(float dt){
//    if(countTimeDelayGoToLoginScene >= 0) {
//        countTimeDelayGoToLoginScene += dt;
//        if(countTimeDelayGoToLoginScene >= timerDelayGoToLoginScene) {
//            countTimeDelayGoToLoginScene = -1;
//            forceGotoLoginScene(messageGoToLoginScene);
//        }
//    }
    
}

/**
 Dat: go to Lobby
 */
void BaseScene::gotoLuckyWheelScene(float dt) {
    
    //go to init session scene
    Director::getInstance()->replaceScene(
      TransitionFade::create(
         Configs::TIME_TRANSITION_FADE_SCENE,
         LuckyWheelScene::createScene()
         )
      );
    
}


/**
 Dat: go to Slot Game Test Scene
 */
void BaseScene::gotoGameTestScene(float dt) {
    
    //go to init session scene
    Director::getInstance()->replaceScene(
      TransitionFade::create(
         Configs::TIME_TRANSITION_FADE_SCENE,
         CoinAnimationTestScene::createScene()
         )
      );
    
}

/// <summary>
/// Dat: go to game slot scene
/// </summary>
/// <param name="gameId"></param>
GameSlot::GameSlotScene* BaseScene::gotoGameSlotScene(int gameId) {
    
    return GameSlot::GameSlotScene::showGame(gameId);
}

/**
 Dat: go to InitSession
 */
void BaseScene::gotoInitSessionScene(float dt, ppEnum::LoginAndInitSSFrom loginFrom) {
    
    //go to init session scene
    Director::getInstance()->replaceScene(
      TransitionFade::create(
         Configs::TIME_TRANSITION_FADE_SCENE,
         InitSessionScene::createScene(loginFrom)
         )
      );
    
}

/**
 Dat: go to InitSession
 */
void BaseScene::gotoInitSessionScene(float dt) {
    //go to init session scene
    Director::getInstance()->replaceScene(
      TransitionFade::create(
         Configs::TIME_TRANSITION_FADE_SCENE,
         InitSessionScene::createScene(ppEnum::LoginAndInitSSFrom::PPAccount)
         )
      );
    
}

